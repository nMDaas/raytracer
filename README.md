# Introduction 

This is a computer graphics application that allows users to build complex scenes with objects and render realistic images. C++, OpenGL and vector math operations were used to implement several raytracing techniques. 
Users can build scenes by adding and transforming objects, translating lights, and adding textures and materials to the objects. Users can also easily duplicate objects. 

# Raytracer Output

<img src="https://github.com/nMDaas/raytracer/blob/main/src/images/finalScene2.jpg" data-canonical-src="https://gyazo.com/eb5c5741b6a9a16c692170a41a49c858.png" width="425" height="425" />

![Image of Key](https://github.com/nMDaas/raytracer/blob/main/src/images/finalScene1.jpg)

# Raytracer Features 
Visit https://www.natashamishradaas.com/code for details on features implemented.

* object translation, scaling and rotation 
* light translation
* phong shading
* point light
* area lights
* soft shadows, accounting for material transparency
* reflection and infinite reflections
* refraction, total internal refraction and infinite refraction
* box and sphere texturing
* cameras 

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

