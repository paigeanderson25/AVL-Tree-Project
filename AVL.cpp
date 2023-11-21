#include "AVL.h"
#include <iostream>
#include "test.cpp"
using namespace std;

//insert node helper function
Node* AVLTree::HelperInsert(Node* currNode, Node* insertedNode) {
    // if currNode == nullptr then currNode set equal to inserted node and the inserted node is returned
    bool isRight = true;
    if (root == nullptr) {
        root = insertedNode;
    }
    if (currNode == nullptr) {
        currNode = insertedNode;
        return insertedNode;
    }
    else {
        // if duplicate gator IDs exist return nullptr (error)

       if (currNode->gatorId == insertedNode->gatorId) {
           return nullptr;
       }
       else {
           // traverse through tree; once spot for inserted node is reached, insert node --> ; currNode stays parent node;
           if (insertedNode->gatorId > currNode->gatorId) {
               currNode->right = HelperInsert(currNode->right, insertedNode);
               isRight = true;
               if (currNode->right == nullptr) {
                   return nullptr;
               }
           }
           else {
               currNode->left = HelperInsert(currNode->left, insertedNode);
               isRight = false;
               if (currNode->left == nullptr) {
                   return nullptr;
               }
           }
       }

    }

    // update heights
    currNode->height = GetMaxHeight(currNode) + 1;

    int balanceFactor = 0;
    balanceFactor = GetBalancingFactor(currNode);

    // perform balance operations
    if (balanceFactor == 2 || balanceFactor == -2) {
        currNode = BalanceTree(currNode, isRight);
        return currNode;
    }
    else {
        return currNode;
    }

}

// pass in node and return whichever height is larger (left or right)
int AVLTree::GetMaxHeight(Node *node) {
    int leftHeight = 0;
    int rightHeight = 0;

    // if no left child nodes, set height to 0; else set left height to node left height
    if (node->left == nullptr) {
        leftHeight = 0;
    }
    else {
        leftHeight = node->left->height;
    }

    // if no right child nodes, set height to 0; else set right height to node right height
    if (node->right == nullptr) {
        rightHeight = 0;
    }
    else {
        rightHeight = node->right->height;
    }

    // return greatest height value
    if (rightHeight > leftHeight) {
        return rightHeight;
    }
    else {
        return leftHeight;
    }

}

// pass in node and return balancing factor (left height - right height)
int AVLTree::GetBalancingFactor(Node* node) {
    int balanceFactor = 0;
    int leftHeight = 0;
    if (node->left == nullptr) {
        leftHeight = 0;
    }
    else {
        leftHeight = node->left->height;
    }
    int rightHeight = 0;
    if (node->right == nullptr) {
        rightHeight = 0;
    }
    else {
        rightHeight = node->right->height;
    }
    balanceFactor = leftHeight - rightHeight;
    return balanceFactor;
}

// pass in node; perform left rotation about its child node; return new center node
Node* AVLTree::RotateLeft(Node* node) {
    Node* centerNode = node->right;
    Node* tempNode = centerNode->left;
    centerNode->left = node;
    node->right = tempNode;

    node->height = GetMaxHeight(node) + 1;
    centerNode->height = GetMaxHeight(centerNode) + 1;


    return centerNode;
}

// pass in node; perform right rotation about its child node; return new center node
Node* AVLTree::RotateRight(Node *node) {
    Node* centerNode = node->left;
    Node* tempNode = centerNode->right;
    centerNode->right = node;
    node->left = tempNode;

    node->height = GetMaxHeight(node) + 1;
    centerNode->height = GetMaxHeight(centerNode) + 1;

    return centerNode;
}

