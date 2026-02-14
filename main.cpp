#include<iostream>
#include<string>
#include<fstream>
#include<vector>

struct storage{
    std::string site;
    std::string user;
    std::string pass;
};

class password{
    private :

        bool verified = false;
        const std::string Password = "Admin@123"; // master password 
        std::string mainUser; // idk what this does so far
        const std::string path = "password.txt"; // hardcoding this value for now , can make it dynamic later
        const int prefixSize = 5; // adding prefix to make it possible to tell between site , user , password. 
        
        std::vector<storage> store;
        int cnt = 0;


    public:

        password(){
            std::cout<<"Enter the master password : ";
            std::string line;
            std::getline(std::cin,line);
            if(line == Password){
                std::cout<<"Authentication successful \n";
                verified = true;
            }
        }

        inline bool getValidity() { return verified; }
        
        void encryptdecrpyt(std::string &data){
            const char key='k';
            for (int i = 0; i < data.length(); i++){
                data[i]=data[i]^key;
            }
        }

        int addPass(){ // return 0 on new pass , 1 if existing password is updated , -1 for fail
            std::ofstream out(path,std::ios::app); // append instead of overwriting the file 
            if(!out.is_open()){
                std::cout<<"Error while accessing file , aborting \n";
                return -1;
            }

            std::string site , user , Pass;
            
            std::cout<<"Enter site name : ";
            std::getline(std::cin,site);
            std::cout<<"Enter user name : ";
            std::getline(std::cin,user);
            std::cout<<"Enter password : ";
            std::getline(std::cin,Pass);
            
            encryptdecrpyt(user);
            encryptdecrpyt(Pass);
            
            write(out,site,user,Pass);
            out.close();
            return 0; // no way to check if existing password was updated for now 
        }


        int getPass(std::ifstream &in ){ // return 0 on success , -1 for fail as usual
            if(!in.is_open()){
                std::cout<<"Error while reading passwords , aborting \n";
                return -1;
            }
            
            in.clear();              
            in.seekg(0, std::ios::beg);  // move to beginning

            // we will read file line by line
            std::string line = "";
            

            while(std::getline(in,line) && cnt < store.size()){
                std::string content =  line.substr(0,prefixSize);
                if(content == std::string("site:")) store[cnt].site = line.substr(prefixSize);
                if(content == std::string("user:")) store[cnt].user = line.substr(prefixSize);
                if(content == std::string("pass:")) store[cnt++].pass = line.substr(prefixSize);
            }

            return 0;
        }

        inline void write(std::ofstream& out ,const std::string& site , const std::string& user , const std::string& pass){
            out<<std::flush;
            out<<"site:"<<site<<std::endl;
            out<<"user:"<<user<<std::endl;
            out<<"pass:"<<pass<<std::endl;
        }

        void viewPass(){ // wrapper around getPass() because getPass() is a flaming piece of mess 
            std::ifstream in(path);

            if(!getPass(in)){
                std::cout<<" --------------- Secure Password Manager --------------- \n";
                
                for(int i = 0; i < store.size(); i++){
                    std::cout<<std::endl;
                    std::cout<<" Site Name: "<<store[i].site<<"\n";
                    std::cout<<" Username : "<<store[i].user <<"\n";
                    std::cout<<" Password : "<<store[i].pass <<"\n";
                }
            } else {
                std::cout<<"";
            }
        }

        void menu() {
            int choice = 0;

            while (true) {
                std::cout << "\n========== MENU ==========\n";
                std::cout << "1. Add Password\n";
                std::cout << "2. View Passwords\n";
                std::cout << "3. Exit\n";
                std::cout << "Enter choice: ";

                std::cin >> choice;
                std::string dummy;
                std::getline(std::cin, dummy);

                switch (choice) {
                    case 1:
                        addPass();
                        break;

                    case 2:
                        viewPass();
                        break;

                    case 3:
                        std::cout << "Exiting...\n";
                        return;   // exit the function instead of dealing with loop 

                    default:
                        std::cout << "Invalid option. Try again.\n";
                }
            }
        }
};



int main(){
    password Pass;
    if(!Pass.getValidity()){
        std::cout<<"Authentication failed \n";
        return -1;
    }
    Pass.menu();
    
 return 0;
}