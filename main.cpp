#include <iostream>
#include <vector>
#include <algorithm> //min_element, max_element

using namespace std;


int vectorMin(vector<int> diagonals){
    /* Returns lowest value of the vector.*/
    int minimum = diagonals[0];
    for (int i = 0; i < diagonals.size() ; ++i) {
        if(diagonals[i] < minimum){
            minimum = diagonals[i];
        }
    }
    return minimum;
}

int vectorMax(vector<int> diagonals){
    /* Returns highest value of the vector.*/
    int maximum = -1;
    for (int i = 0; i < diagonals.size() ; ++i) {
        if(diagonals[i] > maximum){
            maximum = diagonals[i];
        }
    }
    return maximum;
}

void printVector(vector<int> my_vect){
    /* Function iterates over the values in vector and prints them. */
    cout << "{ ";
    for (int i = 0; i < my_vect.size() ; ++i) {
        cout << my_vect[i] << ", ";
    }
    cout << " }";
}

vector<int> getDiagonals(vector<int> diagonals, int arr_height){
    /* Function extends the vector array with possible indexes on every step/column.
     * eg. step 1: starting point 0, step 2: point 0 (going right) + point 1 (going diagonal) (cant go up, below index 0)
     * eg. step 1: starting point 1, step 2: point 0 (diagonal up) + point 1 (going right) + point 2 (diagonal down)
     * */
    auto mymin = vectorMin(diagonals);
    auto mymax = vectorMax(diagonals);
    if(mymin > 0) {
        diagonals.insert(diagonals.end(), mymin - 1);
    }
    if(mymax + 1 < arr_height){
        diagonals.insert(diagonals.end(), mymax + 1);
    }

    return diagonals;
}


int main() {
    //Input, declarations
    int tablica[3][5]= {
            {6, 2, 6, 1, 7},
            {4, 9, 5, 5, 8},
            {3, 1, 4, 5, 6}
            };

    vector<int> diagonals;
    vector<vector<vector<int>>> indexes;

    int height = sizeof(tablica)/sizeof(tablica[0]);
    int width = sizeof(tablica[0])/sizeof(int);

    for (int startingPoint = 0; startingPoint < height ; ++startingPoint) {
        indexes.push_back({});
        diagonals = {startingPoint};
        indexes[startingPoint].push_back(diagonals);
        for(int column = 0; column < width-1; ++column){
            diagonals = getDiagonals(diagonals, height);
            indexes[startingPoint].push_back(diagonals);
        }
    }


    for (int i = 0; i < indexes.size() ; ++i) {
        cout << "{";
        for (int j = 0; j < indexes[i].size(); ++j) {
            printVector(indexes[i][j]);
        } cout << endl;
    } cout << "} ";


    return 0;
}


