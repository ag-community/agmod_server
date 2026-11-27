set_project("agmod_server")
set_version("1.0.0")
set_languages("c++17")
set_policy("build.warning", true)

if is_plat("windows") then
    -- Git Bash makes xmake pick MinGW. Force MSVC.
    -- https://github.com/xmake-io/xmake/blob/v3.1.1/xmake/modules/private/detect/find_platform.lua#L24-L39
    set_toolchains("msvc")
end

if is_mode("debug") then
    set_symbols("debug")
elseif is_mode("release") then
    set_optimize("fastest")
    add_defines("NDEBUG")
elseif is_mode("releasedbg") then
    set_optimize("fast")
    set_symbols("debug")
    add_defines("NDEBUG")
end

option("warnings_as_errors")
    set_default(false)
    set_showmenu(true)
    set_description("Treat compiler warnings as errors")
option_end()

add_repositories("agmod-repo xmake")
add_requires("source_sdk")

includes("xmake/config.lua")
includes("xmake/flags.lua")
includes("xmake/install.lua")
includes("xmake/targets.lua")
includes("xmake/tasks.lua")
