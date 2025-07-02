总结表
锁类型	是否递归	是否共享	是否超时	C++ 标准库支持
std::mutex	否	否	否	是
std::timed_mutex	否	否	是	是
std::recursive_mutex	是	否	否	是
std::recursive_timed_mutex	是	否	是	是
std::shared_mutex	否	是	否	C++17 起
std::shared_timed_mutex	否	是	是	C++14 起


标准库中的 RAII 锁主要包括以下几种：
类名	主要特点	是否支持 unlock	是否可移动	支持多锁	适用场景
std::lock_guard	简单、作用域锁定	否	否	否	简单临界区
std::unique_lock	灵活、功能丰富	是	是	否	复杂同步/条件变量
std::scoped_lock	支持多锁，防死锁	否	否	是	多资源同步（C++17）
