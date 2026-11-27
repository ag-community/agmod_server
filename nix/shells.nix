{
  perSystem =
    {
      pkgs,
      releasePkgs,
      ...
    }:
    {
      devShells.default = pkgs.mkShell {
        packages = [
          pkgs.gnumake
          pkgs.pkg-config
          pkgs.git
          pkgs.python3
          pkgs.curl
          pkgs.unzip
          pkgs.xmake
          pkgs.just
          pkgs.cargo
          pkgs.rustc
          pkgs.clang-tools
          pkgs.pre-commit
          pkgs.nixfmt
          pkgs.actionlint
          pkgs.patchelf
          releasePkgs.pkgsi686Linux.gcc
        ];

        shellHook = ''
          export AG_HOST_CC="${pkgs.gcc}/bin/gcc"
          export AG_HOST_CXX="${pkgs.gcc}/bin/g++"
          export AG_RUSTC="${pkgs.rustc}/bin/rustc"
          export AG_PATCHELF="${pkgs.patchelf}/bin/patchelf"
          export AG_GLIBC_LIB="${pkgs.glibc.out}/lib"
          export AG_CXX_RUNTIME_LIB="${pkgs.gcc.cc.lib}/lib"

          echo "AG server (Half-Life 1) - 32-bit x86, glibc 2.31 (nixos-20.09)"
          just --list 2>/dev/null || true
        '';
      };
    };
}
