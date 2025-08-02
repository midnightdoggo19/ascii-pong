# Pong built using ASCII characters

## Overview

- ASCII based pong game written in C.
- Uses ncurses to emulate terminal window.
- Currently only supports Linux distributions as ncurses doesn't support Windows

## Controls

#### Player 1:

w(up)
s(down)

#### Player 2:

i(up)
k(down)

## Run

On a Linux distribution:

1. Open the terminal
2. Go to the directory containing `pong` file
3. Execute the following command

```sh
./pong
```

4. Enjoy the game!

## Installation

- Install dependancies;

```sh
sudo apt-get install libncurses5-dev
```

- build the project by executing the following command:

```sh
gcc pong.c -o pong -lncurses
```
