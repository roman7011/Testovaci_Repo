#include <stdio.h>

int main() {
	
	int m=10000000, n=100, o=10;
	int nit = 1;
	double A[m+1][n+1][o+1];
	double s;
	
	for (int k=0; k<=o; k++){
		for(int j=0; j<=n; j++){
			for (int i=0; i<=m; i++){
				A[i][j][k] = 1.0;
			}
		}
	}


	printf("Init done. \n");

	for (int it=0; it<nit; it++ ){
		s = 0.0;
		for (int k=1; k<=o; k++){
			for(int j=1; j<=n; j++){
				for (int i=1; i<=m; i++){
					s +=   A[i-1][j  ][k  ] 
					     + A[i  ][j-1][k  ] 
					     + A[i  ][j  ][k-1] 
					     + A[i  ][j  ][k  ];
				}
			}
		}
	}
	printf("sum: %f\n",s);
	return 0;
}
