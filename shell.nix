{
  pkgs ? import <nixpkgs> { },
}:

# To enter shell run: nix-shell

# General Nix Shell Pkgs
pkgs.mkShell {
  # use “packages" instead of buildInputs
  packages = with pkgs; [
  ];

  # Libraries to be linked
  buildInputs = with pkgs; [
    libGL # OpenGL library
    libGLU # OpenGL Utility library
    glfw # GLFW windowing library
    glew # GLEW OpenGL Extension Wrangler
    glm # OpenGL Maths Libraries
    # Or glad, if preferred:
    # glad
    sdl3
    raylib
    llvmPackages.libcxx
  ];

  # Build Tools
  nativeBuildInputs = with pkgs; [
    gcc # C++ compiler
    clang
    ninja
    cmake # Build system
    pkg-config
  ];

  # Set environment variables for OpenGL driver paths if needed,
  # especially if encountering issues with finding drivers.
  # This might be necessary if your system-wide OpenGL setup isn't fully propagated.
  shellHook = ''
    export SHELL=${pkgs.zsh}/bin/zsh

    export CC=clang
    export CXX=clang++

    export CPLUS_INCLUDE_PATH="${pkgs.gcc}/include/c++/14.3.0:${pkgs.gcc}/include/c++/14.3.0/x86_64-linux-gnu"
    export LIBRARY_PATH="${pkgs.gcc}/lib:${pkgs.gcc}/lib64"

    export LD_LIBRARY_PATH="/run/opengl-driver/lib:$LD_LIBRARY_PATH"

    exec ${pkgs.zsh}/bin/zsh
  '';
}
