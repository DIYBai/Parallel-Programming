
//returns bool based on whether face was found or not
//if face is found, writes coordinates of (2) opposite corners to coords array (4 vals total)
#include "inclusion.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace cv;
using namespace std; //unsure if this is necessary/desireable

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
    const int dim = radius*2+1;
    double kernel[dim*dim];
    gaussian_kernel(dim, stddev, kernel);

    // #pragma omp parallel for
    for(int i = y1; i < y2; ++i) {
        for(int j = x1; j < x2; ++j) {
            const int out_offset = i + (j*rows);
            //NOTE: small change from adapted code
            //TODO: Mostly works, but check edge cases (see example in misc)
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

int main(int argc, char **argv){
    if(argc != 2) {
        printf("Usage: %s imageName\n", argv[0]);
        return 1;
    }

    // Obtained from: https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_alt.xml
    CascadeClassifier faceDetector = CascadeClassifier("haarcascade_frontalface_alt.xml");
    // faceDetector.load("./haarcascade_face.xml");

    //put for loop starting here to read all pictures in folder
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(image.empty()){
      printf("Empty or bad file\n");
      return -1;
    }

    const int rows = image.rows;
    const int cols = image.cols;
    pixel * inPixels = (pixel *) malloc(rows * cols * sizeof(pixel));
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            Vec3b p = image.at<Vec3b>(i, j);
            inPixels[i + (j*rows)] = pixel(p[0]/255.0,p[1]/255.0,p[2]/255.0);
        }
    }

    //create output pixels
    pixel * outPixels = (pixel *) malloc(rows * cols * sizeof(pixel));
    memcpy(outPixels, inPixels, sizeof(pixel)*rows*cols);

    // https://stackoverflow.com/questions/15893591/confusion-between-opencv4android-and-c-data-types
    vector <Rect> faceDetections;
    faceDetector.detectMultiScale(image, faceDetections);

    if(faceDetections.size() > 0 ){ //might not need this statement
        for ( vector <Rect>::iterator rect_iter = faceDetections.begin(); rect_iter != faceDetections.end(); ++rect_iter) {
            apply_blur(3, 32.0, rect_iter->x, rect_iter->y, rect_iter->x + rect_iter->width, rect_iter->y + rect_iter->height, rows, cols, inPixels, outPixels);
        }
    }

    Mat dest(rows, cols, CV_8UC3);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            const size_t offset = i + (j*rows);
            dest.at<Vec3b>(i, j) = Vec3b(floor(outPixels[offset].red * 255.0),
                                         floor(outPixels[offset].green * 255.0),
                                         floor(outPixels[offset].blue * 255.0));
        }
    }
    imwrite("TEMP.jpg", dest);

    free(inPixels);
    free(outPixels);

    return 0;
}
