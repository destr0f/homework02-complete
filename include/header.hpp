#ifndef HOMEWORK02_HEADER_HPP
#define HOMEWORK02_HEADER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

// Узел списка
struct Node
{
    int value;
    Node* next;
    Node* prev;
    Node(int v);
};

// Глобальное состояние списка
extern Node* headPtr;
extern Node* tailPtr;
extern int listType; // 1..4
extern int listSize; // кол-во элементов
extern bool listExists; // есть ли сейчас список

// Вид списка
bool isCircular(); // кольцевой ли
bool isDoubly(); // двусвязный ли

// Работа со списком
void initEmptyList(int type);
void initListFromVector(int type, const vector<int>& elems);
void appendElement(int value);
void printList();
void findElement();
void deleteFirstOccurrence();
void deleteAllOccurrences();
void deleteList();

// Работа с файлами
string getTypeMarker();
int markerToType(const string& marker);
void writeToFile(const string& filename);
void readFromFile(const string& filename);

// Разбор строки с элементами "1,2,3"
vector<int> parseElementsString(const string& s);

#endif //HOMEWORK02_HEADER_HPP