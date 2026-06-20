#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    if (argc > 0)
    {
        for (int i = 0; i < argc; i++)
        {
            cout << "arg" << i << ": " << argv[i] << endl;
        }
    }

    auto str = std::string("Hello world");
    cout << str << endl;

    return 0;
}