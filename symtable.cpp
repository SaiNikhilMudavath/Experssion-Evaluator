/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"


void destroytree(SymEntry* root)
{
    if(root==nullptr)
    {
        return;
    }
    destroytree(root->left);
    destroytree(root->right);
    delete root;
}
void inserthelper(SymEntry*& root,SymEntry* ins)
{
    //cout<<"entered insert"<<endl;
    if(root==nullptr)
    {
        //cout<<"root is nullptr"<<endl;
        root=ins;
        return;
    }
    if(root->key<ins->key)
    {
        //cout<<"root<ins"<<endl;
        inserthelper(root->right,ins);
        return;
    }
    else if(root->key>ins->key)
    {
        //cout<<"ins<root"<<endl;
        inserthelper(root->left,ins);
        
        return;
    }
    else
    {
        //cout<<"Else"<<endl;
        return;
    }
    //cout<<"didn't fnd condition"<<endl;
}
SymbolTable::SymbolTable()
{
    root=new SymEntry();
    size=1;
}
SymbolTable::~SymbolTable()
{
     // we should delete the whole tree not just the root node but also all other nodes
    destroytree(root);
}
void SymbolTable::insert(string k,UnlimitedRational* v)
{
    SymEntry* ins=new SymEntry(k,v);
    inserthelper(root,ins);
}
void SymbolTable::remove(string k)
{
    SymEntry* roo=get_root();
    SymEntry* parent=nullptr;
    bool is=true;
    while(is)
    {
        if(k<root->key)
        {
            parent=roo;
            roo=roo->left;
        }
        else if(k>root->key)
        {
            parent=roo;
            roo=roo->right;
        }
        else
        {
            if((roo->left==nullptr)&&(roo->right==nullptr))
            {
                if(parent==nullptr)
                {
                    root=nullptr;
                }
                else if(parent->left==roo)
                {
                    parent->left=nullptr;
                }
                else if(parent->right==roo)
                {
                    //parent->right==nullptr;
                }
                delete roo;
                size=size-1;
                is=false;
            }
            else if((root->left==nullptr)||(root->right=nullptr))
            {
                SymEntry* child=(roo->left!=nullptr)? roo->left: roo->right;
                if(parent==nullptr)
                {
                    root=child;
                }
                else if(parent->left==roo)
                {
                    parent->left=child;
                }
                else
                {
                    parent->right=child;
                }
                delete roo;
                size=size-1;
                is=false;
            }
            else
            {
                SymEntry* succparent=roo;
                SymEntry* succ=roo->right;
                while(succ->left!=nullptr)
                {
                    succparent=succ;
                    succ=succ->left;
                }
                root->key=succ->key;
                root->val=succ->val;
                if(succparent->left==succ)
                {
                    succparent->left=succ->right;
                }
                else
                {
                    succparent->right=succ->right;
                }
                delete succ;
                size=size-1;
                is=false;
            }
        }
    }
}
UnlimitedRational* SymbolTable::search(string k)
{
    SymEntry* roo=get_root();
    if(root==nullptr)
    {
        return roo->val; //just written something. what to write,you cant return roo->right
    }
    bool is=true;
    while(is)
    {
        if(k<roo->key)
        {
            roo=roo->left;
        }
        else if(k>roo->key)
        {
            roo=roo->right;
        }
        else
        {
            return roo->val;
            is=false;
        }
    }
    return nullptr;
}
int SymbolTable::get_size()
{
    return size;
}
SymEntry* SymbolTable::get_root()
{
    return root;
}