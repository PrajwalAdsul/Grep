#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <dirent.h>
#include <ctype.h>
/*
Note
I have declared many global variables across many files, hence I we can't really use a .h file here
 
#include "globals.c"	
#include "choose.c"
#include "priority.c"
#include "trie.c"
#include "foref.c"
#include "dot.c"
#include "brackets.c"
#include "reg.c"
#include "kmp.c"	
#include "rec_files.c"	
#include "help.c"
*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int *a, ef = 0, vcount = 0, normal_c = 0, count_option = 0, nofile = 0;	
struct Trie* head;
char word[2][20];
int num = INT_MAX;
int search(int *a, int s){
	int i;
	for(i = 0; i < count_option; i++){
		if(a[i] == s){
			return 1;
		}
	}
	return 0;
}
int isnumber(char str[]){
	int i = 0;
	if(str[i] == '0')
	{
		printf("\n bad number \n");
		exit(0);
	}
	while(i < strlen(str)){
		if(str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	num = atoi(str);
	return 1;
}
int isword(char str[]){
	if(str[0] == '-')
		return 0;
	if(isnumber(str)){
		return 0;
	}
	int i = 0;
	while(i < strlen(str)){
		if(str[i] == '.')
			return 0;
		i++;
	}	
	return 1;
}
int isoption(char str[]){
	if(strlen(str) == 2 && str[0] == '-')
		return 1;
	return 0;
}
int isfile(char str[]){
		int i = 0;
	while(i < strlen(str)){
		if(str[i] == '.')
			return 1;
		i++;
	}	
	return 0;	
}
int isreg(char str[])
{
	int l = strlen(str);
	int i;
	for(i = 0; i < l; i++)
	{
		if(str[i] == '$' || str[i] == '^' || str[i] == '.' || str[i] =='[' || str[i] == ':')
			return 1;
	}
	return 0;
}

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

#define C_SIZE 10000
struct Trie
{
	int leaf;	
	struct Trie* character[C_SIZE];
};
struct Trie* getNewTrieNode(){
	struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	node -> leaf = 0;
	int i;
	
	for (i = 0; i < C_SIZE; i++)
		node -> character[i] = NULL;
	return node;
}
void insert(struct Trie* *head, char* word)
{
	struct Trie* curr = *head;
	while (*word)
	{
		if (curr->character[*word - 'a'] == NULL)
			curr->character[*word - 'a'] = getNewTrieNode();
		curr = curr->character[*word - 'a'];
		word++;
	}
	curr->leaf = 1;
}
int searchtrie(struct Trie* head, char* word)
{
	if (head == NULL)
		return 0;
	struct Trie* curr = head;
	while (*word)
	{
		curr = curr->character[*word - 'a'];
		if (curr == NULL)
			return 0;
		word++;
	}
	return curr->leaf;
}
int Children(struct Trie* curr) 
{
	int i;
	for (i = 0; i < C_SIZE; i++)
	{
		if (curr->character[i])
		{
			return 1;	
		}
	}
	
	return 0;
}
int efcount = 0;
int efvcount = 0;
void readeachline(char path[]){
     int fd = open(path, O_RDONLY);
     int l = lseek(fd, 0, SEEK_END);
     lseek(fd, 0, 0);        
	 close(fd);
	 
	 char *str, *str1;
	 str = (char*)malloc((l + 1) * sizeof(char));
     
	 FILE *fp = fopen(path, "r");
	 int i = 0, j = 0, found, numcount = 0, lastn = 0;
	 char line[1000], line1[1000];
	 while(1)
	 {
	 	str[i] = fgetc(fp);

	 	if(str[i] >= 'A' && str[i] <= 'Z' && search(a, 1))
	 		line[j] = str[i] + 32;
	 	else
	 	    line[j] = str[i];
		 line1[j] = str[i];
	 	
	 	if(str[i] == EOF)
	 	{
			line[j] = '\0';
			line1[j] = '\0';
			found = searchtrie(head, line);
			
			if(found  && !search(a, 6))
			{
				
				if(!search(a, 4))
				{
					if(search(a, 8))
					{
						//printf("\n%s ", path);
						printf("%s%s:%s ", KMAG, path, KNRM);						
					}
					if(search(a, 5))
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);
					printf("\n");
				}
				efcount++;
				numcount++;
	 		}
			 else if(!found && search(a, 6))
	 		{
				if(!search(a, 4))
				{
					if(search(a, 8) && str[i + 1] != '\0')
					{
						printf("%s%s:%s ", KMAG, path, KNRM);						
					}

					if(search(a, 5) && str[i + 1] != '\0')
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);	
				}
				efvcount++;
				numcount++;	
	 		}
			 break;
		}
		 	if(line[j] == '\n')
	 	{
	 		
			line[j] = '\0';
			line1[j] = '\0';
			found = searchtrie(head, line);
			if(found  && !search(a, 6))
			{
				if(!search(a, 4))
				{
					if(search(a, 8))
					{
							printf("%s%s:%s ", KMAG, path, KNRM);						
					}
					if(search(a, 5))
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);	
				}
				efcount++;
				numcount++;	
	 		}
			 else if(!found && search(a, 6))
	 		{	
	 			if(!search(a, 4))
				{
					if(search(a, 8))
					{
						printf("%s%s:%s ", KMAG, path, KNRM);							
					}

					if(search(a, 5))
					{
						printf("%s%d: %s", KGRN, lastn, KWHT);
					}
					puts(line1);	
				}
				efvcount++;
				numcount++;	
	 		}
			lastn = i + 1; 
			 j = -1;
			}
		 if(numcount == num)
		 	break;
		 
		 
		j++;
		i++;	
	  } 
	  if(search(a, 4) )	 
	  {
		if(search(a, 8))
			printf("%s%s:%s ", KMAG, path, KNRM);										
		 if(search(a, 6))
			printf("%d \n", efvcount - 1);
		else
			printf("%d \n", efcount);
	  }
}
void makeitline(char str[], int index){
	int l = strlen(str), i, j;
	i = index;
	char line[1000];
	while(str[i] != '\n' && i != 0){
		i--;
	}
	if(i != 0){
		i++;
	}
	j = 0;
	while(i < l && str[i] != '\n')
	{
		line[j] = str[i];
		i++; j++;
	}
	line[j] = '\0';
	if(!searchtrie(head, line))
		insert(&head, line);
}
void printlinereg(char*, int);
int find(char str[], char pat[], char firstchar, int firstcharindex)
{
	int i, j, k, l = strlen(str), lpat= strlen(pat);
	for(i = 0; i < l; i++)
	{
		if(str[i] == firstchar)
		{ 
		    k = i;
			for(j = 0; j < firstcharindex; j++)
				k--;			
			for(j = 0; j < lpat; j++)
			{
				if(pat[j] != '.')
				{
					if(pat[j] != str[k])
					{
						break;
					}
				}
				k++;
			}
			if(j == lpat)
			{
				if((str[i + lpat] < 'A' || (str[i + lpat] > 'Z' && str[i + lpat] < 'a') || str[i + lpat] > 'z') && search(a, 2) && (str[i - 1] == ' ' || str[i - 1] == '\n'))
				{			
						makeitline(str, i);
				}
				else if(!search(a, 2))
					makeitline(str, i);
				while(str[i] != '\n')
					i++;
			}
			
		}			
	}
	return 0;
}
int dot(char str[], char pat[], int lpat){
	char firstchar;
	int i, j, firstcharindex;
	for(i = 0; i < lpat; i++)
	{
		if((pat[i] >= 'A' && pat[i] <= 'Z') || (pat[i] >= 'a' && pat[i] <= 'z' ))
		{
			firstchar = pat[i];
			firstcharindex = i;	
			break;
		}
	}

	find(str, pat, firstchar, firstcharindex);
	return 0;
}

int searchinc(int j, char ch, char c[][26])
{
	int i;
	for(i = 0; i < 26; i++)
	{
		if(c[j][i] == ch)
		return 1;
	}
	return 0;
}
int findb(char str[], char pat[], char firstchar, int firstcharindex, char c[][26])
{
	int i, j, k, l = strlen(str), lpat= strlen(pat);
	for(i = 0; i < l; i++)
	{
		if(str[i] == firstchar || firstchar == '@') 
		{ 
		    k = i;
			for(j = 0; j < firstcharindex; j++)
				k--;			
			for(j = 0; j < lpat; j++)
			{
				if(pat[j] != '.')
				{
					if(pat[j] != str[k])
					{
						break;
					}
				}
				else if(pat[j] == '.')
				{
					if(!searchinc(j, str[k], c))
						break;
				}
				k++;
			}
			if(j == lpat)
			{
				if((str[i + lpat] < 'A' || (str[i + lpat] > 'Z' && str[i + lpat] < 'a') || str[i + lpat] > 'z') && search(a, 2) && (str[i - 1] == ' ' || str[i - 1] == '\n'))
				{			
					makeitline(str, i);
				}
				else if(!search(a, 2))
					makeitline(str, i);

				while(str[i] != '\n')
					i++;
			}
			
		}			
	}
	return 0;
}
int dotb(char str[], char pat[], int lpat, char c[][26]){
	char firstchar = '@';                
	int i, j, firstcharindex = 0;   
	lpat = strlen(pat);                    
	for(i = 0; i < lpat; i++)
	{
		if((pat[i] >= 'A' && pat[i] <= 'Z') || (pat[i] >= 'a' && pat[i] <= 'z' ))
		{
			firstchar = pat[i];
			firstcharindex = i;	
			break;
		}
	}
	findb(str, pat, firstchar, firstcharindex, c);
	return 0;
}

int aftern = 0, beforen = 0;
//aftern (^)     beforen ($)
int afterncount = 0;
int beforencount = 0;

void LPSArrayreg(char* pat, int M, int* lps); 
 
char *strlwrreg(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}
void printlinereg(char* str, int i){
	char str1[1000];
	int j = i;
	int l = strlen(str);
	for(j = i - 1; j >= 0; j--){
		if(str[j] == '\n')
			break;
	}
	int start = j + 1;
	if(i == 0)
		start = 0;
	for(j = i + 1; j < l; j++){
		if(str[j] == '\n' || str[j] == '\0'){
			break;
		}
	}
	str[j] = '\n';
	int end = j - 1;
	for(j = start; j <= end; j++)
		printf("%c", str[j]);
	
}
 
void KMPSreg(char* pat, char* txt, char path[]) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
    int lps[M]; 
    LPSArrayreg(pat, M, lps); 
  
    int i = 0;  
    int j = 0;  
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            
			if(aftern)
			{
				if(txt[i - j - 1] == '\n' || i - j == 0)
				{
					if(search(a, 2))
					{	


						if((txt[i - j + M] < 'A' || (txt[i - j + M] > 'Z' && txt[i - j + M] < 'a') || txt[i - j + M] > 'z') && search(a, 2))
						{

							if(search(a, 10))
							{
								exit(0);
							}
							makeitline(txt, i - j);
						}
						
					}
					else if(!search(a, 2))
					{
						if(search(a, 10))
						{
							exit(0);
						}					
						makeitline(txt, i - j);
						
					}
				}	
			}
			if(beforen)
			{
				if(txt[i - j + strlen(pat) + 1] == '\n' || i - j + strlen(pat) == N)
				{
					if(search(a, 2) && (txt[i - j - 1] == '\n' || txt[i - j - 1]== ' '))
					{
						
						if(search(a, 10))
						{
							exit(0);
						}
						makeitline(txt, i - j);
						
					}
					else if(!search(a, 2))
					{

						if(search(a, 10))
						{
							exit(0);
						}
						makeitline(txt, i - j);
					}
				}
			}
			
			j = lps[j - 1]; 
        } 
  		 else if (i < N && pat[j] != txt[i]) { 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
} 
void LPSArrayreg(char* pat, int M, int* lps) 
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
int kmpreg(char pat[], char path[]) 
{ 
	 int fd = open(path, O_RDONLY);
	 if(fd == -1)
	 	exit(0);
     int l = lseek(fd, 0, SEEK_END);
	 lseek(fd, 0, 0);        
     char *str, *str1;
	 str = (char*)malloc((l + 1) * sizeof(char));
   	 //read(fd, str, l);
	 close(fd);
	 FILE *fp = fopen(path, "r");
	 if(fp == NULL)
	 		exit(0);
	 int i = 0;
	 while(1)
	 {
	 	str[i] = fgetc(fp);
	 	if(str[i] == EOF)
	 		break;
	 	i++;
	  } 
	 
	 
	 str[i] = '\0';
	 if(search(a, 1))
	 {
	 	strcpy(str, strlwrreg(str));
	 	strcpy(pat, strlwrreg(pat));
	 }


    KMPSreg(pat, str, path); 
    return 0; 
}
int isdot(char str[])
{
	int i, l = strlen(str);
	for(i = 0; i < l; i++)
	{
		if(str[i] == '.')
			return 1;
	}
	return 0;
}
void reg(char str[], char path[])
{	
	int lstr = strlen(str), l, i = 0;
	if(str[0] == '^' && str[1] != '[')
	{
		aftern = 1;
		for(i = 0; i < lstr - 1; i++)
		{
			str[i] = str[i + 1];
		}
		str[lstr - 1] = '\0';
		kmpreg(str, path);

		readeachline(path);
		exit(0);
	}
	if(str[lstr - 1] == '$')
	{
		beforen = 1;
		str[lstr - 1] = '\0';
		kmpreg(str, path);

		readeachline(path);					
		exit(0);
	}
	
	
	if(isdot(str))
	{
		 int fd = open(path, O_RDONLY);
	     if(fd == -1)
	     {
	     	exit(0);
	     }
	     int l = lseek(fd, 0, SEEK_END);
		 lseek(fd, 0, 0);        
	     char  *str1;
		 str1 = (char*)malloc((l + 1) * sizeof(char));
		 close(fd);
		 FILE *fp = fopen(path, "r");
		 if(fp == NULL)
		 	exit(0);
		 int i = 0;
		 while(1)
		 {
		 	str1[i] = fgetc(fp);
		 	if(str1[i] == EOF)
		 		break;
		 	i++;
		} 
		 str1[i] = '\0';
		 fclose(fp);
		 if(search(a, 1))
		 {
		 	strcpy(str1, strlwrreg(str1));
		 	strcpy(str, strlwrreg(str));	
		 }
	    printf("\n");
		 dot(str1, str, strlen(str));	
		 readeachline(path);
		 exit(0);
	}
	
	int j = 0, k;
	char c[lstr][26], str1[lstr];
	for(i = 0; i < lstr; i++)
		for(j = 0; j < 26; j++)
			c[i][j] = '$';
	
	
	j = 0;
	for(i = 0; i < lstr; i++)
	{
		if(str[i] == '[')
		{
			k = 0;
			i++;
			while(str[i] != ']' && i < lstr)
			{
				c[j][k] = str[i];
				i++;
				k++;
			}
			str1[j] = '.';
			j++;
			continue;
		}
		str1[j] = str[i]; j++;	
	}
	str1[j] = '\0';
	 int fd = open(path, O_RDONLY);
	 if(fd == -1)
	 	exit(0);
     l = lseek(fd, 0, SEEK_END);
	 lseek(fd, 0, 0);        
    str = (char*)malloc((l + 1) * sizeof(char));
   	 close(fd);
	 FILE *fp = fopen(path, "r");
	 if(fp == NULL)
	 	exit(0);
	 i = 0;
	 while(1)
	 {
	 	str[i] = fgetc(fp);
	 	if(str[i] == EOF)
	 		break;
		 	i++;
	} 
	 str[i] = '\0';
	 fclose(fp);
	 if(search(a, 1))
	 {
	 	strcpy(str1, strlwrreg(str1));
	 	strcpy(str, strlwrreg(str));	
	 }
	 printf("\n");
	 dotb(str, str1, strlen(str), c);	
	 readeachline(path);
	 exit(0);
}

//#include <ctype.h>
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

void listFilesRecursively(char *path);
void rec(char path[])
{
    listFilesRecursively(path);
}
void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
	
	if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
			if(isfile(path))
			{
				kmp(word[0], path);
			}		
            listFilesRecursively(path);
        }
    }
    closedir(dir);
}

void showhelp(){
	printf("%s", KRED);
	printf("  Usage: grep [OPTION]... PATTERN [FILE]... \n  Search for PATTERN in each FILE.\n  Example: grep -i 'hello world'  main.c \n");
	printf("%s", KGRN);
	printf("  -r       traverse through directories nd grep\n");
	printf("  -w       force PATTERN to match only whole words\n");
	printf("  -m[NUM]  stop after NUM matches\n");
	printf("  -q       returns a value so that grep can be used by other programs\n");
	printf("  -i       ignore case distinctions\n");
	printf("  -v       select non-matching lines\n");
	printf("  -n       print line number with output lines\n");
	printf("  -c       print only a count of matching lines per FILE\n");
	printf("  -b       print the byte offset with output lines\n");
	printf("  -f       search pattern from file\n");
	printf("  -e       to match word starting with non-alphabet character or for searching multiple patterns\n");
	printf("  -h       suppress the file name prefix on output\n");
	printf("  -H       print the file name for each match\n");
	printf("%s", KYEL);
	printf("  for regular expressions\n");		
	printf("  ^word    grep only those lines whose starting word is word\n");
	printf("  word$    grep only those lines whose ending word is word\n");
	printf("  w.r.     . can hold any values\n");
	printf("  [abc][cd]s    choose between characters in brackets and grep\n");
	printf("%s  Can use any combinations of above commands \n %s eg:- ./project word -v -i -w -c file.txt\n", KCYN, KGRN);
}


int main(int argc, char *argv[]){
	if(argc == 1)
	{
		printf("use ./try --help for help \n");
		return 2;
	}
	if(!strcmp(argv[1], "--help"))
	{
		showhelp();
		return 0;
	}
	if(argc < 3)
	{
		printf("\n bad arguements \n");
		return 130;
	}
	char files[10][20], options[10][3];	
	int i, count_file = 0, count_word = 0;
	strcpy(word[0], " ");
	strcpy(word[1], " ");
	
	for(i = 1; i < argc; i++){
		if(isword(argv[i]))
			strcpy(word[count_word++], argv[i]);
		if(isoption(argv[i]))
			strcpy(options[count_option++], argv[i]);
		if(isfile(argv[i]))
			strcpy(files[count_file++], argv[i]);
	}
	
	a = decide_priority(options, count_option);	

	head = getNewTrieNode();
	
	if(isreg(argv[1]))
	{
		int dotc = 0;
		for(i = 0; i < strlen(argv[1]); i++)
		{
			if(argv[1][i] == '.')
				dotc++;
		}
		if(dotc >= 2)
		{
			strcpy(files[0], files[1]);
		}
		reg(argv[1], files[0]);                            //everthing about reg
		return 0;
	}



	if(num != INT_MAX && !(search(a, 9))){
		printf("%d in command without using -m", num);
		exit(0);
	}

	if(count_file == 0 && search(a, 10))
	{
		return 2;
	}

	FILE *fp;
	fp = fopen("temp.txt", "w");
	
	if(search(a, 12) || search(a, 11))
	{	
		ef = 1;
	}
	if(search(a, 12) && !search(a, 11)){
		for(i = 1; i < argc; i++){
			if(!strcmp(argv[i], "-e") && (isword(argv[i + 1]) || ( (strlen(argv[i + 1]) > 2) && argv[i][0] == '-' ) )   ){
				kmp(argv[i + 1], files[0]);
			}
		}
		readeachline(files[0]);
	}
	if(search(a, 12)){
		for(i = 1; i < argc; i++){
			if(!strcmp(argv[i], "-e") && (isword(argv[i + 1]) || ( (strlen(argv[i + 1]) > 2) && argv[i][0] == '-' ) )   ){
				fputs(argv[i + 1], fp);
				fputc('\n', fp);
			}
		}
	}
	
	char str[100];
	if(search(a, 11)){
		 FILE *fp1 = fopen(files[0], "r");	
		if(!fp1)
		{
			printf("File not found \n");
			exit(0);
		}
		while(fgets(str, 100, fp1)){
			fputs(str, fp);
		}
	}	
	fclose(fp);

	if(search(a, 11) || search(a, 12))
	{
		if(count_file == 1 && search(a, 11))
		{
			printf("\n Bad arguements only one file specified \n");
			exit(0);
		}
		 fp = fopen("temp.txt", "r");
		 while(fgets(str, 100, fp)){
			str[strlen(str) - 2] = '\0';
			kmp(str, files[1]);	 	
		 }
	}
	
	if((search(a, 11) && search(a, 12)) || search(a, 11)) {
		readeachline(files[1]);
		exit(0);
	}

	if(!strcmp(word[1], " ")){
		for(i = 0; i < count_file; i++)
			kmp(word[0], files[i]);
	}
	
	if(!strcmp(word[1], " "))
		strcpy(word[1], word[0]);
	
	if(a[0] == 0){
		rec(word[1]);
	}
	fclose(fp);
	remove("temp.txt");
	
	if(nofile && search(a, 10))
	{
		return 2;
	}

	if(search(a, 10))
	{
		return 1;
	}
	return 0;
}
