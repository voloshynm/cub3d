# cub3D

A 3D maze exploration game built with raycasting techniques, inspired by the legendary Wolfenstein 3D. This project creates a dynamic first-person perspective view inside a maze using the MinilibX graphics library.

![cub3D Demo](https://img.shields.io/badge/42-Project-blue)
![Language](https://img.shields.io/badge/Language-C-brightgreen)
![Graphics](https://img.shields.io/badge/Graphics-MinilibX-orange)

## 🎮 Features

- **Real-time 3D rendering** using raycasting algorithms
- **Textured walls** with different textures for each cardinal direction
- **Smooth player movement** with WASD controls
- **Rotation controls** using arrow keys
- **Collision detection** to prevent walking through walls
- **Customizable maps** with .cub file format
- **Floor and ceiling colors** configuration
- **Cross-platform compatibility** (Linux/macOS)

## 🚀 Quick Start

### Prerequisites

- GCC compiler
- Make
- X11 development libraries (Linux)
- MinilibX library (automatically downloaded)

### Installation

1. **Clone the repository**
git clone https://github.com/voloshynm/cub3d.git
cd cub3d

2. **Compile the project**
make

3. **Run the game**
./cub3D maps/test2.cub

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Exit game |

## 🗺️ Map Configuration

Maps are defined in `.cub` files with the following format:
```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 127,125,119
C 174,234,255

11111111111111111111111111111
10000000001100000000011100001
10000000000000000000000000001
100000N0000000000000000000001
10000000000000000000000000001
10000000000000001100000010001
11111111111111111111111111111
```

### Map Elements

- **Textures**: `NO`, `SO`, `WE`, `EA` - Paths to XPM texture files
- **Colors**: `F` (floor), `C` (ceiling) - RGB values (0-255)
- **Map Characters**:
  - `1` - Wall
  - `0` - Empty space
  - `N/S/E/W` - Player starting position and direction
  - ` ` (space) - Void area

## 🏗️ Project Structure
```
cub3d/
├── src/ # Source files
│ ├── main.c # Program entry point
│ ├── init_visuals.c # launch mlx loop, render frame and textures 
│ ├── parser.c # Map file parsing
│ ├── parse_elements.c # Texture parsing
│ ├── parse_elements_helper.c # Texture parsing
│ ├── parse_elements_color.c # Color parsing
│ ├── parse_map.c # Map validation and processing
│ ├── parse_map_directions.c # Map processing
│ ├── validate_walls.c # Map validation
│ ├── raycasting.c # Core raycasting engine
│ ├── raycasting_helper.c # Core raycasting engine
│ ├── raycasting_rays_direction.c # Core raycasting engine
│ ├── controls.c # Input handling
│ ├── controls_helper.c # Input handling
│ ├── utils.c # Utility functions
│ └── utils_2.c # Utility functions
├── includes/
│ └── cub3d.h # Header file
├── textures/ # Texture files
├── maps/ # Example maps
├── libft/ # Custom C library
├── Makefile # Build configuration
└── README.md
```

## 🔧 Technical Implementation

### Raycasting Algorithm

The project implements a **DDA (Digital Differential Analyzer)** algorithm for raycasting:

1. **Ray initialization** - Calculate ray direction for each screen column
2. **Grid traversal** - Step through the map grid until hitting a wall
3. **Distance calculation** - Compute perpendicular wall distance
4. **Wall rendering** - Draw textured vertical lines based on distance

### Key Components

- **Parser**: Validates and loads map configuration
- **Raycasting Engine**: Renders 3D view from 2D map
- **Texture Mapping**: Applies appropriate textures to walls
- **Input System**: Handles player movement and rotation
- **Memory Management**: Proper allocation and cleanup

## 🛠️ Build System

### Available Commands

make # Compile the project
make clean # Remove object files
make fclean # Remove all generated files
make re # Rebuild everything
make help # Show available targets
make status # Show project status


### Dependencies

The project automatically handles dependencies:
- **MinilibX**: Downloaded and compiled automatically
- **libft**: Custom C library (cloned from repository)

## 🧪 Testing

Test your maps with the provided examples:

Valid map
./cub3D maps/test2.cub

Test error handling
./cub3D maps/invalid_map.cub
./cub3D nonexistent.cub


## 🐛 Troubleshooting

### Common Issues

1. **Segmentation fault**
   - Check map file format and validity
   - Ensure texture files exist and are accessible
   - Verify player position is valid

2. **Compilation errors**
   - Install required development libraries
   - Check GCC version compatibility

3. **Texture loading fails**
   - Verify XPM file format
   - Check file permissions
   - Ensure paths are correct

### Debug Mode

Compile with debug symbols:
make CFLAGS="-Wall -Wextra -Werror -g"
gdb ./cub3D maps/test2.cub


## 📚 Learning Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Wolfenstein 3D Technical Details](https://en.wikipedia.org/wiki/Wolfenstein_3D)

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is part of the 42 School curriculum. Feel free to use it for educational purposes.

## 👥 Authors

- **Maksym Voloshyn <mvoloshy>** - **Hugo Huber <hhuber>**

Thanks to mcombeau for sharing textures and maps for rigirous testing!
https://github.com/mcombeau/cub3D

## 🙏 Acknowledgments

- 42 School for the project specification
- The creators of Wolfenstein 3D for inspiration
- MinilibX developers for the graphics library
- The raycasting community for tutorials and resources

---

*Made with ❤️ at 42 School*