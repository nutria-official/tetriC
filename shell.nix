{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    raylib
    clang
    cmake
    pkg-config
  ];

  shellHook = ''
    export LD_LIBRARY_PATH="${pkgs.raylib}/lib:$LD_LIBRARY_PATH"
    echo "tetriC environtment loaded. Compile with ./run.c"
  '';
}
