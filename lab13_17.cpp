#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <stack>






class HashTable {

private:
    std::pair<std::string, std::string>* arr;
    size_t cap;

    int hash(const std::string& str) {
        int sum = 0;
        for (char i : str) {
            sum += i;
        }
        
        int hash = sum % cap;
        if (hash < 0) hash *= -1;


        return hash;

    }

public:
    HashTable(size_t size) {
        arr = new std::pair<std::string, std::string>[size];
        cap = size;
        for (int i = 0; i < size; i++) {
            arr[i].first = "\0";
            arr[i].second = "\0";
        }

    }

    size_t size() {
        return cap;
    }

    struct Map_Val {
        std::pair<std::string, std::string>* arr;
        //ключ значение

        std::string key;
        int hash;
        int sz;

        Map_Val(int hashh, const std::string& k, std::pair<std::string, std::string>* l, int size): hash(hashh), key(k), arr(l), sz(size) {
        }

        std::string value() {
            if (arr[hash].first == key) {
                return arr[hash].second;
            }

            for (int i = 0; i < sz; i++) {
                if (arr[i].first == key) {
                    return arr[i].second;
                }
            }

            std::string a = "\0";
            return a;

        }


        std::string& operator= (const std::string& val) {
            //если ячейка пуста или элемент с таким ключом
            if ((arr[hash].first == "\0") || (arr[hash].first == key)) {
                arr[hash].first = key;
                arr[hash].second = val;
                return arr[hash].second;
            }

            //Если ячейка занята или найден элемент с таким ключом
            for (int i = 0; i < sz; i++) {
                if ((arr[i].first == "\0") || (arr[i].first == key)) {
                    arr[i].first = key;
                    arr[i].second = val;
                    return arr[i].second;
                }
            }
            
            
        }

    };

    Map_Val operator[](const std::string& key) {
        return Map_Val(hash(key), key,  arr, cap);
    }


    std::pair<std::string, std::string>* get_data() {
        return arr;
    }

    ~HashTable() {
        delete[] arr;
    }


};

void lab13() {
    
    std::cout << "lab13" << std::endl;
    std::ifstream f;
    f.open("example.txt");

    if (f.is_open()) {
        int len_of_words = 0;
        std::string str;
        std::vector<std::string> words;
        while (!f.eof()) {
            f >> str;
            words.push_back(str);
        }

        HashTable h_table (words.size() * 2);


        for (auto& word : words) {

            switch (word.back())
            {
            case '.':
                h_table["."] = ".";
                word.pop_back();
                break;
            case ',':
                h_table[","] = ",";
                word.pop_back();
                break;
            case ';':
                h_table[";"] = ";";
                word.pop_back();
                break;
            case ':':
                h_table[":"] = ":";
                word.pop_back();
                break;
            case '?':
                h_table["?"] = "?";
                word.pop_back();
                break;
            case '!':
                h_table["!"] = "!";
                word.pop_back();
                break;
            }

            
            h_table[word] = word;
        }

        std::cout << h_table["keep"].value() << std::endl;
           
        std::ofstream out;
        out.open("table.txt");
        for (int i = 0; i < h_table.size(); i++) {
            out << i << " : \"" << h_table.get_data()[i].second << "\"" << std::endl;
        }

        out.close();

    }


    f.close();



}


class HashTableWithLists {
private:

    std::vector<std::pair<std::string, std::string>>* arr;
    
    int sz;

    int hash(const std::string& str) {
        int sum = 0;
        for (char i : str) {
            sum += i;
        }

        int hash = sum % sz;
        if (hash < 0) hash *= -1;


        return hash;

    }

public:

    HashTableWithLists(int size): sz(size){
        arr = new std::vector<std::pair<std::string, std::string>>[size];
    }


    
    struct MapWL_val {

        int m_hash;
        std::string key;
        std::vector<std::pair<std::string, std::string>>* m_arr;

        MapWL_val(int hash,const std::string& k, std::vector<std::pair<std::string, std::string>>* arr): m_hash(hash), key(k), m_arr(arr) {}


