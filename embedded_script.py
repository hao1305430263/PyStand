# 这是将会被嵌入到PyStand.exe中的Python脚本
import os
import sys


def main():
    msg = "这是从编译时嵌入的Python脚本运行的!"
    print(msg)
    print()

    print("Python路径:")
    for path in sys.path:
        print(">", path)

    os.MessageBox(msg, "嵌入式脚本")


if __name__ == "__main__":
    main()
