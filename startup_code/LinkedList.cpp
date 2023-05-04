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

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::setw;

// Mark
LinkedList::LinkedList(string stockDataFile) { 
   head = nullptr;
   tail = nullptr;

    string fileLine;
    std::ifstream stockFile;
    stockFile.open(stockDataFile);
    
    if (stockFile.is_open()) {
        while (stockFile.peek() != EOF) {
            std::getline(stockFile, fileLine);

            vector<string> stock_list;
            Helper::splitString(fileLine, stock_list, STOCK_DELIM);

            // TODO - Check validity of stock info
            string id = stock_list[0];
            string name = stock_list[1];
            string description = stock_list[2];
            unsigned on_hand = stoi(stock_list[4]);

            

            vector<string> split_price;
            Helper::splitString(stock_list[3], split_price, PRICE_DELIM);
            Price* price = new Price(stoi(split_price[0]), stoi(split_price[1]));

            Stock* stock = new Stock(id, name, description, price, on_hand);

            Node* node = new Node(stock, nullptr);

            if (head == nullptr) {
                head = node;
                tail = node;
            }
            else {
                //Node* previousTail = tail;
                tail->next = node;
                tail = node;
            }

            // Store last itemID for addItem function
            lastItemID = stoi(id.substr(1,5));

        }

        stockFile.close();

    }

    LinkedList::sortLinkedList();
}

LinkedList::~LinkedList() {
    cout << "Linked List destroyed" << endl;
}

// Laura
void LinkedList::sortLinkedList() {

    // nothing to sort if head is null or theres only 1 item in the list
    if (head == nullptr || head->next == nullptr) {
        return; 
    }

    Node* currentNode = head;
    Node* nextNode = head->next;
    
    // while the next node is not null
    while (nextNode != nullptr) {
        // while the current node does not equal the next node
        while (currentNode != nextNode) {
            string currentName = currentNode->data->name;
            string nextName = nextNode->data->name;
            // if lexographically nextName comes before currentName
            if (currentName.compare(nextName) > 0) {
                // swap the data of currentNode and nextNode
                Stock* temp = currentNode->data;
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

bool LinkedList::itemAvailability(string itemID) {

    Node* currentNode = head;
    while (currentNode->next != nullptr && currentNode->data->id != itemID) {
        currentNode = currentNode->next;
    }

    bool itemAvailable = false;
    if (currentNode->data->on_hand > 0) {
        itemAvailable = true;
    }

    return itemAvailable;

}

// Kiran
void LinkedList::updateItemCount(string selectedID) 
{
    Node* currentNode = head;
    // Finds id by traversing through the LinkedList
    while (currentNode != nullptr && currentNode->data->id != selectedID)
    {
        currentNode = currentNode->next;
    }

    // cout << currentNode->data->on_hand << endl;
    if (currentNode->data->on_hand == 0)
    {
        cout << "We have no more of this item." << endl;
    }

    else 
    {
        currentNode->data->on_hand--;
    }

    return;
}

// Add item in correct sort spot
// EG when inserting 'Lemon Meringue Pie' it must go between 'Lemon cheesecake' and 'Lemon Tart'
// Apple Pie -> Lemon Cheesecake -> Lemon Tart ->  Meat Pie
// Laura
void LinkedList::addItem(string id, string newItemName, string newItemDescription, string newItemPrice) {
    // TODO
    // NOTE: User is prompted for item name, description, and price.
    // Refer to REQ7 for more details regarding the rest of the data for the item.

    // create new Node* currentNode that holds the current node position
    Node* currentNode = head;
    while (currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
    }
    

    // to do, update on_hand
    int on_hand = DEFAULT_STOCK_LEVEL;

    // create a vectore string splitPrice
    vector<string> splitPrice;
    Helper::splitString(newItemPrice, splitPrice, ".");
    // create new Price* price and Stock* item
    Price* price = new Price(stoi(splitPrice[0]), stoi(splitPrice[1]));
    Stock* item = new Stock(id, newItemName, newItemDescription, price, on_hand);

    // create new Node* newNode for the node we are adding to linked list, and make its pointer nullptr
    Node* newNode = new Node(item, nullptr);

    currentNode->next = newNode;
    newNode = tail;

    LinkedList::sortLinkedList();
    
    // display new item information to show it has indeed been added to the menu
    cout << "This item \"" << newItemName << " - " << newItemDescription << "\", has now been added to the menu." << endl;
}


// Kiran   
void LinkedList::removeItem(string removeID) 
{   
    // If there are no items in the stock menu
    if (head == nullptr)
    {
        cout << "The task Remove Item failed to run successfully." << endl;
    }
        
    // If the first node matches
    else if (head->data->id == removeID)
    {
        Node* tmp = head;
        head = head->next;

        cout << "\"" << tmp->data->id << " - " << tmp->data->name << " - " 
        << tmp->data->description << "\"" << " has been removed from the system." << endl;

        delete tmp;
    }

    // If the last node matches
    else if (tail->data->id == removeID)
    {
        
        Node* currentNode = head;
        Node* tmp = tail;

        while (currentNode->next->next != nullptr)
        {
            currentNode = currentNode->next;
        }

        currentNode->next = nullptr;

        cout << "\"" << tmp->data->id << " - " << tmp->data->name << " - " 
        << tmp->data->description << "\"" << " has been removed from the system." << endl;

        delete tmp;
    }

    // If not the first or last node
    else 
    {
        Node* currentNode = head;

        // Finds id by traversing through the LinkedList
        while (currentNode != nullptr && currentNode->data->id != removeID)
        {
            currentNode = currentNode->next;
        }

        // If the id was not found
        if (currentNode == nullptr)
        {
            cout << "The task Remove Item failed to run successfully." << endl;
        } 
        
        // Relinks the LinkedList after after removing a node
        else 
        {
            Node* tmp = currentNode->next;
            currentNode->data = tmp->data;
            currentNode->next = tmp->next;

            cout << "\"" << tmp->data->id << " - " << tmp->data->name << " - " 
            << tmp->data->description << "\"" << " has been removed from the system." << endl;

            delete tmp;
        }
    }
    
    return;
}


void LinkedList::resetStockCount() {
    // TODO
}


// Lance
void LinkedList::displayItems() {
    int idPrintWidth = 6;
    int namePrintWidth = 40;
    int availablePrintWidth = 12;

    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID" << setw(idPrintWidth - 2) << "|";
    cout << "Name" << setw(namePrintWidth - 4) << "|";
    cout << " Available " << "|";
    cout << " Price  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    Node* currentNode = head;
    while (currentNode != nullptr) {
        string itemName = currentNode->data->name;
        string itemCount = std::to_string(currentNode->data->on_hand);
        cout << currentNode->data->id << "|";
        cout << itemName << setw(namePrintWidth - itemName.size()) << "|";
        cout << currentNode->data->on_hand << setw(availablePrintWidth - itemCount.size()) << "|";
        if (currentNode->data->price->cents == 0) {
            cout << "$ " << currentNode->data->price->dollars << "." << "00" << endl;
        }
        else {
            cout << "$ " << currentNode->data->price->dollars << "." << currentNode->data->price->cents << endl;
        }
        
        currentNode = currentNode->next;
    }
}

string LinkedList::exportData() {
    // TODO
    return "";
}