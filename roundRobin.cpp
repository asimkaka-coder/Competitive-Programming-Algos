#include <iostream>
using namespace std;
//Declaring Process Class
class Process{
	public:
		int process_length;
		int process_id;
		Process *next;
		//Method to display a process
    void displayProcess() {
        cout << "Process #" << process_id << " (" << process_length << " s)";
    }
};
//Declaring Round Robin Class
class RoundRobin{
	Process *head = NULL;
	Process *tail = NULL;
	int id = 0;
	int quantum = 5;

	void deleteAtHead(){		//delete process
		if(head != NULL){		//if there is a process
			cout<<"Process "<<head->process_id<<" Completed(Deleted)"<<endl;
			if(head == tail){	//if there is one process then delete it
				delete head;
				head = NULL;
				tail = NULL;
			}
			else{				//else delete current process and move to next
				tail->next = head->next;
				delete head;
				head = tail->next;
			}
		}
		else cout<<"No Active Process\n";
	}

		void shift_position(){			//shift_position process
			if(head != tail){		//if there are more than one process
				cout<<"Shifted Process "<<head->process_id<<". Remaining process length is "<<head->process_length<<endl;
				//move to next process
				tail = tail->next;
				head = head->next;
			}
			else cout<<"No need to shift Process "<<head->process_id<<" Remaining process length is "<<head->process_length<<endl;
		}

	public:
		void insertAtTail(int value){				//insert process
			Process *newNode = new Process();		//make process
			newNode->process_length = value;		//assign it length
			newNode->process_id = ++id;		//and id
			if(head == tail && head == NULL){		//if there is no process
				head = newNode;						//insert process at start
				tail = newNode;
			}
			else{									//if there is a process present
				tail->next = newNode;				//insert process at last
				newNode->next = head;
				tail = newNode;
			}
		}

		void runProcesses(){					//runProcesses round robin
	        display();
			if(head != NULL){
				if(head->process_length <= quantum){	//if process length is equal or less than quantum
					deleteAtHead();						//delete process

				}
				else{									//else runProcesses for given quantum and shift_position
					head->process_length = head->process_length - quantum;
                    shift_position();

				}
			}
			else cout<<"No task to runProcesses\n";
		}

		bool process_is_there(){		//if there is a process
			return head != NULL;
		}
    void display() {
        Process* temp = head;

        while (temp != tail) {
            temp->displayProcess();
            temp = temp->next;
            cout << " -> ";
        }
        temp->displayProcess();
        cout << endl;
    }

};

int main(){
	RoundRobin *roundRobin = new RoundRobin();
	roundRobin->insertAtTail(5);
	roundRobin->insertAtTail(10);
	roundRobin->insertAtTail(20);
	roundRobin->insertAtTail(7);
	roundRobin->insertAtTail(2);

	//while there are tasks runProcesses them
	while(roundRobin->process_is_there()){
        roundRobin->runProcesses();
	}

	return 0;
}
