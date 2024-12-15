#include "main_menu.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

void show_main_menu(){
    system("cls");
    std::cout << "Welcome to FLibrary framework" << std::endl;
    std::cout << "Here, we have more than hundreds of books information. Enter '\\h' to show this menu." << std::endl;
    std::cout << "\t 1. Login" << std::endl;
    std::cout << "\t 2. Registration" << std::endl;
    std::cout << "\t 3. Quit" << std::endl;
}

std::string login_form(){
    std::string sessionid = "";
    int counter = 0;
    while(true){
        system("cls");
        std::cout << "Welcome to FLibrary framework" << std::endl;
        std::cout << "Please enter your information to log in" << std::endl;
        std::cout << "To go back to last menu, please enter '<<back' text then press ENTER button." << std::endl;
        if(counter > 0){
            std::cout << " - Username or password is wrong. Please try again. \n";
        }
        std::string username;
        std::string password;
        std::cout << "[*] Please enter your username: ";
        std::getline(std::cin, username);
        if(username == "<<back"){
            return sessionid;
        }
        if(username != ""){
            std::cout << "[*] Please enter your password: ";
            std::getline(std::cin, password);
            if(password == "<<back"){
                return sessionid;

            }
            std::fstream f_("dbs/users.db");
            if (!f_.is_open()) {
                std::cout << "Error: Could not connect to users database!" << std::endl;
                return sessionid;
            }else{
                std::string line; 
                while (std::getline(f_, line)) {
                    User user;
                    if(line[0] != '#'){
                        user = user_line_splitter(line, '|');
                        if(user.username == username && user.password == password){
                            f_.close();
                            sessionid = generate_session_id(username);
                            std::ofstream fsession("dbs/session.db");
                            fsession << "# This file is auto generated.\n";
                            fsession << "# Please do not change this file.\n";
                            fsession << sessionid;
                            fsession.close();
                            return sessionid;
                        }
                    }
                }
                f_.close();
                counter++;
            }
        }
    }
    return sessionid;
}

void registration_form(){
    system("cls");
    std::cout << "Welcome to FLibrary framework" << std::endl;
    std::cout << "Please enter your information." << std::endl;
    std::cout << "To go back to last menu, please enter '<<back' then press ENTER button." << std::endl;
    while(true){
        std::string username;
        std::string password;
        std::string password2;
        std::string phone;
        std::cout << "[*] Please enter your username: ";
        std::getline(std::cin, username);
        if(username == "<<back"){
            return;
        }
        if(username == ""){
            continue;
        }
        if(check_username_availability(username) == false){
            std::cout << " - Username '" << username << "' is not available.\n";
            continue;
        }
        while(true){
            std::cout << "[*] Please enter your password: ";
            std::getline(std::cin, password);
            if(password == "<<back"){
                return;
            }
            std::cout << "[*] Please enter your password confirmation: ";
            std::getline(std::cin, password2);
            if(password2 == "<<back"){
                return;
            }
            if(password == "" || password2 == ""){
                std::cout << " - Password can not be empty.\n";
                continue;
            }
            if((password != password2)){
                std::cout << " - Your password and its confirmation are not matched. \n";
                continue;
            }
            if(password2.length() < 5){
                std::cout << " - Your password should be at least 6 characters. \n";
                continue;
            }
            break;
        }

        while(true){
            std::cout << "[*] Please enter your phone number: ";
            std::getline(std::cin, phone);
            if(phone == "<<back"){
                return;
            }
            if(phone == ""){
                std::cout << " - Phone number can not be empty.\n";
                continue;
            }
            if(phone.length() != 11){
                std::cout << " - Phone number should contain 11 digits.\n";
                continue;
            }
            if(!isValidNumber(phone)){
                std::cout << " - Phone number just can contain digits.\n";
                continue;
            }
            if(check_phone_availability(phone) == false){
                std::cout << " - Phone number is not available. \n";
                continue;
            }
            break;
        }
        User user;
        user.password = password2;
        user.phone = phone;
        user.role = "user";
        user.status = "active";
        user.username = username;
        add_new_user(user);
        return;
    }  
}