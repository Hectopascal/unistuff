//PeiChen HSU, z5014198
//26/08/15
//hw1 assignment
//print out triangle
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float area(float x1,float y1, float x2, float y2, float x3, float y3){

   return fabs((x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2))/2);
}

float inside(float x1,float y1, float x2, float y2, float x3, float y3, float x, float y){
   float Tol=0.00000001;   
   float A=area(x1,y1,x2,y2,x3,y3);
   float A1=area(x,y,x2,y2,x3,y3);
   float A2=area(x1,y1,x,y,x3,y3);
   float A3=area(x1,y1,x2,y2,x,y);
   float B=A1+A2+A3;
   return (A>B-Tol && A<B+Tol);

}
/*
float recA(float x1,float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y){
   float Tol=0.00000001;

   float a1=sqrt(pow(x1-x2, 2.0)+pow(y1-y2, 2.0));
   float a2=sqrt(pow(x2-x3, 2.0)+pow(y2-y3, 2.0));
   float a3=sqrt(pow(x3-x4, 2.0)+pow(y3-y4, 2.0));
   float a4=sqrt(pow(x4-x1, 2.0)+pow(y4-y1, 2.0));

   float b1=sqrt(pow(x1-x, 2.0)+pow(y1-y,2.0));
   float b2=sqrt(pow(x2-x, 2.0)+pow(y2-y,2.0));
   float b3=sqrt(pow(x3-x, 2.0)+pow(y3-y,2.0));
   float b4=sqrt(pow(x4-x, 2.0)+pow(y4-y,2.0));

   float A=a1*a2=a2*a3=a3*a4=a4*a1;
   float u1=(a1+b1+b2)/2;
   float u2=(a2+b2+b3)/2;
   float u3=(a3+b3+b4)/2;
   float u4=(a4+b4+b1)/2;

   float A1=sqrt(u1*(u1-a1)*(u1-b1)*(u1-b2));
   float A2=sqrt(u2*(u2-a2)*(u2-b2)*(u2-b3));
   float A3=sqrt(u3*(u3-a3)*(u3-b3)*(u3-b4));
   float A4=sqrt(u4*(u4-a4)*(u4-b4)*(u4-b1));

   float B=A1+A2+A3+A4;
   return (A>B-Tol && A<B+Tol);


}
*/
int main(int argc, char* argv[]){
	int row, column;
	float xmin, ymin, xmax, ymax, x1, y1, x2, y2, x3, y3;

	scanf("%d", &row);
	scanf("%d", &column);
	scanf("%f", &xmin);
	scanf("%f", &ymin);
	scanf("%f", &xmax);
	scanf("%f", &ymax);
	scanf("%f", &x1);
	scanf("%f", &y1);
	scanf("%f", &x2);
	scanf("%f", &y2);
	scanf("%f", &x3);
	scanf("%f", &y3);
	/*
	x1=x1+'0';
	y1=y1+'0';
	x2=x2+'0';
	y2=y2+'0';
	x3=x3+'0';
	y3=y3+'0';
	*/
	
	int i;
	int j;
	for(i=0; i<row+2;i++){
		printf("\n");
		for(j=0; j<column+2; j++){
			if((i==0 && j==0)|| (i==row+1 && j==0)||
                        (i==0 && j==column+1)||(i==row+1 && j==column+1)){

				printf("+");
			}else if(i==0 || i==row+1){
				printf("-");
			}else if(j>0 && j<column+1){
				printf(" ");
			}else{
				printf("|");
			}
		}
		
	}
	int x, y;
	for(y=1; y<row; y++){
		for(x=1;x<column;x++){
			if(inside(x1,y1,x2,y2,x3,y3,x,y)){
				printf("*");
         		/*
         		if(rectangle(x1,y1,row,column)||rectangle(x2,y2,row,column)||rectangle(x3,y3,row,column)){
               		printf("*");
         		}
         		*/
 
   			}else{
         		     printf(" ");
   			}
		}
	}
	
        printf("\n");
	return EXIT_SUCCESS;
}
