#include "commun.h"

//missile_usb *control_main;

int main(int argc, char *argv[]) {

    char key=0;
    IplImage *image;
    IplImage *imageBinaire;
    CvCapture * fluxVideo;
    CvPoint positionObj;
    int dx=0, dy=0;

    int device_type = 1;

    missile_usb * control_main=init(&device_type);


    Webcam * maWebcam = new Webcam();
    fluxVideo = maWebcam->initFlux();
    maWebcam->initWindow("binairisation");
    maWebcam->initWindow("suivi couleur");

  /*  if(control_main != NULL) {
        cout << control_main->timeout << "avant le while"<< endl;
    } */

    while(key!='q' && key!='Q') {

        image = cvQueryFrame(fluxVideo); //récupération du flux video dans la var image

        imageBinaire = maWebcam->binairisation(image); //binairisation de l'image

        positionObj=maWebcam->calculBarycentre(imageBinaire); //calcul barycentre
        maWebcam->tracking(positionObj, image); //affiche un point rouge sur la cible


// l'origine des pixel est en haut à gauche


            dx=positionObj.x - 320;
            dy=240 - positionObj.y;

            cout << " dX="<< dx << " /dY=" << dy << endl;

            traitement(control_main,dx,dy);


            //Affichage de l'image dans la fenetre :
            maWebcam-> affiche("binairisation",imageBinaire);
            maWebcam-> affiche("suivi couleur",image);



        // On attend 10 ms :
        key = cvWaitKey(10);
    }


    delete maWebcam;

    cvReleaseCapture(&fluxVideo);
    cvDestroyWindow("binairisation");
    cvDestroyWindow("suivi couleur");
    missile_usb_destroy(control_main);

    return 0;
}
