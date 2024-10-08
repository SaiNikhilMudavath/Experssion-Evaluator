/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

/*
my records::
get array give in reverse form
and the get frac str in unlimited rational gives in straight order only
remove iostream from all .cpp files
in get array return the array as it is means in which way you stored in that way
check if all the destructors are written correct*/



#include "ulimitedint.h"

UnlimitedInt* bigger(UnlimitedInt* i1,UnlimitedInt* i2)
{
    int s1=i1->get_size();int s2=i2->get_size();
    if(s1<s2)
    {
        return i2;
    }
    else if(s1>s2)
    {
        return i1;
    }
    else
    {
        int* a1=i1->get_array();int* a2=i2->get_array();
        for(int i=s1-1;i>=0;i--)
        {
            if(a1[i]>a2[i])
            {
                return i1;
            }
            else if(a1[i]<a2[i])
            {
                return i2;
            }
            else
            {}
        }
        return i1;
    }
}
UnlimitedInt::UnlimitedInt()
{
    capacity=20;
    unlimited_int=new int[capacity];
    size=0;
}
UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
    size=0;
    capacity=20;
}
UnlimitedInt::UnlimitedInt(string s)
{
    capacity=20;
    size=0;
    unlimited_int=new int[capacity];
    int n=s.length();
    ////cout<<n<<endl;
    ////cout<<s[0]<<endl;
    if(s[0]=='-')
    {
        sign=-1;
    }
    else if(s[0]=='0')
    {
        sign=0; 
    }
    else
    {
        sign=1;
    }
    if(s[0]=='-')
    {
        for(int i=n-1;i>=1;i--)
        {
            if(size>=capacity)
            {
                capacity*=2;
                int* ne=new int[capacity];
                for(int i=0;i<size;i++)
                {
                    ne[i]=unlimited_int[i];
                }
                delete[] unlimited_int;
                unlimited_int=ne;
            }
            unlimited_int[n-i-1]=s[i]-'0';
            size=size+1;
        }
    }
    else
    {
        for(int i=n-1;i>=0;i--)
        {
            if(size>=capacity)
            {
                capacity*=2;
                int* ne=new int[capacity];
                for(int i=0;i<size;i++)
                {
                    ne[i]=unlimited_int[i];
                }
                delete[] unlimited_int;
                unlimited_int=ne;
            }
            unlimited_int[n-i-1]=s[i]-'0';
            size=size+1;
        }
    }
}
UnlimitedInt::UnlimitedInt(int i)
{
    if(i>0)
    {
        capacity=20;
        size=0;sign=1;
        unlimited_int=new int[capacity];
    }
    else if(i<0)
    {
        capacity=20;size=0;sign=-1;
        unlimited_int=new int[capacity];
        i=-i;
    }
    while(i>0)
    {
        if(size<=capacity)
        {
            capacity*=2;
            int* ne=new int[capacity];
            for(int i=0;i<size;i++)
            {
                ne[i]=unlimited_int[i];
            }
            delete[] unlimited_int;
            unlimited_int=ne;
        }
        unlimited_int[size]=i%10;
        size=size+1;
        i=i/10;
    }
    for(int i=0;i<(size/2);i++)
    {
        int t=unlimited_int[i];
        unlimited_int[i]=unlimited_int[size-i-1];
        unlimited_int[size-i-1]=t;
    }
    if(i==0)
    {
        sign=0;size=1;
        unlimited_int=new int[capacity];
        unlimited_int[0]=0;
    }
}
UnlimitedInt::UnlimitedInt(int* ulimited_int,int cap,int sgn,int sz)
{
    capacity=cap;sign=sgn;size=sz;
    unlimited_int=ulimited_int;
}
int UnlimitedInt::get_size()
{
    return size;
}
int* UnlimitedInt::get_array()
{
    int* temp=new int[size];
    for(int i=0;i<size;i++)
    {
        temp[i]=unlimited_int[i];
    }
    // //cout<<"checkgetarray"<<unlimited_int[size-1]<<endl;
    return temp; // how to delete temp after returning . can we do that?
}
int UnlimitedInt::get_sign()
{
    return sign;
}
int UnlimitedInt::get_capacity()
{
    return capacity;
}
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1,UnlimitedInt* i2)
{
    if((i1->sign)*(i2->sign)==-1)
    {
        if((i1->sign)==-1)
        {
            i1->sign=1;
            return sub(i2,i1);
        }
        else
        {
            i2->sign=1;
            return sub(i1,i2);
        }
    }
    int s1=i1->size;int s2=i2->size;int max;
    if(s1<=s2)
    {
        max=s2;
    }
    else
    {
        max=s1;
    }
    UnlimitedInt* result=new UnlimitedInt();
    int c=0;int temp;
    if(result->size>=result->capacity)
    {
        result->capacity*=2;
        int* ne=new int[result->capacity];
        for(int i=0;i<result->size;i++)
        {
            ne[i]=result->unlimited_int[i];
        }
        delete[] result->unlimited_int;
        result->unlimited_int=ne;
    }
    for(int i=0;i<max;i++)
    {
        temp=c;
        if(i<s1)
        {
            temp=temp+i1->unlimited_int[i];
        }
        if(i<s2)
        {
            temp=temp+i2->unlimited_int[i];
        }
        c=temp/10;temp=temp%10;
        result->unlimited_int[result->size]=temp;
        result->size+=1;
    }
    if(c!=0)
    {
        if(result->size>=result->capacity)
        {
            result->capacity*=2;
            int* ne=new int[result->capacity];
            for(int i=0;i<result->size;i++)
            {
                ne[i]=result->unlimited_int[i];
            }
            delete[] result->unlimited_int;
            result->unlimited_int=ne;

        }
        result->unlimited_int[result->size]=c;
        result->size+=1;
    }
    result->sign=i1->sign;
    return result;
}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1,UnlimitedInt* i2)
{
    bool glob=true;
    if((i1->sign)*(i2->sign)==-1)
    {
        if((i1->sign)==-1)
        {
            //cout<<"p"<<endl;
            i2->sign=-1;
            return add(i2,i1);
        }
        else
        {
            i2->sign=1;
            return add(i1,i2);
        }
    }
    int s1=i1->size;int s2=i2->size;int max;int c=0;int temp=0;
    //cout<<s1<<" "<<s2<<endl;
    UnlimitedInt* result=new UnlimitedInt();
    if(s1<s2)
    {
        max=s2;
        //cout<<"entered s1<s2.max is:"<<max<<endl;
    }
    else if(s1>s2)
    {
        max=s1;
        //cout<<"entered s1>s2.max is:"<<max<<endl;
    }
    else
    {
        UnlimitedInt* hike=bigger(i1,i2);
        //cout<<"entered s1=s2"<<endl;

        if(hike!=i1)
        {
            glob=false;
            max=s1; 
            //cout<<"entered s1=s2.max is:"<<max<<endl;
            result->sign=-1;
            hike=i1;
            i1=i2;
            i2=hike;
            //cout<<"q"<<endl;
        }
        else
        {
            max=s1;
        }
    }
    if(result->size>=result->capacity)
    {
        result->capacity*=2;
        int* ne=new int[result->capacity];
        for(int i=0;i<result->size;i++)
        {
            ne[i]=result->unlimited_int[i];
        }
        delete[] result->unlimited_int;
        result->unlimited_int=ne;
        //cout<<"r"<<endl;
    }
    //cout<<max<<endl;
    for(int i=0;i<max;i++)
    {
        temp=c;
        if(s1>=s2)
        {
            if(i<s1)
            {
                temp=temp+i1->unlimited_int[i];
                ////cout<<"temp is1:"<<temp<<endl;
            }
            if(i<s2)
            {
                temp=temp-i2->unlimited_int[i];
                ////cout<<"temp is2:"<<temp<<endl;
            }
            result->sign=1;
        }
        else
        {
            if(i<s2)
            {
                temp=temp+i2->unlimited_int[i];
                ////cout<<"temp is1:"<<temp<<endl;
            }
            if(i<s1)
            {
                temp=temp-i1->unlimited_int[i];
                ////cout<<"temp is2:"<<temp<<endl;
            }
            result->sign=-1;
        }
        ////cout<<"s"<<endl;
        if(temp<0)
        {
            if(i==max-1)
            {
                temp=-temp;
                result->unlimited_int[result->size]=temp;
                result->size+=1;
                result->sign=-1;
            }
            else
            {
                c=-1;temp=10+temp;
                result->unlimited_int[result->size]=temp;
                ////cout<<"result:is"<<result->unlimited_int[result->size]<<endl;
                result->size+=1;
            }
            //cout<<"t"<<endl;
        }
        else 
        {
            c=0;
            result->unlimited_int[result->size]=temp;
            ////cout<<"result:is"<<result->unlimited_int[result->size]<<endl;
            result->size+=1;
        }
    }
    //cout<<"u"<<endl;
    if(c!=0)
    {
        if(result->size>=result->capacity)
        {
            result->capacity*=2;
            int* ne=new int[result->capacity];
            for(int i=0;i<result->size;i++)
            {
                ne[i]=result->unlimited_int[i];
            }
            delete[] result->unlimited_int;
            result->unlimited_int=ne;
        }
    }
    //cout<<"v"<<endl;
    while((result->size>1)&&(result->unlimited_int[(result->size)-1]==0))
    {
        result->size-=1;
    }
    //cout<<"w"<<endl;
    if(((i1->sign)==-1)&&((i2->sign==-1)))
    {
        result->sign*=-1;
    }
    if(!glob)
    {
        result->sign*=-1;
    }
    //cout<<"x"<<endl;
    return result;
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1,UnlimitedInt* i2)
{
    int s1=i1->size;int s2=i2->size;
    UnlimitedInt* result=new UnlimitedInt();
    int rsize=s1+s2;int temp=0;int c;
    for(int j=0;j<rsize;j++)
    {
        if(result->size>=result->capacity)
        {
            result->capacity*=2;
            int* ne=new int[result->capacity];
            for(int i=0;i<result->size;i++)
            {
                ne[i]=result->unlimited_int[i];
            }
            delete[] result->unlimited_int;
            result->unlimited_int=ne;
        }
        result->unlimited_int[j]=0;
        result->size+=1;
    }
    for(int i=0;i<s1;i++)
    {
        c=0;
        for(int j=0;j<s2;j++)
        {
            temp=c+((i1->unlimited_int[i])*(i2->unlimited_int[j]))+(result->unlimited_int[i+j]);
            c=temp/10;temp=temp%10;
            result->unlimited_int[i+j]=temp;
        }
        if(c!=0)
        {
            if(result->size>=result->capacity)
            {
                result->capacity*=2;
                int* ne=new int[result->capacity];
                for(int x=0;x<result->size;x++)
                {
                    ne[x]=result->unlimited_int[x];
                }
                delete[] result->unlimited_int;
                result->unlimited_int=ne;
            }
            result->unlimited_int[i+s2]+=c;
        }
    }
    while((result->size>1)&&(result->unlimited_int[(result->size)-1]==0))
    {
        result->size-=1;
    }
    result->sign=((i1->sign)*(i2->sign));
    return result;
}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1,UnlimitedInt* i2)
{
   UnlimitedInt* result=new UnlimitedInt();
   result->sign=((i1->sign)*(i2->sign));
   int s1=i1->sign;int s2=i2->sign;i1->sign=1;i2->sign=1;
   UnlimitedInt* quo=new UnlimitedInt();
   UnlimitedInt* temp=new UnlimitedInt();
   quo->capacity=i1->capacity;quo->size=i1->size;quo->unlimited_int=new int[quo->capacity];quo->sign=1;
   temp->unlimited_int=new int[temp->capacity];temp->sign=1;
   ////cout<<"assigned quo temp"<<endl;
   for(int i=0;i<quo->size;i++)
   {
        quo->unlimited_int[i]=0;
        temp->unlimited_int[i]=0;
   }
   UnlimitedInt* ten=new UnlimitedInt();
   ten->unlimited_int[0]=10;
   ten->size=1;ten->capacity=1;ten->sign=1;
   UnlimitedInt* d=new UnlimitedInt();
   d->size=1;d->capacity=1;d->sign=1;
   int qq=0;
   //cout<<"a"<<endl;
   ////cout<<"goingtoforbeforewhile"<<endl;
   for(int i=0;i<(i1->size);i++)
   {
        int q=0;
        temp=mul(temp,ten);
        //int* h=temp->get_array();
        // //cout<<"before loop:"<<endl;
        // for(int u=0;u<temp->get_size();u++)
        // {
        //     //cout<<h[i]<<" ";
        // }
        // //cout<<endl;
        d->unlimited_int[0]=i1->unlimited_int[(i1->size)-i-1];
        temp=add(temp,d);  
        //cout<<"b"<<endl;   
        while(bigger(temp,i2)==temp)
        {
            // //cout<<"in loop before assigning:"<<endl;
            // for(int u=0;u<temp->get_size();u++)
            // {
            //     //cout<<temp->get_array()[u]<<" ";
            // }
            // //cout<<endl;
            // //cout<<"check sub:"<<endl;
            // for(int o=0;o<sub(temp,i2)->get_size();o++)
            // {
            //     //cout<<sub(temp,i2)->get_array()[o]<<" ";
            // }
            // //cout<<endl;
            //cout<<"before seg fault"<<endl;
            temp=sub(temp,i2);
            //cout<<"after seg fault"<<endl;
            // //cout<<"after assigning"<<endl;
            // for(int u=0;u<temp->get_size();u++)
            // {
            //     //cout<<temp->get_array()[u]<<" ";
            // }
            // //cout<<endl;
            ////cout<<"inwhile"<<endl;
            q++;
        }
        //cout<<"exitedwhile"<<endl;
        quo->unlimited_int[qq]=q;
        qq+=1;
        ////cout<<"completed for"<<endl;
   }
   result->size=qq;
   result->capacity=quo->capacity;
   result->unlimited_int=new int[result->capacity];
   for(int i=0;i<qq;i++)
   {
        result->unlimited_int[i]=quo->unlimited_int[qq-i-1];
        ////cout<<"in for"<<endl;
   }
   //cout<<"exited for loop"<<endl;
   while((result->size>1)&&(result->unlimited_int[(result->size)-1]==0))
   {
       result->size-=1;
   }
   // //cout<<"exited last while"<<endl;
   ////cout<<"i1:"<<i1->sign<<" "<<"i2:"<<i2->sign<<endl;
   if(s1*s2==-1)
   {
        //int s1=i1->sign;int s2=i2->sign;
        // if(i1->sign==-1)
        // {
        //     i1->sign=1;
        // }
        // if(i2->sign==-1)
        // {
        //     i2->sign=1;
        // }
        //UnlimitedInt* mo=mod(i1,i2);
        if(temp->unlimited_int[(temp->get_size())-1]!=0) // temp to mo
        {
            ////cout<<"Entered mod loop"<<endl;
            UnlimitedInt* one=new UnlimitedInt();
            one->size=1;one->capacity=1;one->unlimited_int[0]=1;
            result=add(result,one);
            //cout<<"added one"<<endl;
        }
        //i1->sign=s1;i2->sign=s2;
   }
   //i1->sign=s1;i2->sign=s2;
   ////cout<<"i1:"<<i1->sign<<" "<<"i2:"<<i2->sign<<endl;
   //result->sign=((i1->sign)*(i2->sign));
   return result;
}
// UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1,UnlimitedInt* i2)
// {
//     ////cout<<"sign is:"<<(i1->sign)*(i2->sign)<<endl;
//     UnlimitedInt* temp=new UnlimitedInt();
//     temp->size=i1->size;temp->unlimited_int=i1->unlimited_int;temp->capacity=i1->capacity;
//     UnlimitedInt* one=new UnlimitedInt();
//     one->size=1;one->capacity=1;one->unlimited_int[0]=1;
//     UnlimitedInt* quo=new UnlimitedInt();
//     int s1=i1->sign;int s2=i2->sign;i1->sign=1;i2->sign=1;temp->sign=1;
//     ////cout<<"sign is:"<<(i1->sign)*(i2->sign)<<endl;
//     // quo=div(i1,i2);
//     // result=mul(i2,quo);
//     // result=sub(i1,result);
//     // return result;
//    if(bigger(temp,i2)==temp)
//    {
//         while(bigger(temp,i2)==temp)
//         {
//             temp=sub(temp,i2);
//             quo=add(quo,one);
//             ////cout<<"stuck in while"<<endl;
//         }
//         ////cout<<"doing"<<endl;
//         ////cout<<"quo sign"<<quo->sign<<endl;
//         i1->sign=s1;i2->sign=s2;
//         quo=mul(quo,i2);
//         quo=sub(i1,quo);
//         ////cout<<"quo sign"<<quo->sign<<endl;
//         if(s1*s2==-1)
//         {
//             if(temp->unlimited_int[(temp->size)-1]!=0)
//             {
//                 quo->sign=-1;
//             } 
//             else
//             {
//                 quo->size=1;quo->unlimited_int[(temp->size)-1]=0;quo->sign=0;
//             }
//         }
//         else
//         {
//             if(temp->unlimited_int[(temp->size)-1]!=0)
//             {
//                 quo->sign=1;
//             } 
//             else
//             {
//                 quo->size=1;quo->unlimited_int[(temp->size)-1]=0;quo->sign=0;
//             }
//         }
//         return quo;
//    }
//    else
//    {
//         return i1;
//    }
// }
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1,UnlimitedInt* i2)
{
    UnlimitedInt* result=new UnlimitedInt();
    int s1=i1->sign;int s2=i2->sign;i1->sign=1;i2->sign=1;
    //cout<<"seg fault for div"<<endl;
    result=div(i1,i2);
    //cout<<"not seg fault for div"<<endl;
    result=mul(result,i2);
    //cout<<"not seg fault for mul"<<endl;
    result=sub(i1,result);
    //cout<<"not seg fault for sub"<<endl;
    if(s1*s2==-1)
    {
        result->sign=-1;
        return result;
    }
    i1->sign=s1;i2->sign=s2;
    result->sign=1;
    return result;
}
string UnlimitedInt::to_string()
{
    string s="";
    if(sign==-1)
    {
        s=s+"-";
    }
    for(int i=size-1;i>=0;i--)
    {
        s=s+std::to_string(unlimited_int[i]);
    }
    return s;
}