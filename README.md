# DFT

Discrete Fourier Transform is a program that takes "shape data" as ordered x and y coordinates of points that make the shape and changes it to a system of epicycles
created based on Discrete Fourier Transform that works together to recreate the shape.
DFT is also able to re-draw what the user has drawn in an app (see the last video, I know I can't draw, but my program can!).

# **DFT is in an _early development_ stage**! 
It is full of unnecessary variables, methods, it lacks basic classes like e.x. engine class or menu class.
Most implemented features like changing the end of an arrow that the camera focuses on, zooming in and out, drawing(by the user)
are simply prototypes done only in main.cpp.
In the next DFT updates, these features will be implemented in their respective classes, and way more optimized. 
It just works, the code is not remotely close to being done.

# Where does the _data_ come from?
The data comes from a program I made called CurveMaker that takes an image of a shape, finds contours, and saves them in a text file. The text file that is created by CurveMaker is then used by DFT. I will not be sharing CurveMaker code yet since DFT is just a prototype and will eventually be merged with CurveMaker in an attemp to create a fully done and functioning program.

# What _libraries_ does DFT use?
The only not standard library that I use in this project is SFML.
`SFML provides a simple interface to the various components of your PC, to ease the development of games and multimedia application.`
- https://www.sfml-dev.org/
# Videos made in DFT
- #### Heart being drawn using 10 epicycles.
[![Heart being drawn using 10 circles](https://img.youtube.com/vi/1mlfrY3zZhw/0.jpg)](http://www.youtube.com/watch?v=1mlfrY3zZhw)
- #### Heart being drawn using 50 epicycles.
[![Heart being drawn using 50 circles.](https://img.youtube.com/vi/RPOd6p5jZBU/0.jpg)](http://www.youtube.com/watch?v=RPOd6p5jZBU)
- #### Twitter
[![Twitter](https://img.youtube.com/vi/TqnXOXs5jjw/0.jpg)](http://www.youtube.com/watch?v=TqnXOXs5jjw)
- #### Snowflake shape
[![Snowflake shape](https://img.youtube.com/vi/YWogU_hj87o/0.jpg)](http://www.youtube.com/watch?v=YWogU_hj87o)
- #### User shape re-drawn
[![User shape re-drawn](https://img.youtube.com/vi/AfE4H6LQC1c/0.jpg)](http://www.youtube.com/watch?v=AfE4H6LQC1c)




