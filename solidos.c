#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "funcionesPersonales.h"
#include "variables.h"
#include "funcionesA.h"
#include "funcionesB.h"
#include "funcionesC.h"
#include "funcionesD.h"
#include "funcionesMain.h"

//******************************************************************************
//*  ANÁLISIS DE DOS SÓLIDOS ELÁSTICOS TRIDIMENSIONALES EN CONTACTO MEDIANTE   *
//*  EL MÉTODO DE LOS ELEMENTOS DE CONTORNO. SE CONSIDERAN CARGAS TERMICAS.    *
//*  SE USAN ELEMENTOS TRIANGULARES CONSTANTES (DISCONTINUOS)                  *
//******************************************************************************

//******************************************************************************
//*                                                                            *
//*  Name:        prep.f90                                                     *
//*  Date:        Viernes, 5 de Febrero de 2007                               *
//*  Input:       Fichero 'Entrada.dat'                                        *
//*  Output:      Ficheros 'SalDatos.sal', DatosAux.sal','CondCont.dat'        *
//*  Usage:       prep.exe                                                     *
//*  Description: Gestiona la entrada de datos y realiza las integraciones     *
//*                para la opbtención de los coeficientess                     *
//*                                                                            *
//******************************************************************************


int dims=2;


void pruebaF(int array[dims][dims])
{
	//array[0] = 1;
	//array[1] = 2;
	array[0][0] = 1;
	array[1][1] = 2;
	//array[2][2] = 5;
}
/**/

/*
void pruebaF(int** array)
{
	//array[0] = 1;
	//array[1] = 2;
	array[0][0] = 1;
	array[1][1] = 2;
	//array[2][2] = 5;
}
/**/

