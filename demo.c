#include <stdio.h>
#include <math.h>
#include <time.h>

float permutation_invertion (int arr[], int length){
  int i;
  int step = length/1000;
  int value=0;
  for (i = 0; i < length-step; i+=step){
    if ( arr[i]>arr[i+step] )
      value++;
  }
  
  return value/(float) 1000;
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
    float pi=permutation_invertion(arr,length);
    if(pi<.1)
      insertion_sort(arr,length);
    else if (pi>.9)
      ShellSort(arr,length);
    else
      heapsort(arr,length);
  }
}

int main(int argc, char *argv[]){
  int sorted[10]={0,1,2,3,4,5,6,7,8,9}; 
  int reversed[10]={9,8,7,6,5,4,3,2,1,0}; 
  int random[10]={5,8,1,3,2,9,4,7,0,6}; 
  int random2[10]={5,8,1,3,2,9,4,7,0,6}; 
  printf("%f\n",permutation_invertion(sorted,10));
  printf("%f\n",permutation_invertion(reversed,10));
  printf("%f\n",permutation_invertion(random,10));
  clock_t begin, end;
  double time_spent;

  begin = clock();
  oursort(random2,10);//give real values
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;  
  printf("%f\n",time_spent);
  return 0;
}

