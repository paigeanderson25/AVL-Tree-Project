#include <iostream>
#include <sstream>
#include <string>
#include "AVL.h"
using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/
bool verifyId(string &id);
bool verifyName(string &name);

int main(){
    int numCommands = 0;
    cin >> numCommands;

    AVLTree tree = AVLTree();

    for (int i = 0; i <= numCommands; i++) {
        //take in input and assign to input string
        string inputLine;
        getline(cin, inputLine);

        //create input stream
        istringstream input(inputLine);

        //take in command
        string command;
        input >> command;


        // if statement based on commands
        if (command == "insert") {
           //read up to next quotation
           string name;
           getline(input, name, '"');
           getline(input, name, '"');

           string id;
           input >> id;

            int gatorID;
            gatorID = stoi(id);

           //check UFID 8 digits long & name contains a-z, A-Z, and spaces
           if (!verifyId(id) || !verifyName(name)) {
               cout << "Unsuccessful" << endl;
           }
           else {
               tree.Insert(name, gatorID);
           }

        }
        else if (command == "printLevelCount") {
            tree.PrintLevelCount();
        }
        else if (command == "printInorder") {
            tree.PrintInorder();
        }
        else if (command == "printPreorder") {
            tree.PrintPreorder();
        }
        else if (command == "printPostorder") {
            tree.PrintPostorder();
        }
        else if (command == "search") {
            string searchType = "";
            int quoteLoc = -1;
            quoteLoc = inputLine.find("\"");
            if (quoteLoc == -1) {
                input >> searchType;
            }
            else {
                getline(input, searchType, '"');
                getline(input, searchType, '"');
            }

            if (isalpha(searchType.at(0))) {
                string searchName = searchType;
                if (verifyName(searchType)) {
                    tree.SearchName(searchName);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                int searchGatorID = 0;
                if (verifyId(searchType)) {
                    searchGatorID = stoi(searchType);
                    tree.SearchID(searchGatorID);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
        }
        else if (command == "remove") {
            string removeIDString = "";
            input >> removeIDString;
            if (verifyId(removeIDString)) {
                int removeID = 0;
                removeID = stoi(removeIDString);
                tree.RemoveID(removeID)  ;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command == "removeInorder") {
            string indexString = "";
            input >> indexString;
            int index = stoi(indexString);
            tree.RemoveNthID(index);
        }
    }

	return 0;
}

// verify id is 8 digits long
bool verifyId(string &id) {
    if (id.length() == 8) {
        for (int i = 0; i < id.length(); i++) {
            if (isdigit(id.at(i))) {
                continue;
            }
            else {
                return false;
            }
        }


        return true;
    }
    else {
        return false;
    }
}

//verify name contains appropriate characters
bool verifyName(string &name) {
    for (int i = 0; i < name.length(); i++) {
        if (isalpha(name.at(i)) || isspace(name.at(i))) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

