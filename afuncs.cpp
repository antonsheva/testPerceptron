#include "afuncs.h"
#include <cmath>

#define MX_ARR_LEN  10

AFuncs::AFuncs()
{

}


/**
 * @brief AFuncs::getSigmoid for single value
 * @param x         main value
 * @param tilt       tilt of graphic
 * @param bias     bias regarden of start
 * @return
 */
double AFuncs::getSigmoid(double x,  double  tilt, double bias)
{
  double tmp, res;
  tmp = pow( 2.72, -1*(x+bias) * tilt);  //-0.5
  res = (1/(1 + tmp));
  return res;
}

/**
 * @brief AFuncs::getSigmoid  for array
 * @param arrX
 * @param len
 * @param tilt
 * @param bias
 * @return
 */
double AFuncs::getSigmoid(double arrX[], int len,  double  tilt, double bias)
{
  double tmp, res;
  for (int var = 0; var < len; ++var) {
      tmp = pow( 2.72, -1*(arrX[var]+bias) * tilt);  //-0.5
      arrX[var] = (1/(1 + tmp));
  }


  return res;
}

/**
 * @brief AFuncs::matrixMul   - for int
 * @param l1         lines  qty a1[]                structure
 * @param r1         rows qty  a1[]                    B B B B
 * @param a1        first matrix                         B B B B
 * @param l2         lines  qty a2[]              A A
 * @param r2         rows qty  a2[]             A A
 * @param a2        second matrix              A A
 * @param lRes      lines  qty result[]
 * @param rRes      rows qty  result[]
 * @param result    result matrix
 * @return  error
 */
bool AFuncs::matrixMul(int l1, int r1, int a1[], int l2, int r2, int a2[], int lRes, int rRes,  int result[])
{
    int i,k, n;
    int arr1[MX_ARR_LEN][MX_ARR_LEN];
    int arr2[MX_ARR_LEN][MX_ARR_LEN];
    int arrRes[MX_ARR_LEN][MX_ARR_LEN];

    if (r1 != l2) return false;

    M_RESET_MATRIX(arrRes, MX_ARR_LEN)

    M_GET_TWO_MATRIX(l1,r1,a1, l2,r2,a2, arr1,arr2, MX_ARR_LEN)

    for(i=0; i < l1; i++){
        for(k=0; k < r2; k++){
             for(n=0; n < r1; n++){
                 arrRes[i][k] += arr1[i][n]*arr2[n][k];
             }
        }
    }
    i=0;
    M_CONV_MATRIX_TO_ARR(lRes, rRes, arrRes, result)

    return true;
}



/**
 * @brief AFuncs::matrixMul    - for float
 * @param l1         lines  qty a1[]                structure
 * @param r1         rows qty  a1[]                    B B B B
 * @param a1        first matrix                         B B B B
 * @param l2         lines  qty a2[]              A A
 * @param r2         rows qty  a2[]             A A
 * @param a2        second matrix              A A
 * @param lRes      lines  qty result[]
 * @param rRes      rows qty  result[]
 * @param result    result matrix
 * @return  error
 */
bool AFuncs::matrixMul(int l1, int r1, float a1[], int l2, int r2, float a2[], int lRes, int rRes,  float result[])
{
    int i,k, n;
    float arr1[MX_ARR_LEN][MX_ARR_LEN];
    float arr2[MX_ARR_LEN][MX_ARR_LEN];
    float arrRes[MX_ARR_LEN][MX_ARR_LEN];

    if (r1 != l2) return false;

    M_RESET_MATRIX(arrRes, MX_ARR_LEN);

    M_GET_TWO_MATRIX(l1,r1,a1, l2,r2,a2, arr1,arr2, MX_ARR_LEN)

    for(i=0; i < l1; i++){
        for(k=0; k < r2; k++){
             for(n=0; n < r1; n++){
                 arrRes[i][k] += arr1[i][n]*arr2[n][k];
             }
        }
    }
    i=0;
    M_CONV_MATRIX_TO_ARR(lRes, rRes, arrRes, result)

    return true;
}

