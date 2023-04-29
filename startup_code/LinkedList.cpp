#include "LinkedList.h"
#include "helper.h"

#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
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
void LinkedList::addItem(string newItemName, string newItemDescription, string newItemPrice) {
    // TODO
    // NOTE: User is prompted for item name, description, and price.
    // Refer to REQ7 for more details regarding the rest of the data for the item.

    // create new Node* currentNode that holds the current node position
    Node* currentNode = head;
    while (currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
    }
    
    // create static int that hold the nextID value 6, so that when we add a new item, we know which int to start at when adding ID's
    static int nextId = 6;
    // these lines create the ID by making sure there are 4 places, and to set the spaces not filled to 0
    std::stringstream ss;
    ss << "I" << std::setfill('0') << std::setw(4) << ++nextId;
    string id = ss.str();
    // should hold an example value of: I0006

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