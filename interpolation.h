#ifndef INTERPOLATION_H
#define INTERPOLATION_H

/**
 * @file interpolation.h
 * @brief Header file for the interpolation functions.
 */

#include <stdio.h>

/**
 * @brief Performs linear, bilinear, or trilinear interpolation based on the dimension.
 * 
 * @param dim Dimension of the data (1 for 1D, 2 for 2D, 3 for 3D).
 * @param coords Array of pointers to coordinate arrays (e.g., {x}, {x, y}, {x, y, z}).
 * @param n Array of the number of points in each dimension (e.g., {nx}, {nx, ny}, {nx, ny, nz}).
 * @param values Array of data values corresponding to the grid points.
 *               - For 1D: values[i] = f(x[i])
 *               - For 2D: values[i * ny + j] = f(x[i], y[j])
 *               - For 3D: values[(i * ny * nz) + (j * nz) + k] = f(x[i], y[j], z[k])
 * @param query_points Array of query points (e.g., {xq}, {xq, yq}, {xq, yq, zq}).
 * @return Interpolated value at the query point.
 */
double interpolate(int dim, const double *coords[], const int n[], const double values[], const double query_points[]);

#endif // INTERPOLATION_H
