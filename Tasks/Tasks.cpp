#include "Tasks.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
// 1. FUNGSI CRUD
void addTask(Tasks* &firstTask) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    Tasks* newTask = new Tasks();

    // Menentukan ID secara otomatis berdasarkan tugas terakhir
    if (firstTask == nullptr) {
        newTask->id = 1; // ID pertama
    } else {
        Tasks* current = firstTask;
        while (current->nextTask != nullptr) {
            current = current->nextTask;
        }
        newTask->id = current->id + 1; // ID berikutnya
    }

    cout << "Masukkan nama tugas: ";
    cin.ignore(); // Bersihkan newline dari input sebelumnya
    getline(cin, newTask->title);
    newTask->isCompleted = false;
    newTask->nextTask = nullptr;

    // Memasukkan tugas baru ke urutan paling akhir (Append)
    if (firstTask == nullptr) {
        firstTask = newTask; // Tugas pertama
    } else {
        Tasks* current = firstTask;
        while (current->nextTask != nullptr) {
            current = current->nextTask;
        }
        current->nextTask = newTask; // Tambahkan tugas baru di akhir
    }

    cout << "Tugas berhasil ditambahkan!" << endl;
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

void viewTasks(Tasks* &firstTask) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    if (firstTask == nullptr) {
        cout << "| ID | Nama Tugas [Status] |\n";
        cout << "|----|---------------------|\n";
        cout << "Daftar tugas masih kosong." << endl;
    } else {
        cout << "| ID | Nama Tugas [Status] |\n";
        cout << "|----|---------------------|\n";
        Tasks* current = firstTask;
        // Perulangan untuk menampilkan semua tugas dalam linked list
        while (current != nullptr) {
            string status = current->isCompleted ? "Selesai" : "Belum Selesai";
            cout << "| " << current->id << "  | " << current->title << " [" << status << "] |\n";
            current = current->nextTask; // Pindah ke tugas berikutnya
        }
    }
}

void markTaskCompleted(Tasks* &firstTask) {
    if (firstTask == nullptr) {
        system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
        cout << "Daftar tugas masih kosong." << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        return;
    }

    int searchId;
    cout << "\nMasukkan ID tugas yang ingin ditandai selesai: ";
    cin >> searchId;

    // ALGORITMA: Cari tugas berdasarkan ID, jika ditemukan, ubah statusnya menjadi selesai
    Tasks* current = firstTask;
    bool found = false;
    while (current != nullptr) {
        if (current->id == searchId) {
            system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
            current->isCompleted = true; // Tandai tugas sebagai selesai
            found = true;
            cout << "Tugas dengan ID " << searchId << " telah ditandai selesai." << endl;
            break; // Keluar dari loop setelah menemukan tugas
        }
        current = current->nextTask; // Pindah ke tugas berikutnya
    }

    if (!found) {
        system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
        cout << "Tugas dengan ID " << searchId << " tidak ditemukan." << endl;
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void deleteTask(Tasks* &firstTask, StackTask* &undoHistory) {
    if (firstTask == nullptr) {
        system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
        cout << "Daftar tugas masih kosong." << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        return;
    }

    int deleteId;
    cout << "\nMasukkan ID tugas yang ingin dihapus: ";
    cin >> deleteId;

    Tasks* current = firstTask;
    Tasks* previousTask = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->id == deleteId) {
            system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
            found = true;

            // Simpan tugas yang akan dihapus ke dalam stack undo sebelum dihapus secara permanen
            // saveToUndoHistory(undoHistory, current->id, current->title);

            // Hapus tugas dari linked list
            if (previousTask == nullptr) {
                firstTask = current->nextTask; // Hapus tugas pertama
            } else {
                previousTask->nextTask = current->nextTask; // Hapus tugas di tengah atau akhir
            }
            delete current; // Bebaskan memori untuk tugas yang dihapus
            cout << "Tugas dengan ID " << deleteId << " telah dihapus." << endl;
            break; // Keluar dari loop setelah menemukan dan menghapus tugas
        }
        previousTask = current; // Simpan tugas sebelumnya sebelum pindah ke tugas berikutnya
        current = current->nextTask; // Pindah ke tugas berikutnya
    }

    if (!found) {
        system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
        cout << "Tugas dengan ID " << deleteId << " tidak ditemukan." << endl;
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// 2. FUNGSI IMPLEMENTASI ARRAY STATIS (KATEGORI FAVORIT)
void addFavoriteCategory(FavoriteTask categories[], int &currentSize, int maxSize) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    if (currentSize >= maxSize) {
        cout << "Penyimpanan Array Penuh! Tidak bisa menambah kategori favorit lagi." << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(); cin.get(); return;
    }

    cout << "=== TAMBAH KATEGORI TUGAS (Menerapkan Array) ===\n";
    categories[currentSize].refId = currentSize + 1;
    cout << "Masukkan Nama Kategori Baru (contoh: Kuliah, Tugas Rumah, Project): ";
    cin.ignore();
    getline(cin, categories[currentSize].taskCategory);

    currentSize++; // Ukuran elemen array bertambah
    cout << "\nKategori berhasil disimpan ke dalam Array!" << endl;
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

void viewFavoriteCategories(FavoriteTask categories[], int currentSize) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    cout << "=== DAFTAR KATEGORI TUGAS (Isi Data dari Array) ===\n";
    if (currentSize == 0) {
        cout << "Array masih kosong. Belum ada kategori yang didaftarkan." << endl;
    } else {
        cout << "| No | Nama Kategori |\n";
        cout << "|----|---------------|\n";
        for (int i = 0; i < currentSize; i++) {
            cout << "|  " << categories[i].refId << " | " << categories[i].taskCategory << " |\n";
        }
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); 
    cin.get();
}

// 3. FUNGSI SEARCHING BY NAME (LINEAR SEARCH)
void searchTask(Tasks* &firstTask) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    // Todo: Implementasi fungsi pencarian tugas berdasarkan nama (linear search)
}

