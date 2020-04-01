## Overview

This tool implement a simple front-end to the _OpenCV_ _inpaint_ method that allows to extrapolated missing pixels of an image based on the neighbouring existing pixels. This allows to reconstruct missing part of image or to replace and hide specific elements on the image.

The missing pixels are specified through a mask image that comes with the same size as the image to process but containing black values on the pixels to extrapolate and white value on the pixels to keep.

## Usage example

Considering the following panoramic image acquired with a spherical camera, one can see that part of the camera and the vehicle on which it is mounted can be seen on the image. The following image shows the raw panoramic image and its corresponding mask that point to the pixels to extrapolate :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-missing-pixel/doc/spherical-camera.jpg?raw=true" width="384">
&nbsp;
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-missing-pixel/doc/spherical-camera-mask.png?raw=true" width="384">
<br />
<i>Example of a spherical camera image and its corresponding mask</i>
</p>
<br />

Using the following command :

    ./image-missing-pixel -s spherical-camera.jpg 
                          -m spherical-camera-mask.png 
                          -e spherical-camera-filled.jpg 
                          -k 16

one obtain the following result :

<br />
<p align="center">
<img src="https://github.com/nils-hamel/image-suite/blob/master/src/image-adaptative-histogram/doc/spherical-camera-filled.jpg?raw=true" width="384">
<br />
<i>Result of the selected pixel extrapolation</i>
</p>
<br />

As the value of the kernel _k_  is increased, the quality of the extrapolated pixel increase but showing a more blurry aspect. In addition, increasing _k_ can lead to very long processes.