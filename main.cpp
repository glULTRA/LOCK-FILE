#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream myfile("MyPassword.lock");

    stringstream ss;
    ss << myfile.rdbuf();
    const char* PASSWORD = ss.str().c_str();

    int choice;
    cout << "1. Unlock\n2. Lock\n";
    cout << "Enter 1 or 2 :";
    cin >> choice;

    if(choice == 1)
    {
        Keep_Trying:
            string pass;
            cout << "Please Enter Password :";
            cin >> pass;
            if(pass == PASSWORD)
            {
                ifstream is_file_locked("isLocked.txt");
                stringstream ss2;
                ss2 << is_file_locked.rdbuf();
                is_file_locked.close();
                if(ss2.str() == "LOCKED"){
                    ofstream unlocked_file("isLocked.txt");
                    unlocked_file << "UNLOCKED";
                    unlocked_file.close();
                }
                else{
                    cout << "It's already Unlocked :)\n";
                    return 0;
                }
                system("attrib -s -h Keep.ans");
                system("ren Keep.ans MyFile.txt");
                ofstream unlocked_file("isLocked.txt");
                unlocked_file << "UNLOCKED";
                return 0;
            }
            else if (pass != PASSWORD){
                cout << "Enter password again (for exit type \"exit\")\n";
                if(pass == "exit") return 0;
                goto Keep_Trying;
            }
    }
    else if(choice == 2)
    {
        Keep_Trying_Old_Password:
            string prev_pass;
            cout << "Please enter prevoius password :";
            cin >> prev_pass;
            if(prev_pass != PASSWORD)
                goto Keep_Trying_Old_Password;
            else{
                ifstream is_file_locked("isLocked.txt");
                stringstream ss2;
                ss2 << is_file_locked.rdbuf();
                is_file_locked.close();
                if(ss2.str() == "LOCKED"){
                    cout << "It's LOCKED you can't change password !";
                    return 0;
                }
                else{
                    ofstream unlocked_file("isLocked.txt");
                    unlocked_file << "LOCKED";
                    unlocked_file.close();
                }
            }
        string new_pass;
        cout << "Enter new passowrd :";
        cin >> new_pass;

        ofstream myfile_input("MyPassword.lock");
        myfile_input << new_pass;
        myfile_input.close();

        system("ren MyFile.txt Keep.ans");
        system("attrib +h +s Keep.ans");
    }

    myfile.close();
    return 0;
}   