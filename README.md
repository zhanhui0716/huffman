# Huffman Coding in C++

[简体中文](README.zh-CN.md)

A C++ console program that builds a Huffman tree from fixed English letter frequencies, prints the codes for `A` through `Z`, and encodes a line of uppercase English letters.

## Build and run

Open a terminal in this repository. Use GCC's `g++` (MinGW on Windows) with C++11 or later. The source uses `<bits/stdc++.h>`.

**Windows (PowerShell)**

```powershell
g++ -std=c++11 "哈夫曼树.cpp" -o huffman.exe
.\huffman.exe
```

**Linux**

```bash
g++ -std=c++11 "哈夫曼树.cpp" -o huffman
./huffman
```

## Example

The program prints the root weight (`10002`) and all 26 letter codes before prompting for input. The console messages are in Chinese.

```text
请输入一串大写英文字母：ET
哈夫曼编码：100000
```

The program concatenates the code for `E` (`100`) and the code for `T` (`000`). Enter at least one letter from `A` to `Z`. Empty input, lowercase letters, spaces, and punctuation are rejected.

## How it works

1. Store the 26 letters as leaves in an array. Repeatedly merge the two lowest-weight nodes without a parent. The resulting tree has 51 nodes.
2. Generate each letter's code by walking from its leaf to the root, recording `0` for a left branch and `1` for a right branch. Reverse the recorded bits to get the root-to-leaf code.
3. For each input letter, use `ch - 'A'` to look up its code and append it to the result.

The source also includes `decode()`. It walks the tree from the root, prints a letter when it reaches a leaf, and returns `false` for characters other than `0` and `1` or an incomplete final code. The current `main()` exposes encoding at the prompt.
