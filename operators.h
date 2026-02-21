#ifndef OPERATORS_H
#define OPERATORS_H

// Math operators
double opAdd(double a, double b);
double opSubtract(double a, double b);
double opMultiply(double a, double b);
double opDivide(double a, double b);
double opMod(double a, double b);
double opAbs(double a);
double opFloor(double a);
double opCeiling(double a);
double opSqrt(double a);
double opSin(double degrees);
double opCos(double degrees);
double opRandom(double min, double max);

// Comparison operators
bool opLessThan(double a, double b);
bool opGreaterThan(double a, double b);
bool opEquals(double a, double b);

// Logical operators
bool opAnd(bool a, bool b);
bool opOr(bool a, bool b);
bool opNot(bool a);

// String operators
int stringLength(const char* str);
char letterOf(const char* str, int index);
void joinStrings(const char* str1, const char* str2, char* result, int maxLen);

#endif
