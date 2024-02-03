#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double **createMat(int m,int n);
double slope(double **A, double **B);
double **solve(double **p,double **N);
double distance(double **A, double **B);
void freeMat(double **matrix, int rows);
double **loadtxt(char *str,int m,int n);
double **transpose(double **a,  int m, int n);
double **block(double **a,double **b,int m,int n);
double **dir_vec(double **A,double **B,int m,int n);
double **midpoint(double **A, double **B, int m, int n);
double **mat_mul(double **a, double **b, int r1,int c1, int c2);
double **line_intersect(double **m3,double **B,double **m1,double **C, int m,int n);


double **intersect(double m1, double c1, double m2, double c2);


double **intersect(double m1, double c1, double m2, double c2) {
    double **intersection = createMat(2, 1);

    // Calculate intersection coordinates
    intersection[0][0] = (c2 - c1) / (m1 - m2);
    intersection[1][0] = m1 * intersection[0][0] + c1;

    return intersection;
}


double **dir_vec(double **A,double **B,int m,int n)
{
    int i, j;
    double **c;
    c = createMat(m,n);

    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
    c[i][j]= B[i][j]-A[i][j];
    }
    }
    return c;
}


void freeMat(double **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

double slope(double **A, double **B)
{
    return (B[1][0] - A[1][0]) / (B[0][0] - A[0][0]);
}


double distance(double **A, double **B)
{
    return sqrt(pow(A[0][0] - B[0][0], 2) + pow(A[1][0] - B[1][0], 2));
}

double **solve(double **p,double **N)
{
    double **sol;
    sol=createMat(2,1);
    sol[1][0]=(p[0][0]*N[1][0]-N[0][0]*p[1][0])/(N[0][1]*N[1][0]-N[0][0]*N[1][1]);
    sol[0][0]=(p[0][0]*N[1][1]-N[0][1]*p[1][0])/(N[0][0]*N[1][1]-N[0][1]*N[1][0]);
    return sol;

}



double **mat_mul(double **a, double **b, int r1,int c1, int c2)
{
    int i, j, k;
    double **c; 
    c = createMat(r1,c2);                                                            
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            c[i][j]=0;
        }
    }
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            for(k=0;k<c1;k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    return c;
}



double **block(double **a,double **b,int m,int n)
{
    double **l;
    int i,j,k=0;

    l=createMat(m,m);
    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
        l[i][k]=a[i][j];
    }
    }
    k+=1;
        
    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
    l[i][k]=b[i][j];
    }
    }
    k+=1;


    return l;
}



double **line_intersect(double **m3,double **B,double **m1,double **C, int m,int n)
{
    double **N,**m3_t,**m1_t,**p0,**p1,**p,**P1,**P2,**solution;
    p=createMat(2,1);
    N=transpose(block(m3,m1,m,n),m,m);
    m3_t=transpose(m3,m,n);
    m1_t=transpose(m1,m,n);
    p0=mat_mul(m3_t,B,n,m,n);
    p1=mat_mul(m1_t,C,n,m,n);
    p[0][0]=p0[0][0];
    p[1][0]=p1[0][0];
    solution=solve(p,N);
    return(solution);
}



double **transpose(double **a,  int m, int n)
{
    int i, j;
    double **c;
    //printf("I am here");
    c = createMat(n,m);

    for(i=0;i<n;i++)
    {
    for(j=0;j<m;j++)
    {
    c[i][j]= a[j][i];
    //  printf("%lf ",c[i][j]);
    }
    }
    return c;
}



double **midpoint(double **A,double **B,int m,int n)
{
    int i, j;
    double **c;
    c = createMat(m,n);

    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
    c[i][j]= (A[i][j]+B[i][j])/2;
    }
    }
    return c;
}



double **createMat(int m,int n)
{
    int i;
    double **a;
    
    //Allocate memory to the pointer
    a = (double **)malloc(m * sizeof( *a));
        for (i=0; i<m; i++)
            a[i] = (double *)malloc(n * sizeof( *a[i]));

 return a;
}



double **loadtxt(char *str,int m,int n)
{
    FILE *fp;
    double **a;
    int i,j;


    a = createMat(m,n);
    fp = fopen(str, "r");

    for(i=0;i<m;i++)
    {
    for(j=0;j<n;j++)
    {
    fscanf(fp,"%lf",&a[i][j]);
    }
    }
    fclose(fp);
    
    return a;
    
}