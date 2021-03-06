#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void fileinput(FILE *fp, char firstarray[], char secondarray[]);
int compare(char firstarray[], char secondarray[]);
void fileoutput(FILE *ofp, int result, int a);

main(int argc, char *argv[])
{
char ch, firstarray[4] = {0, 0, 0, 0}, secondarray[4] = {0, 0, 0, 0};
int count=0,i,j,result;
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
	fileinput(fp,firstarray,secondarray);
	result = compare(firstarray,secondarray);
	fileoutput(ofp,result,i+1);
for(j=0; j<4; j++)
{
firstarray[j] = 0;
secondarray[j] = 0;
}
}

fclose(fp);
fclose(ofp);

}

void fileinput(FILE *fp, char firstarray[], char secondarray[])
{
int first;
char ch;
int count=0,i,j;

for(j=0; j<2; j++)
{
count=0;
while( isdigit( ch = fgetc(fp) ) == 0 )
    ;
first = (int)(ch - '0');
printf("first = %d\n",first);
while(count<first)
{
	if((ch = fgetc(fp)) == '\n')
		count++;
}

for(i=0;i<4;)
{
if(isdigit(ch = fgetc(fp)) != 0)
{
	if(j == 0)
	firstarray[i] = firstarray[i]*10 + (ch - '0');
	else
	secondarray[i] = secondarray[i]*10 + (ch - '0');
}
if(ch == ' ' || ch == '\n')
	i++;
}

while(count<4)
{
	if((ch = fgetc(fp)) == '\n')
		count++;
}
}
printf("firstarray = %d %d %d %d\n",firstarray[0],firstarray[1],firstarray[2],firstarray[3]);
printf("secondarray = %d %d %d %d\n",secondarray[0],secondarray[1],secondarray[2],secondarray[3]);

}

int compare(char firstarray[], char secondarray[])
{
int flag = 0;
int result = 0;
int i,j;

for(i=0; i<4; i++)
{
for(j=0; j<4; j++)
{
	if(firstarray[i] == secondarray[j])
	{
		if(flag==0)
		{
			flag = 1;
			result = firstarray[i];
		}
		else
		{
			return 17;
		}
	}
}
}

return result;
}

void fileoutput(FILE *ofp, int result, int a)
{
switch (result)
{
case 0:
printf("Case #%d: Volunteer cheated!\n",a);
fprintf(ofp,"Case #%d: Volunteer cheated!\n",a);
break;
case 17:
printf("Case #%d: Bad magician!\n",a);
fprintf(ofp,"Case #%d: Bad magician!\n",a);
break;
default:
printf("Case #%d: %d\n",a,result);
fprintf(ofp,"Case #%d: %d\n",a,result);
}

}
