#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-6;
const int PRECISION = 20;

typedef vector<double> Column;
typedef vector<double> Row;
typedef vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

Equation ReadEquation() {
    int size;
    cin >> size;
    Matrix a(size, vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            cin >> a[row][column];
        cin >> b[row];
    }
    return Equation(a, b);
}
Equation RReadEquation(vector<vector<double>> matrix, int size) {
    Matrix a(size, vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            a[row][column]= matrix[row][column];
        b[row] = matrix[row][size];
    }
    return Equation(a, b);
}


void SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();
    for(int i=0; i<size; i++){
        //find first non-zero in ith column
        int row_num = -1;
        for(int j=i; j<size; j++){
            if(a[j][i] != 0){
                row_num = j;
                break;
            }
        }
        if(row_num != -1){
            swap(a[i], a[row_num]);
            double pivot_num = a[i][i];
            for(int j=i; j<size; j++){
                a[i][j]/=pivot_num;
            }
            b[i]/=pivot_num;
            for(int j=i+1; j<size; j++){
                int x = -a[j][i];
                for(int k=i; k<size; k++){
                    a[j][k]+=x*a[i][k];
                }
                b[j]+=x*b[i];
            }

        }
    }
    int sum =0;
    for(int i= size-2; i>=0; i--){
        for(int j=i+1; j<size; j++){
            b[i] -= a[i][j]*b[j];
        }
    }
    // return b;
    cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        cout << b[row] << endl;
}

void PrintColumn(const Column &column) {
    int size = column.size();
    cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        cout << column[row] << endl;
}

void partial_pivot(vector<vector<double>>& matrix) {
    int size= matrix.size();
    for (int i = 0; i < size; i++) {
        int pivot_row = i;
        for (int j = i+1; j < size; j++) {
            if (abs(matrix[j][i]) > abs(matrix[pivot_row][i])) {
                pivot_row = j;
            }
        }
        if (pivot_row != i) {
            for (int j = i; j <= size; j++) {
                swap(matrix[i][j], matrix[pivot_row][j]);
            }
        }
        for (int j = i+1; j < size; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= size; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}
 
void back_substitute(vector<vector<double>>& matrix, vector<double>& x) {
    int n = matrix.size();
    
    for (int i = n-1; i >= 0; i--) {
        double sum = 0;
        for (int j = i+1; j < n; j++) {
            sum += matrix[i][j] * x[j];
        }
        x[i] = (matrix[i][n] - sum) / matrix[i][i];
    }
}
 
// void stress_test(){
    
//     // int n = rand()%3+1;
//     // vector<vector<double>> matrix (n, vector<double> (n+1));
//     int n =3;
//     vector<vector<double>> matrix{{3.0, 2.0,-4.0, 3.0},
//                               {2.0, 3.0, 3.0, 15.0},
//                               {5.0, -3, 1.0, 14.0}
//                              };
//     vector<vector<double>> matrix2{{3.0, 2.0,-4.0, 3.0},
//                               {2.0, 3.0, 3.0, 15.0},
//                               {5.0, -3, 1.0, 14.0}
//                              };
//     // for(int i=0; i<n; i++){
//     //     for(int j=0; j<n+1; j++){
//     //         matrix[i][j] = (rand()%1000);
//     //         cout<<matrix[i][j] << " ";
//     //     }
//     //     cout<<endl;
//     // }
//     partial_pivot(matrix);
//     vector<double> x(matrix.size(), 0);
//     back_substitute(matrix, x);

//     Equation equation = RReadEquation(matrix2, n);
//     Column solution = SolveEquation(equation);

//     for(int i=0; i<matrix.size(); i++){
//         cout<<solution[i] <<"  " << x[i] << endl;
//     }
// }
int main() {
    // srand(time(NULL));
    Equation equation = ReadEquation();
    SolveEquation(equation);
    // PrintColumn(solution);
    // stress_test();
    return 0;
}
