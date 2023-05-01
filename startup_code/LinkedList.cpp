#include "LinkedList.h"
#include "helper.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

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
            string description = stock_list[1];
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

        }

        stockFile.close();
    }

    //TODO call sort linked list
}

LinkedList::~LinkedList() {
    cout << "Linked List destroyed" << endl;
}

// Mark
void LinkedList::sortLinkedList() {
    // TODO
}


void LinkedList::updateItemCount() {
    // TODO
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
    int on_hand = 6;

    // create a vectore string splitPrice
    vector<string> splitPrice;
    Helper::splitString(newItemPrice, splitPrice, ".");
    // create new Price * price and Stock* item
    Price* price = new Price(stoi(splitPrice[0]), stoi(splitPrice[1]));
    Stock* item = new Stock(id, newItemName, newItemDescription, price, on_hand);

    // create new Node* newNode for the node we are adding to linked list, and make its pointer nullptr
    Node* newNode = new Node(item, nullptr);

    currentNode->next = newNode;
    newNode = tail;

    // here is where I call LinkedList::sortLinkedList();
    
    // display new item information to show it has indeed been added to the menu
    cout << "This item \"" << newItemName << " - " << newItemDescription << "\", has now been added to the menu." << endl;
}


// Kiran   
// Fix: First and Last items in stock menu not working!!!
void LinkedList::removeItem(string removeID) 
{   
    bool match = true;

    while (match == true) 
    {
        // If there are no items in the stock menu
        if (head == nullptr)
        {
            cout << "No items to remove" << endl;
            match = false;
        }
        
        // If the first node matches
        if (head->data->id == removeID)
        {
            cout << "FIRST" << endl;

            Node* tmp = head;
            head = head->next;
            delete tmp;
            cout << "Item removed" << endl;
            match = false;
        }

        // If the last node matches
        if (tail->data->id == removeID)
        {
            cout << "LAST" << endl;

            cout << "Item removed" << endl;
            delete tail;
            match = false;
        }

        Node* currentNode = head;

        // Finds id by traversing through the LinkedList
        while (currentNode->data->id != removeID && currentNode != nullptr)
        {
            currentNode = currentNode->next;
        }

        // If the id was not found
        if (currentNode == nullptr)
        {
            cout << "Id not found" << endl;
            match = false;
        }

        // Relinks the LinkedList after after removing a node
        Node* tmp = currentNode->next; // Creates a temporary node
        currentNode->data = tmp->data;
        currentNode->next = tmp->next;

        // Deletes the node

        cout << "ALL" << endl;

        delete tmp;
        cout << "Item removed" << endl;
        match = false;
    }
    return;
}


void LinkedList::resetStockCount() {
    // TODO
}


// Lance
void LinkedList::displayItems() {
    Node* currentNode = head;
    while (currentNode != nullptr) {
        cout << currentNode->data->name << endl;
        currentNode = currentNode->next;
    }
}

string LinkedList::exportData() {
    // TODO
    return "";
}