        std::string& value() {
            for (int i = 0; i < m_arr[m_hash].size(); i++) {
                if (m_arr[m_hash][i].first == key) {
                    return m_arr[m_hash][i].second;
                }
            }
            std::string r = "\0";
            return r;
        }


        std::string& operator = (const std::string& val) {

            for (int i = 0; i < m_arr[m_hash].size(); i++) {
                if (m_arr[m_hash][i].first == key) {
                    m_arr[m_hash][i].second = val;
                    return m_arr[m_hash][i].second;
                }
            }
            m_arr[m_hash].push_back({ key, val });
            return m_arr[m_hash][m_arr[m_hash].size() - 1].second;
        }
    };
    

    MapWL_val operator [](const std::string& key) {
        return MapWL_val(hash(key), key, arr);
    }

    int size() {
        return sz;
    }


    std::vector<std::pair<std::string, std::string>>* get_data() {

        return arr;

    }

    ~HashTableWithLists() {
        delete[] arr;
    }


};

void lab14() {
    std::cout << "lab14" << std::endl;
    std::ifstream f;
    f.open("example.txt");

    if (f.is_open()) {
        int len_of_words = 0;
        std::string str;
        std::vector<std::string> words;
        while (!f.eof()) {
            f >> str;
            words.push_back(str);
        }

        HashTableWithLists h_table(words.size() * 2);

        for (auto& word : words) {

            switch (word.back())
            {
            case '.':
                h_table["."] = ".";
                word.pop_back();
                break;
            case ',':
                h_table[","] = ",";
                word.pop_back();
                break;
            case ';':
                h_table[";"] = ";";
                word.pop_back();
                break;
            case ':':
                h_table[":"] = ":";
                word.pop_back();
                break;
            case '?':
                h_table["?"] = "?";
                word.pop_back();
                break;
            case '!':
                h_table["!"] = "!";
                word.pop_back();
                break;
            }


            h_table[word] = word;
        }
        h_table["keep"] = "Hello World!";


        std::ofstream out;
        out.open("table.txt");
        for (int i = 0; i < h_table.size(); i++) {
            out << i << " : { ";
            for (int j = 0; j < h_table.get_data()[i].size(); j++) {
                out << "\"" << h_table.get_data()[i][j].second << "\" ";
            }
            out << "}\n";
        }

        out.close();


    }

    f.close();

}



namespace BTree {
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;

        int value;

        Node(int val = NULL) : value(val) {}

        static void insert(Node* node, int value) {
            if (node->value == NULL) {
                node->value = value;
                return;
            }
                
            if (value < node->value) {
                if (node->left == nullptr) {
                    node->left = new Node(value);
                }
                else insert(node->left, value);
            }
            else if (value >= node->value) {
                if (node->right == nullptr) {
                    node->right = new Node(value);
                }
                else insert(node->right, value);
            }
        }

        static Node* search(Node* node, int value) {
            if (node == nullptr) return node;

            if (node->value == value) return node;

            if (value < node->value) {
                return search(node->left, value);
            }
            else {
                return search(node->right, value);
            }
        }

        
        static Node* _get_min(Node* node) {
            if (node == nullptr) return node;
            
            if (node->left == nullptr) return node;

            return _get_min(node->left);
        }

        static Node* _delete(Node* node, int value) {

            if (node == nullptr) return node;

            else if (value < node->value) {
                node->left = _delete(node->left, value);
            }
            else if (value > node->value) {
                node->right = _delete(node->right, value);
            }
            else {
                //Если только один дочерний узел (или их вовсе нет)
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
                    Node* min_right = _get_min(node->right);
                    node->value = min_right->value;
                    node->right = _delete(node->right, min_right->value);
                }
            }

