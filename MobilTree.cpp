#include "MobilTree.h"
#include <algorithm> 

MobilTree::MobilTree() {
    root = new Node("Database"); 
}

MobilTree::~MobilTree() {
    deleteTree(root);
}

// FIX: Password tepat 8 karakter
string MobilTree::inputPassword() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) { 
            if (password.length() == 8) { cout << endl; break; }
            else { cout << "\n[!] Wajib 8 karakter! Ulangi: "; password = ""; }
        }
        else if (ch == 8) { 
            if (!password.empty()) { password.pop_back(); cout << "\b \b"; }
        }
        else if (password.length() < 8) {
            password += ch; cout << '*';
        }
    }
    return password;
}

// Fitur Baru: Lihat semua akun yang terdaftar
void MobilTree::printUsers() {
    cout << "\n--- DAFTAR USER TERDAFTAR ---\n";
    for (size_t i = 0; i < userDB.size(); i++) {
        cout << i + 1 << ". " << userDB[i].username << " [" << userDB[i].role << "]\n";
    }
}

// Fitur Baru: Kelola Riwayat Sewa
void MobilTree::tambahRiwayat(string info) {
    riwayatSewa.push_back(info);
}

void MobilTree::lihatRiwayat() {
    cout << "\n--- DAFTAR USER YANG SUDAH MEMESAN ---\n";
    if (riwayatSewa.empty()) cout << "Belum ada pesanan.\n";
    else {
        for (const string& s : riwayatSewa) cout << "- " << s << endl;
    }
}

void MobilTree::registerUser() {
    string u, p;
    cout << "\n--- REGISTRASI AKUN BARU ---\n";
    cout << "Username: "; getline(cin, u);
    cout << "Password (Pas 8 karakter): ";
    p = inputPassword();
    userDB.push_back({u, p, "customer"});
    cout << "[Success] Akun '" << u << "' terdaftar.\n";
}

void MobilTree::initCarData() {
    root->subTree = insertBST(root->subTree, "SUV");
    root->subTree = insertBST(root->subTree, "Sedan");
    root->subTree = insertBST(root->subTree, "MPV");
    root->subTree = insertBST(root->subTree, "Electric");
    root->subTree = insertBST(root->subTree, "Sport");

    addChild("SUV", "Toyota"); addChild("Toyota", "Fortuner"); addChild("Toyota", "Land Cruiser");
    addChild("SUV", "Mitsubishi"); addChild("Mitsubishi", "Pajero Sport");
    addChild("Sedan", "Honda"); addChild("Honda", "Civic RS"); 
    addChild("Sedan", "BMW"); addChild("BMW", "M3 Competition");
    addChild("MPV", "Toyota"); addChild("Toyota", "Alphard"); addChild("Toyota", "Avanza");
    addChild("MPV", "Hyundai"); addChild("Hyundai", "Stargazer");
    addChild("Electric", "Tesla"); addChild("Tesla", "Model 3");
    addChild("Sport", "Porsche"); addChild("Porsche", "911 GT3");
}

// Logika Save & Load
void MobilTree::saveRecursive(Node* currentRoot, string parentName, ofstream& file) {
    if (!currentRoot) return;
    file << parentName << "|" << currentRoot->name << endl;
    saveRecursive(currentRoot->subTree, currentRoot->name, file);
    saveRecursive(currentRoot->left, parentName, file);
    saveRecursive(currentRoot->right, parentName, file);
}

void MobilTree::saveToFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        if (root->subTree) saveRecursive(root->subTree, "Database", file);
        file.close();
    }
}

void MobilTree::loadFromFile(string filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                string parent = line.substr(0, pos);
                string child = line.substr(pos + 1);
                if (parent == "Database") root->subTree = insertBST(root->subTree, child);
                else {
                    Node* pNode = search(parent);
                    if (pNode) pNode->subTree = insertBST(pNode->subTree, child);
                }
            }
        }
        file.close();
    } else {
        initCarData(); 
    }
}

