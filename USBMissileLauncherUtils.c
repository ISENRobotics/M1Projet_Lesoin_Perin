#ifndef DEPEND
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/io.h>
#include <errno.h>
#include <linux/input.h>
#endif
#include "InputEvent.h"
#include "USBMissileLauncher.h"
#include "traitement.h"
#include "action.h"
#include "initialisation.h"

#define USB_TIMEOUT 1000 /* milliseconds */

missile_usb *control;

int main() {

	int Dx = 0;	// de 0 à 640 
	int Dy = 0; // de 0 à 480 
	
  int device_type = 1;
  FILE* fichier = NULL;
  
  init(&device_type);
  
  fichier = fopen("coordonnees.txt", "r+");
  
  if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier
        // Boucle de lecture des caractères un à un
        do
        {
            fscanf(fichier, "%d %d", &Dx, &Dy);
  					fprintf(stderr,"x:%d y:%d \n",Dx,Dy);
            traitement(Dx,Dy);
            //usleep(500);

        } while (Dx != EOF);
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier coordonnees.txt \n");
    }
    	
  
  //traitement(Dx,Dy);

  missile_usb_destroy(control);  

  return 0;
}

//=============================================================================

/*
 * Local Variables:
 * mode: C
 * End:
 */

// structure à respecter : INIT / IF / DO
