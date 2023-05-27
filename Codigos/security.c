#include "security.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>




// Function to check if a password contains a sequence of consecutive numbers
bool hasConsecutiveNumbers(const char* password) {
    int length = strlen(password);
    for (int i = 0; i < length - 2; i++) {
        if (isdigit(password[i]) && isdigit(password[i + 1]) && isdigit(password[i + 2])) {
            int firstDigit = password[i] - '0';
            int secondDigit = password[i + 1] - '0';
            int thirdDigit = password[i + 2] - '0';
            if (secondDigit == firstDigit + 1 && thirdDigit == secondDigit + 1) {
                // Found a sequence of consecutive numbers
                return true;
            }
        }
    }
    // No consecutive numbers found
    return false;
}



// Function to check if a password contains any special characters
bool hasSpecialCharacters(const char* password) {
    int length = strlen(password);
    for (int i = 0; i < length; i++) {
        if (!isalnum(password[i])) {
            // Found a special character
            return true;
        }
    }
    // No special characters found
    return false;
}



// Function to check if a password contains at least one uppercase letter
bool hasUppercaseLetter(const char* password) {
    int length = strlen(password);
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) {
            // Found an uppercase letter
            return true;
        }
    }
    // No uppercase letter found
    return false;
}




// Function to check if a password contains at least one lowercase letter
bool hasLowercaseLetter(const char* password) {
    int length = strlen(password);
    for (int i = 0; i < length; i++) {
        if (islower(password[i])) {
            // Found a lowercase letter
            return true;
        }
    }
    // No lowercase letter found
    return false;
}



// Function to check if a password meets the minimum length requirement
bool hasMinimumLength(const char* password, int minLength) {
    int length = strlen(password);
    return length >= minLength;
}




// Function to check if a password contains at least one number
bool hasNumber(const char* password)
{
    int length = strlen(password);
    for (int i = 0; i < length; i++) {
        if (isdigit(password[i])) {
            // Found a number
            return true;
        }
    }
    // No number found
    return false;
}
