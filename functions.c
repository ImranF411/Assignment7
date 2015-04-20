#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char* factor (char* number);
char* fibonacci (char* number);
char* add (char* number1, char* number2);
char* subtract (char* number1, char* number2);
char* multiply(char* number1, char* number2);
char* divide(char* number1, char* number2);
char* exponent(char* number, char* exponent);
int isPrime(int number);

int not_main(int argc, char** argv){
	fibonacci("22");
	return 0;
}

char* factor (char* number){
	char retchar = malloc(1000);
	char tempchar = malloc(50);
	float f = 0;
	int i = 0;
	f = (float)atof(number);

	if(f == 0){
		printf("Cannot factor, bad input\n");
		return;
	}

	while( i < strlen(number)){   //(sizeof(number)/sizeof(char*))){
		if(number[i] == '.'){
			printf("Cannot factor, bad input\n");
			return;
		}
		i++;
	}	
	
	i = 1;
	int facnumber = f;
	while(i <= facnumber){
		if(facnumber % i == 0){	
			sprintf(tempchar, "%d", i);
			if(i != 1){
				strcat(retchar, tempchar);
				strcat(retchar, "\n");
			}else{
				strcpy(retchar, tempchar);
				strcat(retchar, "\n");
			}
		}
		i++;
	}
	return retchar;
}

char* fibonacci(char* number){
	char retchar = malloc(1000);
	char tempchar = malloc(50);
	float f = 0;
	int i = 0;
	f = (float)atof(number);

	if(f == 0){
		printf("Cannot fibnoacci, bad input\n");
		return;
	}

	while( i < strlen(number)){   //(sizeof(number)/sizeof(char*))){
		if(number[i] == '.'){
			printf("Cannot factor, bad input\n");
			return;
		}
		i++;
	}	
	
	int j = 1;
	int k = 1;
	int l = 0;
	int index = 0;
	sprintf(tempchar, "%d", j);
	strcpy(retchar, tempchar);
	strcat(retchar, "\n");
	while(index < f-1){

		sprintf(tempchar, "%d", k);
		strcat(retchar, tempchar);
		strcat(retchar, "\n");

		l = k;
		k = k + j;
		j = l;
		index++;
	}
	printf("%s", retchar);
	return retchar;
}

char* add (char* number1, char* number2){	
	char retchar = malloc(1000);
	float f1 = 0, f2 = 0, f3 = 0;
	f1 = (float)atof(number1);
	f2 = (float)atof(number2);
	
	f3 = f1 + f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* subtract (char* number1, char* number2){
	char retchar = malloc(1000);
	float f1 = 0, f2 = 0, f3 = 0;
	f1 = (float)atof(number1);
	f2 = (float)atof(number2);
	
	f3 = f1 - f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* multiply(char* number1, char* number2){
	char retchar = malloc(1000);
	float f1 = 0, f2 = 0, f3 = 0;
	f1 = (float)atof(number1);
	f2 = (float)atof(number2);
	
	f3 = f1 * f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* divide(char* number1, char* number2){
	char retchar = malloc(1000);
	float f1 = 0, f2 = 0, f3 = 0;
	f1 = (float)atof(number1);
	f2 = (float)atof(number2);

	if(f2 == 0){
		printf("Cannot divide by 0\n");
		return;
	}

	f3 = f1/ f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* exponent(char* number, char* exponent){
	char retchar = malloc(1000);
	float f1 = 0, f2 = 0, f3 = 0;
	f1 = (float)atof(number);
	f2 = (float)atof(exponent);
	
	f3 = pow(f1, f2);
	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

int isPrime(int number){
	int i;
	for(i = 2; i < number; i++){
		if(number % i == 0 && i != number)
			return 0;
	}
	return 1;
}
