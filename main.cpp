#include <iostream>
#include <utility>
#include <vector>

using namespace std;

enum class TaskStatus {
    Todo,
    Progress,
    Done
};

class Task {
    public:
        void changeStatus(const TaskStatus newStatus) {
            this->status = newStatus;
        }

        void setName(string name) {
            this->name = move(name);
        }

        void setDesc(string desc) {
            this->desc = move(desc);
        }

        string getName() {
            return this->name;
        }

        string getDesc() {
            return this->desc;
        }

        string getStatus() {
            status = this->status;

            switch (status) {
                case TaskStatus::Done:
                    return "Done";
                case TaskStatus::Progress:
                    return "Progress";
                case TaskStatus::Todo:
                    return "Todo";
            }
            return "Unknown";
        }

    private:
        string name;
        string desc;
        TaskStatus status = TaskStatus::Todo;

};

class TaskManager {
    public:
        void addTask(string name, string desc) {
            Task task = TaskManager::createTask(move(name), move(desc));
            this->taskList.push_back(move(task));
        }

        vector<Task>& getTasks() {
            return this->taskList;
        }

        void removeTask(const int index) {
            this->taskList.erase(this->taskList.begin() + index);
        }

    private:
        vector<Task> taskList;


        static Task createTask(string name, string desc) {
            Task task;
            task.setDesc(move(desc));
            task.setName(move(name));
            task.changeStatus(TaskStatus::Todo);
            return task;
        }
};

int main() {
    TaskManager taskManager;
    string command, name, desc;

    cout << "Create a task by writing the create command and after that inform it's name and description. To show the tasks write show. To quit the program write exit." << endl;

    while (true) {
        cin >> command;
        if (command == "exit") {
            break;
        }

        if (command == "show") {
            cout << "Index   Name   Desc   Status";
            for (int i = 0; i < taskManager.getTasks().size(); i++) {
                cout << "Task " << i << ": " << taskManager.getTasks()[i].getName() << "  " << taskManager.getTasks()[i].getDesc() << "  " << taskManager.getTasks()[i].getStatus() << endl;
            }
        }

        if (command == "create") {
            cin.ignore();
            getline(cin, name);
            getline(cin, desc);
            taskManager.addTask(name, desc);
        }
    }

    return 0;
}

