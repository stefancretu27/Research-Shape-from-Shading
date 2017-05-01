# Research-Shape-from-Shading

This document contains summary on the relevant aspects from the support articles related to Shape from Shading topic.

Document [1]:

Problem to solve: Having a 2D image, estimate the physical (3D) world that produced the given image. In other terms, try to reconstruct the original 3D object given the 2D picture of it. Also, the process of recovering the intrinsic scene properties from a single image of a
object is called "shape, illumination, and reflectance from shading", or "SIRFS".

Issues in solving the problem: the set of possible shapes, colors, illumination (light) that could produce the image is vast. Thus, the aim is to find the shape (Z), illuminance (L) and reflectance (R) factors that best approximate the original => the algorithm is an optimization problem.  

R = I - S(Z, L). Z (depth map) and R (log reflectance) are images with same dimensions. S(Z, L) is a rendering engine that linearizes Z into a set of surface normals and produces a shape image from Z and L. I is equal to a rendering of the given model.

The gradient optimization approach is not suitable to the problem in discussion, as it needs an arbitrary starting point for finding the minim. Once found, it cannot guarantee whether it's a local minima or a global one, whereas the problem in discussion needs to find the global minima for Z, L and R.
  The approach is base don constructing the Gaussian pyramid from a given signal G(X), where G is a matrix as this construction is linear. Alos, there is used a L-BFGS algorithm (limited memory Broyden–Fletcher–Goldfarb–Shanno) to perform parameter estimation "to the inverse Hessian matrix to steer the search through the variable space" [2]. 
  Furthermore, for building the Gaussian pyramid there is needed a filter with a certain magnitude. It was chosen a 4-tap binomial filter. If the magnitude was too high it only worked for the higher (coarse scale) values, whereas the finer scales are ignored; if the magnitude was too low the coeficients of the higher values were to small and, consequently, ignored. The filter is: [1, 3, 3, 1] * 1/√8 and it optimizes all scales (both coarse and fine; or low and high) simultaneously. This approach helped in finding a much lower minima and worked faster than coarse-to-fine optimization techniques.
  For computing the optimization, both Z and L are initialized to 0 => complete white illumination. The optimization is done with repsect to a vector obtained a sthe concatenation of L and transp(G) * Z. At each iteration the gradient and loss are computed and the white illumination is unwhithened. Once optimization is done, approximation of the originals Z and L are obtained, and R is computed from them.


Refereneces:

[1] J. T. Barron, J. Malik, "Shape, Illumination, and Reflectance from Shading", IEEE TRANSACTIONS ON PATTERN ANALYSIS AND MACHINE INTELLIGENCE
[2] https://en.wikipedia.org/wiki/Limited-memory_BFGS
