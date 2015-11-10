#ifndef FUNCIONESA_H_
#define FUNCIONESA_H_

#include "funcionesPersonales.h"
#include "variables.h"

#include "funcionesB.h"
#include "funcionesC.h"
#include "funcionesD.h"

//******************************************************************************
//*                                                                            *
//*  Input:       Fichero 'Entrada.dat'                                        *
//*               elInicial = Numero de elemento inicial                       *
//*               exInicial = Numero de extremo inicial                        *
//*               bContacto = 1 si es superficie de contacto                   *
//*  Output:      elInicial = Numero de elemento final                         *
//*               exInicial = Numero de extremo final                          *
//*  Usage:                                                                    *
//*  Description: Superficie de contacto codificada de 4 extremos              *
//*                                                                            *
//*                                                                            *
//******************************************************************************

void SUPERFICIE_CUATRO(int* punteroA_elInicial,int* punteroA_exInicial,int* punteroA_bContacto)
{
	//* Declaracion de variables


	int elInicial=*punteroA_elInicial,exInicial=*punteroA_exInicial;	//Elemento y extremo inicial
	int bContacto=*punteroA_bContacto;	//Indica si es superficie de contacto
	double  ptA[3],ptB[3],ptC[3],ptD[3];	//Coordenadas extremo superficie
	double  rAB,rAD;	//Razon de la progresion en ambos sentidos
	int  exAB,exAD;	//Numero de extremos menos uno en las direcciones AB y AD
	int  tpEl,fMallado;	//Flag de tipo de elemento y de mallado
	int  elPri, exPri;	//Auxiliares
	int  nexAB,nexAD,nelAB,nelAD;
	int  i;
	double  eta1,eta2,modulo;
	//* Inicializa variables
	exPri=exInicial;
	elPri=elInicial;
	//* Lee valores de la codificacion
	leeEntero(in1,&exAB);leeEntero(in1,&exAD);leeDouble(in1,&rAB);leeDouble(in1,&rAD);leeLinea(in1);
	leeEntero(in1,&tpEl);leeEntero(in1,&fMallado);leeLinea(in1);	//OJO: No se utilizan
	leeDouble(in1,&ptA[1-1]);leeDouble(in1,&ptA[2-1]);leeDouble(in1,&ptA[3-1]);leeLinea(in1);
	leeDouble(in1,&ptB[1-1]);leeDouble(in1,&ptB[2-1]);leeDouble(in1,&ptB[3-1]);leeLinea(in1);
	leeDouble(in1,&ptC[1-1]);leeDouble(in1,&ptC[2-1]);leeDouble(in1,&ptC[3-1]);leeLinea(in1);
	leeDouble(in1,&ptD[1-1]);leeDouble(in1,&ptD[2-1]);leeDouble(in1,&ptD[3-1]);leeLinea(in1);
	//* Calcula los extremos de los elementos
	for( nexAD=0; nexAD<=exAD; nexAD++)      
	{
		if((nexAD == 0) || (rAD == 1.0) )        
		{
			eta2=-1.0+(2.0/exAD)*nexAD;
		}
		else        
		{
			eta2=-1.0+2.0*((pow(rAD,nexAD)-1.0)/(pow(rAD,exAD)-1.0));
		}
		for( nexAB=0; nexAB<=exAB; nexAB++)        
		{
			if((nexAB == 0) || (rAB == 1.0) )          
			{
				eta1=-1.0+(2.0/exAB)*nexAB;
			}
			else          
			{
				eta1=-1.0+2.0*((pow(rAB,nexAB)-1.0)/(pow(rAB,exAB)-1.0));
			}
			for( i=1; i<=3; i++)          
			{
				exB[exInicial-1][i-1]=(ptA[i-1]*(1.0-eta1)*(1.0-eta2)+
				ptB[i-1]*(1.0+eta1)*(1.0-eta2)+
				ptC[i-1]*(1.0+eta1)*(1.0+eta2)+
				ptD[i-1]*(1.0-eta1)*(1.0+eta2))/4.0;;
				if(bContacto == 1) exA[exInicial-1][i-1]=exB[exInicial-1][i-1];
			}
			exInicial=exInicial+1;
		}
	}
	//* Genera la tabla de conectividades y segundo eje del sistema local
	for( nelAD=1; nelAD<=exAD; nelAD++)      
	{
		for( nelAB=1; nelAB<=exAB; nelAB++)        
		{
			if(bContacto == 1)          
			{
				conB[elInicial-1][1-1]=exPri+(nelAD-1)*(exAB+1)+nelAB-1;
				conB[elInicial-1][2-1]=exPri+(nelAD-1)*(exAB+1)+nelAB+exAB;
				conB[elInicial-1][3-1]=exPri+(nelAD-1)*(exAB+1)+nelAB;
				conA[elInicial-1][1-1]=conB[elInicial-1][1-1];
				conA[elInicial-1][2-1]=conB[elInicial-1][3-1];
				conA[elInicial-1][3-1]=conB[elInicial-1][2-1];
				modulo=0.0;
				for( i=1; i<=3; i++)            
				{
					locB[elInicial-1][3+i-1]=exB[conB[elInicial-1][2-1]-1][i-1]-exB[conB[elInicial-1][1-1]-1][i-1];
					modulo=modulo+pow(locB[elInicial-1][3+i-1],2);
				}
				modulo=sqrt(modulo);
				for( i=4; i<=6; i++)            
				{
					locB[elInicial-1][i-1]=locB[elInicial-1][i-1]/modulo;
					locA[elInicial-1][i-1]=locB[elInicial-1][i-1];
				}
				elInicial=elInicial+1;
				conB[elInicial-1][1-1]=exPri+(nelAD-1)*(exAB+1)+nelAB+exAB+1;
				conB[elInicial-1][2-1]=exPri+(nelAD-1)*(exAB+1)+nelAB;
				conB[elInicial-1][3-1]=exPri+(nelAD-1)*(exAB+1)+nelAB+exAB;
				conA[elInicial-1][1-1]=conB[elInicial-1][1-1];
				conA[elInicial-1][2-1]=conB[elInicial-1][3-1];
				conA[elInicial-1][3-1]=conB[elInicial-1][2-1];
				modulo=0.0;
				for( i=1; i<=3; i++)            
				{
					locB[elInicial-1][3+i-1]=exB[conB[elInicial-1][1-1]-1][i-1]-exB[conB[elInicial-1][2-1]-1][i-1];
					modulo=modulo+pow(locB[elInicial-1][3+i-1],2);
				}
				modulo=sqrt(modulo);
				for( i=4; i<=6; i++)            
				{
					locB[elInicial-1][i-1]=locB[elInicial-1][i-1]/modulo;
					locA[elInicial-1][i-1]=locB[elInicial-1][i-1];
				}
				elInicial=elInicial+1;
			}
			else          
			{
				conB[elInicial-1][1-1]=exPri+(nelAD-1)*(exAB+1)+nelAB-1;
				conB[elInicial-1][2-1]=exPri+(nelAD-1)*(exAB+1)+nelAB;
				conB[elInicial-1][3-1]=exPri+(nelAD-1)*(exAB+1)+nelAB+exAB;
				modulo=0.0;
				for( i=1; i<=3; i++)            
				{
					locB[elInicial-1][3+i-1]=exB[conB[elInicial-1][2-1]-1][i-1]-exB[conB[elInicial-1][1-1]-1][i-1];
					modulo=modulo+pow(locB[elInicial-1][3+i-1],2);
				}
				modulo=sqrt(modulo);
				for( i=1; i<=3; i++)            
				{
					locB[elInicial-1][3+i-1]=locB[elInicial-1][3+i-1]/modulo;
				}
				elInicial=elInicial+1;
				conB[elInicial-1][1-1]=exPri+(nelAD-1)*(exAB+1)+nelAB+exAB+1;
				conB[elInicial-1][2-1]=exPri+(nelAD-1)*(exAB+1)+nelAB+exAB;
				conB[elInicial-1][3-1]=exPri+(nelAD-1)*(exAB+1)+nelAB;
				modulo=0.0;
				for( i=1; i<=3; i++)            
				{
					locB[elInicial-1][3+i-1]=exB[conB[elInicial-1][1-1]-1][i-1]-exB[conB[elInicial-1][2-1]-1][i-1];
					modulo=modulo+pow(locB[elInicial-1][3+i-1],2);
				}
				modulo=sqrt(modulo);
				for( i=1; i<=3; i++)            
				{
					locB[elInicial-1][3+i-1]=locB[elInicial-1][3+i-1]/modulo;
				}
				elInicial=elInicial+1;
			}
		}
	}
	*punteroA_elInicial = elInicial; *punteroA_exInicial = exInicial; *punteroA_bContacto = bContacto; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:       Fichero 'Entrada.dat'                                        *
//*  Output:                                                                   *
//*  Usage:                                                                    *
//*  Description: Superficie de contacto codificada de 3 extremos              *
//*                                                                            *
//******************************************************************************

void SUPERFICIE_TRES(int* punteroA_elInicial,int* punteroA_exInicial,int* punteroA_bContacto)
{
	//* Declaracion de variables


	int elInicial=*punteroA_elInicial,exInicial=*punteroA_exInicial;	//Elemento y extremo inicial
	int bContacto=*punteroA_bContacto;	//Indica si es superficie de contacto


	elInicial=0;
	exInicial=0;
	bContacto=0;


	//*       INCOMPLETA


	*punteroA_elInicial = elInicial; *punteroA_exInicial = exInicial; *punteroA_bContacto = bContacto; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:       Fichero 'Entrada.dat'                                        *
//*               ndInicial = Nodo en el que se comienza la asignacion         *
//*               ndFinal = Nodo en el que se finaliza la asignacion           *
//*  Output:                                                                   *
//*  Usage:                                                                    *
//*  Description: Lee los codigos de carga                                     *
//*                                                                            *
//******************************************************************************

void LEE_CODIGOS(int* punteroA_ndInicial,int* punteroA_ndFinal)
{
	//* Declaracion de variables


	int ndInicial=*punteroA_ndInicial,ndFinal=*punteroA_ndFinal;	//Nodos inicial y final
	int  tpCod;	//Auxiliares
	//* Codigos elasticos
	if((tpproE == 1) || (tpproTE == 1))      
	{
		tpCod=1;
		CODIGOS(&ndInicial,& ndFinal,&tpCod);if(enExcepcion==1)return;
	}
	//* Codigos termicos
	if((tpproT == 1) || (tpproTE == 1))      
	{
		tpCod=2;
		CODIGOS(&ndInicial,& ndFinal,&tpCod);if(enExcepcion==1)return;
	}
	*punteroA_ndInicial = ndInicial; *punteroA_ndFinal = ndFinal; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:       Fichero 'Entrada.dat'                                        *
//*               ndInicial = Nodo en el que se comienza la asignacion         *
//*               ndFinal = Nodo en el que se finaliza la asignacion           *
//*  Output:                                                                   *
//*  Usage:                                                                    *
//*  Description: Lee los condiciones de contorno                              *
//*                                                                            *
//******************************************************************************

void LEE_CC(int* punteroA_ndInicial,int* punteroA_ndFinal)
{
	//* Declaracion de variables


	int ndInicial=*punteroA_ndInicial,ndFinal=*punteroA_ndFinal;	//Nodos inicial y final
	int  ndUlt,ndAct,nd,i;	//Auxiliares
	double  dat1, dat2,dat3;
	//* Condiciones de contorno elasticas
	if((tpproE == 1) || (tpproTE == 1))      
	{
		ndAct = ndInicial;
		while(ndAct <= ndFinal)
		{
			leeEntero(in1,&ndUlt);leeDouble(in1,&dat1);leeDouble(in1,&dat2);leeDouble(in1,&dat3);leeLinea(in1);
			if((ndUlt < ndAct) || (ndUlt > ndFinal))          
			{
				printf(" Nodo = %d Dato 1 = %e Dato 2 = %e Dato 3 = %e\n",ndUlt,dat1,dat2,dat3);
				printf("***ERROR*** => ERROR EN CONDICIONES DE CONTORNO\n"); enExcepcion=1;return;
			}
			for( nd=ndAct; nd<=ndUlt; nd++)          
			{
				//* Inicializa valores de las condiciones de contorno
				for( i=1; i<=10; i++)            
				{
					ccB[nd-1][i-1]=0.0;
				}
				//* Asigna las condiciones de contorno
				if(codB[nd-1][1-1] == 1)            
				{
					//* Codigo 1
					ccB[nd-1][1-1]=dat1;
					ccB[nd-1][2-1]=dat2;
					ccB[nd-1][3-1]=dat3;
				}
				else if(codB[nd-1][1-1] == 2)            
				{
					//* Codigo 2
					ccB[nd-1][1-1]=dat1;
					ccB[nd-1][2-1]=dat2;
					ccB[nd-1][6-1]=dat3;
				}
				else if(codB[nd-1][1-1] == 3)            
				{
					//* Codigo 3
					ccB[nd-1][1-1]=dat1;
					ccB[nd-1][5-1]=dat2;
					ccB[nd-1][3-1]=dat3;
				}
				else if(codB[nd-1][1-1] == 4)            
				{
					//* Codigo 4
					ccB[nd-1][1-1]=dat1;
					ccB[nd-1][5-1]=dat2;
					ccB[nd-1][6-1]=dat3;
				}
				else if(codB[nd-1][1-1] == 5)            
				{
					//* Codigo 5
					ccB[nd-1][4-1]=dat1;
					ccB[nd-1][2-1]=dat2;
					ccB[nd-1][3-1]=dat3;
				}
				else if(codB[nd-1][1-1] == 6)            
				{
					//* Codigo 6
					ccB[nd-1][4-1]=dat1;
					ccB[nd-1][2-1]=dat2;
					ccB[nd-1][6-1]=dat3;
				}
				else if(codB[nd-1][1-1] == 7)            
				{
					//* Codigo 7
					ccB[nd-1][4-1]=dat1;
					ccB[nd-1][5-1]=dat2;
					ccB[nd-1][3-1]=dat3;
				}
				else if(codB[nd-1][1-1] == 8)            
				{
					//* Codigo 8
					ccB[nd-1][4-1]=dat1;
					ccB[nd-1][5-1]=dat2;
					ccB[nd-1][6-1]=dat3;
				}
				else            
				{
					printf(" Nodo = %d Codigo = %d\n",nd,codB[nd-1][1-1]);
					printf("***ERROR*** => ERROR EN CONDICIONES DE CONTORNO ELASTICAS\n"); enExcepcion=1;return;
				}
			}
			ndAct=ndUlt+1;
		}
	}
	//* Condiciones de contorno termicas
	if((tpproT == 1) || (tpproTE == 1))      
	{
		ndAct = ndInicial;
		while(ndAct <= ndFinal)
		{
			leeEntero(in1,&ndUlt);leeDouble(in1,&dat1);leeDouble(in1,&dat2);leeLinea(in1);
			if((ndUlt < ndAct) || (ndUlt > ndFinal))          
			{
				printf("%d Dato 1 = %e Dato 2 = %e Dato 3 = %e\n",ndUlt,dat1,dat2,dat3);
				printf("***ERROR*** => ERROR EN CONDICIONES DE CONTORNO\n"); enExcepcion=1;return;
			}
			for( nd=ndAct; nd<=ndUlt; nd++)          
			{
				//* Asigna las condiciones de contorno
				if(codB[nd-1][2-1] == 1)            
				{
					//* Codigo 1
					ccB[nd-1][7-1]=dat1;
				}
				else if(codB[nd-1][2-1] == 2)            
				{
					//* Codigo 2
					ccB[nd-1][8-1]=dat1;
				}
				else if(codB[nd-1][2-1] == 4)            
				{
					//* Codigo 4
					ccB[nd-1][9-1]=dat1;
					ccB[nd-1][10-1]=dat2;
				}
				else            
				{
					printf(" Nodo = %d Codigo = %d\n",nd,codB[nd-1][2-1]);
					printf("***ERROR*** => ERROR EN CONDICIONES DE CONTORNO TERMICAS\n"); enExcepcion=1;return;
				}
			}
			ndAct=ndUlt+1;
		}
	}
	*punteroA_ndInicial = ndInicial; *punteroA_ndFinal = ndFinal; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:                                                                    *
//*  Output:                                                                   *
//*  Usage:                                                                    *
//*  Description: Calcula los nodos en ambos sólidos                           *
//*                                                                            *
//******************************************************************************

void CALCNODOS()
{
	//* Declaracion de variables


	int  i,j,k;	//Auxiliares
	//* Calcula los nodos de "A"
	for( i=1; i<=nelA; i++)      
	{
		for( j=1; j<=3; j++)        
		{
			ndA[i-1][j-1]=0.;
			for( k=1; k<=3; k++)          
			{
				ndA[i-1][j-1]=ndA[i-1][j-1]+exA[conA[i-1][k-1]-1][j-1]/3.;
			}
		}
	}
	//* Calcula los nodos de "B"
	for( i=1; i<=nelB; i++)      
	{
		for( j=1; j<=3; j++)        
		{
			ndB[i-1][j-1]=0.;
			for( k=1; k<=3; k++)          
			{
				ndB[i-1][j-1]=ndB[i-1][j-1]+exB[conB[i-1][k-1]-1][j-1]/3.;
			}
		}
	}
	return;
}
//******************************************************************************
//*                                                                            *
//*  Input:                                                                    *
//*  Output:                                                                   *
//*  Usage:                                                                    *
//*  Description: Calcula el sistema local en ambos sólidos                    *
//*                                                                            *
//******************************************************************************

void SISTLOCAL()
{
	//* Declaracion de variables


	int  i,j;	//Auxiliares
	double  xx[3],yy[3],zz[3],modulo;
	//* Calcula el vector normal de "A" ( Eje 1 )
	for( i=1; i<=nelA; i++)      
	{
		for( j=1; j<=3; j++)        
		{
			xx[j-1]= exA[conA[i-1][j-1]-1][1-1];
			yy[j-1]= exA[conA[i-1][j-1]-1][2-1];
			zz[j-1]= exA[conA[i-1][j-1]-1][3-1];
		}
		locA[i-1][1-1]=(yy[2-1]-yy[1-1])*(zz[3-1]-zz[1-1])-(zz[2-1]-zz[1-1])*(yy[3-1]-yy[1-1]);
		locA[i-1][2-1]=(zz[2-1]-zz[1-1])*(xx[3-1]-xx[1-1])-(xx[2-1]-xx[1-1])*(zz[3-1]-zz[1-1]);
		locA[i-1][3-1]=(xx[2-1]-xx[1-1])*(yy[3-1]-yy[1-1])-(yy[2-1]-yy[1-1])*(xx[3-1]-xx[1-1]);
		modulo=sqrt(pow(locA[i-1][1-1],2)+pow(locA[i-1][2-1],2)+pow(locA[i-1][3-1],2));
		if(modulo != 0.0 )        
		{
			locA[i-1][1-1]=locA[i-1][1-1]/modulo;
			locA[i-1][2-1]=locA[i-1][2-1]/modulo;
			locA[i-1][3-1]=locA[i-1][3-1]/modulo;
		}
		else        
		{
			printf("*** ERROR*** => MODULO NULO EN SISTEMA LOCAL. SOLIDO A\n"); enExcepcion=1;return;
		}
	}
	//* Calcula la tercera direccion local de "A"
	for( i=1; i<=nelA; i++)      
	{
		locA[i-1][7-1]=locA[i-1][2-1]*locA[i-1][6-1]-locA[i-1][3-1]*locA[i-1][5-1];
		locA[i-1][8-1]=locA[i-1][3-1]*locA[i-1][4-1]-locA[i-1][1-1]*locA[i-1][6-1];
		locA[i-1][9-1]=locA[i-1][1-1]*locA[i-1][5-1]-locA[i-1][2-1]*locA[i-1][4-1];
	}
	//* Calcula el vector normal de "B" ( Eje 1 )
	for( i=1; i<=nelB; i++)      
	{
		for( j=1; j<=3; j++)        
		{
			xx[j-1]= exB[conB[i-1][j-1]-1][1-1];
			yy[j-1]= exB[conB[i-1][j-1]-1][2-1];
			zz[j-1]= exB[conB[i-1][j-1]-1][3-1];
		}
		locB[i-1][1-1]=(yy[2-1]-yy[1-1])*(zz[3-1]-zz[1-1])-(zz[2-1]-zz[1-1])*(yy[3-1]-yy[1-1]);
		locB[i-1][2-1]=(zz[2-1]-zz[1-1])*(xx[3-1]-xx[1-1])-(xx[2-1]-xx[1-1])*(zz[3-1]-zz[1-1]);
		locB[i-1][3-1]=(xx[2-1]-xx[1-1])*(yy[3-1]-yy[1-1])-(yy[2-1]-yy[1-1])*(xx[3-1]-xx[1-1]);
		modulo=sqrt(pow(locB[i-1][1-1],2)+pow(locB[i-1][2-1],2)+pow(locB[i-1][3-1],2));
		if(modulo != 0.0 )        
		{
			locB[i-1][1-1]=locB[i-1][1-1]/modulo;
			locB[i-1][2-1]=locB[i-1][2-1]/modulo;
			locB[i-1][3-1]=locB[i-1][3-1]/modulo;
		}
		else        
		{
			printf("*** ERROR*** => MODULO NULO EN SISTEMA LOCAL. SOLIDO B\n"); enExcepcion=1;return;
		}
	}
	//* Calcula la tercera direccion local de "B"
	for( i=1; i<=nelB; i++)      
	{
		locB[i-1][7-1]=locB[i-1][2-1]*locB[i-1][6-1]-locB[i-1][3-1]*locB[i-1][5-1];
		locB[i-1][8-1]=locB[i-1][3-1]*locB[i-1][4-1]-locB[i-1][1-1]*locB[i-1][6-1];
		locB[i-1][9-1]=locB[i-1][1-1]*locB[i-1][5-1]-locB[i-1][2-1]*locB[i-1][4-1];
	}
	return;
}
//******************************************************************************
//*                                                                            *
//*  Input:                                                                    *
//*  Output:                                                                   *
//*  Usage:                                                                    *
//*  Description: Subrutina maestra de integracion                             *
//*                                                                            *
//******************************************************************************
//********************************* NOTA ***************************************
//*    ---  Se integra desde el nodo   "nd"   sobre el elemento   "el"  ---    *
//******************************************************************************

void COEFICIENTES(double** AE_T,double** BE_T,double** AT_T,double** BT_T,double** CTE_T,double** DTE_T)
{
	//* Declaracion de variables


	int  nd,el;	//Auxiliares
	int  i,j,intenum;
	double  extraux;
	double  AE1[3][3],AE2[3][3],AE3[3][3],AE4[3][3],AE5[3][3],AE6[3][3],AE7[3][3];
	double  BE1[3][3],BE2[3][3],BE3[3][3],BE4[3][3],BE5[3][3],BE6[3][3],BE7[3][3];
	double  AT1,AT2,AT3,AT4,AT5,AT6,AT7;
	double  BT1,BT2,BT3,BT4,BT5,BT6,BT7;
	double  C1[3],C2[3],C3[3],C4[3],C5[3],C6[3],C7[3];
	double  D1[3][3],D2[3][3],D3[3][3],D4[3][3],D5[3][3],D6[3][3],D7[3][3];

	/*double AE_T[3*nelT][3*nelT];*	//*double BE_T[3*nelT][3*nelT];*/;
	/*double AT_T[nelT][nelT];*	//*double BT_T[nelT][nelT];*/;
	/*double CTE_T[3*nelT][nelT];*	//*double DTE_T[3*nelT][nelT];*/;

	//* Calcula constantes
	cte1=16.0*4.0*atan(1.0)*GT*(1.0-nuT);
	cte2=1.0-2.0*nuT;
	cte3=8.0*(1.0-nuT)*4.0*atan(1.0);
	cte4=4.0*4.0*atan(1.0);
	cte5=alT*(1.0+nuT)/(8.0*4.0*atan(1.0)*(1.0-nuT));
	//cte1=16.D0*3.141592654D0*GT*(1.D0-nuT)
	//cte3=8.D0*(1.D0-nuT)*3.141592654D0
	//cte4=4.D0*3.141592654D0
	//cte5=alT*(1.D0+nuT)/(8.D0*3.141592654D0*(1.D0-nuT))


	//* Caso en que no haya simetria implicita ++++++++++++++++++++++++++++++++++++++++++++++++
	if((simXY != 1) && (simXZ != 1) && (simYZ != 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;

				if((tpproE == 1) || (tpproTE == 1))                        
				{
					//* Cambia de coordenadas los coeficientes elasticos
					TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif
				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
		//* Caso en que haya simetria respecto del plano OXY ++++++++++++++++++++++++++++++++++++++++
	}
	else if((simXY == 1) && (simXZ != 1) && (simYZ != 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;

				//* Integra SIMÉTRICO OXY

				//* Asigna extremos
				for( i=1; i<=3; i++)                         
				{
					for( j=1; j<=3; j++)                            
					{
						if(j == 3)                                
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                                
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				//* Asigna tipo de integral
				intenum=1;
				INTEGRA(&intenum,AE1,BE1,&AT1,&BT1,C1,D1);if(enExcepcion==1)return;

				//* Combina coeficientes
				//* Elásticos
				if((tpproE == 1) || (tpproTE == 1))                        
				{
					for( i=1; i<=3; i++)                           
					{
						for( j=1; j<=3; j++)                              
						{
							if(j == 3)                                 
							{
								AE[i-1][j-1]=AE[i-1][j-1]-AE1[i-1][j-1];
								BE[i-1][j-1]=BE[i-1][j-1]-BE1[i-1][j-1];
							}
							else                                 
							{
								AE[i-1][j-1]=AE[i-1][j-1]+AE1[i-1][j-1];
								BE[i-1][j-1]=BE[i-1][j-1]+BE1[i-1][j-1];
							}
						}
					}
					//* Térmoelásticos
					if(tpproTE == 1)                           
					{
						for( i=1; i<=3; i++)                               
						{
							CTE[i-1]=CTE[i-1]+C1[i-1];
							for( j=1; j<=3; j++)                                  
							{
								if(j == 3)                                     
								{
									DTE[i-1][j-1]=DTE[i-1][j-1]-D1[i-1][j-1];
								}
								else                                     
								{
									DTE[i-1][j-1]=DTE[i-1][j-1]+D1[i-1][j-1];
								}
							}
						}
					}
					//* Cambia de coordenadas los coeficientes elasticos y termoelásticos
					TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;
				}
				//* Térmicos
				if((tpproT == 1) || (tpproTE == 1))                        
				{
					AT=AT+AT1;
					BT=BT+BT1;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif
				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
		//* Caso de que haya simetria respecto del plano OXZ ++++++++++++++++++++++++++++++++++++++++
	}
	else if((simXY != 1) && (simXZ == 1) && (simYZ != 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;

				//* Integra simetrico Oxz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 2)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				//* Asigna tipo de integral
				intenum=1;
				INTEGRA(&intenum,AE1,BE1,&AT1,&BT1,C1,D1);if(enExcepcion==1)return;

				//* Elásticos
				//* Combina coeficientes
				if((tpproE == 1) || (tpproTE == 1))                        
				{
					for( i=1; i<=3; i++)                           
					{
						for( j=1; j<=3; j++)                              
						{
							if(j == 2)                                 
							{
								AE[i-1][j-1]=AE[i-1][j-1]-AE1[i-1][j-1];
								BE[i-1][j-1]=BE[i-1][j-1]-BE1[i-1][j-1];
							}
							else                                 
							{
								AE[i-1][j-1]=AE[i-1][j-1]+AE1[i-1][j-1];
								BE[i-1][j-1]=BE[i-1][j-1]+BE1[i-1][j-1];
							}
						}
					}
					//* Térmoelásticos
					if(tpproTE == 1)                           
					{
						for( i=1; i<=3; i++)                              
						{
							CTE[i-1]=CTE[i-1]+C1[i-1];
							for( j=1; j<=3; j++)                                 
							{
								if(j == 2)                                    
								{
									DTE[i-1][j-1]=DTE[i-1][j-1]-D1[i-1][j-1];
								}
								else                                    
								{
									DTE[i-1][j-1]=DTE[i-1][j-1]+D1[i-1][j-1];
								}
							}
						}
					}
					//* Cambia de coordenadas los coeficientes elasticos
					TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;
				}
				//* Térmicos
				if((tpproT == 1) || (tpproTE == 1))                        
				{
					AT=AT+AT1;
					BT=BT+BT1;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif
				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
		//* Caso de que haya simetria respecto del plano OYZ ++++++++++++++++++++++++++++++++++++++++
	}
	else if((simXY != 1) && (simXZ != 1) && (simYZ == 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;

				//* Integra simetrico Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 1)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				intenum=1;
				INTEGRA(&intenum,AE1,BE1,&AT1,&BT1,C1,D1);if(enExcepcion==1)return;

				//* Elasticos
				//* Combina coeficientes
				if((tpproE == 1) || (tpproTE == 1))                        
				{
					for( i=1; i<=3; i++)                           
					{
						for( j=1; j<=3; j++)                              
						{
							if(j == 1)                                 
							{
								AE[i-1][j-1]=AE[i-1][j-1]-AE1[i-1][j-1];
								BE[i-1][j-1]=BE[i-1][j-1]-BE1[i-1][j-1];
							}
							else                                 
							{
								AE[i-1][j-1]=AE[i-1][j-1]+AE1[i-1][j-1];
								BE[i-1][j-1]=BE[i-1][j-1]+BE1[i-1][j-1];
							}
						}
					}
				}
				//* Térmoelásticos
				if(tpproTE == 1)                        
				{
					for( i=1; i<=3; i++)                           
					{
						CTE[i-1]=CTE[i-1]+C1[i-1];
						for( j=1; j<=3; j++)                              
						{
							if(j == 1)                                 
							{
								DTE[i-1][j-1]=DTE[i-1][j-1]-D1[i-1][j-1];
							}
							else                                 
							{
								DTE[i-1][j-1]=DTE[i-1][j-1]+D1[i-1][j-1];
							}
						}
					}
				}
				//* Cambia de coordenadas los coeficientes elasticos
				TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;

				//* Térmicos
				if((tpproT == 1) || (tpproTE == 1))                        
				{
					AT=AT+AT1;
					BT=BT+BT1;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif
				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
		//* Caso de simetria respecto de los planos OXY y OXZ ++++++++++++++++++++++++++++++++++++++++
	}
	else if((simXY == 1) && (simXZ == 1) && (simYZ != 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;

				//* Integra simetrico Oxy

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 3)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				//* Asigna tipo de integral
				intenum=1;
				INTEGRA(&intenum,AE1,BE1,&AT1,&BT1,C1,D1);if(enExcepcion==1)return;

				//* Integra simetrico Oxy y Oxz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 1)                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				INTEGRA(&intenum,AE2,BE2,&AT2,&BT2,C2,D2);if(enExcepcion==1)return;

				//* Integra simetrico Oxz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 2)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				INTEGRA(&intenum,AE3,BE3,&AT3,&BT3,C3,D3);if(enExcepcion==1)return;

				//* Elasticos
				//* Combina coeficientes
				if((tpproE == 1) || (tpproTE == 1))                        
				{
					for( i=1; i<=3; i++)                           
					{
						AE[i-1][1-1]=AE[i-1][1-1]+AE1[i-1][1-1]+AE2[i-1][1-1]+AE3[i-1][1-1];
						AE[i-1][2-1]=AE[i-1][2-1]+AE1[i-1][2-1]-AE2[i-1][2-1]-AE3[i-1][2-1];
						AE[i-1][3-1]=AE[i-1][3-1]-AE1[i-1][3-1]-AE2[i-1][3-1]+AE3[i-1][3-1];
						BE[i-1][1-1]=BE[i-1][1-1]+BE1[i-1][1-1]+BE2[i-1][1-1]+BE3[i-1][1-1];
						BE[i-1][2-1]=BE[i-1][2-1]+BE1[i-1][2-1]-BE2[i-1][2-1]-BE3[i-1][2-1];
						BE[i-1][3-1]=BE[i-1][3-1]-BE1[i-1][3-1]-BE2[i-1][3-1]+BE3[i-1][3-1];
					}
				}
				//* Térmoelásticos
				if(tpproTE == 1)                        
				{
					for( i=1; i<=3; i++)                           
					{
						DTE[i-1][1-1]=DTE[i-1][1-1]+D1[i-1][1-1]+D2[i-1][1-1]+D3[i-1][1-1];
						DTE[i-1][2-1]=DTE[i-1][2-1]+D1[i-1][2-1]-D2[i-1][2-1]-D3[i-1][2-1];
						DTE[i-1][3-1]=DTE[i-1][3-1]-D1[i-1][3-1]-D2[i-1][3-1]+D3[i-1][3-1];
					}
				}
				//* Cambia de coordenadas los coeficientes elasticos
				TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;
				//* Térmicos
				if((tpproT == 1) || (tpproTE == 1))                        
				{
					AT=AT+AT1+AT2+AT3;
					BT=BT+BT1+BT2+BT3;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif
				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
		//* Caso de simetria respecto de los planos OXY y OYZ ++++++++++++++++++++++++++++++++++++++++
	}
	else if((simXY == 1) && (simXZ != 1) && (simYZ == 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;

				//* Integra simetrico Oxy

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 3)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				//* Asigna tipo de integral
				intenum=1;
				INTEGRA(&intenum,AE1,BE1,&AT1,&BT1,C1,D1);if(enExcepcion==1)return;

				//* Integra simetrico Oxy y Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 2)                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				INTEGRA(&intenum,AE2,BE2,&AT2,&BT2,C2,D2);if(enExcepcion==1)return;

				//* Integra simetrico Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 1)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				INTEGRA(&intenum,AE3,BE3,&AT3,&BT3,C3,D3);if(enExcepcion==1)return;

				//* Elasticos
				//* Combina coeficientes
				if((tpproE == 1) || (tpproTE == 1))                        
				{
					for( i=1; i<=3; i++)                           
					{
						AE[i-1][1-1]=AE[i-1][1-1]+AE1[i-1][1-1]-AE2[i-1][1-1]-AE3[i-1][1-1];
						AE[i-1][2-1]=AE[i-1][2-1]+AE1[i-1][2-1]+AE2[i-1][2-1]+AE3[i-1][2-1];
						AE[i-1][3-1]=AE[i-1][3-1]-AE1[i-1][3-1]-AE2[i-1][3-1]+AE3[i-1][3-1];
						BE[i-1][1-1]=BE[i-1][1-1]+BE1[i-1][1-1]-BE2[i-1][1-1]-BE3[i-1][1-1];
						BE[i-1][2-1]=BE[i-1][2-1]+BE1[i-1][2-1]+BE2[i-1][2-1]+BE3[i-1][2-1];
						BE[i-1][3-1]=BE[i-1][3-1]-BE1[i-1][3-1]-BE2[i-1][3-1]+BE3[i-1][3-1];
					}
				}
				//* Térmoelásticos
				if(tpproTE == 1)                        
				{
					CTE[1-1]=CTE[1-1]+C1[1-1]+C2[1-1]+C3[1-1];
					CTE[2-1]=CTE[2-1]+C1[2-1]+C2[2-1]+C3[2-1];
					CTE[3-1]=CTE[3-1]+C1[3-1]+C2[3-1]+C3[3-1];
					for( i=1; i<=3; i++)                           
					{
						DTE[i-1][1-1]=DTE[i-1][1-1]+D1[i-1][1-1]-D2[i-1][1-1]-D3[i-1][1-1];
						DTE[i-1][2-1]=DTE[i-1][2-1]+D1[i-1][2-1]+D2[i-1][2-1]+D3[i-1][2-1];
						DTE[i-1][3-1]=DTE[i-1][3-1]-D1[i-1][3-1]-D2[i-1][3-1]+D3[i-1][3-1];
					}
				}
				//* Cambia de coordenadas los coeficientes elasticos
				TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;
				//* Térmicos
				if((tpproT == 1) || (tpproTE == 1))                        
				{
					AT=AT+AT1+AT2+AT3;
					BT=BT+BT1+BT2+BT3;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif
				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
		//* Caso de simetria respecto de los planos OXZ y OYZ ++++++++++++++++++++++++++++++++++++++++
	}
	else if((simXY != 1) && (simXZ == 1) && (simYZ == 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;
				//if ((nd.eq.1).and.(el.eq.129))then
				//write(out11,*) 'AE',AE(1,1),AE(1,2),AE(1,3),AE(2,1),AE(2,2),AE(2,3),AE(3,1),AE(3,2),AE(3,3)
				//endif


				//* Integra simetrico Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 1)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				//* Asigna tipo de integral
				intenum=1;
				INTEGRA(&intenum,AE1,BE1,&AT1,&BT1,C1,D1);if(enExcepcion==1)return;
				//if ((nd.eq.1).and.(el.eq.129))then
				//write(out11,*) 'AE1',AE1(1,1),AE1(1,2),AE1(1,3),AE1(2,1),AE1(2,2),AE1(2,3),AE1(3,1),AE1(3,2),AE1(3,3)
				//endif


				//* Integra simetrico Oxz y Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 3)                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				INTEGRA(&intenum,AE2,BE2,&AT2,&BT2,C2,D2);if(enExcepcion==1)return;
				//if ((nd.eq.1).and.(el.eq.129))then
				//write(out11,*) 'AE2',AE2(1,1),AE2(1,2),AE2(1,3),AE2(2,1),AE2(2,2),AE2(2,3),AE2(3,1),AE2(3,2),AE2(3,3)
				//endif


				//* Integra simetrico Oxz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 2)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				INTEGRA(&intenum,AE3,BE3,&AT3,&BT3,C3,D3);if(enExcepcion==1)return;
				//if ((nd.eq.1).and.(el.eq.129))then
				//write(out11,*) 'AE3',AE3(1,1),AE3(1,2),AE3(1,3),AE3(2,1),AE3(2,2),AE3(2,3),AE3(3,1),AE3(3,2),AE3(3,3)
				//endif


				//* Elasticos
				//* Combina coeficientes
				if((tpproE == 1) || (tpproTE == 1))                        
				{
					for( i=1; i<=3; i++)                           
					{
						AE[i-1][1-1]=AE[i-1][1-1]-AE1[i-1][1-1]-AE2[i-1][1-1]+AE3[i-1][1-1];
						AE[i-1][2-1]=AE[i-1][2-1]+AE1[i-1][2-1]-AE2[i-1][2-1]-AE3[i-1][2-1];
						AE[i-1][3-1]=AE[i-1][3-1]+AE1[i-1][3-1]+AE2[i-1][3-1]+AE3[i-1][3-1];
						BE[i-1][1-1]=BE[i-1][1-1]-BE1[i-1][1-1]-BE2[i-1][1-1]+BE3[i-1][1-1];
						BE[i-1][2-1]=BE[i-1][2-1]+BE1[i-1][2-1]-BE2[i-1][2-1]-BE3[i-1][2-1];
						BE[i-1][3-1]=BE[i-1][3-1]+BE1[i-1][3-1]+BE2[i-1][3-1]+BE3[i-1][3-1];
					}
				}
				//* Térmoelásticos
				if(tpproTE == 1)                        
				{
					CTE[1-1]=CTE[1-1]+C1[1-1]+C2[1-1]+C3[1-1];
					CTE[2-1]=CTE[2-1]+C1[2-1]+C2[2-1]+C3[2-1];
					CTE[3-1]=CTE[3-1]+C1[3-1]+C2[3-1]+C3[3-1];
					for( i=1; i<=3; i++)                           
					{
						DTE[i-1][1-1]=DTE[i-1][1-1]-D1[i-1][1-1]-D2[i-1][1-1]+D3[i-1][1-1];
						DTE[i-1][2-1]=DTE[i-1][2-1]+D1[i-1][2-1]-D2[i-1][2-1]-D3[i-1][2-1];
						DTE[i-1][3-1]=DTE[i-1][3-1]+D1[i-1][3-1]+D2[i-1][3-1]+D3[i-1][3-1];
					}
				}
				//if ((nd.eq.1).and.(el.eq.129))then
				//write(out11,*) 'combina',AE(1,1),AE(1,2),AE(1,3),AE(2,1),AE(2,2),AE(2,3),AE(3,1),AE(3,2),AE(3,3)
				//endif
				//* Cambia de coordenadas los coeficientes elasticos
				TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;

				//if ((nd.eq.1).and.(el.eq.129))then
				//write(out11,*) 'transforma',AE(1,1),AE(1,2),AE(1,3),AE(2,1),AE(2,2),AE(2,3),AE(3,1),AE(3,2),AE(3,3)
				//endif
				//* Termicos
				if((tpproT == 1) || (tpproTE == 1))                        
				{
					AT=AT+AT1+AT2+AT3;
					BT=BT+BT1+BT2+BT3;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				if(nd == 1)					
				{
					printf("Elemento:%7d%7d\n",nd,el);
				}
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif

				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
		//* Caso en que haya simetria respecto de los tres planos coordenados ++++++++++++++++++++++++++++++++
	}
	else if((simXY == 1) && (simXZ == 1) && (simYZ == 1))                
	{
		//* Para todos los elementos COMIENZA EL PRIMER ELEMENTO (SOBRE EL QUE SE INTEGRA)
		for( el=1; el<=nelT; el++)	      	
		{
			//* Para todos los nodos COMIENZA EL PRIMER NODO (DESDE EL QUE SE INTEGRA)
			for( nd=1; nd<=nelT; nd++)	           
			{
				//* Asigna punto de colocacion
				for( i=1; i<=3; i++)	                
				{
					ndCol[i-1]=ndT[nd-1][i-1];
				}
				//* Asigna tipo de integral
				if(el == nd)	                
				{
					intenum = 0;
				}
				else	                
				{
					intenum = 1;
				}
				//* Integra NORMAL

				//* Asigna extremos
				for( i=1; i<=3; i++)	                
				{
					for( j=1; j<=3; j++)	                   
					{
						extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
					}
				}
				INTEGRA(&intenum,AE,BE,&AT,&BT,CTE,DTE);if(enExcepcion==1)return;

				//* Integra simetrico Oxy

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 3)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				//* Asigna tipo de integral
				intenum = 1;
				INTEGRA(&intenum,AE1,BE1,&AT1,&BT1,C1,D1);if(enExcepcion==1)return;

				//* Integra simetrico Oxy y Oxz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 1)                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				INTEGRA(&intenum,AE2,BE2,&AT2,&BT2,C2,D2);if(enExcepcion==1)return;

				//* Integra simetrico Oxy,Oxz y Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				INTEGRA(&intenum,AE3,BE3,&AT3,&BT3,C3,D3);if(enExcepcion==1)return;

				//* Integra simetrico Oxz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 2)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				INTEGRA(&intenum,AE4,BE4,&AT4,&BT4,C4,D4);if(enExcepcion==1)return;

				//* Integra simetrico Oxz y Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 3)                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				INTEGRA(&intenum,AE5,BE5,&AT5,&BT5,C5,D5);if(enExcepcion==1)return;

				//* Integra simetrico Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 1)                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				//* Intercambia extremos 2 y 3
				for( i=1; i<=3; i++)                        
				{
					extraux=extr[2-1][i-1];
					extr[2-1][i-1]=extr[3-1][i-1];
					extr[3-1][i-1]=extraux;
				}
				INTEGRA(&intenum,AE6,BE6,&AT6,&BT6,C6,D6);if(enExcepcion==1)return;

				//* Integra simetrico Oxy y Oyz

				//* Asigna extremos
				for( i=1; i<=3; i++)                        
				{
					for( j=1; j<=3; j++)                           
					{
						if(j == 2)                              
						{
							extr[i-1][j-1]=exT[conT[el-1][i-1]-1][j-1];
						}
						else                              
						{
							extr[i-1][j-1]=-exT[conT[el-1][i-1]-1][j-1];
						}
					}
				}
				INTEGRA(&intenum,AE7,BE7,&AT7,&BT7,C7,D7);if(enExcepcion==1)return;

				//* Elasticos
				//* Combina coeficientes
				if((tpproE == 1) || (tpproTE == 1))                        
				{
					for( i=1; i<=3; i++)                           
					{
						AE[i-1][1-1]=AE[i-1][1-1]+AE1[i-1][1-1]+AE2[i-1][1-1]-AE3[i-1][1-1]+AE4[i-1][1-1]-AE5[i-1][1-1]-AE6[i-1][1-1]-AE7[i-1][1-1];
						AE[i-1][2-1]=AE[i-1][2-1]+AE1[i-1][2-1]-AE2[i-1][2-1]-AE3[i-1][2-1]-AE4[i-1][2-1]-AE5[i-1][2-1]+AE6[i-1][2-1]+AE7[i-1][2-1];
						AE[i-1][3-1]=AE[i-1][3-1]-AE1[i-1][3-1]-AE2[i-1][3-1]-AE3[i-1][3-1]+AE4[i-1][3-1]+AE5[i-1][3-1]+AE6[i-1][3-1]-AE7[i-1][3-1];
						BE[i-1][1-1]=BE[i-1][1-1]+BE1[i-1][1-1]+BE2[i-1][1-1]-BE3[i-1][1-1]+BE4[i-1][1-1]-BE5[i-1][1-1]-BE6[i-1][1-1]-BE7[i-1][1-1];
						BE[i-1][2-1]=BE[i-1][2-1]+BE1[i-1][2-1]-BE2[i-1][2-1]-BE3[i-1][2-1]-BE4[i-1][2-1]-BE5[i-1][2-1]+BE6[i-1][2-1]+BE7[i-1][2-1];
						BE[i-1][3-1]=BE[i-1][3-1]-BE1[i-1][3-1]-BE2[i-1][3-1]-BE3[i-1][3-1]+BE4[i-1][3-1]+BE5[i-1][3-1]+BE6[i-1][3-1]-BE7[i-1][3-1];
					}
				}
				//* Térmoelásticos
				if(tpproTE == 1)                        
				{
					CTE[1-1]=CTE[1-1]+C1[1-1]+C2[1-1]+C3[1-1]+C4[1-1]+C5[1-1]+C6[1-1]+C7[1-1];
					CTE[2-1]=CTE[2-1]+C1[2-1]+C2[2-1]+C3[2-1]+C4[2-1]+C5[2-1]+C6[2-1]+C7[2-1];
					CTE[3-1]=CTE[3-1]+C1[3-1]+C2[3-1]+C3[3-1]+C4[3-1]+C5[3-1]+C6[3-1]+C7[3-1];
					for( i=1; i<=3; i++)                           
					{
						DTE[i-1][1-1]=DTE[i-1][1-1]+D1[i-1][1-1]+D2[i-1][1-1]-D3[i-1][1-1]+D4[i-1][1-1]-D5[i-1][1-1]-D6[i-1][1-1]-D7[i-1][1-1];
						DTE[i-1][2-1]=DTE[i-1][2-1]+D1[i-1][2-1]-D2[i-1][2-1]-D3[i-1][2-1]-D4[i-1][1-1]-D5[i-1][1-1]+D6[i-1][1-1]+D7[i-1][1-1];
						DTE[i-1][3-1]=DTE[i-1][3-1]-D1[i-1][3-1]-D2[i-1][3-1]-D3[i-1][3-1]+D4[i-1][1-1]+D5[i-1][1-1]+D6[i-1][1-1]-D7[i-1][1-1];
					}
				}
				//* Cambia de coordenadas los coeficientes elasticos
				TRANSFORMA(AE,BE,&el);if(enExcepcion==1)return;
				//* Termicos
				if((tpproT == 1) || (tpproTE == 1))                        
				{
					AT=AT+AT1+AT2+AT3+AT4+AT5+AT6+AT7;
					BT=BT+BT1+BT2+BT3+BT4+BT5+BT6+BT7;
				}
				//* Almacena coeficientes
				reg=(el-1)*nelT+nd;
				//if((tpproE.eq.1).or.(tpproTE.eq.1))then
				//write(out11,*)'Elemento:',nd,el
				//write(out12,*)'Elemento:',nd,el
				//endif
				//if((tpproT.eq.1).or.(tpproTE.eq.1))then
				//write(out13,*)'Elemento:',nd,el
				//write(out14,*)'Elemento:',nd,el
				//endif
				//if(tpproTE.eq.1)then
				//write(out15,*)'Elemento:',nd,el
				//write(out16,*)'Elemento:',nd,el
				//endif

				ALMACENA(&el,&nd,AE_T,BE_T,AT_T,BT_T,CTE_T,DTE_T);if(enExcepcion==1)return;
			}
		}
	}
	else                
	{
		//* No hay mas casos de simetria
		printf(" **** ERROR **** => Simetrias erroneas\n"); enExcepcion=1;return;
	}
	return;
}
//******************************************************************************
//*                                                                            *
//*  Input:  ?                                                                 *
//*  Output: coeficientes del sistema ax=b                                     *
//*  Usage:                                                                    *
//*  Description: Monta el sistema de ecuaciones lineales en funcion de codigos*
//*               1= temperatura conocida; 2= flujo conocido;3= contacto       *
//******************************************************************************

void MONTAJETER()
{
	//* DEFINICION DE VARIABLES


	int i,j;	//auxiliar
	//* Inicializa los valores de los coeficientes
	for( i=1; i<= nelT; i++)    
	{
		b[i-1]=0.0;
		for( j=1; j<=nelT; j++)      
		{
			a[i-1][j-1]=0.0;
		}
	}
	//* CUERPO A

	nel=nelA;
	for( i=1; i<=nel; i++)    
	{
		codT[i-1]=codA[i-1][2-1];
		temp[i-1]=ccA[i-1][7-1];
		fluj[i-1]=ccA[i-1][8-1];
		tf[i-1]=ccA[i-1][9-1];
		hf[i-1]=ccA[i-1][10-1];

	}
	//* Abre ficheros
	//open(unit=in1s,file='coe_AT_A.dat',status='unknown',access='direct',form='unformatted',recl=72)
	//open(unit=in2s,file='coe_BT_A.dat',status='unknown',access='direct',form='unformatted',recl=72)

	//* lee coeficientes de la ecuacion
	for( i=1; i<=nel; i++)    
	{
		for( j=1; j<=nel; j++)      
		{
			//reg=(j-1)*nel+i
			//read(unit=in1s,rec=reg)AT
			//read(unit=in2s,rec=reg)BT
			AT = AT_A[j-1][i-1];
			BT = BT_A[j-1][i-1];
			if(codT[j-1] == 1)        
			{
				b[i-1]=b[i-1]-AT*temp[j-1];
				a[i-1][j-1]=-BT;
			}
			if(codT[j-1] == 2)        
			{
				b[i-1]=b[i-1]+BT*fluj[j-1];
				a[i-1][j-1]=AT;
			}
			if(codT[j-1] == 4)        
			{
				b[i-1]=b[i-1]+BT*hf[j-1]/lamA*tf[j-1];
				a[i-1][j-1]=AT+BT*hf[j-1]/lamA;
			}
			if((codT[j-1] == 3) || (codT[j-1] == 5))        
			{
				a[i-1][j-1]=AT;
				a[i-1][j+nelA-1]=lamB/lamA*BT;
			}
		}
	}
	//close(unit=in1s)
	//close(unit=in2s)

	//* CUERPO B

	nel=nelB;
	for( i=1; i<=nel; i++)    
	{
		codT[i-1]=codB[i-1][2-1];
		temp[i-1]=ccB[i-1][7-1];
		fluj[i-1]=ccB[i-1][8-1];
		tf[i-1]=ccB[i-1][9-1];
		hf[i-1]=ccB[i-1][10-1];

	}
	//* Abre ficheros
	//open(unit=in3s,file='coe_AT_B.dat',status='unknown',access='direct',form='unformatted',recl=72)
	//open(unit=in4s,file='coe_BT_B.dat',status='unknown',access='direct',form='unformatted',recl=72)

	//* lee coeficientes de la ecuacion
	for( i=1; i<=nel; i++)    
	{
		for( j=1; j<=nel; j++)      
		{
			//reg=(j-1)*nel+i
			//read(unit=in3s,rec=reg)AT
			//read(unit=in4s,rec=reg)BT
			AT = AT_B[j-1][i-1];
			BT = BT_B[j-1][i-1];

			if(codT[j-1] == 1)        
			{
				b[i+nelA-1]=b[i+nelA-1]-AT*temp[j-1];
				a[i+nelA-1][j+nelA-1]=-BT;
			}
			if(codT[j-1] == 2)        
			{
				b[i+nelA-1]=b[i+nelA-1]+BT*fluj[j-1];
				a[i+nelA-1][j+nelA-1]=AT;
			}
			if(codT[j-1] == 4)        
			{
				b[i+nelA-1]=b[i+nelA-1]+BT*hf[j-1]/lamB*tf[j-1];
				a[i+nelA-1][j+nelA-1]=AT+BT*hf[j-1]/lamB;
			}
			if((codT[j-1] == 3) || (codT[j-1] == 5))        
			{
				//* Este termino incluye el contacto imperfecto y la resistencia debida a un material intermedio
				a[i+nelA-1][j-1]=AT;
				a[i+nelA-1][j+nelA-1]=-BT-lamB*RTC[j-1]*AT;
			}
		}
	}
	//close(unit=in3s)
	//close(unit=in4s)

	return;
}
//******************************************************************************
//*                                                                            *
//*  Input:                                                                    *
//*  Output: variables                                                         *
//*  Usage:                                                                    *
//*  Description:  algoritmo de resolucion de un sistema de                    *
//*            ecuaciones por el metodo de GAUSS                               *
//*                                                                            *
//******************************************************************************
void GAUSS_SOLU()
{
	int i,j,k,np;
	double maxi,piv;	//ALMACENAMIENTO TEMPORAL

	out20 = 20;

	//open(unit=out20,file='A.dat')
	//do i=1,nT
	//do j=1,nT
	//write(out20,*)i,j,a(i,j)
	//enddo
	//enddo
	//close(unit=out20)

	//open(unit=out20,file='B.dat')
	//do i=1,nT
	//write(out20,*)i,b(i)
	//enddo
	//close(unit=out20)

	//MATRIZ AMPLIADA
	for( i=1; i<=nT; i++)        
	{
		a[i-1][nT+1-1]=b[i-1];
	}
	//inicializamos variables
	for( i=1; i<=nT; i++)        
	{
		x[i-1]=0.0;
	}
	//busqueda del pivote
	for( i=1; i<=nT-1; i++)        
	{
		piv=0.0;
		for( j=i; j<=nT; j++)            
		{
			if(fabs(a[j-1][i-1]) > piv)                
			{
				piv=fabs(a[j-1][i-1]);
				np=j;
			}
		}
		//chequeo matriz singular
		if(piv == 0.0 )            
		{
			printf("######### matriz singular #########\n");
			printf("\n"); enExcepcion=1;return;
		}
		//intercambio de filas
		for( j=i; j<=nT+1; j++)            
		{
			maxi=a[np-1][j-1];
			a[np-1][j-1]=a[i-1][j-1];
			a[i-1][j-1]=maxi;
		}
		for( j=i+1; j<=nT; j++)            
		{
			for( k=i+1; k<=nT+1; k++)                
			{
				a[j-1][k-1]=a[j-1][k-1]-a[i-1][k-1]*a[j-1][i-1]/a[i-1][i-1];
			}
		}
	}
	printf(" COMIENZA PROCESO DE SOLUCION\n");

	//resolucion hacia atras
	for( i=nT; i>=1; i+=-1)        
	{
		maxi=0.0;
		if(i != nT)            
		{
			for( j=i; j<=nT; j++)                
			{
				maxi=maxi+a[i-1][j-1]*x[j-1];
			}
		}
		x[i-1]=(a[i-1][nT+1-1]-maxi)/a[i-1][i-1];

	}
	//open(unit=out20,file='gauss.dat')
	//do i=1,nT
	//write(out20,*)i,x(i)
	//enddo
	//close(unit=out20)

	printf("fin gaussssssssss\n");

	return;
}
//******************************************************************************
//*                                                                            *
//*  Input:  ?                                                                 *
//*  Output: RESULTADOS TERMICOS EN EL CONTORNO DE LOS DOS CUERPOS             *
//*  Usage:                                                                    *
//*  Description: Ordena e interpreta el vector que contiene las variables     *
//*              termicas e impone las condiciones de contorno en la zona      *
//*            de contacto.                                                    *
//******************************************************************************


void CONTORNOTER()
{
	//* variables utilizadas


	int i;
	//* CUERPO A
	for( i=1; i<=nelA; i++)    
	{
		codT[i-1]=codA[i-1][2-1];
		tempA[i-1]=ccA[i-1][7-1];
		flujA[i-1]=ccA[i-1][8-1];
		tf[i-1]=ccA[i-1][9-1];
		hf[i-1]=ccA[i-1][10-1];

	}
	for( i=1; i<= nelA; i++)    
	{
		if(codT[i-1] == 1)      
		{
			flujA[i-1]=x[i-1];
		}
		if(codT[i-1] == 2)      
		{
			tempA[i-1]=x[i-1];
		}
		if(codT[i-1] == 4)      
		{
			tempA[i-1]=x[i-1];
			flujA[i-1]=-hf[i-1]/lamA*(x[i-1]-tf[i-1]);
		}
		if((codT[i-1] == 3) || (codT[i-1] == 5))      
		{
			tempA[i-1]=x[i-1];
			flujA[i-1]=-lamB/lamA*x[i+nelA-1];
		}
	}
	//* CUERPO B
	for( i=1; i<=nelB; i++)    
	{
		codT[i-1]=codB[i-1][2-1];
		tempB[i-1]=ccB[i-1][7-1];
		flujB[i-1]=ccB[i-1][8-1];
		tf[i-1]=ccB[i-1][9-1];
		hf[i-1]=ccB[i-1][10-1];
	}
	for( i=1; i<=nelB; i++)    
	{
		if(codT[i-1] == 1)      
		{
			flujB[i-1]=x[i+nelA-1];

		}
		if(codT[i-1] == 2)      
		{
			tempB[i-1]=x[i+nelA-1];
		}
		if(codT[i-1] == 4)      
		{
			tempB[i-1]=x[i+nelA-1];
			flujB[i-1]=-hf[i-1]/lamB*(x[i+nelA-1]-tf[i-1]);
		}
		//* Con resistencia termica
		if((codT[i-1] == 3) || (codT[i-1] == 5))      
		{
			tempB[i-1]=x[i-1]-lamB*RTC[i-1]*x[i+nelA-1];
			flujB[i-1]=x[i+nelA-1];
		}
	}
	return;
}
//**********************************************************************

void SALIDATER()
{
	//* Declaracion de variables


	int i;

	//* abre ficheros de salida
	out2s = fopen(nomArchSalTer, "w");

	fprintf(out2s," %s",titulo);	// Formato: 5
	fprintf(out2s," Resultados problema térmico de contacto\n");	// Formato: 10
	fprintf(out2s," \n");	// Formato: 20
	fprintf(out2s," VECTOR DE CARGA TÉRMICA: TEMPERATURAS Y GRADIENTES TÉRMICOS\n");	// Formato: 30
	fprintf(out2s," \n");	// Formato: 20

	//* CUERPO A

	fprintf(out2s," ==================== CUERPO A ====================\n");	// Formato: 35
	fprintf(out2s,"  - Zona de contacto -\n");	// Formato: 40


	//*  Zona de contacto de A
	//write(out2s,50)
	for( i=1; i<=nelpc; i++)    
	{
		fprintf(out2s," %4d %12.4f %12.4f\n",i,tempA[i-1],flujA[i-1]);		// Formato: 100
	}
	//*  Zona libre de A
	fprintf(out2s,"  - Zona libre -\n");	// Formato: 60
	//write(out2s,50)
	for( i=nelpc+1; i<=nelA; i++)    
	{
		fprintf(out2s," %4d %12.4f %12.4f\n",i,tempA[i-1],flujA[i-1]);		// Formato: 100
	}
	fprintf(out2s," \n");	// Formato: 20

	//* CUERPO B
	fprintf(out2s," ==================== CUERPO B ====================\n");	// Formato: 55
	fprintf(out2s,"  - Zona de contacto -\n");	// Formato: 40


	//*  Zona de contacto de B
	//write(out2s,50)

	for( i=1; i<=nelpc; i++)        
	{
		fprintf(out2s," %4d %12.4f %12.4f\n",i,tempB[i-1],flujB[i-1]);		// Formato: 100
	}
	//*  Zona libre de B
	fprintf(out2s,"  - Zona libre -\n");	// Formato: 60
	//write(out2s,50)
	for( i=nelpc+1; i<=nelB; i++)        
	{
		fprintf(out2s," %4d %12.4f %12.4f\n",i,tempB[i-1],flujB[i-1]);		// Formato: 100
	}
	//*  Cierra fichero

	fclose(out2s);

	//* Formatos
	//5   format(1X,80A);
	//10  format(1X,'Resultados problema térmico de contacto');
	//20  format(1X,'');
	//30  format(1X,'VECTOR DE CARGA TÉRMICA: TEMPERATURAS Y GRADIENTES TÉRMICOS');
	//35  format(1X,'==================== CUERPO A ====================');
	//55  format(1X,'==================== CUERPO B ====================');
	//40  format(2X,'- Zona de contacto -');
	//50  format(10X,'NODOS',2X,'TEMPERATURA',2X,'GRADIENTE TÉRMICO');
	//60  format(2X,'- Zona libre -');
	//100 format(1X,I4,1X,f12.4,1X,f12.4);

	return;
}
//************************************************************************
//*       SUBRUTINA QUE MONTA LA PARTE DE LA  MATRIZ  PERTENECIENTE      *
//*                        A LA ZONA LIBRE.                              *
//************************************************************************

void NOCONTA(int* punteroA_el,int* punteroA_nd)
{
	//* Declaracion de variables



	int el=*punteroA_el;int nd=*punteroA_nd;int i;int j;;

	//* Codigo 1
	if(cod == 1)      
	{
		for( i=1; i<=3; i++)            
		{
			for( j=1; j<=3; j++)                  
			{
				a[3*(nel+nd-1)+i-1][3*(nel+el-1)+j-1]=-BE[i-1][j-1]*Emedia;
				b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][j-1]*cc[j-1];
			}
		}
		//* Codigo 2
	}
	else if(cod == 2)      
	{
		for( i=1; i<=3; i++)            
		{
			for( j=1; j<=2; j++)                  
			{
				a[3*(nel+nd-1)+i-1][3*(nel+el-1)+j-1]=-BE[i-1][j-1]*Emedia;
				b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][j-1]*cc[j-1];
			}
			a[3*(nel+nd-1)+i-1][3*(nel+el)-1]=AE[i-1][3-1];
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][3-1]*cc[6-1];
		}
		//* Codigo 3
	}
	else if(cod == 3)      
	{
		for( i=1; i<=3; i++)            
		{
			a[3*(nel+nd-1)+i-1][3*(nel+el)-2-1]=-BE[i-1][1-1]*Emedia;
			a[3*(nel+nd-1)+i-1][3*(nel+el)-1-1]=AE[i-1][2-1];
			a[3*(nel+nd-1)+i-1][3*(nel+el)-1]=-BE[i-1][3-1]*Emedia;
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][1-1]*cc[1-1];
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][2-1]*cc[5-1];
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][3-1]*cc[3-1];
		}
		//* Codigo 4
	}
	else if(cod == 4)      
	{
		for( i=1; i<=3; i++)            
		{
			for( j=2; j<=3; j++)                  
			{
				a[3*(nel+nd-1)+i-1][3*(nel+el-1)+j-1]=AE[i-1][j-1];
				b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][2-1]*cc[3+j-1];
			}
			a[3*(nel+nd-1)+i-1][3*(nel+el)-2-1]=-BE[i-1][1-1]*Emedia;
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][1-1]*cc[1-1];
		}
		//* Codigo 5
	}
	else if(cod == 5)      
	{
		for( i=1; i<=3; i++)            
		{
			for( j=2; j<=3; j++)                  
			{
				a[3*(nel+nd-1)+i-1][3*(nel+el-1)+j-1]=-BE[i-1][j-1]*Emedia;
				b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][3-1]*cc[j-1];
			}
			a[3*(nel+nd-1)+i-1][3*(nel+el)-2-1]=AE[i-1][1-1];
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][1-1]*cc[4-1];
		}
		//* Codigo 6
	}
	else if(cod == 6)      
	{
		for( i=1; i<=3; i++)            
		{
			a[3*(nel+nd-1)+i-1][3*(nel+el)-2-1]=AE[i-1][1-1];
			a[3*(nel+nd-1)+i-1][3*(nel+el)-1-1]=-BE[i-1][2-1]*Emedia;
			a[3*(nel+nd-1)+i-1][3*(nel+el)-1]=AE[i-1][3-1];
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][1-1]*cc[4-1];
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][2-1]*cc[2-1];
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][3-1]*cc[6-1];
		}
		//* Codigo 7
	}
	else if(cod == 7)      
	{
		for( i=1; i<=3; i++)            
		{
			for( j=1; j<=2; j++)                  
			{
				a[3*(nel+nd-1)+i-1][3*(nel+el-1)+j-1]=AE[i-1][j-1];
				b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][j-1]*cc[j+3-1];
			}
			a[3*(nel+nd-1)+i-1][3*(nel+el)-1]=-BE[i-1][3-1]*Emedia;
			b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]-AE[i-1][3-1]*cc[3-1];
		}
		//* Codigo 8
	}
	else if(cod == 8)      
	{
		for( i=1; i<=3; i++)            
		{
			for( j=1; j<=3; j++)                  
			{
				a[3*(nel+nd-1)+i-1][3*(nel+el-1)+j-1]=AE[i-1][j-1];
				b[3*(nel+nd-1)+i-1]=b[3*(nel+nd-1)+i-1]+BE[i-1][j-1]*cc[j+3-1];
			}
		}
	}
	*punteroA_el = el; *punteroA_nd = nd; return;
}
//************************************************************************
//*       SUBRUTINA PARA INTERPRETAR RESULTADOS EN LA ZONA LIBRE         *
//************************************************************************

void INTLIBR(int* punteroA_j,int* punteroA_ix)
{
	//* Declaracion de variables


	int ix=*punteroA_ix;;	//parametro para identificar la numeración de las variables.
	int j=*punteroA_j;;	//auxiliar

	if(ix == 0)      
	{
		//* Cuerpo "A"
		//* Codigo 1
		if(codA[j-1][1-1] == 1)            
		{
			ccA[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccA[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccA[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 2
		}
		else if(codA[j-1][1-1] == 2)            
		{
			ccA[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccA[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccA[j-1][3-1]=x[ix+3*j-1];
			//* Codigo 3
		}
		else if(codA[j-1][1-1] == 3)            
		{
			ccA[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccA[j-1][2-1]=x[ix+3*j-1-1];
			ccA[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 4
		}
		else if(codA[j-1][1-1] == 4)            
		{
			ccA[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccA[j-1][2-1]=x[ix+3*j-1-1];
			ccA[j-1][3-1]=x[ix+3*j-1];
			//* Codigo 5
		}
		else if(codA[j-1][1-1] == 5)            
		{
			ccA[j-1][1-1]=x[ix+3*j-2-1];
			ccA[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccA[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 6
		}
		else if(codA[j-1][1-1] == 6)            
		{
			ccA[j-1][1-1]=x[ix+3*j-2-1];
			ccA[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccA[j-1][3-1]=x[ix+3*j-1];
			//* Codigo 7
		}
		else if(codA[j-1][1-1] == 7)            
		{
			ccA[j-1][1-1]=x[ix+3*j-2-1];
			ccA[j-1][2-1]=x[ix+3*j-1-1];
			ccA[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 8
		}
		else if(codA[j-1][1-1] == 8)            
		{
			ccA[j-1][1-1]=x[ix+3*j-2-1];
			ccA[j-1][2-1]=x[ix+3*j-1-1];
			ccA[j-1][3-1]=x[ix+3*j-1];
		}
	}
	else      
	{
		//* Cuerpo "B"
		//* Codigo 1
		if(codB[j-1][1-1] == 1)            
		{
			ccB[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccB[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccB[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 2
		}
		else if(codB[j-1][1-1] == 2)            
		{
			ccB[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccB[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccB[j-1][3-1]=x[ix+3*j-1];
			//* Codigo 3
		}
		else if(codB[j-1][1-1] == 3)            
		{
			ccB[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccB[j-1][2-1]=x[ix+3*j-1-1];
			ccB[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 4
		}
		else if(codB[j-1][1-1] == 4)            
		{
			ccB[j-1][4-1]=x[ix+3*j-2-1]*Emedia;
			ccB[j-1][2-1]=x[ix+3*j-1-1];
			ccB[j-1][3-1]=x[ix+3*j-1];
			//* Codigo 5
		}
		else if(codB[j-1][1-1] == 5)            
		{
			ccB[j-1][1-1]=x[ix+3*j-2-1];
			ccB[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccB[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 6
		}
		else if(codB[j-1][1-1] == 6)            
		{
			ccB[j-1][1-1]=x[ix+3*j-2-1];
			ccB[j-1][5-1]=x[ix+3*j-1-1]*Emedia;
			ccB[j-1][3-1]=x[ix+3*j-1];
			//* Codigo 7
		}
		else if(codB[j-1][1-1] == 7)            
		{
			ccB[j-1][1-1]=x[ix+3*j-2-1];
			ccB[j-1][2-1]=x[ix+3*j-1-1];
			ccB[j-1][6-1]=x[ix+3*j-1]*Emedia;
			//* Codigo 8
		}
		else if(codB[j-1][1-1] == 8)            
		{
			ccB[j-1][1-1]=x[ix+3*j-2-1];
			ccB[j-1][2-1]=x[ix+3*j-1-1];
			ccB[j-1][3-1]=x[ix+3*j-1];
		}
	}
	*punteroA_j = j; *punteroA_ix = ix; return;
}
//************************************************************************
//*              SUBRUTINA PARA EL CHEQUEO DE TRACCIONES                 *
//************************************************************************

void CHETRAC()
{
	//* Declaracion de variables
	/*
	printf("nelpc = %d",nelpc);
	for(int t=0;t<nelpc;t++)
	{
		printf("ccA[%d][3] = %12.4f\n",t,ccA[t][3]);
		char tDavid;
		if(t+1 % 50 == 0)
		scanf("%c",tDavid);
	}
	*/

	int nd,j;	//auxiliar

	//* Chequea tracciones
	for( nd=1; nd<=nelpc; nd++)      
	{
		if((((tpproT == 1) || (tpproTE == 1)) && (codA[nd-1][2-1] == 3)) || ((tpproE == 1) && (codA[nd-1][1-1] == 9)))         
		{
			if(ccA[nd-1][4-1] < 0.0 )           
			{
				//*                  write(out1s,50)nd,ccA(nd,4),codA(nd,1)
			}
			else            
			{
				ifla=ifla+1;
				codA[nd-1][1-1]=8;
				codB[nd-1][1-1]=8;
				for( j=4; j<=6; j++)                  
				{
					ccA[nd-1][j-1]=0;
					ccB[nd-1][j-1]=0;
				}
				//defino el tipo de transferencia de calor en los despegues

				if(tip == 0)                  
				{
					//*sin intercambio de calor en los despegues

					codA[nd-1][2-1]=2;
					codB[nd-1][2-1]=2;

					ccA[nd-1][8-1]=0;
					ccB[nd-1][8-1]=0;

				}
				else if(tip == 1)                   
				{
					//* Convección libre

					codA[nd-1][2-1]=5;
					codB[nd-1][2-1]=5;

					RTC[nd-1]=2/hflu;

				}
				else if(tip == 2)                   
				{
					//* convección forzada

					codA[nd-1][2-1]=4;
					codB[nd-1][2-1]=4;

					ccA[nd-1][9-1]=tflu;
					ccA[nd-1][10-1]=hflu;
					ccB[nd-1][9-1]=tflu;
					ccB[nd-1][10-1]=hflu;

				}
				else if(tip == 3)                   
				{
					//* conducción NO VA BIEN

					//xgap=abs(-(ccA(nd,1)+ccB(nd,1)-gap(nd)))
					//RTC(nd)=(xgap+sigA+sigB)/kg

				}
			}
		}
	}
	//*10     format(1x,'+++++++++++++++++++++')
	//*20     format(2x,'======== CHEQUEO DE TRACCIONES ========')
	//*30     format(5x,'NODO',6X,'T1',5x,'Nuevo Codigo')
	//*50     format(3X,I4,1x,E10.4,7x,I4)


	return;
}
//************************************************************************
//*       SUBRUTINA PARA EL CALCULO Y CHEQUEO DE INTERPENETRACIONES      *
//************************************************************************

void CHEINTE()
{
	//* Declaracion de variables


	int nd;	//auxiliar
	double xgap;

	//* Calcula la separacion entre los pares de contacto ( gap )

	for( nd=1; nd<=nelpc; nd++)      
	{
		xgap=-(ccA[nd-1][1-1]+ccB[nd-1][1-1]-gap[nd-1]);
		//* Chequea interpenetraciones
		if(xgap >= 0. )            
		{
			//*                  write(out1s,50)nd,gap(nd),xgap,codA(nd,1)
		}
		else            
		{
			if(fabs(xgap) < 1.0E-10 )                  
			{
				//*                        write(out1s,50)nd,gap(nd),xgap,codA(nd,1)
			}
			else                  
			{
				ifla=ifla+1;
				codA[nd-1][1-1]=9;
				codB[nd-1][1-1]=9;
				codA[nd-1][2-1]=3;
				codB[nd-1][2-1]=3;
			}
		}
	}
	//*20     format(2x,'======== INTERPENETRACIONES =======')
	//*30     format(1x,'Par',9x,'gap',9x,'xgap',9x,'Nuevo Codigo')
	//*50     format(1x,I4,1x,E10.4,1x,E10.4,7x,I4)

	return;
}
#endif /* FUNCIONESA_H_ */

