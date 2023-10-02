#include <string>
#include <vector>
#include <iostream>
class AVLTree{
private:
    struct Node {
        int idNum;
        int balanceFactor;
        std::string studentName;
        Node *left;
        Node *right;
        Node(std::string name, int id) : idNum(id), studentName(name), left(nullptr), right(nullptr){}
    };
    Node* root = nullptr;
    int getHeight(Node* node){
        if(node == nullptr)
            return 0;
        int leftHeight = 1 + getHeight(node->left);
        int rightHeight = 1 + getHeight(node->right);
        int height = leftHeight;
        if(rightHeight > height)
            height = rightHeight;
        return height;
    }
    int getBalance(Node* node){
        int leftTree = getHeight(node->left);
        int rightTree = getHeight(node->right);
        return (leftTree - rightTree);
    }

    //Helpers

    //From Aman's Lecture
    Node* helperInsert(AVLTree::Node *helpRoot, std::string name, int id) {
        if(helpRoot == nullptr)
            return new Node(name, id);
        else if(id < helpRoot->idNum) {
            helpRoot->left = helperInsert(helpRoot->left, name, id);
            helpRoot = rotateLogic(helpRoot);
        }
        else {
            helpRoot->right = helperInsert(helpRoot->right, name, id);
            helpRoot = rotateLogic(helpRoot);
        }
        return helpRoot;
    };

    void inorderHelp(Node* node, std::vector<std::string> &in){
        if (node == nullptr)
            return;
        else {
            inorderHelp(node->left, in);
            in.push_back(node->studentName);
            inorderHelp(node->right, in);
        }
    }

    void preorderHelp(Node* node, std::vector<std::string> &in){
        if (node == nullptr)
            return;
        else {
            in.push_back(node->studentName);
            preorderHelp(node->left, in);
            preorderHelp(node->right, in);
        }
    }

    void postorderHelp(Node* node, std::vector<std::string> &in){
        if (node == nullptr)
            return;
        else {
            postorderHelp(node->left, in);
            postorderHelp(node->right, in);
            in.push_back(node->studentName);
        }
    }

    void searchNameHelp(Node* node, std::string name, int& count){
        if(node == nullptr)
            return;
        else{
            searchNameHelp(node->left, name, count);
            if(node->studentName == name) {
                std::string str = std::to_string(node->idNum);
                if(str.length() != 8) {
                    for (int i = str.length(); i < 8; i++){
                        std::cout << "0";
                    }
                }
                std::cout << node->idNum << std::endl;
                count++;
            }
            searchNameHelp(node->right, name, count);
        }
    }

    void searchIDHelp(Node* node, int id, int& count, bool print){
        if (node == nullptr)
            return;
        else {
            if(node->idNum == id) {
                if (print)
                    std::cout << node->studentName << std::endl;
                count++;
            }
            searchIDHelp(node->left, id, count, print);
            searchIDHelp(node->right, id, count, print);
        }
    }

    Node* findInorderSuccessor(Node* node){
        Node* smallest = node;
        while(smallest->left != nullptr){
            smallest = smallest->left;
        }
        return smallest;
    }

    Node* removeIDHelp(Node* nodeC, int id){
        if (nodeC == nullptr)
            nodeC = nullptr;
        if(id!=nodeC->idNum){
            if(id < nodeC->idNum) {
                nodeC->left = removeIDHelp(nodeC->left, id);
            }
            else {
                nodeC->right = removeIDHelp(nodeC->right, id);
            }
        }
        else{
            //No children
            if(nodeC->left == nullptr && nodeC->right == nullptr) {
                return nullptr;
            }
            //Right child
            else if (nodeC->left == nullptr){
                nodeC = nodeC->right;
            }
            //Left child
            else if (nodeC->right == nullptr){
                nodeC = nodeC->left;
            }
            //2 children
            else {
                Node *successor = findInorderSuccessor(nodeC->right);
                nodeC->studentName = successor->studentName;
                nodeC->idNum = successor->idNum;
                nodeC->right = removeIDHelp(nodeC->right, successor->idNum);
            }
        }
        return nodeC;
    }

