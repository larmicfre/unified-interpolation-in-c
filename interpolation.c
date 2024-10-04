/**
 * @file interpolation.c
 * @brief Source file for the interpolation functions.
 */

#include "interpolation.h"

/**
 * @brief Binary search to find the interval for a query point.
 * 
 * @param arr Array to search (must be sorted in ascending order).
 * @param n Number of elements in the array.
 * @param q Query value.
 * @return Index i such that arr[i] <= q < arr[i + 1].
 */
static int find_interval(const double arr[], int n, double q) {
    if (q <= arr[0]) {
        return 0;
    }
    if (q >= arr[n - 1]) {
        return n - 2;
    }
    int low = 0;
    int high = n - 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (q < arr[mid]) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return low;
}

double interpolate(int dim, const double *coords[], const int n[], const double values[], const double query_points[]) {
    if (dim < 1 || dim > 3) {
        fprintf(stderr, "Error: Dimension must be 1, 2, or 3.\n");
        return 0.0;
    }

    int indices[3] = {0};
    double t[3] = {0.0};

    // Find intervals and compute weights for each dimension
    for (int d = 0; d < dim; d++) {
        indices[d] = find_interval(coords[d], n[d], query_points[d]);
        double x0 = coords[d][indices[d]];
        double x1 = coords[d][indices[d] + 1];
        t[d] = (query_points[d] - x0) / (x1 - x0);
    }

    // Interpolation based on dimension
    if (dim == 1) {
        // Linear interpolation
        double y0 = values[indices[0]];
        double y1 = values[indices[0] + 1];
        return y0 + t[0] * (y1 - y0);
    } else if (dim == 2) {
        // Bilinear interpolation
        int i = indices[0];
        int j = indices[1];
        int ny = n[1];

        double z00 = values[i * ny + j];
        double z01 = values[i * ny + (j + 1)];
        double z10 = values[(i + 1) * ny + j];
        double z11 = values[(i + 1) * ny + (j + 1)];

        double z0 = z00 + t[1] * (z01 - z00);
        double z1 = z10 + t[1] * (z11 - z10);

        return z0 + t[0] * (z1 - z0);
    } else if (dim == 3) {
        // Trilinear interpolation
        int i = indices[0];
        int j = indices[1];
        int k = indices[2];
        int ny = n[1];
        int nz = n[2];

        double c000 = values[(i * ny * nz) + (j * nz) + k];
        double c001 = values[(i * ny * nz) + (j * nz) + (k + 1)];
        double c010 = values[(i * ny * nz) + ((j + 1) * nz) + k];
        double c011 = values[(i * ny * nz) + ((j + 1) * nz) + (k + 1)];
        double c100 = values[((i + 1) * ny * nz) + (j * nz) + k];
        double c101 = values[((i + 1) * ny * nz) + (j * nz) + (k + 1)];
        double c110 = values[((i + 1) * ny * nz) + ((j + 1) * nz) + k];
        double c111 = values[((i + 1) * ny * nz) + ((j + 1) * nz) + (k + 1)];

        double c00 = c000 + t[2] * (c001 - c000);
        double c01 = c010 + t[2] * (c011 - c010);
        double c10 = c100 + t[2] * (c101 - c100);
        double c11 = c110 + t[2] * (c111 - c110);

        double c0 = c00 + t[1] * (c01 - c00);
        double c1 = c10 + t[1] * (c11 - c10);

        return c0 + t[0] * (c1 - c0);
    }

    // Should not reach here
    return 0.0;
}
