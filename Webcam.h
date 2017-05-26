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
        void affiche(Mat imageTracking1, Mat imageBinaire1, Mat imageTracking2, Mat imageBinaire2, int focus1, int focus2, int locked1, int locked2, int nbPixelsLocked1, int nbPixelsLocked2, int check);
        Mat binairisation (Mat image);
        int getNbPixels();
        int getNbPixelsLocked(Mat imageBinaire);

    private:

        int nbPixels;
        int nbPixelsLocked;
};

#endif // WEBCAM_H_INCLUDED
