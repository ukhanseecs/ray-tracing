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

## Dependencies

This project utilizes a custom `vec3.h` header file that defines the `Vector3D` class, which I wrote myself. This library provides essential vector operations for the ray tracing algorithm.

### Main Features of `Vector3D`:

- **Vector Operations**: Supports addition, subtraction, scalar multiplication, and division.
- **Element Access**: Provides read-only and read-write access to vector components.
- **Length Calculations**: Includes methods to compute the length and length squared of the vector.
- **Dot and Cross Products**: Implements dot and cross product operations for vector mathematics.
- **Output Formatting**: Overloads the `<<` operator for easy output of vector values.

This library is designed to facilitate vector calculations in graphics programming, making it easier to implement algorithms like ray tracing.
