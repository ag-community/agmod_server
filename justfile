format_files := replace(`find src -type f \( -name '*.h' -o -name '*.cpp' -o -name '*.cc' \) 2>/dev/null`, "\n", " ")

# List available recipes
default:
    @just --list

# Build the server (debug | release | releasedbg)
build mode="debug":
    #!/usr/bin/env bash
    set -euo pipefail

    mode="{{mode}}"
    case "$mode" in
        debug|release|releasedbg) ;;
        *)
            echo "Invalid mode: $mode (valid: debug, release, releasedbg)" >&2
            exit 1
            ;;
    esac

    xmake f -y -a x86 -m "$mode" -c
    xmake -y

# Generate AMXX gamedata
amxx-offsets:
    just build releasedbg
    xmake amxx-offsets

# Generate hamdata.ini
hamdata:
    just build releasedbg
    xmake hamdata

# Remove build and xmake caches
clean:
    rm -rf build .xmake

# Build and install into a mod directory
dist prefix mode="release":
    just build {{mode}}
    xmake install -o {{prefix}}

# Format sources
format:
    clang-format -i {{format_files}}

# Check formatting
check:
    clang-format --dry-run --Werror {{format_files}}
