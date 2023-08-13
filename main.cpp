#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Node {
public:
    Node(int d, string ta_name, int flag)
    {
        data = d;
        name = ta_name;
        flag = 0;
        next = NULL;
    }
    int data; // value
    string name;
    int flag;
    Node* next;
};

class Linkedlist {
    Node* head;
public:
    // Default constructor
    Linkedlist() { head = NULL;}
    void insertNode(int data, string name, int flag) {
        Node* newNode = new Node(data, name, flag);
        if (head == NULL) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Insert at the last as it would be more organized
        temp->next = newNode;
    }
    void printList() {
        Node* temp = head;
        // Check for empty list.
        if (head == nullptr) {
            cout << "List empty" << endl;
            return;
        }
        // Traverse the list.
        while (temp != nullptr) {
            cout << temp->name << endl;
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
    int count(int search_for)
    {
        Node* current = head;
        int count = 0;
        while (current != NULL) {
            if (current->data == search_for)
                count++;
            current = current->next;
        }
        return count;
    }
    int search(string name)
    {
        Node* position_curr = head; // Initialize current 
        while (position_curr != NULL)
        {
            if (position_curr->name == name)
                return 1;
            position_curr = position_curr->next;
        }
        return 0;
    }
    void deleteList()
    {
        Node* current = head;
        Node* next = NULL;

        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }

        /* deref head_ref to affect the real head back
            in the caller. */
        head = NULL;
    }

    Node* getHead()
    {
        return head;
    }

};

class Lab_Info {

private:
    int* nLabCount;
    int LAB_MAX_SIZE;
    Linkedlist my_list;
    Linkedlist final_list;
    Linkedlist Unassigned_list;
    void read_lab_info();

public:
    Lab_Info()
    {
        nLabCount = NULL;
        LAB_MAX_SIZE = 13;
    }

    ~Lab_Info()
    {
        if (nLabCount != NULL)
        {
            delete[]nLabCount;
        }
    }

    int Init_Lab_Info(int nMaxSize = 0)
    {
        LAB_MAX_SIZE = nMaxSize; // ideally read this from file
        nLabCount = new int[LAB_MAX_SIZE];
        if (nLabCount == NULL)
        {
            cout << endl << "No memory..." << endl;
            return 0;
        }
        // initialize array
        for (int i = 0; i < LAB_MAX_SIZE; i++)
        {
            nLabCount[i] = 0;
        }
    }
    void ask_input() {
        string temp_name;
        int temp_lab = 0;
        int entry_opt = 0;
        do
        {
            cout << "Enter name: " << endl;
            cin >> temp_name;
            cout << "* Section 01: TU 7 : 45 to 10 : 35 am PST; EME 128;" << endl;
            cout << "* Section 02: TU 10 : 35 am to 1 : 25 pm PST; EME 128;" << endl;
            cout << "* Section 03 : TU 1 : 30 to 4 : 20 pm PST; EME 128;" << endl;
            cout << "* Section 04 : TU 4 : 20 to 7 : 10 pm PST; EME 128;" << endl;
            cout << "* Section 05 : W 11 : 10 am to 2 : 00 pm PST; EME 128;" << endl;
            cout << "* Section 06 : W 2 : 10 to 5 : 00 pm PST; EME 128;" << endl;
            cout << "* Section 07 : TH 7 : 45 to 10 : 35 am PST; EME 128;" << endl;
            cout << "* Section 08 : TH 10 : 35 am to 1 : 25 pm PST; EME 128;" << endl;
            cout << "* Section 09 : TH 1 : 30 to 4 : 20 pm PST; EME 128;" << endl;
            cout << "* Section 10 : TH 4 : 20 to 7 : 10 pm PST; EME 128;" << endl;
            cout << "* Section 11 : F 11 : 10 am to 2 : 00 pm PST; EME 128;" << endl;
            cout << "* Section 12 : F 2 : 10 to 5 : 00 pm PST; EME 128;" << endl;
            cout << "Enter Lab time: " << endl;
            cin >> temp_lab;
            my_list.insertNode(temp_lab, temp_name, 0);
            cout << "Do you have another entry: 1 for YES , 0 for NO" << endl;
            cin >> entry_opt;
        } while (entry_opt == 1);
    }

