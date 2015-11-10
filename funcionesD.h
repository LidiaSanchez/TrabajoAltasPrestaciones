#ifndef FUNCIONESD_H_
#define FUNCIONESD_H_


#include "funcionesPersonales.h"
#include "variables.h"


//******************************************************************************
//*                                                                            *
//*  Input:       el = elemento sobre el que se integra                        *
//*               nd = nodo desde el que se integra                            *
//*  Output:     puntos de integracion y funciones peso                        *
//*  Usage:                                                                    *
//*  Description: Obtiene los puntos de integracion de Gauss                   *
//*                                                                            *
//*                                                                            *
//*                                                                            *
//******************************************************************************

void GAUSS(double punt[7][3])      
{
	//* Declaracion de variables


	/*double punt[7][3];*/;	//puntos de integracion de Gauss
	double  cnat[7][3];	//valores de las coordenadas naturales
	double  acnat;	//auxiliares
	double  bcnat;	//auxiliares
	int  i,p,j;

	//* Coordenadas naturales
	acnat=(6.0+sqrt(15.0))/21.0;
	bcnat=4.0/7.0-acnat;

	cnat[1-1][1-1]=1.0/3.0;
	cnat[2-1][1-1]=1.0-2.0*acnat;
	cnat[3-1][1-1]=acnat;
	cnat[4-1][1-1]=acnat;
	cnat[5-1][1-1]=1.0-2.0*bcnat;
	cnat[6-1][1-1]=bcnat;
	cnat[7-1][1-1]=bcnat;

	cnat[1-1][2-1]=1.0/3.0;
	cnat[2-1][2-1]=acnat;
	cnat[3-1][2-1]=1.0-2.0*acnat;
	cnat[4-1][2-1]=acnat;
	cnat[5-1][2-1]=bcnat;
	cnat[6-1][2-1]=1.0-2.0*bcnat;
	cnat[7-1][2-1]=bcnat;

	cnat[1-1][3-1]=1.0/3.0;
	cnat[2-1][3-1]=acnat;
	cnat[3-1][3-1]=acnat;
	cnat[4-1][3-1]=1.0-2.0*acnat;
	cnat[5-1][3-1]=bcnat;
	cnat[6-1][3-1]=bcnat;
	cnat[7-1][3-1]=1.0-2.0*bcnat;

	//* Inicializacion de los puntos de integracion
	for( p=1; p<=7; p++)        
	{
		for( i=1; i<=3; i++)            
		{
			punt[p-1][i-1]=0.0;
		}
	}
	//* Calculo de los puntos de integracion
	for( p=1; p<=7; p++)        
	{
		for( i=1; i<=3; i++)            
		{
			for( j=1; j<=3; j++)                
			{
				punt[p-1][i-1]=punt[p-1][i-1]+cnat[p-1][j-1]*extr[j-1][i-1];
			}
		}
	}
	return;

}
#endif /* FUNCIONESD_H_ */

