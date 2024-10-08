/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{
    val=new UnlimitedRational();
    evaluated_value=new UnlimitedRational();
    left=nullptr;
    right=nullptr;
}
ExprTreeNode::ExprTreeNode(string t,UnlimitedInt* v)
{
    UnlimitedInt* one=new UnlimitedInt(1);
    val=new UnlimitedRational(v,one);
     //should we write this.
    type=t;
    left=nullptr;
    right=nullptr;
}
ExprTreeNode::ExprTreeNode(string t,UnlimitedRational* v)
{
    val=v;type=t;
     //should we write this  what about id
    left=nullptr;
    right=nullptr;
}
ExprTreeNode::~ExprTreeNode()
{
    delete val;
    delete evaluated_value;
}