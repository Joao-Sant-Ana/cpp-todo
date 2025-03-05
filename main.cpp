#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Types for status
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

        //[[nodiscard]] Means that the value returned can't be ignored.
        [[nodiscard]] string getName() const {
            return this->name;
        }

        // Const for encapsulation.
        [[nodiscard]] string getDesc() const {
            return this->desc;
        }

        [[nodiscard]] string getStatus() const {
            switch (this->status) {
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

        [[nodiscard]] vector<Task> getTasks() const {
            return this->taskList;
        }

        void removeTask(const int index) {
            this->taskList.erase(this->taskList.begin() + index);
        }

        void changeStatus(const int index, const TaskStatus newStatus) {
            this->taskList[index].changeStatus(newStatus);
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
    string command, name, desc, status;
    int idx;
    cout << "Create a task by writing the create command and after that inform it's name and description. To show the tasks write show. To quit the program write exit." << endl;

    while (true) {
        cin >> command;

        if (command == "exit") {
            break;
        }

        if (command == "show") {
            cout << "Index   Name   Desc   Status" << endl;
            for (int i = 0; i < taskManager.getTasks().size(); i++) {
                cout << "Task " << i << ": " << taskManager.getTasks()[i].getName() << "  " << taskManager.getTasks()[i].getDesc() << "  " << taskManager.getTasks()[i].getStatus() << endl;
            }
        } else if (command == "create") {
            cin.ignore();
            getline(cin, name);
            getline(cin, desc);
            taskManager.addTask(name, desc);
            cout << "Task created" << endl;
        } else if (command == "change") {
            cin.ignore();
            cin>>idx;
            getline(cin, status);

            if (status == "done") {
                taskManager.changeStatus(idx, TaskStatus::Done);
            } else if (status == "progress") {
                taskManager.changeStatus(idx, TaskStatus::Progress);
            } else if (status == "todo") {
                taskManager.changeStatus(idx, TaskStatus::Todo);
            } else {
                cout << "Unknown status" << endl;
            }
        } else {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}

