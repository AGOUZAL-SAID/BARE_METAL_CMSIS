#include <stdio.h>
void print2(int b){
	int c = b;
	printf("troisiemme variable c %p\n",&c);
}
void print(int a){
	int b=a;
	printf("premier variable b  %p\n",&b);
	print2(b);}
int main(){
	int a=255;
	printf("premier variable a  %p\n",&a);
	print(a);
}
