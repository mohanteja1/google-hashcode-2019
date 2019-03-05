// PROBLEM:
// AIM : given something find something.
// CONSTRAINTS:
/* TEST CASES:  INPUT   SOLUTION
        1            -->
        2           -->
 */

/* ALGORITHM1:
              1.READ INPUT AS STRING TO REDUCE THE MEMORY
              2.
              3.
              4.
   */
//COMPLEXITY:              MEMORY:

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
#define DEBUG if(0)
#define PAUSE system("pause")
#define READ(f) freopen(f, "r", stdin)
#define WRITE(f) freopen(f, "w", stdout)
#define ALL(c) c.begin(), c.end()
#define PB(x) push_back(x)
#define UB(s, e, x) upper_bound(s, e, x)
#define LB(s, e, x) lower_bound(s, e, x)
#define REV(s, e) reverse(s, e);
#define SZ(c) c.size()
#define SET(p) memset(p, -1, sizeof(p))
#define CLR(p) memset(p, 0, sizeof(p))
#define MEM(p, v) memset(p, v, sizeof(p))
#define i64 long long
#define ff first
#define ss second
#define i64 long long
#define FS "%lld"

template< class T > T sq(T &x) { return x * x; }
template< class T > T abs(T &n) { return (n < 0 ? -n : n); }
template< class T > T max(T &a, T &b) { return (!(a < b) ? a : b); }
template< class T > T min(T &a, T &b) { return (a < b ? a : b); }
template< class T > T gcd(T a, T b) { return (b != 0 ? gcd<T>(b, a%b) : a); }
template< class T > T lcm(T a, T b) { return (a / gcd<T>(a, b) * b); }
template< class T > T mod(T &a, T &b) { return (a < b ? a : a % b); }
template< class T > bool inside(T &a, T &b, T &c) { return a<=b && b<=c; }
template< class T > void setmax(T &a, T b) { if(a < b) a = b; }
template< class T > void setmin(T &a, T b) { if(b < a) a = b; }


const int INF = 1000000001;
const double EPS = 1e-10;
const int MAX = 100001;

using namespace std;

vector<pair<int,int>>  kernelGenerator(int minSize,int maxSize){
 //returns kernels 
  vector<pair<int ,int>> kernels;

 int temp;
 for(int i=minSize ; i<=maxSize ; i++)
 {
     temp=1;
     while (temp <= i)
    {
        if (!( i % temp))
            kernels.push_back(make_pair(temp,i/temp));
        temp++;
    }
 }
 // cout<< "kernels" <<endl;

  //std::copy(kernels.begin(), kernels.end(), std::ostream_iterator<pair<int,int>>(std::cout, " "));
  
// for(int i=0;i<kernels.size();i++){
//     cout<< kernels.at(i).first << " " << kernels.at(i).second<<endl;
// }

  return kernels;
}

// vector<pair<int,int>> listBoundaryPoints(int topLeftX,int topLeftY,int bottomRightX,int bottomRightY,int rows,int cols){
//     //lists boundary points
// }

bool isKernelOk(pair<int,int> coordinate,vector<string> *matrix,pair<int,int> kernel,vector<string>* flagMatrix,int minNoOfIngred){
    int tomatoe=minNoOfIngred,mushroom=minNoOfIngred;
    
  

    if(flagMatrix->at(coordinate.first).at(coordinate.second)=='x')
       return false;

    if(coordinate.first+kernel.first> matrix->size()||coordinate.second+kernel.second > matrix->at(0).length())
       return false;

    for(int i = coordinate.first;i<coordinate.first + kernel.first;i++){
         for(int j=coordinate.second;j<coordinate.second+kernel.second;j++)
                        {
                            if(flagMatrix->at(i).at(j)=='0')
                               return false;

                            if(matrix->at(i).at(j)=='T')tomatoe--;
                              else mushroom--;  
                       
                        }

    }
  if(tomatoe<=0 && mushroom <=0) 
        return true;
    else
        return false;
}

