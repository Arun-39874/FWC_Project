#include <stdio.h>
#include <math.h>
#include"libr_pgm.h"

int main() {

    double **A,**B,**C,**D,**E,**F,**m1,**m2,**m3,**H;
    int m=2,n=1;

    // Read coordinates from separate .dat files
    A=loadtxt("A.dat",2,1);
    B=loadtxt("B.dat",2,1);
    C=loadtxt("C.dat",2,1);

    // Calculate midpoints
    D=midpoint(B,C,m,n);
    E=midpoint(C,A,m,n);
    F=midpoint(A,B,m,n);
 
    m1=dir_vec(A,B,m,n);
    m2=dir_vec(B,C,m,n);
    m3=dir_vec(C,A,m,n);

    // Calculate angle bisector slopes
    double slope_AB = slope(A,B);
    double slope_AC = slope(A,C);
    double slope_BC = slope(B,C);

    // Calculate altitude slopes
    double m_altA = -1 / slope_BC;
    double m_altB = -1 / slope_AC;
    double m_altC = -1 / slope_AB;

    double **O = intersect((B[1][0] - C[1][0]) / (B[0][0] - C[0][0] + B[1][0] - C[1][0]), B[1][0] - ((B[1][0] - C[1][0]) / (B[0][0] - C[0][0] + B[1][0] - C[1][0])) * B[0][0], -slope_AC, A[1][0] + slope_AC * A[0][0]);

    double R = distance(A,O);

    // Calculate altitude intersection points
    H=line_intersect(m3,B,m1,C,m,n);

    printf("Midpoint D: (%lf, %lf)\n", D[0][0], D[1][0]);
    printf("Midpoint E: (%lf, %lf)\n", E[0][0], E[1][0]);
    printf("Midpoint F: (%lf, %lf)\n", F[0][0], F[1][0]);
    //printf("Circumcenter O: (%.lf, %.lf)\n", O[0][0], O[1][0]);
    //printf("Circumradius: %.lf\n", R);
    printf("Orthocenter H: (%lf, %lf)\n", H[0][0], H[1][0]);

    freeMat(A,2);
    freeMat(B,2);
    freeMat(C,2);
    freeMat(m1,2);
    freeMat(m2,2);
    freeMat(m3,2);
    freeMat(H,2);

    return 0;
}
