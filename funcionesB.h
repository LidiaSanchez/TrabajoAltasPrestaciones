#ifndef FUNCIONESB_H_
#define FUNCIONESB_H_

#include "funcionesPersonales.h"
#include "variables.h"

#include "funcionesC.h"
#include "funcionesD.h"


//******************************************************************************
//*                                                                            *
//*  Input:       Fichero 'Entrada.dat'                                        *
//*               ndInicial = Nodo en el que se comienza la asignacion         *
//*               ndFinal = Nodo en el que se finaliza la asignacion           *
//*               tpCod = 1 para codigos elasticos y 2 para codigos termicos   *
//*  Output:                                                                   *
//*  Usage:                                                                    *
//*  Description: Lee los codigos de carga                                     *
//*                                                                            *
//*                                                                            *
//******************************************************************************

void CODIGOS(int* punteroA_ndInicial,int* punteroA_ndFinal,int* punteroA_tpCod)
{
	//* Declaracion de variables


	int ndInicial=*punteroA_ndInicial,ndFinal=*punteroA_ndFinal;	//Nodos inicial y final
	int  ndUlt,ndAct,nd;	//Auxiliares
	int codigo, tpCod=*punteroA_tpCod;
	ndAct = ndInicial;
	while(ndAct <= ndFinal)
	{
		leeEntero(in1,&ndUlt);leeEntero(in1,&codigo);leeLinea(in1);
		if((tpCod == 1) && ((codigo > 11) || (codigo < 1)))        
		{
			printf(" Nodo = %d Codigo = %d\n",ndUlt,codigo);
			printf("***ERROR*** => CODIGO ELASTICO NO VALIDO\n"); enExcepcion=1;return;
		}
		else if((tpCod == 2) && ((codigo > 4) || (codigo < 1)))        
		{
			printf(" Nodo = %d Codigo = %d\n",ndUlt,codigo);
			printf("***ERROR*** => CODIGO TERMICO NO VALIDO\n"); enExcepcion=1;return;
		}
		if((ndUlt < ndAct) || (ndUlt > ndFinal))        
		{
			printf(" Nodo = %d Codigo = %d\n",ndUlt,codigo);
			printf("***ERROR*** => ERROR EN CODIGOS\n"); enExcepcion=1;return;
		}
		for( nd=ndAct; nd<=ndUlt; nd++)        
		{
			codB[nd-1][tpCod-1]=codigo;
		}
		ndAct=ndUlt+1;
	}
	*punteroA_ndInicial = ndInicial; *punteroA_ndFinal = ndFinal; *punteroA_tpCod = tpCod; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:       intenum = 1 -> Integracion numerica                          *
//*                        = 0 -> Integracion analitica                        *
//*  Output:      AET,BET,ATT,BTT,CT,DT = coeficientes de integracion          *
//*  Usage:                                                                    *
//*  Description: Coordina las integraciones. LLama a las subrutina de         *
//*               integracion apropiada                                        *
//*                                                                            *
//******************************************************************************

void INTEGRA(int* punteroA_intenum,double AET[3][3],double BET[3][3],double* punteroA_ATT,double* punteroA_BTT,double CT[3],double DT[3][3])
{
	//* Declaracion de variables


	int intenum=*punteroA_intenum;;	//tipo de integracion
	/*double AET[3][3];*	//*double BET[3][3];*/;      //Coeficientes de integracion elasticos
	double ATT=*punteroA_ATT;double BTT=*punteroA_BTT;;	//Coeficientes de integracion termicos
	/*double CT[3];*	//*double DT[3][3];*/;      //Coeficientes de integracion termoelasticos
	double  AEP[3][3],BEP[3][3];	//Coeficientes de integracion elasticos parciales
	double  ATP,BTP;	//Coeficientes de integracion termicos parciales
	double  CP[3],DP[3][3];	//Coeficientes de integracion termoelasticos parciales
	double  dist;	//Distancia entre el punto de colocacion y el baricentro del elemento
	double  subextr[MAX_SUB][4][3];	//Coordenadas de los vertices de los cuatro subtriangulos
	double  extrs[4][3];	//Coordenadas de los vertices del triangulo a dividir
	double  subex[4][4][3];	//Auxiliares
	int  i,j,k,m,p;
	double  bar[3];	//baricentro del elemento
	double  lado[3];	//longitud de cada lado del elemento
	double  lad[3][3];	//vector de cada lado del elemento
	double  n[3];
	double  distancia,dis[3];

	//* Asigna cuarto extremo y calcula baricentro del elemento
	for( i=1; i<=3; i++)      
	{
		extr[4-1][i-1]=extr[1-1][i-1];
		bar[i-1]=(extr[1-1][i-1]+extr[2-1][i-1]+extr[3-1][i-1])/3.0;
	}
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
	//* Calcula el vector normal
	n[1-1]=-lad[1-1][2-1]*lad[3-1][3-1]+lad[1-1][3-1]*lad[3-1][2-1];
	n[2-1]=-lad[1-1][3-1]*lad[3-1][1-1]+lad[1-1][1-1]*lad[3-1][3-1];
	n[3-1]=-lad[1-1][1-1]*lad[3-1][2-1]+lad[1-1][2-1]*lad[3-1][1-1];

	//* Decide el tipo de integracion
	if(intenum == 0)      
	{
		ANALITICA(AET,BET,&ATT,&BTT,CT,DT,n,bar);if(enExcepcion==1)return;
	}
	else      
	{
		//*Calcula el vector que va del baricentro al nodo desde el que se integra
		dist=0.0;
		distancia=0.0;
		for( i=1; i<=3; i++)          
		{
			dis[i-1]=(bar[i-1]-ndCol[i-1]);
			dist=dist+pow(dis[i-1],2);
			distancia=distancia+dis[i-1]*n[i-1];
		}
		dist=sqrt(dist);
		//*Calcula la distancia del nodo desde el que se integra al plano del elemento
		distancia=fabs(distancia);

		//* Decide si hay que subdividir el elemento
		if((lado[1-1] > dist) || (lado[2-1] > dist) || (lado[3-1] > dist))        
		{
			//* Hay que subdividir el elemento
			for( i=1; i<=4; i++)             
			{
				for( j=1; j<=3; j++)              
				{
					extrs[i-1][j-1]=extr[i-1][j-1];
				}
			}
			SUBDIVIDE(extrs, subex);if(enExcepcion==1)return;
			for( i=1; i<=4; i++)          
			{
				for( j=1; j<=4; j++)            
				{
					for( k=1; k<=3; k++)              
					{
						subextr[i-1][j-1][k-1]=subex[i-1][j-1][k-1];
					}
				}
			}
			i=1;
			k=4;
			while(i <= k)
			{
				//* Nuevas constantes de subdivision
				dist=0.0;
				for( j=1; j<=3; j++)            
				{
					bar[j-1]=(subextr[i-1][1-1][j-1]+subextr[i-1][2-1][j-1]+subextr[i-1][3-1][j-1])/3.0;
					dist=dist+pow((ndCol[j-1]-bar[j-1]),2);
					lado[j-1]=0.0;
					for( m=1; m<=3; m++)              
					{
						lado[j-1]=lado[j-1]+pow((subextr[i-1][j+1-1][m-1]-subextr[i-1][j-1][m-1]),2);
					}
					lado[j-1]=sqrt(lado[j-1]);
				}
				dist=sqrt(dist);

				if((lado[1-1] > dist) || (lado[2-1] > dist) || (lado[3-1] > dist))            
				{
					//* Hay que volver a subdividir
					for( j=1; j<=4; j++)              
					{
						for( m=1; m<=3; m++)                
						{
							extrs[j-1][m-1]=subextr[i-1][j-1][m-1];
						}
					}
					SUBDIVIDE(extrs, subex);if(enExcepcion==1)return;

					for( j=1; j<=4; j++)              
					{
						for( p=1; p<=3; p++)                
						{
							subextr[i-1][j-1][p-1]=subex[1-1][j-1][p-1];
						}
					}
					for( m=2; m<=4; m++)              
					{
						for( j=1; j<=4; j++)                
						{
							for( p=1; p<=3; p++)                  
							{
								subextr[k+m-1-1][j-1][p-1]=subex[m-1][j-1][p-1];
							}
						}
					}
					k=k+3;
					if(k > 997)              
					{
						printf("Superado el numero maximo de subdivisiones\n"); enExcepcion=1;return;
					}
				}
				else            
				{
					i=i+1;
				}
			}
			for( i=1; i<=3; i++)        
			{
				CT[i-1]=0.0;
				for( j=1; j<=3; j++)            
				{
					AET[i-1][j-1]=0.0;
					BET[i-1][j-1]=0.0;
					DT[i-1][j-1]=0.0;
				}
			}
			ATT=0.0;
			BTT=0.0;

			for( i=1; i<=k; i++)        
			{
				for( j=1; j<=4; j++)            
				{
					for( m=1; m<=3; m++)                
					{
						extr[j-1][m-1]=subextr[i-1][j-1][m-1];
					}
				}
				NUMERICA(AEP,BEP,&ATP,&BTP,CP,DP,n,&distancia);if(enExcepcion==1)return;

				if((tpproE == 1) || (tpproTE == 1))            
				{
					for( j=1; j<=3; j++)                
					{
						for( m=1; m<=3      ; m++)                    
						{
							AET[j-1][m-1]=AET[j-1][m-1]+AEP[j-1][m-1];
							BET[j-1][m-1]=BET[j-1][m-1]+BEP[j-1][m-1];
						}
					}
				}
				if((tpproT == 1) || (tpproTE == 1))            
				{
					ATT=ATT+ATP;
					BTT=BTT+BTP;
				}
				if(tpproTE == 1)            
				{
					for( j=1; j<=3; j++)                
					{
						CT[j-1]=CT[j-1]+CP[j-1];
						for( m=1; m<=3; m++)                    
						{
							DT[j-1][m-1]=DT[j-1][m-1]+DP[j-1][m-1];
						}
					}
				}
			}
		}
		else        
		{
			//* No hay que subdividir
			//write(*,*) '  no subdivision'
			//write(*,*) '   NUMÉRICA'
			NUMERICA(AET,BET,&ATT,&BTT,CT,DT,n,&distancia);if(enExcepcion==1)return;
		}
	}
	*punteroA_intenum = intenum; *punteroA_ATT = ATT; *punteroA_BTT = BTT; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:       el = elemento sobre el que se ha integrado                   *
//*  Output:      Coeficientes elasticos transformados                         *
//*  Usage:                                                                    *
//*  Description: Cambia a coordenadas locales los coeficientes de integracion *
//*               elasticos                                                    *
//*                                                                            *
//******************************************************************************

void TRANSFORMA(double AETR[3][3],double BETR[3][3],int* punteroA_el)
{
	//* Declaracion de variables


	int el=*punteroA_el;;	//Elemento sobre el que se ha integrado
	int  i,j;	//Auxiliares
	double ccc[3][3];/*double AETR[3][3];*	//*double BETR[3][3];*/;
	//real*8  cct(3),CTR(3),DTR(3,3)
	//* Realiza transformacion

	//* Coeficientes elásticos
	for( i=1; i<=3; i++)      
	{
		ccc[i-1][1-1]=AETR[i-1][1-1]*locT[el-1][1-1]+AETR[i-1][2-1]*locT[el-1][2-1]+AETR[i-1][3-1]*locT[el-1][3-1];
		ccc[i-1][2-1]=AETR[i-1][1-1]*locT[el-1][4-1]+AETR[i-1][2-1]*locT[el-1][5-1]+AETR[i-1][3-1]*locT[el-1][6-1];
		ccc[i-1][3-1]=AETR[i-1][1-1]*locT[el-1][7-1]+AETR[i-1][2-1]*locT[el-1][8-1]+AETR[i-1][3-1]*locT[el-1][9-1];

	}
	for( i=1; i<=3; i++)      
	{
		for( j=1; j<=3; j++)        
		{
			AETR[i-1][j-1]=ccc[i-1][j-1];
		}
	}
	for( i=1; i<=3; i++)      
	{
		ccc[i-1][1-1]=BETR[i-1][1-1]*locT[el-1][1-1]+BETR[i-1][2-1]*locT[el-1][2-1]+BETR[i-1][3-1]*locT[el-1][3-1];
		ccc[i-1][2-1]=BETR[i-1][1-1]*locT[el-1][4-1]+BETR[i-1][2-1]*locT[el-1][5-1]+BETR[i-1][3-1]*locT[el-1][6-1];
		ccc[i-1][3-1]=BETR[i-1][1-1]*locT[el-1][7-1]+BETR[i-1][2-1]*locT[el-1][8-1]+BETR[i-1][3-1]*locT[el-1][9-1];
	}
	for( i=1; i<=3; i++)      
	{
		for( j=1; j<=3; j++)        
		{
			BETR[i-1][j-1]=ccc[i-1][j-1];
		}
	}
	//* Coeficientes termoelásticos
	//do i=1,3
	//ccc(i,1)=DTR(i,1)*locT(el,1)+DTR(i,2)*locT(el,2)+DTR(i,3)*locT(el,3)
	//ccc(i,2)=DTR(i,1)*locT(el,4)+DTR(i,2)*locT(el,5)+DTR(i,3)*locT(el,6)
	//ccc(i,3)=DTR(i,1)*locT(el,7)+DTR(i,2)*locT(el,8)+DTR(i,3)*locT(el,9)
	//enddo
	//do i=1,3
	//do j=1,3
	//DTR(i,j)=ccc(i,j)
	//enddo
	//enddo

	//cct(1)=CTR(1)*locT(el,1)+CTR(2)*locT(el,2)+CTR(3)*locT(el,3)
	//cct(2)=CTR(1)*locT(el,4)+CTR(2)*locT(el,5)+CTR(3)*locT(el,6)
	//cct(3)=CTR(1)*locT(el,7)+CTR(2)*locT(el,8)+CTR(3)*locT(el,9)
	//do i=1,3
	//CTR(i)=cct(i)
	//enddo
	*punteroA_el = el; return;
}
//******************************************************************************
//*                                                                            *
//*  Input:                                                                    *
//*  Output:      Ficheros de coeficientes de integracion                      *
//*  Usage:                                                                    *
//*  Description: Almacena los coeficientes de integracion                     *
//*                                                                            *
//******************************************************************************

void ALMACENA(int* punteroA_el,int* punteroA_nd,double** AE_T,double** BE_T,double** AT_T,double** BT_T,double** CTE_T,double** DTE_T)
{
	//* Declaracion de variables


	int el=*punteroA_el;int nd=*punteroA_nd;;	//Elemento sobre el que se ha integrado y nodo
	int  i,j;	//Auxiliares

	/*double AE_T[3*nelT][3*nelT];*	//*double BE_T[3*nelT][3*nelT];*/;
	/*double AT_T[nelT][nelT];*	//*double BT_T[nelT][nelT];*/;
	/*double CTE_T[3*nelT][nelT];*	//*double DTE_T[3*nelT][nelT];*/;

	//* Coeficientes elasticos
	if((tpproE == 1) || (tpproTE == 1))      
	{
		//* SI SE DESEA PUEDEN ESCALARSE LOS COEFICIENTES Bij ANTES DEL ALMACENAJE

		int arTemp_0;int arTemp_1;int arTemp_2;int arTemp_3;arTemp_2 = 1-1; for(arTemp_0=el*3 - 2;arTemp_0<=el*3;arTemp_0+=1)
		{
			arTemp_2 += 1;arTemp_3 = 1-1; for(arTemp_1=nd*3 -2;arTemp_1<=nd*3;arTemp_1+=1)
			{
			arTemp_3 += 1;AE_T[arTemp_0-1][arTemp_1-1] = AE[arTemp_2-1][arTemp_3-1];
			}
		}
		;
		int arTemp_4;int arTemp_5;int arTemp_6;int arTemp_7;arTemp_6 = 1-1; for(arTemp_4=el*3 - 2;arTemp_4<=el*3;arTemp_4+=1)
		{
			arTemp_6 += 1;arTemp_7 = 1-1; for(arTemp_5=nd*3 -2;arTemp_5<=nd*3;arTemp_5+=1)
			{
			arTemp_7 += 1;BE_T[arTemp_4-1][arTemp_5-1] = BE[arTemp_6-1][arTemp_7-1];
			}
		}
		;
		//write(unit=out1,rec=reg)AE
		//write(unit=out2,rec=reg)BE

		//write(out11,*)AE(1,1),AE(1,2),AE(1,3),AE(2,1),AE(2,2),AE(2,3),AE(3,1),AE(3,2),AE(3,3)
		//write(out12,*)BE(1,1),BE(1,2),BE(1,3),BE(2,1),BE(2,2),BE(2,3),BE(3,1),BE(3,2),BE(3,3)
	}
	//* Coeficientes termicos
	if((tpproT == 1) || (tpproTE == 1))     
	{
		AT_T[el-1][nd-1]=AT;
		BT_T[el-1][nd-1]=BT;
		//write(unit=out3,rec=reg)AT
		//write(out13,*)AT
		//write(unit=out4,rec=reg)BT
		//write(out14,*)BT
	}
	//* Coeficientes termoelasticos
	if(tpproTE == 1)     
	{
		//inicializa coeficiente termoelástico
		for( i=1; i<=3; i++)        
		{
			DTTE[i-1]=0.0;
		}
		//* Calcula el coeficiente termoelástico Di=Dij*nj
		for( i=1; i<=3; i++)        
		{
			for( j=1; j<=3; j++)            
			{
				DTTE[i-1]=DTTE[i-1]+DTE[i-1][j-1]*locT[el-1][j-1];
			}
		}
		int arTemp_8;int arTemp_9;int arTemp_10;arTemp_10 = 1-1; for(arTemp_8=el*3 - 2;arTemp_8<=el*3;arTemp_8+=1)
		{
			arTemp_10 += 1;for(arTemp_9=nd;arTemp_9<=nd;arTemp_9+=1)
			{
			CTE_T[arTemp_8-1][arTemp_9-1] = CTE[arTemp_10-1];
			}
		}
		;
		int arTemp_11;int arTemp_12;int arTemp_13;arTemp_13 = 1-1; for(arTemp_11=el*3 - 2;arTemp_11<=el*3;arTemp_11+=1)
		{
			arTemp_13 += 1;for(arTemp_12=nd;arTemp_12<=nd;arTemp_12+=1)
			{
			DTE_T[arTemp_11-1][arTemp_12-1] = DTTE[arTemp_13-1];
			}
		}
		;
		//write(unit=out5,rec=reg)CTE
		//write(unit=out6,rec=reg)DTTE
		//write(out15,*)CTE
		//write(out16,*)DTTE
	}
	*punteroA_el = el; *punteroA_nd = nd; return;

}
#endif /* FUNCIONESB_H_ */

