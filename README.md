# 🚗 Aplikasi Rental Mobil System menggunakan BST

Aplikasi konsol sederhana yang dirancang untuk mengelola data katalog mobil rental. Proyek ini mengimplementasikan struktur data **Multi-Level Binary Search Tree (BST)** untuk menyusun data secara hierarkis dan terurut (Kategori → Brand/Tipe → Model).

## ✨ Fitur Utama

Aplikasi ini mendukung manajemen data dan otentikasi pengguna:

* [cite_start]**Otentikasi & Akses**: Mendukung dua peran pengguna: **Admin** untuk manajemen data dan **Pelanggan** untuk melihat katalog dan simulasi sewa[cite: 316].
* [cite_start]**CRUD Hierarkis**: Tambah data di berbagai level (Kategori, Brand, atau Model)[cite: 350].
* [cite_start]**Struktur Data Multi-Level BST**: Data diorganisir dalam struktur BST yang bertingkat, memungkinkan pengurutan alfabetis otomatis di setiap level[cite: 326]. 
* [cite_start]**Pencarian Cepat**: Menggunakan algoritma rekursif (`searchGlobal`) untuk mencari mobil di seluruh Tree secara efisien[cite: 345].
* [cite_start]**Traversal In-Order**: Menampilkan seluruh katalog mobil dalam format *Tree View* yang terstruktur dan terurut alfabetis[cite: 347, 348].

## 🧱 Struktur Data Proyek

Struktur data utama yang diimplementasikan adalah BST yang dimodifikasi, menggunakan pointer berlapis:

| Komponen | Deskripsi | Tujuan |
| :--- | :--- | :--- |
| **`Node`** | [cite_start]Unit data dasar (Kategori, Brand, atau Model)[cite: 332]. | Menyimpan entitas data mobil. |
| **`left`, `right`** | [cite_start]Pointer ke *Sibling Node*[cite: 333]. | [cite_start]Mengorganisir data pada level yang sama (misalnya, Sport dan SUV) dalam bentuk **BST** untuk pengurutan otomatis[cite: 334]. |
| **`subTree`** | [cite_start]Pointer ke *Child Node*[cite: 335]. | [cite_start]Menghubungkan ke level di bawahnya (misalnya, dari Kategori ke Brand), yang juga diorganisir sebagai BST[cite: 336]. |
| **`Account`** | [cite_start]Struktur untuk menyimpan `username`, `password`, dan `role` (`admin`/`customer`)[cite: 337]. | Manajemen Login. |


### Struktur File

* `main.cpp`
* `MobilTree.h`
* `MobilTree.cpp`
