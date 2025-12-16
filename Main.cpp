#include "MobilTree.h"

void runAdminSession(MobilTree& manager, Account* user) {
    bool loggedIn = true;
    while (loggedIn) {
        cout << "\n=== DASHBOARD ADMIN (" << user->username << ") ===\n";
        cout << "1. Lihat Database Mobil\n";
        cout << "2. Tambah Data (Kategori/Brand/Model)\n";
        cout << "3. Hapus Data (Kategori/Brand/Model)\n"; 
        cout << "4. Lihat Daftar User\n";
        cout << "5. Lihat Statistik Database\n"; 
        cout << "6. Logout\n";
        cout << "Pilih: ";
        
        int choice = manager.getSafeInt(); 

        switch (choice) {
            case 1:
                manager.printKatalog(); 
                break;
            case 2: {
                string parent, child;
                cout << "Induk (ex: Database/Sport/Toyota): "; getline(cin, parent);
                cout << "Data Baru (ex: MPV/Ferrari/Avanza): "; getline(cin, child);
                if (parent == "Database") {
                     manager.addChild("Database", child);
                } else {
                     manager.addChild(parent, child); 
                }
                break;
            }
            case 3: {
                string target;
                cout << "Nama data yang ingin dihapus: "; getline(cin, target);
                manager.removeNode(target);
                break;
            }
            case 4:
                manager.printUsers();
                break;
            case 5:
                manager.getStatistics();
                break;
            case 6:
                cout << "Logging out...\n";
                loggedIn = false;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
}

void runCustomerSession(MobilTree& manager, Account* user) {
    bool loggedIn = true;
    while (loggedIn) {
        cout << "\n=== DASHBOARD PELANGGAN (" << user->username << ") ===\n";
        cout << "1. Lihat Katalog Mobil\n";
        cout << "2. Cari & Sewa Mobil\n";
        cout << "3. Logout\n";
        cout << "Pilih: ";

        int choice = manager.getSafeInt();

        switch (choice) {
            case 1:
                manager.printKatalog();
                break;
            case 2: {
                string target;
                cout << "Nama mobil yang dicari (Model Unit): "; getline(cin, target);
                Node* res = manager.search(target); 
                if (res) {
                    cout << "Ditemukan: " << res->name << endl;
                    if (res->subTree == nullptr)
                        cout << ">> [SUKSES] Sewa Berhasil diproses untuk " << res->name << "!\n";
                    else
                        cout << ">> [GAGAL] '" << res->name << "' adalah Kategori/Brand.\n";
                } else {
                    cout << ">> [404] Mobil tidak ditemukan.\n";
                }
                break;
            }
            case 3:
                cout << "Logging out...\n";
                loggedIn = false;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
}

int main() {
    MobilTree manager; 
    manager.initUsers();
    manager.initCarData();

    bool systemRunning = true;
    while (systemRunning) {
        cout << "\n============================\n";
        cout << "   RENTAL MOBIL SYSTEM   \n";
        cout << "============================\n";
        cout << "1. Login\n";
        cout << "2. Daftar Akun Baru\n";
        cout << "3. Keluar Sistem\n";
        cout << "Pilih: ";
        int menuAwal = manager.getSafeInt();

        if (menuAwal == 3) {
            cout << "Sampai jumpa!\n";
            systemRunning = false;
        } 
        else if (menuAwal == 2) {
            manager.registerUser();
        } 
        else if (menuAwal == 1) {
            string u, p;
            cout << "Username : "; getline(cin, u);
            cout << "Password : "; p = manager.inputPassword();

            Account* currentUser = manager.login(u, p);
            if (currentUser == nullptr) {
                cout << "[!] Login Gagal! Username atau password salah.\n";
            } else {
                cout << "\n[OK] Login Berhasil! Role: " << currentUser->role << "\n";
                if (currentUser->role == "admin") {
                    runAdminSession(manager, currentUser);
                } else {
                    runCustomerSession(manager, currentUser);
                }
            }
        } 
        else {
            cout << "Input salah.\n";
        }
    }
    return 0; 
}