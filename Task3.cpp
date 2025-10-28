#include <iostream>
using namespace std;
int main() {
    char str[200];
    cin.getline(str, 200);
    if (str[0] == '/' && str[1] == '/')
        cout << "Single line comment";
    else if (str[0] == '/' && str[1] == '*') {
        int i = 2;
        while (str[i] != '\0') {
            if (str[i] == '*' && str[i + 1] == '/') {
                cout << "Multi line comment";
                return 0;
            }
            i++;
        }
        cout << "Not a comment";
    } else
        cout << "Not a comment";
    return 0;
}
