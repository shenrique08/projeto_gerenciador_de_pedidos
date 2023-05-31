#include "security.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>




// verifica números consecutivos de qualquer tamanho
bool hasConsecutiveNumbers(const char* password) {
    int length = strlen(password);
    int consecutiveCount = 1;  // Initialize the count of consecutive digits to 1
    for (int i = 0; i < length - 1; i++) {
        if (isdigit(password[i]) && isdigit(password[i + 1])) {
            int firstDigit = password[i] - '0';
            int secondDigit = password[i + 1] - '0';
            if (secondDigit == firstDigit + 1) {
                // Found a consecutive digit
                consecutiveCount++;
                if (consecutiveCount >= 3) {
                    // Found a sequence of consecutive numbers of length 3 or more
                    return true;
                }
            } else {
                // Reset the count of consecutive digits
                consecutiveCount = 1;
            }
        }
    }
    // No consecutive numbers of length 3 or more found
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
