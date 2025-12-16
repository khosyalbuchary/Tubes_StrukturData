#include "CarTree.h"
#include <algorithm> // Diperlukan jika ada sorting
#include <fstream> // Diperlukan untuk File Handling (walaupun belum diimplementasikan penuh di sini)

// ==========================================
// KONSTRUKTOR & DESTRUKTOR
// ==========================================

MobilTree::MobilTree() {
    root = new Node("Database"); // Root utama [cite: 272]
}

MobilTree::~MobilTree() {
    // Dipanggil saat program berakhir
    deleteTree(root);
    cout << "\n[Cleanup] Seluruh memori tree telah dibebaskan.\n";
}

// ==========================================
// FUNGSI HELPER (UTILITIES)
// ==========================================

// Fungsi input password dengan masking bintang (*) [cite: 296]
string MobilTree::inputPassword() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) { // Enter
            cout << endl;
            break;
        }
        else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password += ch;
            cout << '*';
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


// ==========================================
// LOGIKA USER (AUTH & REG)
// ==========================================

void MobilTree::initUsers() {
    // Akun default [cite: 283]
    userDB.push_back({"admin", "admin123", "admin"});
    userDB.push_back({"user", "user123", "customer"});
}

Account* MobilTree::login(string u, string p) {
    for (int i = 0; i < userDB.size(); i++) {
        if (userDB[i].username == u && userDB[i].password == p) {
            return &userDB[i]; // Login Berhasil [cite: 296]
        }
    }
    return nullptr; // Login Gagal
}

void MobilTree::registerUser() {
    string u, p;
    cout << "\n--- BUAT AKUN BARU ---\n";
    cout << "Username: "; getline(cin, u);

    // Cek duplikasi username
    for (const auto& acc : userDB) {
        if (acc.username == u) {
            cout << "[!] Username sudah terpakai!\n";
            return;
        }
    }

    cout << "Password: ";
    p = inputPassword();

    userDB.push_back({u, p, "customer"}); // Registrasi berhasil [cite: 286]
    cout << "[Success] Registrasi berhasil! Silahkan login.\n";
}

// ==========================================
// LOGIKA TREE (BST & MULTI-LEVEL)
// ==========================================

// Helper: Menambahkan Node ke BST (rekursif) [cite: 290]
Node* MobilTree::insertBST(Node* currentRoot, string data) {
    if (currentRoot == nullptr) return new Node(data);
    
    // Jika data baru lebih kecil (sebelum) secara alfabetis, pindah ke kiri
    if (data < currentRoot->name) { 
        currentRoot->left = insertBST(currentRoot->left, data);
    }
    // Jika data baru lebih besar (setelah) secara alfabetis, pindah ke kanan
    else if (data > currentRoot->name) { 
        currentRoot->right = insertBST(currentRoot->right, data);
    }
    // Jika sama, abaikan (mencegah duplikasi) [cite: 342]
    return currentRoot;
}

// Helper: Mencari Node di seluruh Multi-Level Tree (rekursif) [cite: 291, 292]
Node* MobilTree::searchGlobalRecursive(Node* currentRoot, string target) {
    if (currentRoot == nullptr) return nullptr;

    // 1. Cek Node saat ini
    if (currentRoot->name == target) return currentRoot;

    // 2. Cari di SubTree (Child) [cite: 281, 282]
    Node* found = searchGlobalRecursive(currentRoot->subTree, target);
    if (found) return found;

    // 3. Cari di Sibling Kiri (BST) [cite: 279, 280]
    found = searchGlobalRecursive(currentRoot->left, target);
    if (found) return found;

    // 4. Cari di Sibling Kanan (BST) [cite: 279, 280]
    return searchGlobalRecursive(currentRoot->right, target);
}

// Implementasi Public Search
Node* MobilTree::search(string target) {
    return searchGlobalRecursive(root, target);
}


// Helper: Traversal In-Order untuk tampilan (rekursif) [cite: 293, 294]
void MobilTree::printTreeRecursive(Node* currentRoot, int depth) {
    if (!currentRoot) return;

    // 1. Traversal Kiri (In-Order)
    printTreeRecursive(currentRoot->left, depth);

    // 2. Proses Node Saat Ini (Root)
    for (int i = 0; i < depth; i++) cout << "    ";
    
    if (depth == 0) cout << ">> " << currentRoot->name << " (Kategori)\n";
    else if (currentRoot->subTree != nullptr) cout << "- " << currentRoot->name << " (Brand/Tipe)\n";
    else cout << "  - " << currentRoot->name << " (Model Unit)\n";


    // 3. Traversal SubTree (Children)
    printTreeRecursive(currentRoot->subTree, depth + 1);

    // 4. Traversal Kanan (In-Order)
    printTreeRecursive(currentRoot->right, depth);
}

