#include <stdio.h>

int main() {
    int ch;
    // 从标准输入读取字符，直到遇到 EOF（例如 Ctrl+D）
    while ((ch = getc(stdin)) != EOF) {
        putc(ch, stdout);
    }
    return 0;
}