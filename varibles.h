#ifndef VARIABLES_H_
#define VARIABLES_H_

#define  MAX_EX 5000// Máximo número de extremos ( son 4000 todos)
#define  MAX_ND 5000// Máximo número de nodos
#define MAX_EL 5000// Máximo número de elementos
#define MAX_SUB 5000// Máximo número de subelementos

int enExcepcion=0;

char titulo[80];// Título del problema
char nomArchSalTer[80];// Nombre del archivo de salida [térmico]
char nomArchSalElas[80];// Nombre del archivo de salida [elástico

int  nelA;// Número total de elementos. Sólido A
int  nelB;// Número total de elementos. Sólido B
int  nelT;// Número total de elementos.
int  nelpA;// Número de elementos pasivos. Sólido A
int  nelpB;// Número de elementos pasivos. Sólido B
int  nelwA;// Número de elementos cargados. Sólido A
int  nelwB;// Número de elementos cargados. Sólido B
int  nelpc;// Número de elementos en zona potencial de contacto
int  nexA;// Número total de extremos. Sólido A
int  nexB;// Número total de extremos. Sólido B
int  nexT;// Número total de extremos.

int  nel;// Auxiliar montaje cuerpo A-cuerpoB
int  ngl;// Número total de grados de libertad del problema

int  conA[MAX_EL][3];// Tabla de conectividades. Sólido A
int  conB[MAX_EL][3];// Tabla de conectividades. Sólido B
int  conT[MAX_EL][3];// Tabla de conectividades.

int  codA[MAX_ND][2];// Códigos de carga. Sólido A
int  codB[MAX_ND][2];// Códigos de carga. Sólido B
int  codT[MAX_ND];// Codigos genericos
int  cod;// Codigos genericos para el montaje sistema elastico

double  ccA[MAX_EL][10];// Condiciones de contorno cuerpo A
double  ccB[MAX_EL][10];// Condiciones de contorno cuerpo B
double  cc[MAX_EL];// Condiciones de contorno generales para el montaje del sistema

double  exA[MAX_EX][3];// Coordenadas de los extremos. Sólido A
double  exB[MAX_EX][3];// Coordenadas de los extremos. Sólido B
double  exT[MAX_EX][3];// Coordenadas de los extremos.

double  ndA[MAX_ND][3];// Coordenadas de los nodos. Sólido A
double  ndB[MAX_ND][3];// Coordenadas de los nodos. Sólido B
double  ndT[MAX_ND][3];// Coordenadas de los nodos.

double  locA[MAX_ND][9];// Componentes del sistema local en los nodos. Sólido A
double  locB[MAX_ND][9];// Componentes del sistema local en los nodos. Sólido B
double  locT[MAX_ND][9];// Componentes del sistema local en los nodos.


double  gap[MAX_ND];// Gap en los pares de nodos en contacto

double  EA;// Módulo de elasticidad. Sólido A
double  EB;// Módulo de elasticidad. Sólido B
double  ET;// Módulo de elasticidad.
double  Emedia;// Factor de escalado = Módulo de elasticidad medio.

double  nuA;// Módulo de Poisson. Sólido A
double  nuB;// Módulo de Poisson. Sólido B
double  nuT;// Módulo de Poisson.
double  GT;// Módulo de elasticidad transversal.

double  tref;// Temperatura de referencia
double  alA;// Coeficiente de dilatación lineal. Sólido A
double  alB;// Coeficiente de dilatación lineal. Sólido B
double  alT;// Coeficiente de dilatación lineal.
double  lamA;// Conductividad térmica del sólido A
double  lamB;// Conductividad térmica del sólido B
double  diA;// Distorsionabilidad del sólido A
double  diB;// Distorsionabilidad del sólido B

int  TIM;// Tipo de contacto
double  HAmicro;// Microdureza. Sólido A
double  HBmicro;// Microdureza. Sólido B
double  sigA;// Rugosidad. Sólido A
double  sigB;// Rugosidad. Sólido B
double  mA;// Acabado superficial. Sólido A
double  mB;// Acabado superficial. Sólido B

double  M0;// Parámetro del gas
double  kg;// conductividad material en la interfase
double  tTIM;// Espesor de la interfase
double  ETIM;// Módulo de elasticidad interfase

int  tip;// material en despegue
double  hflu;// convección del gas en despegue
double  tflu;// temperatura del gas despegue convección forzada
double  cf;// Coeficiente de fricción

