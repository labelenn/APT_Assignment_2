#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#define STOCK_DELIM "|"
#define PRICE_DELIM "."
#include "Node.h"


class LinkedList
{
public:
    LinkedList(string);
    ~LinkedList();

    // Sort nodes by Item Name
    void sortLinkedList();

    // Update node/item count (for when item is purchased -- item on hand number (number of stock for that item) is deducted)
    void updateItemCount();

    // Add node/item
    void addItem();

    // Remove node/item
    void removeItem();

    // For resetting stock count
    void resetStockCount();

    // Display items stored in linked list
    void displayItems();

    // Returns data in linked list as string for saving to file.
    string exportData();

private:
    // the beginning of the list
    Node* head;
    // End of list
    Node* tail;
  
    // how many nodes are there in the list?
    // TODO -  Add count again
    //unsigned count;
};

#endif  // LINKEDLIST_H


