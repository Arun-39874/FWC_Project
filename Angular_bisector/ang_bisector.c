#include <stdio.h>
#include <math.h>

// Function to calculate the norm of a vector
double norm(double x, double y) {
    return sqrt(x * x + y * y);
}

// Function to calculate the direction vector from A to B
void dir_vec(double A[2], double B[2], double result[2]) {
    result[0] = B[0] - A[0];
    result[1] = B[1] - A[1];
}

// Function to calculate the side lengths of a triangle
void tri_sides(double A[2], double B[2], double C[2], double sides[3]) {
    sides[0] = norm(B[0] - C[0], B[1] - C[1]);
    sides[1] = norm(C[0] - A[0], C[1] - A[1]);
    sides[2] = norm(A[0] - B[0], A[1] - B[1]);
}

// Function to calculate the circumcenter and circumradius of a triangle
void ccircle(double A[2], double B[2], double C[2], double O[2], double *R) {
    double a = norm(B[0] - C[0], B[1] - C[1]);
    double b = norm(C[0] - A[0], C[1] - A[1]);
    double c = norm(A[0] - B[0], A[1] - B[1]);

    double s = (a + b + c) / 2.0;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));

    // Circumcenter coordinates
    O[0] = (a * A[0] + b * B[0] + c * C[0]) / (a + b + c);
    O[1] = (a * A[1] + b * B[1] + c * C[1]) / (a + b + c);

    // Circumradius
    *R = (a * b * c) / (4.0 * area);
}

// Function to calculate the incenter of a triangle
void incenter(double A[2], double B[2], double C[2], double I[2]) {
    double a = norm(B[0] - C[0], B[1] - C[1]);
    double b = norm(C[0] - A[0], C[1] - A[1]);
    double c = norm(A[0] - B[0], A[1] - B[1]);

    I[0] = (a * A[0] + b * B[0] + c * C[0]) / (a + b + c);
    I[1] = (a * A[1] + b * B[1] + c * C[1]) / (a + b + c);
}

int main() {
    // Triangle vertices
    double A[2] = {1, -1};
    double B[2] = {-4, 6};
    double C[2] = {-3, -5};

    // Triangle sides
    double sides[3];
    tri_sides(A, B, C, sides);
    printf("Triangle Sides: (%f, %f, %f)\n", sides[0], sides[1], sides[2]);

    // Points of contact
    double insides[3];
    insides[0] = 1.60690925;
    insides[1] = 6.99541602;
    insides[2] = 4.049945;

    // Points of contact
    double F[2], D[2], E[2];
    F[0] = (insides[1] * A[0] + insides[0] * B[0]) / (insides[1] + insides[0]);
    F[1] = (insides[1] * A[1] + insides[0] * B[1]) / (insides[1] + insides[0]);
    D[0] = (insides[2] * B[0] + insides[1] * C[0]) / (insides[2] + insides[1]);
    D[1] = (insides[2] * B[1] + insides[1] * C[1]) / (insides[2] + insides[1]);
    E[0] = (insides[0] * C[0] + insides[2] * A[0]) / (insides[0] + insides[2]);
    E[1] = (insides[0] * C[1] + insides[2] * A[1]) / (insides[0] + insides[2]);

    // Circumcenter and circumradius
    double O[2], R;
    ccircle(A, B, C, O, &R);
    printf("Circumcenter O: (%f, %f)\n", O[0], O[1]);
    printf("Circumradius R: %f\n", R);
    
    // Incenter
    double I[2];
    incenter(A, B, C, I);
    printf("Incenter I: (%f, %f)\n", I[0], I[1]);

    // Print vertices
    printf("Vertices A, B, C: (%f, %f), (%f, %f), (%f, %f)\n", A[0], A[1], B[0], B[1], C[0], C[1]);

    // Print angle bisector intersection points
    printf("Angle Bisector Intersection Points F, D, E: (%f, %f), (%f, %f), (%f, %f)\n", F[0], F[1], D[0], D[1], E[0], E[1]);

    return 0;
}