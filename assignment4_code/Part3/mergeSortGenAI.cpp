#include <iostream>

struct Node {
    int data;
    Node* next;
};

// Merge two sorted linked lists
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    Node* result = nullptr;
    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    }
    else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

// Merge sort for linked list
Node* mergeSort(Node* head) {
    if (!head || !head->next) return head; // 0 or 1 element

    // Split list into two halves
    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* mid = slow->next;
    slow->next = nullptr;

    // Recursive sort
    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);

    // Merge sorted halves
    return merge(left, right);
}

// Helper function to print list
void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Example usage
int main() {
    Node* head = new Node{ 29, new Node{10, new Node{41, new Node{37, new Node{13, new Node{42, new Node{5, new Node{8, nullptr}}}}}}} };

    std::cout << "Original list: ";
    printList(head);

    head = mergeSort(head);

    std::cout << "Sorted list:   ";
    printList(head);
    return 0;
}
