#include<stdio.h>
#include<string.h>
#define MAX 6

void decode(char* str,char* decodefile)
{
	FILE* wfp = fopen(decodefile,"w");
	char* token;
	int i=0, frdnum=1 ,len;
	len = strlen(str);
		
	token = strtok(str,"/");
	fprintf(wfp,"*USER STATUS*\nID: ");
	fprintf(wfp,"%s\nNAME: ",token);
	token = strtok(NULL,"/");
	fprintf(wfp,"%s\nGENDER: ",token);
	token = strtok(NULL,"/");
	if(strcmp(token,"F")==0) fprintf(wfp,"FEMALE\nAGE: ");
	else fprintf(wfp,"FEMALE\nAGE: ");
	token = strtok(NULL,"/");		
	fprintf(wfp,"%s\nHP: ",token);
	token = strtok(NULL,"/");
	fprintf(wfp,"%s\nMP: ",token);
	token = strtok(NULL,"/");
	fprintf(wfp,"%s\nCOIN: ",token);
	token = strtok(NULL,"/");
	fprintf(wfp,"%s\n\n",token);

	/*---ITEM---*/	
	fprintf(wfp,"*ITEMS*\n");
	token = strtok(NULL,"/");

	while(strcmp(token,"@")!=0){
		if(strncmp(token,"BM",2)==0){
			
			token = strtok(NULL,"/");
			fprintf(wfp,"BOMB: %s\n",token);
		}
		else if(strncmp(token,"PN",2)==0){
			token = strtok(NULL,"/");
			fprintf(wfp,"POTION: %s\n",token);
		}
		else if(strncmp(token,"CR",2)==0){
			token = strtok(NULL,"/");
			fprintf(wfp,"CURE: %s\n",token);
		}
		else if(strncmp(token,"CN",2)==0){
			token = strtok(NULL,"/");
			fprintf(wfp,"CANNON: %s\n",token);
		}
		else if(strncmp(token,"BK",2)==0){
			token = strtok(NULL,"/");
			fprintf(wfp,"BOOK: %s\n",token);
		}
		else if(strncmp(token,"SD",2)==0){
			token = strtok(NULL,"/");
			fprintf(wfp,"SHIELD: %s\n",token);
		}
		else break;
	
		
		token = strtok(NULL,"/");
	}

	/*---FRIEND LIST---*/
	token = strtok(NULL,"/");	
	fprintf(wfp,"\n*FRIENDS LIST*\n");
	
	while(strcmp(token,"@")!=0){
	fprintf(wfp,"FRIEND%d ID: %s\n",frdnum,token);
	token = strtok(NULL,"/");
	fprintf(wfp,"FRIEND%d NAME: %s\n",frdnum,token);
	token = strtok(NULL,"/");
	if(strcmp(token,"F")==0) fprintf(wfp,"FRIEND%d GENDER: FEMALE\n",frdnum);
	else fprintf(wfp,"FRIEND%d GENDER: MALE\n",frdnum);
	token = strtok(NULL,"/");
	fprintf(wfp,"FRIEND%d AGE: %s\n\n",frdnum,token);
	token = strtok(NULL,"/");
	frdnum++;
	}
	
	/*---DESCRIPTION---*/

	fprintf(wfp,"*DESCRIPTION*");
	while(1){
	token = strtok(NULL,"/");
	if(token!=NULL)	fprintf(wfp,"\n%s",token);
	else break;
	}

	fclose(wfp);
	return;
} 

void errorCheck(char* encodefile, char* decodefile){
	
	char sourse[3000];
	char buf[MAX][3000];

	FILE* rfp = fopen(encodefile,"r");
	int count = 0;


	while(fgets(sourse,3000,rfp)!=NULL)
	{
		strcpy(buf[count], sourse); 
		count++;
	}

	fclose(rfp);

	for(int i=0;i<MAX;i++)
	{
		for(int j=i+1;j<MAX;j++)
		{
			if(strcmp(buf[i],buf[j])==0)
			{
				decode(buf[j],decodefile);
				return; 
			} 
		}
	}
	printf("정상 문장 탐색 실패");
	return;
	
	

}
int main(int argc, char* argv[]){

	errorCheck(argv[1],argv[2]);
	return 0;
	
}

