#ifndef AFUNCS_H
#define AFUNCS_H
#include "a_macro.cpp"

class AFuncs
{
public:
    AFuncs();

    double getSigmoid(double x, double tilt, double bias = -0.5);
    bool matrixMul(int l1, int r1, int a1[], int l2, int r2, int a2[], int lRes, int rRes, int result[]);
    bool matrixMul(int l1, int r1, float a1[], int l2, int r2, float a2[], int lRes, int rRes, float result[]);
    bool matrixMul(int l1, int r1, double a1[], int l2, int r2, double a2[], int lRes, int rRes, double result[]);
    bool matrixMul(int a1[], int len1, int l2, int r2, int a2[],  int result[]);
    bool matrixMul(double a1[], int len1, int l2, int r2, double a2[],  double result[]);
    bool matrixMul(float a1[], int len1, int l2, int r2, float a2[], float result[]);
    double getSigmoid(double arrX[], int len, double tilt, double bias = -0.5);
private:

};

#endif // AFUNCS_H