int  simXY;// Flag de simetría respecto del plano xOy
int  simXZ;// Flag de simetría respecto del plano xOz
int  simYZ;// Flag de simetría respecto del plano yOz
int  tpproE;// Flag de tipo de problema elastico
int  tpproT;// Flag de tipo de problema termico
int  tpproTE;// Flag de tipo de problema termoelastico
int  tpcarFP;// Flag de tipo de carga térmica. Fuentes puntuales
int  tpcarFL;// Flag de tipo de carga térmica. Fuentes lineales
int  tpcarFD;// Flag de tipo de carga térmica. Fuentes distribuidas
int  tpcarFC;// Flag de tipo de carga elástica. Fuerza centrífuga
int  tpcarPP;// Flag de tipo de carga elástica. Peso propio




double  AE[3][3];// Coeficientes A elasticos
double  BE[3][3];// Coeficientes B elasticos
double  AT;// Coeficiente A termico
double  BT;// Coeficiente B termico
double  CTE[3];// Coeficientes C termoelasticos
double  DTTE[3];// Coeficientes D termoelasticos
double  DTE[3][3];// Coeficientes D termoelasticos


double** AE_A;double** AE_B;
double** BE_A;double** BE_B;
double** AT_A;double** AT_B;
double** BT_A;double** BT_B;
double** CTE_A;double** CTE_B;
double** DTE_A;double** DTE_B;
/*
double][ allocatable :: AE_A[:][:]][AE_B[:][:]
double][ allocatable :: BE_A[:][:]][BE_B[:][:]
double][ allocatable :: AT_A[:][:]][AT_B[:][:]
double][ allocatable :: BT_A[:][:]][BT_B[:][:]
double][ allocatable :: CTE_A[:][:]][CTE_B[:][:]
double][ allocatable :: DTE_A[:][:]][DTE_B[:][:]*/

double  a[3*MAX_EL][3*MAX_EL];// Matriz del sistema de ecuaciones
double  b[3*MAX_EL];// Términos independientes del sistema de ecuaciones
double  x[3*MAX_EL];// Incognitas del sistema de ecuaciones

int  nT;// Número total de grados de libertad para resolución del sistema
int  nTA;// Número total de elementos de A para resolución del sistema
int  nTpc;// Número total de elementos zona contacto para resolución del sistema

double  tempA[MAX_EL];// Temperatura en el contorno del cuerpo A
double  tempB[MAX_EL];// Temperatura en el contorno del cuerpo B
double  tempT;// Temperatura en los nodos
double  temp[MAX_EL];// Temperatura en el contorno
double  flujA[MAX_EL];// Flujo de calor en el contorno del cuerpo A
double  flujB[MAX_EL];// Flujo de calor en el contorno del cuerpo B
double  fluj[MAX_EL];// Flujo de calor en el contorno
double  flujT;// Flujo en los nodos
double  tf[MAX_EL];// Temperatura fluido convectivo
double  hf[MAX_EL];// Coeficiente de transmisión térmica por convección

double  RTC[MAX_EL];// Vector resistencia térmica de cálculo
double  RTCC[MAX_EL];// Vector resistencia térmica de comparación
int  chires;// chivato de convergencia resistencia termica

double  ve[MAX_EL];// Deslizamiento total relativo
double  anguv[MAX_EL];// Ángulo de deslizamiento
double  ve2[MAX_EL];// Componente 2 del deslizamiento relativo
double  ve3[MAX_EL];// Componente 3 del deslizamiento relativo

double  ndCol[3];// Coordenadas del nodo de colocacion
double  nelInte;// Numero del elemento sobre el que se integra
double  extr[4][3];// Extremos del elemento sobre el que se integra

long int  reg;// Registro del fichero de coeficientes

int  nmiter;// Número máximo de iteraciones
int  iter;// Número total de iteraciones
int  ifla;// Chivato para iteraciones
double  rsq;

double  cte1;// Constante en la integracion elastica
double  cte2;// Constante en la integracion elastica
double  cte3;// Constante en la integracion elastica
double  cte4;// Constante en la integracion termica
double  cte5;// Constante en la integracion termoelastica

FILE*   in1;// Fichero de entrada

int  out1;// Fichero de salida
int  out2;// Fichero de salida
int  out3;// Fichero de salida
int  out4;// Fichero de salida


int  in1s;// Fichero de entrada
int  in2s;// Fichero de entrada
int  in3s;// Fichero de entrada
int  in4s;// Fichero de entrada
int  in5s;// Fichero de entrada
int  in6s;// Fichero de entrada
int  in7s;// Fichero de entrada
int  in8s;// Fichero de entrada
int  in9s;// Fichero de entrada
int  in10s;// Fichero de entrada
int  out1s;// Fichero de salida
FILE*  out2s;// Fichero de salida
FILE*  out3s;// Fichero de salida

int  out11;// Fichero de salida
int  out12;// Fichero de salida

int  out13;// Fichero de salida
int  out14;// Fichero de salida

int  out15;// Fichero de salida
int  out16;// Fichero de salida

int out20;


#endif /* VARIABLES_H_ */

