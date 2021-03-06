#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void fileinput(FILE *fp, int *r, int *c, int *m);
int possible(int r, int c, int m);
void fileoutput(FILE *ofp, int result, int a, int r, int c, int m);
void printarray(int r, int c, int m);
void onenumber(FILE *ofp,int r,int c,int a);
void singlerow(FILE *ofp,int r,int c,int m,int a);
void doublerow(FILE *ofp,int r,int c,int m,int a);
void hell(FILE *ofp,int r,int c,int m,int a);

main(int argc, char *argv[])
{
char ch;
int count=0,i,result, r, c, m;
FILE *fp;
FILE *ofp;

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
	fileinput(fp,&r, &c, &m);
	result = possible(r,c,m);
/*	if (result)
		printf("Possible.\n");
	else
		printf("Impossible.\n"); */
	fileoutput(ofp,result,i+1, r, c, m);
}

fclose(fp);
fclose(ofp);

}

void fileinput(FILE *fp, int *c, int *f, int *x)
{
double value;
char ch;
int count=0,i,j;



while( isdigit( ch = fgetc(fp) ) == 0 )
    ;

value = (int)(ch - '0');
for(i=0;i<3;)
{
if(isdigit(ch = fgetc(fp)) != 0)
{
	value = value*10 + (int)(ch - '0');
}

//printf("value after decimal = %f\n",value);
//printf("power = %d\n",power);
if(ch == ' ' || ch == '\n')
{

	if(i==0)
		*c = value;
	else if(i==1)
		*f = value;
	else
		*x = value;
	i++;
	value=0;
}
}

//printf("r = %d c = %d m = %d \n",*c,*f,*x);

}

int possible(int r, int c, int m)
{
int number;

number = (r*c) - m;

if (number == 1)
	return 1;
if (r == 1 || c == 1)
	return 2;
if ((r == 2 || c == 2))
	if(number%2 == 0 && number > 3)
		return 3;
	else
		return 0;
if (number > 7 || number == 4 || number == 6)
	return 4;


return 0;
}

void fileoutput(FILE *ofp, int result, int a, int r, int c, int m)
{
switch (result)
{
case 0:
	fprintf(ofp,"Case #%d:\nImpossible\n",a);
	break;
case 1:
	onenumber(ofp,r,c,a);
	break;
case 2:
	singlerow(ofp,r,c,m,a);
	break;
case 3:
	doublerow(ofp,r,c,m,a);
	break;
default:
	hell(ofp,r,c,m,a);
}
	//fprintf(ofp,"%dx%d m = %d n = %d\n\n",r,c,m,(r*c)-m);
}

void onenumber(FILE *ofp,int r,int c,int a)
{
int i,j;

fprintf(ofp,"Case #%d:\n",a);

for(i=0; i<r; i++)
{
	for(j=0; j<c; j++)
	{
		if(j==0 && i==0)
		{
			fprintf(ofp,"c");
			continue;
		}
		else
		{
			fprintf(ofp,"*");
		}	

	}
	fprintf(ofp,"\n");
}
}

void singlerow(FILE *ofp,int r,int c,int m,int a)
{
int i,j;
int number;

fprintf(ofp,"Case #%d:\n",a);

number = (r*c) - m - 1;

for(i=0; i<r; i++)
{
	for(j=0; j<c; j++)
	{
		if(j==0 && i==0)
		{
			fprintf(ofp,"c");
			continue;
		}
		else
		{
			if(number)
			{
				fprintf(ofp,".");
				number--;			
				continue;
			}
			else
				fprintf(ofp,"*");
		}	

	}
	fprintf(ofp,"\n");
}
}

void doublerow(FILE *ofp,int r,int c,int m,int a)
{
int i,j;
int number, count;

//printf("%d : double row\n",a);

fprintf(ofp,"Case #%d:\n",a);

number = (r*c) - m;

count = (number/2);

for(i=0; i<r; i++)
{
	for(j=0; j<c; j++)
	{
		if(j==0 && i==0)
		{
			fprintf(ofp,"c");
			continue;
		}
		else
		{
			if(c == 2 && i < count)
			{
				fprintf(ofp,".");			
				continue;
			}
			else if(r == 2 && j < count)
			{
				fprintf(ofp,".");			
				continue;
			}
			else
				fprintf(ofp,"*");
		}	

	}
	fprintf(ofp,"\n");
}
}

void hell(FILE *ofp,int r,int c,int m,int a)
{
int number;
int i,j;
int count, flag=0, incount;
int colcount=0, rowcount=0;

number = (r*c) - m;

fprintf(ofp,"Case #%d:\n",a);

count = number - 8;

if((((count%2) != 0) && (count > 0)) || ((count > ((2*(c-3)) + (2*(r-3))))))
	flag=1;

if(count == 0)
	flag = 0;

incount = count -  (2*(c-3)) - (2*(r-3)) - flag; 

if(incount < 0)
	incount = 0;

count = count - flag;

if(count)
{
if(count <= (2*(c-3)))
	colcount = count/2;

if((count - (2*(c-3))) <= (2*(r-3)) && (count - (2*(c-3))) >= 0)
	rowcount = (count - (2*(c-3)))/2;
}



printf("number = %d count = %d rowcount = %d colcount = %d incount = %d flag = %d\n",number,count,rowcount,colcount,incount,flag);

for(i=0; i<r; i++)
{
	for(j=0; j<c; j++)
	{
		if(j==0 && i==0)
		{
			fprintf(ofp,"c");
			continue;
		}
		if(j<3 && i<3)
		{
			if(number == 4)
			{
				if(j<2 && i<2)
				{
					fprintf(ofp,".");
					continue;
				}
				else
				{
					fprintf(ofp,"*");
					continue;
				}
			}
			if(number == 6)
			{
				if(j<3 && i<2)
				{
					fprintf(ofp,".");
					continue;
				}
				else
				{
					fprintf(ofp,"*");
					continue;
				}
			}
			if(flag == 0 && j == 2 && i == 2)
			{
				fprintf(ofp,"*");
				continue;
			}	
			if(number != 4 && number != 6)
			{
				fprintf(ofp,".");
				continue;
			}

		}
		else if(number > 9)
		{
			if(colcount != 0)
			{
				if((j-2) <= colcount && i < 2)
				{
					fprintf(ofp,".");
					continue;
				}
				else
				{
					fprintf(ofp,"*");
					continue;
				}
			}
			if(rowcount != 0)
			{
				if(i < 2)
				{
					fprintf(ofp,".");
					continue;
				}
				else if((i-2) <= rowcount && j < 2)
				{
					fprintf(ofp,".");
					continue;
				}
				else
				{
					fprintf(ofp,"*");
					continue;
				}
			}
			if(colcount == 0 && i<2 && count > 0)
			{
				fprintf(ofp,".");
				continue;
			}
			if(rowcount == 0 && j<2 && count > 0)
			{
				fprintf(ofp,".");
				continue;
			}
			if(incount)
			{

				fprintf(ofp,".");
				incount--;
			}
			else
			{
				fprintf(ofp,"*");
			}
		}
		else
		{
			fprintf(ofp,"*");
		}	

	}
	fprintf(ofp,"\n");
}
}

