//
//  regression.hpp
//  cpp
//


#ifndef regression_h
#define regression_h

#include<iostream>
#include<cmath>
#include<Eigen/Eigen>


using namespace std;
using namespace Eigen;

class SimpleLinear_Regression
{
    Eigen::MatrixXd x;
    Eigen::MatrixXd y;
    double x_mean;
    double y_mean;
    
public:
    SimpleLinear_Regression(Eigen::MatrixXd x_data, Eigen::MatrixXd y_data)
    {
        x = x_data;
        y = y_data;
        x_mean = mean(x);
        y_mean = mean(y);
    }

private:
    
    // calculate mean
    double mean(Eigen::MatrixXd input)
    {
        double output;
        double temp=0;
        
        for(int i=0;i<input.rows();i++)
        {
            temp +=input(i,0);
        }
        output = temp/input.rows();
        return output;
    }
    
    
    // calculate variance
    double variance()
    {
        double output=0;
        double temp =0;
        // have to calculate the variance
        for(int i=0;i<x.size();i++)
        {
            double intn =0;
            intn = x(i) - x_mean;
            temp+=intn;
        }
        output = sqrt(temp);
        return output;
        
     }
    
    // calculate covariance
    double covariance()
    {
        double output;
        double temp=0;
        for(int i=0;i<x.size();i++)
        {
            double x_local, y_local;
            x_local = x(i) - x_mean;
            y_local = y(i)-y_mean;
            temp += x_local * y_local;
        }
        
        output = temp;
        return output;
        
    }
    
    //error calculation -> root mean square error
    double rmse(std::vector<double>y_pred)
    {
        double error =0;
        for(int i=0;i<y_pred.size();i++)
        {
            double temp;
            temp = y_pred[i] - y(i);
            error += sqrt(temp);
        }
        
        return error;
    }
    
    
    std::vector<double>  coefficents()
    {
        
        std::vector<double> output;
        
        double var, covar;
        var = variance();
        covar = covariance();
        
        double b0,b1;
        b1 = covar/var;
        b0 = y_mean - (b1*x_mean);
        
        output.push_back(b0);
        output.push_back(b1);
        return output;
        
    }
    
public:
    
    auto fit()
    {
        std::vector<double>  prediction;
        std::vector<double> coeff_out;
        coeff_out = coefficents();
        double b0,b1;
        b0 = coeff_out[0];
        b1 = coeff_out[1];
        std::vector<double> y_pred;
        for(int i=0;i<x.rows();i++)
        {
            double temp;
            temp = b0 + (b1*x(i));
            y_pred.push_back(temp);
        }
        
        double error;
        error = rmse(y_pred);
        cout<<"[*] The error score of the model is: "<<error<<endl;
        
        return 0;
        
        
    }
};

#endif
