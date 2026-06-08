#ifndef TASKS__h
#define TASKS__h

#include <string>

using namespace std;

// 1. STRUCT UNTUK ARRAY STATIS
struct FavoriteTask {
    int refId;
    string taskCategory;
};

// 2. STRUCT UTAMA: representasi satu data Tugas (Node Linked List)
struct Tasks
{
    int id;
    string title;
    bool isCompleted;
    Tasks* nextTask; // Pointer ke tugas berikutnya (untuk linked list)
};

// 3. STRUCT STACK: untuk fitur UNDO (menyimpan ID tugas yang terakhir dihapus)
struct StackTask
{
    int deleteId;
    string deleteTitle;
    StackTask* lowerHistory; // Pointer ke node berikutnya dalam stack
};

// 4. STRUCT QUEUE: untuk merekomendasikan tugas terlama yang harus dikerjakan duluan
struct QueueTask
{
    int id;
    string title;
    QueueTask* behindTask; // Pointer ke node berikutnya dalam queue
};

// Deklarasi fungsi-fungsi manajemen tugas (CRUD & SEARCHING & SORTING)
// CRUD
void addTask(Tasks* &firstTask);
void viewTasks(Tasks* &firstTask);
void markTaskCompleted(Tasks* &firstTask);
void deleteTask(Tasks* &firstTask, StackTask* &undoHistory);
void sortTasks(Tasks* &firstTask); // BUBBLE SORTING
void searchTask(Tasks* &firstTask); // PENCARIAN NAMA TUGAS

// FUNGSI UNTUK MANIPULASI ARRAY
void addFavoriteCategory(FavoriteTask categories[], int &currentSize, int maxSize);
void viewFavoriteCategories(FavoriteTask categories[], int currentSize);

// Fungsi untuk fitur UNDO (STACK)
void saveToUndoHistory(StackTask* &undoHistory, int id, string title);
void restoreDeletedTask(StackTask* &undoHistory, Tasks* &firstTask);

// Fungsi untuk fitur RECOMMENDATION (QUEUE)
void joinQueue(QueueTask* &frontTask, QueueTask* &rearTask, int id, string title);
void leaveQueue(QueueTask* &frontTask, QueueTask* &rearTask);
void showWorkRecomendation(Tasks* firstTask);

// Fungsi untuk menyimpan dan memuat data tugas ke/dari file
void saveTasksToFile(Tasks* firstTask, const string &filename);
void loadTasksFromFile(Tasks* &firstTask, const string &filename);

#endif