在 C++ 中，常见的锁类型主要有以下几种，主要定义在 `<mutex>` 和 `<shared_mutex>` 头文件中：

---

### 1. std::mutex（互斥锁）
- 最基本的互斥锁，单线程独占，不能递归加锁。
- 头文件：`<mutex>`

### 2. std::recursive_mutex（递归锁）
- 允许同一线程多次加锁，需对应多次解锁。
- 适用于递归调用时需要加锁的场景。
- 头文件：`<mutex>`

### 3. std::timed_mutex（定时互斥锁）
- 除了普通加锁，还可以设置超时时间尝试加锁。
- 头文件：`<mutex>`

### 4. std::recursive_timed_mutex（递归定时锁）
- 结合递归锁和定时锁。
- 头文件：`<mutex>`

### 5. std::shared_mutex（共享互斥锁，C++17及以上）
- 支持“多读单写”，即多个线程可以同时读取，写操作时独占。
- 头文件：`<shared_mutex>`

### 6. std::shared_timed_mutex（共享定时锁，C++14及以上，C++17被std::shared_mutex替代）
- 支持定时功能的共享锁。
- 头文件：`<shared_mutex>`

---

#### 结合锁的智能管理器

- **std::lock_guard\<MutexType\>**  
  自动加锁解锁，推荐用法，避免忘记解锁。

- **std::unique_lock\<MutexType\>**  
  功能更强，可以手动控制加锁/解锁、延迟加锁、条件变量配合使用。

- **std::shared_lock\<SharedMutexType\>** （C++17）  
  用于只读时上共享锁。

---

#### 总结表

| 锁类型                       | 递归 | 定时 | 多读 | 头文件          |
|-----------------------------|------|------|------|-----------------|
| std::mutex                  | 否   | 否   | 否   | <mutex>         |
| std::recursive_mutex        | 是   | 否   | 否   | <mutex>         |
| std::timed_mutex            | 否   | 是   | 否   | <mutex>         |
| std::recursive_timed_mutex  | 是   | 是   | 否   | <mutex>         |
| std::shared_mutex           | 否   | 否   | 是   | <shared_mutex>  |
| std::shared_timed_mutex     | 否   | 是   | 是   | <shared_mutex>  |

---

如需具体某种锁的用法示例，请告知！