#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

vector<char>ara,per,tex,rad,smooth,target;

vector<char>tara,tper,ttex,trad,tsmooth,ttarget;

int ca_r=0,cb_r=0,cc_r=0,cd_r=0;
int ca_t=0,cb_t=0,cc_t=0,cd_t=0;
int ca_p=0,cb_p=0,cc_p=0,cd_p=0;
int ca_a=0,cb_a=0,cc_a=0,cd_a=0;
int ca_s=0,cb_s=0,cc_s=0,cd_s=0;

class measure
{
public:
    string area;
    string perimeter;
    string texture;
    string radius;
    string smoothness;
    string val;

    measure(string a,string p,string t,string r,string s,string v)
    {
        area=a;
        perimeter=p;
        texture=t;
        radius=r;
        smoothness=s;
        val=v;
    }

    void disp()
    {
        cout<<radius<<" "<<texture<<" "<<perimeter<<" "<<area<<" "<<smoothness<<endl;
    }
};

float entropy(vector<char>arr,vector<char>target,char attribute)
{
    int pos=0,neg=0;
    int l=arr.size();

    for(int i=0;i<l;i++)
    {
        if(arr[i]==attribute)
        {
            if(target[i]=='0')
                pos++;

            else
                neg++;
        }

    }

    float p=(float(pos))/(pos+neg);
    float n=(float(neg))/(pos+neg);

    float denp=0;

    if(p)
    denp=log10(p)/log10(2);

    float denn=0;

    if(n)
    denn=log10(n)/log10(2);


    float ent=(p*denp)+(n*denn);

    if(ent==0)
        return 0;

    return -1*(ent);
}

float common_base_entropy(vector<char>target)
{
    int pos=0,neg=0;
    int l=target.size();
    for(int i=0;i<l;i++)
    {
        if(target[i]=='0')
            pos++;
        else
            neg++;
    }

    float p=(float(pos))/(pos+neg);
    float n=(float(neg))/(pos+neg);

    float denp=0;

    if(p)
    denp=log10(p)/log10(2);

    float denn=0;

    if(n)
    denn=log10(n)/log10(2);


    float ent=(p*denp)+(n*denn);

    if(ent==0)
        return 0;

    return -1*(ent);
}


float mean_entropy(map<char,float>m,int ca,int cb,int cc,int cd)
{
    int total = ca+cb+cc+cd;

    float ment = (m['a']*((float(ca))/total))+(m['b']*((float(cb))/total))+(m['c']*((float(cc))/total))+(m['d']*((float(cd))/total));

    return ment;

}


int count_attribute(vector<char>arr,char attribute)
{
    int cnt=0;
    vector<char> :: iterator itr=arr.begin();
    while(itr!=arr.end())
    {
        if((*itr) == attribute)
            cnt++;
        itr++;
    }
    return cnt;
}


float info_gain(vector<char>target , vector<char>arr)
{
    float cbe = common_base_entropy(target);

    map<char,float>m;
    m['a']=entropy(arr,target,'a');
    m['b']=entropy(arr,target,'b');
    m['c']=entropy(arr,target,'c');
    m['d']=entropy(arr,target,'d');

    int ca=count_attribute(arr,'a');
    int cb=count_attribute(arr,'b');
    int cc=count_attribute(arr,'c');
    int cd=count_attribute(arr,'d');

    float ment = mean_entropy(m,ca,cb,cc,cd);

    return (cbe-ment);

}

char predict(vector<char>arr,vector<char>target,char attr)
{
    int p=0,n=0;

    vector<char> :: iterator a = arr.begin();
    vector<char> :: iterator t = target.begin();

    while(a!=arr.end())
    {
        if(*a==attr)
        {
            if(*t=='0')
                p++;
            else
                n++;
        }

        a++;
        t++;
    }
    if(p>=n)
        return '0';

    return '1';
}

