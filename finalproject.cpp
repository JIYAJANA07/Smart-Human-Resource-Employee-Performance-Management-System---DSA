#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

//================ EMPLOYEE STRUCTURE ================//

struct Employee
{
    int id;
    string name;
    string department;
    int attendance;
    float performanceScore;
};

//================ BST IMPLEMENTATION ================//

class Node
{
public:
    Employee emp;
    Node *left;
    Node *right;

    Node(Employee e)
    {
        emp = e;
        left = NULL;
        right = NULL;
    }
};

class BST
{
public:
    Node *root = NULL;

    Node* insert(Node *root, Employee e)
    {
        if(root == NULL)
            return new Node(e);

        if(e.id < root->emp.id)
            root->left = insert(root->left, e);
        else
            root->right = insert(root->right, e);

        return root;
    }

    Node* search(Node *root, int id)
    {
        if(root == NULL || root->emp.id == id)
            return root;

        if(id < root->emp.id)
            return search(root->left, id);

        return search(root->right, id);
    }

    void inorder(Node *root)
    {
        if(root != NULL)
        {
            inorder(root->left);

            cout << "\nID: " << root->emp.id;
            cout << "\nName: " << root->emp.name;
            cout << "\nDepartment: " << root->emp.department;
            cout << "\nAttendance: " << root->emp.attendance;
            cout << "\nPerformance: " << root->emp.performanceScore;
            cout << "\n---------------------";

            inorder(root->right);
        }
    }
};

//================ GRAPH IMPLEMENTATION ================//

class Graph
{
public:
    unordered_map<int, vector<int>> adj;

    void addRelation(int manager, int employee)
    {
        adj[manager].push_back(employee);
    }

    void BFS(int start)
    {
        unordered_map<int, bool> visited;
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "\nBFS Traversal: ";

        while(!q.empty())
        {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for(int child : adj[node])
            {
                if(!visited[child])
                {
                    visited[child] = true;
                    q.push(child);
                }
            }
        }
    }

    void DFSUtil(int node, unordered_map<int,bool> &visited)
    {
        visited[node] = true;

        cout << node << " ";

        for(int child : adj[node])
        {
            if(!visited[child])
                DFSUtil(child, visited);
        }
    }

    void DFS(int start)
    {
        unordered_map<int,bool> visited;

        cout << "\nDFS Traversal: ";

        DFSUtil(start, visited);
    }
};

//================ GLOBAL VARIABLES ================//

BST companyDB;
vector<Employee> employees;

queue<string> recruitmentQueue;
stack<string> historyStack;

unordered_map<int,string> employeeHash;

Graph organization;

//================ FUNCTIONS ================//

void addEmployee()
{
    Employee e;

    cout << "\nEnter Employee ID: ";
    cin >> e.id;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, e.name);

    cout << "Enter Department: ";
    getline(cin, e.department);

    cout << "Enter Attendance: ";
    cin >> e.attendance;

    cout << "Enter Performance Score: ";
    cin >> e.performanceScore;

    employees.push_back(e);

    companyDB.root = companyDB.insert(companyDB.root, e);

    employeeHash[e.id] = e.name;

    historyStack.push("Added Employee: " + e.name);

    cout << "\nEmployee Added Successfully!\n";
}

void displayEmployees()
{
    if(employees.empty())
    {
        cout << "\nNo Employee Records Found.\n";
        return;
    }

    companyDB.inorder(companyDB.root);
}

void searchEmployee()
{
    int id;

    cout << "\nEnter Employee ID: ";
    cin >> id;

    Node *result = companyDB.search(companyDB.root, id);

    if(result)
    {
        cout << "\nEmployee Found\n";

        cout << "ID: " << result->emp.id << endl;
        cout << "Name: " << result->emp.name << endl;
        cout << "Department: " << result->emp.department << endl;
        cout << "Attendance: " << result->emp.attendance << endl;
        cout << "Performance: " << result->emp.performanceScore << endl;
    }
    else
    {
        cout << "\nEmployee Not Found.\n";
    }
}

void rankEmployees()
{
    if(employees.empty())
    {
        cout << "\nNo Employees Available.\n";
        return;
    }

    vector<Employee> temp = employees;

    sort(temp.begin(), temp.end(),
         [](Employee a, Employee b)
         {
             return a.performanceScore > b.performanceScore;
         });

    cout << "\n===== PERFORMANCE RANKING =====\n";

    for(int i=0;i<temp.size();i++)
    {
        cout << i+1 << ". "
             << temp[i].name
             << " (Score: "
             << temp[i].performanceScore
             << ")\n";
    }
}

void markAttendance()
{
    int id;

    cout << "\nEnter Employee ID: ";
    cin >> id;

    for(auto &e : employees)
    {
        if(e.id == id)
        {
            e.attendance++;

            historyStack.push("Attendance Updated for " + e.name);

            cout << "\nAttendance Updated.\n";
            return;
        }
    }

    cout << "\nEmployee Not Found.\n";
}

void recruitEmployee()
{
    string name;

    cin.ignore();

    cout << "\nEnter Applicant Name: ";
    getline(cin, name);

    recruitmentQueue.push(name);

    cout << "\nApplicant Added to Queue.\n";
}

void processRecruitment()
{
    if(recruitmentQueue.empty())
    {
        cout << "\nNo Applicants Available.\n";
        return;
    }

    cout << "\nSelected Candidate: "
         << recruitmentQueue.front()
         << endl;

    recruitmentQueue.pop();
}

void verifyEmployee()
{
    int id;

    cout << "\nEnter Employee ID: ";
    cin >> id;

    if(employeeHash.find(id) != employeeHash.end())
        cout << "\nEmployee Verified Successfully.\n";
    else
        cout << "\nEmployee Not Found.\n";
}

void showHistory()
{
    if(historyStack.empty())
    {
        cout << "\nNo History Available.\n";
        return;
    }

    stack<string> temp = historyStack;

    cout << "\n===== RECORD HISTORY =====\n";

    while(!temp.empty())
    {
        cout << temp.top() << endl;
        temp.pop();
    }
}

void createOrganization()
{
    int manager, employee;

    cout << "\nEnter Manager ID: ";
    cin >> manager;

    cout << "Enter Employee ID: ";
    cin >> employee;

    organization.addRelation(manager, employee);

    cout << "\nRelation Added Successfully.\n";
}

void graphTraversal()
{
    int start;

    cout << "\nEnter Starting Manager ID: ";
    cin >> start;

    organization.BFS(start);
    cout << endl;

    organization.DFS(start);
    cout << endl;
}

//================ MAIN FUNCTION ================//

int main()
{
    int choice;

    do
    {
        cout << "\n\n========== HR MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Performance Ranking\n";
        cout << "5. Mark Attendance\n";
        cout << "6. Add Recruitment Applicant\n";
        cout << "7. Process Recruitment\n";
        cout << "8. Verify Employee\n";
        cout << "9. Show Record History\n";
        cout << "10. Create Organization Structure\n";
        cout << "11. BFS & DFS Traversal\n";
        cout << "0. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                rankEmployees();
                break;

            case 5:
                markAttendance();
                break;

            case 6:
                recruitEmployee();
                break;

            case 7:
                processRecruitment();
                break;

            case 8:
                verifyEmployee();
                break;

            case 9:
                showHistory();
                break;

            case 10:
                createOrganization();
                break;

            case 11:
                graphTraversal();
                break;

            case 0:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);

    return 0;
}