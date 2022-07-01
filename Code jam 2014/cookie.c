#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void fileinput(FILE *fp, double *, double *, double *);
double compare(double,double,double);
void fileoutput(FILE *ofp, double result, int a);

main(int argc, char *argv[])
{
char ch;
int count=0,i;
FILE *fp;
FILE *ofp;
double c,f,x,result;

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
printf("count = %d\n",count);



for(i=0; i<count; i++)
{
	fileinput(fp,&c,&f,&x);
	result = compare(c,f,x);
	fileoutput(ofp,result,i+1);
	c=0;
	f=0;
	x=0;
}

fclose(fp);
fclose(ofp);

}

void fileinput(FILE *fp, double *c, double *f, double *x)
{
double value;
char ch;
int count=0,i,j;
int power=0;


while( isdigit( ch = fgetc(fp) ) == 0 )
    ;

value = (int)(ch - '0');
for(i=0;i<3;)
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

	if(i==0)
		*c = value/power;
	else if(i==1)
		*f = value/power;
	else
		*x = value/power;
	power = 0;
	i++;
	value=0;
}
}

printf("c = %f f = %f x = %f \n",*c,*f,*x);

}

double compare(double c,double f,double x)
{
double min = x/2;
double result = 0;
double valueadd=c/2;
int i=1;
printf("value %f\n",valueadd + (x/(2 + i*f)));
while(min > (valueadd + (x/(2 + i*f))) )
{
min = valueadd + (x/(2 + i*f));
valueadd = valueadd + (c/(2 + i*f));
i++;

}

return min;
}

void fileoutput(FILE *ofp, double result, int a)
{

printf("Case #%d: %f\n",a,result);
fprintf(ofp,"Case #%d: %f\n",a,result);


}
