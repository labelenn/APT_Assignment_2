#include "LinkedList.h"
#include "helper.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ios>
#include <iomanip>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::vector;


LinkedList::LinkedList(string stockDataFile)
{
    head = nullptr;
    tail = nullptr;

    bool inputError = false;
    string fileLine;
    std::ifstream stockFile;
    stockFile.open(stockDataFile);
    if (stockFile.is_open())
    {
        while (stockFile.peek() != EOF && inputError == false)
        {
            std::getline(stockFile, fileLine);

            if (fileLine.size() > 0)
            {

                vector<string> stock_list;
                Helper::splitString(fileLine, stock_list, STOCK_DELIM);

                if (stock_list.size() == 5)
                {
                    // TODO - Check validity of stock info
                    string id = stock_list[0];
                    string name = stock_list[1];
                    string description = stock_list[2];
                    unsigned on_hand = stoi(stock_list[4]);

                    vector<string> split_price;
                    Helper::splitString(stock_list[3], split_price, PRICE_DELIM);
                    Price *price = new Price(stoi(split_price[0]), stoi(split_price[1]));

                    Stock *stock = new Stock(id, name, description, price, on_hand);

                    Node *node = new Node(stock, nullptr);

                    if (head == nullptr)
                    {
                        head = node;
                        tail = node;
                    }
                    else
                    {
                        // Node* previousTail = tail;
                        tail->next = node;
                        tail = node;
                    }
                }
                else
                {
                    cout << "item does not match expected format in input file" << endl;
                }
            }
            else
            {
                cout << "line is empty in stock input file" << endl;
            }
        }

        stockFile.close();

        if (head != nullptr)
        {
            LinkedList::sortLinkedList();
        }
        else
        {
            cout << "stock input file was empty or no inputs matched the required format" << endl;
        }
    }
    else
    {
        cout << "Cannot open file." << endl;
    }
}

LinkedList::~LinkedList()
{
    Node *currentNode = head;

    while (currentNode != nullptr)
    {
        currentNode->~Node();
        currentNode = currentNode->next;
    }

    // cout << "Linked List destroyed" << endl;
}


void LinkedList::sortLinkedList()
{
    // nothing to sort if head is null or theres only 1 item in the list
    if (head != nullptr && head->next != nullptr)
    {

        Node *currentNode = head;
        Node *nextNode = head->next;

        // while the next node is not null
        while (nextNode != nullptr)
        {
            // while the current node does not equal the next node
            while (currentNode != nextNode)
            {
                string currentName = currentNode->data->name;
                string nextName = nextNode->data->name;
                // if lexographically nextName comes before currentName
                if (currentName.compare(nextName) > 0)
                {
                    // swap the data of currentNode and nextNode
                    Stock *temp = currentNode->data;
                    currentNode->data = nextNode->data;
                    nextNode->data = temp;
                }
                // get next node
                currentNode = currentNode->next;
            }
            // reset the pointers and names for the next iteration
            currentNode = head;
            nextNode = nextNode->next;
        }
    }
}

bool LinkedList::findItem(string itemID)
{
    Node *currentNode = head;
    bool itemFound = false;

    if (currentNode != nullptr)
    {
        if (head->data->id == itemID)
        {
            itemFound = true;
        }

        else
        {
            while (currentNode->next != nullptr && currentNode->data->id != itemID)
            {

                currentNode = currentNode->next;

                if (currentNode->data->id == itemID)
                {
                    itemFound = true;
                }
            }
        }
    }

    return itemFound;
}

Stock LinkedList::getItem(string itemID)
{
    Node *currentNode = head;

    // Temp values to return if the list is empty
    Stock returnData;

    if (currentNode != nullptr)
    {
        while (currentNode->next != nullptr && currentNode->data->id != itemID)
        {
            currentNode = currentNode->next;
        }

        returnData = *currentNode->data;
    }

    return returnData;
}

bool LinkedList::itemAvailability(string itemID)
{

    Node *currentNode = head;
    bool itemAvailable = false;

    if (currentNode != nullptr)
    {
        while (currentNode->next != nullptr && currentNode->data->id != itemID)
        {
            currentNode = currentNode->next;
        }

        if (currentNode->data->on_hand > 0)
        {
            itemAvailable = true;
        }
    }

    return itemAvailable;
}


void LinkedList::updateItemCount(string selectedID)
{
    Node *currentNode = head;

    if (currentNode != nullptr)
    {
        // Finds id by traversing through the LinkedList
        while (currentNode != nullptr && currentNode->data->id != selectedID)
        {
            currentNode = currentNode->next;
        }

        currentNode->data->on_hand--;
    }
}

void LinkedList::findHighestID()
{
    Node *currNode = head;
    int highestID = 0;
    int currentID = 0;

    if (currNode == nullptr)
    {
        highestID = 0001;
    }

    else
    {
        while (currNode != nullptr)
        {
            currentID = stoi(currNode->data->id.substr(1, 4));

            if (currentID > highestID)
            {
                highestID = currentID;
            }

            currNode = currNode->next;
        }
        lastItemID = highestID;
    }
}


