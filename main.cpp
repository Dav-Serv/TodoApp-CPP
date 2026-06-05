#include <iostream>
#include "Tasks/Tasks.hpp"

using namespace std;

int main()
{
    vector<Tasks> todoList;
    const string filename = "data_todo.txt";
    int pilihan, id;

    // Muat tugas dari file saat program dimulai
    loadTasksFromFile(todoList, filename);

    do {
        system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
        cout << "\n=== MENU TO-DO LIST ===\n";
        cout << "1. Tambah Tugas\n";
        cout << "2. Lihat Semua Tugas\n";
        cout << "3. Tandai Tugas Selesai\n";
        cout << "4. Hapus Tugas\n";
        cout << "5. Simpan & Keluar\n";
        cout << "Pilih Menu (1-5): ";
        cin >> pilihan;
        cin.ignore(); // Bersihkan newline dari input sebelumnya

        switch (pilihan)
        {
        case 1:
            addTask(todoList);
            break;
        case 2:
            viewTasks(todoList);
            break;
        case 3:
            viewTasks(todoList);
            cout << "Masukkan ID tugas yang ingin ditandai selesai: ";
            cin >> id;
            markTaskCompleted(todoList, id);
            break;
        case 4:
            viewTasks(todoList);
            cout << "Masukkan ID tugas yang ingin dihapus: ";
            cin >> id;
            deleteTask(todoList, id);
            break;
        case 5:
            system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
            saveTasksToFile(todoList, filename);
            cout << "Tugas berhasil disimpan. Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan pilih antara 1-5." << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            break;
        }
    } while (pilihan != 5);
    

    return 0;
}