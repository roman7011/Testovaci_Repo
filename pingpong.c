#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main (int argc, char **argv) {
	
	MPI_Init (NULL, NULL);

	int rank, n_ranks;
	MPI_Comm_size (MPI_COMM_WORLD, &n_ranks);
	if (n_ranks != 2) {
		printf ("Error: PingPong requires exactly two processes! (Given %d)\n", n_ranks);
		MPI_Abort(MPI_COMM_WORLD, -1);
		return -1;
	}

	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	int n_reps = 2000;
	
	for (long msg_size = 1; msg_size <= 4194304; msg_size *= 2) {
		void *data = (void*)malloc (msg_size);
		double t_tot = 0.0;
		double t_start, t_end;
		for (int i = 0; i < n_reps; i++) {
			if (rank == 0) {
				t_start = MPI_Wtime();

				MPI_Send (data, msg_size, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
				MPI_Recv (data, msg_size, MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				t_end = MPI_Wtime();

				t_tot += (t_end - t_start);
			} else {
				MPI_Recv (data, msg_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send (data, msg_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
			}
				
		}
		free(data);
		if (rank == 0) {
			printf ("Msg size: %d Bytes, avg time: %lf us, bandwith: %lf MB / s\n",
				msg_size, 0.5 * t_tot / n_reps * 1e6, 2 * n_reps * msg_size / t_tot / 1024 / 1024);
		}
	}
		

	MPI_Finalize ();
	return 0;
}

