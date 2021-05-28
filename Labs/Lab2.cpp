#include <iostream> 
#include <cstdlib>

using namespace std; 

static int count = 30;

void fibonacci(int n1, int n2){

    if(count-2>0){
        int n3 = n1+n2;
        count--;
        cout << ", " << n3;
        fibonacci(n2, n3);
    }

} 

int main() 
{
    cout << "0, 1" ;
    fibonacci(0, 1);
    cout << endl;

    return 0;
}