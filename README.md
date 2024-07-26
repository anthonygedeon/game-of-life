# Conway's Game of Life

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Rules](#rules)
- [Controls](#controls)
- [License](#license)

## Description

This project is an implementation of Conway's Game of Life using C99. The Game of Life is a zero-player game, meaning its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

## Features

- **TODO**: Infinite grid simulation.
- Customizable initial configurations.
- Step through generations manually or automatically.
- Adjustable speed for automatic generation progression.

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/anthonygedeon/game-of-life.git
    cd game-of-life
    ```

2. Compile the source code:
    ```sh
    mkdir build
    cd build
    cmake ..
    make 
    ```

## Usage

1. Run the executable:
    ```sh
    ./game-of-life
    ```

2. Follow the on-screen instructions to input your initial configuration.

3. Choose whether to step through generations manually or let the game run automatically.

## Rules

The Game of Life is played on a grid of square cells. Each cell is either alive or dead. Each generation is calculated based on the following rules:

1. **Birth**: A dead cell with exactly three live neighbors becomes a live cell.
2. **Survival**: A live cell with two or three live neighbors stays alive.
3. **Death**: In all other cases, a cell dies or remains dead.

## Controls


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

