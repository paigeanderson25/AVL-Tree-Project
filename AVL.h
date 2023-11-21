#pragma once
#include <string>
#include <vector>
using namespace std;

struct Node {
    string name;
    int gatorId;
    int height;
    Node* left;
    Node* right;
    Node() : name(""), gatorId(0), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private: //helper functions do the behind the scenes work & handle memory
    // helperinsert --> if root = nullptr then set node to root; else traverse and insert
    Node* HelperInsert(Node* currNode, Node* insertedNode);

    // height/balancing factor
    int GetMaxHeight(Node* node);
    int GetBalancingFactor(Node* node);

    // balance tree (pass in currNode) --> use recursion for each node; 4 balancing operations (left rotate and right rotate functions)
    Node* BalanceTree(Node* node, bool isRight);
    Node* RotateLeft(Node* node);
    Node* RotateRight(Node* node);

    // print helper
    void HelperPrintInorder(Node* root);
    void HelperPrintPreorder(Node* root);
    void HelperPrintPostorder(Node* root);
    int HelperPrintLevelCount();

    // helper search
    Node* HelperSearchID(Node* root, int &gatorID);
    string HelperReturnIDName(int &gatorID);
    void HelperSearchName(Node* root, string &name);
    void SetNameFound(bool value);
    bool GetNameFound();

    // helper remove
    Node* HelperRemoveID(Node* node, int &gatorID);
    Node* HelperRemoveNth(Node* node, int n, vector<Node*> &nodeVector);




    // variables
    Node* root;
    bool nameFound;
    vector<Node*> nodeVector;



public: //public functions used in main

    // insert constructor
    AVLTree() : root(nullptr), nameFound(false) {}

    // insert destructor

    // get root
    Node* GetRoot();
    void SetRoot(Node* newRoot);

    // insert
    void Insert(string name, int gatorId);

    // print functions
    void PrintInorder();
    void PrintPreorder();
    void PrintPostorder();
    void PrintLevelCount();

    // search functions
    void SearchID(int &gatorID);
    void SearchName(string &name);

    // remove functions
    void RemoveID(int &gatorID);
    Node* CreateVector(Node* node, vector<Node*> &nodeVector);
    void RemoveNthID(int &n);






};



