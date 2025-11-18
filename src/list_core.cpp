#include "../include/header.hpp"

Node* headPtr = nullptr;
Node* tailPtr = nullptr;
int listType = 0;
int listSize = 0;
bool listExists = false;

Node::Node(int v) : value(v), next(nullptr), prev(nullptr) {}

bool isDoubly() {return listType == 2 || listType == 4;}
bool isCircular() {return listType == 3 || listType == 4;}

// Создать пустой список указанного типа
void initEmptyList(int type)
{
    headPtr = nullptr;
    tailPtr = nullptr;
    listType = type;
    listSize = 0;
    listExists = true;
}

// Создать список из вектора чисел
void initListFromVector(int type, const vector<int>& elems)
{
    initEmptyList(type);
    for (int v : elems)
    {
        appendElement(v);
    }
}

// Добавить элемент в конец
void appendElement(int value)
{
    if (!listExists)
    {
        cout << "Error: list does not exist yet.\n";
        return;
    }

    Node* node = new Node(value);
    if (!headPtr)
    {
        headPtr = tailPtr = node; // первый элемент
    }
    else
    {
        tailPtr->next = node; // цепляем в хвост
        if (isDoubly())
        {
            node->prev = tailPtr;
        }
        tailPtr = node;
    }

    listSize++;

    // если список кольцевой нужно замкнуть кольцо
    if (isCircular() && headPtr && tailPtr)
    {
        tailPtr->next = headPtr;
        if (isDoubly())
        {
            headPtr->prev = tailPtr;
        }
    }
}

// Вывод списка
void printList()
{
    if (!listExists || !headPtr || listSize == 0)
    {
        cout << "Error: list is empty.\n";
        return;
    }

    cout << "List: ";
    Node* cur = headPtr;
    for (int i = 0; i < listSize; ++i)
    {
        cout << cur->value;
        if (i != listSize - 1) cout << " ";
        cur = cur->next;
    }
    cout << endl;
}

// Поиск элемента - вывод всех позиций
void findElement()
{
    if (!listExists || !headPtr || listSize == 0)
    {
        cout << "Error: list is empty.\n";
        return;
    }

    int x;
    cout << "Enter element : ";
    cin >> x;

    vector<int> positions;
    Node* cur = headPtr;
    for (int i = 0; i < listSize; ++i)
    {
        if (cur->value == x)
        {
            positions.push_back(i+1);
        }
        cur = cur->next;
    }

    if (positions.empty())
    {
        cout << "Error: value not found.\n";
    }
    else
    {
        cout << "Found at positions: ";
        for (size_t i = 0; i < positions.size(); ++i)
        {
            cout << positions[i];
            if (i != positions.size() - 1) cout << " ";
        }
        cout << endl;
    }
}

// Удалить конкретный узел
static void removeNode(Node* node, Node* prev)
{
    if (!node) return;

    Node* next = node->next;

    if (node == headPtr)
    {
        headPtr = next;
    }
    if (node == tailPtr)
    {
        tailPtr = next;
    }

    if (prev)
    {
        prev->next = next;
    }
    if (isDoubly())
    {
        if (next) next->prev = prev;
    }

    listSize--;

    if (listSize == 0)
    {
        headPtr = tailPtr = nullptr;
    }
    else if (isCircular())
    {
        if (tailPtr) tailPtr->next = headPtr;
        if (isDoubly() && headPtr && tailPtr) {headPtr->prev = tailPtr;}
    }

    delete node;
}

// Удалить первое вхождение значения
void deleteFirstOccurrence()
{
    if (!listExists || !headPtr || listSize == 0)
    {
        cout << "Error: list is empty.\n";
        return;
    }

    int x;
    cout << "Enter value to delete (first occurrence): ";
    cin >> x;

    Node* cur = headPtr;
    Node* prev = nullptr;

    int ogSize = listSize;
    for (int i = 0; i < ogSize&&cur; ++i)
    {
        if (cur->value == x)
        {
            removeNode(cur, prev);
            cout << "Success: first occurrence deleted.\n";
            return;
        }
        prev = cur;
        cur = cur->next;
    }

    cout << "Error: value not found.\n";
}

// Удалить все вхождения значения
void deleteAllOccurrences()
{
    if (!listExists || !headPtr || listSize == 0)
    {
        cout << "Error: list is empty.\n";
        return;
    }

    int x;
    cout << "Enter value to delete (all occurrences): ";
    cin >> x;

    Node* cur = headPtr;
    Node* prev = nullptr;
    bool deleted = false;
    int ogSize = listSize;

    for (int i = 0; i < ogSize&&cur&&listSize > 0; ++i)
    {
        if (cur->value == x)
        {
            Node* toDelete = cur;
            cur = cur->next;
            removeNode(toDelete, prev);
            deleted = true;
            // prev останется тем же, он указывает на живой элемент
        }
        else
        {
           prev = cur;
           cur = cur->next;
        }
    }

    if (deleted) {cout << "Success: all occurrences deleted.\n";}
    else {cout << "Error: value not found.\n";}
}

// Удалить весь список
void deleteList()
{
    if (!listExists || !headPtr || listSize == 0)
    {
        cout << "Error: list is empty.\n";
        return;
    }

    Node* cur = headPtr;
    for (int i = 0; i < listSize; ++i)
    {
        Node* tmp = cur->next;
        delete cur;
        cur = tmp;
    }

    headPtr = tailPtr = nullptr;
    listSize = 0;
    listExists = false;

    cout << "Success: list deleted.\n";
}

