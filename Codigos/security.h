#ifndef security_h
#define security_h


#include <stdbool.h>


bool hasConsecutiveNumbers(const char* password);
bool hasSpecialCharacters(const char* password);
bool hasUppercaseLetter(const char* password);
bool hasLowercaseLetter(const char* password);
bool hasMinimumLength(const char* password, int minLength);
bool hasNumber(const char* password);


#endif