pair<int,int> findOptimalKernel(pair<int,int> coordinate,int minNoOfIngred,vector<pair<int,int>> kernels,vector<string>*matrix,vector<string>*flagMatrix){
    


    for(int i=kernels.size()-1;i>=0;i--)
    {
        //optimise implement best kernel first if possible
       if(isKernelOk(coordinate,matrix,kernels.at(i),flagMatrix,minNoOfIngred))
            return kernels.at(i);
        
    
    }

    flagMatrix->at(coordinate.first).at(coordinate.second)='x';


return make_pair(-1,-1) ;
}

void markZeros(vector<string> *flagMatrix,pair<int,int> coordinate,pair<int,int> kernel){
   //updates flagmatrix 

    if(flagMatrix->at(coordinate.first).at(coordinate.second)=='x')
       return ;

   if(coordinate.first+kernel.first> flagMatrix->size()||coordinate.second+kernel.second > flagMatrix->at(0).length())
       return ;

   for(int i = coordinate.first;i<coordinate.first + kernel.first;i++)
         for(int j=coordinate.second;j<coordinate.second+kernel.second;j++)
                        flagMatrix->at(i).at(j)='0';

  return;

}


vector<pair<pair<int,int>,pair<int,int>>> pizzaSlicer(vector<string> *matrix,vector<string> *flagmatrix,int rows,int cols,int minNoOfIngred,int maxSize)
{ 
    


    //all the kernels required
    vector<pair<int ,int>> kernels ;
    kernels = kernelGenerator(minNoOfIngred*2,maxSize);
    
    //list of coordinate to be sent
     vector<pair<pair<int,int>,pair<int,int>>> coordinates ;
     
     pair<int ,int > optimalCoordinate,optimalKernel;

     vector<pair<int,int>> boundaryCoordinates;
     boundaryCoordinates.push_back(make_pair(0,0));
    
    //apply the kernels on each boundary points

      for(int i=0;i<rows;i++){
         {  
           //  printf("ps\n");
              for(int j=0; j<cols; )
              {

                  if(flagmatrix->at(i).at(j)== '1')
                   { 
                      

                       optimalKernel=findOptimalKernel(make_pair(i,j),minNoOfIngred,kernels,matrix,flagmatrix);
                       
                       if(optimalKernel.first!=-1)
                          {
                                                  

                              markZeros(flagmatrix,make_pair(i,j),optimalKernel);
                              coordinates.push_back(make_pair(make_pair(i,j),make_pair(i+optimalKernel.first-1,j+optimalKernel.second-1)));
                              j=j+optimalKernel.second-1;
                              
                          }
                        else{
                            j++;
                        }
                         
                   }
                   else
                      j++;
         
              }            
            
                  
         }            
         
      }

    //

    return coordinates ;
}


int main()
{

	// your code here
    
    int rows,cols,min,maxSize;

	cin >> rows;
    cin >> cols;
	cin >> min;
	cin >> maxSize;
     
    vector<string> matrix(rows); 
    vector<string> flagMatrix(rows);
    string flagMatrixline(cols,'1'); 

    int i=0;

	while (i<rows)
	{
		cin >> matrix.at(i);
        flagMatrix.at(i).append(flagMatrixline);
        i++;
	}

    vector<pair<pair<int,int>,pair<int,int>>> coordinates ;
    coordinates = pizzaSlicer(&matrix,&flagMatrix,rows,cols,min,maxSize);
    
    cout<<coordinates.size()<<endl;
    for(int i=0;i<coordinates.size();i++ )
    {
        cout << coordinates.at(i).first.first << " " << coordinates.at(i).first.second << " " << coordinates.at(i).second.first << " " <<coordinates.at(i).second.second << endl;
    }


   // std::copy((*coordinates).begin(),(*coordinates).end(), std::ostream_iterator<pair<pair<int,int>,pair<int,int>>>(std::cout, " "));


	return 0;
}