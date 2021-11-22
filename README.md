#  Mandelbrot Zoom

This is an application developed using SFML library
on C++ which visualize Mandelbrot Set fractals.


## SFML Documentation

https://www.sfml-dev.org/documentation/2.5.1/


## Design

For creating Mandelbrot set given range along X and Y axis,
we divide the 2D plane into small squares and color the squares
based on number of iterations of optimised escape time algorithm.

Dynamic2DArray to be constructed to store the pixel data,
as it can help in saving space when resolution is changed.

A History class [not in the literal sense ;)] which basically 
contains two stacks (Undo and Redo) to implement these commands. 

A Button class and Textbox class to implement GUI elements 
as there is no such native objects in SFML.   
________________________________________________________________________________________

Pseudo-code for getting number of iterations at each pixel

for each pixel (Px, Py) on the screen do
    x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
    y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
    x := 0.0
    y := 0.0
    iteration := 0
    max_iteration := 1000
    // Here N = 2^8 is chosen as a reasonable bailout radius.

    while x*x + y*y ≤ (1 << 16) and iteration < max_iteration do
        xtemp := x*x - y*y + x0
        y := 2*x*y + y0
        x := xtemp
        iteration := iteration + 1

    // Used to avoid floating point issues with points inside the set.
    if iteration < max_iteration then
        // sqrt of inner term removed using log simplification rules.
        log_zn := log(x*x + y*y) / 2
        nu := log(log_zn / log(2)) / log(2)
        // Rearranging the potential function.
        // Dividing log_zn by log(2) instead of log(N = 1<<8)
        // because we want the entire palette to range from the
        // center to radius 2, NOT our bailout radius.
        iteration := iteration + 1 - nu
    
Credits : Wikipedia.org
________________________________________________________________________________________


## Features

-> Click on canvas to Zoom in at the point 
-> Undo command (Z or undo button)
-> Redo command (R or redo button)
-> Go to home view using H or Home button
-> Set Zoom-In-factor at each step
-> Modify Maximum Iterations 
-> Change Resolution


## References

https://www.sfml-dev.org/index.php
https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
https://en.wikipedia.org/wiki/Mandelbrot_set
https://www.codingame.com/playgrounds/2358/how-to-plot-the-mandelbrot-set/adding-some-colors
https://math.hws.edu/eck/js/mandelbrot/MB-info.html
https://www.youtube.com/watch?v=T31MoLJws4U


## Video Link

https://drive.google.com/file/d/10L4_VlvkyiQ-vY1TeO-Tnebl9RMuVTXO/view?usp=sharing
