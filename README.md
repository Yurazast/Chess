# Chess
Standard chess game for two players, developed in C++ using SFML graphics library.

![Demo](resources/images/chess.png)

## Installation
You need to have [SFML library](https://www.sfml-dev.org/download.php) installed before compiling the project.

Compile the project by following these steps:

- Generate makefiles in `build` directory:

```bash
cmake . -B build
```

- Build the project:

```bash
cd build/
make
```

Executable file should be now in `build/Chess`.

## Usage
In order to properly run the game, you should place the executable file near the `resources` directory.

Then, run the application with the following command:

```bash
./Chess
```

You can restart the game by pressing `R`.
