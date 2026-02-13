#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class password{
    private :

        bool verified = false;
        const std::string password = "Admin@123";
        std::string mainUser;
        const std::string path = "password.txt";
        const int prefixSize = 4;

    public:

        password(){
            std::cout<<"Enter the master password : ";
            std::string line;
            std::getline(std::cin,line);
            if(line == password){
                std::cout<<"Authentication successful \n";
                verified = true;
            }
        }

        inline bool getValidity() { return verified; } // this function is probably a bad idea , breaks the whole point of making the bool private 
        void encryptdecrpyt(string &data){
            const char key='k';
            for (int i = 0; i < data.length(); i++){
                data[i]=data[i]^key;
            }
        }

        int addPass(){ // return 0 on new pass , 1 if existing password is updated , -1 for fail
            std::ofstream out(path);
            if(!out.is_open()){
                std::cout<<"Error while accessing file , aborting \n";
                return -1;
            }

            std::string site , user , password;
            
            std::cout<<"Enter site name : ";
            std::getline(std::cin,site);
            std::cout<<"Enter user name : ";
            std::getline(std::cin,user);
            std::cout<<"Enter password : ";
            std::getline(std::cin,password);
            
            encryptdecrpyt(user);
            encryptdecrpyt(password);
            
            write(out,site,user,password);
            out.close();
            return 0; // no way to check if existing password was updated for now 
        }

        int getPass(std::ifstream &in){ // return 0 on success , -1 for fail as usual
            if(!in.is_open()){
                std::cout<<"Error while reading passwords , aborting \n";
                return -1;
            }
            
            // we will read file line by line
            std::string line = "";
            while(std::getline(in,line)){
                std::string content =  line.substr(0,prefixSize);
                if(content == std::string(""))
            }
        }

        inline void write(std::ofstream& out ,const std::string& site , const std::string& user , const std::string& pass){
            out<<std::flush;
            out<<site<<std::endl;
            out<<user<<std::endl;
            out<<pass<<std::endl;
        }

    void viewpass(){
        ifstream in("vault.txt");
        string site, user,pass;
        if(!in.is_open()){
            cout<<"Error while opening file for reading \n";
            return;
        }
        while (in>>site>>user>>pass){
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
            cout<<"Enter choice \n";
            cin>>choice;
            switch (choice){
                case 1:
                // getPass(); 
                break;

                case 2:
                // viewpass();
                break;

                case 3:
                cout<<"Exiting the file";
                break;

                default:
                cout<<"invalid option";
                }
            } while (choice !=3);
        }
        // this part of code needs a re-work its ugly as fuck , no matter how i indent it , it looks wrong
};



int main(){
    password Pass;
    if(!Pass.getValidity()){
        std::cout<<"Authentication failed \n";
        return -1;
    }
    
 return 0;
}