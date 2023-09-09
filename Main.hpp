#ifndef _MAIN_HPP_
#define _MAIN_HPP_ "_MAIN_HPP_"

#include "Goodreads.hpp"

typedef std::vector<Books> BooksTable;
typedef std::vector<Books*> BooksPtr;
typedef std::vector<Reviews> ReviewsTable;
typedef std::vector<Reviews*> ReviewsPtr;
typedef std::vector<Authors> AuthorsTable;
typedef std::vector<Authors*> AuthorsPtr;
typedef std::vector<Users*> UsersPtr;
typedef std::vector<Users> UsersTable;

void parse_line(std::vector<std::string> &row, std::string line, char format);
BooksTable read_book(std::string folder);
AuthorsTable read_author(std::string folder, BooksTable &book);
BooksTable find_books_by_author_id(int id, BooksTable &book);
ReviewsTable read_review(std::string folder, BooksTable &book);
Books* find_book_by_id(int book_id, BooksTable &book);
Authors* find_author_by_id(int author_id, AuthorsTable &author);
UsersTable read_user(std::string folder, ReviewsTable &review, BooksTable &book, AuthorsTable &author);
void parse_user_details(std::vector<std::vector<std::string> > &user_data, std::vector<std::string> &row);
void parse_user_authors(AuthorsPtr &author_ptr, std::vector<std::vector<std::string> > &user_data, AuthorsTable &author);
void parse_user_shelves(std::vector<BooksPtr > &books_ptr, std::vector<std::vector<std::string> > &user_data, BooksTable &book);
bool compare_two_string(Books* book1, Books* book2);
ReviewsTable set_user_reviews(int user_id , ReviewsTable review);

int duplicate_counter(Books* book, std::vector<BooksPtr > best_books);
bool is_duplicate(Users* user, UsersPtr visited_users);
bool compare_two_books(Books* book1, Books* book2);
bool compare_two_book_id(Books book1, Books book2);
bool compare_two_author(Authors* author1, Authors* author2);
bool compare_two_id(Reviews review1, Reviews review2);


#endif
