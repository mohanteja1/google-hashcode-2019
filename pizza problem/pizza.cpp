// PROBLEM:
// AIM : FIND SOLUTION FOR PIZZA PROBLEM
// CONSTRAINTS:
/* TEST CASES:  INPUT   SOLUTION
        1            -->
        2           -->
 */

/* ALGORITHM1:
              1.READ INPUT MATRIX AS STRING TO REDUCE THE MEMORY
              2.FIND THE FACTORIAL KERNELS (EACH SIZE OF THE PIECE THAT CAN BE CUT DOWN)
              3.APPLY THESE KERNELS OVER THE MATRIX( RASTER SCAN ) FIND OPTIMAL ONE
              4.UPDATE COORDINATES OF SLICES (PRINT)
   */
//COMPLEXITY:  O(n^2)            MEMORY: 20 MB

//SCORE: 9.35 LAKH IN GOOGLE JUDGE

//BY MOHANTEJA

#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <utility>

using namespace std;

vector<pair<int, int>> kernelGenerator(int minSize, int maxSize)
{   
    //calculates all the factors for the number x ranging from minSize and MaxSize 
    // kernels for number 6 --> (1x6) ,(2x3),(3x2),(6x1)
    //returns kernels
    vector<pair<int, int>> kernels;

    int temp;
    for (int i = minSize; i <= maxSize; i++) //calculates factors
    {
        temp = 1;
        while (temp <= i)
        {
            if (!(i % temp))
                kernels.push_back(make_pair(temp, i / temp));
            temp++;
        }
    }
   
    return kernels;
}


 vector<pair<int,int>> listBoundaryPoints(int topLeftX,int topLeftY,int bottomRightX,int bottomRightY,int rows,int cols){
   //lists boundary points of applied kernel
      //implement code for optimization 

      return {};
 }



bool isKernelOk(pair<int, int> coordinate, vector<string> *matrix, pair<int, int> kernel, vector<string> *flagMatrix, int minNoOfIngred)
{
    //checks 
    int tomatoe = minNoOfIngred, mushroom = minNoOfIngred;
    if (flagMatrix->at(coordinate.first).at(coordinate.second) == 'x')
        return false;
    if (coordinate.first + kernel.first > matrix->size() || coordinate.second + kernel.second > matrix->at(0).length())
        return false;
    for (int i = coordinate.first; i < coordinate.first + kernel.first; i++)
    {
        for (int j = coordinate.second; j < coordinate.second + kernel.second; j++)
        {
            if (flagMatrix->at(i).at(j) == '0')
                return false;

            if (matrix->at(i).at(j) == 'T')
                tomatoe--;
            else
                mushroom--;
        }
    }
    if (tomatoe <= 0 && mushroom <= 0)
        return true;
    else
        return false;
}

pair<int, int> findOptimalKernel(pair<int, int> coordinate, int minNoOfIngred, vector<pair<int, int>> kernels, vector<string> *matrix, vector<string> *flagMatrix)
{

    for (int i = kernels.size() - 1; i >= 0; i--)
    {
        //optimise implement best kernel first if possible here
        if (isKernelOk(coordinate, matrix, kernels.at(i), flagMatrix, minNoOfIngred))
            return kernels.at(i);
    }

    flagMatrix->at(coordinate.first).at(coordinate.second) = 'x';

    return make_pair(-1, -1);
}

void markZeros(vector<string> *flagMatrix, pair<int, int> coordinate, pair<int, int> kernel)
{
    //updates flagmatrix

    if (flagMatrix->at(coordinate.first).at(coordinate.second) == 'x')
        return;

    if (coordinate.first + kernel.first > flagMatrix->size() || coordinate.second + kernel.second > flagMatrix->at(0).length())
        return;

    for (int i = coordinate.first; i < coordinate.first + kernel.first; i++)
        for (int j = coordinate.second; j < coordinate.second + kernel.second; j++)
            flagMatrix->at(i).at(j) = '0';

    return;
}

vector<pair<pair<int, int>, pair<int, int>>> pizzaSlicer(vector<string> *matrix, vector<string> *flagmatrix, int rows, int cols, int minNoOfIngred, int maxSize)
{

    //generate kernels: all the possible rectangular slices that fit given constraints
    vector<pair<int, int>> kernels;
    kernels = kernelGenerator(minNoOfIngred * 2, maxSize);

    //list of coordinate to be sent
    vector<pair<pair<int, int>, pair<int, int>>> coordinates;

    pair<int, int> optimalCoordinate, optimalKernel;
         
    vector<pair<int, int>> boundaryCoordinates;
    boundaryCoordinates.push_back(make_pair(0, 0));


    //apply the kernels row wise checking flag matrix

    for (int i = 0; i < rows; i++)
    {
            for (int j = 0; j < cols;)
            {
                if (flagmatrix->at(i).at(j) == '1') //piece is available
                {
                     //find best slice that can be applied on that point
                    optimalKernel = findOptimalKernel(make_pair(i, j), minNoOfIngred, kernels, matrix, flagmatrix);
                    
                    if (optimalKernel.first != -1) //if atleast a kernel can be applied
                    {
                       //mark zeros in flag matrix indicating pieces are cut
                        markZeros(flagmatrix, make_pair(i, j), optimalKernel);
                       // push the coordinates of that slice
                        coordinates.push_back(make_pair(make_pair(i, j), make_pair(i + optimalKernel.first - 1, j + optimalKernel.second - 1)));
                        j = j + optimalKernel.second - 1;
                    }
                    else  //else iterate for next slice 
                    {           
                        j++;
                    }
                }
                else  //else increament next slice in row 
                    j++;
            }
    }

    return coordinates;
}

int main()
{
    

    int rows, cols, min, maxSize;

    cin >> rows;
    cin >> cols;
    cin >> min;
    cin >> maxSize;

    vector<string> matrix(rows); //matrix for pizza

    vector<string> flagMatrix(rows); //matrix for marking cutted pizza slices 
    string flagMatrixline(cols, '1');

    int i = 0;

    while (i < rows)
    {
        cin >> matrix.at(i);
        flagMatrix.at(i).append(flagMatrixline);
        i++;
    }
    //output type defination : coordinates of topleft and bottom right points of each pizza slice cutted
    vector<pair<pair<int, int>, pair<int, int>>> coordinates;

     //call the pizza slicer
    coordinates = pizzaSlicer(&matrix, &flagMatrix, rows, cols, min, maxSize);


     //print the slices 

    cout << coordinates.size() << endl;
    for (int i = 0; i < coordinates.size(); i++)
    {
        cout << coordinates.at(i).first.first << " " << coordinates.at(i).first.second << " " << coordinates.at(i).second.first << " " << coordinates.at(i).second.second << endl;
    }

    // std::copy((*coordinates).begin(),(*coordinates).end(), std::ostream_iterator<pair<pair<int,int>,pair<int,int>>>(std::cout, " "));

    return 0;
}