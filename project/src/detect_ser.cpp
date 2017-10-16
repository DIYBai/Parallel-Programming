#include "inclusion.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std; //unsure if this is necessary/desireable

const int SEE_BOX = 1;

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
        //below two for-loops purely for making blurred boxes more visible
        if(SEE_BOX){
            for (int temp = x1-5; temp < x1; ++temp){
                if(temp >= 0 && temp < cols){
                    const int left_pix = i + (temp*rows);
                    out[left_pix].red = 200;
                    out[left_pix].green = 0;
                    out[left_pix].blue  = 0;
                }
            }
            for (int temp = x2; temp < x2 + 5; ++temp){
                if(temp >= 0 && temp < cols){
                    const int right_pix = i + (temp*rows);
                    out[right_pix].red = 200;
                    out[right_pix].green = 0;
                    out[right_pix].blue  = 0;
                }
            }
        }

        for(int j = x1; j < x2; ++j) {
            const int out_offset = i + (j*rows);
            //NOTE: small change from adapted code
            out[out_offset].red   = 0;
            out[out_offset].green = 0;
            out[out_offset].blue  = 0;
            for(int x = i - radius, kx = 0; x <= i + radius; ++x, ++kx) {
                for(int y = j - radius, ky = 0; y <= j + radius; ++y, ++ky) {
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
    if(argc != 3) {
        printf("Usage: %s inputFolderName outputFolderName\n", argv[0]);
        return 1;
    }

    //from https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    DIR *dir;
    struct dirent *ent;
    if ( (dir = opendir(argv[1])) == NULL ) {
        printf("Error attempting to access input directory %s!", argv[1]);
        return -1;
    }
    int count = 0;
    while ( (ent = readdir(dir)) != NULL ) {
        char *f_ext = strrchr(ent->d_name, '.'); //https://stackoverflow.com/questions/10347689/how-can-i-check-whether-a-string-ends-with-csv-in-c
        if ( f_ext && !strcmp(f_ext, ".png") ){
          count++;
        }
    }
    char f_names[count][256]; //hardcoded buffer size of 256 chars
    int  face_found[count] = {0};

    rewinddir(dir);
    count = 0;
    while ( (ent = readdir(dir)) != NULL ){
        char *f_ext = strrchr(ent->d_name, '.');
        if ( f_ext && !strcmp(f_ext, ".png") ){
            strcpy(f_names[count], ent->d_name);
            // printf("Found file: %s\n", ent->d_name);
            count++;
        }
    }
    closedir(dir);
    // sort(f_names[0], f_names[count-1]); //https://stackoverflow.com/questions/5897319/how-to-use-stdsort-to-sort-an-array-in-c

    struct timespec start_time;
    struct timespec end_time;
    printf("\nStarting serial processing\n");
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i = 0; i < count; i++){
        // Obtained from: https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_alt.xml
        CascadeClassifier faceDetector = CascadeClassifier("input/haarcascade_frontalface_alt.xml");

        // if( !(i%50) ) { //(i%100 == 0) {
        //     printf("Processed %d frames\n", i);
        // }
        char in_loc[256];
        sprintf(in_loc, "%s/%s", argv[1], f_names[i]);
        // printf(in_loc);
        Mat image = imread(in_loc, CV_LOAD_IMAGE_COLOR);
        if(image.empty()){
            printf("Empty or bad file\n");
            break;
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

        if( faceDetections.size() > 0){ //TODO: remove >0...unnecessary
            face_found[i] = 1;
            for ( vector <Rect>::iterator rect_iter = faceDetections.begin(); rect_iter != faceDetections.end(); ++rect_iter) {
                apply_blur(10, 1024.0, rect_iter->x, rect_iter->y, rect_iter->x + rect_iter->width, rect_iter->y + rect_iter->height, rows, cols, inPixels, outPixels);
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

        char out_loc[256];
        sprintf(out_loc, "%s/out_%s", argv[2], f_names[i]);
        imwrite(out_loc, dest);

        free(inPixels);
        free(outPixels);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    long msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;
    printf("serial took %dms\n", msec);

    char out_faces[256];
    sprintf(out_faces, "%s/ser_faces.txt", argv[2]);
    FILE *faces = fopen(out_faces, "w");
    for(int i = 0; i < count; i++) {
        fprintf(faces, "%d: %s\n", face_found[i], f_names[i]);
        // if(face_found[i]){
        //     fprintf(faces, "%s\n", f_names[i]);
        // }
    }
    fclose(faces);

    return 0;
}
