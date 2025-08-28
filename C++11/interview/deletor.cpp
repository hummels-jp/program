#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;

// 自定义文件删除器
struct FileDeletor {
    void operator()(FILE* fp) const {
        if (fp) {
            cout << "Closing file..." << endl;
            fclose(fp);
        }
    }
};

int main() {
    unique_ptr<FILE, FileDeletor> filePtr(fopen("test.txt", "w"));
    if (filePtr) {
        fprintf(filePtr.get(), "Hello, unique_ptr with custom deletor!\n");
    }
    // 离开作用域时自动调用 FileDeletor 关闭文件
    return 0;
}