//
//  trie.c
//  trie
//
//  Created by Joe Million on 3/6/14.
//  Copyright (c) 2014 iMillIndustries. All rights reserved.
//


#include "trie.h"



// Creates a new node
trieNode* trieNodeCreate()
{
    trieNode* tn = (trieNode *) calloc(1, sizeof(trieNode));
    return tn;
}

// removes a node
void trieRemoveNode(trieNode* node)
{
    for(int i = 0; i < 27; ++i)
        if(node->children[i])
            trieRemoveNode(node->children[i]);
    free(node);
}



// checks to see if a word is present in the root node, returns true if yes, else false
bool trieWordIsFound(const char* word, const trieNode* root)
{
    int length = (int) strlen(word);
    trieNode* nextTri = NULL;
    
    for (int i = 0; i < length; i++)
    {
        int index = trieIndexForChar(word[i]);
        if (nextTri)
        {
            if (nextTri->children[index])
            {
                nextTri = nextTri->children[index];
            }
            else return false;
        }
        else
        {
            if (root->children[index])
            {
                nextTri = root->children[index];
            }
            else return false;
        }
        
        if (i == length - 1)
        {
            if (nextTri->isWord)
            {
                return true;
            }
            return false;
        }
        
    }
    
    return NULL;
}

// inserts word into trie
void trieWordInsert(const char* word, trieNode* root)
{
    int length = (int) strlen(word);
    trieNode* nextTri = NULL;
    
    for (int i = 0; i < length; i++)
    {
        int index = trieIndexForChar(word[i]);
        
        if (index < 0)
        {
            printf("FAIL: word:%s \n", word);
        }
        
        if (nextTri)
        {
            if (!nextTri->children[index])
            {
                nextTri->children[index] = trieNodeCreate();
            }
            
            nextTri = nextTri->children[index];
            
        }
        
        else if (root->children[index] && i == 0)
        {
            
            nextTri = root->children[index];
        }
        
        else if ( (!root->children[index]) && i == 0)
        {
            
            root->children[index] = trieNodeCreate();
            nextTri = root->children[index];
            
        }
        
        else if (i == length - 1 && word[i] == '\n')
        {
            nextTri->isWord = true;
        }
        
    }
}

// return int for mapping to child array
// return -1 for fail.
int trieIndexForChar(char input)
{
    if (islower(input) )
    {
        return input - 'a';
    }
    else if (isupper(input))
    {
        return input - 'A';
    }
    else if (strcmp(&input, "\'") == 0)
    {
        printf("Returning 26");
        return 26;
    }
    else
    {
        printf("Fail char: %c\n", input);
        return -1;
    }
    
}
