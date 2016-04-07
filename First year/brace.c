#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
int main(int argc, char*argv[]){
	char s[MAX];
	gets(s);
	int i;
	int len=strlen(s);
	int count1=0;
	int count2=0;
	int count3=0;
	int count4=0;
	int count5=0;
	int count6=0;
	int a=0, b=0,c=0;
	for(i=0;i<len;i++){
		if(s[i]=='('){
			count1++;
		}else if(s[i]==')'){
			count2++;
		}else if(s[i]=='['){
			count3++;
		}else if(s[i]==']'){
			count4++;
		}else if(s[i]=='{'){
			count5++;
		}else if(s[i]=='}'){
			count6++;
		}else{
			return 0;
		}

	}
	a=count1-count2;
	b=count3-count4;
	c=count5-count6;
	a=abs(a);
	b=abs(b);
	c=abs(c);
	if((a+b+c)==0){
		printf("balanced\n");
	}else{
		printf("unbalanced\n");
	}
	

	return 0;
}