/**
 * @brief AFuncs::matrixMul      - for double
 * @param l1         lines  qty a1[]                structure
 * @param r1         rows qty  a1[]                    B B B B
 * @param a1        first matrix                         B B B B
 * @param l2         lines  qty a2[]              A A
 * @param r2         rows qty  a2[]             A A
 * @param a2        second matrix              A A
 * @param lRes      lines  qty result[]
 * @param rRes      rows qty  result[]
 * @param result    result matrix
 * @return  error
 */
bool AFuncs::matrixMul(int l1, int r1, double a1[], int l2, int r2, double a2[], int lRes, int rRes,  double result[])
{
    int i,k, n;
    double arr1[MX_ARR_LEN][MX_ARR_LEN];
    double arr2[MX_ARR_LEN][MX_ARR_LEN];
    double arrRes[MX_ARR_LEN][MX_ARR_LEN];

    if (r1 != l2) return false;

    M_RESET_MATRIX(arrRes, MX_ARR_LEN);

    M_GET_TWO_MATRIX(l1,r1,a1, l2,r2,a2, arr1,arr2, MX_ARR_LEN)

    for(i=0; i < l1; i++){
        for(k=0; k < r2; k++){
             for(n=0; n < r1; n++){
                 arrRes[i][k] += arr1[i][n]*arr2[n][k];
             }
        }
    }
    i=0;
    M_CONV_MATRIX_TO_ARR(lRes, rRes, arrRes, result)

    return true;
}

/**
 * @brief AFuncs::matrixMul   -  Array * matrix  for int
 * @param a1        array   a1[]
 * @param len1      length  of  a1[]
 * @param l2         lines  qty a2[]                      structure
 * @param r2         rows qty  a2[]                             B B B B
 * @param a2        matrix  a2[][]                              B B B B
 * @param result    result array                            A A
 * @return  error
 */
bool AFuncs::matrixMul( int a1[], int len1, int l2, int r2, int a2[],  int result[])
{
    int i,  n;
    int arr[MX_ARR_LEN][MX_ARR_LEN];
    if (len1 != l2) return false;
    M_RESET_ARR(result, len1)
    M_GET_MATRIX(l2,r2,a2,  arr, MX_ARR_LEN)

    for(i=0; i < len1; i++){
        for(n=0; n < r2; n++){
            result[i] += a1[n] * arr[i][n];
        }
    }
    return true;
}


/**
 * @brief AFuncs::matrixMul   -  Array * matrix  for float
 * @param a1        array   a1[]
 * @param len1      length  of  a1[]
 * @param l2         lines  qty a2[]                      structure
 * @param r2         rows qty  a2[]                             B B B B
 * @param a2        matrix  a2[][]                              B B B B
 * @param result    result array                            A A
 * @return  error
 */
bool AFuncs::matrixMul( float a1[], int len1, int l2, int r2, float a2[],  float result[])
{
    int i,  n;
    float arr[MX_ARR_LEN][MX_ARR_LEN];
    if (len1 != l2) return false;
    M_RESET_ARR(result, len1)
    M_GET_MATRIX(l2,r2,a2,  arr, MX_ARR_LEN)

    for(i=0; i < len1; i++){
        for(n=0; n < r2; n++){
            result[i] += a1[n] * arr[i][n];
        }
    }
    return true;
}


/**
 * @brief AFuncs::matrixMul   -  Array * matrix  for double
 * @param a1        array   a1[]
 * @param len1      length  of  a1[]
 * @param l2         lines  qty a2[]                      structure
 * @param r2         rows qty  a2[]                             B B B B
 * @param a2        matrix  a2[][]                              B B B B
 * @param result    result array                            A A
 * @return  error
 */
bool AFuncs::matrixMul( double a1[], int len1, int l2, int r2, double a2[],  double result[])
{
    int i,  n;
    double arr[MX_ARR_LEN][MX_ARR_LEN];
    if (len1 != l2) return false;
    M_RESET_ARR(result, len1)
    M_GET_MATRIX(l2,r2,a2,  arr, MX_ARR_LEN)

    for(i=0; i < len1; i++){
        for(n=0; n < r2; n++){
            result[i] += a1[n] * arr[i][n];
        }
    }
    return true;
}








