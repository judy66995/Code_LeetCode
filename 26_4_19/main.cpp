#include <iostream>
#include <string>//引入封装好的字符串类
#include <vector>
using namespace std;

string frequencySort(string s) ;
int main()
{
    string s="tree";
    string res=frequencySort(s);
    cout<<res<<endl;
    return 0;
}

string frequencySort(string s) 
{
    //1.统计频率
    int count[256]={0};
    for(int i=0;i<s.size();i++)
    {
        char c=s[i];
        count[c]++;//这里c是char，但C++会自动把char转成int（ASCII值）
     }

    //2.按频率入桶,一个桶就是一个字符串，整个bucket=字符串数组（5个字符串）
    //开辟一个动态字符串数组,长度（桶的个数）为s.size()+1,桶的索引：0~s.size()
    vector<string> bucket(s.size()+1);
    for(int i=0;i<256;i++)
    {
        if(count[i]!=0)
        {
            bucket[count[i]] += (char)i;//(char)i是C++中的强制类型转换，目的把ASC码值转换为对应字符
        }
    }

        //3.从高到低拼接结果
    string res;
    for(int i=s.size();i>=0;i--)
    {
        for(char ch : bucket[i])//这叫范围for循环,意思是：把 bucket [i] 里的每一个字符，一个一个拿出来，叫 ch
        {
            res.append(i,ch);//把字符ch，连续拼接i次到结果res里
        }
    }
    return res;
}