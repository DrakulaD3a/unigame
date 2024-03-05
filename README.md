# Unigame

An attempt to build a game supporting both linux and windows completely from scratch.

## Windows

Dependencies:

- [Visual Studio Community 2022](https://visualstudio.microsoft.com/downloads/) (with Visual C++ Build Tools 2022)

1. Generate the project:

```sh
configure.bat
```

2. Open the project in Visual Studio

## Linux

Dependencies:

- [SDL2](https://www.libsdl.org/)

1. Generate the project:

```sh
configure.sh
```

2. Build the project:

```sh
cd ./build
make
```

Now you have an executable `unigame` which can be runned.
