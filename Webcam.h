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
        VideoCapture initFlux(int device);
        CvPoint calculBarycentre(Mat imageBinaire);
        Mat tracking(CvPoint x, Mat image);
        void affiche(Mat imageTracking1, Mat imageBinaire1, Mat imageTracking2, Mat imageBinaire2);
        Mat binairisation (Mat image);
        int getNbPixels();
        int getNbPixelsLocked(Mat imageBinaire);

    private:

        int nbPixels;
        int nbPixelsLocked;
};

#endif // WEBCAM_H_INCLUDED
