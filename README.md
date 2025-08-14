# Triangle Transformations (SDL2)

This project demonstrates **2D geometric transformations** (translation, scaling, rotation, shearing, and reflection) on a triangle using **SDL2** in C.

## Features
- **Translation** → Move the triangle.
- **Scaling** → Grow or shrink the triangle relative to its centroid.
- **Rotation** → Rotate around the triangle's centroid.
- **Shearing** → Tilt the triangle horizontally or vertically.
- **Reflection** → Flip across X-axis or Y-axis.
- Displays both the **original triangle (green)** and the **transformed triangle (red)**.

## Controls
| Key        | Action                        |
|------------|--------------------------------|
| `T`        | Translate down and right       |
| `S`        | Scale up by 10%                |
| `R`        | Rotate by 15°                  |
| `H`        | Shear horizontally             |
| `X`        | Reflect across X-axis          |
| `Y`        | Reflect across Y-axis          |
| `ESC`      | Exit program                   |

## Requirements
Make sure you have:
- **SDL2** installed
- GCC / g++

### Installing SDL2
#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install libsdl2-dev
