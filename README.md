# EnTT Dino
[![MITLicensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![Build status](https://github.com/omgitsaheadcrab/entt_dino/actions/workflows/cmake.yml/badge.svg)

A [Dinosaur Game](https://en.wikipedia.org/wiki/Dinosaur_Game) clone using the
Entity Component System (ECS) from the [EnTT library](https://github.com/skypjack/entt).

## Dependencies

- [CMake](https://cmake.org/) version 3.7 or later.
- [SDL2](https://www.libsdl.org/) and
[SDL2_image](https://www.libsdl.org/projects/SDL_image/) for input and
rendering.

To install these on `Arch Linux`:

```sh
sudo pacman -S cmake sdl2 sdl2_image
```

For other platforms and distributions please refer to your package manager's
documentation or visit the official [installation instructions](https://wiki.libsdl.org/Installation).

## Building

To build simply run:

```sh
cd build/
cmake ..
make
```

The resultant `entt_dino` executable can then be found in `bin/`.

## Licence

Copyright (c) 2021 Tobias Backer Dirks.

Code released under [the MIT licence](LICENCE).
