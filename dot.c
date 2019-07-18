#include <stdio.h>
#include <string.h>
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
