
#include<stdio.h>

int binary_search(int num[],int l,int r,int key);
int bi_search_r(int num[],int length,int key);
int bi_search_l(int num[],int length,int key);
int main()
{
	int num[] = {1,2,3,4,5,6,7,7,8,9};
	//printf("%d\n",binary_search(num,0,9,6));
	printf("%d\n",bi_search_r(num,10,7));
	//printf("%d\n",bi_search_l(num,10,7));
	return 0;
}

int binary_search(int num[],int l,int r,int key)
{
	if (num[l] > key || num[r] < key)
		return 0;
	while (l <= r){
		int mid = (l+r)/2;
		printf("%d %d %d\n",l,mid,r);
		if (num[mid] == key)
			return mid+1;
		else if (num[mid] < key)
			l = mid + 1;
		else r = mid - 1;
	}
}

int bi_search_l(int num[],int length,int key)
{
	//a[low]  <  key  <=  a[high]
	// key < a[mid]
	// key >= a[mid]
	int l = -1,r = length;//*****
	while (l + 1 != r){
		int mid = (l+r)/2;
		printf("%d %d %d\n",l,mid,r);
		if (key > num[mid])
			l = mid;
		else 
			r = mid;
	}
	if (num[r] != key || r == length )
		return 0;
	return r+1;
}

int bi_search_r(int num[],int length,int key)
{
	int l = -1,r = length;//*****
	while (l + 1 != r){
		int mid = (l+r)/2;
		printf("%d %d %d\n",l,mid,r);
		if (key >= num[mid])
			l = mid;
		else 
			r = mid;
	}
	if (num[l] != key || l == -1)
		return 0;
	return l+1;
}
