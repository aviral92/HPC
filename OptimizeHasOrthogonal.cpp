/*
Optimize the function hasOrthogonalColumns to make it as fast as possible using the gcc compiler.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <xmmintrin.h>

#define N 501


int hasOrthogonalColumns(float *A, int n) {
    // This function should return a non-zero integer
    // if some two columns of the n x n matrix A are
    // orthogonal. Otherwise, the function should
    // return 0.
	int i,j,k,m,q;
	float x,sum=0;
	m=n%4;
	q=n+4-m;
	float b[q][q];
	 __m128 *p1;
	__m128 *p2;
	
	float temp[q+16];
	
	float *p;
	for(p = temp; ((int) p) % 16 != 0; p++)
		;
	if(m==0)
	{
	for(i=0;i<n;i++)
		for(j=i,k=0;j<n*n,k<n;j+=n,k++)
			{
				b[i][k]=A[j];
				
			}
	}

	else
	{	
		for(i=0;i<q;i++)
		for(j=i,k=0;j<q*q,k<q;j+=n,k++)
			{	
				if((i<n) && (k<n))
		
				b[i][k]=A[j];
		
				else if(i>=n)
				b[i][k]=1;
				

				else if(k>=n)
					b[i][k]=0;
					
				
			}
		
	
	}
 
 for(k=0;k<(q-1);k++)
    {
	

      p1=(__m128*)&b[k][0];

         for(j=k+1;j<q;j++)
              {
				

                           p2=(__m128*)&b[j][0];
                           sum=0;
                           	for(i = 0; i < q/4; i++, p1++,p2++) {
	
	  _mm_store_ps(p, _mm_mul_ps(*p1, *p2));

		
	  	
	  sum+=p[0] +p[1] + p[2] +p[3];
                           }
                           if(sum==0)
                           return 1;
             }
      
      }
      
	
	return 0;	

}

int main() {
   float A[N*N];
    float *b;
  for(b = A; ((int) b) % 16 != 0; b++)
    ;
	
    int i;
    clock_t start;

    srand(time(NULL));
    
    for(i = 0; i < N*N; i++) {
    b[i] = (rand() % N) / (0.01f + (rand() % N));
	
    }      

    start = clock();
     i = hasOrthogonalColumns(b, N);
    printf("Answer: %s, Time: %d ticks\n", (i == 0 ? "No" : "Yes"), clock() - start);

     getch();
    return 0;
  
    
}
