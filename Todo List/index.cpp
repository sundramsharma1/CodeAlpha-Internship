#include<iostream>
#include<string>
#include<fstream>
#include<sstream> 
#include<vector>

using namespace std;

struct todolist{
    int id;
    string task;
};

int ID = 0;

void banner(){
    cout << "______________________________________________________" << endl;
    cout << "\t        My Todo List Application" << endl;
    cout << "______________________________________________________" << endl;
}

void initializeID() {
    ifstream fin("todo.txt");
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            ID++;
        }
    }
    fin.close();
}

void addTask(){
    system("cls");
    banner();
    todolist todo;
    cout << "Enter New Task: " << endl;
    cin.get();
    getline(cin, todo.task);
    char save;
    cout << " Save? (Y/N): ";
    cin >> save;
    if(save == 'Y' || save == 'y'){
        cout << "Task Saved Successfully!" << endl;
        ID++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << ID << ": " << todo.task << endl;
        fout.close();

        char more;
        cout << "Add More Task? (y/n): ";
        cin >> more;
        if(more == 'Y' || more == 'y'){
            addTask();
        } else {
            system("cls");
            cout << "Task Added Successfully!" << endl;
            return;
        }
    }
    system("cls");
}

void showTask() {
    system("cls"); 
    banner();       
    todolist todo;
    ifstream fin("todo.txt");
    cout << "Task: " << endl;

    while (fin >> todo.id) {  
        fin.ignore();  
        getline(fin, todo.task);  

        if (todo.task.empty()) {
             cout << "\t Todo list is Empty!" << endl;
        }else{
             cout << "\t" << todo.id << ": " << todo.task << endl;
        }
    }

    fin.close();

    char exit;
    cout << "Exit? (y/n): ";
    cin >> exit;

    if (exit != 'Y' && exit != 'y') {
        showTask();  
    }
    
    system("cls"); 
}

 int searchTask(){
    system("cls");
    banner();
    int id;
    cout << "Enter Task id: ";
    cin >> id;
    todolist todo;
    ifstream fin("todo.txt");
    while(!fin.eof()){
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.id == id){
            system("cls");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            return id;
        }
    }
  system("cls");
  cout << "Not Found!" << endl;
  return 0;

};
void deleteTask() {
    system("cls");
    banner();
    int id = searchTask();
    if (id != 0) {
        char del;
        cout << "\n\tDelete? (y/n): ";
        cin >> del;
        if (del == 'y' || del == 'Y') {
            todolist todo;
            ofstream tempfile;
            tempfile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");

            int newID = 0; // New ID counter for tasks
            while (fin >> todo.id) {
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id != id) {
                    newID++;
                    tempfile << newID << ": " << todo.task << endl;
                }
            }

            fin.close();
            tempfile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");

            // Update the global ID to the last used ID
            ID = newID;

            system("cls");
            cout << "\n\tDeleted Successfully!" << endl;
        } else {
            system("cls");
            cout << "\n\tNot Deleted" << endl;
        }
    }
};
void updateTask() {
    system("cls");
    banner();

    int id = searchTask(); // Search for the task to update
    if (id != 0) { // If the task was found
        char update;
        cout << "\n\tUpdate? (y/n): ";
        cin >> update;
        if (update == 'y' || update == 'Y') {
            cout << "Enter New Task Description: ";
            cin.get(); // Consume any leftover newline character
            string newTask;
            getline(cin, newTask);

            todolist todo;
            ifstream fin("todo.txt");
            ofstream tempfile("temp.txt");

            while (getline(fin, todo.task)) {
                stringstream ss(todo.task);
                string id_str;
                getline(ss, id_str, ':');
                todo.id = stoi(id_str);
                getline(ss, todo.task);

                if (todo.id == id) {
                    tempfile << todo.id << ": " << newTask << endl;
                } else {
                    tempfile << todo.id << ": " << todo.task << endl;
                }
            }

            fin.close();
            tempfile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");

            system("cls");
            cout << "\n\tUpdated Successfully!" << endl;
        } else {
            system("cls");
            cout << "\n\tNot Updated" << endl;
        }
    }
};

int main(){
    system("cls");
    initializeID();  
    while(true){
        banner();
        cout << "\n\t1. Add Task";
        cout << "\n\t2. Show Task";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Update Task";

        int choice;
        cout << "\n\tEnter Your Choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                addTask();
                break;
            case 2:
                showTask();
                break;
            case 3:
                searchTask();
                break;
            case 4:
                deleteTask();
                break; 
            case 5:
                updateTask();
                break;  
        }
    }
    return 0;
}
