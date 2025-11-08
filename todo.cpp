#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Task {
private:
    string name;
    bool completed;

public:
    Task(string n, bool c = false) : name(n), completed(c) {}

    string getName() const { return name; }
    bool isCompleted() const { return completed; }

    void markComplete() { completed = true; }
    string toString() const {
        return (completed ? "[X] " : "[ ] ") + name;
    }

    // For saving/loading
    string serialize() const {
        return (completed ? "1|" : "0|") + name;
    }

    static Task deserialize(const string& line) {
        if (line.size() < 3) return Task("Invalid");
        bool c = (line[0] == '1');
        string n = line.substr(2);
        return Task(n, c);
    }
};

class ToDoList {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    void loadFromFile() {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            tasks.push_back(Task::deserialize(line));
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        for (auto& t : tasks)
            file << t.serialize() << endl;
        file.close();
    }

    void addTask() {
        cout << "Enter task name: ";
        string name;
        getline(cin, name);
        tasks.push_back(Task(name));
        cout << "Task added!\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks yet.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i].toString() << endl;
        }
    }

    void completeTask() {
        viewTasks();
        cout << "Enter task number to mark complete: ";
        int index;
        cin >> index;
        cin.ignore();
        if (index > 0 && index <= (int)tasks.size()) {
            tasks[index - 1].markComplete();
            cout << "Task marked complete!\n";
        } else {
            cout << "Invalid selection.\n";
        }
    }

    void deleteTask() {
        viewTasks();
        cout << "Enter task number to delete: ";
        int index;
        cin >> index;
        cin.ignore();
        if (index > 0 && index <= (int)tasks.size()) {
            tasks.erase(tasks.begin() + index - 1);
            cout << "Task deleted!\n";
        } else {
            cout << "Invalid selection.\n";
        }
    }

    void menu() {
        loadFromFile();
        int choice;
        do {
            cout << "\n=== To-Do List Menu ===\n";
            cout << "1. View Tasks\n2. Add Task\n3. Complete Task\n4. Delete Task\n5. Save and Exit\n";
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1: viewTasks(); break;
            case 2: addTask(); break;
            case 3: completeTask(); break;
            case 4: deleteTask(); break;
            case 5: saveToFile(); cout << "Tasks saved. Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    ToDoList todo;
    todo.menu();
    return 0;
}
