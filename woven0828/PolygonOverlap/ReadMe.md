# PolygonOverlap 使用说明

## 编译方法

推荐使用 CMake 构建：

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

或者直接用 g++ 编译（需 C++11 及以上）：

```sh
g++ -std=c++11 -pthread -o PolygonOverlap main.cpp PolygonFilter.cpp ... # 省略其它源文件
```

## 运行参数

程序支持单线程和多线程两种模式，命令格式如下：

```
./PolygonOverlap <input_json> <output_json> <single|multi> [min_threads]
```

- `<input_json>`：输入多边形数据的 JSON 文件路径
- `<output_json>`：输出结果 JSON 文件路径
- `<single|multi>`：处理模式，`single` 为单线程，`multi` 为多线程
- `[min_threads]`：多线程模式下最小线程数（可选，默认2）

### 示例

单线程：
```
./PolygonOverlap ../input/convex_hulls_100.json ../output/output_100.json single
```

多线程（最小线程数为4）：
```
./PolygonOverlap ../input/convex_hulls_1000.json ../output/output_1000.json multi 4
```

## 输入输出格式

- 输入文件为 JSON 格式，包含多边形顶点信息。
- 输出文件为 JSON 格式，包含筛选后的多边形及其属性。

## 依赖

- C++11 或更高
- CMake 3.10+
- nlohmann/json（或兼容 JSON 库）

## 其他说明

- 程序会自动创建输出目录（如不存在）。
- 多线程模式下线程池会根据任务量动态调整线程数量。
- 程序结束后会输出总耗时（单位：毫秒）。
