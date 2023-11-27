#pragma once
#include <iostream>
#include <string>

namespace BTree {

    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int value;
        Node(int val = NULL) : value(val) {}
    };

    class BinaryTree {
    public:
        BinaryTree(int value = NULL);
        BinaryTree(const BinaryTree& tree);
        ~BinaryTree();

        void init_with_string(const std::string& line);

        void  _insert(int value);
        Node* _search(int value);
        void  _delete(int value);

        //Обходы https://i.ytimg.com/vi/WLvU5EQVZqY/maxresdefault.jpg
        void preorder_traversal();
        void inorder_traversal();
        void postorder_traversal();
        void stack_preorder_travelsal();

        void print_node(Node* node);
        void print();

    private:
        void copy(Node* dest, Node* src);

        void preorder_traversal(Node* node);
        void inorder_traversal(Node* node);
        void postorder_traversal(Node* node);
        void stack_preorder_travelsal(Node* node);

        Node* get_min(Node* node);
        void  _insert(Node* node, int value);
        Node* _search(Node* node, int value);
        Node* _delete(Node* node, int value);

        bool is_digit(char c);
        void print_node(const std::wstring& prefix, const Node* node, bool isLeft);
        void clear_node(Node* node);

        Node* root;
    };
}