// Implementasi Public Print
void MobilTree::printKatalog() {
    if (root->subTree == nullptr) {
        cout << "[!] Database kosong. Silahkan tambahkan data.\n";
        return;
    }
    cout << "\n=== KATALOG MOBIL (TREE VIEW) ===\n";
    // Mulai dari subTree pertama root ("Database")
    printTreeRecursive(root->subTree, 0); 
}


// Menambahkan Child Node ke Parent tertentu [cite: 273]
void MobilTree::addChild(string parentName, string childName) {
    Node* parent = search(parentName); // Cari parent menggunakan search global
    if (parent != nullptr) {
        // Tambahkan child ke subTree parent (menggunakan BST logic)
        parent->subTree = insertBST(parent->subTree, childName); 
        cout << "[Success] Data '" << childName << "' berhasil ditambahkan di bawah '" << parentName << "'.\n";
    } else {
        cout << "[!] Induk '" << parentName << "' tidak ditemukan!\n";
    }
}

// Inisialisasi data mobil awal
void MobilTree::initCarData() {
    // Kategori
    root->subTree = insertBST(root->subTree, "SUV");
    root->subTree = insertBST(root->subTree, "Sport");
    root->subTree = insertBST(root->subTree, "Sedan");

    // Brand/Model (Sub-level)
    addChild("Sport", "Mazda");
    addChild("Sport", "Honda");
    addChild("Sport", "Toyota");
    
    addChild("SUV", "HR-V");
    addChild("SUV", "Fortuner");
    
    // Model Unit (Sub-level dari Brand)
    addChild("Mazda", "RX-7");
    addChild("Honda", "Civic Type R");
    addChild("Toyota", "Supra");
    addChild("Sedan", "Civic");

    cout << "[INFO] Data default telah diinisialisasi.\n";
}

// Helper: Mencari suksesor In-Order (Node terkecil di subTree kanan)
Node* findMin(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Helper: Menghapus Node dari BST (rekursif) [cite: 304]
Node* MobilTree::deleteNodeBST(Node* currentRoot, string target) {
    if (currentRoot == nullptr) return currentRoot;

    // 1. Traverse BST untuk menemukan Node target
    if (target < currentRoot->name) {
        currentRoot->left = deleteNodeBST(currentRoot->left, target);
    } 
    else if (target > currentRoot->name) {
        currentRoot->right = deleteNodeBST(currentRoot->right, target);
    } 
    else {
        // Node ditemukan (currentRoot adalah Node target)
        
        // Cek apakah Node memiliki children (SubTree)
        if (currentRoot->subTree != nullptr) {
            cout << "[!] Gagal menghapus. Node '" << target << "' masih memiliki data unit di dalamnya.\n";
            return currentRoot; // Tidak dihapus
        }
        
        // Kasus 1: Node hanya punya satu anak atau tidak punya anak
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

        // Kasus 2: Node punya dua anak
        Node* temp = findMin(currentRoot->right);
        currentRoot->name = temp->name; // Copy data suksesor
        currentRoot->right = deleteNodeBST(currentRoot->right, temp->name); // Hapus suksesor
    }
    return currentRoot;
}

// Implementasi Public Remove Node
void MobilTree::removeNode(string target) {
    if (target == root->name) {
        cout << "[!] Tidak dapat menghapus root database utama.\n";
        return;
    }
    
    // Coba hapus target dari BST utama (kategori)
    Node* newRootSubTree = deleteNodeBST(root->subTree, target);
    if (newRootSubTree != root->subTree) {
        root->subTree = newRootSubTree; // Update root jika node dihapus dari level 0
        cout << "[Success] Data '" << target << "' berhasil dihapus dari kategori utama.\n";
        return;
    }

    // Jika tidak ditemukan di level 0, cari di level yang lebih dalam (tidak diimplementasikan penuh di sini)
    // Untuk tujuan Tugas Besar, kita fokus pada penghapusan di level teratas/sub-level terdekat.
    
    // Perlu implementasi rekursif untuk mencari Parent node dari Target di Multi-Level Tree
    cout << "[WARNING] Penghapusan data sub-level belum sepenuhnya didukung di versi ini.\n";
}


// Helper: Membersihkan seluruh Tree (rekursif) [cite: 305]
void MobilTree::deleteTree(Node* currentRoot) {
    if (currentRoot == nullptr) return;

    // Hapus SubTree (Child)
    deleteTree(currentRoot->subTree);
    // Hapus Sibling Kiri
    deleteTree(currentRoot->left);
    // Hapus Sibling Kanan
    deleteTree(currentRoot->right);

    // Hapus Node saat ini
    delete currentRoot;
}