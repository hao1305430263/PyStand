# ScriptConverter - Python 脚本转换工具

这个工具用于将 Python 脚本转换为 C++头文件，以便将 Python 代码嵌入到 C++程序中。

## 编译方法

```bash
# 创建构建目录
mkdir build
cd build

# 配置
cmake ..

# 编译
cmake --build . --config Release

# 安装(可选)
cmake --install . --prefix=安装路径
```

## 使用方法

```bash
ScriptConverter 输入文件.py 输出文件.h
```

例如：

```bash
ScriptConverter ../../embedded_script.py ../../generated/embedded_script.h
```

## 集成到其他项目

1. 首先编译并安装此工具
2. 在目标项目的 CMakeLists.txt 中，使用此工具来生成头文件
3. 在代码中包含生成的头文件
