#ifndef _GOODREADS_HPP_
#define _GOODREADS_HPP_ "_GOODREADS_HPP_"

#include "Users.hpp"
#include "Authors.hpp"

typedef std::vector<Books> BooksTable;
typedef std::vector<Reviews> ReviewsTable;
typedef std::vector<Authors> AuthorsTable;
typedef std::vector<Users> UsersTable;
typedef std::vector<Users*> UsersPtr;

class Goodreads{
    public:

        Goodreads(AuthorsTable _author, UsersTable _user){
            author = _author;   user = _user;
        }
        void linking_process();
        void update_author(BooksTable &book);
        void update_user(std::string folder);

        void show_author_info(std::stringstream &sstream);
        void show_sorted_shelf(std::stringstream &sstream);
        void show_credit(std::stringstream &sstream);
        void show_best_book();
        void show_best_reviewer();
        void show_suggest_book(std::stringstream &sstream);
        void show_suggest_book_2(std::stringstream &sstream);

        BooksTable best_user_books();
        Users* find_user_by_id(int user_id);
        Authors& find_author_by_id(int author_id);

    private:
        void get_users_best_books(Users* user, std::vector<BooksPtr > &best_books, UsersPtr &visited_users);
        void initialize_totals(int &total_likes, int &total_reviews);
        void set_credit(int total_likes, int total_reviews);
        void set_book_ratings();
        void parse_flw(std::vector<std::string> row, UsersPtr &following, UsersPtr &follower);
        void show_suggest(Books suggest_book);
        Books find_book_by_id(int book_id, BooksTable &book);
        Books* find_most_duplicate(std::vector<BooksPtr > best_books);
        Books most_score(std::vector<std::string> fav_genres);

        AuthorsTable author;
        UsersTable user;
        
};

#endif
