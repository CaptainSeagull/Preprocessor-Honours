#include <fstream> // include filestream support
#include <string>
#include <iostream>

using namespace std;

int main()
{
    ofstream writer("poem.txt");

    string poem = "\n\tI never saw a man who looked";
    poem.append("\n\tWith such a wistful eye");
    poem.append("\n\tUpon that little tend of blue");
    poem.append("\n\tWhich prisoners call the sky");
    // add more statements here

    if(!writer)
    {
        cout << "Error opening file for output" << endl;
        return -1; // signal error then exit program
    }
    writer << poem << endl; // write output
    writer.close(); // close filestream

    return 0;
}