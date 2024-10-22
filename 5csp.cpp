#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isValidSolution(const vector<int>& digits) {

    int E = digits[0], A = digits[1], T = digits[2], H = digits[3], P = digits[4], L = digits[5];

    int EAT = E * 100 + A * 10 + T;
    int THAT = T * 1000 + H * 100 + A * 10 + T;
    int APPLE = A * 10000 + P * 1000 + P * 100 + L * 10 + E;
   
    return (EAT + THAT == APPLE);
}

void solveCryptarithmetic() {  
    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  
    

    do {
        if (isValidSolution(digits)) {
            cout << "Solution found!" << endl;
            cout << "E = " << digits[0] << endl;
            cout << "A = " << digits[1] << endl;
            cout << "T = " << digits[2] << endl;
            cout << "H = " << digits[3] << endl;
            cout << "P = " << digits[4] << endl;
            cout << "L = " << digits[5] << endl;
        
            int EAT = digits[0] * 100 + digits[1] * 10 + digits[2];
            int THAT = digits[2] * 1000 + digits[3] * 100 + digits[1] * 10 + digits[2];
            int APPLE = digits[1] * 10000 + digits[4] * 1000 + digits[4] * 100 + digits[5] * 10 + digits[0];
            
            cout << "EAT = " << EAT << endl;
            cout << "THAT = " << THAT << endl;
            cout << "APPLE = " << APPLE << endl;
            cout << "Exact equation: " << EAT << " + " << THAT << " = " << APPLE << endl;
            return;
        }
    } while (next_permutation(digits.begin(), digits.end()));
    
    cout << "No solution found." << endl;
}

int main() {
    solveCryptarithmetic();
    return 0;
}