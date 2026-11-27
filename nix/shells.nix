{
  perSystem =
    {
      pkgs,
      releasePkgs,
      ...
    }:
    let
      i686 = pkgs.pkgsi686Linux;
    in
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
          i686.gcc
          i686.libGL
        ];

        shellHook = ''
          export AG_HOST_CC="${pkgs.gcc}/bin/gcc"
          export AG_HOST_CXX="${pkgs.gcc}/bin/g++"
          export AG_CARGO="${pkgs.cargo}/bin/cargo"
          export AG_RUSTC="${pkgs.rustc}/bin/rustc"
          export AG_PATCHELF="${pkgs.patchelf}/bin/patchelf"
          export AG_GLIBC_LIB="${pkgs.glibc.out}/lib"
          export AG_CXX_RUNTIME_LIB="${pkgs.gcc.cc.lib}/lib"

          echo "AG server (Half-Life 1) - 32-bit x86"
          just --list 2>/dev/null || true
        '';
      };

      devShells.release = releasePkgs.mkShell {
        packages = [
          releasePkgs.gnumake
          releasePkgs.pkg-config
          releasePkgs.git
          releasePkgs.python3
          releasePkgs.curl
          releasePkgs.unzip
          releasePkgs.xmake
          releasePkgs.just
          releasePkgs.cargo
          releasePkgs.rustc
          releasePkgs.pkgsi686Linux.gcc
        ];

        shellHook = ''
          echo "AG server / release - 32-bit x86, older glibc from nixos-24.05"
          just --list 2>/dev/null || true
        '';
      };
    };
}
