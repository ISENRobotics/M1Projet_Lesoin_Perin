#include "commun.h"


void configLauncher (missile_usb * control_device) {
	int i,j,k,l=0;
	for (i=0;i<90;i++) {
		action(control_device,1,95); // le lance missile tourne de 180 deg pour 90 action d'un delay de 110
		cout << i << endl;
	}

	for (j=0;j<45;j++) {
		action(control_device,2,95); // le lance missile tourne de 90 deg pour 45 action d'un delay de 110
		cout << j << endl;
	}

	for (k=0;k<35;k++) {
		action(control_device,3,95);
		cout << k << endl;
	}

	for (l=0;l<25;l++) {
		action(control_device,4,95);
		cout << l << endl;
	}



}




