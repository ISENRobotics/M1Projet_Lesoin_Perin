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
        int initWindow(const char *);
        VideoCapture initFlux();
        CvPoint calculBarycentre(Mat mask);
        Mat tracking(CvPoint x, Mat image);
        void affiche(Mat imageTracking, Mat imageBinaire);
        Mat binairisation (Mat fluxOriginal);

    private:
        IplImage *image;
        CvCapture *capture;
        IplImage *hsv;
        IplImage *mask;
        CvScalar pixel;
        IplConvKernel * kernel;
        int h, s, v, tolerance;
        int event;
        int x,y, ds, dh, dv;
        int sommeX,sommeY;
        int nbPixels;
        CvPoint positionObj;

};

#endif // WEBCAM_H_INCLUDED
