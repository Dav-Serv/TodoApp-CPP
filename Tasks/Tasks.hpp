#ifndef TASKS__h
#define TASKS__h

#include <string>
#include <vector>

using namespace std;

struct Tasks
{
    int id;
    string title;
    bool isCompleted;
};

void addTask(vector<Tasks> &tasks);
void viewTasks(const vector<Tasks> &tasks);
void markTaskCompleted(vector<Tasks> &tasks, int id);
void deleteTask(vector<Tasks> &tasks, int id);
void saveTasksToFile(const vector<Tasks> &tasks, const string &filename);
void loadTasksFromFile(vector<Tasks> &tasks, const string &filename);

#endif