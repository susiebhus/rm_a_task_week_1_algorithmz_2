# 区域膨胀算法

这是算法组第一周“区域膨胀算法”的独立 C++17 练习项目。它不依赖 OpenCV：输入是 `0/1` 二值矩阵，图像外部统一按背景 `0` 处理。

项目将 `BinaryImage`（数据和校验）、`StructuringElement`（可替换核）和 `Morphology`（操作）分开。默认题目要求可用 `StructuringElement::square(5)` 完成 5×5 方形膨胀。

## 构建与验证

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/morphology_demo.exe
```

测试覆盖单像素、小正方形、边缘像素、相邻区域、无前景图像、菱形核和腐蚀。

## dilation1、dilation2 与腐蚀

- `square(5)`：5×5 全 1 方形核。每个前景像素向八个方向最多扩展 2 格，得到题目所称的方形外扩（dilation1）。
- `diamond(2)`：5×5 菱形核。四个角不参与运算，因此得到削去方角的菱形外扩；若题图 dilation2 为该形状，直接替换核即可，无需改膨胀循环。
- `cross(5)`：仅横、纵方向参与，适合需要十字形方向扩张的 dilation2 变体。
- `erode`：只有核的所有有效位置都覆盖前景时才保留当前像素，因此会收缩前景、去除细小孤立区域，并使边界向内退缩。

普通卷积与形态学膨胀都使用滑动局部核，但普通卷积是乘加求和；二值膨胀相当于邻域逻辑 OR / 最大值，腐蚀相当于逻辑 AND / 最小值。它们是不同代数规则下的局部邻域算子。
