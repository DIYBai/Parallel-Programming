//code (adapted) from repo/patterns/stencil/openmp.cpp

// #define _USE_MATH_DEFINES //not sure what this line is for; may not be necessary
#include <cmath>
#include <string.h>

struct pixel {
    double red;
    double green;
    double blue;
    double intensity;

    pixel(double r, double g, double b) : red(r), green(g), blue(b) {};
};

void gaussian_kernel(const int size, const double stddev, double * const kernel) {
    // values needed for the curve
    const double denom = 2.0 * stddev * stddev;
    const double g_denom = M_PI * denom;
    const double g_denom_recip = (1.0/g_denom);
    // accumulator so that values can be normalized to 1
    double sum = 0.0;

    // Build the template
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            const double row_dist = i - (size/2);
            const double col_dist = j - (size/2);
            const double dist_sq = (row_dist * row_dist) + (col_dist * col_dist);
            const double value = g_denom_recip * exp((-dist_sq)/denom);
            kernel[i + (j*size)] = value;
            sum += value;
        }
    }

    // Normalize
    const double recip_sum = 1.0 / sum;
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            kernel[i + (j*size)] *= recip_sum;
        }
    }
}

void apply_blur(int radius, const double stddev, const int x1, const int y1, const int x2, const int y2, const int rows, const int cols, pixel * const in, pixel * const out) {
    //make sure 0 <= x1 < x2 <= cols and 0 <= y1 < y2 <= rows ??
    memcpy(out, in, sizeof(pixel)*rows*cols); //unsure if this could/should be done before
    const int dim = radius*2+1;
    double kernel[dim*dim];
    gaussian_kernel(dim, stddev, kernel);

    // #pragma omp parallel for
    for(int i = y1; i < y2; ++i) {
        for(int j = x1; j < x2; ++j) {
            const int out_offset = i + (j*rows);
            //NOTE: small change from adapted code
            out[out_offset].red   = 0;
            out[out_offset].green = 0;
            out[out_offset].blue  = 0;
            for(int x = i - radius, kx = 0; x <= i + radius; ++x, ++kx) {
                for(int y = j - radius, ky = 0; y <= j + radius; ++y, ++ky) {
                    //TODO: consider the edge cases instead of treating them as 0s (by not adding)
                    if(x >= 0 && x < rows && y >= 0 && y < cols) {
                        // Acculate intensities in the output pixel
                        const int in_offset = x + (y*rows);
                        const int k_offset = kx + (ky*dim);
                        out[out_offset].red   += kernel[k_offset] * in[in_offset].red;
                        out[out_offset].green += kernel[k_offset] * in[in_offset].green;
                        out[out_offset].blue  += kernel[k_offset] * in[in_offset].blue;
                    }
                }
            }
        }
    }
}

//placeholder to make GCC happy
int main(int argc, char **argv){
  return 1;
}
