#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
float permutation_invertion (int arr[], int length,int size){
  int i;
  int step = length/size;
  int value=0;
  for (i = 0; i < length-step; i+=step){
    if ( arr[i]>arr[i+step] )
      value++;
  }
  
  return value/(float) (size-1);
}
//from http://cforbeginners.com/insertionsort.html
void insertion_sort (int arr[], int length){
  int i, j, temp;
  
  for (i = 0; i < length; i++){
    j = i;
    
    while (j > 0 && arr[j] < arr[j-1]){
      temp = arr[j];
      arr[j] = arr[j-1];
      arr[j-1] = temp;
      j--;
    }
  }
}

//originally Java code from http://www.thelearningpoint.net/computer-science/arrays-and-sorting-shell-sort--with-c-program-source-code 
void ShellSort(int array[], int number_of_elements)
{
  int iter, jter, increment, temp,i,j;
  for(increment = number_of_elements/2;increment > 0; increment /= 2)
    {
      for(i = increment; i<number_of_elements; i++)
	{
	  temp = array[i];
	  for(j = i; j >= increment ;j-=increment)
	    {
	      if(temp < array[j-increment])
		{
		  array[j] = array[j-increment];
		}
	      else
		{
		  break;
		}
	    }
	  array[j] = temp;
	}
    }
}
// code from http://scanftree.com/programs/c/c-program-to-implement-heap-sort/
void heapsort(int[],int);
void heapify(int[],int);
void adjust(int[],int);
/*main() {
  int n,i,a[50];
  system("clear");
  printf("\nEnter the limit:");
  scanf("%d",&n);
  printf("\nEnter the elements:");
  for (i=0;i<n;i++)
    scanf("%d",&a[i]);
  heapsort(a,n);
  printf("\nThe Sorted Elements Are:\n");
  for (i=0;i<n;i++)
    printf("\t%d",a[i]);
  printf("\n");
}*/
void heapsort(int a[],int n) {
  int i,t;
  heapify(a,n);
  for (i=n-1;i>0;i--) {
    t = a[0];
    a[0] = a[i];
    a[i] = t;
    adjust(a,i);
  }
}
void heapify(int a[],int n) {
  int k,i,j,item;
  for (k=1;k<n;k++) {
    item = a[k];
    i = k;
    j = (i-1)/2;
    while((i>0)&&(item>a[j])) {
      a[i] = a[j];
      i = j;
      j = (i-1)/2;
    }
    a[i] = item;
  }
}
void adjust(int a[],int n) {
  int i,j,item;
  j = 0;
  item = a[j];
  i = 2*j+1;
  while(i<=n-1) {
    if(i+1 <= n-1)
      if(a[i] <a[i+1])
	i++;
    if(item<a[i]) {
      a[j] = a[i];
      j = i;
      i = 2*j+1;
    } else
      break;
  }
  a[j] = item;
}



//our selector
void oursort(int arr[],int length){
  if(length<2000)
    ShellSort(arr,length);
  else{
    float pi=permutation_invertion(arr,length,1000);
    if(pi<.1)
      insertion_sort(arr,length);
    else if (pi>.9)
      ShellSort(arr,length);
    else
      heapsort(arr,length);
  }
}
int* makeOrdered(int length){
  int* arr=(int*)malloc(sizeof(int)*length);
  int i;
  for(i=0;i<length;i++) 
    { 
      arr[i] = i;  
    } 
  return arr;
}
int* makeReversed(int length){
  int* arr=(int*)malloc(sizeof(int)*length);
  int i;
  for(i=0;i<length;i++) 
    { 
      arr[i] = length-i;  
    } 
  return arr;
}
int * makeRandom(int length){
  int* arr=(int*)malloc(sizeof(int)*length);
  int i;
  for(i=0;i<length;i++) 
    { 
      arr[i] = rand();  
    } 
  return arr;
}

