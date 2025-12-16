# 🚗 Aplikasi Rental Mobil Menggunakan BST

Aplikasi konsol sederhana yang dirancang untuk mengelola data katalog mobil rental. Proyek ini mengimplementasikan struktur data **Multi-Level Binary Search Tree (BST)** untuk menyusun data secara hierarkis dan terurut (Kategori → Brand/Tipe → Model).

## ✨ Fitur Utama

Aplikasi ini mendukung manajemen data dan otentikasi pengguna:

* **Otentikasi & Akses**: Mendukung dua peran pengguna: **Admin** untuk manajemen data dan **Pelanggan** untuk melihat katalog dan simulasi sewa.
* **CRUD Hierarkis**: Tambah data di berbagai level (Kategori, Brand, atau Model).
* **Struktur Data Multi-Level BST**: Data diorganisir dalam struktur BST yang bertingkat, memungkinkan pengurutan alfabetis otomatis di setiap level. 
* **Pencarian Cepat**: Menggunakan algoritma rekursif (`searchGlobal`) untuk mencari mobil di seluruh Tree secara efisien.
* **Traversal In-Order**: Menampilkan seluruh katalog mobil dalam format *Tree View* yang terstruktur dan terurut alfabetis.

## 🧱 Struktur Data Proyek

Struktur data utama yang diimplementasikan adalah BST yang dimodifikasi, menggunakan pointer berlapis:

| Komponen | Deskripsi | Tujuan |
| :--- | :--- | :--- |
| **`Node`** | Unit data dasar (Kategori, Brand, atau Model). | Menyimpan entitas data mobil. |
| **`left`, `right`** | Pointer ke *Sibling Node*. | Mengorganisir data pada level yang sama (misalnya, Sport dan SUV) dalam bentuk **BST** untuk pengurutan otomatis. |
| **`subTree`** | Pointer ke *Child Node*. | Menghubungkan ke level di bawahnya (misalnya, dari Kategori ke Brand), yang juga diorganisir sebagai BST. |
| **`Account`** | Struktur untuk menyimpan `username`, `password`, dan `role` (`admin`/`customer`). | Manajemen Login. |


### Struktur File

* `main.cpp`
* `MobilTree.h`
* `MobilTree.cpp`
