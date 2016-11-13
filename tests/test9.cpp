// Function Template Example

#include <iostream>

using namespace std;

// This is a Function Template

template <class X> 
void SwapArguments(X &a, X &b)
{
    X temp;

    temp = a;
    a = b;
    b = temp;
    cout << "Inside template SwapArguments.\n";
}

// This overrides the generic version of SwapArguments() for ints.
template<> void SwapArguments<int>(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
    cout << "Inside SwapArguments int specialisation.\n";
}

int main()
{
    int i = 10, j = 20;
    double x = 10.1, y = 23.3;
    char a = 'x', b = 'y';

    cout << "Original i, j: " << i << ',' << ' ' << j << '\n';
    cout << "Original x, y: " << x << ',' << ' ' << y << '\n';
    cout << "Original a, b: " << a << ',' << ' ' << b << '\n';
    cout << '\n';

    SwapArguments(i, j); // calls explicitly overloaded SwapArguments
    SwapArguments(x, y); // calls generic SwapArguaments
    SwapArguments(a, b); // calls generic SwapArguments

    cout << "Swapped i, j: " << i << ',' << ' ' << j << '\n';
    cout << "Swapped x, y: " << x << ',' << ' ' << y << '\n';
    cout << "Swapped a, b: " << a << ',' << ' ' << b << '\n';

    return 0;
}