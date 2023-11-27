#include "b_tree.h"
#include <vector>
#include <stack>

BTree::BinaryTree::BinaryTree(int value)
{
	root = new Node(value);
}

BTree::BinaryTree::BinaryTree(const BinaryTree& tree)
{
	root = new Node();
	copy(root, tree.root);
}

BTree::BinaryTree::~BinaryTree()
{
	clear_node(root);
}

void BTree::BinaryTree::_insert(int value)
{
	_insert(root, value);
}

BTree::Node* BTree::BinaryTree::_search(int value)
{
    return _search(root, value);
}

void BTree::BinaryTree::_delete(int value)
{
    root = _delete(root, value);
    if (root == nullptr) root = new Node();
    return;
}

void BTree::BinaryTree::preorder_traversal()
{
    preorder_traversal(root);
}

void BTree::BinaryTree::inorder_traversal()
{
    inorder_traversal(root);
}

void BTree::BinaryTree::postorder_traversal()
{
    postorder_traversal(root);
}

void BTree::BinaryTree::stack_preorder_travelsal()
{
    stack_preorder_travelsal(root);
}

void BTree::BinaryTree::init_with_string(const std::string& line)
{
    std::string number;
    std::vector<int> numbers;
    bool num_read = false;
    for (char c : line) {
        if ((c == '-') || (is_digit(c))) {
            number += c;
            num_read = true;
        }
        else {
            if (num_read) {
                num_read = false;
                numbers.push_back(atoi(number.c_str()));
                number.clear();
            }

        }
    }

    if (!number.empty()) {
        numbers.push_back(atoi(number.c_str()));
    }

    for (auto num : numbers) {
        _insert(root, num);
    }
}

void BTree::BinaryTree::print_node(Node* node)
{
    std::wcout << L"Дерево" << std::endl;
    print_node(L"", node, false);
}

void BTree::BinaryTree::print()
{
    print_node(root);
}

void BTree::BinaryTree::copy(Node* dest, Node* src)
{
    _insert(dest, src->value);
    if (src->left != nullptr) copy(dest, src->left);
    if (src->right != nullptr) copy(dest, src->right);
}

void BTree::BinaryTree::preorder_traversal(Node* node)
{
    if (node == nullptr) return;
    std::cout << node->value << " ";
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

void BTree::BinaryTree::inorder_traversal(Node* node)
{
    if (node == nullptr) return;
    inorder_traversal(node->left);
    std::cout << node->value << " ";
    inorder_traversal(node->right);
}

void BTree::BinaryTree::postorder_traversal(Node* node)
{
    if (node == nullptr) return;
    postorder_traversal(node->left);
    postorder_traversal(node->right);
    std::cout << node->value << " ";
}

void BTree::BinaryTree::stack_preorder_travelsal(Node* node)
{
    Node* temp = node;
    std::stack<Node*> nodes;
    while ((temp != nullptr) || (!nodes.empty())) {
        if (!nodes.empty()) {
            temp = nodes.top();
            nodes.pop();
        }

        while (temp != nullptr) {
            std::cout << temp->value << " ";

            if (temp->right != nullptr) {
                nodes.push(temp->right);
            }

            temp = temp->left;
        }
    }
}

BTree::Node* BTree::BinaryTree::get_min(Node* node)
{
    if (node == nullptr) return node;
    if (node->left == nullptr) return node;
    return get_min(node->left);
}

void BTree::BinaryTree::_insert(Node* node, int value)
{
    if (node->value == NULL) {
        node->value = value;
        return;
    }

    if (value < node->value) {
        if (node->left == nullptr) {
            node->left = new Node(value);
        }
        else _insert(node->left, value);
    }
    else if (value > node->value) {
        if (node->right == nullptr) {
            node->right = new Node(value);
        }
        else _insert(node->right, value);
    }
    else if (value == node->value) return;
}

BTree::Node* BTree::BinaryTree::_search(Node* node, int value)
{
    if (node == nullptr) return node;

    if (node->value == value) return node;

    if (value < node->value) {
        return _search(node->left, value);
    }
    else {
        return _search(node->right, value);
    }
}

BTree::Node* BTree::BinaryTree::_delete(Node* node, int value)
{
    if (node == nullptr) return node;

    else if (value < node->value) {
        node->left = _delete(node->left, value);
    }
    else if (value > node->value) {
        node->right = _delete(node->right, value);
    }
    else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else {
                Node* temp = node->left;
                delete node;
                return temp;
            }
        }
        else {
            Node* min_right = get_min(node->right);
            node->value = min_right->value;
            node->right = _delete(node->right, min_right->value);
            return node;
        }
    }

    
}

bool BTree::BinaryTree::is_digit(char c)
{
    return (c >= 48) && (c <= 57);
}

void BTree::BinaryTree::print_node(const std::wstring& prefix, const Node* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::wcout << prefix;

        std::wcout << (isLeft ? L"│l-> " : L"│r-> ");

        std::cout << node->value << std::endl;
        print_node(prefix + (isLeft ? L"│   " : L"    "), node->left, true);
        print_node(prefix + (isLeft ? L"│   " : L"    "), node->right, false);
    }
}

void BTree::BinaryTree::clear_node(Node* node)
{
    if (node->left != nullptr)   clear_node(node->left);
    if (node->right != nullptr)  clear_node(node->right);
    if (node != nullptr) delete node;
}



