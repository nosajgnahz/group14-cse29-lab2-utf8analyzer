#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool allASCII(char string[]){
	bool result = true;
	for(int i=0; i<strlen(string);i++){
		if ((string[i]&0b10000000)!=0b00000000){
			result=false;
		}
	}
	return result;
}

void upperASCII(char string[], char dest[]){
	for(int i=0; i<strlen(string);i++){
		if(string[i]>=97 && string[i]<=122){
			dest[i]=string[i]-32;
		}
		else{
			dest[i]=string[i];
		}
	}
	dest[strlen(string)]=0;
}

int stringByteLen(char string[]){
	return strlen(string);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }
    printf("Valid ASCII: %s\n", allASCII(argv[1])? "true":"false");
    char uppercaseString[strlen(argv[1])+1];
    upperASCII(argv[1],uppercaseString);
    printf("Upercased ASCII: %s\n", uppercaseString);
    printf("Length in bytes: %d\n", stringByteLen(argv[1]));

    // implement the UTF-8 analyzer here
}

