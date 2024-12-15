#include "functions.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool isValidNumber(const std::string& input) {
    if (input.empty()) {
        return false; 
    }
    for (char c : input) {
        if (!isdigit(c)) {
            return false; 
        }
    }
    return true;
}

std::vector<std::string> session_id_splitter(const std::string& str, char separator) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(separator);

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start)); // بخش جدا شده
        start = end + 1; // به بخش بعدی بروید
        end = str.find(separator, start);
    }
    result.push_back(str.substr(start)); // آخرین بخش
    return result;
}

User user_line_splitter(const std::string& str, char separator) {
    std::vector<std::string> result;
    std::istringstream ss(str); // ساخت stream برای پردازش رشته
    std::string token;

    while (std::getline(ss, token, separator)) {
        result.push_back(token); // اضافه کردن هر بخش جدا شده به لیست
    }
    User user;
    user.username = result[0];
    user.password = result[1];
    user.role = result[2];
    user.status = result[3];
    user.phone = result[4];
    return user;
}


Book book_line_splitter(const std::string& str, char separator) {
    std::vector<std::string> result;
    std::istringstream ss(str);
    std::string token;

    while (std::getline(ss, token, separator)) {
        result.push_back(token);
    }
    Book book;
    book.title = result[0];
    book.author = result[1];
    book.published_year = result[2];
    book.isbn = result[3];
    book.availability = std::stoi(result[4]);
    return book;
}

User get_user_info(std::string sessionid){
    std::string username = session_id_splitter(sessionid, '|')[1];
    std::fstream f_("dbs/users.db");
    std::string line; 
    while (std::getline(f_, line)) {
        User user_inline;
        if(line[0] != '#'){
            user_inline = user_line_splitter(line, '|');
            if(user_inline.username == username){
                return user_inline;
            }
        }
    }
    f_.close();
    User user;
    user.username = "";
    user.password = "";
    user.role = "";
    user.status = "";
    user.phone = "";
    return user;
}

std::string get_session_id(){
    std::string sessionid = "";
    std::fstream f_("dbs/session.db");
    std::string line; 
    while (std::getline(f_, line)) {
        if(line[0] != '#'){
            sessionid = line;
        }
    }
    f_.close();
    return sessionid;
}

void destroy_session(){
    std::ofstream fsession("dbs/session.db");
    fsession << "# This file is auto generated.\n";
    fsession << "# Please do not change this file.";
    fsession.close();
}

std::string generate_session_id(std::string username) {
    std::string randomNumber = "";
    for (int i = 0; i < 16; ++i) {
        randomNumber += std::to_string(rand() % 10);  // افزودن یک رقم تصادفی (۰ تا ۹)
    }
    return randomNumber + '|' + username;
}

bool check_username_availability(std::string username){
    std::fstream f_("dbs/users.db");
    std::string line; 
    while (std::getline(f_, line)) {
        User user_inline;
        if(line[0] != '#'){
            user_inline = user_line_splitter(line, '|');
            if(user_inline.username == username){
                return false;
            }
        }
    }
    return true;
}

bool check_phone_availability(std::string phone){
    std::fstream f_("dbs/users.db");
    std::string line; 
    while (std::getline(f_, line)) {
        User user_inline;
        if(line[0] != '#'){
            user_inline = user_line_splitter(line, '|');
            if(user_inline.phone == phone){
                return false;
            }
        }
    }
    return true;
}

void add_new_user(User user){
    std::string user_line = user.username + "|" + user.password + "|" + user.role + "|" + user.status + "|" + user.phone + "\n";
    std::ofstream f_;
    f_.open("dbs/users.db", std::ios::app);
    f_ << user_line;
    f_.close();
}

void edit_auser(User old_user, User new_user){
    remove_user(old_user);
    add_new_user(new_user);
}

User get_user(std::string username){
    std::fstream f_("dbs/users.db");
    std::string line; 
    while (std::getline(f_, line)) {
        User user_inline;
        if(line[0] != '#'){
            user_inline = user_line_splitter(line, '|');
            if(user_inline.username == username){
                return user_inline;
            }
        }
    }
    f_.close();
    User user;
    user.username = "";
    user.password = "";
    user.role = "";
    user.status = "";
    user.phone = "";
    return user;
}

