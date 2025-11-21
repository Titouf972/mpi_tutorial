/**
 * Parallel Trapezoidal rule
 * 
 * Input : None
 * Output : Estimate of the integral from a to b of f(x) using 
 * the trapezoidal rule and n trapezoids
 * 
 * Algorithm: 
 *      1. Each process calculates its own interval of integration.
 *      2. Each process estimates the integral of f(x) over its interval using the trapezoidal rule.
 *      3a. Each process different from process 0 sends its integral to process 0
 *      3b. Process 0 sums the calculations received from the individual processes and prints the result.
 * 
 * Note : f(x), a, b, and n are hardwired. 
 */

#include <iostream>
#include "mpi.h"

int main(int argc, char ** argv){

    int myRank; /* my process rank */
    int p; /* the number of processes */
    double a = 0.; /* Left (global) endpoint */
    double b = 1.; /* Right (global) endpoint */
    int n = 8192; /* Number of trapezoids */
    double h; /* Trapezoids base length */
    double local_a; /* Local left endpoint */
    double local_b; /* Local right endpoint */
    int local_n; /* Local number of trapezoids */
    double integral; /* integral over local interval */
    double total; /* Integral over global interval */
    int source; /* Process sending integral */
    int dest = 0; /* All messages go to 0 */
    int tag = 0;
    MPI_Status status;

    double Trap(double local_a, double local_b, int local_n, double h); /* Calculate local integral */

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    h = (b-a)/((double)n); /* h is the same for all the processes */
    local_n = n/p; /* So is the number of trapezoids */
    
    /** The length of each process's interval of integration is local_n * h, so my
     * interval starts at
     */
    local_a = a + myRank * local_n * h;
    local_b = local_a + local_n * h;
    integral = Trap(local_a, local_b, local_n, h);

    /** Add up the integrals calculated by each process */
    if(myRank == 0){
        total = integral;
        for(source = 1; source < p; source++){
            MPI_Recv(&integral, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
            total += integral;
        }
    }else{
        MPI_Send(&integral, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }

    /* Print the result */
    if(myRank == 0){
        std::cout << "With n=" << n << " our estimation of the integral from " << a << " to " << b << " = " << total << "\n" ;
    }

    MPI_Finalize();

    return 0;
}

double Trap(double local_a, double local_b, int local_n, double h){
    double integral;
    double x;
    int i;

    double f(double x); /* function we're integrating */
    integral = (f(local_a) + f(local_b))/2.;
    x = local_a;
    for(i = 1; i <= local_n; i++){
        x += h;
        integral += f(x);
    }
    integral *= h;
    return integral;
}

/* test with square function */
double f(double x){
    double return_val;

    return_val = x*x;

    return return_val;
}
