#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // Sort nodes by Item Name
    sortLinkedList();

    // Update node/item count (for when item is purchased -- item on hand number (number of stock for that item) is deducted)
    updateItemCount();

    // Add node/item
    addItem();

    // Remove node/item
    removeItem();

    // For resetting stock count
    resetStockCount();

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


