#include <iostream>
#include "Tasks/Tasks.hpp"

using namespace std;

int main()
{
    Tasks* todoList = nullptr; // Inisialisasi linked list tugas pertama
    StackTask* undoHistory = nullptr; // Inisialisasi stack untuk fitur UNDO
    const string filename = "data_todo.txt"; // Nama file untuk menyimpan data tugas
    int choice;

    // DEKLARASI ARRAY STATIS
    const int MAX_ARRAY_SIZE = 10;
    FavoriteTask favCategories[MAX_ARRAY_SIZE];
    int currentArraySize = 0; // Melacak jumlah elemen di dalam array

    // Load data tugas dari file saat program dijalankan
    loadTasksFromFile(todoList, filename);

    do {
        system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
        cout << "===============================================\n";
        cout << "    APLIKASI TO-DO LIST (FINAL PROJECT DS)     \n";
        cout << "===============================================\n";
        cout << " 1. Tambah Tugas Baru (Create)\n";
        cout << " 2. Lihat Semua Daftar Tugas (Read)\n";
        cout << " 3. Tandai Tugas Selesai (Update)\n";
        cout << " 4. Hapus Tugas (Delete)\n";
        cout << " 5. Cari Tugas Berdasarkan Nama (Searching)\n";
        cout << " 6. Urutkan Tugas Berdasarkan Status (Sorting)\n";
        cout << " 7. Batalkan Penghapusan Terakhir (Stack Undo)\n";
        cout << " 8. Rekomendasi Urutan Kerja Prioritas (Queue)\n";
        cout << " 9. [ARRAY] Tambah Kategori Tugas Favorit\n"; // Menu Baru Array
        cout << " 10. [ARRAY] Lihat Semua Kategori Favorit\n";
        cout << " 11. Simpan Database & Keluar Aplikasi\n";
        cout << "-----------------------------------------------\n";
        cout << "Pilih Opsi Menu (1-11): ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTask(todoList);
            break;
        case 2:
            viewTasks(todoList);
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); 
            cin.get();
            break;
        case 3:
            viewTasks(todoList); // Tampilkan daftar tugas sebelum memilih ID
            markTaskCompleted(todoList);
            break;
        case 4:
            viewTasks(todoList); // Tampilkan daftar tugas sebelum memilih ID
            deleteTask(todoList, undoHistory);
            break;
        // coming soon features:
        case 5:
            cout << "Fitur Coming Soon!" << endl;
            // searchTask(todoList);
            break;
        case 6:
            cout << "Fitur Coming Soon!" << endl;
            // sortTasks(todoList);
            break;
        case 7:
            cout << "Fitur Coming Soon!" << endl;
            // restoreDeletedTask(undoHistory, todoList);
            break;
        case 8:
            cout << "Fitur Coming Soon!" << endl;
            // showWorkRecomendation(todoList);
            break;
        case 9:
            addFavoriteCategory(favCategories, currentArraySize, MAX_ARRAY_SIZE);
            break;
        case 10:
            viewFavoriteCategories(favCategories, currentArraySize);
            break;
        case 11:
            system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
            saveTasksToFile(todoList, filename);
            cout << "Data tugas telah disimpan." << endl;
            cout << "Tekan Enter untuk keluar...";
            cin.ignore();
            cin.get();
            break;
        default:
            system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
            cout << "Pilihan tidak valid. Silakan pilih menu antara 1-11." << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            break;
        }
    } while (choice != 11);
    
    return 0;
}