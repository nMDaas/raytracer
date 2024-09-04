# Introduction 

This is a ray tracing engine that allows users to build complex scenes with objects and render realistic images. C++, OpenGL and vector math operations were used to implement several raytracing techniques. 
Users can build scenes by adding and transforming objects, translating lights, and adding textures and materials to the objects. Users can also easily duplicate objects. 

# Raytracer Output

<img src="https://github.com/nMDaas/raytracer/blob/main/src/images/finalScene2.jpg" data-canonical-src="https://gyazo.com/eb5c5741b6a9a16c692170a41a49c858.png" width="425" height="425" />

![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/finalScene1.jpg)

# Raytracer Features 
* Customizable Scenes and Hierarchical Rendering of Nodes
* Box, Sphere, Cylinder Raytracing
* Box and Sphere Texturing
* Point Lights, Area Lights, Hard and Soft Shadows
  * Shadows accounting for material transparency
* Reflection & Infinite Reflections
* Refraction, Total Internal Refraction and Infinite Refraction
* Spotlights
* Object Translation, Scaling and Rotation 
* Light Translation
* Phong Shading
* Cameras

## Box, Sphere, Cylinder Raytracing 
* Used vector calculations to determine ray-object intersections and calculate the normals of the objects at the point of intersection.
  
![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/output2.png)

## Box and Sphere Texturing
* Used texture mapping to create ppm images that can wrap around sphere and box objects.

![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/output3.png)

## Point Lights, Area Lights, Hard and Soft Shadows
* Implemented point lights that create hard shadows and area lights that create softer shadows. As the number of cells in the area lights is increased, the soft shadow is more smooth and has less banding. 
* Shadow intensity also depends on the transparency of the material the light is passing through.

![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/output4.png)

## Reflection & Infinite Reflections
* Implemented reflections, allowing objects in the scene to have reflective properties. Accounted for infinite reflection and stack overflow by limiting "reflective bounces"

![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/output5.png)

## Refraction, Total Internal Refraction and Infinite Refraction
* Implemented refraction, allowing objects in the scene to have transparency determined by their refractive index.
* Accounted for total internal reflection and infinite refraction. Also accounted for multiple transparent objects within the scene or transparent objects within each other. 

![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/output6.png)

## Spotlights
* Spotlights can be added to the scene by mentioning angle of spotlight and spotlight direction.

![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/output7.png)

# How to Run 
```
make -C src
make
src/Raytracer src/scenegraphs/["example txt file in scenegraphs directory"]
```

# External Resources Used: 
* Some OpenGL and starter code provided by Professor Amit Shesh
* https://www.scratchapixel.com/index.html
* Peter Shirley, Trevor D Black, Steve Hollasch's Ray Tracing series 
* The Raytracer Challenge by Jamis Buck  