// Fungsi BST Asli (Tidak diubah)
Node* MobilTree::insertBST(Node* currentRoot, string data) {
    if (currentRoot == nullptr) return new Node(data);
    if (data < currentRoot->name) currentRoot->left = insertBST(currentRoot->left, data);
    else if (data > currentRoot->name) currentRoot->right = insertBST(currentRoot->right, data);
    return currentRoot;
}

Node* MobilTree::searchGlobalRecursive(Node* currentRoot, string target) {
    if (currentRoot == nullptr) return nullptr;
    if (currentRoot->name == target) return currentRoot;
    Node* found = searchGlobalRecursive(currentRoot->subTree, target);
    if (found) return found;
    found = searchGlobalRecursive(currentRoot->left, target);
    if (found) return found;
    return searchGlobalRecursive(currentRoot->right, target);
}

Node* MobilTree::search(string target) { return searchGlobalRecursive(root, target); }

void MobilTree::addChild(string parentName, string childName) {
    Node* p = search(parentName);
    if (p) p->subTree = insertBST(p->subTree, childName);
}

void MobilTree::removeNode(string target) {
    root->subTree = deleteNodeBST(root->subTree, target);
}

Node* findMin(Node* node) {
    while (node && node->left != nullptr) node = node->left;
    return node;
}

Node* MobilTree::deleteNodeBST(Node* currentRoot, string target) {
    if (currentRoot == nullptr) return currentRoot;
    if (target < currentRoot->name) currentRoot->left = deleteNodeBST(currentRoot->left, target);
    else if (target > currentRoot->name) currentRoot->right = deleteNodeBST(currentRoot->right, target);
    else {
        if (currentRoot->subTree != nullptr) return currentRoot;
        if (currentRoot->left == nullptr) { Node* temp = currentRoot->right; delete currentRoot; return temp; }
        else if (currentRoot->right == nullptr) { Node* temp = currentRoot->left; delete currentRoot; return temp; }
        Node* temp = findMin(currentRoot->right);
        currentRoot->name = temp->name;
        currentRoot->right = deleteNodeBST(currentRoot->right, temp->name);
    }
    return currentRoot;
}

void MobilTree::printTreeRecursive(Node* currentRoot, int depth) {
    if (!currentRoot) return;
    printTreeRecursive(currentRoot->left, depth);
    for (int i = 0; i < depth; i++) cout << "    ";
    if (depth == 0) cout << ">> " << currentRoot->name << " (Kategori)\n";
    else if (currentRoot->subTree != nullptr) cout << "- " << currentRoot->name << " (Brand)\n";
    else cout << "  - " << currentRoot->name << " (Unit)\n";
    printTreeRecursive(currentRoot->subTree, depth + 1);
    printTreeRecursive(currentRoot->right, depth);
}

void MobilTree::printKatalog() {
    if (!root->subTree) cout << "[!] Kosong.\n";
    else printTreeRecursive(root->subTree, 0);
}

int MobilTree::getSafeInt() {
    int x;
    while (!(cin >> x)) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "[!] Masukkan angka: ";
    }
    cin.ignore(1000, '\n');
    return x;
}

void MobilTree::initUsers() { 
    userDB.push_back({"admin", "admin123", "admin"}); 
}

Account* MobilTree::login(string u, string p) {
    for (auto &acc : userDB) if (acc.username == u && acc.password == p) return &acc;
    return nullptr;
}

void MobilTree::getStatistics() {
    cout << "Total Item: " << countNodes(root->subTree) << endl;
}

int MobilTree::countNodes(Node* r) {
    if (!r) return 0;
    return 1 + countNodes(r->left) + countNodes(r->right) + countNodes(r->subTree);
}

void MobilTree::deleteTree(Node* currentRoot) {
    if (!currentRoot) return;
    deleteTree(currentRoot->subTree);
    deleteTree(currentRoot->left);
    deleteTree(currentRoot->right);
    delete currentRoot;
}