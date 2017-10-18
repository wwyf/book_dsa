
#include <stdio>

void bubble_sort(int num[],int length);
void select_sort(int num[],int length);
void insert_sort(int num[],int length);
void merge_sort(int num[],int l,int r);
void merge_sort2(int num[],int l,int m,int r);
void quick_sort(int num[],int l,int r);
void bucket_sort(int num[],int length);
void bitmap_sort(int num[],int length);

void swap(int* a,int* b);

void bubble_sort(int num[],int length)
{
	int i,j;
	for (i = 0;i < length - 1;i++){
		for (j = length - 1;j > i;j--)
			if (num[j-1] > num[j]){
				swap(&num[j-1],&num[j]);
			}
	}
}
void select_sort(int num[],int length)
// 选择排序，每次找到最小的元素，放到数组最前面，然后对之后的元素执行相同操作
{
	int i,j,min = 0;
	for (i = 0;i < length - 1;i++){// 每循环一次，就把[i,length-1]中最小的值放到num[i]
		min = i; // 初始化最小值下标为开头
		// 找到[i,length-1]中最小的值的下标
		for (j = i; j < length;j++)
			if (num[min] > num[j])
				min = j;

		swap(&num[min],&num[i]); // 找到最小的值的下标之后，拿最小的值与num[i]交换，从而确定num[i]，下一次循环不再改变num[i];
	}		
}

void insert_sort(int num[],int length)// 最好情况极好，n-1次比较即可，有时候还有点用, 但是赋值次数过多，如果赋值操作代价过高，慎用
// 插入排序
{
	int i,j;
	for (first_unsorted = 1 ; first_unsorted < length; first_unsorted++){
		if (num[first_unsorted-1] > num[first_unsorted]){
			j = first_unsorted;
			int temp = num[first_unsorted]; // temp ： 需要插入的元素的值
			while ( j > 0 && temp < num[j-1]){// j 的含义是那一个需要插入的元素应该要放在的position
				num[j] = num[j-1];
				j--;
			}
			num[j] = temp;
		}
	}
}

void merge_sort2(int num[],int l,int m,int r)
{
	// pre：两个数组，num[l ~ m] 和 num[m+1 ~ r]已经分别有序
	// 功能：将两个已经有序的数组合并成一个
	int temp[r-l+1];
	int k = 0; // k 是指针下标，指向合并后数组未经填充的第一位
	int i = l; // i, j 是两个指针下标，指向两段数组的开头
	int j = m+1;
	while(i <= m && j <= r){ // 两个数组都还没有合并完，取开头较小的那一个填进temp数组，然后两个指针+1
		if (num[i] < num[j]){
			temp[k++] = num[i++];
		}
		else{
			temp[k++] = num[j++];
		}
	}
	// 其中一个数组已经全部填进temp了，但是另一个数组还没有填完，就把剩下的全部填进去
	while (i <= m){
		temp[k++] = num[i++];
	}
	while (j <= r){
		temp[k++] = num[j++];
	}
	for (i = l,k = 0;i <= r;i++,k++){
		num[i] = temp[k];
	}
}
void merge_sort(int num[],int l,int r)//入口函数
{
	if (l == r) 
		return ;
	int mid = (l + r) / 2;
	merge_sort(num,l,mid);
	merge_sort(num,mid+1,r);
	merge_sort2(num,l,mid,r);// 合并的是l ~ mid , mid+1 ~ r 这两段
}

// 取num[r]为快排中间的参考值pivot
// 遍历数组，将比pivot小的值放在数组最前面
// 完成后，递归执行
// inspired by yb
void quick_sort(int num[], int l, int r){
	if (l >= end) return ;
	int k = beg;
	int pivot = num[r];
	for (int i = l; i < r; i++){
		if (num[i] < pivot){
			swap(num[i], num[k++]);// k是在该数组前面已经分好类的数中，比pivot大的第一个数。作为数组中比pivot小，大的数的分界线
		}
	}
	swap(num[k], num[r]);// 交换pivot与num[k]，确保pivot在数组中间 
	quick_sort(num, l, k-1);
	quick_sort(num, k+1, r);
}

void bucket_sort(int num[],int length)
{
	int temp[20] = {0}; // 初始化桶
	int i = 0,k = 0,j = 0; // j 是一个指针下标，用于给num赋值的时候使用，每对num赋一个值，都对j+1；
	for(i = 0;i < length;i++){// 将元素放入桶中，在桶中存放的是元素个数
		temp[num[i]]++;
	}
	for (i = 0;i < 20;i++){ // 遍历桶
		for(k = 0;k < temp[i];k++){ // 遍历桶内元素
			num[j] = i;
			j++;
		}
	}
}
void bitmap_sort(int num[],int length)
{
	unsigned int bitmap[10] = {0};
	int j,k = 0;
	for (j = 0;j < length;j++){
		bitmap[num[j]/32] +=  1 << num[j]%32;
	}
	for (j = 0;j < 30;j++){
		if(bitmap[j/32] & 1<<j%32){
			num[k] = j;
			k++;
		}			
	}
}