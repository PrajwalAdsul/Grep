#include <stdio.h>
#include <stdlib.h>
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