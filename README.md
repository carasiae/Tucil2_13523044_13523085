# 🌟 Tucil 2 Strategi Algoritma IF2211 : QuadTree Image Compression
#### Muhammad Jibril Ibrahim - 13523085
#### Muhammad Luqman Hakim - 13523044

---

## 🚀 Tech Stack
- **Language:** C 
- **Library :** stb_image.h(\*), stb_image_write.h(\*)

---

## 📌 Overview

This project is an assignment for the IF2211 Strategi Algoritma course. The main purpose of this assignment is to implement a **divide-and-conquer algorithms** againts a problem we may face in daily life. One such problem is compressing an image. Through this project, we can deepens our understanding of divide-and-conquer algorithms and experience the strengths and limitations of divide-and-conquer algorithms.

---

## 📖 About

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
Download stb_image.h & stb_image_write.h library if not yet installed
```
make dep
```
### **1️⃣ Build**
To build the project, run
```
make build
```
## **Usage**
To run the program, run
```
make run
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
<br/>
<br/>
