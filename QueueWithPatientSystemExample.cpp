
#include <iostream>
#include <sstream>
#include <algorithm>


using namespace std;

// Array based Queue
class Patient{
private:
    int id;

public:
    Patient(){
    }
    //set name
    void setName(string name){
        this->name = name;
    }
    //set id
    void setID(int id){
        this->id = id;
    }
    // to get id
    int getID(){
        return this->id;
    }
    // to get name
    string getName(){
        return this->name;
    }

    string name;
};
//Queue for Patients
class PatientQueue{
private:
    Patient* queue;
    Patient* new_queue;
    int rear,front;
    unsigned long size_queue;
    int id=0;
public:
    PatientQueue(int size){
        this->size_queue = size;

        queue = new Patient[size_queue];
        new_queue = new Patient[size_queue];
        rear = -1;
        front = -1;
    }
    bool CanDoctorGoHome(){
        return front == -1;
    }
    bool isFull(){
        return front==0 && rear== size_queue-1;
    }
    void cancelAllAppointments(){
        delete []queue;
        delete []new_queue;
        front = -1;
        rear = -1;
        cout<<"All appointments for today have been cleared!"<<endl;
    }
    bool RegisterPatient(string &name){
        if(isFull()){
            cout<<"Queue is Full!"<<endl;
            return false;
        }
        else{
            if(CanDoctorGoHome()) front=0;
            rear++;
            Patient patient;
            patient.setID(id);
            patient.setName(name);
            queue [rear] = patient;
            id++;
        }
        return true;
    }
    void ServePatient(){

        if (CanDoctorGoHome()) {
            cout << "No More Appointments left!" << endl;
        } else {
            if (front >= rear) {
                front = -1;
                rear = -1;
            } /* Q has only one element, so we reset the queue after deleting it. */
            else {
                front++;
            }
            size_queue--;
            cout<<"One Patient has been served and Appointments left are: "<<size_queue<<endl;
        }
    }
    // display sorted array
    void showAllPatients(){
        if(CanDoctorGoHome()){
            cout<<"No More Appointments Left!"<<endl;
        }
        else{
            for(int i=front;i<=rear;i++){
                cout<<"ID#"<<new_queue[i].getID()<<" Name: "<<new_queue[i].getName()<<endl;
            }
        }
    }
    // to sort array by names
    void sortByName(){
        for(int i=front;i<=rear;i++){
            new_queue[i] = queue[i];
        }
        //copy_n(queue,size_queue,new_queue);
        int flag=1;
        Patient tmp_patient;
        for(int i=front;(i<=rear)&&flag;i++){
            flag = 0;
            for(int j=front;j<=rear-1;j++){
                if(new_queue[j+1].getName()<new_queue[j].getName()){
                    tmp_patient = new_queue[j];
                    new_queue[j] = new_queue[j+1];
                    new_queue[j+1] = tmp_patient;
                    flag=1;
                }
            }
        }
    }
};

int main() {
    string name_patient;
    string appointments;
    cout<<"How many patients can be appointed today: ";
    getline(cin,appointments);
    stringstream toInt(appointments);
    int apoins=0;
    toInt >> apoins;
    PatientQueue patientQueue(apoins);
    string choice;
    while(choice!="-1"){
        cout<<"Pick a Option"<<endl;
        cout<<"1.Register a Patient"<<endl;
        cout<<"2.Serve a Patient"<<endl;
        cout<<"3.Cancel all appointments"<<endl;
        cout<<"4.Show Patients IDs (sorted by Name)"<<endl;
        getline(cin,choice);
        if(choice=="1"){
            cout<<"Enter name of patient: ";
            getline(cin,name_patient);
            if(patientQueue.RegisterPatient(name_patient)){
                cout<<"Patient has been Registered!"<<endl;
            }
        }
        else if(choice=="4"){
            patientQueue.sortByName();
            patientQueue.showAllPatients();
        }
        else if(choice=="2"){
            patientQueue.ServePatient();
        }
        else if(choice=="3"){
            patientQueue.cancelAllAppointments();
        }
        cout<<"--------------------------------------------"<<endl;
    }
    return 0;
}
