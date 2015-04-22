#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

char* factor (char* number);
char* fibonacci (char* number);
char* add (char* number1, char* number2);
char* subtract (char* number1, char* number2);
char* multiply(char* number1, char* number2);
char* divide(char* number1, char* number2);
char* exponent(char* number, char* exponent);
int isPrime(int number);

char retchar[10000];
char tempchar[500];


int not_main(int argc, char** argv){
	factor("123");
	return 0;
}

int numbersOnly(char* toCheck){
	int i;
	for(i = 0;i<strlen(toCheck);i++){
		if(isalpha(toCheck[i]) != 0)
			return -1;		//Character is a letter.
	}
	return 0;				//All characters are not letters.
	
}

char* factor (char* number){
	memset(retchar, 0, sizeof(retchar));
	memset(tempchar, 0, sizeof(tempchar));
	double f = 0;
	int i = 0;
	if(numbersOnly(number) == -1){
		char * letter_found = "Number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	f = strtod(number,NULL);

	if(f == 0){
		char * error_msg = "Cannot factor, bad input\n";
		printf("%s",error_msg);
		return error_msg;
	}

	while( i < strlen(number)){   //(sizeof(number)/sizeof(char*))){
		if(number[i] == '.'){
			char * error_fact = "Cannot factor, bad input\n";
			printf("%s",error_fact);
			return error_fact;
		}
		i++;
	}	
	
	i = 2;
	int facnumber = f;
	while(i <= facnumber){
		if(facnumber % i == 0 && isPrime(i)){	
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
	printf("%s", retchar);
	return retchar;
}

char* fibonacci(char* number){
	memset(retchar, 0, sizeof(retchar));
	memset(tempchar, 0, sizeof(tempchar));
	double f = 0;
	int i = 0;
	if(numbersOnly(number) == -1){
		char * letter_found = "Number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	f = strtod(number,NULL);

	if(f == 0){
		char * error_zero = "Cannot fibnoacci, bad input\n";
		printf("%s",error_zero);
		return error_zero;
	}

	while( i < strlen(number)){   //(sizeof(number)/sizeof(char*))){
		if(number[i] == '.'){
			char * error_decimal = "Decimal found, bad input\n";
			printf("%s",error_decimal);
			return error_decimal;
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
		if(k < 0){
			char * error_msg = "Overflowing integer. Use smaller number. Stopping here.";
			return error_msg;
		}
		j = l;
		index++;
	}
	printf("%s", retchar);
	return retchar;
}

char* add (char* number1, char* number2){	
	memset(retchar, 0, sizeof(retchar));
	memset(tempchar, 0, sizeof(tempchar));
	double f1 = 0, f2 = 0, f3 = 0;
	if(numbersOnly(number1) == -1){
		char * letter_found = "First number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	if(numbersOnly(number2) == -1){
		char * letter_found = "Second number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	f1 = strtod(number1,NULL);
	f2 = strtod(number2,NULL);
	
	f3 = f1 + f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* subtract (char* number1, char* number2){
	memset(retchar, 0, sizeof(retchar));
	memset(tempchar, 0, sizeof(tempchar));
	double f1 = 0, f2 = 0, f3 = 0;
	if(numbersOnly(number1) == -1){
		char * letter_found = "First number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	if(numbersOnly(number2) == -1){
		char * letter_found = "Second number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	f1 = strtod(number1,NULL);
	f2 = strtod(number2,NULL);
	
	f3 = f1 - f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* multiply(char* number1, char* number2){
	memset(retchar, 0, sizeof(retchar));
	memset(tempchar, 0, sizeof(tempchar));
	double f1 = 0, f2 = 0, f3 = 0;
	if(numbersOnly(number1) == -1){
		char * letter_found = "First number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	if(numbersOnly(number2) == -1){
		char * letter_found = "Second number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	f1 = strtod(number1,NULL);
	f2 = strtod(number2,NULL);
	
	f3 = f1 * f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* divide(char* number1, char* number2){
	memset(retchar, 0, sizeof(retchar));
	memset(tempchar, 0, sizeof(tempchar));
	double f1 = 0, f2 = 0, f3 = 0;
	if(numbersOnly(number1) == -1){
		char * letter_found = "First number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	if(numbersOnly(number2) == -1){
		char * letter_found = "Second number contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	f1 = strtod(number1,NULL);
	f2 = strtod(number2,NULL);

	if(f2 == 0){
		char * error_div_zero = "Cannot divide by 0\n";
		printf("%s",error_div_zero);
		return error_div_zero;
	}

	f3 = f1/ f2;

	sprintf(retchar, "%f", f3);
	strcat(retchar, "\n");
	return retchar;
}

char* exponent(char* number, char* exponent){
	memset(retchar, 0, sizeof(retchar));
	memset(tempchar, 0, sizeof(tempchar));
	double f1 = 0, f2 = 0, f3 = 0;
	if(numbersOnly(number) == -1){
		char * letter_found = "Base contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	if(numbersOnly(exponent) == -1){
		char * letter_found = "Exponent contains a letter. Not performing operation.\n";
		printf("%s",letter_found);
		return letter_found;
	}
	f1 = strtod(number,NULL);
	f2 = strtod(exponent,NULL);
	
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
