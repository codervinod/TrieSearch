//
//  main.cpp
//  TrieSearch
//
//  Created by Vinod Gupta on 1/29/15.
//  Copyright (c) 2015 Vinod Gupta. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
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
    
    bool insertString(std::string word)
    {
        TrieNode *prev_itr = _root;
        TrieNode *node_itr = _root->child();

        for(std::string::const_iterator itr = word.begin(); itr != word.end(); ++itr)
        {
            const char c = *itr;
            while(node_itr)
            {
                if(node_itr->val() == c)
                    break;
                prev_itr = node_itr;
                node_itr = node_itr->next();
            }
            if(!node_itr)
            {
                prev_itr->AddChild(new TrieNode(c,0));
                node_itr = prev_itr->child();
            }
        }
        
        return false;
    }
    
    
private:
    TrieNode *_root;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
