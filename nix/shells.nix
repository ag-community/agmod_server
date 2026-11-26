{
  perSystem =
    {
      pkgs,
      releasePkgs,
      ...
    }:
    let
      i686 = pkgs.pkgsi686Linux;

      vcpkgTripletEnv = ''
        export VCPKG_DEFAULT_TRIPLET=x86-linux
        export VCPKG_DEFAULT_HOST_TRIPLET=x86-linux
        export VCPKG_FORCE_SYSTEM_BINARIES=1
      '';
    in
    {
      devShells.default = pkgs.mkShell {
        packages = [
          pkgs.cmake
          pkgs.ninja
          pkgs.gnumake
          pkgs.pkg-config
          pkgs.git
          pkgs.python3
          pkgs.vcpkg
          pkgs.clang-tools
          pkgs.pre-commit
          pkgs.nixfmt
          pkgs.actionlint
          i686.gcc
          i686.libGL
        ];

        shellHook = ''
          ${vcpkgTripletEnv}

          if [ -d "$PWD/vcpkg/scripts/buildsystems" ]; then
            export VCPKG_ROOT="$PWD/vcpkg"
          fi

          echo "AG server (Half-Life 1) - 32-bit x86"
          echo "  git submodule update --init --recursive        # fetch source_sdk"
          echo "  git clone https://github.com/microsoft/vcpkg vcpkg"
          echo "  export VCPKG_ROOT=\"\$PWD/vcpkg\""
          echo "  cmake --preset github-actions"
          echo "  cmake --build --preset github-actions --target ci-server"
        '';
      };

      devShells.release = releasePkgs.mkShell {
        packages = [
          releasePkgs.cmake
          releasePkgs.ninja
          releasePkgs.gnumake
          releasePkgs.pkg-config
          releasePkgs.git
          releasePkgs.pkgsi686Linux.gcc
        ];

        shellHook = ''
          ${vcpkgTripletEnv}
          echo "AG server / release - 32-bit x86, older glibc from nixos-24.05"
        '';
      };
    };
}
