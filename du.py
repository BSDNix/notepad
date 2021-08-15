import os

path = input()
size = 0

for root, directories, files in os.walk(path, topdown=False):
    for name in files:
        print(os.path.join(root, name), end=" ")
        size += os.path.getsize(path)
        print(str(size))
    for name in directories:
        print(os.path.join(root, name), end=" ")
        print(str(size))
