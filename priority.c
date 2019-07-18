#include<stdio.h> 
int* decide_priority(char options[10][3], int count_option) 
{ 
    int *a;
    a = (int*)malloc(14 * sizeof(int));
      
    int i;
	for(i = 0; i < count_option; i++)
		a[i] = -1;

	for(i = 0; i < count_option; i++)
	{
		if(options[i][1] == 'r')
			a[i] = 0;
		if(options[i][1] == 'i')
			a[i] = 1;
		if(options[i][1] == 'w')
			a[i] = 2;
		if(options[i][1] == 'm')
			a[i] = 3;
		if(options[i][1] == 'c')
			a[i] = 4;
		if(options[i][1] == 'b')
			a[i] = 5;
		if(options[i][1] == 'v')
			a[i] = 6;
		if(options[i][1] == 'h')
			a[i] = 7;
		if(options[i][1] == 'H')
			a[i] = 8;
		if(options[i][1] == 'm')
			a[i] = 9;
		if(options[i][1] == 'q')
			a[i] = 10;
		if(options[i][1] == 'f')
			a[i] = 11;
		if(options[i][1] == 'e')
		{
			a[i] = 12;
		}
		if(a[i] == -1)
		{
			printf("\n%d Bad arguements", i);
			exit(0);
		}
	}
	int j;
	  for(i = 0; i < count_option; i++){
	  	for(j = 0; j < count_option - 1; j++)
	  	{
	  		if(a[j] > a[j + 1]){
	  			int t = a[j];
	  			a[j] = a[j + 1];
	  			a[j + 1] =t;
			  }
		  }
	  }
	  return a;
}