std::vector<User> search_in_users(std::string query){
    std::fstream f_("dbs/users.db");
    std::string line; 
    std::vector<User> users;
    while (std::getline(f_, line)) {
        User user_inline;
        if(line[0] != '#'){
            user_inline = user_line_splitter(line, '|');
            if(user_inline.username.find(query) < user_inline.username.length()){
                users.push_back(user_inline);
            }
            if(user_inline.role.find(query) < user_inline.role.length()){
                users.push_back(user_inline);
            }
            if(user_inline.phone.find(query) < user_inline.phone.length()){
                users.push_back(user_inline);
            }
            if(user_inline.status.find(query) < user_inline.status.length()){
                users.push_back(user_inline);
            }
        }
    }
    return users;
}


User get_user_by_phone(std::string phone){
    std::fstream f_("dbs/users.db");
    std::string line; 
    while (std::getline(f_, line)) {
        User user_inline;
        if(line[0] != '#'){
            user_inline = user_line_splitter(line, '|');
            if(user_inline.phone == phone){
                return user_inline;
            }
        }
    }
    f_.close();
    User user;
    user.username = "";
    user.password = "";
    user.role = "";
    user.status = "";
    user.phone = "";
    return user;
}


void remove_user(User user){
    std::fstream f_("dbs/users.db");
    std::ofstream f_2;
    f_2.open("dbs/users_tmp.db");
    std::string line;
    while (std::getline(f_, line)) {
        if(line[0] != '#'){
            User user2 = user_line_splitter(line, '|');
            if((user2.username == user.username)){
                continue;
            }
            f_2 << line << std::endl;
        }else{
            f_2 << line << std::endl;
        }
    }
    f_.close();
    f_2.close();
    std::fstream f2_("dbs/users_tmp.db");
    std::ofstream f2_2;
    f2_2.open("dbs/users.db");
    while (std::getline(f2_, line)) {
        f2_2 << line << std::endl;
    }
    f2_.close();
    f2_2.close();
    system("del dbs\\users_tmp.db");
}

std::vector<User> get_users(){
    std::vector<User> users;
    std::fstream f_("dbs/users.db");
    std::string line; 
    while (std::getline(f_, line)) {
        User user;
        if(line[0] == '#' || line.length() == 0){
            continue;
        }
        user = user_line_splitter(line, '|');
        users.push_back(user);
    }
    return users;
}

std::vector<Book> get_books_list(){
    std::vector<Book> books;
    std::fstream f_("dbs/books.db");
    std::string line; 
    while (std::getline(f_, line)) {
        Book book;
        if(line[0] != '#'){
            book = book_line_splitter(line, '|');
            books.push_back(book);
        }
    }
    return books;
}

void add_new_book(Book book){
    std::string book_line = book.title + "|" + book.author + "|" + book.published_year + "|" + book.isbn + "|" + std::to_string(book.availability) + "\n";
    std::ofstream f_;
    f_.open("dbs/books.db", std::ios::app);
    f_ << book_line;
    f_.close();
}

bool check_isbn_availability(std::string isbn){
    std::vector<Book> books = get_books_list();
    for(int i = 0; i < books.size(); i++){
        Book book = books[i];
        if(book.isbn == isbn){
            return false;
        }
    }
    return true;
}




std::vector<Book> search_in_books(std::string query){
    std::vector<Book> books = get_books_list();
    std::vector<Book> selected_books;
    for(int i = 0; i < books.size(); i++){
        Book book = books[i];
        if(book.title.find(query) <= book.title.length() || book.author.find(query) <= book.author.length() || book.isbn.find(query) <= book.isbn.length()){
            selected_books.push_back(book);
        }
    }
    return selected_books;
}
void remove_book(Book book){
    std::fstream f_("dbs/books.db");
    std::ofstream f_2;
    f_2.open("dbs/books_tmp.db");
    std::string line;
    while (std::getline(f_, line)) {
        if(line[0] != '#'){
            Book book2 = book_line_splitter(line, '|');
            if((book2.title == book.title) && (book2.author == book.author) && (book2.isbn == book.isbn) && (book2.published_year == book.published_year)){
                continue;
            }
            f_2 << line << std::endl;
        }else{
            f_2 << line << std::endl;
        }
    }
    f_.close();
    f_2.close();
    std::fstream f2_("dbs/books_tmp.db");
    std::ofstream f2_2;
    f2_2.open("dbs/books.db");
    while (std::getline(f2_, line)) {
        f2_2 << line << std::endl;
    }
    f2_.close();
    f2_2.close();
    system("del dbs\\books_tmp.db");
}


void editing_abook(Book old_book, Book new_book){
    remove_book(old_book);
    add_new_book(new_book);  
}