void construct(char grade[],map<char,float>info)
{
    cout<<"IN THE PROCESS... : \n";
    char act_attr;
    map<char,float> :: iterator it = info.begin();
    float maxinfo=it->second;act_attr=it->first;
    while(it!=info.end())
    {

        if((it->second)>maxinfo)
        {

            maxinfo = it->second;
            act_attr=it->first;
        }

        it++;
    }

    if(act_attr=='r')
    {
        cout<<"Active Attribute : Radius\n\n"<<endl;
        info.erase('r');
        if(grade[0]=='a')
        {
            if((entropy(trad,ttarget,'a'))==0)
            {
                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=trad.end())
                {
                    if(*r=='a')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(trad,ttarget,'a'))!=0) && info.empty())
            {
                        char ch=predict(trad,ttarget,'a');;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step\n"<<endl;

                while(r!=trad.end())
                {

                    if((*r)=='a')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step\n"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }


        }
        if(grade[0]=='b')
        {
            if((entropy(trad,ttarget,'b'))==0)
            {
                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=trad.end())
                {
                    if(*r=='b')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(trad,ttarget,'b'))!=0) && info.empty())
            {
                        char ch=predict(trad,ttarget,'b');;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(r!=trad.end())
                {

                    if((*r)=='b')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }


        }
        if(grade[0]=='c')
        {
            if((entropy(trad,ttarget,'c'))==0)
            {
                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=trad.end())
                {
                    if(*r=='c')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(trad,ttarget,'c'))!=0) && info.empty())
            {
                        char ch=predict(trad,ttarget,'c');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(r!=trad.end())
                {

                    if((*r)=='c')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }
        if(grade[0]=='d')
        {
            if((entropy(trad,ttarget,'d'))==0)
            {
                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=trad.end())
                {
                    if(*r=='d')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(trad,ttarget,'d'))!=0) && info.empty())
            {
                        char ch=predict(trad,ttarget,'d');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(r!=trad.end())
                {

                    if((*r)=='d')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

    }

    if(act_attr=='t')
    {
        cout<<"Active Attribute : Texture\n"<<endl;
        info.erase('t');
        if(grade[1]=='a')
        {
            if((entropy(ttex,ttarget,'a'))==0)
            {
                vector<char> :: iterator r=ttex.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=ttex.end())
                {
                    if(*r=='a')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(ttex,ttarget,'a'))!=0) && info.empty())
            {
                        char ch=predict(ttex,ttarget,'a');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;


            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(t!=ttex.end())
                {

                    if((*t)=='a')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[1]=='b')
        {
            if((entropy(ttex,ttarget,'b'))==0)
            {
                vector<char> :: iterator r=ttex.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=ttex.end())
                {
                    if(*r=='b')
                    {
                       char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(ttex,ttarget,'b'))!=0) && info.empty())
            {
                        char ch=predict(ttex,ttarget,'b');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(t!=ttex.end())
                {

                    if((*t)=='b')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[1]=='c')
        {
            if((entropy(ttex,ttarget,'c'))==0)
            {
                vector<char> :: iterator r=ttex.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=ttex.end())
                {
                    if(*r=='c')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(ttex,ttarget,'c'))!=0) && info.empty())
            {
                        char ch=predict(ttex,ttarget,'c');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(t!=ttex.end())
                {

                    if((*t)=='c')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[1]=='d')
        {
            if((entropy(ttex,ttarget,'d'))==0)
            {
                vector<char> :: iterator r=ttex.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=ttex.end())
                {
                    if(*r=='d')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(ttex,ttarget,'d'))!=0) && info.empty())
            {
                        char ch=predict(ttex,ttarget,'d');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(t!=ttex.end())
                {

                    if((*t)=='d')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

    }

    if(act_attr=='p')
    {
        cout<<"Active Attribute : Perimeter\n"<<endl;
        info.erase('p');

        if(grade[2]=='a')
        {

            if((entropy(tper,ttarget,'a'))==0)
            {

                vector<char> :: iterator r=tper.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tper.end())
                {
                    if(*r=='a')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tper,ttarget,'a'))!=0) && info.empty())
            {
                        char ch=predict(tper,ttarget,'a');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(p!=tper.end())
                {


                    if((*p)=='a')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[2]=='b')
        {
            if((entropy(tper,ttarget,'b'))==0)
            {
                vector<char> :: iterator r=tper.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tper.end())
                {
                    if(*r=='b')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tper,ttarget,'b'))!=0) && info.empty())
            {
                char ch=predict(tper,ttarget,'b');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(p!=tper.end())

                    {

                    if((*p)=='b')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[2]=='c')
        {
            if((entropy(tper,ttarget,'c'))==0)
            {
                vector<char> :: iterator r=tper.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tper.end())
                {
                    if(*r=='c')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tper,ttarget,'c'))!=0) && info.empty())
            {
                char ch=predict(tper,ttarget,'c');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(p!=tper.end())
                {

                    if((*p)=='c')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[2]=='d')
        {

            if((entropy(tper,ttarget,'d'))==0)
            {

                vector<char> :: iterator r=tper.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tper.end())
                {
                    if(*r=='d')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tper,ttarget,'d'))!=0) && info.empty())
            {
                char ch=predict(tper,ttarget,'d');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(p!=tper.end())

                    {


                    if((*p)=='d')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

    }

    if(act_attr=='a')
    {
        cout<<"Active Attribute : Area\n"<<endl;
        info.erase('a');
        if(grade[3]=='a')
        {
            if((entropy(tara,ttarget,'a'))==0)
            {
                vector<char> :: iterator r=tara.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tara.end())
                {
                    if(*r=='a')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tara,ttarget,'a'))!=0) && info.empty())
            {
                char ch=predict(tara,ttarget,'a');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {

                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(a!=tara.end())
                {

                    if((*t)=='a')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[3]=='b')
        {
            if((entropy(tara,ttarget,'b'))==0)
            {
                vector<char> :: iterator r=tara.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tara.end())
                {
                    if(*r=='b')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tara,ttarget,'b'))!=0) && info.empty())
            {
                char ch=predict(tara,ttarget,'b');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(a!=tara.end())
                {

                    if((*t)=='b')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[3]=='c')
        {
            if((entropy(tara,ttarget,'c'))==0)
            {
                vector<char> :: iterator r=tara.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tara.end())
                {
                    if(*r=='c')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }

                    r++;t++;
                }
            }

            else if(((entropy(tara,ttarget,'c'))!=0) && info.empty())
            {
                char ch=predict(tara,ttarget,'c');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(a!=tara.end())
                {

                    if((*t)=='c')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[3]=='d')
        {
            if((entropy(tara,ttarget,'d'))==0)
            {
                vector<char> :: iterator r=tara.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tara.end())
                {
                    if(*r=='d')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tara,ttarget,'d'))!=0) && info.empty())
            {
                char ch=predict(tara,ttarget,'d');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(a!=tara.end())
                {

                    if((*t)=='d')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('s')!=info.end())
                    info['s']=info_gain(ttarget,tsmooth);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }
    }

    if(act_attr=='s')
    {
        cout<<"Active Attribute : Smoothness\n"<<endl;
        info.erase('s');

        if(grade[4]=='a')
        {
            if((entropy(tsmooth,ttarget,'a'))==0)
            {
                vector<char> :: iterator r=tsmooth.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tsmooth.end())
                {
                    if(*r=='a')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tsmooth,ttarget,'a'))!=0) && info.empty())
            {
                char ch=predict(tsmooth,ttarget,'a');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(s!=tsmooth.end())
                {

                    if((*s)=='a')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[4]=='b')
        {
            if((entropy(tsmooth,ttarget,'b'))==0)
            {
                vector<char> :: iterator r=tsmooth.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tsmooth.end())
                {
                    if(*r=='b')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tsmooth,ttarget,'b'))!=0) && info.empty())
            {
                char ch=predict(tsmooth,ttarget,'b');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;


            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(s!=tsmooth.end())
                {

                    if((*s)=='b')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[4]=='c')
        {
            if((entropy(tsmooth,ttarget,'c'))==0)
            {
                vector<char> :: iterator r=tsmooth.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tsmooth.end())
                {
                    if(*r=='c')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tsmooth,ttarget,'c'))!=0) && info.empty())
            {
                char ch=predict(tsmooth,ttarget,'c');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(s!=tsmooth.end())
                {

                    if((*s)=='c')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);

                cout<<"3 step\n"<<endl;
                construct(grade,info);
            }

        }

        if(grade[4]=='d')
        {
            if((entropy(tsmooth,ttarget,'d'))==0)
            {
                vector<char> :: iterator r=tsmooth.begin();
                vector<char> :: iterator t=ttarget.begin();

                while(r!=tsmooth.end())
                {
                    if(*r=='d')
                    {
                        char ch=*t;
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;
                    }
                    r++;t++;
                }
            }

            else if(((entropy(tsmooth,ttarget,'d'))!=0) && info.empty())
            {
                char ch=predict(tsmooth,ttarget,'d');
                        if(ch=='0')
                            cout<<"Type I Cancer Predicted.\n\n";
                        else
                            cout<<"Type II Cancer Predicted.\n\n";
                        return;

            }

            else
            {


                vector<char> :: iterator r=trad.begin();
                vector<char> :: iterator t=ttex.begin();
                vector<char> :: iterator p=tper.begin();
                vector<char> :: iterator a=tara.begin();
                vector<char> :: iterator s=tsmooth.begin();
                vector<char> :: iterator tr=ttarget.begin();

                vector<char> radt,text,pert,arat,smootht,targett;

                cout<<"1 step"<<endl;

                while(s!=tsmooth.end())
                {

                    if((*s)=='d')
                    {
                        radt.push_back(*r);
                        text.push_back(*t);
                        pert.push_back(*p);
                        arat.push_back(*a);
                        smootht.push_back(*s);
                        targett.push_back(*tr);
                    }
                    r++;t++;p++;a++;s++;tr++;
                }
                cout<<"2 step"<<endl;
                trad.swap(radt);
                ttex.swap(text);
                tper.swap(pert);
                tara.swap(arat);
                tsmooth.swap(smootht);
                ttarget.swap(targett);
                if(info.find('p')!=info.end())
                    info['p']=info_gain(ttarget,tper);
                if(info.find('r')!=info.end())
                    info['r']=info_gain(ttarget,trad);
                if(info.find('t')!=info.end())
                    info['t']=info_gain(ttarget,ttex);
                if(info.find('a')!=info.end())
                    info['a']=info_gain(ttarget,tara);

                cout<<"3 step\n"<<endl;
                construct(grade,info);            }

        }

    }


}


