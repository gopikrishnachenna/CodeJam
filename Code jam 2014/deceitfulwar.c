#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void fileinput(FILE *fp, double *, double *, int *);
int war(double *,double *,int);
double findmax(double *,double ,int);
double findmin(double *,double ,int);
int deceitfulwar(double *,double *,int);
void fileoutput(FILE *ofp, int result,int dresult, int a);

#define MAX 1000

main(int argc, char *argv[])
{
char ch;
int count=0,i;
FILE *fp;
FILE *ofp;
double naomiarray[MAX],kenarray[MAX];
int n;
int result=0,dresult=0;

if(argc != 2)
	printf("Error in the arguments\n");

fp = fopen(argv[1],"r");
ofp = fopen("Yosha","w");

if( fp == NULL )
    printf("Error while opening the file.\n");

if( ofp == NULL )
    printf("Error while opening the file.\n");

while( isdigit( ch = fgetc(fp) ) == 0 )
    ;
count = (int)(ch - '0');
while( isdigit( ch = fgetc(fp) ) != 0 )
    count = (count*10) + (int)(ch - '0');
//printf("count = %d\n",count);                                                                        /* print main count */



for(i=0; i<count; i++)
{
	fileinput(fp,naomiarray,kenarray,&n);

	dresult = deceitfulwar(naomiarray,kenarray,n);
	result = war(naomiarray,kenarray,n);

	fileoutput(ofp,result,dresult,i+1);

}

fclose(fp);
fclose(ofp);

}

void fileinput(FILE *fp, double *na, double *ka, int *n)
{
double value;
char ch;
int count=0,i,j;
int power=0;
int nu;

while( isdigit( ch = fgetc(fp) ) == 0 )
    ;
nu = (int)(ch - '0');
while( isdigit( ch = fgetc(fp) ) != 0 )
    nu = (nu*10) + (int)(ch - '0');
//printf("count = %d\n",nu);                                                             /* print N */

*n = nu;

while( isdigit( ch = fgetc(fp) ) == 0 )
    ;

value = (int)(ch - '0');
for(i=0;i<nu;)
{
if(isdigit(ch = fgetc(fp)) != 0)
{

	//printf("after decimal ch = %c\n",ch);
	power = power*10;
	value = value*10 + (int)(ch - '0');
}
	if (ch == '.')
		power = 1;
//printf("value after decimal = %f\n",value);
//printf("power = %d\n",power);
if(ch == ' ' || ch == '\n')
{

	na[i] = value/power;
	power = 0;
	i++;
	value=0;
}
}

while( isdigit( ch = fgetc(fp) ) == 0 )
    ;

value = (int)(ch - '0');
for(i=0;i<nu;)
{
if(isdigit(ch = fgetc(fp)) != 0)
{

	//printf("after decimal ch = %c\n",ch);
	power = power*10;
	value = value*10 + (int)(ch - '0');
}
	if (ch == '.')
		power = 1;
//printf("value after decimal = %f\n",value);
//printf("power = %d\n",power);
if(ch == ' ' || ch == '\n')
{

	ka[i] = value/power;
	power = 0;
	i++;
	value=0;
}
}

//printf("number = %d ",*n);                                                                 /* print N */

for(i=0; i<nu; i++)
	;
	//printf("%f %f, ",na[i],ka[i]);                                                  /* print input */
//printf("\n");                                                                             /* print input */
}



void fileoutput(FILE *ofp, int result, int dresult, int a)
{

printf("Case #%d: %d %d\n",a,dresult,result);
fprintf(ofp,"Case #%d: %d %d\n",a,dresult,result);


}

int war(double *na,double *kaa,int number)
{
int count=0;
int i,j;
double min, minl;
int flag, flagl;
double ka[MAX];

for(i=0; i<number; i++)
{
ka[i] = kaa[i];
}

for(i=0; i<number; i++)
{
	min = 1.0;
	minl = 1.0;
	flag = -1;
	for(j=0; j<number; j++)
	{
		if(ka[j] > na[i] && min > ka[j])
		{
			min = ka[j];
			flag = j;
		}
		if(ka[j] < minl && ka[j] > 0.0)
		{
			minl = ka[j];
			flagl = j;
		}
	}
	//printf("%f   %f\n",na[i],((flag == -1) ? ka[flagl] : ka[flag]));                               /* print for war*/
	if(flag != -1)
	{
		count++;
		ka[flag] = 0.0;
	}
	else
	{
		ka[flagl] = 0.0;
	}

}

return (number - count);
}

int deceitfulwar(double *na,double *ka,int number)
{

double minn = na[0], maxn = na[0];
double mink = ka[0], maxk = ka[0];
int i,count = 0;

for(i=0; i<number; i++)
{
if (minn > na[i])
	minn = na[i];

if (maxn < na[i])
	maxn = na[i];
}

for(i=0; i<number; i++)
{
if (mink > ka[i])
	mink = ka[i];

if (maxk < ka[i])
	maxk = ka[i];
}

	printf("(%f %f) (%f %f)\n",minn,maxn,mink,maxk);

for(i=0; i<number; i++)
{
	if(minn < mink)
	{
	printf("%f                    %f\n",minn,maxk);
	minn = findmin(na,minn,number);
	maxk = findmax(ka,maxk,number);

	if(minn > maxk)
	{
		i++;
		break;
	}	
	}
	else 
	{
	printf("%f                    %f\n",minn,mink);
	minn = findmin(na,minn,number);
	mink = findmin(ka,mink,number);
	
	count++;
	}
}

count = count + number - i;

return count;
}

double findmax(double *ka,double maxk, int number)
{
int i;
double result = 0.0;
for(i=0; i<number; i++)
	if(ka[i] < maxk && ka[i] > result)
		result = ka[i];
return result;
}

double findmin(double *ka,double maxk, int number)
{
int i;
double result = 1.0;
for(i=0; i<number; i++)
	if(ka[i] > maxk && ka[i] < result)
		result = ka[i];
return result;
}
