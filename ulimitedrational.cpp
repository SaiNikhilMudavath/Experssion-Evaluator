/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedInt* gcd(UnlimitedRational* i)
{
    UnlimitedInt* n=i->get_p();
    UnlimitedInt* d=i->get_q();
    //cout<<"not seg fault for get p and q "<<endl;
    if(d->get_array()[(d->get_size())-1]==0)
    {
        return n;
    }
    //cout<<"not seg fault for 0"<<endl;
    UnlimitedInt* mo=UnlimitedInt::mod(n,d);
    //cout<<"not seg fault for indi mod"<<endl;
    UnlimitedRational* result=new UnlimitedRational(d,mo);
    //cout<<"not seg fault for mod"<<endl;
    return gcd(result);
}
UnlimitedRational::UnlimitedRational()
{
    p=new UnlimitedInt();
    q=new UnlimitedInt();
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num,UnlimitedInt* den)
{
    if(den->get_array()[(den->get_size())-1]==0)
    {
        p=den;q=den;
    }
    p=num;q=den;
}
UnlimitedRational::~UnlimitedRational()
{
    delete[] p;
    delete[] q;
}
UnlimitedInt* UnlimitedRational::get_p()
{
    return p;
}
UnlimitedInt* UnlimitedRational::get_q()
{
    return q;
}
string UnlimitedRational::get_p_str()
{
    return p->to_string();
}
string UnlimitedRational::get_q_str()
{
    return q->to_string();
}
string UnlimitedRational::get_frac_str()
{
    UnlimitedInt* n=p;
    UnlimitedInt* d=q;
    int s1=n->get_sign();int s2=d->get_sign();
    if(s1*s2==1)
    {
        string s1=n->to_string();
        string s2="/";
        string s3=d->to_string();
        return s1+s2+s3;
    }
    else if(s1*s2==-1)
    {
        //string s1="-";
        string s2=n->to_string();
        string s3="/";
        string s4=d->to_string();
        return s2+s3+s4;
    }
    else
    {
        string s="0/0";
        return s;
    }
}
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1,UnlimitedRational* i2)
{
    //cout<<"entered add"<<endl;
    UnlimitedRational* result=new UnlimitedRational();
    UnlimitedInt* n1=UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* n2=UnlimitedInt::mul(i1->q,i2->p);
    UnlimitedInt* d=UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedInt* n=UnlimitedInt::add(n1,n2);
    result->p=n;
    result->q=d;
    //cout<<"not seg fault for arithmetic"<<endl;
    UnlimitedInt* f=gcd(result);
    //cout<<"not seg fault for gcd"<<endl;
    //int* ne=f->get_array();
    result->p=UnlimitedInt::div(result->p,f);
    result->q=UnlimitedInt::div(result->q,f);
    //cout<<"not seg fault for div"<<endl;
    // int* np=result->get_p()->get_array();
    // //cout<<"start:";
    // for(int i=0;i<result->get_p()->get_size();i++)
    // {
    //     //cout<<np[i]<<" ";
    // }
    // //cout<<"finish"<<endl;
    // int* nq=result->get_q()->get_array();
    // //cout<<"start:";
    // for(int i=0;i<result->get_q()->get_size();i++)
    // {
    //     //cout<<nq[i]<<" ";
    // }
    // //cout<<"finish"<<endl;
    return result;
}
UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1,UnlimitedRational* i2)
{
    UnlimitedRational* result=new UnlimitedRational();
    UnlimitedInt* n1=UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* n2=UnlimitedInt::mul(i1->q,i2->p);
    UnlimitedInt* d=UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedInt* n=UnlimitedInt::sub(n1,n2);
    result->p=n;
    result->q=d;
    UnlimitedInt* f=gcd(result);
    result->p=UnlimitedInt::div(result->p,f);
    result->q=UnlimitedInt::div(result->q,f);
    return result;
}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1,UnlimitedRational* i2)
{
    UnlimitedRational* result=new UnlimitedRational();
    UnlimitedInt* n=UnlimitedInt::mul(i1->p,i2->p);
    UnlimitedInt* d=UnlimitedInt::mul(i1->q,i2->q);
    result->p=n;result->q=d;
    UnlimitedInt* f=gcd(result);
    result->p=UnlimitedInt::div(result->p,f);
    result->q=UnlimitedInt::div(result->q,f);
    return result;
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1,UnlimitedRational* i2)
{
    UnlimitedRational* result=new UnlimitedRational();
    UnlimitedInt* n=UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* d=UnlimitedInt::mul(i1->q,i2->p);
    result->p=n;result->q=d;
    UnlimitedInt* f=gcd(result);
    result->p=UnlimitedInt::div(result->p,f);
    result->q=UnlimitedInt::div(result->q,f);
    return result;
}