#ifndef WEBCAM_H_INCLUDED
#define WEBCAM_H_INCLUDED

#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

class Webcam
{
    public:
        Webcam();
        ~Webcam();
        VideoCapture initFlux();
        CvPoint calculBarycentre(Mat imageBinaire);
        Mat tracking(CvPoint x, Mat image);
        void affiche(Mat imageTracking, Mat imageBinaire);
        Mat binairisation (Mat image);

    private:

        int nbPixels;
};

#endif // WEBCAM_H_INCLUDED
