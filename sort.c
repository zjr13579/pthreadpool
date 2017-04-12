#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//冒泡排序
void bubble_sort(int * array,int len)
{
	int i=0,j=0;
	for(i=0;i<len;i++)
	{
		for(j=0;j<len-i-1;j++)
		{
			if(array[j]>array[j+1])
			{
				int temp=array[j+1];
				array[j+1]=array[j];
				array[j]=temp;
			}
		}
	}
}
//交换排序
void exchange_sort(int* array,int len)
{
	int i=0,j=0;
	for(i=0;i<len;i++)
	{
		for(j=i+1;j<len;j++)//j从0开始是从大到小，从i+1开始是从小到大
		{
			if(array[i]>array[j])
			{
				int temp=array[i];
				array[i]=array[j];
				array[j]=temp;
			}
		}
	}
}
//选择排序
void select_sort(int * array,int len)
{
	int i=0,j=0;
	for(i=0;i<len;i++)
	{
		int temp=array[i];
		int min=temp;
		int pos=-1;/*保存j的值,初始化不可以直接=0。因为等于0的话，会影响下面的赋值,当while循环
		            进不去的时候，会有影响*/
		j=i+1;
		while(j<len)
		{
			if(array[j]<array[i])
			{
				min=array[j];
				pos=j;
			}
			j++;
		}
		array[pos]=temp;
		array[i]=min;
	}
}
//插入排序
void insert_sort(int * array,int len)
{
	int i=0,j=0;
	for(i=1;i<len;i++)
	{
		int temp=array[i];
		j=i-1;
		while(j>=0)
		{
			if(temp>array[j])
			{
				break;
			}
			if(temp<array[j])
			{
				array[j+1]=array[j];
			}
			j--;
		}
		array[j+1]=temp;
	}
}
//计数排序
//排没有重复的数字
void count_sort1(int* array,int len)
{
	int temp[100];
	int index=0;
	memset(temp,-1,sizeof(temp));
	for(index=0;index<len;index++)
	{
		temp[array[index]]=array[index];
	}
	for(index=0;index<100;index++)
	{
		if(temp[index]!=-1)
		{
			printf("%d\n",temp[index]);
		}
	}
}
//计数排序，排有重复数字的数
//获得最大值
int get_max(int* array,int len)
{
	int i=0;
	int max=0;
	for(i=0;i<len;i++)
	{
		if(max<array[i])
		{
			max=array[i];
		}
	}
	//max++;//分配多一个空间,
	return max;
}
//动态分配数组空间
int * dynamic_allot_array(int* array,int max)
{
	int * ptr=(int*)malloc(max*sizeof(int));
	memset(ptr,-1,sizeof(int)*max);
	return ptr;
}
//释放空间
void free_space(int* ptr)
{
	if(ptr!=NULL)
	{
		free(ptr);
		ptr=NULL;
	}	
}
//计数排序
void count_sort(int* array,int len)
{
	int i=0;
	int max=get_max(array,len);
	int* ptr=dynamic_allot_array(array,max);
	for(i=0;i<len;i++)
	{
		ptr[array[i]]++;
	}
	i=0;
	int j=0;
	for(j=0;j<max;j++)
	{
		while(ptr[j]>=0)
		{
			array[i]=j;
			ptr[j]--;
			i++;
		}
	}
	free_space(ptr);
}

