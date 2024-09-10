 
#include<iostream>
#include<mutex>
#include<string>
#include<thread>
#include<condition_variable>

using namespace std;

condition_variable Event;
mutex mutex_object;
string text;
bool flag = false;
bool flag_end = false;
bool Read_flag = false;

void Read_Thread(){
    while(true){
        Read_flag = false;
        unique_lock<mutex> lock(mutex_object);
        cout << "Nhap du lieu" ;
        getline(cin, text);
        flag = true;
        if(text == "?"){
            flag_end = true;
            Event.notify_one();
            break;
        }
        flag = true;
        Event.notify_one();
        Event.wait(lock, []{return Read_flag;});
    }
   
}

void Print_Thread(){
    while(true){
        unique_lock<mutex> lock(mutex_object);
        Event.wait(lock, []{return flag;});

        if(flag_end){
            break;
        }

        cout << "Output: " << text << endl;
        text = "\0";
        flag = false;
        Read_flag = true;
        Event.notify_one();
    }
   
}



int main(){
    

    thread Read(Read_Thread);
    thread Print(Print_Thread);
    Read.join();
    Print.join();

    return 0;
}
 
