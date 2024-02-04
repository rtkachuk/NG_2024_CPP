#include <iostream>

using namespace std;

int main()
{
    int num = 0;
    cout << "Enter variable: ";
    cin >> num;
    cout << "You entered: " << num << endl;

    // && - and
    // || - or
    // == - same

    if (num > 6) {
        cout << "You entered more, than 6!";
    } else {
        cout << "You entered lower or same, as 6!";
    }

    cout << endl;

    for (int row = 0; row < num; row++ ) {
        int column = 0;
        while (column < row) {
            cout << "*";
            column++;
        }
        cout << endl;
    }
    cout << endl;

    int index = 0;

    do {
        cout << index << " ";
        index++;
    } while (index < num);

    return 0;
}

      1
     121
    12321
   123 321
    12321
     121
      1
