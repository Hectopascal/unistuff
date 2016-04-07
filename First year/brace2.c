#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
int main(int argc, char*argv[]){
	char s[MAX];
	gets(s);
	int i;
	int len=strlen(s);
	int result=0;
	for(i=0;i<len;i++){
		for(int j=len-1;j>=0;j--){
			if((s[i]=='(')&&(s[j]==')')){
				result=0;
			}else if((s[i]=='[')&&(s[j]==']')){
				result=0;
			}else if((s[i]=='{')&&s[j]=='}'){
				result=0;
			}else{
				result=1;
			}
		}
	}
	if(result==0){
		printf("Balanced\n");
	}else{
		printf("Unbalanced\n");
	}

	return 0;
}