#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NVAL 10000000
#define NITER 1000

int main (int argc, char **argv) {

        ////////////////////////////////////////////////////////
        ///// Initialize MPI here, get rank and world size /////
        ////////////////////////////////////////////////////////


	double x[NVAL];
        // In principle, all ranks could read the input file.
        // However, for a large number of ranks, this yields large traffic.
        // Therefore, make only rank 0 access the file. 
	FILE *f = fopen ("random.in", "r");
	double this_x;
	int i = 0;
	while (fscanf (f, "%lf\n", &this_x) != EOF) {
		x[i++] = this_x;
	}
	fclose (f);
        /// After the file has been read, you need to distribute the content of
        /// the x array to all other ranks.
        ///
        /// Can you be sure that the other ranks did not proceed with the
        /// calculation before x has been read in?

        ////////////////////////////////////////////////////////
        ///// Compute the boundaries of the MPI domain     /////
        ////////////////////////////////////////////////////////

	double mu, sigma;
	
	for (int n = 0; n < NITER; n++) {
		double sum = 0.0;
                /// The local sum now has to only include the MPI domain
                /// boundaries
		for (int i = 0; i < NVAL; i++) {
			sum += x[i];
		}

		/// Compute the sum of all local sums for all
                /// MPI ranks to compute the mean value.
                /// The mean value is required for the computation of the
                /// standard deviation. Make sure that all MPI ranks obtain
                /// the value of this global sum.

		mu = sum / NVAL;

		/// Same as above
		sum = 0.0;
		for (int i = 0; i < NVAL; i++) {
			sum += (x[i] - mu) * (x[i] - mu);
		}	
		sigma = sqrt(sum / (NVAL - 1));
	}

	printf ("Average: %lf\n", mu);
	printf ("sigma: %lf\n", sigma);
			
	return 0;
}
