#include <iostream> // to print
#include <fstream> // to read and write to files
#include "armadillo.hpp" // the library we will use for linear algebra
#include <cmath> // math stuff
#include <cassert>

// Declare a function that uses gradient descent to determine omega
arma::colvec gradient_descent(arma::mat data, arma::vec labels, arma::vec omega_init, double epsilon, double alpha);

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

    // Now we need to create a file in which we can write the results
    std::ofstream output_file("LogReg.dat");
    assert(output_file.is_open());

    // Let initial guess of omega be zeros, and have same size as number of columns
    arma::colvec omega_0( xTrain.n_cols, arma::fill::zeros );

    // Define tolerance
    double eps = 1e-7;

    // Define learning rate
    double alph = 0.3;

    // Determine omega with gradient descent method
    arma::vec omega = gradient_descent(xTrain, yTrain, omega_0, eps, alph);

    // Collect results
    // We now loop over xTest data, one point at a time
    // n_rows is an attribute describing number of rows: http://arma.sourceforge.net/docs.html#attributes
    // in this case number of test points
    for (int i=0; i<xTest.n_rows; i++){
        
        // Compute f(x)=w^Tx
        double fx = arma::dot( omega, xTest.row(i) );
        //std::cout << fx << std::endl;

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

arma::colvec gradient_descent(arma::mat data, arma::colvec labels, arma::colvec omega_init, double epsilon, double alpha){
    /*
    data = a matrix where each row represents a point that can vote (dataX.dat)
    labels = a vector of labels (int) either 1 or -1, representing a class (dataY.dat)
    omega = initial guess of omega, can just be zeros, vector with n elements, where n is the number of columns in data
    epsilon = the tolerance we accept omega with

    returns____ omega
    */

    // Define N (number of dimensions)
    int N = data.n_rows;

    // Ensure omega's initial guess has the right size
    //assert( N == arma::size(omega_init) );

    // Compute the first iteration of the gradient from initial omega guess
    arma::colvec grad(omega_init.n_rows, arma::fill::zeros);
    // Loop over rows (train points)
    for (int i=0; i<data.n_rows; i++){
        // Add contribution to all dimensions from each train point
        //grad += (-(1/N) * labels(i) * 1/(1+exp( labels(i) * arma::dot(omega_init,data.row(i)) ))) * data.row(i).t();
        auto factor = 1.0/(1+exp(labels[i] * arma::dot(omega_init, data.row(i))));
        grad += labels[i] * factor * data.row(i).t();
        grad = -grad/data.n_rows;
    }
    // Update omega
    arma::colvec omega(omega_init.n_rows);
    omega = omega_init - alpha*grad;

    // Run this as long as the tolerance is not obtained
    //while( arma::norm(grad) > epsilon ){
    for (int i=0; i<1e6;i++){

        // Reset gradient
        grad.zeros(omega.n_rows);

        // Loop over rows (train points)
        for (int i=0; i<data.n_rows; i++){
            // Compute the gradient
            // Add contribution to all dimensions from each train point
            //grad += (-(1/N) * labels(i) * 1/(1+exp( labels(i) * arma::dot(omega,data.row(i)) ))) * data.row(i).t();
            auto factor = 1.0/(1+exp(labels[i] * arma::dot(omega, data.row(i))));
            grad += labels[i] * factor * data.row(i).t();
            grad = -grad/data.n_rows;
        }

        // Update omega
        omega = omega - alpha*grad;

        if( arma::norm(grad) < epsilon ){
            std::cout << "I stopped at i=" << i << std::endl;
            break;
        }
    }

    // Return omega
    return omega;
}



