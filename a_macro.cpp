#define M_GET_MATRIX(l, r, a, arr, len)                     \
    for (int gtmI=0; gtmI < len; gtmI++){                     \
       for (int gtmK=0; gtmK < len; gtmK++){                \
            arr[gtmI][gtmK]=0;                                     \
        }                                                                  \
    }                                                                      \
    for(int gtmI = 0; gtmI < l; gtmI++){                         \
         for (int gtmK = 0; gtmK < r ; gtmK++){                \
             arr[gtmI][gtmK] = a[gtmI * r + gtmK];         \
         }                                                                 \
    }                                                                      \



#define M_GET_TWO_MATRIX(l1, r1, a1, l2,r2,a2, arr1,arr2,  arrLen)  \
    for (int gtmI=0; gtmI < arrLen; gtmI++){                     \
       for (int gtmK=0; gtmK < arrLen; gtmK++){                \
            arr1[gtmI][gtmK]=0;                                     \
            arr2[gtmI][gtmK]=0;                                     \
        }                                                                  \
    }                                                                      \
    for(int gtmI = 0; gtmI < l1; gtmI++){                         \
         for (int gtmK = 0; gtmK < r1 ; gtmK++){                \
             arr1[gtmI][gtmK] = a1[gtmI * r1 + gtmK];     \
         }                                                                 \
    }                                                                      \
    for(int gtmI = 0; gtmI < l2; gtmI++){                        \
         for (int gtmK = 0; gtmK < r2 ; gtmK++){               \
             arr2[gtmI][gtmK] = a2[gtmI * r2 + gtmK];     \
         }                                                                 \
    }

#define M_ARR(l, r, arr) \
    l, r, &arr[0][0]

#define M_CONV_MATRIX_TO_ARR(l,r,inArr, outArr)\
    for(int cmtaI = 0; cmtaI < l; cmtaI++){\
         for (int cmtaK = 0; cmtaK < r ; cmtaK++){\
             outArr[cmtaI * r + cmtaK] = inArr[cmtaI][cmtaK];\
         }\
    }

#define M_RESET_ARR(arr, len)\
    for (int rstaI=0; rstaI < len; rstaI++) arr[rstaI]  = 0;



#define M_RESET_MATRIX(matrix, len)            \
    for (int rstmI=0; rstmI < len; rstmI++){      \
       for (int rstmK=0; rstmK < len; rstmK++){ \
            matrix[rstmI][rstmK]=0;                    \
        }                                                       \
    }



#define M_SET_MATRIX(matrix, val, l,r)         \
    for (int rstmI=0; rstmI < len; rstmI++){        \
       for (int rstmK=0; rstmK < len; rstmK++){   \
            matrix[rstmI][rstmK]=val;               \
        }                                                    \
    }

