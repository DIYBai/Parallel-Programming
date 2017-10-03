/**
 * Program to scale and project data into 2D and find a centroid
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

/* struct to hold objects attributes */
struct phaseballs {
    float *x;
    float *y;
    float *z;
    float *mass;
};

struct volume {
    size_t size;
    size_t last;
    struct phaseballs* objects;
};

// // Add phaseball to a volume
// void volume_append(struct volume* v, struct phaseball* o) {
//     if( v->last == v->size ) {
//         (v->size) += 100;
//         v->objects = realloc(v->objects, sizeof(struct phaseball*)*(v->size)+100);
//     }
//     (v->objects)[(v->last)] = o;
//     (v->last) += 1;
//     return;
// }

// Place phaseballs uniformly in a box, with mass equal to the manhattan distance
void place_uniformly(int sx, int ex, int sy, int ey, int sz, int ez, struct volume* v) {
    long x_dim = (1 + ex-sx);
    long y_dim = (1 + ey-sy);
    long z_dim = (1 + ez-sz);
    long size =  x_dim * y_dim * z_dim;

    struct phaseballs* n = malloc( sizeof(struct phaseballs) );
    n->x = malloc(sizeof(float) * size);
    n->y = malloc(sizeof(float) * size);
    n->z = malloc(sizeof(float) * size);
    n->mass = malloc(sizeof(float) * size);

    v->objects = n;
    for(int i=sx; i<=ex; i++) {
        for(int j=sy; j<=ey; j++) {
            for(int k=sz; k<=ez; k++) {
                long idx = (k-sz) + ( (j -sy)*z_dim ) + ( (i-sx)*y_dim*z_dim );
                n->x[idx] = i;
                n->y[idx] = j;
                n->z[idx] = k;
                // printf("x: %f  y: %f  z: %f  idx: %d\n", n->x[idx], n->y[idx], n->z[idx], idx);
                // n->mass[idx] = 1;
                n->mass[idx] = fabs(n->x[idx]) + fabs(n->y[idx]) + fabs(n->z[idx]);
                v->last++;
                // printf("Reached here\n");
                // volume_append(v,n);
            }
        }
    }
}

// Projects 3D volume to 11x11 2D map and report centroid
void post_process(struct volume* v, float* cx, float* cy) {
    double mass_sum=0.0;
    double wx=0.0;
    double wy=0.0;
    struct phaseballs *o = v->objects;

    #pragma omp parallel for reduction(+:mass_sum) reduction(+:wx) reduction(+:wy)
    for(int i=0; i<v->last; i++) {
        mass_sum += o->mass[i];
        wx += o->x[i] * o->mass[i];
        wy += o->y[i] * o->mass[i];
    }
    *cx = wx.value / mass_sum.value;
    *cy = wy.value / mass_sum.value;

    return;
}

int main(int argc, char** argv) {
    // make a volume to store objects in
    struct volume v;
    v.size=100;
    v.last=0;
    v.objects = malloc(sizeof(struct phaseball*) * 100);

    // Set the initial configuration
    place_uniformly(-1000,1000,-100,100,-100,100,&v);

    // Generate output
    float cx,cy;
    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    post_process(&v, &cx, &cy);
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    long msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;

    // Print output
    printf("Centroid at: %f,%f\n",cx,cy);
    printf("found in %dms\n",msec);

    return EXIT_SUCCESS;
}
