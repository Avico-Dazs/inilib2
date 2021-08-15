#include <iostream>
#include <vector>
#include "ini/ini.hpp"
using namespace std;

int main()
{
    ini i("test.ini");
    printf("hello!!¥n");
    string value = i["section"]["key"];
    printf("value:%S¥n",value);
}