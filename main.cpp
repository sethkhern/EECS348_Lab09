#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void read_matrix(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2, int &x) {
    string filename;
    cout << "Enter name of Matrix file: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout <<"Cannot open the file!\n";
        exit(0);
    } else {
        int matrix_size = 0;
        file >> matrix_size;

        if (matrix_size <= 0) {
            cout <<"Invalid matrix size!\n";
            exit(0);
        }

        matrix1 = vector<vector<int>>(matrix_size, vector<int>(matrix_size));
        matrix2 = vector<vector<int>>(matrix_size, vector<int>(matrix_size));

        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                file >> matrix1[i][j];
            }
        }

        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                file >> matrix2[i][j];
            }
        }
    }
}


int main (int argc, char*argv[]){
    vector<vector<int>> matrix1, matrix2;
    int x;
    read_matrix(matrix1, matrix2, x);
    cout <<"The value of the first matrix" <<endl;
    print_matrix(matrix1);
    cout <<"The value of the second matrix" <<endl;
    print_matrix(matrix2);


    return 0;
}