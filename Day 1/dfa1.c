#include<stdio.h>
#include<string.h>

int main(){
	char input[100];
	printf("Enter a binary string: ");
	scanf("%s", input);
	
	int state = 0;
	
	for(int i=0; i<strlen(input); i++){
	char c = input[i];
	if(c != '0' && c != '1'){
		printf("Invalid input");
		return 1;
	}
	
	switch(state){
		case 0:
			if(c == '0') state = 2;
			else state = 1;
			break;
		case 1:
			if(c == '0') state = 3;
			else state = 0;
			break;
		case 2:
			if(c == '1') state = 3;
			else state = 0;
			break;
		case 3:
			if(c == '1') state = 2;
			else state = 1;
			break;
		}
	}
	
	if(state == 3){
		printf("The string contains an odd number of 1's and 0's");
	}
	else{
		printf("The string does not contain odd number of 1's and 0's");
	}
	
	return 0;
}
			
		


