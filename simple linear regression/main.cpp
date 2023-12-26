
#include "file_loader.hpp"
//#include "data_processing.hpp"
#include "regression.hpp"

#include<iostream>
#include<vector>
#include<Eigen/Eigen>


using namespace std;
using namespace Eigen;


int main()
{
    std::vector<std::vector<double>> output;
    
    string path="/Users/kavi/Documents/Salary_dataset.csv";
    
    // Loading the dataset
    load_csv loader;
    Eigen::MatrixXd data = loader.load(path);
    
    
    // x and y data for regression model
    long int row_Count = data.rows();
    Eigen::MatrixXd x_data(row_Count, 1);
    Eigen::MatrixXd y_data(row_Count,1);
    
    // x data
    for(int i=0;i<data.rows();i++){
        x_data(i,0) = data(i,1);
    }
    // y data
    for(int i=0;i<data.rows();i++){
        y_data(i,0) = data(i,2);
    }
    
    
    // simple linear regression class
    SimpleLinear_Regression regressor(x_data, y_data);
    regressor.fit();
    
    
    
    return 0;
    
}

