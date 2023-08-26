#include<stdio.h>
#include<string.h>
int main(){
	char string[100];
	printf("enter the string=");
	scanf("%s",&string);
	int n=strlen(string);
	if(string[0]=='/')
	{
		if(string[1]=='/'){
			printf("it is a comment");
		}
		else if(string[1]=='*'){
			if(string[n-1]=='/'){
				if(string[n-2]=='*'){
					printf("it is a comment");
				}
				else{
					printf("it is not comment");
				}
			}
			else{
				printf("it is not comment");
			}
		
		}
		else{
		
		printf("it is not comment");
		}
	}
	else{
		printf("it is not comment");
	}
	return 0;
}