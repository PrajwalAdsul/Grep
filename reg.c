#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
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
