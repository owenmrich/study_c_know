#include<vector>
#include<iostream>
#include<map>
using namespace std;
int main()
{
    
    map<char, string> lang = 
    {
        {'a',"this is a"},
        {'b',"this is b"},
        {'z',"aaa"},
    };
    pair<map<char,string>::iterator,bool> ret;
    ret = lang.insert(pair<char,string>('z',"ssss"));
    if (ret.second == false) {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }
    lang.insert({'w',"ok"});
    map<char, string>::iterator iter;    
    for(iter = lang.begin(); iter != lang.end(); iter++)  
         cout<<iter->first<<' '<<iter->second<<endl; 

    iter = lang.find('w');
    //for(iter = lang.find('w'); iter != lang.end(); iter++)  
         cout<<iter->first<<' '<<iter->second<<endl; 
    vector <int> vc;
    vector <vector<int> >obj(6);
    int a[5][3]= {0};
    printf("size is %d\n",vc.size());
    for(int i = 0;i < 3;i++)
    {
        vc.push_back(i);
    }
    printf("size is %d\n",vc.size());
    // 使用迭代器 iterator 访问值  
   vector<int>::iterator v = vc.begin();
   while( v != vc.end()) 
   {
       printf("%d\n",v);
        v++;
   }
    return 0;
}