-- set_menu exposes the task as an xmake command.
task("amxx-offsets")
    set_menu {
        usage = "xmake amxx-offsets",
        description = "Generate AMXX gamedata from the built server library.",
        options = {}
    }
    on_run(function ()
        import("core.project.project")
        import("core.project.config")
        import("lib.detect.find_tool")
        import("net.http")
        import("utils.archive.extract")
        -- xmake doesn't load the build config for tasks.
        config.load()

        local version = "1.0.1"
        local url = "https://github.com/tmp64/amxx-offset-generator/releases/download/v" .. version ..
            "/amxx-offset-generator-v" .. version .. ".zip"
        local sha256 = "8fb1b0dd311cdbade408621bad66bf58c2e3472a8c68d3126a5b7b1b26c6da8e"
        local projectdir = os.projectdir()
        local target = project.target("server")
        local targetfile = target:targetfile()
        local plat = target:plat()

        if not os.isfile(targetfile) then
            raise("server target is not built: %s", targetfile)
        end

        if not (plat == "windows" or plat == "linux") then
            raise("AMXX offset generation is supported on Windows and Linux only")
        end

        local cache = path.join(projectdir, "build", "amxx-offset-generator")
        local archive = path.join(cache, "amxx-offset-generator-v" .. version .. ".zip")
        local source = path.join(cache, "amxx-offset-generator-v" .. version)

        os.mkdir(cache)

        if not os.isfile(archive) or hash.sha256(archive) ~= sha256 then
            os.tryrm(archive)
            http.download(url, archive)
            local actual = hash.sha256(archive)
            if actual ~= sha256 then
                os.tryrm(archive)
                raise("sha256 mismatch: expected %s, got %s", sha256, actual)
            end
        end

        if not os.isdir(source) then
            extract.main(archive, cache)
        end

        local class_list = path.join(projectdir, "src", "game", "server", "AmxxOffsetClassList.txt")
        local platform_name = plat == "windows" and "windows" or "linux"
        local json = path.join(projectdir, "build", "ag-amxx-offsets-" .. platform_name .. ".json")
        local out = path.join(projectdir, "build", "amxx-offsets")
        local exporter
        local argv

        if plat == "windows" then
            local pdb = target:symbolfile()
            if not pdb or not os.isfile(pdb) then
                raise("PDB not found for the server library: %s", pdb or "nil")
            end

            exporter = path.join(source, "win64", "OffsetExporter.Pdb.exe")
            argv = {"--class-list", class_list, "--pdb", pdb, "--out", json}
        else
            exporter = path.join(source, "linux64", "OffsetExporter.Dwarf")
            -- The ZIP doesn't set +x.
            os.vrunv("chmod", {"+x", exporter})
            local patchelf = os.getenv("AG_PATCHELF")
            local glibc = os.getenv("AG_GLIBC_LIB")
            local cxx = os.getenv("AG_CXX_RUNTIME_LIB")
            -- Exporter links against the host glibc.
            if os.isfile("/etc/NIXOS") and patchelf and glibc and cxx then
                local patched = path.join(source, "linux64", "OffsetExporter.Dwarf.patched")
                os.cp(exporter, patched)
                os.vrunv(patchelf, {
                    "--set-interpreter", path.join(glibc, "ld-linux-x86-64.so.2"),
                    "--set-rpath", glibc .. ":" .. cxx,
                    patched,
                })
                exporter = patched
            end

            argv = {"--class-list", class_list, "--so", targetfile, "--out", json}
        end

        -- The AMXX writer is Python.
        local python = find_tool("python3") or find_tool("python")
        if not python then
            raise("Python is required to run the AMXX offset generator")
        end

        os.mkdir(out)
        os.vrunv(exporter, argv)
        os.vrunv(python.program, {
            path.join(source, "create_amxx_files.py"),
            "--" .. platform_name .. "=" .. json,
            "--out", out,
            "--banner", "AG offset file. Generated using amxx-offset-generator.",
            "--file-prefix", "ag",
        })
    end)

task("hamdata")
    set_menu {
        usage = "xmake hamdata",
        description = "Generate hamdata.ini from the built server library.",
        options = {}
    }
    on_run(function ()
        import("core.project.project")
        import("core.project.config")
        -- xmake doesn't load the build config for tasks.
        config.load()

        local repo = "https://github.com/ag-community/hamdata_ini_generator"
        local ref = "0207bd185fd1c7baa9ce00c6b24ca3434404feac"
        local target = project.target("server")
        -- vtable runs from the release directory.
        local targetfile = path.absolute(target:targetfile())

        if not os.isfile(targetfile) then
            raise("server target is not built: %s", targetfile)
        end

        if target:plat() ~= "linux" then
            raise("hamdata generation is Linux-only")
        end

        local root = path.join(os.projectdir(), "build", "hamdata_ini_generator")
        if not os.isdir(path.join(root, ".git")) then
            -- Stale caches break git clone.
            os.tryrm(root)
            os.vrunv("git", {"clone", repo, root})
        end

        os.vrunv("git", {"fetch", "--depth", "1", "origin", ref}, {curdir = root})
        os.vrunv("git", {"checkout", "--detach", ref}, {curdir = root})

        -- hamdata builds for the host, not the target.
        local envs = os.getenvs()
        local host_cc = os.getenv("AG_HOST_CC")
        if host_cc then
            envs.CC = host_cc
            envs.CXX = os.getenv("AG_HOST_CXX") or host_cc
            envs.CARGO_TARGET_X86_64_UNKNOWN_LINUX_GNU_LINKER = host_cc
        end

        local rustc = os.getenv("AG_RUSTC")
        if rustc then
            envs.RUSTC = rustc
        end

        os.vrunv("make", {"release"}, {curdir = root, envs = envs})

        local release = path.join(root, "target", "release")
        -- vtable writes output/ relative to the working directory.
        os.vrunv(path.join(release, "vtable"), {"vtable-dump", targetfile}, {curdir = release})

        local generated = path.join(release, "output", "auto_hamdata190.ini")
        if not os.isfile(generated) then
            raise("hamdata was not generated: %s", generated)
        end

        os.cp(generated, path.join(os.projectdir(), "build", "hamdata.ini"))
    end)
