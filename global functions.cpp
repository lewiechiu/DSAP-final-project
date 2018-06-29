using namespace std;
#include <time.h>
#include <iostream>
int now()
{
    time_t seconds;
    time(&seconds);
    cout << seconds << endl;
}
