#include "MobilTree.h"
#include <algorithm> 
#include <fstream> 

MobilTree::MobilTree() {
    root = new Node("Database"); 
}

MobilTree::~MobilTree() {
    deleteTree(root);
    cout << "\n[Cleanup] Seluruh memori tree telah dibebaskan.\n";
}

int MobilTree::getSafeInt() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[!] Input salah! Masukkan angka menu: ";
    }
    cin.ignore(1000, '\n');
    return x;
}

bool MobilTree::validatePassword(string p) {
    return p.length() >= 8;
}

int MobilTree::countNodes(Node* r) {
    if (!r) return 0;
    return 1 + countNodes(r->left) + countNodes(r->right) + countNodes(r->subTree);
}

void MobilTree::getStatistics() {
    int total = countNodes(root->subTree);
    cout << "\n--- STATISTIK DATABASE ---" << endl;
    cout << "Total Item (Kategori/Brand/Unit): " << total << " item" << endl;
}

string MobilTree::inputPassword() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();
        
        if (ch == 13) { 
            if (password.length() < 8) {
                cout << "\n[!] Password harus tepat 8 karakter!";
            }
            cout << endl;
            break;
        }
        else if (ch == 8) { 
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }

        else {
            if (password.length() < 8) {
                password += ch;
                cout << '*';
            }
        }
    }
    return password;
}

void MobilTree::printUsers() {
    cout << "\n--- LIST USER ---\n";
    for (const auto& u : userDB) {
        cout << "User: " << u.username << " | Role: " << u.role << endl;
    }
}

void MobilTree::initUsers() {
    userDB.push_back({"admin", "admin123", "admin"});
    userDB.push_back({"user", "user12345678", "customer"});
}

Account* MobilTree::login(string u, string p) {
    for (int i = 0; i < userDB.size(); i++) {
        if (userDB[i].username == u && userDB[i].password == p) {
            return &userDB[i]; 
        }
    }
    return nullptr; 
}

void MobilTree::registerUser() {
    string u, p;
    cout << "\n--- BUAT AKUN BARU ---\n";
    cout << "Username: "; getline(cin, u);

    for (const auto& acc : userDB) {
        if (acc.username == u) {
            cout << "[!] Username sudah terpakai!\n";
            return;
        }
    }

    while (true) {
        cout << "Password (Harus 8 karakter): ";
        p = inputPassword();
        if (p.length() == 8) break;
        cout << "[!] Password kurang dari 8 karakter! Ulangi.\n";
    }

    userDB.push_back({u, p, "customer"});
    cout << "[Success] Registrasi berhasil! Akun '" << u << "' siap digunakan.\n";
}

Node* MobilTree::insertBST(Node* currentRoot, string data) {
    if (currentRoot == nullptr) return new Node(data);
    if (data < currentRoot->name) { 
        currentRoot->left = insertBST(currentRoot->left, data);
    }
    else if (data > currentRoot->name) { 
        currentRoot->right = insertBST(currentRoot->right, data);
    }
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

Node* MobilTree::search(string target) {
    return searchGlobalRecursive(root, target);
}

void MobilTree::printTreeRecursive(Node* currentRoot, int depth) {
    if (!currentRoot) return;
    printTreeRecursive(currentRoot->left, depth);
    for (int i = 0; i < depth; i++) cout << "    ";
    if (depth == 0) cout << ">> " << currentRoot->name << " (Kategori)\n";
    else if (currentRoot->subTree != nullptr) cout << "- " << currentRoot->name << " (Brand/Tipe)\n";
    else cout << "  - " << currentRoot->name << " (Model Unit)\n";

    printTreeRecursive(currentRoot->subTree, depth + 1);
    printTreeRecursive(currentRoot->right, depth);
}

void MobilTree::printKatalog() {
    if (root->subTree == nullptr) {
        cout << "[!] Database kosong. Silahkan tambahkan data.\n";
        return;
    }
    cout << "\n=== KATALOG MOBIL (TREE VIEW) ===\n";
    printTreeRecursive(root->subTree, 0); 
}

void MobilTree::addChild(string parentName, string childName) {
    Node* parent = search(parentName);
    if (parent != nullptr) {
        parent->subTree = insertBST(parent->subTree, childName); 
        cout << "[Success] Data '" << childName << "' berhasil ditambahkan di bawah '" << parentName << "'.\n";
    } else {
        cout << "[!] Induk '" << parentName << "' tidak ditemukan!\n";
    }
}

void MobilTree::initCarData() {
    root->subTree = insertBST(root->subTree, "SUV");
    root->subTree = insertBST(root->subTree, "Sport");
    root->subTree = insertBST(root->subTree, "Sedan");

    addChild("Sport", "Mazda");
    addChild("Sport", "Honda");
    addChild("Sport", "Toyota");
    addChild("SUV", "Fortuner");
    addChild("SUV", "HR-V");
    addChild("Mazda", "RX-7");
    addChild("Honda", "Civic Type R");
    addChild("Toyota", "Supra");
    addChild("Sedan", "Civic");
}

Node* findMin(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* MobilTree::deleteNodeBST(Node* currentRoot, string target) {
    if (currentRoot == nullptr) return currentRoot;
    if (target < currentRoot->name) {
        currentRoot->left = deleteNodeBST(currentRoot->left, target);
    } 
    else if (target > currentRoot->name) {
        currentRoot->right = deleteNodeBST(currentRoot->right, target);
    } 
    else {
        if (currentRoot->subTree != nullptr) {
            cout << "[!] Gagal menghapus. Node '" << target << "' masih memiliki data unit di dalamnya.\n";
            return currentRoot; 
        }
        if (currentRoot->left == nullptr) {
            Node* temp = currentRoot->right;
            delete currentRoot;
            return temp;
        } 
        else if (currentRoot->right == nullptr) {
            Node* temp = currentRoot->left;
            delete currentRoot;
            return temp;
        }
        Node* temp = findMin(currentRoot->right);
        currentRoot->name = temp->name; 
        currentRoot->right = deleteNodeBST(currentRoot->right, temp->name); 
    }
    return currentRoot;
}

void MobilTree::removeNode(string target) {
    if (target == root->name) {
        cout << "[!] Tidak dapat menghapus root database utama.\n";
        return;
    }
    Node* newRootSubTree = deleteNodeBST(root->subTree, target);
    if (newRootSubTree != root->subTree) {
        root->subTree = newRootSubTree; 
        cout << "[Success] Data '" << target << "' berhasil dihapus.\n";
    }
}

void MobilTree::deleteTree(Node* currentRoot) {
    if (currentRoot == nullptr) return;
    deleteTree(currentRoot->subTree);
    deleteTree(currentRoot->left);
    deleteTree(currentRoot->right);
    delete currentRoot;
}