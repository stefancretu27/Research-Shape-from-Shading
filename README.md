# Research-Shape-from-Shading

This document contains summary on the relevant aspects from the support articles related to Shape from Shading topic.

Document [1]:

Problem to solve: Having a 2D image, estimate the physical (3D) world that produced the given image. In other terms, try to reconstruct the original 3D object given the 2D picture of it. Also, the process of recovering the intrinsic scene properties from a single image of a
object is called "shape, illumination, and reflectance from shading", or "SIRFS".

Issues in solving the problem: the set of possible shapes, colors, illumination (light) that could produce the image is vast. Thus, the aim is to find the shape, illuminance and reflectance factors that best approximate the original => the algorithm is an optimization problem.  

The gradient optimization approach is not suitable to the problem in discussion, as it needs an arbitrary starting point

Refereneces:

[1] J. T. Barron, J. Malik, "Shape, Illumination, and Reflectance from Shading", IEEE TRANSACTIONS ON PATTERN ANALYSIS AND MACHINE INTELLIGENCE
