#include <iostream> // to print
#include <fstream> // to read and write to files
#include "armadillo.hpp" // the library we will use for linear algebra
#include <cmath> // math stuff
#include <cassert>

// Declare a function that uses gradient descent to determine omega
arma::colvec gradient_descent(arma::mat data, arma::vec labels, arma::vec omega, double epsilon, double alpha);

int main(){

    // First of all, we initialise the objects in which we will store our data
    arma::mat xTrain;
    arma::vec yTrain;
    arma::mat xTest;

    // Now we need to load in the data from the files
    // The format is raw_ascii (explained here: http://arma.sourceforge.net/docs.html#save_load_mat)
    xTrain.load("dataX.dat", arma::raw_ascii);
    yTrain.load("dataY.dat", arma::raw_ascii);
    xTest.load("dataXtest.dat", arma::raw_ascii);

    // Let initial guess of omega be zeros, and have same size as number of columns (dimensions)
    arma::colvec omega;
    omega.zeros(xTrain.n_cols);

    // Define tolerance
    double eps = 1e-7;

    // Define learning rate
    double alph = 0.5;

    // Run one iteration of gradient descent
    arma::colvec grad = gradient_descent(xTrain, yTrain, omega, eps, alph);

    // Update omega
    omega = omega - alph * grad;

    // Run gradient descent iteratively until tolerance is obtained (but limited to N)
    int N=1e6;
    for (int i=0; i<N; i++){
        
        // Run one iteration of gradient descent
        arma::colvec grad = gradient_descent(xTrain, yTrain, omega, eps, alph);

        // Update omega
        omega = omega - alph * grad;

        if ((double)(arma::norm(grad)) < eps){
            break;
        }
    }

    // Now we need to create a file in which we can write the results
    std::ofstream output_file("LogReg.dat");
    assert(output_file.is_open());

    // Collect results ----------------
    // We now loop over xTest data, one point at a time
    // n_rows is an attribute describing number of rows: http://arma.sourceforge.net/docs.html#attributes
    // in this case number of test points
    for (int i=0; i<xTest.n_rows; i++){
        
        // Compute f(x)=w^Tx
        double fx = arma::dot( omega, xTest.row(i) );

        // Assign label according to: y = sign(f(x))
        if (fx >= 0){

            // Write to output file
            output_file << 1 << "\n";
        }
        else{
            // Write to output file
            output_file << -1 << "\n";
        }
    }
    return 0;
}

arma::colvec gradient_descent(arma::mat data, arma::vec labels, arma::vec omega, double epsilon, double alpha){
    
    // Initialize gradient to 0
    arma::colvec g(omega.n_rows);
    g.zeros(omega.n_rows);

    // Iterate over points in train
    for (int i=0; i<data.n_rows; i++){

        // Compute gradient
        auto factor = 1.0/(1+exp(labels[i] * arma::dot(omega, data.row(i))));
        g += labels[i] * factor * data.row(i).t();
    }

    return -g/data.n_rows;
}
