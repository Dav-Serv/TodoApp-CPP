#include "Tasks.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void addTask(vector<Tasks> &tasks) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    Tasks newTask;

    // logik untuk menentukan ID tugas baru
    newTask.id = tasks.empty() ? 1 : tasks.back().id + 1;

    cout << "Enter nama tugas: ";
    cin.ignore();
    getline(cin, newTask.title);
    newTask.isCompleted = false;

    tasks.push_back(newTask);
    cout << "Tugas berhasil ditambahkan!" << endl;
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
}

void viewTasks(const vector<Tasks> &tasks) {
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
    if (tasks.empty()) {
        cout << "| ID | Nama Tugas [Status] |\n";
        cout << "|----|---------------------|\n";
        cout << "Daftar tugas masih kosong." << endl;
    } else {
        cout << "\n=== Daftar Tugas ===\n";
        cout << "| ID | Nama Tugas [Status]             |\n";
        cout << "|----|---------------------------------|\n";
        for (const auto &task : tasks) {
            string status = task.isCompleted ? "Selesai" : "Belum Selesai";
            cout << "| " << task.id << ". |" << task.title << " [" << status << "]" << endl;
        }
    }
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

void markTaskCompleted(vector<Tasks> &tasks, int id) {
    for (auto &task : tasks) {
        if (task.id == id) {
            task.isCompleted = true;
            cout << "Tugas dengan ID " << id << " telah ditandai sebagai selesai." << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            return;
        }
    }

    cout << "Tugas dengan ID " << id << " tidak ditemukan." << endl;
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
}

void deleteTask(vector<Tasks> &tasks, int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            cout << "Tugas dengan ID " << id << " telah dihapus." << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            return;
        }
    }

    cout << "Tugas dengan ID " << id << " tidak ditemukan." << endl;
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    system("clear"); // Bersihkan layar (gunakan "clear" untuk Linux/Mac, gunakan "cls" untuk Windows)
}

void saveTasksToFile(const vector<Tasks> &tasks, const string &filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk menyimpan tugas." << endl;
        return;
    }

    for (const auto &task : tasks) {
        file << task.id << "|" << task.title << "|" << task.isCompleted << endl;
    }
    file.close();
}

void loadTasksFromFile(vector<Tasks> &tasks, const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk memuat tugas." << endl;
        return;
    }

    tasks.clear(); // Bersihkan daftar tugas sebelum memuat dari file
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, statusStr;

        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, statusStr, '|');

        if (!idStr.empty() && !title.empty() && !statusStr.empty()) {
            Tasks task;
            task.id = stoi(idStr);
            task.title = title;
            task.isCompleted = (statusStr == "1"); // Anggap "1" berarti selesai, "0" berarti belum selesai
            tasks.push_back(task);
        }
    }
    file.close();
}

