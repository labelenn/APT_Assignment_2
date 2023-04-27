#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
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

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


