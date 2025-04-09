#include "lock_guard.h"
#include "unique_lock.h"
#include "shared_mutex.h"
#include "atomic.h"
#include "conditional_variable.h"
#include <iostream>
#include "semaphore.h" // Custom header for semaphore operations

int main()
{
    // lock_guard_demo();
    // unique_lock_demo();
    // shared_mutext_demo();
    // atomic_demo();
    // conditional_variable_demo();
    semaphore_demo(); // Call the semaphore demo function
    return 0;
}