    void read_from_file() {
        ifstream infile;
        string imp;
        int imp_num;
        int imp_flag;
        final_list.deleteList();
        infile.open("final_list.txt", ios::in);
        if (infile.is_open()) {
            while (!infile.eof()) {
                infile >> imp;
                infile >> imp_num;
                infile >> imp_flag;
                final_list.insertNode(imp_num, imp, imp_flag);
            }
        }
        infile.close();
    }
    void write_to_file() {
        ofstream myfile;
        myfile.open("final_list.txt",ios::out);
        Node* temp_file = final_list.getHead();
        while (temp_file != nullptr) {
            myfile << temp_file->name << endl;
            myfile << temp_file->data << endl;
            myfile << temp_file->flag;
            if (temp_file->next != nullptr)
            {
                myfile << endl;
            }
            temp_file = temp_file->next;
        }
        //my_list.deleteList();
        myfile.close();
    }
    void Assign_lab() {
        int z = 0;
        int i = 0;
        for (i = 0; i < LAB_MAX_SIZE; i++)
        {
            nLabCount[i] = my_list.count(i + 1);
            cout << endl << "Count of Lab : " << (i + 1) << " is " << nLabCount[i] << endl;
            if (nLabCount[i] == 0) {
                cout << "Lab" << (i + 1) << "is empty" << endl;
            }
            if (nLabCount[i] == 1) {
                Node* temp = my_list.getHead();
                while (temp != NULL) {
                    if (temp->data == (i + 1)) {
                        if (final_list.search(temp->name) == 1) {
                            cout << "already assigned" << endl;
                            break;
                        }
                        cout << "lab" << (i + 1) << "is assigned to" << temp->name << endl;
                        final_list.insertNode((i + 1), temp->name, 1);
                        temp->flag = 1;
                    }
                    temp = temp->next;
                }
            }
            if (nLabCount[i] > 1) {
                Node* iden = my_list.getHead();
                while (iden != NULL) {
                    if (iden->data == (i + 1)) {
                            cout << "lab" << (i + 1) << "is assigned to" << iden->name << endl;
                            final_list.insertNode((i + 1), iden->name, 1);
                            iden->flag = 1;
                            break;
                        }
                    iden = iden->next;
                }
            }
        }
        Node* diff_between = my_list.getHead();
        while (diff_between != nullptr) {
            if (diff_between->flag == 0) {
                Unassigned_list.insertNode(0, diff_between->name, 0);
            }
            diff_between = diff_between->next;
        }
        final_list.printList();
    }
    void allocated_list() {
        final_list.printList();
    }
    void print_unassigned() {
        Unassigned_list.printList();
    }
    void order_lab() {
        int i = 0, j = 0,temp = 0;
        for (i = 0; i < LAB_MAX_SIZE; i++)
        {
            for (j = i + 1; j < LAB_MAX_SIZE; j++)
            {
                if (nLabCount[i] > nLabCount[j])
                {
                    temp = nLabCount[i];
                    nLabCount[i] = nLabCount[j];
                    nLabCount[j] = temp;
                }
            }
        }
        for (i = 0; i < LAB_MAX_SIZE; i++) {
            cout << nLabCount[i] << ' ';
        }
    }

};


int main(void) {
    int option = 0;
    Lab_Info lab;
    while (option != 7) {
        cout << "MENU:" << endl;
        cout << "Option 1: input available lab times" << endl;
        cout << "Option 2: Assigning members" << endl;
        cout << "Option 3: Print assigned list" << endl;
        cout << "Option 4: Assign unassigned members" << endl;
        cout << "Option 5: Load existing file" << endl;
        cout << "Option 6: Write to file" << endl;
        cout << "Option 7: EXIT" << endl;
        cout << "Please choose an option above: " << endl;
        cin >> option;
        while (option > 7 || option < 1) {
            cout << "please choose an option between 1 and 5: " << endl;
            cin >> option;
        }
        switch (option) {
        case 1:
            lab.ask_input();
            break;
        case 2:
            lab.Init_Lab_Info(13);
            lab.Assign_lab();
            break;
        case 3:
            lab.allocated_list();
            break;
        case 4:
            lab.print_unassigned();
            break;
        case 5:
            lab.read_from_file();
            break;
        case 6:
            lab.write_to_file();
            break;
        case 7:
            cout << "Thanks for your inputs" << endl;
            break;
        }
    }
    return 0;
}