void runtime(int arr[], int length){
  clock_t begin, end;
  double time_spent;

  begin = clock();
  oursort(arr,length);//give real values
  
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;  
  printf("Using Our meta sorting took %f seconds \n",time_spent);
  free(arr);

}
void runtimeISort(int arr[], int length){
  clock_t begin, end;
  double time_spent;

  begin = clock();
  insertion_sort(arr,length);
  
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;  
  printf("Using Insertion sort took %f seconds\n",time_spent);
  free(arr);

}
void runtimeShell(int arr[], int length){
  clock_t begin, end;
  double time_spent;

  begin = clock();
  ShellSort(arr,length);
  
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;  
  printf("Using Shell Sort took %f seconds\n",time_spent);
  free(arr);

}
void runtimeHeap(int arr[], int length){
  clock_t begin, end;
  double time_spent;

  begin = clock();
  heapsort(arr,length);
  
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;  
  printf("Using Heap Sort took %f second \n",time_spent);
  free(arr);

}
int main(int argc, char *argv[]){
  int sorted[10]={0,1,2,3,4,5,6,7,8,9}; 
  int reversed[10]={9,8,7,6,5,4,3,2,1,0}; 
  int random[10]={5,8,1,3,2,9,4,7,0,6}; 
  printf("Small sample of permutation invertion for sorted %f\n",permutation_invertion(sorted,10,10));
  printf("Small sample of permutation invertion for reversed %f\n",permutation_invertion(reversed,10,10));
  printf("Small sample of permutation invertion for random %f\n",permutation_invertion(random,10,10));
  int size=10000000;
  int * ORDER =makeOrdered(size);
  int * REV = makeReversed(size);
  int * RAND = makeRandom(size);
  int * order;
  int * rev;
  int * rand;
  order=(int *) memcpy(malloc(sizeof(int)*size),ORDER,sizeof(int)*size);
  printf("\n\nSorted: ");
  runtimeISort(order,size);
  if (size<10000){
    
    rev=(int *) memcpy(malloc(sizeof(int)*size),REV,sizeof(int)*size);
    rand=(int *) memcpy(malloc(sizeof(int)*size),RAND,sizeof(int)*size);
 
    runtimeISort(rev,size);
    runtimeISort(rand,size);}
  else{
    printf("Reversed: Using Insertion sort ARRAY WILL TAKE TOO LONG\n");
    printf("Rabdom: Using Insertion sort ARRAY WILL TAKE TOO LONG\n");
  }  
  order=(int *) memcpy(malloc(sizeof(int)*size),ORDER,sizeof(int)*size);
  rev=(int *) memcpy(malloc(sizeof(int)*size),REV,sizeof(int)*size);
  rand=(int *) memcpy(malloc(sizeof(int)*size),RAND,sizeof(int)*size);
 

  printf("\n\nSorted: ");
  runtimeShell((int *)order,size);
  printf("Revered: ");
  runtimeShell(rev,size);
  printf("Random: ");
  runtimeShell(rand,size);
  order=(int *) memcpy(malloc(sizeof(int)*size),ORDER,sizeof(int)*size);
  rev=(int *) memcpy(malloc(sizeof(int)*size),REV,sizeof(int)*size);
  rand=(int *) memcpy(malloc(sizeof(int)*size),RAND,sizeof(int)*size);
 
  printf("\n\nSorted: ");
  runtimeHeap(order,size);
  printf("Reversed: ");
  runtimeHeap(rev,size);
  printf("Random: ");
  runtimeHeap(rand,size);

  order=(int *) memcpy(malloc(sizeof(int)*size),ORDER,sizeof(int)*size);
  rev=(int *) memcpy(malloc(sizeof(int)*size),REV,sizeof(int)*size);
  rand=(int *) memcpy(malloc(sizeof(int)*size),RAND,sizeof(int)*size);

  printf("\n\nSorted: ");
  runtime(order,size);
  printf("Reversed: ");
  runtime(rev,size);
  printf("Random: ");
  runtime(rand,size);
  free(ORDER);
  free(REV);
  free(RAND);
  return 0;
}

