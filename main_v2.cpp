#include <iostream>
#include <string>
#include <stdexcept>

const std::string multiple_ten = "IXCM";
const std::string multiple_five = "VLD";

inline short char_to_int(char ch) { return ch - 48; }

inline std::string dup_char(char ch, int a)
{
    std::string str;
    for(int i=0 ; i<a ; ++i) str += ch;
    return str;
}

std::string convert_unit(short number, short power)
{
    if(number==9) return std::string(1,multiple_ten[power]) + std::string(1,multiple_ten[power + 1]);
    else if(number<4 || number==4 && power==3) return dup_char(multiple_ten[power],number);

    else if(number==4) return std::string(1,multiple_ten[power]) + std::string(1,multiple_five[power]);

    else return multiple_five[power] + dup_char(multiple_ten[power],(number - 5));
}

std::string convert_int(const std::string& num)
{
    std::string s;
    short size = num.length() - 1;
    for(short i=0 ; i<=size ; ++i)
        s += convert_unit(char_to_int(num[i]),size - i);
    return s;
}

int main()
try{
    std::cout << convert_int("2013");

    return 0;
}catch(std::exception& err){
    std::cerr << "Error : " << err.what() << " !" << std::endl;
    return 1;
}
