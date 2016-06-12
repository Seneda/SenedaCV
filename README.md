# SenedaCV
A simple computervision library in c++

Workflow:
- Load image as PPMImage
- Apply edge filter


To Do:

- Add tests for the normalise method.
- Split the pixel class into two types: rgb and mono
  - rgb can then also have methods for getting things like YUV values to allow converting to mono
  - The PixelGrid class can then be used for all processing, convolutions etc.
- Pseudo colorise processed images by resizing the original to the new size and then using the color map scaled by the mono intensity.
- Write unit tests for modules
  - Get some simple images and check that the convolutions work
- Do a full implementation of canny edge detection

Goals:
- ~~Loading in simple image files~~
- Displaying images.
- Applying Convolution filters to images.
- Write a script which will read in a file containing instructions:
 - specify and image, specify a set of kernels, specify an output file name
 - load the image and convolve with the filters and save the output.
- Generate key filter kernels at given sizes.
- ??
- Blurring and downscaling images
- Interpolating and upscaling images
- ??
- Edge detection
- ??
- Feature detection (Something like SIFT)
- ??