//位排序
int get_max_from_array(int* array,int len)
{
	int max=array[0];
	int i=0;
	for(i=0;i<len;i++)
	{
		if(max<array[i])
		{
			max=array[i];
		}
	}
	return max;
}
//将目标值放入位数组
void set_value_bit_array(int* ptr,int* array,int len)
{
	int index,i;
	int block_id;	
	for(i=0;i<len;i++)
	{
		int value=0x1;		
		block_id=array[i]/32;
		index=array[i]%32;
		value=value << index;
		ptr[block_id]=ptr[block_id] | value;
		//printf("%d\n",ptr[block_id]);
	}
}
//从数组中获取元素值
void get_element(int* ptr,int* array,int max)
{
	int i=0;
	for(i=0;i<=max;i++)
	{
		int index=i%32;
		int block_id=i/32;
		int value=0x1;
		value=value<<index;
		if(ptr[block_id]&value)
		{
			printf("%d\n",i);
		}
	}
}
//位排序
void bit_sort(int* array,int len)
{
	int max=get_max_from_array(array,len);
	int size=max%32?max/32+1:max/32;
	int *ptr=(int*)malloc(size*sizeof(int));
	set_value_bit_array(ptr,array,len);
	get_element(ptr,array,max);
}
//基数排序：就是根据个十百千位进行排序
//构造桶
int ** create_pail(int len)
{
	int **ptr=(int**)malloc(len*sizeof(int*));
	int i=0;
	for(i=0;i<len;i++)
	{
		*(ptr+i)=(int*)malloc(len*sizeof(int));
		memset(*(ptr+i),-1,sizeof(int)*len);
	}
	return ptr;
}
//获得最大值的位数
int get_max_bit(int* array,int len)
{
	int i=0;
	int max=array[0];
	for(i=0;i<len;i++)
	{
		if(max<array[i])
		{
			max=array[i];
		}
	}
	int max_bit=0;
	while(max!=0)
	{
		max_bit++;
		max=max/10;		
	}
	return max_bit;
}
//释放桶
void free_pail(int** ptr,int len)
{
	int i=0;
	if(ptr!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(ptr[i]!=NULL)
			{
				free(ptr[i]);
				ptr[i]=NULL;
			}
		}
		free(ptr);
		ptr=NULL;
	}
}
//基数排序
void cardinal_sort(int* array,int len)
{
	int **ptr=create_pail(len);
	int max_bit=get_max_bit(array,len);
	int base=1;
	int k=0;//桶的列数
	int index=0;
	int i=1,j;
	while(i<=max_bit)
	{
		//将元素放入桶
		for(j=0;j<len;j++)
		{			
			k=0;
			while(ptr[array[j]/base%10][k]!=-1)
			{
				k++;
			}
			ptr[array[j]/base%10][k]=array[j];
		}
		index=0;
		//取出元素值
		for(j=0;j<len;j++)
		{
			k=0;
			while(ptr[j][k]!=-1)
			{
				array[index++]=ptr[j][k];
				ptr[j][k]=-1;
				k++;
			}
		}
		i++;
        base=base*10;
	}	
	free_pail(ptr,len);
}
//归并排序
void merger_sort(int* list1,int list1_len,int* list2,int list2_len)
{
	int i,j,k;
	int temp[10];
	i=j=k=0;
	while(i<list1_len && j<list2_len)
	{
		if(list1[i]<list2[j])
		{
			temp[k++]=list1[i++];
		}
		else
		{
			temp[k++]=list2[j++];
		}
	}
	while(i<list1_len)
	{
		temp[k++]=list1[i++];
	}
	while(j<list2_len)
	{
		temp[k++]=list2[j++];
	}
	for(i=0;i<list1_len+list2_len;i++)//将合并数组值赋给原始数组
	{
		list1[i]=temp[i];
	}
}
//拆分函数
void merger(int* array,int len)
{
	if(len>1)
	{
		int *list1=array;
		int list1_len=len/2;
		int *list2=array+list1_len;
		int list2_len=len-list1_len;
		merger(list1,list1_len);
		merger(list2,list2_len);
		merger_sort(list1,list1_len,list2,list2_len);
	}
}
//希尔排序 ?
void shell_sort(int* array,int len)
{
	int i,j,k;
	for(i=len/2;i>0;i=i/2)
	{
		for(j=i;j<len;j++)
		{
			int temp=array[j];
			for(k=j-i;k>=0&&temp<array[k];k=k-i)
			{
				array[k+i]=array[k];
			}
			array[k+i]=temp;
		}
	}
}
//快排
int quick_sorting(int* array,int left,int right)
{
	int temp=array[left];
	while(left<right)
	{
		while(temp<array[right] && left<right)
		{
			right--;
		}
		if(left<right)
		{
			array[left]=array[right];
		}
		while( temp>array[left] && left<right)
		{
			left++;		
	    }
	    if(left<right)
	    {
	    	array[right]=array[left];
	    }
	    array[left]=temp;
	    return left;
	}
}
//递归实现快排
void recursion_quick_sort(int* array,int left,int right)
{
	if(left<right)
	{
		int mid=quick_sorting(array,left,right);
		recursion_quick_sort(array,left,mid-1);
		recursion_quick_sort(array,mid+1,right);
	}	
} 
//非递归实现快排
void not_recursion_quick_sort(int *array,int left,int right)
{
	int left_data=left;
	int right_data=right;
	int temp;
	while(left_data<right)
	{
		while(left<right)
		{
			temp=array[left];
			right=right_data;
			while(temp<array[right] && left<right)
			{
				right--;
			}
			if(left<right)
			{
				array[left]=array[right];
			}
			left=left_data;
			while(left<right && temp>array[left])
			{
				left++;
			}
			if(left<right)
			{
				array[right]=array[left];
			}
			array[right]=temp;
		}
		left=left_data++;
		right=right_data;
	}
}
//堆排序
void heap_sort(int *array)
{
	
}
//输出数组元素
void print_array(int *array,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		printf("%d\n",array[i]);
	}
}
int main(int argc, char const *argv[])
{
	int array[]={10,2,37,45,34,56,89,31,67,900};	
	//bubble_sort(array,10);
	//exchange_sort(array,10);
	//select_sort(array,10);
	//insert_sort(array,10);	
	//count_sort(array,10);
	//bit_sort(array,10);
	//cardinal_sort(array,10);
	//merger(array,10);
	//shell_sort(array,10);
	not_recursion_quick_sort(array,0,9);
	print_array(array,10);
	return 0;
}
