#include "operators.h"
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double opAdd(double a, double b) {
    return a + b;
}

double opSubtract(double a, double b) {
    return a - b;
}

double opMultiply(double a, double b) {
    return a * b;
}

double opDivide(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return a / b;
}

double opMod(double a, double b) {
    if (b == 0) {
        printf("Error: Modulo by zero\n");
        return 0;
    }
    return fmod(a, b);
}

double opAbs(double a) {
    return fabs(a);
}

double opFloor(double a) {
    return floor(a);
}

double opCeiling(double a) {
    return ceil(a);
}

double opSqrt(double a) {
    if (a < 0) {
        printf("Error: Square root of negative number\n");
        return 0;
    }
    return sqrt(a);
}

double opSin(double degrees) {
    return sin(degrees * M_PI / 180.0);
}

double opCos(double degrees) {
    return cos(degrees * M_PI / 180.0);
}

double opRandom(double min, double max) {
    if (min > max) {
        double temp = min;
        min = max;
        max = temp;
    }
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

bool opLessThan(double a, double b) {
    return a < b;
}

bool opGreaterThan(double a, double b) {
    return a > b;
}

bool opEquals(double a, double b) {
    return fabs(a - b) < 0.0001;
}

bool opAnd(bool a, bool b) {
    return a && b;
}

bool opOr(bool a, bool b) {
    return a || b;
}

bool opNot(bool a) {
    return !a;
}

int stringLength(const char* str) {
    return (int)strlen(str);
}

char letterOf(const char* str, int index) {
    if (index < 1 || index > (int)strlen(str)) {
        printf("Error: Invalid string index\n");
        return '\0';
    }
    return str[index - 1];
}

void joinStrings(const char* str1, const char* str2, char* result, int maxLen) {
    strncpy(result, str1, maxLen - 1);
    result[maxLen - 1] = '\0';
    int len1 = strlen(result);
    if (len1 < maxLen - 1) {
        strncat(result, str2, maxLen - len1 - 1);
    }
}
