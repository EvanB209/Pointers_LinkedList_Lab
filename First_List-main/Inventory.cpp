#include "Inventory.h"
#include <iostream>
#include <algorithm>


Inventory::Inventory() : head(nullptr) {

}


Inventory::~Inventory() {

    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current->data;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}


void Inventory::addBook(Book* bookPtr) {
    if (bookPtr == nullptr) {
        std::cout << "Error: Cannot add null book pointer.\n";
        return;
    }

    Node* newNode = new Node(bookPtr);


    if (head == nullptr || bookPtr->getTitle() < head->data->getTitle()) {
        newNode->next = head;
        head = newNode;
    }

    else {
        Node* current = head;
        while (current->next != nullptr &&
               !(bookPtr->getTitle() < current->next->data->getTitle())) {
            current = current->next;
               }
        newNode->next = current->next;
        current->next = newNode;
    }

    std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";
}


void Inventory::displayAll() const {
    if (head == nullptr) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";
    std::cout << "Total books: " << getBookCount() << "\n\n";

    const Node* current = head;
    int position = 1;
    while (current != nullptr) {
        std::cout << "Book #" << position++ << ":\n";
        current->data->displayInfo();
        current = current->next;
    }
    std::cout << "\n";
}


void Inventory::removeBook(const std::string& title) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr && current->data->getTitle() != title) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        std::cout << "Book '" << title << "' not found in inventory.\n";
        return;
    }
    std::cout << "Removing book: " << current->data->getTitle() << "\n";

    if (previous == nullptr) head = current->next;
    else previous->next = current->next;

    delete current->data;
    delete current;

}


size_t Inventory::getBookCount() const {
    size_t count = 0;
    for (const Node* cur = head; cur != nullptr; cur = cur->next) ++count;
    return count;
}


Book* Inventory::findBook(const std::string& title) const {
    for (const Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data->getTitle() == title) {
            return cur->data;
        }
    }
    return nullptr;
}


bool Inventory::isEmpty() const {
    return head == nullptr;
}