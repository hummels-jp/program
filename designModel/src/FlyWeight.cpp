#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

// 享元接口：Font
class Font {
private:
    std::string fontName; // 内部状态

public:
    explicit Font(const std::string& name) : fontName(name) {}

    void display(const std::string& text) const {
        std::cout << "Displaying text: \"" << text << "\" with font: " << fontName << std::endl;
    }

    const std::string& getFontName() const {
        return fontName;
    }
};

// 享元工厂：FontPool
class FontPool {
private:
    std::unordered_map<std::string, std::shared_ptr<Font>> fontPool;

public:
    std::shared_ptr<Font> getFont(const std::string& fontName) {
        if (fontPool.find(fontName) == fontPool.end()) {
            std::cout << "FontPool: Creating new font: " << fontName << std::endl;
            fontPool[fontName] = std::make_shared<Font>(fontName);
        } else {
            std::cout << "FontPool: Reusing existing font: " << fontName << std::endl;
        }
        return fontPool[fontName];
    }
};

// 客户端代码
int main() {
    FontPool fontPool;

    // 获取字体对象
    auto font1 = fontPool.getFont("Arial");
    font1->display("Hello, World!");

    auto font2 = fontPool.getFont("Times New Roman");
    font2->display("Design Patterns in C++");

    auto font3 = fontPool.getFont("Arial");
    font3->display("Flyweight Pattern Example");

    return 0;
}