#include<iostream>
#include<string>
#include<fstream>
using namespace std;


void encryptdecrpyt(string &data){
    const char key='k';
    for (int i = 0; i < data.length(); i++){
        data[i]=data[i]^key;
    }
}

void addpass(){
    string site,user,pass;
    ofstream out("vault.txt");
    if(!out.is_open()){
        cout<<"Error while opening file for adding password \n";
        return;
    }
        cout<<"enter website name:";
        cin>>site;
        cout<<"enter username:";
        cin>>user;
        cout<<"enter password:";
        cin>>pass;
        encryptdecrpyt(user);
        encryptdecrpyt(pass);
        out<<site<<" "<<user<<" "<<pass;
    out.close();
    cout<<"  Saved \n ";
}

void viewpass(){
    ifstream in("vault.txt");
    string site, user,pass;
    if(!in.is_open()){
        cout<<"Error while opening file for reading \n";
        return;
    }
    while (in>>site>>user>>pass)
    {
        cout<<"\n site: "<<site<<endl;
        encryptdecrpyt(user);
        encryptdecrpyt(pass);
        cout<<"\n username: "<<user<<endl;
        cout<<"\n Password: "<<pass<<endl;
    }
    in.close();
}

void menu(){
    int choice;
    do{
    cout<<"\n1.Add Password \n2.View Passwords \n3.exit\n";
    cout<<"Enter choice";
    cin>>choice;
    switch (choice){
        case 1:
        addpass();
        break;

        case 2:
        viewpass();
        break;

        case 3:
        cout<<"Exiting the file";
        break;

    default:
    cout<<"invalid option";
        break;
}
    } while (choice !=3);
}


int main(){

    const string pass="admin@123";
    string input;
    cout<<"enter master password:";
    cin>>input;
    if (input != pass){
        cout<<"Access denied";
        return 0;
    }
    cout<<"Login successfull"<<endl;
    menu();
 return 0;
}