#include <iostream>
#include <fstream>
#include "b_tree.h"
#include <vector>

class HashTableWithLists {
public:

    HashTableWithLists(int size) : sz(size) {
        arr = new std::vector<std::pair<std::string, std::string>>[size];
    }
    HashTableWithLists(const HashTableWithLists& table) {
        sz = table.sz;
        arr = new std::vector<std::pair<std::string, std::string>>[sz];
        std::memcpy(arr, table.arr, sizeof(arr));
    }
    ~HashTableWithLists() {
        delete[] arr;
    }

    int size() {
        return sz;
    }

    std::vector<std::pair<std::string, std::string>>* data() {
        return arr;
    }

    std::string& operator [](const std::string& key) {
        for (auto& el : arr[hash(key)]) {
            if (el.first == key) return el.second;
        }

        arr[hash(key)].push_back({ key, "\0" });

        return arr[hash(key)].back().second;
    }

private:
    int hash(const std::string& str) {
        int hash = 0;
        for (char i : str) {
            hash += i;
        }
        if (hash < 0) hash *= -1;
        hash %= sz;
        return hash;
    }

    std::vector<std::pair<std::string, std::string>>* arr;
    int sz;
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
            for (int j = 0; j < h_table.data()[i].size(); j++) {
                out << "\"" << h_table.data()[i][j].second << "\" ";
            }
            out << "}\n";
        }

        out.close();


    }

    f.close();

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
    BTree::BinaryTree tree;
    tree.init_with_string("8 (3 (1, 6 (4,7)), 10 (, 14(13,)))");
   
    tree.print();
    write_cmds();

    std::string a;
    std::cin >> a;

    while (true) {
        int num;
        switch (a[0])
        {


        case '1':
            system("cls");
            tree.print();
            std::cout << "1. Добавить" << std::endl;
            std::cout << "Введите значение: ";
            std::cin >> num;
            tree._insert(num);
            system("cls");
            break;

        case '2':
            system("cls");
            tree.print();
            std::cout << "2. Удалить" << std::endl;
            std::cout << "Введите значение: ";
            std::cin >> num;
            tree._delete(num);
            system("cls");
            break;



        case '3': {
            system("cls");
            tree.print();
            std::cout << "2. Поиск" << std::endl;
            std::cout << "Введите значение: ";
            std::cin >> num;
            BTree::Node* sub_tree = tree._search(num);

            if (sub_tree == nullptr) {
                std::cout << "Результат: Не найдено" << std::endl;
            }
            else {
                std::cout << "Результат:" << std::endl;
                tree.print_node(sub_tree);
            }



            std::cout << "\n\n";
            break;
        }

        case '4':
            system("cls");
            std::cout << "Прямой обход: ";
            tree.preorder_traversal();
            std::cout << "\n\n";
            break;

        case '5':
            system("cls");
            std::cout << "Центрированный обход: ";
            tree.inorder_traversal();
            std::cout << "\n\n";
            break;

        case '6':
            system("cls");
            std::cout << "Концевой обход: ";
            tree.postorder_traversal();
            std::cout << "\n\n";
            break;

        case '7':
            system("cls");
            std::cout << "Нерекурсивный прямой обход: ";
            tree.stack_preorder_travelsal();
            std::cout << "\n\n";
            break;


        case '8':
            system("cls");
            return;

        default:
            system("cls");
            break;
        }


        tree.print();
        write_cmds();

        std::cin >> a;
    }

}




int main()
{
    std::setlocale(LC_ALL, "RUS");
    //lab14();

    lab15_17();
}
