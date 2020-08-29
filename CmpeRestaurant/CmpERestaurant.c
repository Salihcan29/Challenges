#include <stdio.h>
#include <stdlib.h>

struct table{
	int number;
	int empty;
};typedef struct table Table;

int n,q; // number of tables, number of arrives

void quicksort(Table * T,int first,int last){
   int i, j, pivot;
   Table temp;

   if(first<last){
    	pivot=first;
    	i=first;
    	j=last;
	
	    while(i<j){
	        while((T[i].empty<=T[pivot].empty||(T[i].number>T[pivot].number&&T[i].empty == T[pivot].empty))&&i<last)
	            i++;
	        while(T[j].empty>T[pivot].empty||(T[j].number<T[pivot].number&&T[j].empty == T[pivot].empty))
	            j--;
	        if(i<j){
	        	temp = T[i];
	        	T[i] = T[j];
	        	T[j] = temp;
	        }
	    }

	    temp = T[pivot];
	    T[pivot] = T[j];
	    T[j] = temp;
	    
	    quicksort(T,first,j-1);
	    quicksort(T,j+1,last);
   }
}

void place(Table * T,int s_i){
	if(s_i > T[n-1].empty){
		printf("%d\n",-1);
	}else{
		printf("%d\n",T[n-1].number);
		T[n-1].empty -= s_i;
	}
}
void show_tables(Table * T){
	int i;
	for(i = 0;i<n;i++){
		printf("%d ",T[i].empty);
	}
	printf("\n");
}

void resort(Table * T){
	int index = n-1;
	Table temp = T[index];
		
	for(;index>0;index--){
		if(temp.empty < T[index-1].empty){
			T[index] = T[index-1];
		}else if(temp.empty == T[index-1].empty && temp.number > T[index-1].number){
			T[index] = T[index-1];
		}else{
			break;
		}
		T[index-1] = temp;
	}
}

int main(){
	FILE * fp;
	fp = fopen("CmpERestaurantInput3.txt","r");
	
	fscanf(fp,"%d",&n);
	Table T[n];
	
	int i;
	
	int c_i;
	for(i = 0;i<n;i++){
		fscanf(fp,"%d",&c_i);
		T[i].empty = c_i;
		T[i].number = i;
	}
	int s_i;

	quicksort(T,0,n-1);
	
	fscanf(fp,"%d",&q);
	for(i = 0;i<q;i++){
		fscanf(fp,"%d",&s_i);
		place(T,s_i);
		resort(T);	
	}
	show_tables(T);
}
