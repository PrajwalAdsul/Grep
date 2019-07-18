#include <ctype.h>
void LPSArray(char* pat, int M, int* lps); 
int c;
int resize(int *index, int size)
{
	size = size * 2;
	index = (int*)realloc(index, sizeof(int) * size);
	return size;
}
char *strlwrr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}
int* KMPS(char* pat, char* txt, int count, int size) 
{ 
	
	char str[strlen(txt)];
	
	strcpy(str, txt);
	
	if(search(a, 1))
	{
		strcpy(str, strlwrr(str));
		strcpy(pat, strlwrr(pat));
	}
	int *index;
	index = (int*)malloc(sizeof(int) * size);
    
    int M = strlen(pat), N = strlen(txt); 
   
    int lps[M]; 
  
    LPSArray(pat, M, lps); 
  
    int i = 0, j = 0; 
    while (i < N) 
	{ 
        if (pat[j] == str[i])
	    { 
            j++; 
		    i++; 
        } 
        if (j == M) { 
            if(count == size){
            	size = resize(index, size);
			}
			
			if( (str[i - j - 1] < 'A' || (str[i - j - 1] > 'Z' && str[i - j - 1] < 'a') || str[i - j - 1] > 'z') && search(a, 2) )	
			{
				if((str[i - j + M] < 'A' || (str[i - j + M] > 'Z' && str[i - j + M] < 'a') || str[i - j + M] > 'z') && search(a, 2))
				{	
					if(search(a, 10))
						exit(0);	
					index[count++] = i - j;
					if(search(a, 12) || search(a, 11))
					{					
						makeitline(str, i - j);
					}
				}
			}
			else if(!search(a, 2))
			{

					if(search(a, 10))
						exit(0);
				index[count++] = i - j;
				if(search(a, 12) || search(a, 11))
					{
						makeitline(str, i - j);
					}
			}
            j = lps[j - 1]; 
        } 
  		else if (i < N && pat[j] != str[i]) { 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
    index[0] = count;
    return index;
} 
void LPSArray(char* pat, int M, int* lps) 
{ 
    int len = 0, i;   
    lps[0] = 0; 
	 i = 1; 
    while (i < M) 
	{ 
        if (pat[i] == pat[len]) 
		{ 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else 
		{ 
            if (len != 0) { 
                len = lps[len - 1]; 
  		    } 
            else
			{ 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
}
int searchv(int index[], int v)
{
	int i;
	for(i = 1; i < index[0]; i++){
		if(index[i] == v)
			return 1;
	}
	return 0;
} 
void printline(char* str, int i, int index[], char path[]){
	
	int j = i;

	for(j = i - 1; j >= 0; j--){
		if(str[j] == '\n')
			break;
		if(searchv(index, j))
		{
			c--;
			return;
		}
	}
	int start = j + 1;
	for(j = i + 1; j < strlen(str) && str[j] != '\0'; j++){
		if(str[j] == '\n'){
			break;
		}
	}
	str[j] = '\n';
	int end = j - 1;
	if(!search(a, 4)){
		if(search(a, 8) || (search(a, 0) && !search(a, 7)))               
			printf("%s%s%s: ", KMAG, path, KNRM);

		if(!search(a, 11) && !search(a, 12))
		{
		
			for(j = start; j <= end; j++){

				printf("%c", str[j]);
			}
			printf("\n");
		}	
	}
}
void printvline(char* str, int index[], int j, int ii, int n, char path[]){
		int i = j - 1;
		if(j == 0)
			return;	
		
		i = j - 1;
		while(i > 0 && str[i] != '\n'){
			if(searchv(index, i))
				return;			 
			i--;
		}
		int end = i;
		if(i == 0)
			return;
		i--;
		while(i > 0 ){
			if(searchv(index, i))
				break;
			i--;
		}
		if(i != 0)
			while(str[i] != '\n' && str[i] != '\0'){
				i++;
			}
		if(i == 0 && searchv(index, i))
		{
			while(str[i] != '\n'){
				i++;
			}
		}
		int start = i;
		if(!search(a, 4))
		{
			if(start != 0)
			{
				start++;
			}

			
			if((search(a, 8) || (search(a, 0) && !search(a, 7)) ) && start < end    ) 
				printf("\n%s%s%s ", KMAG, path, KNRM); 


			if(search(a, 5) && ii == 1){
				if(!i)
					printf("\n%s0:%s", KGRN, KWHT);
				else
					printf("\n%s%d:%s", KGRN, start + 1, KWHT);
			}


			for(i = start; i < end; i++){
				
				if(str[i - 1] == '\n' && (search(a, 8) || (search(a, 0) && !search(a, 7))) && i != start)   
					printf("%s%s%s ", KMAG, path, KNRM);				
				if(str[i - 1] == '\n' && search(a, 5) )
				{
					printf("\n%s%d:%s", KGRN, i, KWHT); 
				}
					printf("%c", str[i]);
			}
			
		}
		else
		{
			for(i = start + 1; i < end; i++)
			{
				if(str[i] == '\n')
					vcount++;
			}
		}
		
		if(ii == n - 1 ){
		
			i = j;		
			while(1)
			{
				if(str[i] == '\n' || str[i] == '\0')
					break;
				i++;
			}
			if(str[i + 1] == '\0' || str[i] == '\0')
				return;
			else
			{
				i++;
					printf("\n");
   				if(search(a, 8) || (search(a, 0) && !search(a, 7)))  
   					printf("%s%s%s ", KMAG, path, KNRM);	
				while(1){
					if(str[i] == '\0')
						break;
					if(str[i] == '\n')
						vcount++;
					
					if(str[i] == '\n' && (search(a, 8) || (search(a, 0) && !search(a, 7)) )&& str[i + 1] != '\0')
					{
						printf("\n%s%s%s ", KMAG, path, KNRM);						
					}
					else if(str[i] == '\n') 
					{
						printf("\n");
					}
					if(str[i] == '\n' && str[i + 1] == '\n')
						break;
					if(!search(a, 4))
					{	
						if(str[i - 1] == '\n' && search(a, 5))
						{
							printf("\n%s%d%s:", KGRN, i, KWHT);
						}
						if(str[i] != '\n')
							printf("%c", str[i]);
					}
					
					i++;
				}
				printf("\n");
				vcount++;
				vcount++;
			}
			return;
		}
			
}
int byteoffset(char str[], int i, int index){
	while(str[i] != '\n' && i > 0)
		{
			i--;
		}
		if(i + 1 == 1)
			return 0;
	return i + 1;
}
int totallines(char str[])
{
	int l = strlen(str);
	int i, countc = 0;
	for(i = 0; i < l; i++)
	{
		if(str[i] == '\n')
		{
			countc++;
		}
	}
	return countc + 1;
}
int kmp(char *pat, char *path) 
{ 
	 int fd = open(path, O_RDONLY);
	 if(fd == -1)
	 {
	 	nofile = 1;
	 	return 0; 
	 }
     int l = lseek(fd, 0, SEEK_END);
     char *str, *str1;
      str = (char*)malloc((l + 1) * sizeof(char));
     
     lseek(fd, 0, 0);        
	 close(fd);
	 FILE *fp = fopen(path, "r");
	 if(fp == NULL){
	 	printf("\n No such file or directory \n");
	 	exit(2);
	 }
	 int i = 0;
	 while(1)
	 {
	 	str[i] = fgetc(fp);
	 	if(str[i] == EOF)
	 		break;
	 	i++;
	  } 
	 
	 
	 str[i] = '\0';
	 int numcount = 0;
	 i = 0;
	int *index = KMPS(pat, str, 1, 20); 
  
  	c = index[0];
  	//printf("\n%d$$$ \n", c);
  	i = 0;
  		if(!search(a, 11) && !search(a, 12))
		{
			
			if(search(a, 6) && !search(a, 11) && !search(a, 12)) 	                                    
			{
		/*		if(c == 1){
					printf("sad");
					readeachline(path);
				}
		*/		if(search(a, 8))
				{
					if(index[0] == 1)
					{
					//	puts(str);
						readeachline(path);
						exit(0);
					}
					
					for(i = 1; i < index[0]; i++)
					{
						if(i + 1 == num)
						{
							exit(0);
						}
						printvline(str, index, index[i], i, index[0], path);
					}
				}
				else
				{
					if(index[0] == 1)
					{
					//	puts(str);
						readeachline(path);
						exit(0);
					}
					
					for(i = 1; i < index[0]; i++)
					{
						
						if(i + 1 == num)
						{
							exit(0);
						}
						printvline(str, index, index[i], i, index[0], path);
						if(!search(a, 4))
							printf("\n");
					}		
				}
			
			}
			else
			{
				if(search(a, 8))
				{
					for(i = 1; i < index[0]; i++)
					{
						
						if(i + 1 == num)
						{
							exit(0);
						}
						if(search(a, 5) && !ef)
							printf("\n%s%d:%s ", KGRN, byteoffset(str, index[i], i), KWHT);
						printline(str, index[i], index, path);	
					}
				}	
				else
				{
					for(i = 1; i < index[0]; i++)
					{
						if(i  == num + 1)
						{
							exit(0);
						}
						 if(search(a, 5) && !ef)
							printf("\n%s%d:%s ", KGRN, byteoffset(str, index[i], i), KWHT);
						printline(str, index[i], index, path);	
					}	
				}
			}
		}
	
	if(search(a, 4) && !ef)
	{
		if(search(a, 8) || (search(a, 0) && !search(a, 7)))
			printf("\n %s%s%s:%s", KMAG, path, KGRN, KWHT);
		if(search(a, 6))
		{
			vcount = totallines(str);
			if(strlen(pat) == 1){
				vcount = vcount - c;
				vcount = vcount - 2;
				printf("\n%d\n", vcount + 2);
	
			}
			else{
				vcount = vcount - c;
				vcount = vcount - 1;
				printf("\n%d\n", vcount + 1);
	
			}
		}
		else if(strlen(pat) == 1){
			printf("%d\n", c - 2);
		}
		else{
			printf("%d\n", c - 1);
		}
	}
	normal_c = normal_c + c - 1;
	return 0; 
} 
