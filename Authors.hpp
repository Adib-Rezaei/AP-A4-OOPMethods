#ifndef _AUTHORS_HPP_
#define _AUTHORS_HPP_ "_AUTHORS_HPP_"

#include "Books.hpp"
typedef std::vector<Books> BooksTable;

class Authors{
    public:

        Authors(int _id, std::string _name, std::string _gender, std::string _member_since, int _year,
        std::string _place, std::vector<std::string> _genres, BooksTable _books)
        {
            id = _id; name = _name; gender = _gender; member_since = _member_since;
            year_of_birth = _year; place_of_birth = _place; genres = _genres; books = _books;
        }
        void update_author(BooksTable &book);

        void show_author_info();
        int get_id(){ return id; }
        std::string get_name(){ return name; }
        BooksTable& get_books(){ return books; }

    private:

        Books find_book_by_id(int book_id, BooksTable &book);

        int id;
        std::string name;
        std::string gender;
        std::string member_since;
        int year_of_birth;
        std::string place_of_birth;
        std::vector<std::string> genres;
        BooksTable books;
};

#endif
