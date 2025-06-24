#include <sys/time.h>
#include <iostream>
using namespace std;

int main()
{
    itimerval itime_new;
    itime_new.it_value.tv_sec = 1;
    itime_new.it_value.tv_usec = 0;

    itime_new.it_interval.tv_sec = 0;
    itime_new.it_interval.tv_usec = 0;

    itimerval itime_old;

    setitimer(ITIMER_REAL, &itime_new, &itime_old);

    while (true)
    {
        /* code */
        cout << "hello, world" << endl;
    }
    
}