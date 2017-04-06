#include "commun.h"

missile_usb *control_main;

int main(int argc, char *argv[]) {

    char key=0;
    Mat image;
    Mat imageBinaire;
    Mat imageTracking;
    VideoCapture fluxVideo;
    CvPoint positionObj;
    int dx=0, dy=0;

    int device_type = 1;

    missile_usb * control_main=init(device_type);

    Webcam * maWebcam = new Webcam();
    fluxVideo = maWebcam->initFlux();

    while(key!='q' && key!='Q') {

        fluxVideo >> image; //récupération du flux video dans la var image

        imageBinaire = maWebcam->binairisation(image); //binairisation de l'image

        positionObj=maWebcam->calculBarycentre(imageBinaire); //calcul barycentre
        imageTracking = maWebcam->tracking(positionObj, image); //affiche un point rouge sur la cible


        // l'origine des pixel est en haut à gauche
        dx=positionObj.x - 320;
        dy=240 - positionObj.y;

        cout << " dX="<< dx << " dY=" << dy << endl;

        traitement(control_main,dx,dy);

        //Affichage des fenetres :
        maWebcam->affiche(imageTracking, imageBinaire);

        if(waitKey(30) >= 0); // on patiente 30 millisecondes avant de passer à l'image suivante

    }

    delete maWebcam;
    missile_usb_destroy(control_main);

    return 0;
}
