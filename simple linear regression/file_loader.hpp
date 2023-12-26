//
//  file_loader.hpp



#ifndef file_loader_h
#define file_loader_h

#include<iostream>
#include<fstream>
#include<vector>
#include<Eigen/Eigen>

using namespace std;
using namespace Eigen;


class load_csv
{
private:
    
    auto Mat_Data_loader(std::vector<std::vector<double>> input)
    {
        long int row_count = input.size();
        long int col_count = input[0].size();
        
        Eigen::MatrixXd output(row_count, col_count);
        
        for(int i=0;i<row_count;i++)
        {
            for(int j=0;j<col_count;j++)
            {
                //cout<<input[i][j];
                output(i,j) = input[i][j];
            }
        }
        cout<<"[*] Data Frame is created."<<endl;
        return output;
        
        
    }
    
    std::vector<std::vector<double>> DataType_conv(std::vector<std::vector<string>> input)
    {
        std::vector<std::vector<double>> output;
        unsigned long int m = input.size();
        long int n = input[0].size();
        
        for(int i=0;i<m;i++){
            std::vector<double> row;
            for(int j=0;j<n;j++)
            {
                string temp_str;
                temp_str = input[i][j];
                double temp_dbl = std::stod(temp_str);
                row.push_back(temp_dbl);
            }
            output.push_back(row);
        }
        
        return output;
    } // data type conversion();
    
    
    std::vector<string> split(string input_line)
    {
        // line input is converted into words
        long  int temp = input_line.size();
        std::vector<string> output;
        string word="";
        for(int i=0;i<=temp;i++)
        {
            string loc;
            loc = input_line[i];
            if((loc != ",")&(i<temp))
            {
                word += loc;
            }
            else{
                output.push_back(word);
                word = "";
            }
            
        }
        
        return output;
    }//split ();
       
    
public:
        
    auto load(string file_path)
    {
        fstream file;
        file.open(file_path);
        int i=0;
        std::vector<std::vector<string>> coln_vector;
        
        if(file.is_open()){
            cout<<"[*] The file is loaded .."<<endl;
            cout<<endl;
            
            string line;
            
            while(getline(file, line))
            {
                if(i!=0)
                {
                    std::vector<string> temp;
                    temp = split(line);
                    coln_vector.push_back(temp);
                }
                i+=1;
            }
            
    
        }
        else {
            cout<<"[*] There is an error importing the file...!"<<endl;
        }
        
        std::vector<std::vector<double>> data_vector;
        data_vector = DataType_conv(coln_vector);
        
        long int rows = data_vector.size();
        long int cols = data_vector[0].size();
        
        
        Eigen::MatrixXd data_output(rows, cols);
        data_output = Mat_Data_loader(data_vector);
        
        
        return data_output;
    }  // load function
    
    
};// load_csv class



#endif
