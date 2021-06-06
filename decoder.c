#include<stdio.h>
#include<string.h>
#define MAX 6

void decode(char* str,char* decodefile)
{
	FILE* wfp = fopen(decodefile,"w");
	char* token;
	int i=0, frdnum=1 ,len;
	len = strlen(str);
	//프로토콜에 따라 정보를 슬래쉬 단위로 구분하였기 때문에 strtok 함수를 통하여 문장을 파싱
	
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
	// 아이템은 순서대로 나오지 않기 때문에 if문을 활용하여 항목 구분
	// 이후 아이템, 친구리스트, 서명은 '@'를 기준으로 분리
	
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
	//인코딩된 파일을 읽기형태로 오픈

	int count = 0;


	while(fgets(sourse,3000,rfp)!=NULL)
	{
		strcpy(buf[count], sourse); 
		count++;
		//인코딩된 파일을 읽어와 buf 다차원 배열에 저장
	}

	fclose(rfp);

	for(int i=0;i<MAX;i++)
	{
		for(int j=i+1;j<MAX;j++)
		{
			if(strcmp(buf[i],buf[j])==0)
			{
				decode(buf[j],decodefile);
				//변조되지 않은 문장을 탐색했다면 복호화 실행
				return; 
			}
		}
	}
	printf("정상 문장 탐색 실패");
	return;
	
	

}
int main(int argc, char* argv[]){

	/*
	 
	errorCheck 함수를 호출하여 파일을 오픈, 변조 여부 확인 및 복원
	복원이 완료되었다면 decode() 함수를 호출하여 프로토콜에 따라 압축된 파일을 복호화
	
	*/


	errorCheck(argv[1],argv[2]);
	return 0;
	
}

