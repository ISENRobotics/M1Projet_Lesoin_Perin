/*
 * transformtation_control.cpp
 *
 *  Created on: 16 mai 2017
 *      Author: isen
 */

#include "commun.h"

#include <boost/multi_array.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;
using namespace boost;



int transformation_control (float distance_objet,float distance_WD, float distance_WG, float angle_gauche, float angle_droite) {

	int l,j,k,z,y;
	float R[4][4]={0}; //matrice de transformation tot (produit des T[i])
	float T[4][4]={0}; //matrice de denavit
	float M[4][4]={0};
	float Ow[4]={0}; //origine "world
	float Od[4]={0}; //origine après changement de repère de droite
	float Og[4]={0}; //origine après changement de repère de gauche

	Ow[3]=1;

	//tableau de denavit initialisé pour la transformation en passant par la droite

		float teta[10]={0};
		teta[0]=PI/2;
		teta[1]=PI/2-((angle_droite*2*PI)/360);
		teta[2]=PI/2;
		teta[3]=PI/2;
		//teta[5]=angle_droite_vertical; à récupérer dans le main
		teta[7]=-PI/2;


		float alpha[10]={0};
		alpha[4]=PI/2;
		alpha[6]=-PI/2;
		alpha[8]=PI/2;

		float d[10]={0};
		d[0]=30;
		d[2]=3;
		d[3]=5;
		d[6]=-4;

		float r[10]={0};
		r[1]=5.6;
		float H=pow(distance_WD,2)+pow(distance_objet-7,2);
		r[9]=sqrt(H);


		for (z=0;z<2;z++) {

			if (z==1) {		//z==1 transformation de repère passant par la gauche

				H=pow(distance_WG,2)+pow(distance_objet-7,2);
				r[9]=sqrt(H);
				teta[1]=((angle_gauche*2*PI)/360)-PI/2;
				d[0]=-20;
			}
			int i=0;

			R[0][0]=cos(teta[i]);
			R[0][1]=-sin(teta[i]);
			R[0][2]=0;
			R[0][3]=d[i];
			R[1][0]=cos(alpha[i])*sin(teta[i]);
			R[1][1]=cos(alpha[i])*cos(teta[i]);
			R[1][2]=-sin(alpha[i]);
			R[1][3]=-r[i]*sin(alpha[i]);
			R[2][0]=sin(alpha[i])*sin(teta[i]);
			R[2][1]=sin(alpha[i])*cos(teta[i]);
			R[2][2]=cos(alpha[i]);
			R[2][3]=r[i]*cos(alpha[i]);
			R[3][0]=0;
			R[3][1]=0;
			R[3][2]=0;
			R[3][3]=1;


			for (i=1;i<10;i++) {

				M[0][0]=0;
				M[0][1]=0;
				M[0][2]=0;
				M[0][3]=0;
				M[1][0]=0;
				M[1][1]=0;
				M[1][2]=0;
				M[1][3]=0;
				M[2][0]=0;
				M[2][1]=0;
				M[2][2]=0;
				M[2][3]=0;
				M[3][0]=0;
				M[3][1]=0;
				M[3][2]=0;
				M[3][3]=0;

				T[0][0]=cos(teta[i]);
				T[0][1]=-sin(teta[i]);
				T[0][2]=0;
				T[0][3]=d[i];
				T[1][0]=cos(alpha[i])*sin(teta[i]);
				T[1][1]=cos(alpha[i])*cos(teta[i]);
				T[1][2]=-sin(alpha[i]);
				T[1][3]=-r[i]*sin(alpha[i]);
				T[2][0]=sin(alpha[i])*sin(teta[i]);
				T[2][1]=sin(alpha[i])*cos(teta[i]);
				T[2][2]=cos(alpha[i]);
				T[2][3]=r[i]*cos(alpha[i]);
				T[3][0]=0;
				T[3][1]=0;
				T[3][2]=0;
				T[3][3]=1;

				//printf(" MATRICE T \n%f       %f       %f       %f\n%f         %f         %f       %f\n%f         %f         %f       %f\n%f         %f         %f       %f\n",T[0][0],T[0][1],T[0][2],T[0][3],T[1][0],T[1][1],T[1][2],T[1][3],T[2][0],T[2][1],T[2][2],T[2][3],T[3][0],T[3][1],T[3][2],T[3][3]);
		//calcul de la matrice de transformation R
				for (l=0;l<4;l++) //ligne
					{
						for (j=0;j<4;j++) //colonne
						{
							for (k=0;k<4;k++)
							{
								M[l][j]=R[l][k]*T[k][j]+M[l][j];
							}
						}
					}


					R[0][0]=M[0][0];
					R[0][1]=M[0][1];
					R[0][2]=M[0][2];
					R[0][3]=M[0][3];
					R[1][0]=M[1][0];
					R[1][1]=M[1][1];
					R[1][2]=M[1][2];
					R[1][3]=M[1][3];
					R[2][0]=M[2][0];
					R[2][1]=M[2][1];
					R[2][2]=M[2][2];
					R[2][3]=M[2][3];
					R[3][0]=M[3][0];
					R[3][1]=M[3][1];
					R[3][2]=M[3][2];
					R[3][3]=M[3][3];
			}

			if (z==1) { //calcul du repère Og après transformation par la gauche

				for (l=0;l<4;l++) //ligne
				{
					for (k=0;k<4;k++)
					{
						Og[l]=R[l][k]*Ow[k]+Og[l];
					}
				}
			}
			else {
				for (l=0;l<4;l++) //ligne
				{
					for (k=0;k<4;k++)
					{
						Od[l]=R[l][k]*Ow[k]+Od[l];
					}
				}

			}

		}


		//printf("MATRICE R FINAL\n%f       %f       %f       %f\n%f         %f         %f       %f\n%f         %f         %f       %f\n%f         %f         %f       %f\n",R[0][0],R[0][1],R[0][2],R[0][3],R[1][0],R[1][1],R[1][2],R[1][3],R[2][0],R[2][1],R[2][2],R[2][3],R[3][0],R[3][1],R[3][2],R[3][3]);

	int check = 0;
	for (y=0;y<4;y++){
		printf("Od[%d]=%f    Og[%d]=%f \n",y,Od[y],y,Og[y]);
		if ( Od[y]<=(Og[y]+5) && Od[y]>=(Og[y]-5) ){
			check = 1;
		}
		else{
			check = 0;
		}
	}


   return check;

}
