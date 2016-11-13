#include<iostream>
#include<string>

using namespace std;

int main()
{
    string str = "hello";
    string *pStr = &str;
    string *ppStr = pStr;

    cout << "ppStr->size() is: " << ppStr->size() << "\n";

    return 0;
}