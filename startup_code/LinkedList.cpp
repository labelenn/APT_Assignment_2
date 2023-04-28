#include "LinkedList.h"
#include "helper.cpp"
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
            splitString(fileLine, stock_list, STOCK_DELIM);

            // TODO - Check validity of stock info
            string id = stock_list[0];
            string name = stock_list[1];
            string description = stock_list[1];
            unsigned on_hand = stoi(stock_list[4]);

            vector<string> split_price;
            splitString(stock_list[3], split_price, PRICE_DELIM);
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
void LinkedList::addItem() {
    // TODO
    // NOTE: User is prompted for item name, description, and price.
    // Refer to REQ7 for more details regarding the rest of the data for the item.
}

    
void LinkedList::removeItem() {
    // TODO
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