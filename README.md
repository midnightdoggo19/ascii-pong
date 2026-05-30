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

1. Build the project (see Installation)
2. Open the terminal
3. Go to the directory containing `pong` file
4. Execute the following command

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
make
```
