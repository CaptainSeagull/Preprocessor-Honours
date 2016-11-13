#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    ofstream writer("poem.txt", ios::app);

    string info = "\n\tThe Ballad of Reading Gaol";
    info.append("\n\t\tOscar Wilde 1896");
    // add more statements here

    if(!writer)
    {
        cout << "Wrroe opening file for output" << endl;
        return -1; // signal error then exit
    }
    writer << info << endl; // append output
    writer.close(); // close filestream

    return 0;
}