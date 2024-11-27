#include <stdio.h>

int min(int x, int y){
	int res;
	if(x<y){
		res=x;
	}else{
		res=y;
	}
	return res;
}


int main() {
	
	//int m=10000000, n=100, o=10;
	int o=10000000, n=100, m=10;
	int nit = 1;
	double A[m+1][n+1][o+1];
	double s;
	
	int is,js,ks;
	int kb=256, jb=16, ib=16;
	//int ib=m,jb=n,kb=o;
	
	for (int i=0; i<=m; i++){
		for(int j=0; j<=n; j++){
			for (int k=0; k<=o; k++){
				A[i][j][k] = 1.0;
			}
		}
	}

	printf("Init done. \n");

	for (int it=0; it<nit; it++ ){
		s = 0.0;

		for (ks=1; ks<=o; ks+=kb){
			int ke = min(ks+kb-1,o);
			for (js=1; js<=n; js+=jb){
				int je = min(js+jb-1,n);
				for (is=1; is<=m; is+=ib){
					int ie = min(is+ib-1,m);
					for (int i=is; i<=ie; i++){
						for(int j=js; j<=je; j++){
							for (int k=ks; k<=ke; k++){
								s +=   A[i-1][j  ][k  ] 
								     + A[i  ][j-1][k  ]
								     + A[i  ][j  ][k-1]
								     + A[i  ][j  ][k  ];
							}
						}
					}
				}
			}
		}
	}
	printf("sum: %f\n",s);
	return 0;
}
