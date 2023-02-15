#include <iostream> // to print
#include <fstream> // to read and write to files
#include "armadillo.hpp" // the library we will use for linear algebra

// Declare the function we will use to classify one point according to kNN
int kNN(arma::rowvec point, arma::mat data, arma::vec labels, int k);

// Main function that runs our code
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
    std::ofstream output_file("NN.dat");
    assert(output_file.is_open());

    // We now loop over xTest data, one point at a time
    // n_rows is an attribute describing number of rows: http://arma.sourceforge.net/docs.html#attributes
    // in this case number of test points
    for (int i=0; i<xTest.n_rows; i++){

        // Classify the point with k=5
        // To do this we use submatrix views with .row(rownumber) (see here: http://arma.sourceforge.net/docs.html#submat)
        int label = kNN(xTest.row(i), xTrain, yTrain, 5);

        // Write to output-file
        //output_file << label << "\n";
        output_file << label << std::endl;
    }

    // Close the file again
    output_file.close();

    return 1;
}


// Define the function that classifies one point according to kNN
int kNN(arma::rowvec point, arma::mat data, arma::vec labels, int k){
    /*
    point = a vector of numbers (each row is a point in the dataXtest.dat)
    data = a matrix where each row represents a point that can vote (dataX.dat)
    labels = a vector of labels (int) either 1 or -1, representing a class (dataY.dat)
    k = int of how many neighbours should vote

    returns___ label an int either 1 or -1
    */

    // Compute distances between the test-point and the train-data: x_i - x
    // We do this by taking the 2-norm of a row (one train-point) and the test-point
    arma::vec distances(data.n_rows);
    // Loop over rows (points in train)
    for (int i=0; i<data.n_rows; i++){
        distances(i) = arma::norm( data.row(i) - point, 2);
    }
    
    // Now we need to sort the indices according to ascending distance
    // So if sorted_idx[0] = 31, then the smallest distance is distances[31]
    // We can do this with sort_index, see here: http://arma.sourceforge.net/docs.html#sort
    arma::uvec sorted_idx = arma::sort_index(distances, "ascend");

    // The voting proces can be done by a simple summation, since the labels are 
    // either -1 or 1. If the sum of the labels is positive, there are more 1's,
    // and the point should be labeled as such. The opposite goes if the sum is negative.
    int label_sum = 0;
    
    // Loop over the k nearest neighbours we want to consider
    for (int i=0;i<k;i++){
        label_sum += labels[sorted_idx(i)];
    }

    // Return the appropriate label (as long as k is uneven it will never be zero)
    if (label_sum > 0){
        return 1;
    }
    else{
        return -1;
    }
}

