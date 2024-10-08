/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarelse ified on Piazza. */
#include "evaluator.h"


void postordereval(ExprTreeNode* root,SymbolTable* symtable)
{
    //cout<<"Entered postorder eval"<<endl;
    if(root==nullptr)
    {
        //cout<<"returning now"<<endl;
        return;
    }
    //cout<<"going to left"<<endl;
    postordereval(root->left,symtable);
    //cout<<"going to right"<<endl;
    //cout<<"before seg fault"<<endl;
    postordereval(root->right,symtable);
    if(root->type=="ADD")
    {
        //cout<<"entered add"<<endl;
        //cout<<root->left->evaluated_value->get_frac_str()<<endl;
        //cout<<"frac returned"<<endl;
        //cout<<root->right->evaluated_value->get_frac_str()<<endl;
        //cout<<"frac returned"<<endl;
        //cout<<root->evaluated_value->get_frac_str()<<endl;
        //cout<<"frac returned"<<endl;
        //cout<<UnlimitedRational::add(root->left->evaluated_value,root->right->evaluated_value)->get_frac_str()<<endl;
        //cout<<"frac returned"<<endl;
        root->evaluated_value=UnlimitedRational::add(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(root->type=="SUB")
    {
        //cout<<"entered sub"<<endl;
        root->evaluated_value=UnlimitedRational::sub(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(root->type=="MUL")
    {
        //cout<<"entered mul"<<endl;
        root->evaluated_value=UnlimitedRational::mul(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(root->type=="DIV")
    {
        //cout<<"entered div"<<endl;
        root->evaluated_value=UnlimitedRational::div(root->left->evaluated_value,root->right->evaluated_value);
    }
    //cout<<"nothing"<<endl;
    // else if(root->type=="EQUAL")
    // {
    //     root->evaluated_value=root->right->evaluated_value;
    // }
    // else if(root->type=="VAR")
    // {
    //     root->evaluated_value=symtable->search(root->id);
    // }
    // else if(root->type=="VAL")
    // {
    //     root->evaluated_value=root->evaluated_value;
    // }
}

Evaluator::Evaluator()
{
    symtable=new SymbolTable();
}
Evaluator::~Evaluator()
{
    delete symtable;
}
void Evaluator::parse(vector<string> code)
{
    ////cout<<"entered parse"<<endl;
    vector<ExprTreeNode*> t;
    ExprTreeNode* root=new ExprTreeNode();
    root->left=new ExprTreeNode();
    root->left->type="VAR";
    //root->value or root->eval_value? value or evaluated value for variable;
    root->left->id=code[0];
    root->left->left=nullptr;root->left->right=nullptr;
    root->type="EQUAL";
    root->right=new ExprTreeNode();
    //root->value or root->eval value?;
    //ExprTreeNode* temp=new ExprTreeNode();
    ExprTreeNode* temp=root->right;
    ////cout<<"before run"<<endl;
    t.push_back(temp);
    for(std::vector<string>::size_type i=2;i<code.size();i++)
    {
        ////cout<<"entered for"<<endl;
        if(code[i]=="(")
        {
            temp->left=new ExprTreeNode();
            t.push_back(temp);
            temp=temp->left;
        }
        else if(code[i]=="+")
        {
            temp->type="ADD";
            temp->right=new ExprTreeNode();
            t.push_back(temp);
            temp=temp->right;
        }
        else if(code[i]=="-")
        {
            temp->type="SUB";
            temp->right=new ExprTreeNode();
            t.push_back(temp);
            temp=temp->right;
        }
        else if(code[i]=="*")
        {
            temp->type="MUL";
            temp->right=new ExprTreeNode();
            t.push_back(temp);
            temp=temp->right;
        }
        else if(code[i]=="/")
        {
            temp->type="DIV";
            temp->right=new ExprTreeNode();
            t.push_back(temp);
            temp=temp->right;
        }
        else if(code[i]==")")
        {
            temp=t.back();
            t.pop_back();
        }
        else if(('0'<=code[i][0])&&(code[i][0]<='9'))
        {
            ////cout<<"entered val"<<endl;
            temp->type="VAL";
            ////cout<<"assignmed val"<<endl;
            UnlimitedInt* t1=new  UnlimitedInt(code[i]);
            UnlimitedInt* t2=new UnlimitedInt("1");
           // //cout<<"rational sarts"<<endl;
            UnlimitedRational* r=new UnlimitedRational(t1,t2);
            ////cout<<"asignment complete"<<endl;
            temp->val=r;
            temp->evaluated_value=r;
            ////cout<<"pop starts"<<endl;
            temp=t.back();
            t.pop_back();
        }
        else
        {
            temp->type="VAR";
            temp->id=code[i];
            temp->val=symtable->search(temp->id);
            temp->evaluated_value=symtable->search(temp->id);
            temp=t.back();
            t.pop_back();
        }
    }
    //std:://cout<<"for runned"<<std::endl;
    root->right=temp; //modification starts.
    expr_trees.push_back(root);
    ////cout<<"exited"<<endl;
    
}
void Evaluator::eval()
{
    //cout<<'a'<<endl;
    ExprTreeNode* root=expr_trees[expr_trees.size()-1];
    //cout<<'b'<<endl;
    postordereval(root->right,symtable);
    //cout<<'c'<<endl;
    symtable->insert(root->left->id,root->right->evaluated_value);
    //cout<<'d'<<endl;
}