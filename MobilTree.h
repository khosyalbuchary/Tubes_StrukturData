#ifndef MOBILTREE_H
#define MOBILTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 

using namespace std;

struct Account {
    string username;
    string password;
    string role; 
};

struct Node {
    string name; 
    Node *left, *right; 
    Node *subTree; 
    Node(string n) {
        name = n;
        left = right = subTree = nullptr;
    }
};

class MobilTree {
private:
    Node* root;
    vector<Account> userDB; 

    Node* insertBST(Node* currentRoot, string data);
    void printTreeRecursive(Node* currentRoot, int depth);
    Node* searchGlobalRecursive(Node* currentRoot, string target);
    Node* deleteNodeBST(Node* currentRoot, string target);
    void deleteTree(Node* currentRoot); 

public:
    MobilTree();
    ~MobilTree(); 

    void initCarData();
    void printKatalog();
    void addChild(string parentName, string childName);
    Node* search(string target);
    void removeNode(string target);

    void initUsers();
    Account* login(string u, string p);
    void registerUser();

    string inputPassword();
    void printUsers();
    
    bool validatePassword(string p); 
    void getStatistics();            
    int countNodes(Node* r);         
    int getSafeInt();               
};

#endif