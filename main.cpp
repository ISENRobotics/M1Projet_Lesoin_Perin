#include "commun.h"


int main(int argc, char *argv[]) {

    char key=0;
    IplImage *image;
    IplImage *imageBinaire;
    CvCapture * fluxVideo;
    CvPoint positionObj;


    Webcam * maWebcam = new Webcam();
    fluxVideo = maWebcam->initFlux();
    maWebcam->initWindow("binairisation");
    maWebcam->initWindow("suivi couleur");



    while(key!='q' && key!='Q') {

        image = cvQueryFrame(fluxVideo); //récupération du flux video dans la var image

        imageBinaire = maWebcam->binairisation(image); //binairisation de l'image

        positionObj=maWebcam->calculBarycentre(imageBinaire); //calcul barycentre
        maWebcam->tracking(positionObj, image); //affiche un point rouge sur la cible


        cout << " dX="<< 320 - positionObj.x << " / Y=" << 240 - positionObj.y << endl;

        // Affichage de l'image dans la fenetre :

        maWebcam-> affiche("binairisation",imageBinaire);
        maWebcam-> affiche("suivi couleur",image);



        // On attend 10 ms :
        key = cvWaitKey(10);


    }


    delete maWebcam;

    cvReleaseCapture(&fluxVideo);
    cvDestroyWindow("binairisation");
    cvDestroyWindow("suivi couleur");

    return 0;
}
