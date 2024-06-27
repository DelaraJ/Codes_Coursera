#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-6;
const int PRECISION = 20;

typedef vector<double> Column;
typedef vector<double> Row;
typedef vector<Row> Matrix;

void roundToPrecision(double& number, int precision = 15) {
    double factor = std::pow(10.0, precision);
    number = round(number * factor) / factor;
}

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
            swap(b[i], b[row_num]);
            double pivot_num = a[i][i];
            for(int j=i; j<size; j++){
                a[i][j]/=pivot_num;
                roundToPrecision(a[i][j]);
            }
            b[i]/=pivot_num;
            roundToPrecision(b[i]);
            for(int j=0; j<size; j++){
                if(j==i) continue;
                double x = a[j][i];
                for(int k=0; k<size; k++){
                    a[j][k]-=x*a[i][k];
                    roundToPrecision(a[j][k]);
                }
                b[j]-=x*b[i];
                roundToPrecision(b[j]);
            }

        }
    }
    // for(int i= size-2; i>=0; i--){
    //     for(int j=i+1; j<size; j++){
    //         b[i] -= a[i][j]*b[j];
    //     }
    // }
    // return b;
    cout.precision(PRECISION);
    for (int row = 0; row < size; ++row){
        if(b[row] == -0) cout << 0 << endl;
        else cout << b[row] << endl;
    }
}

void PrintColumn(const Column &column) {
    int size = column.size();
    cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        cout << column[row] << endl;
}

int main() {
    Equation equation = ReadEquation();
    SolveEquation(equation);
    return 0;
}
