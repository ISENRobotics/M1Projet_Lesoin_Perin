#include "commun.h"

missile_usb *control_main;

int main(int argc, char* argv[]) {

	//driver lance missile
    int device_type = 1;

	// Initialisation variable pour les calculs d'angles
	float angleCibleLauncherPan = 0; //angle cible horizontal du lanceur
	float dwg = 0; //distance entre la webcam de gauche et la projection perpendiculaire de l'objet sur la planche
	float dwd = 0; //distance entre la webcam de droite et la projection perpendiculaire de l'objet sur la planche
	float dl = 0; //distance entre la projection perpendiculaire de l'objet sur la planche et le lanceur
	float ang1 = 0; //variable intermédiaire de calcul
	float angleLauncherPan = 90; // angle honrizontal du lanceur après initialisation
	float angleLauncherTilt = 90; // angle vertical du lanceur après initialisation
	float ratio; // ratiode différenciation entre le nombre de pixels de l'objet tracké principal et le secondaire
	float distancePlancheObjet = 0; // distance minimale entre l'objet traqué et la planche
	float angleCamGauche = 0; // angle pris par la webcam gauche
	float angleCamDroite = 0; // angle pris par la webcam droite
	float tiltCamGauche = 0; // orientation verticale de la webcam gauche
	int nbPixels1, nbPixels2, nbPixelsLocked1, nbPixelsLocked2 = 0; // nb de pixels rouge sur l'image de la webcam 1 (gauche)

	// Partie Tracking
	char key=0;
	int focus1, focus2, locked1, locked2, check = 0; // défini quelle webcam traque l'objet prioritaire (le plus gros)
	Mat image1, image2;
	Mat imageBinaire1, imageBinaire2; //images binarisé avec les traitement sur la couleur rouge
	Mat imageTracking1, imageTracking2; //image de tracking (cible plus zone de vérouillage)
	VideoCapture fluxVideo1, fluxVideo2;
	CvPoint positionObj1, positionObj2; //positions à l'image des barycentres sur les webcams 1 et 2
	int dx1=0, dy1=0, dx2, dy2; // écart entre le centre de l'image et le barycentre traqué sur les webcam 1 et 2


	//Initialisation des servocontroler
	PololuMaestro driver;
	Servo  pan1(&driver, 2);
	pan1.configuration(2000);
	Servo tilt1(&driver, 3);
	tilt1.configuration(2000);
	Servo pan2(&driver, 0);
	pan2.configuration(2000);
	Servo tilt2(&driver, 1);
	tilt2.configuration(1800);
	cout << "fin initialisation servos" << endl;

	//initialisation objet webcam et lance missile
    Webcam * maWebcam1 = new Webcam();
    fluxVideo1 = maWebcam1->initFlux(0);
    Webcam * maWebcam2 = new Webcam();
    fluxVideo2 = maWebcam2->initFlux(1);
    missile_usb * control_main=init(device_type);
    state_launcher * state_bruno = new state_launcher();
    configLauncher(control_main);
    cout << "fin initialisation système"  << endl;


    while(key!='q' && key!='Q') {

        fluxVideo1 >> image1; //récupération du flux video dans la var image
        imageBinaire1 = maWebcam1->binairisation(image1); //binairisation de l'image
        positionObj1=maWebcam1->calculBarycentre(imageBinaire1); //calcul barycentre
        imageTracking1 = maWebcam1->tracking(positionObj1, image1); //affiche un point rouge sur la cible

        fluxVideo2 >> image2; //récupération du flux video dans la var image
        imageBinaire2 = maWebcam2->binairisation(image2); //binairisation de l'image
        positionObj2=maWebcam2->calculBarycentre(imageBinaire2); //calcul barycentre
        imageTracking2 = maWebcam2->tracking(positionObj2, image2); //affiche un point rouge sur la cible

        //Affichage des fenetres :
        maWebcam1->affiche(imageTracking1, imageBinaire1, imageTracking2, imageBinaire2, focus1, focus2, locked1, locked2, nbPixelsLocked1, nbPixelsLocked2);

        // Calcul des écarts entre le centre des images des webcams et les barycentres en x et y (l'origine des pixel est en haut à gauche)
        dx1=positionObj1.x - 320;
        dy1=240 - positionObj1.y;
        dx2=positionObj2.x - 320;
        dy2=240 - positionObj2.y;


        nbPixels1=maWebcam1->getNbPixels(); // donne le nb de pixels rouges sur le webcam 1
        nbPixels2=maWebcam2->getNbPixels();
        nbPixelsLocked1=maWebcam1->getNbPixelsLocked(imageBinaire1); // donne le nb de pixels rouges vérouillés sur le webcam 1
        nbPixelsLocked2=maWebcam2->getNbPixelsLocked(imageBinaire2);
        cout << "nbPixelsLocked1 = " << nbPixelsLocked1 << endl;
        cout << "nbPixelsLocked2 = " << nbPixelsLocked2 << endl;


        //Définition de l'objet traqué prioritaire
        ratio = (float)nbPixels1/nbPixels2;
        cout << "nbPixels1 = " << nbPixels1 << " et nbPixels2 = " << nbPixels2 << " et ratio = " << ratio << endl;
        if( ratio > 3.8){ // permet de réorienter les webcam vers la cible principale // 3
        	focus1 = 1;
        	focus2 = 0;
        }else if( ratio < 0.2 ) { // 0.3
        	focus2 = 1;
        	focus1 = 0;
        }
        else{
        	focus1 = 1;
        	focus2 = 1;
        }

        //Commande des servos à partir du tracking des webcams
        locked1 = traitementCam(dx1, dy1, pan1, tilt1, focus1, 1, pan1.getPosition(), pan2.getPosition());
        locked2 = traitementCam(dx2, dy2, pan2, tilt2, focus2, 2, pan1.getPosition(), pan2.getPosition());

        //Traitement lance missile
		if(locked1==1 && locked2==1 && focus1==1 && focus2==1 && nbPixelsLocked1>500 && nbPixelsLocked2>500 ){

			// calcul de la distance minimale entre l'objet traqué et la planche
	        angleCamDroite = 172 - ((pan2.getPosition()-50)*(162.0/3736.0));
	        angleCamGauche = 3 + (pan1.getPosition()-5)*(160.0/3795.0);
	       	tiltCamGauche = 55.0 + (tilt1.getPosition()-1250.0)*(47.0/1050.0);
	       	cout << endl << "L'angle de droite est: " << angleCamDroite << endl;
	       	cout << "L'angle de gauche est: " << angleCamGauche << endl;
	       	distancePlancheObjet  = calculDistance(angleCamGauche, angleCamDroite, 50);
	       	cout << "La distance entre le planche et l'objet est : " << distancePlancheObjet << endl;

	       	//calcul des angles à envoyer au lance missile
			ang1 = (angleCamGauche/360 )*2*PI;
			dwg = distancePlancheObjet/tan(ang1);
			dl = 25-dwg;
			dwd=abs(25+dl);
			angleCibleLauncherPan = atan(distancePlancheObjet/dl)*(180/PI); // angle  horizontal cible du lance missile pour viser la cible
			if(angleCibleLauncherPan < 0){
				angleCibleLauncherPan = 180 + angleCibleLauncherPan;
			}
			angleLauncherPan = state_bruno->angle_h; // angle actuel horizontal du lance missile
			angleLauncherTilt = state_bruno->angle_v; // angle actuel vertical du lance missile

	        //Vérification des coordonnées de l'objet dans le même repère
	        check = transformation_control(distancePlancheObjet, dwd, dwg, angleCamGauche, angleCamDroite);
	        if(check ==1){
	        	traitement(control_main,angleCibleLauncherPan, angleLauncherPan, tiltCamGauche, angleLauncherTilt);
	        	state_bruno->angle_h = angleCibleLauncherPan;
	        	state_bruno->angle_v = tiltCamGauche;
	        }
		 }

         if(waitKey(10) >= 0); // on patient 30 milliseconds avant de passer à l'image suivante

    }

    delete maWebcam1;
    delete maWebcam2;
    missile_usb_destroy(control_main);
    return 0;

}
