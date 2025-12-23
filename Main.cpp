#include "MobilTree.h"

void runAdminSession(MobilTree& manager, Account* user) {
    bool loggedIn = true;
    while (loggedIn) {
        cout << "\n=== DASHBOARD ADMIN (" << user->username << ") ===\n";
        cout << "1. Lihat Database Mobil\n";
        cout << "2. Tambah Data\n";
        cout << "3. Hapus Data\n";
        cout << "4. Lihat User (Akun Terdaftar)\n"; // Menu Baru
        cout << "5. Lihat User Pemesan\n";          // Menu Baru
        cout << "6. Statistik\n";
        cout << "7. Logout\n";
        cout << "Pilih: ";
        int choice = manager.getSafeInt();

        if (choice == 1) manager.printKatalog();
        else if (choice == 2) {
            string p, c;
            cout << "Induk: "; getline(cin, p);
            cout << "Data: "; getline(cin, c);
            manager.addChild(p, c);
        }
        else if (choice == 3) {
            string t; cout << "Hapus: "; getline(cin, t);
            manager.removeNode(t);
        }
        else if (choice == 4) manager.printUsers();
        else if (choice == 5) manager.lihatRiwayat();
        else if (choice == 6) manager.getStatistics();
        else if (choice == 7) loggedIn = false;
    }
}

void runCustomerSession(MobilTree& manager, Account* user) {
    bool loggedIn = true;
    while (loggedIn) {
        cout << "\n=== DASHBOARD PELANGGAN (" << user->username << ") ===\n";
        cout << "1. Lihat Katalog\n";
        cout << "2. Sewa Mobil\n";
        cout << "3. Logout\n";
        cout << "Pilih: ";
        int choice = manager.getSafeInt();

        if (choice == 1) manager.printKatalog();
        else if (choice == 2) {
            string t; cout << "Cari Unit: "; getline(cin, t);
            Node* res = manager.search(t);
            if (res && res->subTree == nullptr) {
                cout << "[OK] Berhasil Sewa: " << res->name << endl;
                manager.tambahRiwayat(user->username + " menyewa " + res->name);
            } else cout << "[!] Unit tidak ditemukan.\n";
        }
        else if (choice == 3) loggedIn = false;
    }
}

int main() {
    MobilTree manager; 
    manager.initUsers();
    manager.loadFromFile("database_mobil.txt");

    bool systemRunning = true;
    while (systemRunning) {
        cout << "\n=== RENTAL MOBIL SYSTEM ===\n";
        cout << "1. Login\n2. Daftar Akun Baru\n3. Keluar (Simpan Data)\nPilih: ";
        int menuAwal = manager.getSafeInt();

        if (menuAwal == 3) {
            manager.saveToFile("database_mobil.txt");
            systemRunning = false;
        } 
        else if (menuAwal == 2) manager.registerUser();
        else if (menuAwal == 1) {
            string u, p;
            cout << "User: "; getline(cin, u);
            cout << "Pass: "; p = manager.inputPassword();
            Account* user = manager.login(u, p);
            if (user) {
                if (user->role == "admin") runAdminSession(manager, user);
                else runCustomerSession(manager, user);
            } else cout << "[!] Gagal Login.\n";
        }
    }
    return 0; 
}