            return node;

        }

        bool is_digit(char c) {
            return (c >= 48) && (c <= 57);
        }

        void init_with_string(const std::string& line) {
            
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
                insert(this, num);
            }
        }


        void print_node(const std::wstring& prefix, const Node* node, bool isLeft)
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

        void print_node(Node * node)
        {
            std::wcout << L"Дерево" << std::endl;
            print_node(L"", node, false);
        }

        void clear_node(Node* node) {
            if (node->left != nullptr)   clear_node(node->left);
            if (node->right != nullptr)  clear_node(node->right);
            if (node != nullptr) delete node;
        }

        void clear() {
            clear_node(left);
            clear_node(right);
        }


        //https://i.ytimg.com/vi/WLvU5EQVZqY/maxresdefault.jpg
        //Прямой
        static void preorder_traversal(Node* node) {
            if (node == nullptr) return;

            std::cout << node->value << " ";
            node->preorder_traversal(node->left);
            node->preorder_traversal(node->right);
        }

        //Центрированный
        static void inorder_traversal(Node* node) {
            if (node == nullptr) return;
            node->inorder_traversal(node->left);
            std::cout << node->value << " ";
            node->inorder_traversal(node->right);
        }

        //Концевой
        static void postorder_traversal(Node* node) {
            if (node == nullptr) return;
            node->postorder_traversal(node->left);
            node->postorder_traversal(node->right);
            std::cout << node->value << " ";
        }

        //Нерекурсивный прямой обход
        void stack_preorder_travelsal() {
            Node* temp = this;
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


    };


}


void write_cmds() {
    std::cout << "1. Добавить" << std::endl;
    std::cout << "2. Удалить" << std::endl;
    std::cout << "3. Поиск" << std::endl;
    std::cout << "4. Прямой обход" << std::endl;
    std::cout << "5. Центрированный обход" << std::endl;
    std::cout << "6. Концевой обход" << std::endl;
    std::cout << "7. Нерекурсивный прямой обход" << std::endl;
    std::cout << "8. Выйти" << std::endl;
}



void lab15_17() {
    BTree::Node node;
    node.init_with_string("8 (3 (1, 6 (4,7)), 10 (, 14(13,)))");



    node.print_node(&node);
    write_cmds();

    std::string a;
    std::cin >> a;

    while (true) {
        int num;
        switch (a[0])
        {


        case '1':
            system("cls");
            node.print_node(&node);
            std::cout << "1. Добавить" << std::endl;
            std::cout << "Введите значение: ";
            std::cin >> num;
            node.insert(&node, num);
            system("cls");
            break;

        case '2':
            system("cls");
            node.print_node(&node);
            std::cout << "2. Удалить" << std::endl;
            std::cout << "Введите значение: ";
            std::cin >> num;
            node._delete(&node, num);
            system("cls");
            break;



        case '3': {
            system("cls");
            node.print_node(&node);
            std::cout << "2. Поиск" << std::endl;
            std::cout << "Введите значение: ";
            std::cin >> num;
            BTree::Node* sub_tree = node.search(&node, num);

            if (sub_tree == nullptr) {
                std::cout << "Результат: Не найдено" << std::endl;
            }
            else {
                std::cout << "Результат:" << std::endl;
                node.print_node(sub_tree);
            }



            std::cout << "\n\n";
            break;
        }

        case '4':
            system("cls");
            std::cout << "Прямой обход: ";
            node.preorder_traversal(&node);
            std::cout << "\n\n";
            break;

        case '5':
            system("cls");
            std::cout << "Центрированный обход: ";
            node.inorder_traversal(&node);
            std::cout << "\n\n";
            break;

        case '6':
            system("cls");
            std::cout << "Концевой обход: ";
            node.postorder_traversal(&node);
            std::cout << "\n\n";
            break;

        case '7':
            system("cls");
            std::cout << "Нерекурсивный прямой обход: ";
            node.stack_preorder_travelsal();
            std::cout << "\n\n";
            break;


        case '8':
            system("cls");
            node.clear();
            return;

        default:
            system("cls");
            break;
        }

        
        node.print_node(&node);
        write_cmds();

        std::cin >> a;
    }

}




int main()
{
    std::setlocale(LC_ALL, "RUS");
    //lab13();
    //lab14();

    lab15_17();
}

