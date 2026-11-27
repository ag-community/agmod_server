format_files := replace(`find src -type f \( -name '*.h' -o -name '*.cpp' -o -name '*.cc' \) 2>/dev/null`, "\n", " ")

default: build

build mode="debug":
    xmake f -y -a x86 -m {{mode}} -c
    xmake -y

release:
    just build release

release-dbg:
    just build releasedbg

amxx-offsets:
    just release-dbg
    xmake amxx-offsets

hamdata:
    just release-dbg
    xmake hamdata

clean:
    -xmake clean -a
    rm -rf build .xmake

dist prefix mode="release":
    just build {{mode}}
    xmake install -o {{prefix}}

format:
    clang-format -i {{format_files}}

check:
    clang-format --dry-run --Werror {{format_files}}
