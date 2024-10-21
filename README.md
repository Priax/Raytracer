# Raytracer
An Epitech Project made by:

<div style="display: flex; justify-content: center;">
  <div style="margin-right: 20px;">
    <a href="https://github.com/NattanCochet" style="text-decoration: none; display: block; text-align: center;">
      <img src="https://github.com/NattanCochet.png?size=85" width="85" style="display: block; margin: 0 auto; margin-bottom: 10px;">
      <sub style="display: block;">COCHET Nattan</sub>
    </a>
  </div>
  <div style="margin-right: 20px;">
    <a href="https://github.com/Priax" style="text-decoration: none; display: block; text-align: center;">
      <img src="https://github.com/Priax.png?size=85" width="85" style="display: block; margin: 0 auto; margin-bottom: 10px;">
      <sub style="display: block;">MONTERO FONTAINE Vincent</sub>
    </a>
  </div>
  <div style="margin-right: 20px;">
    <a href="https://github.com/Sonny-Rameaux" style="text-decoration: none; display: block; text-align: center;">
      <img src="https://github.com/Sonny-Rameaux.png?size=85" width="85" style="display: block; margin: 0 auto; margin-bottom: 10px;">
      <sub style="display: block;">RAMEAUX Sonny</sub>
    </a>
  </div>
  <div>
    <a href="https://github.com/Gonzter" style="text-decoration: none; display: block; text-align: center;">
      <img src="https://github.com/Gonzter.png?size=85" width="85" style="display: block; margin: 0 auto; margin-bottom: 10px;">
      <sub style="display: block;">ROCCHIA Guillaume</sub>
    </a>
  </div>
</div>


## Description
This Epitech Project has to be carried out in group of 3 to 4 students in 28 days.<br>
Ray tracing is a technique used to generate realistic digital images by simulating the inverse path of light.<br>
Our goal is to create a program able to generate an image from a file describing the scene.

## Features

### MUST
The project must support the following features:
- Primitives:
    - Sphere
    - Plane
- Transformations:
    - Translation
- Light:
    - Directional light
    - Ambient light
- Material:
    - Flat color
- Scene configuration:
    - Add primitives to scene
    - Set up lighting
    - Set up camera
- Interface:
    - No GUI, output to a PPM file

### SHOULD
Once the previous features are working properly, the project should handle the following features:
- Primitives:
    - Cylinder
    - Cone
- Transformation:
    - Rotation
- Light:
    - Drop shadows

### COULD
Now the project could handle the following features:
- Primitives:
    - Limited cylinder (0.5)
    - Limited cone (0.5)
    - Torus (1)
    - Tanglecube (1)
    - Triangles (1)
    - .OBJ file (1)
    - Fractals (2)
    - Möbius strip (2)
- Transformations:
    - Scale (0.5)
    - Shear (0.5)
    - Transformation matrix (2)
    - Scene graph (2)
- Light:
    - Multiple directional lights (0.5)
    - Multiple point lights (1)
    - Colored light (0.5)
    - Phong reflection model (2)
    - Ambient occlusion (2)
- Material:
    - Transparency (0.5)
    - Refraction (1)
    - Reflection (0.5)
    - Texturing from file (1)
    - Texturing from procedural generation of chessboard (1)
    - Texturing from procedural generation of Perlin noise (1)
    - Normal mapping (2)
- Scene configuration:
    - Import a scene in a scene (2)
    - Set up antialiasing through supersampling (0.5)
    - Set up antialiasing through adaptative supersampling (1)
- Optimizations:
    - Space partitionning (2)
    - Multithreading (1)
    - Clustering (3)
- Interface:
    - Display the image during and after generation (1)
    - Exit during or after generation (0.5)
    - Scene preview using a basic and fast renderer (2)
    - Automatic reload of the scene at file change (1)

The number in parentheses is the number of points given in the grading scale for each feature.

## Compilation via Makefile

```bash
    make
```

## Usage

```bash
    ./raytracer --help
        USAGE: ./raytracer <SCENE_FILE> <OPTION>
        SCENE_FILE: scene configuration
        OPTION:
            -G: Graphical
            -G--low: Graphical low quality
            none: No preview
```

## More documentation with Doxygen

```bash
    doxygen doxygenConfig
    open html/index.html
```
