#include "menus.h" // هدر مربوطه را اضافه کنید
#include <iostream>    // برای استفاده از cout
#include "functions.h"

void show_administrator_menu(){
    system("cls");
    std::cout << "Welcome to FLibrary framework" << std::endl;
    std::cout << "Here, we have more than hundreds of books information. " << std::endl;
    std::cout << "You can choose below commands to do anything that you want. Enter '\\h' to show this menu. " << std::endl;
    std::cout << "\t 1. Book's options" << std::endl;
    std::cout << "\t 2. Member's options" << std::endl;
    std::cout << "\t 3. Show this help" << std::endl;
    std::cout << "\t 4. Quit" << std::endl;
}

void show_book_options_help(){
    while(true){
        system("cls");
        std::cout << "You can see book's options below. Choose which one you want: " << std::endl;
        std::cout << "\t 1. Show books" << std::endl;
        std::cout << "\t 2. Add new book" << std::endl;
        std::cout << "\t 3. Remove a book" << std::endl;
        std::cout << "\t 4. Edit a book" << std::endl;
        std::cout << "\t 5. Search in book shelves" << std::endl;
        std::cout << "\t 6. Lend a book" << std::endl;
        std::cout << "To clear the screen and showing this menu you can enter \\h or \\cls then press ENTER button. " << std::endl;
        std::cout << "If you want to go back to previous menu, enter '<<back' then press ENTER button. " << std::endl;
        std::string cmd;
        bool a = true;
        while(a){
            std::cout << "CMD> ";
            std::getline(std::cin, cmd);
            if(cmd == "<<back"){
                return;
            }
            if(isValidNumber(cmd) == false){
                if(cmd == "\\h" || cmd == "\\cls"){
                    break;
                }
                if(cmd != ""){
                    std::cout << " - Command '" << cmd << "' is not valid;" << std::endl;
                }
                continue;
            }
            int command = std::stoi(cmd);
            std::vector<Book> books = get_books_list();
            std::string counter = "10";
            counter = books.size() <= 10 ? std::to_string(books.size()) : "10";
            switch (command){
                case 1:                 //1. Show books
                    std::cout << "If you want to go back to last menu, enter '<<back' then press ENTER button. " << std::endl;
                    while(true){
                        std::cout << "[*] Give me the number of books you want to see [default " << counter << "| max " << books.size() << "]: ";
                        std::getline(std::cin, counter);

                        if(counter == "<<back"){
                            break;
                        }
                        if(counter == ""){
                            counter = books.size() <= 10 ? std::to_string(books.size()) : "10";;
                            break;
                        }
                        if(!isValidNumber(counter)){
                            std::cout << " - '" << counter << "' is not a valid number. " << std::endl;
                            continue;
                        }
                        if(std::stoi(counter) <= books.size()){
                            break;
                        }
                        std::cout << " - Number can not be bigger than '" << books.size() << "' " << std::endl;
                    }
                    if(counter == "<<back"){
                        break;
                    }
                    std::cout << "Books information [" << books.size() << " books in the shelves]: " << std::endl;
                    std::cout << "---------------------------------------" << std::endl;
                    for(int i = 0; i < std::stoi(counter); i++){
                        std::cout << "Title: " << books[i].title << std::endl;
                        std::cout << "Author: " << books[i].author << std::endl;
                        std::cout << "Published at: " << books[i].published_year << std::endl;
                        std::cout << "ISBN: " << books[i].isbn << std::endl;
                        std::cout << "Availability: " << books[i].availability << std::endl;
                        std::cout << "---------------------------------------" << std::endl;
                    }
                    if(std::stoi(counter) < books.size()){
                        std::cout << "..." << std::endl;
                    }
                    break;
                case 2:                 //2. Add new book
                    std::cout << "To add a new book, please fill the below form ." << std::endl;
                    std::cout << "To go back to last menu, please enter '<<back' at any situation then press ENTER button." << std::endl;
                    while(true){
                        Book new_book;
                        while(true){
                            std::cout << "[*] Enter book title: ";
                            std::getline(std::cin, new_book.title);
                            if(new_book.title == ""){
                                continue;
                            }
                            break;
                        }
                        if(new_book.title == "<<back"){
                            break;
                        }

                        while(true){
                            std::cout << "[*] Enter author's name: ";
                            std::getline(std::cin, new_book.author);
                            if(new_book.author == ""){
                                continue;
                            }
                            break;
                        }
                        if(new_book.author == "<<back"){
                            break;
                        }
                        while(true){
                            std::string published_year;
                            std::cout << "[*] Enter book's publish year: ";
                            std::getline(std::cin, published_year);
                            if(published_year == ""){
                                continue;
                            }
                            if(!isValidNumber(published_year)){
                                std::cout << " - '" << published_year << "' is not a valid value .\n";
                                continue;
                            }
                            new_book.published_year = published_year;
                            break;
                        }
                        if(new_book.published_year == "<<back"){
                            break;
                        }

                        
                        while(true){
                            std::string isbn;
                            std::cout << "[*] Enter book's isbn: ";
                            std::getline(std::cin, isbn);
                            if(isbn == ""){
                                continue;
                            }
                            // Check isbn availability
                            if(check_isbn_availability(isbn) == false){
                                std::cout << " - '" << isbn << "' is not available. " << std::endl;
                                continue;
                            }

                            if(isbn.length() != 12){
                                std::cout << " - ISBN can not be less than 12 characters.\n";
                                continue;
                            }
                            new_book.isbn = isbn;
                            break;
                        }
                        if(new_book.isbn == "<<back"){
                            break;
                        }

                        new_book.availability = 1;
                        add_new_book(new_book);
                        std::cout << " + '" << new_book.title << "' is added successfully. \n";

                        break;
                    }                  
                    break;
                case 3:                 //3. Remove a book
                    while(true){
                        std::string query;
                        std::cout << "[*] Enter book's title, author or ISBN: ";
                        std::getline(std::cin, query);
                        if(query == ""){
                            continue;
                        }
                        if(query == "<<back"){
                            break;
                        }
                        std::vector<Book> books = search_in_books(query);
                        if(books.size() > 1){
                            std::cout << "Search result contains " << books.size() << " books" << std::endl;
                            for(int i = 0; i < books.size(); i++){
                                std::cout << "Title: " << books[i].title << std::endl;
                                std::cout << "Author: " << books[i].author << std::endl;
                                std::cout << "Published at: " << books[i].published_year << std::endl;
                                std::cout << "ISBN: " << books[i].isbn << std::endl;
                                std::cout << "Availability: " << books[i].availability << std::endl;
                                std::cout << "---------------------------------------" << std::endl;
                            }
                            while(true){
                                std::string isbn;
                                std::cout << "[*] Enter ISBN of the book you want to remove: ";
                                std::getline(std::cin, isbn);

                                if(isbn == "<<back"){
                                    break;
                                }
                                if(isbn == ""){
                                    continue;
                                }
                                if(isbn.size() != 12){
                                    std::cout << " - ISBN can not be less than 12 characters.\n";
                                    continue;
                                }

                                if(search_in_books(isbn).size() == 0){
                                    std::cout << " - There is no book with '" << isbn << "' as ISBN .\n";
                                    continue;
                                }
                                Book book = search_in_books(isbn)[0];
                                std::cout << "Title: " << book.title << std::endl;
                                std::cout << "Author: " << book.author << std::endl;
                                std::cout << "Published at: " << book.published_year << std::endl;
                                std::cout << "ISBN: " << book.isbn << std::endl;
                                std::cout << "Availability: " << book.availability << std::endl;
                                std::cout << "---------------------------------------" << std::endl;
                                std::string confirm = "N";
                                while(true){
                                    std::cout << "[*] Do you want to remove it: [y/N] ";
                                    std::getline(std::cin, confirm);
                                    if(confirm == "n" || confirm == "N"){
                                        std::cout << "Book '" << isbn << "' deletion is canceled .\n";
                                        break;
                                    }
                                    if(confirm == "y" || confirm == "Y"){
                                        // Remove the book;
                                        remove_book(book);
                                        std::cout << "Book '" << isbn << "' is removed .\n";
                                    }
                                    break;
                                }

                            }
                        }else if(books.size() == 1){
                            Book book = books[0];
                            std::cout << "Title: " << book.title << std::endl;
                            std::cout << "Author: " << book.author << std::endl;
                            std::cout << "Published at: " << book.published_year << std::endl;
                            std::cout << "ISBN: " << book.isbn << std::endl;
                            std::cout << "Availability: " << book.availability << std::endl;
                            std::cout << "---------------------------------------" << std::endl;
                            std::string confirm = "N";
                            while(true){
                                std::cout << "[*] Do you want to remove it: [y/N] ";
                                std::getline(std::cin, confirm);
                                if(confirm == "n" || confirm == "N"){
                                    std::cout << "Book '" << book.isbn << "' deletion is canceled .\n";
                                    break;
                                }
                                if(confirm == "y" || confirm == "Y"){
                                    // Remove the book;
                                    remove_book(book);
                                    std::cout << "Book '" << book.isbn << "' is removed .\n";
                                }
                                break;
                            }
                        }else{
                            std::cout << " - No book has been found .\n";
                        }
                    }
                    break;
                case 4:                 //4. Edit a book
                    while(true){
                        std::string query;
                        std::cout << "[*] Enter book's title, author or ISBN: ";
                        std::getline(std::cin, query);
                        if(query == ""){
                            continue;
                        }
                        if(query == "<<back"){
                            break;
                        }
                        std::vector<Book> books = search_in_books(query);
                        if(books.size() > 1){
                            std::cout << "Search result contains " << books.size() << " books" << std::endl;
                            for(int i = 0; i < books.size(); i++){
                                std::cout << "Title: " << books[i].title << std::endl;
                                std::cout << "Author: " << books[i].author << std::endl;
                                std::cout << "Published at: " << books[i].published_year << std::endl;
                                std::cout << "ISBN: " << books[i].isbn << std::endl;
                                std::cout << "Availability: " << books[i].availability << std::endl;
                                std::cout << "---------------------------------------" << std::endl;
                            }
                            while(true){
                                std::string isbn;
                                std::cout << "[*] Enter ISBN of the book you want to edit: ";
                                std::getline(std::cin, isbn);

                                if(isbn == "<<back"){
                                    break;
                                }
                                if(isbn == ""){
                                    continue;
                                }
                                if(isbn.size() != 12){
                                    std::cout << " - ISBN can not be less than 12 characters.\n";
                                    continue;
                                }

                                if(search_in_books(isbn).size() == 0){
                                    std::cout << " - There is no book with '" << isbn << "' as ISBN .\n";
                                    continue;
                                }
                                Book book = search_in_books(isbn)[0];
                                std::cout << "Title: " << book.title << std::endl;
                                std::cout << "Author: " << book.author << std::endl;
                                std::cout << "Published at: " << book.published_year << std::endl;
                                std::cout << "ISBN: " << book.isbn << std::endl;
                                std::cout << "Availability: " << book.availability << std::endl;
                                std::cout << "---------------------------------------" << std::endl;
                                std::cout << "Leave it blank if you do not want to change any of values. \n";
                                std::cout << "If you want to cancel editing, Enter '<<back' then press ENTER button.\n";
                                // Editing
                                Book editted_book;
                                while(true){
                                    std::cout << "[*] Enter book title [" << book.title << "]: ";
                                    std::getline(std::cin, editted_book.title);
                                    if(editted_book.title == ""){
                                        editted_book.title = book.title;
                                    }
                                    break;
                                }
                                if(editted_book.title == "<<back"){
                                    break;
                                }

                                while(true){
                                    std::cout << "[*] Enter author's name [" << book.author << "]: ";
                                    std::getline(std::cin, editted_book.author);
                                    if(editted_book.author == ""){
                                        editted_book.author = book.author;
                                    }
                                    break;
                                }
                                if(editted_book.author == "<<back"){
                                    break;
                                }
                                while(true){
                                    std::string published_year;
                                    std::cout << "[*] Enter book's publish year [" << book.published_year << "]: ";
                                    std::getline(std::cin, published_year);
                                    if(published_year == ""){
                                        editted_book.published_year = book.published_year;
                                        break;
                                    }
                                    if(!isValidNumber(published_year)){
                                        std::cout << " - '" << published_year << "' is not a valid value .\n";
                                        continue;
                                    }
                                    editted_book.published_year = published_year;
                                    break;
                                }
                                if(editted_book.published_year == "<<back"){
                                    break;
                                }

                                
                                while(true){
                                    std::string isbn;
                                    std::cout << "[*] Enter book's isbn [" << book.isbn << "]: ";
                                    std::getline(std::cin, isbn);
                                    if(isbn == ""){
                                        editted_book.isbn = book.isbn;
                                        break;
                                    }
                                    // Check isbn availability
                                    if(check_isbn_availability(isbn) == false){
                                        Book temp_book = search_in_books(isbn)[0];
                                        if(temp_book.isbn == book.isbn){
                                            editted_book.isbn = isbn;
                                            break;
                                        }
                                        std::cout << " - '" << isbn << "' is not available. " << std::endl;
                                        continue;
                                    }

                                    if(isbn.length() != 12){
                                        std::cout << " - ISBN can not be less than 12 characters.\n";
                                        continue;
                                    }
                                    editted_book.isbn = isbn;
                                    break;
                                }
                                if(editted_book.isbn == "<<back"){
                                    break;
                                }

                                editted_book.availability = 1;
                                // Do the edition
                                std::cout << "Title: " << editted_book.title << std::endl;
                                std::cout << "Author: " << editted_book.author << std::endl;
                                std::cout << "Published at: " << editted_book.published_year << std::endl;
                                std::cout << "ISBN: " << editted_book.isbn << std::endl;
                                std::cout << "Availability: " << editted_book.availability << std::endl;
                                std::cout << "---------------------------------------" << std::endl;
                                // Editing process
                                editing_abook(book, editted_book);
                                std::cout << " + Book is edited successfully.\n";
                            }
                        }else if(books.size() == 1){
                            Book book = books[0];
                            std::cout << "Title: " << book.title << std::endl;
                            std::cout << "Author: " << book.author << std::endl;
                            std::cout << "Published at: " << book.published_year << std::endl;
                            std::cout << "ISBN: " << book.isbn << std::endl;
                            std::cout << "Availability: " << book.availability << std::endl;
                            std::cout << "---------------------------------------" << std::endl;
                            // Editing
                            Book editted_book;
                            while(true){
                                std::cout << "[*] Enter book title [" << book.title << "]: ";
                                std::getline(std::cin, editted_book.title);
                                if(editted_book.title == ""){
                                    editted_book.title = book.title;
                                }
                                break;
                            }
                            if(editted_book.title == "<<back"){
                                break;
                            }

                            while(true){
                                std::cout << "[*] Enter author's name [" << book.author << "]: ";
                                std::getline(std::cin, editted_book.author);
                                if(editted_book.author == ""){
                                    editted_book.author = book.author;
                                }
                                break;
                            }
                            if(editted_book.author == "<<back"){
                                break;
                            }
                            while(true){
                                std::string published_year;
                                std::cout << "[*] Enter book's publish year [" << book.published_year << "]: ";
                                std::getline(std::cin, published_year);
                                if(published_year == ""){
                                    editted_book.published_year = book.published_year;
                                    break;
                                }
                                if(!isValidNumber(published_year)){
                                    std::cout << " - '" << published_year << "' is not a valid value .\n";
                                    continue;
                                }
                                editted_book.published_year = published_year;
                                break;
                            }
                            if(editted_book.published_year == "<<back"){
                                break;
                            }

                            
                            while(true){
                                std::string isbn;
                                std::cout << "[*] Enter book's isbn [" << book.isbn << "]: ";
                                std::getline(std::cin, isbn);
                                if(isbn == ""){
                                    editted_book.isbn = book.isbn;
                                    break;
                                }
                                // Check isbn availability
                                if(check_isbn_availability(isbn) == false){
                                    Book temp_book = search_in_books(isbn)[0];
                                    if(temp_book.isbn == book.isbn){
                                        editted_book.isbn = isbn;
                                        break;
                                    }
                                    std::cout << " - '" << isbn << "' is not available. " << std::endl;
                                    continue;
                                }

                                if(isbn.length() != 12){
                                    std::cout << " - ISBN can not be less than 12 characters.\n";
                                    continue;
                                }
                                editted_book.isbn = isbn;
                                break;
                            }
                            if(editted_book.isbn == "<<back"){
                                break;
                            }

                            editted_book.availability = 1;
                            // Do the edition
                            std::cout << "Title: " << editted_book.title << std::endl;
                            std::cout << "Author: " << editted_book.author << std::endl;
                            std::cout << "Published at: " << editted_book.published_year << std::endl;
                            std::cout << "ISBN: " << editted_book.isbn << std::endl;
                            std::cout << "Availability: " << editted_book.availability << std::endl;
                            std::cout << "---------------------------------------" << std::endl;
                            // Editing process
                            editing_abook(book, editted_book);
                            std::cout << " + Book is edited successfully.\n";
                            
                        }else{
                            std::cout << " - No book has been found .\n";
                        }
                    }
                    break;
                case 5:                 //5. Search in book shelves
                    while(true){
                        std::string query;
                        std::cout << "Search in the shelves of FLibrary\n";
                        std::cout << "[*] Enter book's title, author or ISBN to search: ";
                        std::getline(std::cin, query);
                        if(query == ""){
                            continue;
                        }
                        if(query == "<<back"){
                            break;
                        }
                        std::vector<Book> books = search_in_books(query);
                        std::cout << "Search result [" << books.size() << " books have been found]: " << std::endl;
                        std::cout << "---------------------------------------" << std::endl;
                        for(int i = 0; i < books.size(); i++){
                            std::cout << "Title: " << books[i].title << std::endl;
                            std::cout << "Author: " << books[i].author << std::endl;
                            std::cout << "Published at: " << books[i].published_year << std::endl;
                            std::cout << "ISBN: " << books[i].isbn << std::endl;
                            std::cout << "Availability: " << books[i].availability << std::endl;
                            std::cout << "---------------------------------------" << std::endl;
                        }
                    }
                    break;
                case 6:                 //6. Lend a book
                    break;
                default:
                    std::cout << " - Command '" << cmd << "' is not valid;" << std::endl;
                    break;
            }
        }
    }
}

