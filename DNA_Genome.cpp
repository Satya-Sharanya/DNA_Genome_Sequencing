#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int freq;  //if Node is external Node contains no. of times the string is repeated till now
    Node *children[26];  //stores 26 children ie)from A to Z
    bool externalNode; //true if Node is an external Node
    vector <int> indexes;  //if mode is external Node contains at what indexes of dna is this string present
    string mutatedstring;  //if Node is external Node stores mutated string
};
vector <int> diseaseindex; // final vector which we should output
Node* newNode()   //function for creating a new Node 
{
    Node * temp=new Node;
    for(int i=0;i<26;i++)
    {
        temp->children[i]=NULL;
    }
    temp->externalNode=false;
    temp->freq=0;
    return temp;
}

void Insert(string &s,Node * Root,int i)  //consruction of a trie for strings in dna
{
    Node* temp=Root;
    for(int i=0;i<s.size();i++)
    {
        int level=(int)(s[i])-65;
        if(temp->children[level] == NULL)
        {
            temp->children[level]=newNode();
        }
        temp=temp->children[level];
    }
    temp->externalNode=true;
    (temp->indexes).push_back(i);
    if(temp->externalNode==true)
    {
        temp->freq=(temp->freq)+1;
    }
}
    
bool Search(string &s,Node * root)  //Searching for a strng in dna
{
    Node * temproot=root;
    for(int i=0;i<s.size();i++)
    {
        int level=(int)(s[i])-65;
        if(temproot->children[level]==NULL)
        {
            return false;
        }
        temproot=temproot->children[level];
    }
    return true;
}

int Frequency(string &s,Node * Root)  //gives the value of no. of times given string is present in dna
{
    Node* temp=Root;
    if(Search(s,temp)==true)
    {
        for(int i=0;i<s.size();i++)
        {
            int level=(int)(s[i])-65;
            temp=temp->children[level];    
        }
        return (temp->freq);
    }
    return 0;
}

void GetVector(string s,Node* root)  //stores the indices into diseaseindex vector
{
    Node *temp=root;
    for(int i=0;i<s.size();i++)
    {
        int level=(int)(s[i])-65;
        if(temp->children[level]!=NULL)
        {
            temp=temp->children[level];    
        }
    }
    int size=(temp->indexes).size();
    for(int i=0;i<size;i++)
    {
        diseaseindex.push_back(temp->indexes[i]);
    }
}

void Mut_Insert(string beforemut,string aftermut,Node * root)  //construction of a trie for mutations 
{
    Node* temp=root;
    for(int i=0;i<beforemut.size();i++)
    {
        int level=(int)(beforemut[i])-65;
        if(temp->children[level] == NULL)
        {
            temp->children[level]=newNode();
        }
        temp=temp->children[level];
    }
    temp->externalNode=true;
    if(temp->externalNode==true)
    {
        temp->mutatedstring=aftermut;
    }
}

void Mut_Search(string &s,Node * root)  //Searching of a substring in mutations trie and modifying diseases strings 
{
    Node * temproot=root;
    for(int i=0;i<s.size();i++)
    {
        int level=(int)(s[i])-65;
        if(temproot->children[level]==NULL)
        {
            break;
        }
        temproot=temproot->children[level];
    }
    if(temproot->externalNode==true)
    {
        (temproot->mutatedstring).append(s,(temproot->mutatedstring).size(),s.size()-(temproot->mutatedstring).size());
        s=temproot->mutatedstring;
    }
}

void GetMut_Vector(string s,Node * root) ////stores the indices into diseaseindex vector after mutations
{
    Node *temp=root;
    for(int i=0;i<s.size();i++)
    {
        int level=(int)(s[i])-65;
        if(temp->children[level]!=NULL)
        {
            temp=temp->children[level];    
        }
    }
    int size=(temp->indexes).size();
    for(int i=0;i<size;i++)
    {
        diseaseindex.push_back(temp->indexes[i]);
    }    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int k,n,p,IsMutated;
    cin>>k>>n>>p>>IsMutated;
    Node *root=newNode();
    string dna[n];
    for(int i=0;i<n;i++)
    {
        cin>>dna[i];
        Insert(dna[i],root,i);
    }
    string disease[p];
    int f[p];
    for(int i=0;i<p;i++)
    {
        cin>>disease[i]>>f[i];
        GetVector(disease[i],root);
    }
    if(diseaseindex.size()!=0)
    {
        sort(diseaseindex.begin(),diseaseindex.end());
        for(int i=0;i<diseaseindex.size();i++)
        {   
            if(i>=1)
            {
                if(diseaseindex[i]!=diseaseindex[i-1])
                {
                    cout<<diseaseindex[i]<<" ";
                }
            }
            else
            {
                 cout<<diseaseindex[i]<<" ";
            }
        }    
    }
    else
    {
        cout<<"No match found";
    }
    cout<<endl;
    int q=0;//variable to know where to break below loop which detects if dna is diseased or not before mutation
    for(int i=0;i<p;i++)
    {
        if(Frequency(disease[i],root)<f[i])
        {
            q++;
            cout<<"No"<<endl;
            break;
        }
    }
    if(q==0)
    {
        cout<<"Yes"<<endl;
    }
    diseaseindex.clear();
    if(IsMutated==1)
    {
        int m;
        cin>>m;
        string beforemut[m];
        string aftermut[m];
        Node * mut_root=newNode();
        for(int i=0;i<m;i++)
        {
            cin>>beforemut[i]>>aftermut[i];
            Mut_Insert(beforemut[i],aftermut[i],mut_root);
        }
        for(int i=0;i<p;i++)
        {
            Mut_Search(disease[i],mut_root);
            //cout<<disease[i]<<endl;
            GetMut_Vector(disease[i],root);
        }
        if(diseaseindex.size()!=0)
        {
            sort(diseaseindex.begin(),diseaseindex.end());
            for(int i=0;i<diseaseindex.size();i++)
            {   
                if(i>=1)
                {
                    if(diseaseindex[i]!=diseaseindex[i-1])
                    {
                        cout<<diseaseindex[i]<<" ";
                    }
                }
                else
                {
                     cout<<diseaseindex[i]<<" ";
                }
            }    
        }
        else
        {
            cout<<"No match found";
        }
        cout<<endl;
        int q1=0;//variavble to know where to break below loop which detects if dna is diseased or not afer mutation
        for(int i=0;i<p;i++)
        {
            if(Frequency(disease[i],root)<f[i])
            {
                q1++;
                cout<<"No"<<endl;
                break;
            }
        }
        if(q1==0)
        {
            cout<<"Yes"<<endl;
        }
    }
    return 0;
}