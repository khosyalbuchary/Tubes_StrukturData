#ifndef MOBILTREE_H
#define MOBILTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <conio.h> // Untuk _getch()

using namespace std;

// --- STRUKTUR DATA ---

struct Account {
    string username;
    string password;
    string role; // "admin" atau "customer" [cite: 283, 284]
};

struct Node {
    string name; // Nama Kategori, Brand, atau Model [cite: 278]
    Node *left, *right; // Sibling Nodes (untuk BST) [cite: 279, 280]
    Node *subTree; // Child Nodes (untuk level di bawahnya) [cite: 281, 282]

    Node(string n) {
        name = n;
        left = right = subTree = nullptr;
    }
};

// --- KELAS UTAMA ---

class MobilTree {
private:
    Node* root;
    vector<Account> userDB; // Database Akun [cite: 285]

    // Fungsi Helper BST
    Node* insertBST(Node* currentRoot, string data);
    void printTreeRecursive(Node* currentRoot, int depth);
    Node* searchGlobalRecursive(Node* currentRoot, string target);
    Node* deleteNodeBST(Node* currentRoot, string target);
    void deleteTree(Node* currentRoot); // Untuk mencegah Memory Leak [cite: 301]

public:
    MobilTree();
    ~MobilTree(); // Destructor untuk membersihkan memori

    // Fungsi Utama Tree
    void initCarData();
    void printKatalog();
    void addChild(string parentName, string childName);
    Node* search(string target);
    void removeNode(string target);
    
    // Fungsi Autentikasi
    void initUsers();
    Account* login(string u, string p);
    void registerUser();

    // Fungsi Utility
    string inputPassword();
    void printUsers();
};

#endif // MOBILTREE_H