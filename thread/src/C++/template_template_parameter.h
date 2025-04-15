#ifndef TEMPLATE_TEMPLATE_PARAMETER_H
#define TEMPLATE_TEMPLATE_PARAMETER_H

#include <iostream>
#include <vector> // 示例容器

// 定义模板类
template <template <typename> class Container, typename T>
class TemplateContainer {
private:
    Container<T> data; // 使用模板容器

public:
    // 默认构造函数
    TemplateContainer() = default;

    // 自定义构造函数，使用容器赋值
    TemplateContainer(const Container<T>& container) : data(container) {}

    // 添加元素到容器
    void add(const T& value) {
        data.push_back(value);
    }

    // 打印容器内容
    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i];
            if (i < data.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

#endif // TEMPLATE_TEMPLATE_PARAMETER_H