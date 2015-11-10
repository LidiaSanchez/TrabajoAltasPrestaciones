#ifndef FUNCIONESC_H_
#define FUNCIONESC_H_


#include "funcionesPersonales.h"
#include "variables.h"

#include "funcionesD.h"


//****************************************************************************************
//*                                                                                      *
//*  Input:                                                                              *
//*                                                                                      *
//*  Output:      AET,BET,ATT,BTT,CT,DT = coeficientes de integracion                    *
//*  Usage:                                                                              *
//*  Description: Realiza las integraciones analiticas.                                  *
//*                                                                                      *
//*                                                                                      *
//*                                                                                      *
//****************************************************************************************

void ANALITICA(double AEA[3][3],double BEA[3][3],double* punteroA_ATA,double* punteroA_BTA,double CTEA[3],double DTEA[3][3],double n[3],double bar[3])
{
	//* Declaracion de variables


	/*double AEA[3][3];*	//*double BEA[3][3];*/;      //Coeficientes de integracion elasticos
	double ATA=*punteroA_ATA;double BTA=*punteroA_BTA;;	//Coeficientes de integracion termicos
	/*double CTEA[3];*	//*double DTEA[3][3];*/;      //Coeficientes de integracion termoelasticos

	int  i,j;
	/*double n[3];*/;	//vector normal al elemento
	/*double bar[3];*/;	//baricentro del elemento


	double  XB,YB,ZB,R,DD,SE,CO,T2,XI1,C,C1,C4,C5;
	double  E11,E12,E13,E21,E22,E23,E31,E32,E33;


	//*---------------------------------------------------------------------------------------?


	//*Inicializamos los coeficientes
	//coeficientes elasticos
	if((tpproE == 1) || (tpproTE == 1))        
	{
		for( i=1; i<=3; i++)            
		{
			for( j=1; j<=3; j++)                
			{
				AEA[i-1][j-1]=0.0;
				BEA[i-1][j-1]=0.0;
			}
		}
	}
	//*coeficientes termicos
	if((tpproT == 1) || (tpproTE == 1))        
	{
		ATA=0.50;
		BTA=0.0;
	}
	//*coeficientes termoelasticos
	if(tpproTE == 1)        
	{
		for( i=1; i<=3; i++)            
		{
			CTEA[i-1]=0.0;
			for( j=1; j<=3; j++)                
			{
				DTEA[i-1][j-1]=0.0;
			}
		}
	}
	//*=========================================================================================


	//* Como ANTONIO


	C=1.0/(16.0*4.0*atan(1.0)*GT*(1-nuT));
	C1=(1-2.0*nuT)/(2.0*(1-nuT)*4*4.0*atan(1.0));
	C4=1/(4.0*4.0*atan(1.0));
	C5=alT*(1.0+nuT)/(8.0*4.0*atan(1.0)*(1.0-nuT));

	//C=1.D0/(16.D0*3.141592654D0*GT*(1-nuT))
	//C1=(1-2.D0*nuT)/(2.D0*(1-nuT)*4*3.141592654D0)
	//C4=1/(4.D0*3.141592654D0)
	//C5=alT*(1.D0+nuT)/(8.D0*3.141592654D0*(1.D0-nuT))

	XB=bar[1-1];
	YB=bar[2-1];
	ZB=bar[3-1];
	E31=n[1-1];
	E32=n[2-1];
	E33=n[3-1];

	for( i=1; i<=3; i++)      
	{
		R=sqrt(pow((extr[i-1][1-1]-extr[i+1-1][1-1]),2)+pow((extr[i-1][2-1]-extr[i+1-1][2-1]),2)+pow((extr[i-1][3-1]-extr[i+1-1][3-1]),2));
		E11=(extr[i-1][1-1]-extr[i+1-1][1-1])/R;
		E12=(extr[i-1][2-1]-extr[i+1-1][2-1])/R;
		E13=(extr[i-1][3-1]-extr[i+1-1][3-1])/R;
		E21=E32*E13-E33*E12;
		E22=E33*E11-E31*E13;
		E23=E31*E12-E32*E11;
		DD=fabs(E21*(extr[i-1][1-1]-XB)+E22*(extr[i-1][2-1]-YB)+E23*(extr[i-1][3-1]-ZB));
		for( j=i; j<=i+1; j++)            
		{
			R=sqrt(pow((XB-extr[j-1][1-1]),2)+pow((YB-extr[j-1][2-1]),2)+pow((ZB-extr[j-1][3-1]),2));
			XI1=(extr[j-1][1-1]-XB)*E11+(extr[j-1][2-1]-YB)*E12+(extr[j-1][3-1]-ZB)*E13;

			SE=XI1/R;

			CO=DD/R;

			T2=log((SE+1.0)/CO);

			if((tpproE == 1) || (tpproTE == 1))                
			{
				AEA[1-1][2-1]=AEA[1-1][2-1]-(1.0+(i-j)*2.0)*C1*E13*log(R+XI1);
				AEA[1-1][3-1]=AEA[1-1][3-1]+(1.0+(i-j)*2.0)*C1*E12*log(R+XI1);
				AEA[2-1][3-1]=AEA[2-1][3-1]-(1.0+(i-j)*2.0)*C1*E11*log(R+XI1);

				BEA[1-1][1-1]=BEA[1-1][1-1]+(DD*C*((3.0-4.0*nuT)*T2+pow(E11,2)*(-SE+T2)+pow(E21,2)*SE-
				2*E11*E21*CO))*(1.0+(i-j)*2.0);;
				BEA[2-1][2-1]=BEA[2-1][2-1]+(DD*C*((3.0-4.0*nuT)*T2+pow(E12,2)*(-SE+T2)+pow(E22,2)*SE-
				2*E12*E22*CO))*(1.0+(i-j)*2.0);;
				BEA[3-1][3-1]=BEA[3-1][3-1]+(DD*C*((3.0-4.0*nuT)*T2+pow(E13,2)*(-SE+T2)+pow(E23,2)*SE-
				2*E13*E23*CO))*(1.0+(i-j)*2.0);;
				BEA[1-1][2-1]=BEA[1-1][2-1]+(1.0+(i-j)*2.0)*DD*C*(E11*E12*(-SE+T2)+
				E21*E22*SE-(E11*E22+E21*E12)*CO);;
				BEA[1-1][3-1]=BEA[1-1][3-1]+(1.0+(i-j)*2.0)*DD*C*(E11*E13*(-SE+T2)+
				E21*E23*SE-(E11*E23+E21*E13)*CO);;
				BEA[2-1][3-1]=BEA[2-1][3-1]+(1.0+(i-j)*2.0)*DD*C*(E12*E13*(-SE+T2)+
				E22*E23*SE-(E12*E23+E22*E13)*CO);;
			}
			if((tpproT == 1) || (tpproTE == 1))                
			{
				BTA=BTA+(1+(i-j)*2.0)*C4*DD*T2;
			}
			if(tpproTE == 1)                
			{
				CTEA[1-1]=CTEA[1-1]+(1+(i-j)*2.0)*pow(DD,2)*C5/2.0*(E11/CO+E21*T2);
				CTEA[2-1]=CTEA[2-1]+(1+(i-j)*2.0)*pow(DD,2)*C5/2.0*(E12/CO+E22*T2);
				CTEA[3-1]=CTEA[3-1]+(1+(i-j)*2.0)*pow(DD,2)*C5/2.0*(E13/CO+E23*T2);

				DTEA[1-1][1-1]=DTEA[1-1][1-1]+(1+(i-j)*2.0)*C5*DD*(T2-E11*E11*(T2-SE)+
				(E11*E21+E21*E11)*CO-(E21*E21)*SE);;
				DTEA[2-1][2-1]=DTEA[2-1][2-1]+(1+(i-j)*2.0)*C5*DD*(T2-E12*E12*(T2-SE)+
				(E12*E22+E22*E12)*CO-(E22*E22)*SE);;
				DTEA[3-1][3-1]=DTEA[3-1][3-1]+(1+(i-j)*2.0)*C5*DD*(T2-E13*E13*(T2-SE)+
				(E13*E23+E23*E13)*CO-(E23*E23)*SE);;
				DTEA[1-1][2-1]=DTEA[1-1][2-1]+(1+(i-j)*2.0)*C5*DD*(-E11*E12*(T2-SE)+
				(E11*E22+E21*E12)*CO-(E21*E22)*SE);;
				DTEA[1-1][3-1]=DTEA[1-1][3-1]+(1+(i-j)*2.0)*C5*DD*(-E11*E13*(T2-SE)+
				(E11*E23+E21*E13)*CO-(E21*E23)*SE);;
				DTEA[2-1][3-1]=DTEA[2-1][3-1]+(1+(i-j)*2.0)*C5*DD*(-E12*E13*(T2-SE)+
				(E12*E23+E22*E13)*CO-(E22*E23)*SE);;
			}
		}
	}
	DTEA[2-1][1-1]=DTEA[1-1][2-1];
	DTEA[3-1][1-1]=DTEA[1-1][3-1];
	DTEA[3-1][2-1]=DTEA[2-1][3-1];

	if((tpproE == 1) || (tpproTE == 1))          
	{
		for( i=1; i<=2; i++)            
		{
			AEA[i-1][i-1]=AEA[i-1][i-1]+0.50;
			for( j=i+1; j<=3; j++)                
			{
				AEA[j-1][i-1]=-AEA[i-1][j-1];
				BEA[j-1][i-1]=BEA[i-1][j-1];
			}
		}
		AEA[3-1][3-1]=AEA[3-1][3-1]+0.50;
	}
	*punteroA_ATA = ATA; *punteroA_BTA = BTA; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:       extrs(4,3) = Coordenadas de los vertices del triangulo a     *
//*                           dividir                                          *
//*  Output:      subextr(4,3,3) = Coordenadas de los vertices de los cuatro   *
//*                                subtriangulos                               *
//*  Usage:                                                                    *
//*  Description: Divide un triangulo en cuatro triangulos segun esquema       *
//*                                                                            *
//*          1  ----------------------------  3                                *
//*             \              /\          /                                   *
//*              \     1     /    \   2   /                                    *
//*                \       /   3    \    /                                     *
//*                  \   /            \ /                                      *
//*                    \ --------------/                                       *
//*                      \            /                                        *
//*                        \    4    /                                         *
//*                          \      /                                          *
//*                            \   /                                           *
//*                              \/                                            *
//*                               2                                            *
//*                                                                            *
//******************************************************************************

void SUBDIVIDE(double extrs[4][3],double subextr[4][4][3])
{
	//* Declaracion de variables

	/*double subextr[4][4][3];*/;	//Coordenadas de los vertices de los cuatro subtriangulos
	/*double extrs[4][3];*/;	//Coordenadas de los vertices del triangulo a dividir
	//* Subelemento 1
	//* Vertice 1
	subextr[1-1][1-1][1-1]=extrs[1-1][1-1];
	subextr[1-1][1-1][2-1]=extrs[1-1][2-1];
	subextr[1-1][1-1][3-1]=extrs[1-1][3-1];
	//* Vertice 2
	subextr[1-1][2-1][1-1]=(extrs[1-1][1-1]+extrs[2-1][1-1])/2.0;
	subextr[1-1][2-1][2-1]=(extrs[1-1][2-1]+extrs[2-1][2-1])/2.0;
	subextr[1-1][2-1][3-1]=(extrs[1-1][3-1]+extrs[2-1][3-1])/2.0;
	//* Vertice 3
	subextr[1-1][3-1][1-1]=(extrs[1-1][1-1]+extrs[3-1][1-1])/2.0;
	subextr[1-1][3-1][2-1]=(extrs[1-1][2-1]+extrs[3-1][2-1])/2.0;
	subextr[1-1][3-1][3-1]=(extrs[1-1][3-1]+extrs[3-1][3-1])/2.0;
	//* Vertice 4 = Vertice 1
	subextr[1-1][4-1][1-1]=subextr[1-1][1-1][1-1];
	subextr[1-1][4-1][2-1]=subextr[1-1][1-1][2-1];
	subextr[1-1][4-1][3-1]=subextr[1-1][1-1][3-1];
	//* Subelemento 2
	//* Vertice 1
	subextr[2-1][1-1][1-1]=extrs[3-1][1-1];
	subextr[2-1][1-1][2-1]=extrs[3-1][2-1];
	subextr[2-1][1-1][3-1]=extrs[3-1][3-1];
	//* Vertice 2
	subextr[2-1][2-1][1-1]=(extrs[1-1][1-1]+extrs[3-1][1-1])/2.0;
	subextr[2-1][2-1][2-1]=(extrs[1-1][2-1]+extrs[3-1][2-1])/2.0;
	subextr[2-1][2-1][3-1]=(extrs[1-1][3-1]+extrs[3-1][3-1])/2.0;
	//* Vertice 3
	subextr[2-1][3-1][1-1]=(extrs[2-1][1-1]+extrs[3-1][1-1])/2.0;
	subextr[2-1][3-1][2-1]=(extrs[2-1][2-1]+extrs[3-1][2-1])/2.0;
	subextr[2-1][3-1][3-1]=(extrs[2-1][3-1]+extrs[3-1][3-1])/2.0;
	//* Vertice 4 = Vertice 1
	subextr[2-1][4-1][1-1]=subextr[2-1][1-1][1-1];
	subextr[2-1][4-1][2-1]=subextr[2-1][1-1][2-1];
	subextr[2-1][4-1][3-1]=subextr[2-1][1-1][3-1];
	//* Subelemento 3
	//* Vertice 1
	subextr[3-1][1-1][1-1]=(extrs[1-1][1-1]+extrs[2-1][1-1])/2.0;
	subextr[3-1][1-1][2-1]=(extrs[1-1][2-1]+extrs[2-1][2-1])/2.0;
	subextr[3-1][1-1][3-1]=(extrs[1-1][3-1]+extrs[2-1][3-1])/2.0;
	//* Vertice 2
	subextr[3-1][2-1][1-1]=(extrs[2-1][1-1]+extrs[3-1][1-1])/2.0;
	subextr[3-1][2-1][2-1]=(extrs[2-1][2-1]+extrs[3-1][2-1])/2.0;
	subextr[3-1][2-1][3-1]=(extrs[2-1][3-1]+extrs[3-1][3-1])/2.0;
	//* Vertice 3
	subextr[3-1][3-1][1-1]=(extrs[1-1][1-1]+extrs[3-1][1-1])/2.0;
	subextr[3-1][3-1][2-1]=(extrs[1-1][2-1]+extrs[3-1][2-1])/2.0;
	subextr[3-1][3-1][3-1]=(extrs[1-1][3-1]+extrs[3-1][3-1])/2.0;
	//* Vertice 4 = Vertice 1
	subextr[3-1][4-1][1-1]=subextr[3-1][1-1][1-1];
	subextr[3-1][4-1][2-1]=subextr[3-1][1-1][2-1];
	subextr[3-1][4-1][3-1]=subextr[3-1][1-1][3-1];
	//* Subelemento 4
	//* Vertice 1
	subextr[4-1][1-1][1-1]=extrs[2-1][1-1];
	subextr[4-1][1-1][2-1]=extrs[2-1][2-1];
	subextr[4-1][1-1][3-1]=extrs[2-1][3-1];
	//* Vertice 2
	subextr[4-1][2-1][1-1]=(extrs[2-1][1-1]+extrs[3-1][1-1])/2.0;
	subextr[4-1][2-1][2-1]=(extrs[2-1][2-1]+extrs[3-1][2-1])/2.0;
	subextr[4-1][2-1][3-1]=(extrs[2-1][3-1]+extrs[3-1][3-1])/2.0;
	//* Vertice 3
	subextr[4-1][3-1][1-1]=(extrs[1-1][1-1]+extrs[2-1][1-1])/2.0;
	subextr[4-1][3-1][2-1]=(extrs[1-1][2-1]+extrs[2-1][2-1])/2.0;
	subextr[4-1][3-1][3-1]=(extrs[1-1][3-1]+extrs[2-1][3-1])/2.0;
	//* Vertice 4 = Vertice 1
	subextr[4-1][4-1][1-1]=subextr[4-1][1-1][1-1];
	subextr[4-1][4-1][2-1]=subextr[4-1][1-1][2-1];
	subextr[4-1][4-1][3-1]=subextr[4-1][1-1][3-1];
	return;
}
//****************************************************************************************
//*                                                                                      *
//*  Input:       el = elemento sobre el que se integra                                  *
//*               nd = nodo desde el que se integra                                      *
//*  Output:      AET,BET,ATT,BTT,CT,DT = coeficientes de integracion                    *
//*  Usage:                                                                              *
//*  Description: Realiza las integraciones numericas.                                   *
//*                                                                                      *
//*                                                                                      *
//****************************************************************************************

void NUMERICA(double AEN[3][3],double BEN[3][3],double* punteroA_ATN,double* punteroA_BTN,double CTEN[3],double DTEN[3][3],double n[3],double* punteroA_distancia)
{
	//* Declaracion de variables


	/*double AEN[3][3];*	//*double BEN[3][3];*/;      //Coeficientes de integracion elasticos
	double ATN=*punteroA_ATN;double BTN=*punteroA_BTN;;	//Coeficientes de integracion termicos
	/*double CTEN[3];*	//*double DTEN[3][3];*/;      //Coeficientes de integracion termoelasticos
	double distancia=*punteroA_distancia;;	//Distancia entre el nodo y el plano del elemento

	double  punt[7][3];	//puntos de integracion de Gauss
	double  Afp;	//auxiliares
	double  Bfp;	//auxiliares
	double  w[7];	//valores de las funciones peso
	double  s;	//Auxiliar para el calculo del area
	double  Area;	//Area del elemento
	int  i,j;	//Auxiliares
	double  lado[3];	//longitud de cada lado del elemento
	double  lad[3][3];	//vector de cada lado del elemento
	/*double n[3];*/;	//vector normal al elemento
	double  XP,YP,ZP,XNUE,YNUE,ZNUE;
	double  R,C,C1,C2,C4,C5;

	//* Calcula los lados de los elementos
	for( i=1; i<=3; i++)      
	{
		lado[i-1]=0.0;
		for( j=1; j<=3; j++)          
		{
			lado[i-1]=lado[i-1]+pow((extr[i+1-1][j-1]-extr[i-1][j-1]),2);
		}
		lado[i-1]=sqrt(lado[i-1]);
	}
	for( i=1; i<=3; i++)      
	{
		for( j=1; j<=3; j++)        
		{
			lad[i-1][j-1]= (extr[i+1-1][j-1]-extr[i-1][j-1])/lado[i-1];
		}
	}
	//* Calcula el area del elemento (3 lados)
	s=(lado[1-1]+lado[2-1]+lado[3-1])/2.0;
	Area=sqrt(s*(s-lado[1-1])*(s-lado[2-1])*(s-lado[3-1]));

	//* Calcula los puntos de integracón
	GAUSS(punt);if(enExcepcion==1)return;

	//* funciones peso
	Afp=(155.0+sqrt(15.0))/2400.0;
	Bfp=31.0/240.0-Afp;

	w[1-1]=9.0/80.0;
	w[2-1]=Afp;
	w[3-1]=Afp;
	w[4-1]=Afp;
	w[5-1]=Bfp;
	w[6-1]=Bfp;
	w[7-1]=Bfp;
	//*-----------------------------------------------------------------------------------?
	//* Inicializamos coeficientes
	//*coeficientes termicos
	if((tpproT == 1) || (tpproTE == 1))        
	{
		ATN=0.0;
		BTN=0.0;
	}
	//*coeficientes elasticos
	if((tpproE == 1) || (tpproTE == 1))        
	{
		for( i=1; i<=3; i++)            
		{
			for( j=1; j<=3; j++)                
			{
				AEN[i-1][j-1]=0.0;
				BEN[i-1][j-1]=0.0;
			}
		}
	}
	//*coeficientes termoelasticos
	if(tpproTE == 1)        
	{
		for( i=1; i<=3; i++)            
		{
			CTEN[i-1]=0.0;
			for( j=1; j<=3; j++)                
			{
				DTEN[i-1][j-1]=0.0;
			}
		}
	}
	//* ANTONIO  =========================================================================
	C=1.0/(16.0*4.0*atan(1.0)*GT*(1-nuT));
	C1=(1-2.0*nuT)/(2.0*(1-nuT)*4*4.0*atan(1.0));
	C2=3.0/(1.0-2.0*nuT);
	C4=1/(4.0*4.0*atan(1.0));
	C5=alT*(1.0+nuT)/(8.0*4.0*atan(1.0)*(1.0-nuT));
	//C=1.D0/(16.D0*3.141592654D0*GT*(1-nuT))
	//C1=(1-2.D0*nuT)/(2.D0*(1-nuT)*4*3.141592654D0)
	//C2=3.D0/(1.D0-2.D0*nuT)
	//C4=1/(4.D0*3.141592654D0)
	//C5=alT*(1.D0+nuT)/(8.D0*3.141592654D0*(1.D0-nuT))


	XP=ndCol[1-1];
	YP=ndCol[2-1];
	ZP=ndCol[3-1];
	XNUE=n[1-1];
	YNUE=n[2-1];
	ZNUE=n[3-1];

	for( i=1; i<=7; i++)      
	{
		R=sqrt(pow((punt[i-1][1-1]-XP),2)+pow((punt[i-1][2-1]-YP),2)+pow((punt[i-1][3-1]-ZP),2));
		if((tpproE == 1) || (tpproTE == 1))        
		{
			BEN[1-1][1-1]=BEN[1-1][1-1]+(C*(3.0-4.0*nuT+pow(((punt[i-1][1-1]-XP)/R),2))/R)*w[i-1]*2*Area;
			BEN[2-1][2-1]=BEN[2-1][2-1]+(C*(3.0-4.0*nuT+pow(((punt[i-1][2-1]-YP)/R),2))/R)*w[i-1]*2*Area;
			BEN[3-1][3-1]=BEN[3-1][3-1]+(C*(3.0-4.0*nuT+pow(((punt[i-1][3-1]-ZP)/R),2))/R)*w[i-1]*2*Area;
			BEN[1-1][2-1]=BEN[1-1][2-1]+(C*(punt[i-1][1-1]-XP)*(punt[i-1][2-1]-YP)/pow(R,3))*w[i-1]*2*Area;
			BEN[1-1][3-1]=BEN[1-1][3-1]+(C*(punt[i-1][1-1]-XP)*(punt[i-1][3-1]-ZP)/pow(R,3))*w[i-1]*2*Area;
			BEN[2-1][3-1]=BEN[2-1][3-1]+(C*(punt[i-1][2-1]-YP)*(punt[i-1][3-1]-ZP)/pow(R,3))*w[i-1]*2*Area;
			AEN[1-1][1-1]=AEN[1-1][1-1]-(C1*distancia*(1.0+C2*pow(((punt[i-1][1-1]-XP)/R),2))/pow(R,3))*w[i-1]*2*Area;
			AEN[2-1][2-1]=AEN[2-1][2-1]-(C1*distancia*(1.0+C2*pow(((punt[i-1][2-1]-YP)/R),2))/pow(R,3))*w[i-1]*2*Area;
			AEN[3-1][3-1]=AEN[3-1][3-1]-(C1*distancia*(1.0+C2*pow(((punt[i-1][3-1]-ZP)/R),2))/pow(R,3))*w[i-1]*2*Area;
			AEN[1-1][2-1]=AEN[1-1][2-1]-(C1/pow(R,3)*(distancia*C2*(punt[i-1][1-1]-XP)*(punt[i-1][2-1]-YP)/pow(R,2)-
			YNUE*(punt[i-1][1-1]-XP)+XNUE*(punt[i-1][2-1]-YP)))*w[i-1]*2*Area;;
			AEN[1-1][3-1]=AEN[1-1][3-1]-(C1/pow(R,3)*(distancia*C2*(punt[i-1][1-1]-XP)*(punt[i-1][3-1]-ZP)/pow(R,2)-
			ZNUE*(punt[i-1][1-1]-XP)+XNUE*(punt[i-1][3-1]-ZP)))*w[i-1]*2*Area;;
			AEN[2-1][3-1]=AEN[2-1][3-1]-(C1/pow(R,3)*(distancia*C2*(punt[i-1][2-1]-YP)*(punt[i-1][3-1]-ZP)/pow(R,2)-
			ZNUE*(punt[i-1][2-1]-YP)+YNUE*(punt[i-1][3-1]-ZP)))*w[i-1]*2*Area;;
			AEN[2-1][1-1]=AEN[2-1][1-1]-(C1/pow(R,3)*(distancia*C2*(punt[i-1][1-1]-XP)*(punt[i-1][2-1]-YP)/pow(R,2)-
			XNUE*(punt[i-1][2-1]-YP)+YNUE*(punt[i-1][1-1]-XP)))*w[i-1]*2*Area;;
			AEN[3-1][1-1]=AEN[3-1][1-1]-(C1/pow(R,3)*(distancia*C2*(punt[i-1][1-1]-XP)*(punt[i-1][3-1]-ZP)/pow(R,2)-
			XNUE*(punt[i-1][3-1]-ZP)+ZNUE*(punt[i-1][1-1]-XP)))*w[i-1]*2*Area;;
			AEN[3-1][2-1]=AEN[3-1][2-1]-(C1/pow(R,3)*(distancia*C2*(punt[i-1][2-1]-YP)*(punt[i-1][3-1]-ZP)/pow(R,2)-
			YNUE*(punt[i-1][3-1]-ZP)+ZNUE*(punt[i-1][2-1]-YP)))*w[i-1]*2*Area;;

		}
		if((tpproT == 1) || (tpproTE == 1))        
		{
			ATN=ATN-C4*distancia*(1/pow(R,3))*w[i-1]*2.0*Area;
			BTN=BTN+C4*(1/R)*w[i-1]*2.0*Area;
		}
		if(tpproTE == 1)        
		{
			CTEN[1-1]=CTEN[1-1]+C5*((punt[i-1][1-1]-XP)/R)*w[i-1]*2*Area;
			CTEN[2-1]=CTEN[2-1]+C5*((punt[i-1][2-1]-YP)/R)*w[i-1]*2*Area;
			CTEN[3-1]=CTEN[3-1]+C5*((punt[i-1][3-1]-ZP)/R)*w[i-1]*2*Area;

			DTEN[1-1][1-1]=DTEN[1-1][1-1]+C5*((1-pow(((punt[i-1][1-1]-XP)/R),2))/R)*w[i-1]*2*Area;
			DTEN[2-1][2-1]=DTEN[2-1][2-1]+C5*((1-pow(((punt[i-1][2-1]-YP)/R),2))/R)*w[i-1]*2*Area;
			DTEN[3-1][3-1]=DTEN[3-1][3-1]+C5*((1-pow(((punt[i-1][3-1]-ZP)/R),2))/R)*w[i-1]*2*Area;
			DTEN[1-1][2-1]=DTEN[1-1][2-1]+C5*(-(punt[i-1][1-1]-XP)*(punt[i-1][2-1]-YP)/pow(R,3))*w[i-1]*2*Area;
			DTEN[1-1][3-1]=DTEN[1-1][3-1]+C5*(-(punt[i-1][1-1]-XP)*(punt[i-1][3-1]-ZP)/pow(R,3))*w[i-1]*2*Area;
			DTEN[2-1][3-1]=DTEN[2-1][3-1]+C5*(-(punt[i-1][2-1]-YP)*(punt[i-1][3-1]-ZP)/pow(R,3))*w[i-1]*2*Area;

		}
	}
	BEN[2-1][1-1]=BEN[1-1][2-1];
	BEN[3-1][1-1]=BEN[1-1][3-1];
	BEN[3-1][2-1]=BEN[2-1][3-1];
	DTEN[2-1][1-1]=DTEN[1-1][2-1];
	DTEN[3-1][1-1]=DTEN[1-1][3-1];
	DTEN[3-1][2-1]=DTEN[2-1][3-1];

	*punteroA_ATN = ATN; *punteroA_BTN = BTN; *punteroA_distancia = distancia; return;
}
#endif /* FUNCIONESC_H_ */

