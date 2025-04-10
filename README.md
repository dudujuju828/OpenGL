# OpenGL Projects
This repository contains all of my OpenGL projects. Most will be games, but I'm sure some of them will be other sorts of applications.
Currently, the sound only runs on linux as I'm using a custom engine.
## Pong
![Project Banner](./Pong/assets/pong_gameplay.gif)
### Key Mappings

- **`0`**: Toggle left paddle AI
- **`Space`**: Pause or resume the ball's motion

## Requirements

To run these projects, you must have the following dependencies installed in your compiler's include directory:
- `glad/glad.h`
- `GLFW/glfw3.h`
- `alsa/asoundlib.h`
- Other necessary OpenGL dependencies

## OpenGL Version

All projects in this repository are developed using OpenGL version 3.3.

## Compilation Example

To compile one of the projects (for example, Pong), follow these steps:

```bash
git clone "https://github.com/dudujuju828/OpenGL"
cd OpenGL/Pong
make
