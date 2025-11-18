#include "include/header.hpp"

// Разбор параметров из CMD
// Нужны корректные: -t <type>, -c <count>, -e <elems1,elems2,...>
bool parseCommandLine(int argc, char* argv[], int& outType, int& outCount, vector<int>& outElems)
{
    if (argc != 7) {
        cout << "Error: unexpected parameters. Example: -t <type>, -c <count>, -e <elem1,elem2,...>" << endl;
        return false;
    }

    int type = -1;
    int count = -1;
    string elementsStr;

    for (int i = 1; i < argc; i += 2)
    {
        string key = argv[i];
        string value = argv[i + 1];

        if (key == "-t") {type = stoi(value);}
        else if (key == "-c") {count = stoi(value);}
        else if (key == "-e") {elementsStr = value;}
        else {cout << "Error: unknown parameter: " << key << endl; return false;}
    }

    if (type < 1 || type > 4) { cout << "Error: invalid type. List type must be 1..4" << endl; return false;}
    if (count < 0) {cout << "Error: invalid count. Count must be non-negative" << endl; return false;}

    vector<int> elems;
    try {elems = parseElementsString(elementsStr);} catch (...) {cout << "Error: invalid list elements in -e." << endl; return false;}

    if ((int)elems.size() != count) {cout << "Error: count in -c (" <<count<< ") != number of elements in -e ("<<elems.size()<< ")." << endl; return false;}

    outType = type;
    outCount = count;
    outElems = elems;
    return true;
}

// main-start
int main(int argc, char* argv[])
{
    int type;
    int count;
    vector<int> elems;

    // 1) работа с параметрами
    if (!parseCommandLine(argc, argv, type, count, elems)) {return 1;}

    // 2) создаём стартовый список
    initListFromVector(type,elems);

    cout << "Linked list program" << endl;
    cout << "List created. Type = " <<type<< ", elements = " <<listSize<< endl;

    // 3) меню
    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Print list" << endl;
        cout << "2. Add element to the end" << endl;
        cout << "3. Find element" << endl;
        cout << "4. Delete FIRST occurrence" << endl;
        cout << "5. Delete ALL occurrences" << endl;
        cout << "6. Delete whole list" << endl;
        cout << "7. Write list to file" << endl;
        cout << "8. Read list from file (only if no list)" << endl;
        cout << "0. Exit" << endl;
        cout<<endl;
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) {cout << "Input error. Exiiting" << endl; break;}

        switch (choice)
        {
            case 1: {cout<<endl;printList();cout<<endl; break;}
            case 2: {cout<<endl;int val; cout << "Enter element to add: "; cin >> val; appendElement(val);cout<<endl; break;}
            case 3: {cout<<endl;findElement();cout<<endl; break;}
            case 4: {cout<<endl;deleteFirstOccurrence();cout<<endl; break;}
            case 5: {cout<<endl;deleteAllOccurrences();cout<<endl; break;}
            case 6: {cout<<endl;deleteList();cout<<endl; break;}
            case 7: {string filename; cout<<endl; cout << "Enter filename to write: "; cin >> filename; writeToFile(filename);cout<<endl; break;}
            case 8: {string filename; cout<<endl; cout << "Enter filename to read: "; cin >> filename; readFromFile(filename);cout<<endl; break;}
            case 0: {cout<<"Goodbye!\n";return 0;}
            default: {cout << "Error: unknown menu choice." << endl; break;}
        }
    }

    return 0;
}