int main()
{

    float in_r,in_t,in_p,in_a,in_s;
    char gin_r,gin_t,gin_p,gin_a,gin_s;
    cout<<"\t\t\tWelcome to the MediState Breast Cancer Classifier & Predictor System\n\n";
    cout<<"Enter the following clinical measurements for accurate approximation of the Breast Cancer Classification :-\n\n";
    cout<<"1.Mean radius scale measured : ";
    cin>>in_r;
    cout<<"\n2.Mean texture scale measured : ";
    cin>>in_t;
    cout<<"\n3.Mean perimeter scale measured : ";
    cin>>in_p;
    cout<<"\n4.Mean area scale measured : ";
    cin>>in_a;
    cout<<"\n5.Mean smoothness scale measured : ";
    cin>>in_s;


    vector<measure>v;

    map<char,float>m;

    ifstream fin;
    string r,t,p,a,s,vs;
    fin.open("data.csv");

    double minr=INT_MAX,mint=INT_MAX,minp=INT_MAX,mina=INT_MAX,mins=INT_MAX;
    double maxr=0,maxt=0,maxp=0,maxa=0,maxs=0;
    double meanr,meant,meanp,meana,means;
    double sumr,sumt,sump,suma,sums;
    int cnt=0;

    while(!(fin.eof()))
    {
        double val=0.0;

        getline(fin,r,',');
        if(r=="7.76")
            break;
        val=atof(r.c_str());
        sumr+=val;
        if(val<minr)
            minr=val;
        if(val>maxr)
            maxr=val;

        getline(fin,t,',');
        val=atof(t.c_str());
        //val=atof(t);
        sumt+=val;
        if(val<mint)
            mint=val;
        if(val>maxt)
            maxt=val;

        getline(fin,p,',');
        val=atof(p.c_str());
        sump+=val;
        if(val<minp)
            minp=val;
        if(val>maxp)
            maxp=val;

        getline(fin,a,',');
        val=atof(a.c_str());
        suma+=val;
        if(val<mina)
            mina=val;
        if(val>maxa)
            maxa=val;

        getline(fin,s,',');
        val=atof(s.c_str());
        sums+=val;
        if(val<mins)
            mins=val;
        if(val>maxs)
            maxs=val;

        getline(fin,vs,'\n');
        //cout<<"hey : "<<vs[0]<<endl;
        target.push_back(vs[0]);

        measure obj(a,p,t,r,s,vs);
        v.push_back(obj);
        cnt++;

    }

    fin.close();

    cout<<"\n\nData Set Reading Completed !\n"<<endl;

    float benr[5],bent[5],benp[5],bena[5],bens[5];

    benr[0]=minr;benr[4]=maxr;benr[2]=(sumr/cnt);benr[1]=(benr[0]+benr[2])/2;benr[3]=(benr[2]+benr[4])/2;
    bent[0]=mint;bent[4]=maxt;bent[2]=(sumt/cnt);bent[1]=(bent[0]+bent[2])/2;bent[3]=(bent[2]+bent[4])/2;
    benp[0]=minp;benp[4]=maxp;benp[2]=(sump/cnt);benp[1]=(benp[0]+benp[2])/2;benp[3]=(benp[2]+benp[4])/2;
    bena[0]=mina;bena[4]=maxa;bena[2]=(suma/cnt);bena[1]=(bena[0]+bena[2])/2;bena[3]=(bena[2]+bena[4])/2;
    bens[0]=mins;bens[4]=maxs;bens[2]=(sums/cnt);bens[1]=(bens[0]+bens[2])/2;bens[3]=(bens[2]+bens[4])/2;

    cout<<"Benchmarking of data set into grades completed !\n"<<endl;
    //Grading the inputs

    if(in_r>=benr[0]&&in_r<benr[1])
        gin_r='a';
    else if(in_r>=benr[1]&&in_r<benr[2])
        gin_r='b';
    else if(in_r>=benr[2]&&in_r<benr[3])
        gin_r='c';
    else
        gin_r='d';

    if(in_t>=bent[0]&&in_t<bent[1])
        gin_t='a';
    else if(in_t>=bent[1]&&in_t<bent[2])
        gin_t='b';
    else if(in_t>=bent[2]&&in_t<bent[3])
        gin_t='c';
    else
        gin_t='d';

    if(in_p>=benp[0]&&in_p<benp[1])
        gin_p='a';
    else if(in_p>=benp[1]&&in_p<benp[2])
        gin_p='b';
    else if(in_p>=benp[2]&&in_p<benp[3])
        gin_p='c';
    else
        gin_p='d';

    if(in_a>=bena[0]&&in_a<bena[1])
        gin_a='a';
    else if(in_a>=bena[1]&&in_a<bena[2])
        gin_a='b';
    else if(in_a>=bena[2]&&in_a<bena[3])
        gin_a='c';
    else
        gin_a='d';

    if(in_s>=bens[0]&&in_s<bens[1])
        gin_s='a';
    else if(in_s>=bens[1]&&in_s<bens[2])
        gin_s='b';
    else if(in_s>=bens[2]&&in_s<bens[3])
        gin_s='c';
    else
        gin_s='d';

    char grade[6]={gin_r,gin_t,gin_p,gin_a,gin_s};

    cout<<"Grading of input neasurements completed !\n\n"<<endl;

    cout<<"Your graded inputs are as follows :-\n";

    for(int i=0;i<5;i++)
        cout<<grade[i]<<" ";

    cout<<endl<<endl;


    vector<measure> :: iterator it=v.begin();

    while(it!=v.end())
    {
        double val=0.0;
        string check=(*it).radius;
        val=atof(check.c_str());
        if(val>=benr[0]&&val<benr[1])
            {rad.push_back('a');ca_r++;}
        else if(val>=benr[1]&&val<benr[2])
            {rad.push_back('b');cb_r++;}
        else if(val>=benr[2]&&val<benr[3])
            {rad.push_back('c');cc_r++;}
        else
            {rad.push_back('d');cd_r++;}

        it++;
    }

    it=v.begin();


    while(it!=v.end())
    {
        double val=0.0;
        string check=(*it).texture;
        val=atof(check.c_str());
        if(val>=bent[0]&&val<bent[1])
            {tex.push_back('a');ca_t++;}
        else if(val>=bent[1]&&val<bent[2])
            {tex.push_back('b');cb_t++;}
        else if(val>=bent[2]&&val<bent[3])
            {tex.push_back('c');cc_t++;}
        else
            {tex.push_back('d');cd_t++;}
        it++;
    }

    it=v.begin();


    while(it!=v.end())
    {
        double val=0.0;
        string check=(*it).perimeter;
        val=atof(check.c_str());
        if(val>=benp[0]&&val<benp[1])
            {per.push_back('a');ca_p++;}
        else if(val>=benp[1]&&val<benp[2])
            {per.push_back('b');cb_p++;}
        else if(val>=benp[2]&&val<benp[3])
            {per.push_back('c');cc_p++;}
        else
            {per.push_back('d');cd_p++;}
        it++;
    }

    it=v.begin();

    while(it!=v.end())
    {
        double val=0.0;
        string check=(*it).area;
        val=atof(check.c_str());
        if(val>=bena[0]&&val<bena[1])
            {ara.push_back('a');ca_a++;}
        else if(val>=bena[1]&&val<bena[2])
            {ara.push_back('b');cb_a++;}
        else if(val>=bena[2]&&val<bena[3])
            {ara.push_back('c');cc_a++;}
        else
            {ara.push_back('d');cd_a++;}
        it++;
    }

    it=v.begin();

    while(it!=v.end())
    {
        double val=0.0;
        string check=(*it).smoothness;
        val=atof(check.c_str());
        if(val>=bens[0]&&val<bens[1])
            {smooth.push_back('a');ca_s++;}
        else if(val>=bens[1]&&val<bens[2])
            {smooth.push_back('b');cb_s++;}
        else if(val>=bens[2]&&val<bens[3])
            {smooth.push_back('c');cc_s++;}
        else
            {smooth.push_back('d');cd_s++;}
        it++;
    }


    vector<char> :: iterator itrtar=target.begin();
    vector<char> :: iterator itrt=tex.begin();
    vector<char> :: iterator itrp=per.begin();
    vector<char> :: iterator itra=ara.begin();
    vector<char> :: iterator itrs=smooth.begin();
    vector<char> :: iterator itrr=rad.begin();
    while(itrr!=rad.end())
    {
        trad.push_back(*itrr);
        ttex.push_back(*itrt);
        tper.push_back(*itrp);
        tara.push_back(*itra);
        tsmooth.push_back(*itrs);
        ttarget.push_back(*itrtar);
        itrr++;itrt++;itrp++;itra++;itrs++;itrtar++;
    }

    map<char,float>finfo;
    finfo['r']=info_gain(target,rad);
    finfo['t']=info_gain(target,tex);
    finfo['p']=info_gain(target,per);
    finfo['a']=info_gain(target,ara);
    finfo['s']=info_gain(target,smooth);

    cout<<"Initiation phase Information Gain as follows -:\n";

    cout<<finfo['r']<<" "<<finfo['t']<<" "<<finfo['p']<<" "<<finfo['a']<<" "<<finfo['s']<<endl;

    //cout<<"Entropy:"<<entropy(tper,ttarget,'b');


    cout<<"\nFinal classification Process :\n\n ";

    construct(grade,finfo);

    cout<<"\n\nThank You for using our software !!\n";




    /*vector<char> :: iterator itrtar1=ttarget.begin();
    vector<char> :: iterator itrt1=ttex.begin();
    vector<char> :: iterator itrp1=tper.begin();
    vector<char> :: iterator itra1=tara.begin();
    vector<char> :: iterator itrs1=tsmooth.begin();
    vector<char> :: iterator itrr1=trad.begin();
    while(itrr1!=trad.end())
    {
        cout<<*itrr1<<" "<<*itrt1<<" "<<*itrp1<<" "<<*itra1<<" "<<*itrs1<<" "<<*itrtar1<<endl;
        itrr1++;itrt1++;itrp1++;itra1++;itrs1++;itrtar1++;
    }*/



return 0;
}
