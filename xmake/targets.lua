target("server")
    set_kind("shared")
    set_basename("ag")
    set_prefixname("")

    add_files(ag.path("src/game/server/*.cpp"))
    add_files(ag.path("src/game/server/ag/*.cpp"))
    add_files(ag.path("src/game/server/wpn_shared/*.cpp"))
    -- agstats needs AGSTATS, glock is built from wpn_shared, the rest is unused.
    remove_files(
        ag.path("src/game/server/ag/agstats.cpp"),
        ag.path("src/game/server/AI_BaseNPC_Schedule.cpp"),
        ag.path("src/game/server/glock.cpp"),
        ag.path("src/game/server/mpstubb.cpp"),
        ag.path("src/game/server/playermonster.cpp"),
        ag.path("src/game/server/stats.cpp"),
        ag.path("src/game/server/Wxdebug.cpp"))

    add_files(ag.path("src/common/parsemsg.cpp"))
    add_files(ag.path("src/game/shared/mathlib.cpp"))
    add_files(ag.path("src/pm_shared/*.cpp"))

    add_includedirs(
        ag.path("src/game/server"),
        ag.path("src/game/server/ag"),
        ag.path("src/game/shared"),
        ag.path("src/public"),
        ag.path("src/common"),
        ag.path("src/engine"),
        ag.path("src/pm_shared"))

    add_packages("source_sdk")

    add_defines(
        "CLIENT_WEAPONS",
        -- Source SDK mathlib options.
        "MATHLIB_USE_C_ASSERT",
        "MATHLIB_VECTOR_NONTRIVIAL",
        "MATHLIB_HEADER_ONLY")

    if is_plat("windows") then
        -- nodes.cpp checks this.
        add_defines("PLATFORM_WINDOWS")
    else
        -- port.h checks this.
        add_defines("PLATFORM_UNIX")
        -- platform.h and mathlib headers check these.
        add_defines("GNUC", "POSIX", "LINUX", "_LINUX")
        -- MSVC names used by the HL SDK.
        add_defines("_stricmp=strcasecmp", "_strnicmp=strncasecmp",
                    "_snprintf=snprintf", "_alloca=alloca",
                    "_vsnprintf=vsnprintf", "_snwprintf=swprintf")
    end

    ag_library_flags()
target_end()
