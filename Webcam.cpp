#include "commun.h"


using namespace cv;

Webcam::Webcam()
{
	nbPixels = 0;
	nbPixelsLocked = 0;
}

Webcam ::~Webcam()
{
    //destructor
}

VideoCapture Webcam:: initFlux(int device) {

    // Ouverture du flux video :
	VideoCapture capture(device);

    // Verification si l'ouverture du flux est ok :
	if(!capture.isOpened())
    {
        cout << "Erreur ouverture flux video." << endl;
        return 0;
    }

	cout <<"Webcam crée" <<endl;

    return capture;
}



Mat Webcam :: binairisation (Mat image) {

	int h = 170; // de 160 à 180
	int s = 175; // de 100 à 255
    //int v = 0;  non pris en compte pour palier aux variations de luminosité
	int ds = 75;
	int dh = 10;

	Mat hsv;
	vector<Mat> planes;
	cvtColor(image, hsv, CV_BGR2HSV);
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
			if( (h-dh)<pixelH && pixelH<(h+dh) && (s-ds)<pixelS && pixelS<(s+ds) ){
				mask.at<unsigned char>(i, j) = 255;
			} else {
				mask.at<unsigned char>(i, j) = 0;
			}
		}
	}

	erode( mask, mask, MORPH_RECT );
	erode( mask, mask, MORPH_RECT );

	return mask;
}


CvPoint Webcam :: calculBarycentre (Mat imageBinaire) {

    int sommeX = 0;
    int sommeY = 0;
    nbPixels = 0;

    int largeur = imageBinaire.cols;
    int hauteur = imageBinaire.rows;
    int i=0;
    int j=0;
    for(i=0;i<(hauteur);i++){
    	for(j=0;j<(largeur);j++){
            if (imageBinaire.at<unsigned char>(i, j) == 255) {
                        sommeX += j;
                        sommeY += i;
                        nbPixels ++;
            }
        }
    }

    if(nbPixels > 300)
        return cvPoint ((int)(sommeX/nbPixels),(int)(sommeY/nbPixels));
    else
        return cvPoint(-1, -1);
}


Mat Webcam :: tracking(CvPoint barycentre, Mat image) {

    int objectNextStepX, objectNextStepY;
    CvPoint positionAct = barycentre;

    //construction d'un rectangle délimitant la zone de tire
    rectangle(image, cvPoint(300,220), cvPoint(340,260), cvScalar(0,215,255), 2, 4);


    //s'il y a assez de pixels binairisé en blanc on calcul la prochaine position du cercle
    if (nbPixels > 300) {

        // si le barycentre est hors de l'image on ne change pas sa position
        // sinon on change pas à pas la position de l'object vers la position désiriée
        if(abs( positionAct.x - barycentre.x) > 5 ) {
            objectNextStepX = max(5, min (100, abs(positionAct.x - barycentre.x)/2));
            positionAct.x += (-1)* sign(positionAct.x - barycentre.x) * objectNextStepX;
        }
        else if(abs( positionAct.y - barycentre.y) > 5 ) {
            objectNextStepY = max(5, min (100, abs(positionAct.y - barycentre.y)/2));
            positionAct.y += (-1)* sign(positionAct.y - barycentre.y) * objectNextStepY;
        }

        circle(image, positionAct, 10, CV_RGB(255,0,0), -1);

    }

    else {
        positionAct.x = -1;
        positionAct.y = -1;
    }


    return image;
}


void Webcam :: affiche (Mat imageTracking1, Mat imageBinaire1, Mat imageTracking2, Mat imageBinaire2, int focus1, int focus2, int locked1, int locked2, int nbPixelsLocked1, int nbPixelsLocked2) {
	if(locked1==1 && focus1==1 && nbPixelsLocked1>500){
		putText(imageTracking1, "Fire !!!", cvPoint(280,60),   FONT_HERSHEY_DUPLEX, 1, cvScalar(0,0,255), 1);
		rectangle(imageTracking1, cvPoint(300,220), cvPoint(340,260), cvScalar(0,0,255), 5, 4);
	}
	if(locked2==1 && focus2==1 && nbPixelsLocked2>500){
		putText(imageTracking2, "Fire !!!", cvPoint(280,60),   FONT_HERSHEY_DUPLEX, 1, cvScalar(0,0,255), 1);
		rectangle(imageTracking2, cvPoint(300,220), cvPoint(340,260), cvScalar(0,0,255), 5, 4);
	}
	imshow("Image tracking 1", imageTracking1); // affichage de l'image avec le tracking
	imshow("Image tracking 2", imageTracking2); // affichage de l'image avec le tracking
	//imshow("Image binaire 1", imageBinaire1); // affichage de l'image de la binairisation
	//imshow("Image binaire 2", imageBinaire2); // affichage de l'image de la binairisation

}

int Webcam :: getNbPixels () {
	return nbPixels;
}

int Webcam :: getNbPixelsLocked (Mat imageBinaire) {

    nbPixelsLocked = 0;

    int i=0;
    int j=0;
    for(i=220;i<=260;i++){
    	for(j=300;j<=340;j++){
            if (imageBinaire.at<unsigned char>(i, j) == 255) {
                        nbPixelsLocked ++;
            }
        }
    }

    return nbPixelsLocked;

}

