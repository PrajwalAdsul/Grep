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
