#include <iostream>
#include <vector>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct User {
    std::string username;
    std::string password;
    std::string role;
    std::string status;
    std::string phone;
};

struct Book {
    std::string title;
    std::string author;
    std::string published_year;
    std::string isbn;
    int availability;
};

bool isValidNumber(const std::string& input);
User get_user_info(std::string sessionid);
std::vector<User> get_users();
std::string get_session_id();
void destroy_session();
User user_line_splitter(const std::string& str, char separator);
std::string generate_session_id(std::string username);
bool check_username_availability(std::string username);
bool check_isbn_availability(std::string isbn);
bool check_phone_availability(std::string username);
void add_new_user(User user);
void add_new_user(User user);
User get_user(std::string username);
void remove_user(User user);
void edit_auser(User old_user, User new_user);
User get_user_by_phone(std::string phone);
std::vector<User> search_in_users(std::string query);

void add_new_book(Book book);
void remove_book(Book book);
void editing_abook(Book old_book, Book new_book);
std::vector<Book> get_books_list();
std::vector<Book> search_in_books(std::string query);

#endif 
