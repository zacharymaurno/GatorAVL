#include <string>
#include <iostream>
class Tree{
private:
    struct Node{int idNum;
        std::string name;
        Node *left;
        Node *right;
        int balanceFactor; //Difference in height between left and right subtree
    };
    Tree *headNode;
    int nodeCount;
    Node* root;

public:
    Node* curNode;
    //Constructors
    Tree(){
        this->root = nullptr;
        nodeCount = 0;
        //this->root->left = NULL;
        //this->root->right = NULL;
    }

    //Insert and Remove
    Node* insertHelp(Node *node, std::string nameStudent, int id){
        if (node == nullptr){
            Node *n;
            n = new Node;
            n->name = nameStudent;
            n->idNum = id;
            node = n;
            node->left = node->right = nullptr;
            //root->balanceFactor = findBalanceFactor(node);
            return node;
        }

            if(id < (node->idNum))
                node->left = insertHelp(node->left, nameStudent, id);
            else{
                std::cout << "right side" << std::endl;
                node->right = insertHelp(node->right, nameStudent, id);
            }

    }
    Node* insertNameID(std::string nameStudent, int id){
        Node* temp = this->root;
        if (root == nullptr) {
            std::cout << "New Root";
            Node* n;
            n = new Node;
            n->name = nameStudent;
            n->idNum = id;
            root = n;
            //root->left = root->right = nullptr;
            //root->balanceFactor = findBalanceFactor(node);
            return root;
        }
        return insertHelp(root, nameStudent, id);
        /*if (root == nullptr){
            Node *n;
            n = new Node;
            n->name = nameStudent;
            n->idNum = id;
            root = n;
            root->left = root->right = nullptr;
            //root->balanceFactor = findBalanceFactor(node);
            return root;
        }

        else if (node == nullptr){
            Node *n;
            n = new Node;
            n->name = nameStudent;
            n->idNum = id;
            node = n;
            node->left = node->right = nullptr;
            //root->balanceFactor = findBalanceFactor(node);
            return node;
        }
        else{
            if(id < (node->idNum))
                node->left = insertNameID(node->left, nameStudent, id);
            else
                node->right = insertNameID(node->right, nameStudent, id);
        } */

    }
    void removeID(int idNum);
    void removeInorderN();

    //Searching
    bool searchID(int idNum);
    bool searchName(std::string name);

    //Traversals
    void inorderHelp(Node* node){
        if (node == nullptr){
            return;
        }
        inorderHelp(node->left);
        std::string nameCur = node->name;
        std::cout <<  nameCur << ", ";
        inorderHelp(node->right);
    }
    void printInorder(){
        Node* temp = root;
        inorderHelp(temp);
        std::cout << std::endl;
    }
    void printPreorder();
    void printPostOrder();

    void printLevelCount();

    int findBalanceFactor(Node* node);

    //Rotations
    /* Left
     Right
     Left-Right
     Right-Left*/
};

//Node* Tree::insertNameID(Node* root, std::string name, int idNum) {
  //  if(root = nullptr)
//};

/*
int Tree::findBalanceFactor(Node *node) {
    int left = 0;
    int right = 0;
    while(node->left != nullptr){
        left++;
        node = node->left;
    }
    while(node->right != nullptr){
        right++;
        node = node->right;
    }
    return (left-right);
}*/