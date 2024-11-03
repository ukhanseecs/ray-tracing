# Ray Tracing in C++

This project implements a simple ray tracing algorithm in C++. The program generates a PPM image of a gradient.

## Features

- Generates a 256x256 pixel image.
- Outputs the image in PPM format (P3).
- Displays progress in the console while rendering.

## How to Compile

To compile the program, use the following command:
```bash
g++ raytracing.cpp -o raytracing
```

## How to Run

After compiling, run the program with:

```bash
./raytracing > output.ppm
```

This will create an `output.ppm` file containing the rendered image.

## Output

The output is a PPM image file that can be viewed with any image viewer that supports the PPM format.
