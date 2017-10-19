#快速排序

by yb

[TOC]
##简介
快排的基本思路是，在一个乱序数组中选择一个基准（pivot），把比基小的元素放到基的左边，大的放到右边。递归地重复这个操作，直到子数组的长度为1为止。


![Fig1](http://img.blog.csdn.net/20170115210511387?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvWUIwMzE2/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

如上图所示，每一次递归都将数组分为三个部分。

##实现
设`arr[]`为乱序数组，`pivot`为基，`beg end`标记待排序的区间`[beg,end]`
实现的其中一种方法是：


 - 取`arr[end]`为`pivot`
 - 从左到右遍历数组(此时数组为`arr[beg]...arr[end - 1]`)，依次把大于pivot的元素移动到最前面：`arr[0] arr[1]...arr[k]`
 - 把`pivot`移动到数组中间的恰当位置
 - 对两个子数组递归地调用QuickSort，直到子数组的长度为1

 ```C++
 void QuickSort(int* arr, int beg, int end)
 {
		 if (beg >= end) return;
		 int k = beg;   //(1)
		 int pivot = arr[end];
		 for (int i = beg; i < end; ++i) //(2)
				 if (arr[i] < pivot)
						 swap(arr[i], arr[k++]); //(3)
		swap(arr[end], arr[k]); //(4)
		QuickSort(arr, beg, k - 1);
		QuickSort(arr, k + 1, end);
}
 ```
 - 1）这里的k和实现思路的k一致
 - 2）再次提醒待排区间是`[beg, end - 1]`
 - 3）这里所做的事是：若`arr[i]`比`pivot`小，则将`arr[i]`与`arr[k]`交换。初始时`k `为` beg`，等价于把`arr[i]`放到第一位，随后`k++`把k向后挪动一位。区间`[beg, k - 1]`的值始终`≤pivot`。
 - 4）注意到`//(3)`语句是后置递增k，故此时`arr[k - 1]`小于`pivot`，而`arr[k]`应大于`pivot`。故将`arr[end]`与`arr[k]`交换，得到如上图结构的数组。

实现快排还有另外一种思路（见思考题）。

##复杂度分析
| 时空   | 期望          | 最佳          | 最坏       |
| ---- | ----------- | :---------- | -------- |
| 时间   | $O(n\lg n)$ | $O(n\lg n)$ | $O(n^2)$ |
| 空间   | $O(\lg n)$  | $O(\lg n)$  | $O(n)$   |

|稳定性|否|
|----|--|

$$$$

 - 可以证明，只要分割的两个区间任意一个不为空，快排最后的性能就为 $O(n\lg n)$
 - 若每次分割选择的`pivot`都为该区间的最值，则该次分割会出现空子区间。
 - 若每次分割都出现空子区间，快排退化为最坏情况。时间复杂度退化为 $O(n^2)$ 空间复杂度退化为 $O(n)$
 - 绝大多数情况，快排的性能都接近最好情况，而非最坏。

##优化
下面给出快排的常见优化。部分内容当做思考题。

 - 引入随机化。在`int pivot = arr[end]`之前，将数组内的随机一个元素与`arr[end]`交换。
 - 三向切分法。将数组分成三部分。小于`pivot`，等于`pivot`和大于`pivot`
  ![Fig2](http://img.blog.csdn.net/20170118104518482?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvWUIwMzE2/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
  其中`i`指向还未排序的元素。`lt`（less than）左侧的元素都小于`pivot`，`gt`（greater than）右侧的元素都大于`pivot`。程序运行时，`lt`和`i`不断往右递增，而`gt`不断向左递减。当`i`和`gt`重合时，整个数组处理完毕。
  修改后的代码如下
```C
void QuickSort(int* arr, int beg, int end)
{
	if (beg >= end) return;
	int pivot = arr[beg]; //(1)
	int lt = beg; //lt means less than
	int gt = end; //gt means greater than
	int pivot = arr[end];
	while (i <= gt) 
	{
		if (arr[i] < pivot) 
			swap(arr[lt++], arr[i++]);
		else if (arr[i] > pivot) 
			swap(arr[i], arr[gt--]);
		else i++;
	} 
	QuickSort(arr, beg, lt - 1);
	QuickSort(arr, gt + 1, end);
}
```

三向切分法对所有元素都相等的数组（或大部分元素的值都相等的数组）的运行时间是 $O(n)$，而优化前的程序对其的运行时间会退化至 $O(n^2)$


 - 自省排序。当子数组足够小时，将排序改为插入排序。具体做法是将第一句改为`if (end - beg <= M) {InsertSort(arr, beg, end); return;}`其中M是某个常数（C++中STL的Sort将M取为4）。插入排序对短数组、部分有序数组的性能较好。
 - 三点取中法。`pivot` 的选取不再是选择`arr[end]`，而是从`arr[beg] arr[mid] arr[end]`三者的中间值中取，其中`mid = (beg + end) / 2`。这个取法可以保证`pivot`一定不是数组中的最值，从而保证一定不恶化到 $O(n^2)$
 - 用循环优化递归。循环没有递归时函数调用的开销。改进快排，在函数的最后，用循环处理子区间`[beg, k - 1]`，用递归处理子区间`[k + 1, end]`，从而节省一半的递归调用时间。

 ##思考题
 （建议完成这个部分）

 - 修改代码，用“引入随机化”改进快排，并用`附C`的代码产生倒序数组检验其运行时间。(若不进行这个优化，原快排代码会退化到最坏情况）
 - 实现自省排序。写一个循环，将`M`从0遍历至20。输出不同的M对应的排序运行时间，哪个M值最适宜？（使用`<time.h>`中的`clock()`函数统计时间）
 - 实现三点取中法优化。
 - 思考循环代替递归的优化，并试着实现。可以只用循环实现快排吗？
 - 试着说明为何三向切分法的代码能正确工作。并用`附B`的代码产生大多数元素都相同的数组，检验性能。
 - 尽可能多地将上述      优化结合起来，用`附A`的程序产生随机数组检验性能。

##附录
以下代码的输出格式：第一行是一个大整数n，下一行紧接n个整数。

###附A
```
//新建文件“input”并产生乱序的随机数组。

#include <stdio.h>
#include <stdlib.h>
int main()
{
	freopen("test", "w", stdout);
	srand(0);
	const int n = 1E7;
	printf("%d\n", n);
	for (int i = 0; i < n ;++i)
		printf("%d ", rand() % n);
	printf("\n");
	return 0;
}
```

###附B
```
//新建文件“input”并产生大量元素相同的随机数组。
#include <stdio.h>
#include <stdlib.h>
int main()
{
	freopen("test", "w", stdout);
	srand(0);
	const int n = 1E7;
	printf("%d\n", n);
	for (int i = 0; i < n ;++i)
		printf("%d ", rand() % 10);
	printf("\n");
	return 0;
}
```

###附C
```
//新建文件“input”并产生倒序数组。
#include <stdio.h>
#include <stdlib.h>
int main()
{
	freopen("test", "w", stdout);
	const int n = 1E7;
	printf("%d\n", n);
	for (int i = n; i > 0; --i)
		printf("%d ", i);
	printf("\n");
	return 0;
}
```