int main(void)
{
	//* Declaracion de variables

	/*
	int** prueba = malloc(2*sizeof(int*));
	for(int j=0;j<2;j++)
	prueba[j] = malloc(2*sizeof(int));




	//int prueba[2][2];
	prueba[0][0] = 14;
	prueba[1][1] = 24;

	int temp[dims][dims];
	for(int j=0;j<dims;j++)
	for(int i=0;i<dims;i++)
	temp[j][i] = prueba[j][i];

	pruebaF(temp);

	for(int j=0;j<dims;j++)
	for(int i=0;i<dims;i++)
	prueba[j][i] = temp[j][i];


	printf("%d | %d ",prueba[0][0],prueba[1][1]);

	return 0;
	/**/

	float  tinicio,tfinal;
	int  iCod;
	//de solu...
	double  eps;
	int i,j,contador,contres;	//auxiliar
	char fich_parciales[80];

	//* Comienzo del programa
	tinicio = clock()/CLOCKS_PER_SEC;
	printf("Inicio del proceso. Entrando en PREPROCESADOR\n");
	//* Inicializa variables
	out1=2;
	out2=3;
	out3=4;
	out4=5;

	//del Solu...
	in1s=6;
	in2s=7;
	in3s=8;
	in4s=9;
	in5s=10;
	in6s=11;
	in7s=12;
	in8s=13;
	in9s=14;
	in10s=15;
	out1s=16;

	//* Abre fichero
	in1 = fopen("EntradaCompleta.dat", "r");
	//* Lee el titulo del problema a analizar
	leeCadena(in1,&titulo);

	//* Lee el tipo de problema
	leeEntero(in1,&tpproE);leeEntero(in1,&tpproT);leeEntero(in1,&tpproTE);leeLinea(in1);
	//* Lee el tipo de cargas especiales
	leeEntero(in1,&tpcarPP);leeEntero(in1,&tpcarFC);leeEntero(in1,&tpcarFP);leeEntero(in1,&tpcarFL);leeEntero(in1,&tpcarFD);leeLinea(in1);
	//* Lee los flags de simetria
	leeEntero(in1,&simXY);leeEntero(in1,&simXZ);leeEntero(in1,&simYZ);leeLinea(in1);
	//* Lee el numero de elementos cargados
	//read(in1,*)nelwA,nelwB   ! ¿Se podría obtener en tiempo de ejecución?
	//* Lee las caracteristicas elasticas
	leeDouble(in1,&EA);leeDouble(in1,&nuA);leeDouble(in1,&alA);leeDouble(in1,&EB);leeDouble(in1,&nuB);leeDouble(in1,&alB);leeLinea(in1);
	//* Lee las caracteristicas térmicas
	leeDouble(in1,&tref);leeDouble(in1,&lamA);leeDouble(in1,&lamB);leeLinea(in1);
	//* Lee el tipo de contacto
	leeEntero(in1,&TIM);leeLinea(in1);
	//* Contacto imperfecto
	if(TIM == 1)    
	{
		//VACIO
		leeDouble(in1,&HAmicro);leeDouble(in1,&sigA);leeDouble(in1,&mA);leeLinea(in1);		//acabado superficial de A
		leeDouble(in1,&HBmicro);leeDouble(in1,&sigB);leeDouble(in1,&mB);leeLinea(in1);		//acabado superficial de B
	}
	else if(TIM == 2)    
	{
		//GAS
		leeDouble(in1,&HAmicro);leeDouble(in1,&sigA);leeDouble(in1,&mA);leeLinea(in1);		//acabado superficial de A
		leeDouble(in1,&HBmicro);leeDouble(in1,&sigB);leeDouble(in1,&mB);leeLinea(in1);		//acabado superficial de B
		leeDouble(in1,&kg);leeDouble(in1,&M0);leeLinea(in1);		//características térmicas del material en la interfase
	}
	else if(TIM == 3)    
	{
		//LIQUIDO (GREASE, GEL)
		leeDouble(in1,&HAmicro);leeDouble(in1,&sigA);leeDouble(in1,&mA);leeLinea(in1);		//acabado superficial de A
		leeDouble(in1,&HBmicro);leeDouble(in1,&sigB);leeDouble(in1,&mB);leeLinea(in1);		//acabado superficial de B
		leeDouble(in1,&kg);leeLinea(in1);		//características térmicas del material en la interfase
	}
	else if(TIM == 4)    
	{
		//SÓLIDO (POLÍMERO, ADHESIVO, ELASTÓMERO)
		leeDouble(in1,&HAmicro);leeDouble(in1,&sigA);leeDouble(in1,&mA);leeLinea(in1);		//acabado superficial de A
		leeDouble(in1,&HBmicro);leeDouble(in1,&sigB);leeDouble(in1,&mB);leeLinea(in1);		//acabado superficial de B
		leeDouble(in1,&kg);leeDouble(in1,&tTIM);leeDouble(in1,&ETIM);leeLinea(in1);		//características térmicas, mecanicas y espesor del material en la interfase
	}
	//* Materiales intersticiales
	leeEntero(in1,&tip);leeLinea(in1);

	if(tip == 1)    
	{
		//CONVECCION LIBRE
		leeDouble(in1,&hflu);leeLinea(in1);		//coeficiente convectivo del material

	}
	else if(tip == 2)    
	{
		//CONVECCION FORZADA
		leeDouble(in1,&tflu);leeDouble(in1,&hflu);leeLinea(in1);		//temperatura y coeficiente del fluido
	}
	//* Lee el coeficiente de friccion
	leeDouble(in1,&cf);leeLinea(in1);
	//* Lee tipo de codificacion
	leeEntero(in1,&iCod);leeLinea(in1);
	//* En funcion del tipo de codificacion sigue un camino u otro
	if(iCod == 0)      
	{
		//* Entrada muy codificada
		CODIFICADA();if(enExcepcion==1)return 0;
	}
	else      
	{
		//* Entrada normal ( con cierto tipo de codificacion )
		SEMICODIFICADA();if(enExcepcion==1)return 0;
	}
	//* Cierra ficheros
	fclose(in1);
	//* Calcula numero de nodos cargados
	NODOS_CARGADOS();if(enExcepcion==1)return 0;
	//* Calcula el numero de elementos pasivos en cada solido
	nelpA=nelA-nelpc-nelwA;
	nelpB=nelB-nelpc-nelwB;
	//* Calcula las direcciones de contacto
	DIR_CONTACTO();if(enExcepcion==1)return 0;
	//* Calcula las separaciones iniciales entre pares de contacto
	GAP_INICIAL();if(enExcepcion==1)return 0;
	//* Escribe fichero de datos intermedio y fichero de salida de datos
	//call SALIDA
	Emedia=(EA+EB)/2.0;
	//* Valores de la distorsionabilidad
	diA=(1+nuA)*alA/lamA;
	diB=(1+nuB)*alB/lamB;

	//* Escribe fichero de seguridad
	//call SEGURIDAD

	//==============================================================================
	//* Va a la subrutina de cálculo de coeficientes INTEGRAL
	INTEGRAL();if(enExcepcion==1)return 0;
	//==============================================================================
	//* Final del prep
	printf("Final del proceso. Saliendo de PREPROCESADOR\n");
	tfinal = clock()/CLOCKS_PER_SEC;
	printf(" Tiempo de proceso = %f segundos\n",tfinal-tinicio);
	//* Formatos

	//* Comienzo de solu...
	tinicio = clock()/CLOCKS_PER_SEC;

	//* Comienzo del programa
	printf("Inicio del proceso. Entrando en SOLUCION\n");
	//* Inicializa variables

	strcpy(nomArchSalTer, "term.dat");
	strcpy(nomArchSalElas, "elast.dat");
	eps=1.0E-06;
	ifla=1;
	chires=0;

	//* Calcula el numero de grados de libertad del problema
	ngl=3*(nelA+nelB);
	//* Calcula el numero total de elementos
	nelT=nelA+nelB;
	//* Asigna el numero maximo de iteraciones para la subrutina SPARSE
	nmiter=ngl*10;
	//Se inicializa el vector resistencia térmica de contacto inicial RTC
	for( i= 1; i<= nelpc; i++)      
	{
		RTC[i-1]=0.0;
	}
	contador=0;
	contres=0;

	//* Comienza proceso iterativo

	l1000:    printf("+++++++++++++++++++++ proceso iterativo +++++++++++++++++++++++++ \n");

	printf("iteracion resistencia=%d\n",contres);
	printf("iteracion elastica=%d\n",contador);

	//* Inicializa vector de condiciones de contorno para elementos de la zona potencial de contacto
	//zona de contacto inicial si la resistencia no converge

	for( i=1; i<=nelA; i++)      
	{
		if(codA[i-1][1-1] == 9)            
		{
			for( j=1; j<=8; j++)                  
			{
				ccA[i-1][j-1]=0.0;
			}
		}
	}
	for( i=1; i<=nelB; i++)      
	{
		if(codB[i-1][1-1] == 9)            
		{
			for( j=1; j<=8; j++)                  
			{
				ccB[i-1][j-1]=0.0;
			}
		}
	}
	//Se resuelve el problema térmico de potencial
	if((tpproT == 1) || (tpproTE == 1))      
	{
		nT=nelT;
		TERMICO();if(enExcepcion==1)return 0;
	}
	if((tpproE == 1) || (tpproTE == 1))      
	{
		nT=ngl;
		//* Monta el sistema de ecuaciones
		printf(" MONTANDO SISTEMA DE ECUACIONES\n");
		MONTAJE();if(enExcepcion==1)return 0;

		//* Resuelve el sistema de ecuaciones
		printf(" RESOLVIENDO SISTEMA DE ECUACIONES\n");
		rsq=0.0;
		GAUSS_SOLU();if(enExcepcion==1)return 0;

		//* Interpreta los resultados
		printf(" INTERPRETANDO RESULTADOS\n");
		INTERPR();if(enExcepcion==1)return 0;

		//* Escribe los resultados obtenidos
		//open(unit=out1s,file='interpr.sal')

		//*          call CABECER
		//call ESCRIBE
		//close(unit=out1s)

		//* Calcula deslizamientos relativos
		DESLIZA();if(enExcepcion==1)return 0;

		//* Actualiza el número de incrementos
		out1=out1+1;

		//* Escribe los resultados obtenidos
		printf(" ESCRIBIENDO RESULTADOS\n");

		//write(fich_parciales,*) contador
		//fich_parciales = adjustl(fich_parciales)
		//fich_parciales = 'parciales'//trim(fich_parciales)//'.sal'
		//open(unit=out1s,file='parciales.sal')

		//*          call CABECER
		//call ESCRIBE

		//* Chequea los resultados obtenidos
		printf(" CHEQUEANDO RESULTADOS\n");
		CHEQUEO();if(enExcepcion==1)return 0;

		//close(unit=out1s)

		//* Escribe fichero de seguridad
		//open(UNIT=in6s)
		//call ESCSEGU
		//close(UNIT=in6s)

		//* Si es necesario, realiza una nueva iteracion
		if(ifla != 0)            
		{
			contador=contador+1;
			goto l1000;
		}
	}
	//* Compara resitencia térmicas
	if(TIM != 0)        
	{
		if((tpproT == 1) || (tpproTE == 1))            
		{
			COMPRESIS();if(enExcepcion==1)return 0;
			if(chires != 0)                
			{
				contador=0;
				contres=contres+1;
				goto l1000;
			}
		}
	}
	printf("convergencia de resistencia lograda\n");

	//* @@@@@@@@@@@@@@@@@@@@ FIN DEL PROCESO ITERATIVO @@@@@@@@@@@@@@@@@@@@@@

	//* Escribe la solucion definitiva
	printf(" ESCRIBIENDO LA SOLUCION DEFINITIVA\n");
	SALIDA_SOLU();if(enExcepcion==1)return 0;

	//* Final del programa
	printf("Final del proceso. Saliendo de ELASTICO.EXE\n");
	tfinal = clock()/CLOCKS_PER_SEC;
	printf(" Tiempo de proceso = %f segundos\n",tfinal-tinicio);


	free(AE_A);free(AE_B);
	free(BE_A);free(BE_B);
	free(AT_A);free(AT_B);
	free(BT_A);free(BT_B);
	free(CTE_A);free(CTE_B);
	free(DTE_A);free(DTE_B);

	return 0;

}
//******** FIN DEL PROGRAMA ************









