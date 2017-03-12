#include"bigint.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<cctype>
using namespace std;
using namespace Dodecahedron;
struct ReturnValue{
    bool nil;
    Bigint val;
    explicit ReturnValue(bool nil=true):
        nil(nil){}
    explicit ReturnValue(Bigint const &val):
        nil(false),val(val){}
    explicit ReturnValue(int val):
        nil(false),val(val){}
    operator bool(){
        return !nil;
    }
};
typedef ReturnValue (*func_t)(vector<ReturnValue> const&);
map<string,func_t> table;
void skip_space(){
    int ch;
    while(isspace(ch=cin.get()));
    cin.unget();
}
ReturnValue awd(){
    skip_space();
    if(!cin) return ReturnValue();
    char ch;
    cin.get(ch);
    if(ch==')') return ReturnValue();
    if(ch!='('){
        cin.unget();
        Bigint x;
        cin>>x;
        return ReturnValue(x);
    }
    string op;
    cin>>op;
    vector<ReturnValue> args;
    ReturnValue t;
    while((t=awd()))
        args.push_back(t);
    return table[op](args);
}
void regFunc();
int main(){
    regFunc();
    do{awd();}while(cin);
    return 0;
}

#define func(name) ReturnValue name(vector<ReturnValue> const &args)
func(pr){
    for(vector<ReturnValue>::const_iterator it(args.begin());it!=args.end();++it){
        cout<<it->val;
        if(it!=args.end()-1)
            cout.put(' ');
        else
            cout.put('\n');
    }
    return ReturnValue(0);
}
func(pl){
    Bigint ans;
    for(vector<ReturnValue>::const_iterator it(args.begin());it!=args.end();++it)
        ans+=it->val;
    return ReturnValue(ans);
}
func(sb){
    Bigint ans=args.front().val;
    for(vector<ReturnValue>::const_iterator it(args.begin()+1);it<args.end();++it)
        ans-=it->val;
    return ReturnValue(ans);
}
func(ml){
    Bigint ans=1;
    for(vector<ReturnValue>::const_iterator it(args.begin());it!=args.end();++it)
        ans*=it->val;
    return ReturnValue(ans);
}
func(dv){
    Bigint ans=args.front().val;
    for(vector<ReturnValue>::const_iterator it(args.begin()+1);it<args.end();++it)
        ans/=it->val;
    return ReturnValue(ans);
}
func(md){
    Bigint ans=args.front().val;
    for(vector<ReturnValue>::const_iterator it(args.begin()+1);it<args.end();++it)
        ans%=it->val;
    return ReturnValue(ans);
}
func(ab){
    return ReturnValue(abs(args.front().val));
}
func(fc){
    return ReturnValue(factorial(args.front().val.to_builtin()));
}
func(pw){
    return ReturnValue(pow(args.front().val,args.back().val.to_builtin()));
}
void regFunc(){
    table["print"]=pr;
    table["+"]=pl;
    table["-"]=sb;
    table["*"]=ml;
    table["/"]=dv;
    table["%"]=md;
    table["abs"]=ab;
    table["fac"]=fc;
    table["pow"]=pw;
}
