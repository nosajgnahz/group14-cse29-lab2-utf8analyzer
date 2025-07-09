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

uint32_t next_utf8_codepoint(const char *s, int *bytes);
bool is_animal_emoji(uint32_t codepoint);
void print_utf8_codepoint(uint32_t codepoint);



// Step 8
uint32_t next_utf8_codepoint(const char *s, int *bytes) {
    unsigned char c = (unsigned char)s[0];
    if (c < 0x80) {
        *bytes = 1;
        return c;
    } else if ((c >> 5) == 0x6) { // 2-byte
        *bytes = 2;
        return ((c & 0x1F) << 6) | (s[1] & 0x3F);
    } else if ((c >> 4) == 0xE) { // 3-byte
        *bytes = 3;
        return ((c & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
    } else if ((c >> 3) == 0x1E) { // 4-byte
        *bytes = 4;
        return ((c & 0x07) << 18) | ((s[1] & 0x3F) << 12) |
               ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
    } else {
        *bytes = 1;
        return 0xFFFD;
    }
}

//Step 9
bool is_animal_emoji(uint32_t codepoint) {
    return codepoint >= 0x1F400 && codepoint <= 0x1F43F;
}

void print_utf8_codepoint(uint32_t codepoint) {
    if (codepoint <= 0x7F) {
        putchar(codepoint);
    } else if (codepoint <= 0x7FF) {
        putchar(0xC0 | (codepoint >> 6));
        putchar(0x80 | (codepoint & 0x3F));
    } else if (codepoint <= 0xFFFF) {
        putchar(0xE0 | (codepoint >> 12));
        putchar(0x80 | ((codepoint >> 6) & 0x3F));
        putchar(0x80 | (codepoint & 0x3F));
    } else {
        putchar(0xF0 | (codepoint >> 18));
        putchar(0x80 | ((codepoint >> 12) & 0x3F));
        putchar(0x80 | ((codepoint >> 6) & 0x3F));
        putchar(0x80 | (codepoint & 0x3F));
    }
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



    const char *str = argv[1];
    int pos = 0, byte_count;
    uint32_t codepoint;
    int index = 0;
    uint32_t index3_cp = 0;

    printf("Animal emojis: ");
    while (str[pos]) {
        codepoint = next_utf8_codepoint(&str[pos], &byte_count);

        if (is_animal_emoji(codepoint)) {
            print_utf8_codepoint(codepoint);
        }

        if (index == 3) {
            index3_cp = codepoint;
        }

        pos += byte_count;
        index++;
    }

    printf("\nNext character of Codepoint at index 3: ");
    if (index3_cp) {
        print_utf8_codepoint(index3_cp + 1);
        printf(" (U+%04X)", index3_cp + 1);
    } else {
        printf("Invalid or too short input.");
    }
    printf("\n");

    return 0;
}
