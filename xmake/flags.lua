function ag_library_flags()
    if is_plat("windows") then
        add_cxflags("/W3", "/MP")

        -- Legacy code triggers these warnings.
        add_cxflags("/wd4244", "/wd4305", "/wd4514", "/wd4100", "/wd26495", "/wd26451", "/wd26812")

        if ag.warnings_as_errors then
            add_cxflags("/WX")
        end
    else
        add_cxflags("-m32", "-mfpmath=sse", "-msse2")

        -- Only GiveFnptrsToDll is exported.
        add_cxflags("-fvisibility=hidden")

        -- Legacy code requires permissive mode and no strict aliasing.
        add_cxflags("-fpermissive", "-fno-strict-aliasing")

        add_cxflags("gcc::-Werror=return-type")

        -- Legacy code triggers these warnings.
        add_cxflags("-Wno-write-strings", "-Wno-unknown-pragmas", "-Wno-endif-labels")
        add_cxflags("-Wno-switch", "-Wno-unused-variable", "-Wno-unused-function", "-Wno-unused-value")
        add_cxflags("-Wno-pointer-arith", "-Wno-delete-non-virtual-dtor", "-Wno-invalid-offsetof", "-Wno-conversion-null")
        add_cxflags("gcc::-Wno-format-truncation", "gcc::-Wno-unused-but-set-variable")

        if ag.warnings_as_errors then
            add_cxflags("-Werror")
        end

        -- Avoid depending on the host libstdc++/libgcc.
        add_shflags("-m32", "-static-libstdc++", "-static-libgcc")
    end
end