void LinkedList::addItem(string id, string newItemName, string newItemDescription, string newItemPrice)
{
    // create new Node* currentNode that holds the current node position
    Node *currentNode = head;
    if (currentNode != nullptr)
    {
        while (currentNode->next != nullptr)
        {
            currentNode = currentNode->next;
        }
    }

    // default stock level
    int on_hand = DEFAULT_STOCK_LEVEL;
    // split price string to obtain dollars and cents
    vector<string> splitPrice;
    Helper::splitString(newItemPrice, splitPrice, ".");
    // create new Price* price and Stock* item
    Price *price = new Price(stoi(splitPrice[0]), stoi(splitPrice[1]));
    Stock *item = new Stock(id, newItemName, newItemDescription, price, on_hand);

    // make new node tail and currentNode->next point to this node
    Node *newNode = new Node(item, nullptr);
    if (currentNode != nullptr)
    {
        currentNode->next = newNode;
        tail = newNode;
    }
    else
    {
        head = newNode;
        tail = newNode;
    }

    // take list and sort it
    LinkedList::sortLinkedList();

    // display new item information to show it has indeed been added to the menu
    cout << "This item \"" << newItemName << " - " << newItemDescription << "\", has now been added to the menu." << endl;
}


void LinkedList::removeItem(string removeID)
{
    // If there are no items in the stock menu
    if (head == nullptr)
    {
        cout << "Error: desired id was not found." << endl;
        cout << "The task Remove Item failed to run successfully." << endl;
    }
    else
    {
        // If the first node matches
        if (head->data->id == removeID)
        {
            Node *tmp = head;
            head = head->next;

            cout << "\"" << tmp->data->id << " - " << tmp->data->name << " - "
                 << tmp->data->description << "\""
                 << " has been removed from the system." << endl;

            delete tmp;
        }

        // If the last node matches
        else if (tail->data->id == removeID)
        {
            cout << "removing last element" << endl;
            Node *currentNode = head;
            Node *tmp = tail;

            while (currentNode->next->next != nullptr)
            {
                currentNode = currentNode->next;
            }

            tail = currentNode;
            currentNode->next = nullptr;

            cout << "\"" << tmp->data->id << " - " << tmp->data->name << " - "
                 << tmp->data->description << "\""
                 << " has been removed from the system." << endl;

            delete tmp;
        }

        // If not the first or last node
        else
        {
            Node *currentNode = head;
            bool itemFound = false;

            // Finds id by traversing through the LinkedList
            while (currentNode != nullptr && currentNode->next != nullptr && currentNode->data->id != removeID)
            {
                // If id matches
                if (currentNode->next->next != nullptr && currentNode->next->data->id == removeID)
                {
                    itemFound = true;

                    cout << "\"" << currentNode->next->data->id << " - " << currentNode->next->data->name << " - "
                         << currentNode->next->data->description << "\""
                         << " has been removed from the system." << endl;

                    Node *tmp = currentNode->next;
                    currentNode->next = currentNode->next->next;

                    delete tmp;
                }

                currentNode = currentNode->next;
            }

            // If the id was not found
            if (!itemFound)
            {
                cout << "Error: desired id was not found." << endl;
                cout << "The task Remove Item failed to run successfully." << endl;
            }
        }
    }
}

void LinkedList::resetStockCount()
{
    Node *currentNode = head;

    // If there are no items in the stock menu
    if (head == nullptr)
    {
        cout << "The task Reset Stock Count failed to run successfully." << endl;
    }
    else
    {
        // If there is 1 item in the stock menu
        if (head == tail)
        {
            tail->data->on_hand = DEFAULT_STOCK_LEVEL;
            cout << "All stock has been reset to the default level of " << DEFAULT_STOCK_LEVEL << endl;
        }

        else
        {
            // Traverses through the LinkedList
            while (currentNode->next != nullptr)
            {
                currentNode->data->on_hand = DEFAULT_STOCK_LEVEL;
                currentNode = currentNode->next;
            }

            tail->data->on_hand = DEFAULT_STOCK_LEVEL;
            cout << "All stock has been reset to the default level of " << DEFAULT_STOCK_LEVEL << endl;
        }
    }
}

void LinkedList::displayItems()
{
    int idPrintWidth = 6;
    int namePrintWidth = 40;
    int availablePrintWidth = 12;

    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID" << setw(idPrintWidth - 2) << "|";
    cout << "Name" << setw(namePrintWidth - 4) << "|";
    cout << " Available "
         << "|";
    cout << " Price  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    Node *currentNode = head;
    while (currentNode != nullptr)
    {
        string itemName = currentNode->data->name;
        string itemCount = std::to_string(currentNode->data->on_hand);
        cout << currentNode->data->id << "|";
        cout << itemName << setw(namePrintWidth - itemName.size()) << "|";
        cout << currentNode->data->on_hand << setw(availablePrintWidth - itemCount.size()) << "|";
        if (currentNode->data->price->cents == 0)
        {
            cout << "$ " << currentNode->data->price->dollars << "."
                 << "00" << endl;
        }
        else
        {
            cout << "$ " << currentNode->data->price->dollars << "." << currentNode->data->price->cents << endl;
        }

        currentNode = currentNode->next;
    }
}

string LinkedList::exportData()
{

    Node *currentNode = head;
    string exportData = "";

    while (currentNode != nullptr)
    {
        string id = currentNode->data->id;
        string itemName = currentNode->data->name;
        string description = currentNode->data->description;
        string itemCount = std::to_string(currentNode->data->on_hand);
        string priceDollars = std::to_string(currentNode->data->price->dollars);
        string priceCents = std::to_string(currentNode->data->price->cents);

        exportData += id + "|";
        exportData += itemName + "|";
        exportData += description + "|";
        exportData += priceDollars + "." + ((priceCents == "0") ? "00" : priceCents) + "|";
        exportData += itemCount + "\n";

        currentNode = currentNode->next;
    }

    return exportData;
}