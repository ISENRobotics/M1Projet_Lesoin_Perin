#include "commun.h"


using namespace cv;

Webcam::Webcam()
{

    h=170; // de 160 à 180
    s=175; // de 100 à 255
    v=0; // non pris en compte pour palier aux variations de luminosité
    ds = 75;
    dh = 10;
    CvPoint positionObj = cvPoint(-1, -1);

}

Webcam ::~Webcam()
{
    //destructor
}

/*int Webcam::initWindow(const char *name)
{
    // Définition de la fenêtre + redimensionnement :
    cvNamedWindow(name, 0);
    cvResizeWindow(name, 1280,960);
    return 0;
}*/



VideoCapture Webcam:: initFlux() {

    // Ouverture du flux video :
	VideoCapture capture(0);

    // Verification si l'ouverture du flux est ok :
	if(!capture.isOpened())
    {
        cout << "Erreur ouverture flux video." << endl;
        return NULL;
    }

    return capture;
}



Mat Webcam :: binairisation (Mat fluxOriginal) {

	Mat hsv;
	vector<Mat> planes;
	cvtColor(fluxOriginal, hsv, CV_BGR2HSV);
	split(hsv, planes);

	//seuillages
	Mat imgH = planes[0];
	Mat imgS = planes[1];
	Mat imgV = planes[2];
	Mat mask = Mat::zeros(hsv.size(), CV_8UC1);

	int largeur = imgH.cols;
	int hauteur = imgH.rows;
	int i=0;
	int j=0;
	for(i=0;i<(hauteur);i++){
		for(j=0;j<(largeur);j++){
			int pixelH = imgH.at<unsigned char>(i, j);
			int pixelS = imgS.at<unsigned char>(i, j);
			int pixelV = imgV.at<unsigned char>(i, j);
			if( (h-dh)<pixelH && pixelH<(h+dh) && (s-ds)<pixelS && pixelS<(s+ds) ){
				mask.at<unsigned char>(i, j) = 255;
			} else {
				mask.at<unsigned char>(i, j) = 0;
			}
		}
	}

	return mask;
}


CvPoint Webcam :: calculBarycentre (Mat mask) {

    sommeX=0;
    sommeY=0;
    nbPixels=0;

    int largeur = mask.cols;
    int hauteur = mask.rows;
    int i=0;
    int j=0;
    for(i=0;i<(hauteur);i++){
    	for(j=0;j<(largeur);j++){
            if (mask.at<unsigned char>(i, j) == 255) {
                        sommeX += j;
                        sommeY += i;
                        nbPixels ++;
            }
        }
    }

    if(nbPixels > 40)
        return cvPoint ((int)(sommeX/nbPixels),(int)(sommeY/nbPixels));
    else
        return cvPoint(-1, -1);
}


Mat Webcam :: tracking(CvPoint barycentre, Mat image) {

    int objectNextStepX, objectNextStepY;
    CvPoint positionAct = barycentre;

    //construction d'un rectangle délimitant la zone de tire
    rectangle(image, cvPoint(280,200), cvPoint(360,280), cvScalar(0,215,255), 1, 4);


    //s'il y a assez de pixel on calcul la prochaine position du cercle
    if (nbPixels > 225) { //60

        //si le barycentre est hors de l'image on ne change pas sa position
        if (positionAct.x == -1 || positionAct.y == -1) {
            positionAct.x = positionAct.x;
            positionAct.y = positionAct.y;
        }
        // change pas à pas la position de l'object vers la position désiriée
        if(abs( positionAct.x - barycentre.x) > 5 ) {
            objectNextStepX = max(5, min (100, abs(positionAct.x - barycentre.x)/2));
            positionAct.x += (-1)* sign(positionAct.x - barycentre.x) * objectNextStepX;
        }
        if(abs( positionAct.y - barycentre.y) > 5 ) {
            objectNextStepY = max(5, min (100, abs(positionAct.y - barycentre.y)/2));
            positionAct.y += (-1)* sign(positionAct.y - barycentre.y) * objectNextStepY;
        }

        circle(image, positionAct, 15, CV_RGB(255,0,0), -1);

    }

    else {
        positionAct.x = -1;
        positionAct.y = -1;
    }


    return image;
}


void Webcam :: affiche (Mat imageTracking, Mat imageBinaire) {

	imshow("Image tracking", imageTracking); // affichage de l'image avec le tracking
	imshow("Image binaire", imageBinaire); // affichage de l'image de la binairisation

}

