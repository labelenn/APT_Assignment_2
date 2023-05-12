#include "Node.h"

// Node initialisation and destruction
Node::Node(Stock* stock, Node* node) {
    this->next = node;
    this->data = stock;
};
Node::~Node() {
    data->~Stock();
    // cout << "Node destroyed" << endl;
};

// Price initialisation and desctruction
Price::Price(unsigned dollars, unsigned cents) {
    this->dollars = dollars;
    this->cents = cents;
};
Price::~Price() {
    // cout << "Price destroyed" << endl;
};

// Default constructor with no args
Stock::Stock() {
    this->id = "";
    this->name = "";
    this->description = "";
    this->price = new Price(0,0);
    this->on_hand = 0;
};
// Stock initialisation and desctruction
Stock::Stock(string id, string name, string description, Price* price, unsigned on_hand) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->price = price;
    this->on_hand = on_hand;    
};
Stock::~Stock() {
    price->~Price();
    // cout << "Stock destroyed" << endl;
};