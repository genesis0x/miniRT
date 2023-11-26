# Chapter III: miniRT - My First RayTracer with miniLibX

## Project Overview

Welcome to miniRT, a powerful RayTracer designed to generate stunning computer-generated images. This project employs the Raytracing protocol to create scenes, each observed from a specific angle and position, defined by simple geometric objects with their unique lighting systems.

## Mandatory Part

### Program Name: miniRT
### Turn-in Files: All your files
### Makefile Commands: `all`, `clean`, `fclean`, `re`, `bonus`
### Arguments: A scene in the format *.rt

### External Functions
- `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`
- All functions of the math library (`-lm man man 3 math`)
- All functions of the MinilibX

### Constraints
- Use miniLibX, either from the OS or its sources (apply libft rules if using sources).
- Fluid window management: switching, minimization, etc.
- Window content remains unchanged when resolution is altered.
- Geometric objects: plane, sphere, cylinder.
- Correct handling of intersections and inside of objects.
- Resize object properties: diameter for sphere, width and height for cylinder.
- Translation and rotation transformations for objects, lights, and cameras.
- Light management: spot brightness, hard shadows, ambient and diffuse lighting.
- Image display rules:
  - Pressing ESC or clicking the red cross closes the window and quits the program.
  - Use of minilibX images is recommended.

### Scene Description File (.rt)
- Ambient lighting: `A ratio R,G,B`
- Camera: `C x,y,z nx,ny,nz FOV`
- Light: `L x,y,z ratio R,G,B`
- Sphere: `sp x,y,z diameter R,G,B`
- Plane: `pl x,y,z nx,ny,nz R,G,B`
- Cylinder: `cy x,y,z nx,ny,nz diameter height R,G,B`

### Example Scene (.rt)
```
A 0.2 255,255,255
C -50.0,0,20 0,0,1 70
L -40.0,50.0,0.0 0.6 10,0,255
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
sp 0.0,0.0,20.6 12.6 10,0,255
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
```

### Error Handling
- Properly exits and returns "Error\n" with an explicit error message for any misconfiguration.

## Chapter IV: Bonus Part

The Ray-Tracing technique holds potential for advanced features, but for miniRT, simplicity is key. Perfect the mandatory part before exploring these bonuses.

### Bonus List
1. **Specular Reflection:** Implement a full Phong reflection model.
2. **Color Disruption:** Introduce a checkerboard pattern.
3. **Colored and Multi-Spot Lights:** Enhance lighting effects.
4. **Second Degree Object:** Choose from Cone, Hyperboloid, Paraboloid.
5. **Bump Map Textures:** Implement bump mapping for added realism.

### Evaluation
Bonuses are considered only if the mandatory part is PERFECT. Full completion and correctness are essential for bonus points.

## Conclusion

Embark on your RayTracing journey with miniRT, and perfect the basics before delving into the exciting world of advanced features. Enjoy the process and unleash your creativity!
