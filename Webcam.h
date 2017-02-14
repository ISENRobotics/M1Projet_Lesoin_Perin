#ifndef WEBCAM_H_INCLUDED
#define WEBCAM_H_INCLUDED

class Webcam
{
    public:
        Webcam();
        ~Webcam();
        int initWindow(const char *);
        CvCapture * initFlux();
        CvPoint calculBarycentre(IplImage *mask);
        IplImage * tracking(CvPoint x, IplImage * image);
        void affiche(const char * nomFenetre , IplImage * imgAffiche);
        IplImage * binairisation (IplImage * fluxOriginal);

    private:
        IplImage *image;
        CvCapture *capture;
        IplImage *hsv;
        IplImage *mask;
        CvScalar pixel;
        IplConvKernel * kernel;
        int h, s, v, tolerance;
        int event;
        int x,y, ds, dh;
        int sommeX,sommeY;
        int nbPixels;
        CvPoint positionObj;

};

#endif // WEBCAM_H_INCLUDED