// perform rotations based on heights; call left and right rotations using if statement
Node* AVLTree::BalanceTree(Node* node, bool isRight) {
    // determine balancing factor
    Node* currNode = nullptr;

    int parentBF = 0;
    parentBF = GetBalancingFactor(node);

    int childBF = 0;
    //Node* childNode = nullptr;
    if (isRight) {
        //childNode = node->right;
        childBF = GetBalancingFactor(node->right);
    }
    else {
        //childNode = node->left;
        childBF = GetBalancingFactor(node->left);
    }

    // if statement: based on balancing factor of node and child node
    if (parentBF == 2 && childBF == 1) {
        // right
        node = RotateRight(node);
    }
    else if (parentBF == -2 && childBF == -1) {
        // left
        node = RotateLeft(node);
    }
    else if (parentBF == 2 && childBF == -1) {
        // left right
        node->left = RotateLeft(node->left);
        node = RotateRight(node);
    }
    else if (parentBF == -2 && childBF == 1) {
        // right left
        node->right = RotateRight(node->right);
        node = RotateLeft(node);
    }
    /*if (node == root) {
        root = childNode;
    } */
    return node;
}

// print helper

// pass in root node; recursively print nodes in order
void AVLTree::HelperPrintInorder(Node* root) {
    if (root->left != nullptr) {
        HelperPrintInorder(root->left);
        cout << ", ";
    }
    cout << root->name;
    if (root->right != nullptr) {
        cout << ", ";
        HelperPrintInorder(root->right);
    }
}

// pass in root node; recursively print nodes in preorder
void AVLTree::HelperPrintPreorder(Node* root) {
    cout << root->name;
    if (root->left != nullptr) {
        cout << ", ";
        HelperPrintPreorder(root->left);
    }
    if (root->right != nullptr) {
        cout << ", ";
        HelperPrintPreorder(root->right);
    }
}

// pass in root node; recursively print nodes postorder
void AVLTree::HelperPrintPostorder(Node* root) {
    if (root->left != nullptr) {
        HelperPrintPostorder(root->left);
        cout << ", ";
    }
    if (root->right != nullptr) {
        HelperPrintPostorder(root->right);
        cout << ", ";
    }
    cout << root->name;
}

// return height of root (if nullptr return 0)
int AVLTree::HelperPrintLevelCount() {
    Node* root = GetRoot();
    int levelCount = 0;
    if (root == nullptr) {
        return levelCount;
    }
    else {
        levelCount = root->height;
        return levelCount;
    }
}

// helper search
// search ID (pass in node and ID to be searched for) --> returns node with matching id; if no match returns nullptr
Node* AVLTree::HelperSearchID(Node* root, int &gatorID) {
    if (root == nullptr) {
        return root;
    }
    if (root->gatorId == gatorID) {
        return root;
    }
    else {
        if (gatorID > root->gatorId) {
            HelperSearchID(root->right, gatorID);
        }
        else {
            HelperSearchID(root->left, gatorID);
        }
    }

}

// uses helper search ID to return name to public search ID function
string AVLTree::HelperReturnIDName(int &gatorID) {
    Node* root = GetRoot();
    Node* nameNode = HelperSearchID(root, gatorID);
    if (nameNode == nullptr) {
        return "unsuccessful";
    }
    else {
        return nameNode->name;
    }
}

// traverse across entire tree using pre order traversal--> if root->name == print ID
void AVLTree::HelperSearchName(Node* root, string &name) {
    if (root == nullptr) {
        return;
    }
    else {
        if (root->name == name) {
            cout << root->gatorId << endl;
            SetNameFound(true);
        }
        if (root->left != nullptr) {
            HelperSearchName(root->left, name);
        }
        if (root->right != nullptr) {
            HelperSearchName(root->right, name);
        }
    }
}

// functions to determine if name exists or not
void AVLTree::SetNameFound(bool value) {
    if (value == false) {
        nameFound = false;
    }
    else {
        nameFound = true;
    }
}
bool AVLTree::GetNameFound() {
    return nameFound;
}

