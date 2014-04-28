/*
ID: Chao Xiang
TASK: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char** argv)
{
    bool ready=false;
    
    // goes the logic
    string group;
    string comet;
    ifstream in("ride.in");
    ofstream out("ride.out");
    in>>comet;
    in>>group;
    
    int n=comet.length();
    long comet_code=1;
    int ch=0;
    for(int i=0;i<n;i++)
    {
        ch=(comet[i]-'A'+1);
        comet_code*=ch;
    }
    comet_code%=47;
    n=group.length();
    long group_code=1;
    for(int i=0;i<n;i++)
    {
        ch=(group[i]-'A'+1);
        group_code*=ch;
    }
    group_code%=47;
    if(group_code==comet_code)
    {
        ready=true;
    }
    if(ready)
    {
        out<<"GO"<<endl;
    }
    else
    {
        out<<"STAY"<<endl;
    }
    return 0;
}