    void removeInorderHelper(Node* node, int num, int& counter){
        //static int counter = -1;
        if (node == nullptr)
            return;
        if(counter <= num){
            removeInorderHelper(node->left, num, counter);
            counter++;
            if((counter-1) == num) {
                removeID(node->idNum);
                return;
            }
            removeInorderHelper(node->right, num, counter);
        }
    }

    //Rotations
    Node* rotateLogic(Node* node){
        node->balanceFactor = getBalance(node);
        if(node->balanceFactor == -2){
            if(node->right->balanceFactor == 1) {
                node = rotateRightLeft(node);
            }
            else{
                node = rotateLeft(node);
            }
        }
        else if(node->balanceFactor == 2){
            if(node->left->balanceFactor == -1) {
                node = rotateLeftRight(node);
            }
            else{
                node = rotateRight(node);
            }
        }
        return node;
    }

    //Stepik code (all rotations)
    Node* rotateLeft(Node *node){
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        return rightChild;
    }

    Node* rotateRight(Node *node){
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        return leftChild;
    }

    Node* rotateLeftRight(Node *node){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node* rotateRightLeft(Node *node){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

public:
    //Constructor
    AVLTree(){
        this->root = nullptr;
    }

    //Insertion
    void insertStudent(std::string nameIn, int idNUM){
        this->root = helperInsert(this->root, nameIn, idNUM);
    }

    //Printing
    void printInorder(){
        std::vector<std::string> input;
        inorderHelp(this->root, input);
        for(int i = 0; i < input.size()-1; i++){
          std::cout << input[i];
            if (input[i+1] != "")
                std::cout << ", ";
        }
        std::cout << input[input.size()-1] << std::endl;
    }

    void printPreorder(){
        std::vector<std::string> input;
        preorderHelp(this->root, input);
        for(int i = 0; i < input.size()-1; i++){
            std::cout << input[i];
            if (input[i+1] != "")
                std::cout << ", ";
        }
        std::cout << input[input.size()-1] << std::endl;
    }

    void printPostorder(){
        std::vector<std::string> input;
        postorderHelp(this->root, input);
        for(int i = 0; i < input.size()-1; i++){
            std::cout << input[i];
            if (input[i+1] != "")
                std::cout << ", ";
        }
        std::cout << input[input.size()-1] << std::endl;
    }

    //Searching
    void searchName(std::string name){
        int count = 0;
        searchNameHelp(this->root, name, count);
        if (count == 0)
           std::cout << "unsuccessful" << std::endl;
    }

    void searchID(int id){
        int count = 0;
        searchIDHelp(this->root, id, count, true);
        if (count == 0)
            std::cout << "unsuccessful" << std::endl;
    }

    void removeID(int id){
        int count = 0;
        searchIDHelp(this->root, id, count, false);
        if (count == 0)
            std::cout << "unsuccessful" << std::endl;
        else{
            this->root = removeIDHelp(this->root, id);
            std::cout << "successful" << std::endl;
        }
    }

    void removeInorder(int n){
        int count = 0;
        removeInorderHelper(this->root, n, count);
    }

    void printLevelCount(){
        int levels = getHeight(this->root);
        std::cout << levels << std::endl;
    }

    bool checkDuplicatesHelp(Node* node, int id){
        if (node == nullptr)
            return false;
        else {
            if(node->idNum == id) {
                return true;
            }
            checkDuplicatesHelp(node->left, id);
            checkDuplicatesHelp(node->right, id);
        }
    }
    bool checkDuplicates(int id){
        int count = 0;
        searchIDHelp(this->root, id, count, false);
        if (count == 0)
            return false;
        return true;
        //return checkDuplicatesHelp(this->root, id);
    }
};
