#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "Coin.h"
#include "CashRegister.h"
#include <iomanip>
#include <sstream>
#include <cctype>
#include <cstring>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

LinkedList* loadLinkedList(string fileName) 
{
    LinkedList* stockList = new LinkedList(fileName);
    return stockList;
}

void assertEquals(string actual,string  expected) 
{
    if (actual == expected) 
    {
        cout << "Test successful" << endl;
    } 

    else 
    {
        cout << "Test unsuccessful" << endl;
    }       
}

void test_add_item_to_the_list()
{
    cout << "Running Test test_add_item_to_the_list" << endl;
    LinkedList* stockList = loadLinkedList("stock.dat");
    stockList->addItem("I0006", "Test", "Test Description", "20.00"); 

    bool itemFound = stockList->findItem("I0006");

    assertEquals(itemFound ? "true" : "false", "true");
    cout << endl;
}

void test_remove_item_from_the_list() 
{
    cout << "Running Test test_remove_item_from_the_list" << endl; 
    LinkedList* stockList = loadLinkedList("stock.dat");

    stockList->displayItems();
    stockList->removeItem("I0002");
    stockList->removeItem("I0001");
    stockList->removeItem("I0005");
    stockList->removeItem("I0004");
    stockList->displayItems();

    bool itemFound = stockList->findItem("I0003");
    
    if (itemFound)
    {
        cout << "unsuccessful" << endl;
    } 

    else 
    {
        cout << "successful" << endl;
    }

    cout << endl;
}

int main(int argc, char **argv) 
{
    //test_add_item_to_the_list();
    test_remove_item_from_the_list();
    return 0;
}

void test_remove_item_from_the_start_of_the_list() 
{
    cout << "Running Test test_remove_item_from_the_list" << endl; 
    
    LinkedList* stockList = loadLinkedList("stock.dat");
    stockList->removeItem("I0002");
    bool itemFound = stockList->findItem("I0002");
    
    if (itemFound) 
    {
        cout << "unsuccessful" << endl;
    } 

    else 
    {
        cout << "successful" << endl;
    }

    cout << endl;
}

void test_remove_item_from_the_end_of_the_list() 
{
        cout << "Running Test test_remove_item_from_the_list" << endl; 
    
    LinkedList* stockList = loadLinkedList("stock.dat");
    stockList->removeItem("I0001");
    bool itemFound = stockList->findItem("I0001");
    
    if (itemFound) 
    {
        cout << "unsuccessful" << endl;
    } 

    else 
    {
        cout << "successful" << endl;
    }

    cout << endl;
}

void test_remove_item_from_the_middle_of_the_list() 
{
    cout << "Running Test test_remove_item_from_the_list" << endl; 
    
    LinkedList* stockList = loadLinkedList("stock.dat");
    stockList->removeItem("I0003");
    stockList->removeItem("I0004");
    stockList->removeItem("I0005");

    bool itemFound = stockList->findItem("I0003");
    
    if (itemFound) 
    {
        cout << "unsuccessful" << endl;
    } 
    
    else 
    {
        cout << "successful" << endl;
    }

    cout << endl;
}