#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double **createMat(int m,int n);
double distance(double **A, double **B);
double **loadtxt(char *str,int m,int n);
void freeMat(double **matrix, int rows);
double **dir_vec(double **A,double **B,int m,int n);
//double **dot_product(double **A,double **B,int m,int n);
double Matdot(double **a, double ** b, int m);//inner product
double **Matmul(double **a, double **b, int m, int n, int p);//multiply matrices a and b
double **transposeMat(double **a,  int m, int n);//transpose of a





    
void freeMat(double **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
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



//Defining the function for transpose of matrix

double **transposeMat(double **a,  int m, int n)
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




//Defining the function for product of matrices

double **Matmul(double **a, double **b, int m, int n, int p)
{
int i, j, k;
double **c, temp =0;
c = createMat(m,p);

 for(i=0;i<m;i++)
 {
  for(k=0;k<p;k++)
  {
    for(j=0;j<n;j++)
    {
	temp= temp+a[i][j]*b[j][k];
    }
	c[i][k]=temp;
	temp = 0;
  }
 }
return c;

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



double distance(double **A, double **B)
{
    return sqrt(pow(A[0][0] - B[0][0], 2) + pow(A[1][0] - B[1][0], 2));
}



//inner product
double Matdot(double **a, double ** b, int m){
	double **temp= Matmul(transposeMat(a,m,1),b,1,m,1);
	return temp[0][0];
}