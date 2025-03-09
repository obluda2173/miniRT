# miniRT

miniRT is a simple yet efficient raytracer built as part of the 42 curriculum. It adheres to the MiniLibX framework and renders basic 3D scenes defined in .rt files. This project serves as an introduction to raytracing, covering key concepts like ray-object intersection, shading, and lighting models.

## Features
- Basic Shapes: Supports spheres, planes, cylinders and cones.
- Textures: Supports color and normal textures on planes.
- Lighting: Ambient and diffuse light sources.
- Phong Reflection Model: Implements diffuse and specular shading.
- Camera System: Viewpoint manipulation and adjustable field of view.
- Parsing: Reads .rt scene description files.
- MiniLibX Integration: Uses MiniLibX for window creation and pixel rendering.

### Scene of mixed objects
<img src="https://github.com/obluda2173/miniRT/blob/main/img/unbeliavable_objects_on_the_green_checkerboard_plane_are_mindblowing.png" width="100%" height="100%">

### Lonely Amongus on unknown planet
<img src="https://github.com/obluda2173/miniRT/blob/main/img/an_amazing_amongus_somewhere_on_the_unexpored_planet.png" width="100%" height="100%">

## Example .rt File:
```
A 0.2 255,255,255      # Ambient lighting (intensity, RGB)
C 0,0,20 0,0,-1 70     # Camera (position, direction, FOV)
L -40,0,30 0.7 255,255,255  # Light source (position, brightness, RGB)

sp 0,0,20 20 255,0,0   # Sphere (position, diameter, color)
pl 0,0,0 0,1,0 0,255,0 # Plane (position, normal, color)
cy 50,0,20.6 0,0,1 14.2 21.42 0,0,255  # Cylinder (pos, axis, diam, height, color)
co -1,-1,-1 1,1,1 25 0,255,255 # Cone (pos, axis, angle, color)
```

## Implementation Details
1. Raytracing Core
- Casts rays from the camera and computes intersections with objects.
- Determines color based on lighting and surface properties.
2. Intersection Algorithms
- Sphere: Solves a quadratic equation for ray-sphere intersection.
- Plane: Computes the intersection of a ray with an infinite plane.
- Cylinder: Handles lateral surface and cap intersections separately.
3. Lighting Model (Phong Reflection Model)
- Ambient Light: Affects all objects equally.
- Diffuse Light: Depends on the angle between the light and surface normal.
- Specular Highlight: Creates reflections based on the camera position.
#### Error Handling
- Ensures .rt files follow correct syntax.
- Handles invalid or missing scene components.
- Normalizes vectors and checks ranges for FOV, brightness, and colors.
