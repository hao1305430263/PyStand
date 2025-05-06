import os
import sys


def main():
    msg = "hollo world!"
    print(msg)
    print()

    print("Python路径:")
    for path in sys.path:
        print(">", path)

    os.MessageBox(msg, "hi")


if __name__ == "__main__":
    main()
