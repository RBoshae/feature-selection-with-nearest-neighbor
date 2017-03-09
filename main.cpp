/*
 *  File: main.cpp
 *  ---------------
 *  Created by Rick Boshae 03/03/2017
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include <cstdlib>
using namespace std;

// copy_data transfers data from text file to matrix of type float
void copy_data(string data_file_name, vector<vector <float> >& data_matrix);
double leave_one_out_accuracy(vector<vector <float> >& data_matrix);
float nn_classifier(vector< vector<float> >& training_data_matrix, vector<float> &instance, vector<int>& features);

int main() {
    
    vector <vector <float> > data_matrix;

    string  file_name = ""; // Stores name of file to test
    int selection = 1;          
    
    std::cout << "Welcome to Rick Boshae's Feature Selection Algorithm." << std::endl;
    std::cout << "Type in the name of the file to test : ";
    
    getline(cin, file_name);

    // copy_data reads data from input file and stores it to the data_matrix
    copy_data(file_name, data_matrix);    

//    //Print data_matrix -- for testing
//    for(int i = 0; i < data_matrix.size(); i++){
//        for (int j = 0; j < data_matrix[i].size(); j++) {
//            cout << data_matrix[i][j] << " ";
//        }
//        cout << "newline" << endl;
//    }



    cout << "Type the number of the algorithm you want me to run." << std::endl;
    
    cout << "\t1) Forward Selection\n";
    cout << "\t2) Backward Elimination\n";
    cout << "\t3) Rick's Special Algorithm\n";
    
    cin >> selection;
  

    double accuracy = leave_one_out_accuracy(data_matrix);

    cout << "This dataset has " << data_matrix[0].size() - 1 << " features (not including the class attributes), with " << data_matrix.size() << " instances." << endl << endl;

    cout << "Please wait while I normalize the data...(under construction)" << endl <<endl;
        
        
    cout << "Running nearest neighbor with all " << data_matrix[0].size() - 1 << " features, using \"leave-one-out\" evaluation, I get an accuracy of " << accuracy*100 << "%" << endl <<endl;
    
   // vector<float> test_instance;
   // test_instance.push_back(2);
   // test_instance.push_back(4);
   // test_instance.push_back(3);

   // vector<int> features;
    //features.push_back(0);
   // features.push_back(1);
   // features.push_back(2);

    //cout << "Classifying 111...\n" << nn_classifier(data_matrix, test_instance, features) <<endl;

    switch(selection) {
    
        case 1: std::cout << "Forward Selection selected." << std::endl;
                break;
        case 2: std::cout << "Backward Elimination selected." << std::endl;
                break;
        case 3: std::cout << "Ricks Special Algorithm selected." << std::endl;
                break;
        default: std::cout << "No selection was made, default to Rick's Special Algorithm" << std::endl;
                      break;
    }

    return 0; //end of main
}









void copy_data(string data_file_name, vector<vector <float> >& data_matrix) {

    ifstream data_file;
    string line;
    char next;
    float data_value;
    vector<float> row;

    const char* cstr = data_file_name.c_str(); // Convert file name to char* to be used in file stream
    
    data_file.open(cstr);

    if (data_file.is_open()) {
        
        // Output to verify that the file is accessable
        cout << "File successfully opened.\n";

        while( !data_file.eof() ) {    

            getline(data_file, line);
            stringstream ss(line);            // make a stream for the line itself
            
            while( ss >> data_value){
            
                row.push_back(data_value);
                
            }
        // Prevent emtpty row from being stored.
            if (row.size() > 0) {
            data_matrix.push_back(row);
            }
            row.clear();

        }

        data_file.close();
         }else {
        cout << "Error opening file\n";
        cout << "The file may have been mispelled or not exist.\n";
        exit(1);
    }
return;
}




/*
double leave_one_out_accuracy(vector<vector <float> >& data_matrix) {
    double accuracy = 0; // used to calculate
    
    float home_point = 0;
    float nearest_neighbor_distance = pow(10,38);
    float euclidean_distance = 0;
    int nearest_neighbor_row = 0;

    //Loop for each row in matrix
    for (int m = 0; m < data_matrix.size(); m++) {
        //Select a row from the matrix (row i)
        

        //Compute row i's distance from all other rows
        for(int j = 0; j < data_matrix.size(); j++) {
            
            if (m != j){
                for (int k = 1; k < data_matrix[j].size(); k++) {
                
                    euclidean_distance += pow((data_matrix[j][k] - data_matrix[m][k]),2);
                
                }
            
                 euclidean_distance = sqrt(euclidean_distance);
                if (euclidean_distance < nearest_neighbor_distance){
                    nearest_neighbor_distance = euclidean_distance;
                    nearest_neighbor_row = j;
                }
            }

            //clear euclidean distance
            euclidean_distance = 0;

        }
 
 //       cout << "nearest neighbor for " << data_matrix[m][0] << data_matrix[m][1] << data_matrix[m][2] << " is " <<  data_matrix[nearest_neighbor_row][0] << data_matrix[nearest_neighbor_row][1] << data_matrix[nearest_neighbor_row][2] << " with a euclid distance of " << nearest_neighbor_distance << endl;
 //     //check accuracy
        if (data_matrix[m][0] == data_matrix[nearest_neighbor_row][0]){
            
            accuracy++;

        }

        //Clear variables
        nearest_neighbor_distance = pow(10,38);


    }

    return accuracy/(data_matrix.size());
}

*/
double leave_one_out_accuracy(vector<vector <float> >& data_matrix) {
    
    double  accuracy = 0.0; // used to calculate
    vector< vector <float> > training_set = data_matrix;
    vector<float> selected_instance;
    vector<int> features;
    float predicted_class;

    //Loop for each row in matrix
    for (int m = 0; m < data_matrix.size(); m++) {
        //Select a row from the matrix (row i)
        training_set = data_matrix;
        selected_instance = training_set.at(m);
        training_set.erase(training_set.begin() + m);
        
        //for( int i = 1; i < selected_instance.size(); i++) {
        
       //     features.push_back(i);
        
       // }
       features.push_back(5);
       features.push_back(7);
       features.push_back(3);

        predicted_class = nn_classifier(training_set, selected_instance, features);

 
      //check accuracy
    if (selected_instance[0] == predicted_class){
            
            accuracy++;

        }



    }

    return accuracy/(data_matrix.size());
}





float nn_classifier(vector < vector <float> >& training_data_matrix, vector<float>& instance, vector<int>& selected_features) {

    float classification = 0; 
    float nn_distance = pow(10,38);
    float e_distance = 0;
    int nn_instance = 0;

    //Loop through each instance in the training data matrix
    for( int i = 0; i < training_data_matrix.size(); i++) {

        //Compute Euclid distance for selected feautres
        for(int j = 0; j < selected_features.size(); j++) {
        
            
         //   cout << "selected feature: " << selected_features.at(j) << endl;
             e_distance += pow((training_data_matrix[i][selected_features.at(j)] - instance[selected_features.at(j)]),2);
                
        }
            e_distance = sqrt(e_distance);

                if (e_distance < nn_distance){
                    nn_distance = e_distance;
                    nn_instance = i;
                }
            //clear e_distance
            e_distance = 0;
    }

    classification = training_data_matrix[nn_instance][0];
    

    return classification;
}






