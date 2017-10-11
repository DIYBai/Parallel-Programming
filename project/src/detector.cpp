
//returns bool based on whether face was found or not
//if face is found, writes coordinates of (2) opposite corners to coords array (4 vals total)
#include "inclusion.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std; //unsure if this is necessary/desireable

//TODO:
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
    /*
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " imageName\n";
        return 1;
    }
    */

    printf("\nRunning FaceDetector");

    // CascadeClassifier faceDetector = new CascadeClassifier(FaceDetector.class.getResource("haarcascade_frontalface_alt.xml").getPath());
    CascadeClassifier faceDetector;// = malloc(sizeof(CascadeClassifier));
    faceDetector.load("haarcascade_face.xml");

    // Mat image = Highgui.imread(FaceDetector.class.getResource("shekhar.JPG").getPath());
    //TODO: make this based on args
    Mat image = imread("test1.jpg");
    // Mat image = imread(argv[1]);

    // MatOfRect faceDetections = new MatOfRect();
    // https://stackoverflow.com/questions/15893591/confusion-between-opencv4android-and-c-data-types
    vector <Rect> faceDetections;// = malloc( ??? ); //NOTE: unsure what goes in malloc
    Rect *test = Rect(1, 1, 5, 5);
    printf("Rect test: %d %d %d %d", test.x, text.y, test.width, test.height);

    faceDetector.detectMultiScale(image, faceDetections);

    // System.out.println(String.format("Detected %s faces", faceDetections.toArray().length));
    printf( "Detected %d faces", faceDetections.size() );

    //look in opencv2/core/types.hpp (line 383) for clues
    // for ( vector <Rect>::iterator rect_iter = faceDetections.begin(); rect_iter != faceDetections.end(); ++rect_iter) {
    //     // Core.rectangle(image, new Point(rect.x, rect.y), new Point(rect.x + rect.width, rect.y + rect.height), new Scalar(0, 255, 0));
    //     printf("Face found at (%d)", *rect_iter.x);//, rect_iter.y, rect_iter.x + rect_iter.width, rect_iter.y + rect_iter.height);
    // }

    return 1;
    // string filename = "output.png";
    // printf("Writing %s", filename);
    // imwrite(filename, image);
}
