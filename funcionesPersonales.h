#ifndef FUNCIONESPERSONALES_H_
#define FUNCIONESPERSONALES_H_

void leeEntero(FILE* fp,int* r)
{
	fscanf(fp,"%d",&(*r));
}
void leeDouble(FILE* fp,double* r)
{
	char temp[50];
	fscanf(fp,"%s",temp);

	char *endp;
	*r = strtod(temp,&endp);
	if(*endp == 'D' || *endp == 'd')
	{
		*endp = 'e';
		*r = strtod(temp,&endp);
	}
}
void leeCadena(FILE* fp,char* cad)
{
	fgets(cad,80,fp);
}
void leeLinea(FILE* fp)
{
	char temp[80];
	fgets(temp,80,fp);
}
#endif /* FUNCIONESPERSONALES_H_ */

