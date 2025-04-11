# 🌟 Tucil 2 Strategi Algoritma IF2211 : QuadTree Image Compression
#### Muhammad Jibril Ibrahim - 13523085
#### Muhammad Luqman Hakim - 13523044

---

## 🚀 Tech Stack
- **Language:** C 
- **Library :** stb_image.h(\*), stb_image_write.h(\*), gif.h(\*\*)

---

## 📌 Overview
This project is an assignment for the IF2211 Strategi Algoritma course. The main purpose of this assignment is to implement a **divide-and-conquer algorithms** againts a problem we may face in daily life. One such problem is compressing an image. Through this project, we can deepens our understanding of divide-and-conquer algorithms and experience the strengths and limitations of divide-and-conquer algorithms.

---

## 📖 About
<div align="center">
    <img src="https://github.com/carasiae/quadtree/blob/main/assets/flower.gif?raw=true" alt="flower" width="400"/>
    
</div>
<p align="center"><i>QuadTree Compression Process</i></p>

This project implements a quadtree compression algorithm for efficiently reducing image size by recursively dividing an image into quadrants. Uniform regions are stored as single nodes (and colored with the same color), while more complex areas are split further. It's especially effective for compressing images with large areas of similar color.

### Features
- Customizable pixel variance function
- Adjustable variance threshold
- Minimum block size configuration
- Outputs compressed image
- Reports:
    - Original and compressed image sizes
    - Compression ratio
    - Tree depth and number of nodes
    - Execution time
---

## 🛠️ Installation & Setup
### **1️⃣ Prerequisites**
Install dependencies if not yet installed
#### Linux
```
make dep
```
#### Windows
```
./build.bat dep
```
### **2️⃣ Build**
#### Linux
To build the project, run
```
make build
```
#### Windows
```
chcp 65001           // set pwsh or cmd output to utf-8
```
```
./build.bat build
```
### **3️⃣ Usage**
To run the program, run
#### Linux
```
make run
```
#### Windows
```
./build.bat run
```

---

(\*) licensed under MIT license:
```
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

(\*\*) licensed under Unlicense:
```
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
```
<br/>
<br/>
