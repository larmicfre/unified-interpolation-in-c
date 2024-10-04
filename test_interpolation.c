/**
 * @file test_interpolation.c
 * @brief Test cases for the interpolation functions.
 */

#include "interpolation.h"
#include <assert.h>
#include <math.h>

#define EPSILON 1e-6

int main() {
    /* 1D Interpolation Test */
    {
        double x[] = {0, 1, 2, 3, 4};
        double y[] = {0, 2, 4, 6, 8};
        const double *coords[] = {x};
        int n[] = {5};
        double query_points[] = {2.5};

        double expected = 5.0;
        double result = interpolate(1, coords, n, y, query_points);
        assert(fabs(result - expected) < EPSILON);
        printf("1D interpolation test passed.\n");
    }

    /* 2D Interpolation Test */
    {
        double x[] = {0, 1, 2};
        double y[] = {0, 1, 2};
        double z[] = {
            0, 1, 2,
            1, 2, 3,
            2, 3, 4
        };
        const double *coords[] = {x, y};
        int n[] = {3, 3};
        double query_points[] = {1.5, 1.5};

        double expected = 3.0;
        double result = interpolate(2, coords, n, z, query_points);
        assert(fabs(result - expected) < EPSILON);
        printf("2D interpolation test passed.\n");
    }

    /* 3D Interpolation Test */
    {
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
        double query_points[] = {0.5, 0.5, 0.5};

        double expected = 1.5;
        double result = interpolate(3, coords, n, values, query_points);
        assert(fabs(result - expected) < EPSILON);
        printf("3D interpolation test passed.\n");
    }

    /* Edge Case Test: Query point outside the data range */
    {
        double x[] = {0, 1, 2, 3, 4};
        double y[] = {0, 2, 4, 6, 8};
        const double *coords[] = {x};
        int n[] = {5};
        double query_points[] = {-1.0}; // Outside the lower bound

        double expected = y[0];
        double result = interpolate(1, coords, n, y, query_points);
        assert(fabs(result - expected) < EPSILON);
        printf("Edge case test (lower bound) passed.\n");

        query_points[0] = 5.0; // Outside the upper bound
        expected = y[n[0] - 1];
        result = interpolate(1, coords, n, y, query_points);
        assert(fabs(result - expected) < EPSILON);
        printf("Edge case test (upper bound) passed.\n");
    }

    /* Non-uniform Grid Test */
    {
        double x[] = {0, 0.5, 2, 3.5, 5};
        double y[] = {0, 1.5, 4, 7, 10};
        const double *coords[] = {x};
        int n[] = {5};
        double query_points[] = {2.75};

        // Manually compute expected value
        int idx = 2; // x[2] = 2, x[3] = 3.5
        double t = (query_points[0] - x[idx]) / (x[idx + 1] - x[idx]);
        double expected = y[idx] + t * (y[idx + 1] - y[idx]);

        double result = interpolate(1, coords, n, y, query_points);
        assert(fabs(result - expected) < EPSILON);
        printf("Non-uniform grid test passed.\n");
    }

    /* All tests passed */
    printf("All interpolation tests passed successfully.\n");
    return 0;
}