void show_members_options(){
    while(true){
        system("cls");
        std::cout << "You can see Members's options below. Choose which one you want: " << std::endl;
        std::cout << "\t 1. Show members" << std::endl;
        std::cout << "\t 2. Add new member" << std::endl;
        std::cout << "\t 3. Remove a member" << std::endl;
        std::cout << "\t 4. Edit a member" << std::endl;
        std::cout << "\t 5. Search in members" << std::endl;
        std::cout << "To clear the screen and showing this menu you can enter \\h or \\cls then press ENTER button. " << std::endl;
        std::cout << "If you want to go back to previous menu, enter '<<back' then press ENTER button. " << std::endl;
        std::string cmd;
        bool a = true;
        while(a){
            std::cout << "CMD> ";
            std::getline(std::cin, cmd);
            if(cmd == "<<back"){
                return;
            }
            if(isValidNumber(cmd) == false){
                if(cmd == "\\h" || cmd == "\\cls"){
                    break;
                }
                if(cmd != ""){
                    std::cout << " - Command '" << cmd << "' is not valid;" << std::endl;
                }
                continue;
            }
            int command = std::stoi(cmd);
            std::vector<User> members = get_users();
            std::string counter = "10";
            counter = members.size() <= 10 ? std::to_string(members.size()) : "10";
            switch (command){
                case 1:
                    // counter = members.size() <= 10 ? std::to_string(members.size()) : "10";
                    std::cout << "If you want to go back to last menu, enter '<<back' then press ENTER button. " << std::endl;
                    while(true){
                        std::cout << "[*] Give me the number of members you want to see [default " << counter << "| max " << members.size() << "]: ";
                        std::getline(std::cin, counter);

                        if(counter == "<<back"){
                            break;
                        }
                        if(counter == ""){
                            counter = members.size() <= 10 ? std::to_string(members.size()) : "10";
                            break;
                        }
                        if(!isValidNumber(counter)){
                            std::cout << " - '" << counter << "' is not a valid number. " << std::endl;
                            continue;
                        }
                        if(std::stoi(counter) <= members.size()){
                            break;
                        }
                        std::cout << " - Number can not be bigger than '" << members.size() << "' " << std::endl;
                    }
                    if(counter == "<<back"){
                        break;
                    }
                    std::cout << "Member's information [" << members.size() << " members]: " << std::endl;
                    std::cout << "---------------------------------------" << std::endl;
                    std::cout << counter << ":" << members.size() << "\n";

                    for(int i = 0; i < std::stoi(counter); i++){
                        std::cout << "Username: " << members[i].username << std::endl;
                        std::cout << "Phone Number: " << members[i].phone << std::endl;
                        std::cout << "Role: " << members[i].role << std::endl;
                        std::cout << "Status: " << members[i].status << std::endl;
                        std::cout << "---------------------------------------" << std::endl;
                    }
                    if(std::stoi(counter) < members.size()){
                        std::cout << "..." << std::endl;
                    }
                    break;
                case 2:                 // 2. Add new member
                    std::cout << "Adding new member to libary\n";
                    std::cout << "Please fill the requested information below.";
                    std::cout << "To cancel and go back to previous menu, enter '<<back' then press ENTER button.\n";
                    while(true){
                        std::string username;
                        std::string password;
                        std::string password2;
                        std::string phone;
                        bool a = true;
                        while(a){
                            std::cout << "[*] Please enter username: ";
                            std::getline(std::cin, username);
                            if(username == "<<back"){
                                a = false;
                                break;
                            }
                            if(username == ""){
                                continue;
                            }
                            if(check_username_availability(username) == false){
                                std::cout << " - Username '" << username << "' is not available.\n";
                                continue;
                            }
                            break;
                        }
                        while(a){
                            std::cout << "[*] Please enter password: ";
                            std::getline(std::cin, password);
                            if(password == "<<back"){
                                a = false;
                                break;
                            }
                            std::cout << "[*] Please enter password confirmation: ";
                            std::getline(std::cin, password2);
                            if(password2 == "<<back"){
                                a = false;
                                break;
                            }
                            if(password == "" || password2 == ""){
                                std::cout << " - Password can not be empty.\n";
                                continue;
                            }
                            if((password != password2)){
                                std::cout << " - Password and its confirmation are not matched. \n";
                                continue;
                            }
                            if(password2.length() < 5){
                                std::cout << " - Password should be at least 6 characters. \n";
                                continue;
                            }
                            break;
                        }
                        while(a){
                            std::cout << "[*] Please enter phone number: ";
                            std::getline(std::cin, phone);
                            if(phone == "<<back"){
                                a = false;
                                break;
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
                            User user;
                            user.password = password2;
                            user.phone = phone;
                            user.role = "user";
                            user.status = "active";
                            user.username = username;
                            add_new_user(user);
                            break;
                        }
                        break;
                    }
                    break;
                case 3:                 // 3. Remove a member
                    std::cout << "Removing a member from libary\n";
                    std::cout << "To go cancel and go back to previous menu, enter '<<back' then press ENTER button.\n";
                    while(true){
                        std::string username;
                        std::cout << "[*] Please enter username: ";
                        std::getline(std::cin, username);
                        if(username == ""){
                            continue;
                        }
                        if(username == "<<back"){
                            break;
                        }
                        if(check_username_availability(username)){
                            std::cout << " - username '" << username << "' not found.\n";
                            continue;
                        }
                        User user = get_user(username);
                        remove_user(user);
                        break;
                    }
                    break;
                case 4:                 // 4. Edit a member
                    std::cout << "Editing a member\n";
                    std::cout << "Please fill the requested information below.";
                    std::cout << "Leave it blank if you do not want to change any of values. \n";
                    std::cout << "To cancel and go back to previous menu, enter '<<back' then press ENTER button.\n";
                    while(true){
                        std::string username;
                        std::cout << "[*] Please enter username to search: ";
                        std::getline(std::cin, username);
                        if(username == ""){
                            continue;
                        }
                        if(username == "<<back"){
                            break;
                        }
                        if(check_username_availability(username)){
                            std::cout << " - username '" << username << "' not found.\n";
                            continue;
                        }
                        User user = get_user(username);
                        std::cout << "Username: " << user.username << std::endl;
                        std::cout << "Phone Number: " << user.phone << std::endl;
                        std::cout << "Role: " << user.role << std::endl;
                        std::cout << "Status: " << user.status << std::endl;
                        std::cout << "---------------------------------------" << std::endl;
                        User editted_user;
                        bool a = true;
                        while(a){
                            std::cout << "[*] Please enter username [" << user.username << "]: ";
                            std::getline(std::cin, editted_user.username);
                            if(editted_user.username == "<<back"){
                                a = false;
                                break;
                            }
                            if(editted_user.username == ""){
                                editted_user.username = user.username;
                                break;
                            }
                            if(check_username_availability(editted_user.username) == false){
                                std::cout << " - Username '" << editted_user.username << "' is not available.\n";
                                continue;
                            }
                            break;
                        }
                        while(a){
                            std::cout << "[*] Please enter role, admin or user [" << user.role << "]: ";
                            std::getline(std::cin, editted_user.role);
                            if(editted_user.role == "<<back"){
                                a = false;
                                break;
                            }
                            if(editted_user.role == ""){
                                editted_user.role = user.role;
                                break;
                            }

                            if(editted_user.role != "admin"){
                                if(editted_user.role != "user"){
                                    std::cout << " - Role can just be 'admin' or 'user'. \n";
                                    continue;
                                }
                            }
                            break;
                        }
                        while(a){
                            std::cout << "[*] Please enter user's status, active or inactive [" << user.status << "]: ";
                            std::getline(std::cin, editted_user.status);
                            if(editted_user.status == "<<back"){
                                a = false;
                                break;
                            }
                            if(editted_user.status == ""){
                                editted_user.status = user.status;
                                break;
                            }
                            
                            if(editted_user.status != "active"){
                                if(editted_user.status != "inactive"){
                                    std::cout << " - User's status can just be 'active' or 'inactive'. \n";
                                    continue;
                                }
                            }
                            break;
                        }
                        while(a){
                            std::cout << "[*] Please enter password [CENSORED_PASSWORD]: ";
                            std::getline(std::cin, editted_user.password);
                            if(editted_user.password == "<<back"){
                                a = false;
                                break;
                            }
                            if(editted_user.password == ""){
                                editted_user.password = user.password;
                                break;
                            }
                            if(editted_user.password.length() < 5){
                                std::cout << " - Password should be at least 6 characters. \n";
                                continue;
                            }
                            break;
                        }
                        while(a){
                            std::cout << "[*] Please enter phone number [" << user.phone << "]: ";
                            std::getline(std::cin, editted_user.phone);
                            if(editted_user.phone == "<<back"){
                                a = false;
                                break;
                            }
                            if(editted_user.phone == ""){
                                editted_user.phone = user.phone;
                            }
                            if(editted_user.phone.length() != 11){
                                std::cout << " - Phone number should contain 11 digits.\n";
                                continue;
                            }
                            if(!isValidNumber(editted_user.phone)){
                                std::cout << " - Phone number just can contain digits.\n";
                                continue;
                            }
                            if(check_phone_availability(editted_user.phone) == false){
                                User tmp_user = get_user_by_phone(editted_user.phone);
                                if(tmp_user.phone != user.phone){
                                    std::cout << " - Phone number is not available. \n";
                                    continue;
                                }
                            }
                            edit_auser(user, editted_user);
                            break;
                        }
                        break;
                    }
                    break;
                case 5:                 // 5. Search in members
                    std::cout << "Search in members\n";
                    std::cout << "To cancel and go back to previous menu, enter '<<back' then press ENTER button.\n";
                    while(true){
                        std::string query;
                        std::cout << "[*] Please enter username, phone number, role or status: ";
                        std::getline(std::cin, query);
                        if(query == ""){
                            continue;
                        }
                        if(query == "<<back"){
                            break;
                        }

                        std::vector<User> users = search_in_users(query);
                        std::cout << "Search result [" << users.size() << " members]: " << std::endl;
                        std::cout << "---------------------------------------" << std::endl;
                        for(int i = 0; i < users.size(); i++){
                            std::cout << "Username: " << users[i].username << std::endl;
                            std::cout << "Phone Number: " << users[i].phone << std::endl;
                            std::cout << "Role: " << users[i].role << std::endl;
                            std::cout << "Status: " << users[i].status << std::endl;
                            std::cout << "---------------------------------------" << std::endl;
                        }
                    }
                    break;
                default:
                    std::cout << " - Command '" << cmd << "' is not valid;" << std::endl;
                    break;
            }
        }
    }
}