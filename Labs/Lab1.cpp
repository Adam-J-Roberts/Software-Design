#include <chrono> 
#include <iostream> 
#include <cstdlib>
#include <cmath>
//int diff = std::abs(x-y);

using namespace std; 
using namespace std::chrono; 
  

int main() 
{ 
  
    long long a = 1232;
    double c = 1232;
    int x;
    int loops = 1'000'000'000;
    cout.imbue(std::locale(""));

    // Ignore this. First one is amiss.
    auto start = high_resolution_clock::now(); 
    a+a;
    auto stop = high_resolution_clock::now();     // Test speed of long lond addition and saving



    // Test speed of long long addition
    start = high_resolution_clock::now(); 
    for(int i = loops; i>0; i--)
    {   
        a += a;
    }
    stop = high_resolution_clock::now();   
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "LongLong save and add: " << duration.count() << " nanoseconds."<< endl;
    x=duration.count();
    // Test speed of double addition and saving
    start = high_resolution_clock::now(); 
    for(int i = loops; i>0; i--)
    {   
        c += c;
    }
    stop = high_resolution_clock::now();   
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Double save and add: " << duration.count() << " nanoseconds." << endl;
    cout << "Difference: " << abs(x-duration.count()) << " nanoseconds." << endl << endl;

    // Test speed of LongLong multiplication
    start = high_resolution_clock::now(); 
    for(int i = loops; i>0; i--)
    {   
        a *= a;
    }
    stop = high_resolution_clock::now();   
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "LongLong multiplication ONLY!: " << duration.count() << " nanoseconds."<< endl;
    x=duration.count();

    // Test speed of double multiplication
    start = high_resolution_clock::now(); 
    for(int i = loops; i>0; i--)
    {   
        c *= c;
    }
    stop = high_resolution_clock::now();   
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Double multiplication ONLY!: " << duration.count() << " nanoseconds."<< endl;
    cout << "Difference: " << abs(x-duration.count()) << " nanoseconds." << endl << endl;

    //////////////////////////////////////////////////////////////////////////////
    ////////////                Extra Credit                          //////////// 
    //////////////////////////////////////////////////////////////////////////////    
    //test speed of multiDimensional arrays
    //Populating array
    srand (time(NULL));
    int ints[10][10];
    double dubs[10][10];

    for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			ints[row][col] = rand();
            dubs[row][col] = rand();
		}
	}

    //accessing my int array control
    start = high_resolution_clock::now(); 
    for(int i = loops; i>0; i--)
    { 
        ints[0][0];
    } 
    stop = high_resolution_clock::now(); 
    duration = duration_cast<nanoseconds>(stop - start); 
    int control  = duration.count();

    //Testing speed of int array row
    start = high_resolution_clock::now(); 
    for(int i = loops; i>0; i--)
    { 
        ints[7][0];
    } 
    stop = high_resolution_clock::now(); 
    duration = duration_cast<nanoseconds>(stop - start); 
    int row  = duration.count();

    //Testing speed of int array collumn
    start = high_resolution_clock::now(); 
    for(int i = loops; i>0; i--)
    { 
        ints[0][7];
    } 
    stop = high_resolution_clock::now(); 
    duration = duration_cast<nanoseconds>(stop - start); 
    int collumn  = duration.count();

    row -= control;
    collumn -= control;
    cout << "Time difference between the control and rows: " << abs(row) << " nanoseconds."<< endl;
    cout << "Time difference between the control and collums: " << abs(collumn) << " nanoseconds."<< endl;
    cout << "Time difference between rows and collums: " << abs(row-collumn) << " nanoseconds."<< endl;






    return 0; 
}