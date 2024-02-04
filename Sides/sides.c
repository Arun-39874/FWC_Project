#include <stdio.h>
#include <math.h>
#include"lib_sides.h"


int main() {
    double **A,**B,**C,**m1,**m2,**m3;
    int m=2,n=1;

    // Read coordinates from separate .dat files
    A=loadtxt("A.dat",2,1);
    B=loadtxt("B.dat",2,1);
    C=loadtxt("C.dat",2,1);


    // Triangle sides
    double a = distance(B, C);
    double b = distance(C, A);
    double c = distance(A, B);

    printf("Sides: a = %f, b = %f, c = %f\n", a, b, c);

    // Direction Vectors
    m1=dir_vec(A,B,m,n);
    m2=dir_vec(B,C,m,n);
    m3=dir_vec(C,A,m,n);


    // Angles
    double angA = acos(Matdot(m1, m3, m) / (distance(A, B) * distance(C, A))) * 180.0 / M_PI;
    double angB = acos(Matdot(m1, m2, m) / (distance(A, B) * distance(B, C))) * 180.0 / M_PI;
    double angC = acos(Matdot(m2, m3, m) / (distance(B, C) * distance(C, A))) * 180.0 / M_PI;

    printf("Angles: angA = %f, angB = %f, angC = %f\n", angA, angB, angC);

    freeMat(A,2);
    freeMat(B,2);
    freeMat(C,2);
    freeMat(m1,2);
    freeMat(m2,2);
    freeMat(m3,2);

    return 0;
}
