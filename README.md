# Interpolation Functions in C

A high-performance, unified interpolation function in C that performs linear, bilinear, or trilinear interpolation based on the data dimension. The function is designed with efficiency in mind, utilizing efficient search algorithms and memory access patterns.

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
  - [Function Signature](#function-signature)
  - [Parameters](#parameters)
  - [Return Value](#return-value)
- [Example](#example)
- [Compilation](#compilation)
- [Contributing](#contributing)
- [License](#license)

---

## Introduction

This project provides a single, versatile interpolation function capable of performing:

- **Linear interpolation** (1D)
- **Bilinear interpolation** (2D)
- **Trilinear interpolation** (3D)

---

## Features

- **Unified function**: One function handles 1D, 2D, and 3D interpolation.
- **High performance**: Efficient algorithms and memory access patterns are used.
- **Easy integration**: Simple API for easy integration into existing projects.

---

## Usage

### Function Signature

```c
double interpolate(int dim, const double *coords[], const int n[], const double values[], const double query_points[]);
```

### Parameters

- `int dim`: Dimension of the data.
  - `1` for 1D interpolation.
  - `2` for 2D interpolation.
  - `3` for 3D interpolation.
- `const double *coords[]`: Array of pointers to coordinate arrays.
  - For 1D: `{ x }`
  - For 2D: `{ x, y }`
  - For 3D: `{ x, y, z }`
- `const int n[]`: Array containing the number of points in each dimension.
  - For 1D: `{ nx }`
  - For 2D: `{ nx, ny }`
  - For 3D: `{ nx, ny, nz }`
- `const double values[]`: Flattened 1D array of data values corresponding to grid points.
  - For 1D: `values[i] = f(x[i])`
  - For 2D: `values[i * ny + j] = f(x[i], y[j])`
  - For 3D: `values[(i * ny * nz) + (j * nz) + k] = f(x[i], y[j], z[k])`
- `const double query_points[]`: Array of query points.
  - For 1D: `{ xq }`
  - For 2D: `{ xq, yq }`
  - For 3D: `{ xq, yq, zq }`

### Return Value

- Returns the interpolated value at the query point.

---

## Example

### 1D Interpolation Example

```c
#include "interpolation.h"

int main() {
    double x[] = {0, 1, 2, 3, 4};
    double y[] = {0, 2, 4, 6, 8};
    const double *coords[] = {x};
    int n[] = {5};
    double query_point[] = {2.5};

    double result = interpolate(1, coords, n, y, query_point);
    printf("1D Interpolation at x = %f: %f\n", query_point[0], result);

    return 0;
}
```

### 2D Interpolation Example

```c
#include "interpolation.h"

int main() {
    double x[] = {0, 1, 2};
    double y[] = {0, 1, 2};
    double z[] = {
        0, 1, 2,
        1, 2, 3,
        2, 3, 4
    };
    const double *coords[] = {x, y};
    int n[] = {3, 3};
    double query_point[] = {1.5, 1.5};

    double result = interpolate(2, coords, n, z, query_point);
    printf("2D Interpolation at (x, y) = (%f, %f): %f\n", query_point[0], query_point[1], result);

    return 0;
}
```

### 3D Interpolation Example

```c
#include "interpolation.h"

int main() {
    double x[] = {0, 1};
    double y[] = {0, 1};
    double z[] = {0, 1};
    double values[] = {
        0, 1,
        1, 2,

        1, 2,
        2, 3
    };
    const double *coords[] = {x, y, z};
    int n[] = {2, 2, 2};
    double query_point[] = {0.5, 0.5, 0.5};

    double result = interpolate(3, coords, n, values, query_point);
    printf("3D Interpolation at (x, y, z) = (%f, %f, %f): %f\n", query_point[0], query_point[1], query_point[2], result);

    return 0;
}
```

---

## Compilation

To compile the example code:

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/larmicfre/unified-interpolation-in-c.git
   cd interpolation-functions
   ```

2. **Compile with GCC**:

   ```bash
   gcc -o example example.c interpolation.c
   ```

3. **Run the Executable**:

   ```bash
   ./example
   ```

   **Expected Output**:

   ```console
   1D Interpolation at x = 2.500000: 5.000000
   2D Interpolation at (x, y) = (1.500000, 1.500000): 3.000000
   3D Interpolation at (x, y, z) = (0.500000, 0.500000, 0.500000): 1.500000
   ```

---

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
