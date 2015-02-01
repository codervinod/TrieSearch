//
//  main.cpp
//  TrieSearch
//
//  Created by Vinod Gupta on 1/29/15.
//  Copyright (c) 2015 Vinod Gupta. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

class TrieNode
{
public:
    TrieNode(char k,int v):_key(k),_val(v),_next(NULL),_children(NULL)
    {}
    virtual ~TrieNode()
    {
        if(_next)
            delete _next;
        if(_children)
            delete _children;
    }
    
    char key() {return _key;}
    int val() {return _val;}
    
    TrieNode *next() {return _next;}
    TrieNode *child() {return _children;}
    
    void AddNext(TrieNode *next) {_next = next;}
    void AddChild(TrieNode *child) {_children = child;}
    
private:
    char _key;
    int _val;
    TrieNode *_next;
    TrieNode *_children;
};

class Trie
{
public:
    Trie()
    {
        _root = new TrieNode('.',0);
    }
    virtual ~Trie()
    {
        if(_root)
            delete _root;
    }
    
    void insertString(std::string word)
    {
        TrieNode *prev_itr = _root;
        TrieNode *node_itr = _root->child();

        for(std::string::const_iterator itr = word.begin(); itr != word.end(); ++itr)
        {
            const char c = *itr;
            
            if(!node_itr)
            {
                node_itr = new TrieNode(c,0);
                prev_itr->AddChild(node_itr);
                prev_itr = node_itr;
                node_itr = NULL;
                continue;
            }
            
            bool match_found = false;
            while(node_itr)
            {
                if(node_itr->key() == c)
                {
                    match_found = true;
                    prev_itr = node_itr;
                    node_itr = node_itr->child();
                    break;
                }
                prev_itr = node_itr;
                node_itr = node_itr->next();
            }
            
            if(!match_found)
            {
                node_itr = new TrieNode(c,0);
                prev_itr->AddNext(node_itr);
                prev_itr = node_itr;
                node_itr = NULL;
            }
        }
    }
    
    bool searchString(std::string word)
    {
        TrieNode *trie_itr = _root->child();
        for(std::string::const_iterator itr = word.begin(); itr != word.end(); ++itr)
        {
            const char c = *itr;
            bool char_found = false;
            while(trie_itr)
            {
                if(trie_itr->key() == c)
                {
                    char_found = true;
                    break;
                }
                trie_itr = trie_itr->next();
            }
            if(!char_found)
            {
                return false;
            }
            trie_itr = trie_itr->child();
        }
        return true;
    }
    
    void ReadDict()
    {
        std::ifstream fp("/usr/share/dict/words", std::ifstream::in);
        char word[256];
        while(fp.getline(word,256))
        {
            insertString(word);
        }
    }
    
private:
    TrieNode *_root;
};

int main(int argc, const char * argv[]) {
    Trie trie;
    trie.ReadDict();
    return 0;
}
