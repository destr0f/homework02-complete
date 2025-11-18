#include "../include/header.hpp"

string getTypeMarker()
{
    switch (listType)
    {
        case 1: return ">";
        case 2: return "<>";
        case 3: return ">0";
        case 4: return "<>0";
        default: return "?";
    }
}

int markerToType(const string& marker)
{
    if (marker == ">") return 1;
    if (marker == "<>") return 2;
    if (marker == ">0") return 3;
    if (marker == "<>0") return 4;
    return 0;
}

vector<int> parseElementsString(const string& s)
{
    vector<int> elems;
    string current;

    for (char ch : s)
    {
        if (ch == ',')
        {
            if (!current.empty())
            {
                elems.push_back(stoi(current));
                current.clear();
            }
        }
        else if (!isspace((unsigned char)ch))
        {
            current.push_back(ch);
        }
    }

    if (!current.empty())
    {
        elems.push_back(stoi(current));
    }

    return elems;
}

void writeToFile(const string& filename)
{
    if (!listExists || !headPtr || listSize == 0)
    {
        cout << "Error: list is empty.\n";
        return;
    }

    ofstream out(filename, ios::out | ios::trunc);
    if (!out) {cout << "Error: cannot open file for writing"; return;}

    // первая строка - тип
    out << getTypeMarker() << endl;

    Node* cur = headPtr;
    for (int i = 0; i < listSize; ++i)
    {
        out << cur->value;
        if (i+1 < listSize) out << ',';
        cur = cur->next;
    }
    out << endl;

    cout << "Success: list written to file." << endl;
}

void readFromFile(const string& filename)
{
    if (listExists && listSize > 0)
    {
        cout << "Error: list already exists in program.\n";
        return;
    }

    ifstream in(filename);
    if (!in) {cout << "Error: cannot open file for reading.\n"; return;}

    string marker;
    if (!(in >> marker)) {cout << "Error: file is empty or invalid.\n";return;}

    int type = markerToType(marker);
    if (type == 0){cout << "Error: unknown list type in file.\n";return;}

    string line;
    getline(in, line);
    if (!getline(in, line)) {cout << "Error: no elements line in file.\n";return;}

    vector<int> elems;
    try {elems = parseElementsString(line);} catch (...) {cout << "Error: invalid elements in file.\n";return;}

    initListFromVector(type, elems);
    cout << "Success: list read from file. Elements count: " << listSize << endl;
}