// remove functions
// remove node with given gator ID
Node* AVLTree::HelperRemoveID(Node* root, int &gatorID) {

    if (gatorID == root->gatorId) {
        // remove node with no children
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // remove node two children
        else if (root->left != nullptr && root->right != nullptr) {
            Node* succNode = root->right;
            while (succNode->left != nullptr) {
            succNode = succNode->left;
            }
            Node* node = new Node();
            node->gatorId = succNode->gatorId;
            node->name = succNode->name;
            root->right = HelperRemoveID(root->right, succNode->gatorId);
            node->left = root->left;
            node->right = root->right;
            delete root;
            return node;
        }
        // remove node with one child
         else {
            Node* tempNode = nullptr;
             if (root->left != nullptr) {
                tempNode = root->left;
                delete root;
                return tempNode;
            }
            else {
                tempNode = root->right;
                delete root;
                return tempNode;
            }
         }
    }
    else {
        // gator id for removed node is less than root
        if (gatorID < root->gatorId) {
            root->left = HelperRemoveID(root->left, gatorID);
        }
        // gator id for removed node is greater than root
        else {
            root->right = HelperRemoveID(root->right, gatorID);
        }
    }
    return root;
}


Node* AVLTree::CreateVector(Node* node, vector<Node*> &nodeVector) {
    if (node != nullptr) {
        CreateVector(node->left, nodeVector);
        nodeVector.push_back(node);
        CreateVector(node->right, nodeVector);
    }
    else {
        cout << "";
    }
}
Node* AVLTree::HelperRemoveNth(Node *root, int n, vector<Node*> &nodeVector) {
    Node* node = CreateVector(root, nodeVector);
    if (nodeVector.size() > n) {
        Node* removedNode = nodeVector.at(n);
        int removedID = removedNode->gatorId;
        SetRoot(HelperRemoveID(root, removedID));
        return root;
    }
    else {
        return nullptr;
    }

}



// public functions
// get root
Node* AVLTree::GetRoot() {
    return root;
}

void AVLTree::SetRoot(Node* newRoot) {
    root = newRoot;
}

// insert node
void AVLTree::Insert(string name, int gatorId) {
    // call helper function to create and insert a new node --> if returns nullptr print unsuccessful
    Node* insertedNode = new Node;
    insertedNode->name = name;
    insertedNode->gatorId = gatorId;

    Node* helperValue = nullptr;
    helperValue = HelperInsert(root, insertedNode);

    if (helperValue == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    else {
        root = helperValue;
        cout << "successful" << endl;
    }
}


// print functions
// print tree in order using helper
void AVLTree::PrintInorder() {
    Node* root = GetRoot();
    if (root != nullptr) {
        HelperPrintInorder(root);
    }
    cout << endl;
}

//print tree pre order using helper
void AVLTree::PrintPreorder() {
    Node* root = GetRoot();
    if (root != nullptr) {
        HelperPrintPreorder(root);
    }
    cout << endl;
}

//print tree post order using helper
void AVLTree::PrintPostorder() {
    Node* root = GetRoot();
    if (root != nullptr) {
        HelperPrintPostorder(root);
    }
    cout << endl;
}

// print tree level count using helper
void AVLTree::PrintLevelCount() {
       cout << HelperPrintLevelCount() << endl;
}


// search functions
void AVLTree::SearchID(int &gatorID) {
    string name = HelperReturnIDName(gatorID);
    cout << name << endl;
}
void AVLTree::SearchName(string &name) {
    Node* root = GetRoot();
    HelperSearchName(root, name);
    if (!GetNameFound()) {
        cout << "unsuccessful" << endl;
    }
    else {
        SetNameFound(false);
    }
}

// remove functions
// remove passed in ID
void AVLTree::RemoveID(int &gatorID) {
    Node* root = GetRoot();
    Node* node = HelperSearchID(root, gatorID);
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
    }
    else {
        SetRoot(HelperRemoveID(root, gatorID));
        cout << "successful" << endl;
    }
}

// remove ID at nth location if it exists
void AVLTree::RemoveNthID(int &n) {
    // perform inorder traversal nodeVector
    Node* root = GetRoot();
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
    }
    else {
       root = HelperRemoveNth(root, n, nodeVector);
       if (root == nullptr) {
            cout << "unsuccessful" << endl;
        }
        else {
            cout << "successful" << endl;

        }
    }
    nodeVector.clear();

}


















