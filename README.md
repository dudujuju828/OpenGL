# OpenGL Projects
This repository contains all of my OpenGL projects. Most will be games, but I'm sure some of them will be other sorts of applications.
Currently, the sound only runs on linux as I'm using a custom engine.
## Pong
![Project Banner](./Pong/assets/pong_gameplay.gif)
### Key Mappings

- **`0`**: Toggle left paddle AI
- **`Space`**: Pause or resume the ball's motion

## Requirements

To run my projects, you'll need the following includes in your compilers directory.
- `glad/glad.h`
- `GLFW/glfw3.h`
- `alsa/asoundlib.h`

## OpenGL Version

All projects in this repository are developed using OpenGL version 3.3.

## Operating System Information
The projects were built for linux, but they are built upon GLFW, a cross platform windowing library.
The sound however, is only available on linux systems, and attempting to compile on other OS' may raise issues.

## Compilation Example

To compile one of the projects (for example, Pong), follow these steps:

```bash
git clone "https://github.com/dudujuju828/OpenGL"
cd OpenGL/Pong
make
```

## 3D Landscape
![Project Banner](./Pong/assets/3DWorld.gif)