// 4. FUNGSI SORTING (BUBBLE SORT)
void sortTasks(Tasks* &firstTask) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    // Todo: Implementasi fungsi pengurutan tugas
}

// 5. FUNGSI STACK (UNDO)
void restoreDeletedTask(StackTask* &undoHistory, Tasks* &firstTask) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    // Todo: Implementasi fungsi Stack undo
}

// 6. FUNGSI QUEUE (RECOMMENDATION)
void joinQueue(QueueTask* &frontTask, QueueTask* &rearTask, int id, string title) {
    // Todo: Implementasi fungsi untuk menambahkan tugas ke dalam queue rekomendasi
}

void leaveQueue(QueueTask* &frontTask, QueueTask* &rearTask) {
    // Todo: Implementasi fungsi untuk mengeluarkan tugas dari queue rekomendasi
}

void showWorkRecomendation(Tasks* firstTask) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    QueueTask* frontTask = nullptr;
    QueueTask* rearTask = nullptr;

    // Ambil semua tugas yang belum selesai dan masukkan ke dalam queue rekomendasi
    Tasks* current = firstTask;
    while (current != nullptr) {
        if (!current->isCompleted) {
            joinQueue(frontTask, rearTask, current->id, current->title);
        }
        current = current->nextTask;
    }

    // Tampilkan rekomendasi tugas berdasarkan urutan dalam queue
    cout << "=== Rekomendasi Tugas ===" << endl;
    if (frontTask == nullptr) {
        cout << "Tidak ada tugas yang perlu dikerjakan." << endl;
    } else {
        cout << "| ID | Nama Tugas |\n";
        cout << "|----|-------------|\n";
        int orderNumber = 1;
        while (frontTask != nullptr){
            cout << orderNumber << ". " << frontTask->id << " - " << frontTask->title << endl;
            orderNumber++;
        }
    }
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// 7. FUNGSI UNTUK MENYIMPAN DAN MEMUAT DATA TUGAS KE/DARI FILE
void saveTasksToFile(Tasks* firstTask, const string &filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk menyimpan tugas." << endl;
        return;
    }

    Tasks* current = firstTask;
    while (current != nullptr) {
        file << current->id << "|" << current->title << "|" << current->isCompleted << endl;
        current = current->nextTask;
    }
    file.close();
}

void loadTasksFromFile(Tasks* &firstTask, const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk memuat tugas." << endl;
        return;
    }

    string fileLine;
    Tasks* lastTask = nullptr;

    while (getline(file, fileLine)) {
        stringstream ss(fileLine);
        string idStr, title, statusStr;

        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, statusStr);

        if (!idStr.empty() && !title.empty() && !statusStr.empty()) {
            Tasks* newTask = new Tasks();
            newTask->id = stoi(idStr);
            newTask->title = title;
            newTask->isCompleted = (statusStr == "1");
            newTask->nextTask = nullptr;

            if (firstTask == nullptr) {
                firstTask = newTask; // Tugas pertama
                lastTask = newTask;
            } else {
                lastTask->nextTask = newTask; // Tambahkan tugas baru di akhir
                lastTask = newTask; // Update lastTask ke tugas yang baru ditambahkan
            }
        }
    }
    file.close();
}

