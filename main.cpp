#include <iostream>
#include "headers/functions.h"
#include "headers/menus.h"
#include "headers/main_menu.h"


int main(){
    std::string sessionsid;
    sessionsid = get_session_id();
    while(true){
        if(sessionsid != ""){
            break;
        }
        show_main_menu();
        std::string cmd;
        bool a = true;
        while(a){
            std::cout << "CMD> ";
            std::getline(std::cin, cmd);
            if(isValidNumber(cmd) == false){
                if(cmd == "\\h"){
                    break;
                }
                if(cmd != ""){
                    std::cout << " - Command '" << cmd << "' is not valid;" << std::endl;
                }
                continue;
            }
            int command = std::stoi(cmd);
            switch (command){
                case 1:                 // 1. Login
                    sessionsid = login_form();
                    a = false;
                    break;
                case 2:                 // 3. Registration
                    registration_form();
                    a = false;
                    break;
                case 3:                 // 4. Quit
                    destroy_session();
                    std::cout << "Ok bye :(";
                    return 0;
                default:
                    std::cout << " - Command '" << command << "' is not valid;" << std::endl;
                    break;
            }
        }
    } 
    
    User user = get_user_info(sessionsid);
    if(user.status == "inactive"){
        system("cls");
        std::cout << "We are so sorry, your account is inactive.\n";
        std::cout << "To activate it, please contact administrator.\n";
        std::cout << "See you soon .";
        destroy_session();
        return 0;
    }
    // User Menu
    if(user.role == "user" && user.status == "active"){
        destroy_session();
        return 0;
    }

    // Administrator menu
    if(user.role == "admin" && user.status == "active"){
        while(true){
            show_administrator_menu();
            std::string cmd;
            bool a = true;
            while(a){
                std::cout << "CMD> ";
                std::getline(std::cin, cmd);
                if(isValidNumber(cmd) == false){
                    if(cmd == "\\h"){
                        break;
                    }
                    if(cmd != ""){
                        std::cout << " - Command '" << cmd << "' is not valid;" << std::endl;
                    }
                    continue;
                }
                int command = std::stoi(cmd);
                switch (command){
                    case 1:
                        show_book_options_help();
                        a = false;
                        break;
                    case 2:
                        show_members_options();
                        a = false;
                        break;
                    case 3:
                        a = false;
                        break;
                    case 4:
                        destroy_session();
                        std::cout << "Ok bye :(";
                        return 0;
                    default:
                        std::cout << " - Command '" << command << "' is not valid;" << std::endl;
                        break;
                }
            }
        }
    }
    
}