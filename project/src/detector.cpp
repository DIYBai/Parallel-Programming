
//returns bool based on whether face was found or not
//if face is found, writes coordinates of (2) opposite corners to coords array (4 vals total)
#include "inclusion.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;
// int detectFace(pixel * frame_data, int frame_num, int *coords){ //return bool
//   //maybe do this initilization for-loop outside/before function call
//   for(int i = 0; i < 4; i++){
//     coords[i] = -1;
//   }
//
//   if(FIND_FACE){
//       coords[0] = x1_VAR;
//       coords[1] = y1_VAR;
//       coords[2] = x2_VAR;
//       coords[3] = y2_VAR;
//       return 1;
//   }
//   return 0;
// }



int main(int argc, char **argv){
    printf("\nRunning FaceDetector");

    // CascadeClassifier faceDetector = new CascadeClassifier(FaceDetector.class.getResource("haarcascade_frontalface_alt.xml").getPath());
    CascadeClassifier faceDetector;// = malloc(sizeof(CascadeClassifier));
    faceDetector.load("haarcascade_face.xml");

    // Mat image = Highgui.imread(FaceDetector.class.getResource("shekhar.JPG").getPath());
    Mat image = Highgui.imread("test1.jpg");

    // MatOfRect faceDetections = new MatOfRect();
    // https://stackoverflow.com/questions/15893591/confusion-between-opencv4android-and-c-data-types
    vector <Rect> faceDetections = malloc( sizeof(vector<Rect>) ); //unsure what goes in malloc

    faceDetector.detectMultiScale(image, faceDetections);

    // System.out.println(String.format("Detected %s faces", faceDetections.toArray().length));
    printf( "Detected %d faces", faceDetections.size() );

    //faceDetections[i] should be a Rect object w fields x, y, width, and height
    for (iterator rect = faceDetections.begin(); rect != faceDetections.end(); ++rect) {
        // Core.rectangle(image, new Point(rect.x, rect.y), new Point(rect.x + rect.width, rect.y + rect.height), new Scalar(0, 255, 0));
        printf("Face found at (%d, %d) -> (%d, %d)", rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
    }

    return 1;
    char *filename = "output.png";
    printf("Writing %s", filename);
    Highgui.imwrite(filename, image);
}
