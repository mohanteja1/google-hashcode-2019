//this will work ,it is the most brute force you might ever encounter minimum 10 hrs for a test case list of 550,000
//executes at two node per second

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
//COMPLEXITY:   22 hours for test cases size = 80,000          MEMORY: 34 t0 48 M

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
#define DEBUG if (0)
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
using std::ostream;
using std::vector;

template <class T>
T sq(T &x) { return x * x; }
template <class T>
T abs(T &n) { return (n < 0 ? -n : n); }
template <class T>
T max(T &a, T &b) { return (!(a < b) ? a : b); }
template <class T>
T min(T &a, T &b) { return (a < b ? a : b); }
template <class T>
T gcd(T a, T b) { return (b != 0 ? gcd<T>(b, a % b) : a); }
template <class T>
T lcm(T a, T b) { return (a / gcd<T>(a, b) * b); }
template <class T>
T mod(T &a, T &b) { return (a < b ? a : a % b); }
template <class T>
bool inside(T &a, T &b, T &c) { return a <= b && b <= c; }
template <class T>
void setmax(T &a, T b)
{
    if (a < b)
        a = b;
}
template <class T>
void setmin(T &a, T b)
{
    if (b < a)
        a = b;
}

const int INF = 1000000001;
const double EPS = 1e-10;
const int MAX = 100001;

using namespace std;

