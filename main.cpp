#include <iostream>
#include <vector>
#include <numeric> //accumulate
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

void printVector(vector<vector<int>> my_vect){
    /* Function iterates over the values in 2D vector and prints them. */
    cout << "{ "  << endl;
    for (int i = 0; i < my_vect.size() ; ++i) {
        printVector(my_vect[i]);
    }
    cout << endl << "}" << endl ;
}

void printVector(vector<vector<vector<int>>> my_vect){
    /* Function iterates over the values in 3D vector and prints them. */
    for (int i = 0; i < my_vect.size() ; ++i) {
        for (int j = 0; j < my_vect[i].size() ; ++j) {
            printVector(my_vect[i][j]);
        }
        cout << endl;
    }
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

//Rejects invalid paths where the jump is bigger than 1 index at the time (eg. 2-2-2-0-2)
bool isValid(vector<int> path) {
    for (int i = 0; i < path.size() - 1; ++i) {
        if (abs(path[i] - path[i + 1]) > 1)
            return false;
    }
    return true;
}

vector<vector<int>> cartesianProduct( vector<vector<int> >& v ) {
    auto product = []( long long a, vector<int>& b ) { return a*b.size(); };
    const long long N = accumulate( v.begin(), v.end(), 1LL, product );

    vector<vector<int>> result;
    vector<int> u(v.size());

    for( long long n=0 ; n<N ; ++n ) {
        lldiv_t q { n, 0 };
        for( long long i=v.size()-1 ; 0<=i ; --i ) {
            q = div( q.quot, v[i].size() );
            u[i] = v[i][q.rem];
        }

        // Do what you want here with u.
        if(isValid(u))
            result.push_back(u);
    }
    return result ;
}

int countPoints(vector<int> path, int tab[3][5]){
    int sum = 0, col = 0;
    for(auto ind: path) {
        sum += tab[ind][col];
        col++;
    }
    return sum;
}

int main() {
    int tablica[3][5]= {
            {6, 2, 6, 1, 7},
            {4, 9, 5, 5, 8},
            {3, 1, 4, 5, 6}
            };

    vector<vector<vector<int>>> indexes;
    vector<vector<vector<int>>> paths;
    vector<int> diagonals;

    int result_val = INT_MAX;
    vector<int> result_vect;

    int height = sizeof(tablica)/sizeof(tablica[0]);
    int width = sizeof(tablica[0])/sizeof(int);

    //Diagonals loop
    for (int startingPoint = 0; startingPoint < height ; ++startingPoint) {
        indexes.push_back({});
        diagonals = {startingPoint};
        indexes[startingPoint].push_back(diagonals);
        for(int column = 0; column < width-1; ++column){
            diagonals = getDiagonals(diagonals, height);
            indexes[startingPoint].push_back(diagonals);
        }
    }

    //Populate paths
    for(auto point:indexes)
        paths.push_back(cartesianProduct(point));

    //Count points for each path
    int temp_points;
    for(auto startingPoint: paths)
        for(auto path: startingPoint) {
            temp_points = countPoints(path, tablica);
            if(temp_points < result_val) {
                result_val = temp_points;
                result_vect = path;
            }
        }

    cout << "sum : " << result_val << endl;
    printVector(result_vect);
    return 0;
}