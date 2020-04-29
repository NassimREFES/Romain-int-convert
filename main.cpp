#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using std::string;
using std::exception;
using std::runtime_error;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::istream;
using std::ostream;
using std::ios_base;

void error(string s)
{
    throw runtime_error(s);
}

enum Digit{
        I=1,V=5,X=10,L=50,C=100,D=500,M=1000
    };

int int_v(char ch)
{
    if(ch=='I') return I;
    else if(ch=='V') return V;
    else if(ch=='X') return X;
    else if(ch=='L') return L;
    else if(ch=='C') return C;
    else if(ch=='D') return D;
    else if(ch=='M') return M;
    else error("no such number");
}

struct Roman_int{
    string roman_num;
    Roman_int(string s)
        : roman_num(s) { }
    int as_int();
};

int Roman_int::as_int()
{
    int current=0;
    int whole=0;
    int skip=0;
    for(int i=roman_num.size()-1 ; i>=0 ; --i){
        if(skip>0){
            --skip;
            continue;
        }

        current=int_v(roman_num[i]);
        if(i!=0 && int_v(roman_num.at(i-1))<current){
            current-=int_v(roman_num.at(i-1));
            ++skip;
            if(i-1!=0 && int_v(roman_num.at(i-2))==int_v(roman_num.at(i-1))){
                current-=int_v(roman_num.at(i-1));
                ++skip;
                if(i-2!=0 && int_v(roman_num.at(i-3))==int_v(roman_num.at(i-2))){
                    current-=int_v(roman_num.at(i-1));
                    ++skip;
                }
            }
        }
        whole+=current;
    }
    return whole;
}

bool is_roman(const string& s)
{
    int count1=0;
    int count2=0;
    for(int i=0 ; i<s.size() ; ++i){
        if(!(s[i]=='I' || s[i]=='V' || s[i]=='X' || s[i]=='L' || s[i]=='C' || s[i]=='D' || s[i]=='M')) return false;
        if(i!=0 && s[i]==s[i-1]) {
            ++count1;
            if(count1>count2) count2=count1;
        }
        else count1=0;
    }
    if(count2>3) return false;
    return true;
}

istream& operator>>(istream& in,Roman_int& r)
{
    string s;
    in >> s;
    if(!in) {
        in.clear(ios_base::failbit);
        return in;
    }
    if(!is_roman(s)) error("Not a roman integer!");
    r=Roman_int(s);
    return in;
}

ostream& operator<<(ostream& out,const Roman_int& r)
{
    return out << r.roman_num;
}

int main()
try{
    Roman_int r("");
    while(cin >> r)
        cout << r.roman_num << '\t' << r.as_int() << endl;

    return 0;
}
catch(exception& err){
    cerr << "Error : " << err.what() << endl;
    return 1;
}
catch(...){
    cerr << "Unknown error!" << endl;
    return 2;
}