void printImage(pair<pair<int, char>, pair<int, vector<string>>> image)
{
    cout << "---------------------------------------" << endl;
    cout << image.first.first << " " << image.first.second << " " << image.second.first << " " << endl;
    std::copy(image.second.second.begin(), image.second.second.end(), std::ostream_iterator<string>(std::cout, " "));
    cout << "\n---------------------------------------" << endl;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
pair<int, vector<int>> interestingFactorCal(vector<string> image1Tags, vector<string> image2Tags)
{
    // cout << "if" << endl;

    //calculate interesting factor between two tag lists return interestin factor and indexs in l1 having similartags in l2
    int len1 = image1Tags.size();
    int len2 = image2Tags.size();
    std::vector<string>::iterator it;
    int count = 0;
    vector<int> similarTags;
    for (int i = 0; i < len1; i++)
    {
        it = find(image2Tags.begin(), image2Tags.end(), image1Tags.at(i));
        if (it != image2Tags.end())
        {
            count++;
            similarTags.push_back(i);
        }
    }
    return make_pair(min(min(count, len1 - count), len2 - count), similarTags);
}

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
vector<string> mergeTags(vector<string> image1Tags, vector<string> image2Tags, vector<int> similar1Tags)
{
    // cout << "mergeTags" << endl;
    //merges two tag lists
    int len1 = image1Tags.size();
    int len2 = image2Tags.size();
    std::vector<string>::iterator it;
    int count = similar1Tags.size();
    for (int i = 0; i < count; i++)
    {
        it = image1Tags.begin();
        if (it != image2Tags.end())
            image1Tags.erase(it + similar1Tags.at(i), it + similar1Tags.at(i) + 1); //erases similar tags in second list
    }
    //merge two lists
    image1Tags.insert(image1Tags.end(), image2Tags.begin(), image2Tags.end());

    return image1Tags;
}
/*--------------------------------------------------------------photoSlideMaker-----------------------------------------------------------------*/

vector<pair<char, pair<int, int>>> photoSlideMaker(vector<pair<pair<int, char>, pair<int, vector<string>>>> *images, string *imageFlagArray, vector<int> *vArray)
{
    //this makes the slide show
    //output  |type | two images index

    vector<pair<char, pair<int, int>>> imagesOrder;
    //pretty bruteforce

    int length = imageFlagArray->length();
    pair<int, vector<int>> tempIfac = make_pair(0, vector<int>()),
                           maxIfac = make_pair(-1, vector<int>());
    int verticalFlag = 0;
    int currentIndex = 0, maxIndex = 0;
    int nextImageFound = 0;
    int vArrayLen = vArray->size();
    //push first element in images
    imagesOrder.push_back(make_pair(images->at(0).first.second, make_pair(0, -1)));
    imageFlagArray->at(0) = '0';

    //char lastPushedImagetype = images->at(0).first.second;

    vector<string> currentLinkTags;

    //search for next best element and add it current element and make it zero in imageFlag

    for (int i = 1; i < length; i++)
    {

        //scan each element with every other element for maximum interesting factor

        //skip since image is already appended

        //on or off verical flag in case of vertical images
        verticalFlag = (verticalFlag + ((imagesOrder.back().first == 'V') ? 1 : 0)) % 2;
        //cout<< "vflag :" << verticalFlag <<endl;
        currentLinkTags.clear();

        if (imagesOrder.back().first == 'V' && verticalFlag == 0)
        //if last image pushed is 2 Vs then merge their tags into single
        {

            currentLinkTags = mergeTags(images->at(imagesOrder.back().second.first).second.second, images->at(imagesOrder.back().second.second).second.second, maxIfac.second);
            currentIndex = imagesOrder.back().second.second;
        }
        else
        { //else one v or a H then dont mind
            currentLinkTags = images->at(imagesOrder.back().second.first).second.second;
            currentIndex = imagesOrder.back().second.first;
        }

        //  cout << "currentIndex" << endl;
        //  printImage(images->at(currentIndex));

        // find best next image
        nextImageFound = 0;
        // cout<<"searching for next"<< endl;

        if (verticalFlag)
        {
            int currentVindex;
            for (int k = 0; k < vArrayLen; k++)
            {
                currentVindex = vArray->at(k);
                if (imageFlagArray->at(currentVindex) == '0' || currentIndex == currentVindex)
                    continue;

                tempIfac = interestingFactorCal(currentLinkTags, images->at(currentVindex).second.second);

                // cout << j << " " << tempIfac.first <<endl;
                //modify if maximum
                if (tempIfac.first > maxIfac.first)
                {
                    nextImageFound = 1;
                    maxIfac = tempIfac;
                    maxIndex = currentVindex;
                    //     cout <<"maxIndex" << maxIndex <<endl;
                }
            }
        }
        else
        {
            for (int j = 0; j < length; j++)
            {
                if (imageFlagArray->at(j) == '0' || currentIndex == j)
                    continue;

                if (verticalFlag && images->at(j).first.second == 'H')
                    continue;

                //current IF
                tempIfac = interestingFactorCal(currentLinkTags, images->at(j).second.second);

                // cout << j << " " << tempIfac.first <<endl;
                //modify if maximum
                if (tempIfac.first > maxIfac.first)
                {
                    nextImageFound = 1;
                    maxIfac = tempIfac;
                    maxIndex = j;
                    //     cout <<"maxIndex" << maxIndex <<endl;
                }
            }
        }
        //found image then push its details
        if (nextImageFound)
        {
            //if verticalflag on
            if (verticalFlag)
            {
                imagesOrder.back().second.second = maxIndex;
                cout << imagesOrder.back().second.first << " " << imagesOrder.back().second.second << endl; // " | if =" << maxIfac.first  <<endl;
            }
            else
            {
                imagesOrder.push_back(make_pair(images->at(maxIndex).first.second, make_pair(maxIndex, -1)));
                cout << imagesOrder.back().second.first << " " << endl; //"     | if =" << maxIfac.first  <<endl;
            }
            imageFlagArray->at(maxIndex) = '0';

            //  cout<<"nextImage at maxIndex"<<endl;
            //  printImage(images->at(maxIndex));
            //  //start again
            tempIfac = make_pair(0, vector<int>()),
            maxIfac = make_pair(-1, vector<int>());
        }
    }

    return imagesOrder;
}

/*---------------------------------------------------------------------main--------------------------------------------------------------------*/
int main()
{

    // your code here
    int noOfImages;
    cin >> noOfImages;

    vector<pair<pair<int, char>, pair<int, vector<string>>>> images;
    string imageFlagArray(noOfImages, '1');
    int i = 0, noOfTags;
    char HV;

    vector<int> vArray;
    while (i < noOfImages)
    {

        cin >> HV;

        if (HV == 'V')
            vArray.push_back(i);

        cin >> noOfTags;
        vector<string> stringArray;
        string tag;
        for (int j = 0; j < noOfTags; j++)
        {
            cin >> tag;
            stringArray.push_back(tag);
        }
        images.push_back(make_pair(make_pair(i, HV), make_pair(noOfTags, stringArray)));
        stringArray.clear();
        i++;
    }

    //print whether vector is working fine;
    // cout << "NO ty tg " << endl;
    // for (int i = 0; i < images.size(); i++)
    // {
    //     printImage(images.at(i));
    // }

    vector<pair<char, pair<int, int>>> imagesOrder = photoSlideMaker(&images, &imageFlagArray, &vArray);

    //prints output
    // cout << imagesOrder.size() << endl;
    // for (int i = 0; i < imagesOrder.size(); i++)
    // {
    //     if (imagesOrder.at(i).first == 'H')
    //         cout << imagesOrder.at(i).second.first << endl;
    //     else
    //         cout << imagesOrder.at(i).second.first << " " << imagesOrder.at(i).second.second << endl;
    // }

    return 0;
}