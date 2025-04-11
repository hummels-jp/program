#include "lock_guard.h"
#include "unique_lock.h"
#include "shared_mutex.h"
#include "atomic.h"
#include "conditional_variable.h"
#include <iostream>
#include "semaphore.h" // Custom header for semaphore operations
#include "async.h" // Custom header for async operations
#include "promise.h" // Custom header for promise operations
#include "packaged_task.h" // Custom header for packaged_task operations
#include "thread_pool_demo.h" // Custom header for thread pool operations
#include "optional.h" // Custom header for optional operations
#include "regex_search.h"
#include "functor.h"
#include "mutex_demo.h"

int main()
{
    // lock_guard_demo();
    // unique_lock_demo();
    // shared_mutext_demo();
    // atomic_demo();
    conditional_variable_demo();
    // semaphore_demo(); // Call the semaphore demo function
    // async_demo(); // Call the async demo function
    // promise_demo(); // Call the promise demo function
    // packaged_task_demo(); // Call the packaged_task demo function
    // thread_pool_demo(); // Call the thread pool demo function
    // optional_demo(); // Call the optional demo function
    // template_function_demo(); // Call the template function demo
    // template_class_demo(); // Call the template class demo
    // template_class_object_parameter_demo(); // Call the template class with object parameter 
    friend_in_template_class_demo(); // Call the friend in template class demo
    return 0;
}