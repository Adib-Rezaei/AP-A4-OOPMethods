#ifndef _REVIEWS_HPP_
#define _REVIEWS_HPP_ "_REVIEWS_HPP_"

#include <string>
#include "Books.hpp"

class Reviews{
    public:

        Reviews(int _id, Books* _book, int _user_id, int _rating, std::string _date, int _likes){
            id = _id; book = _book; user_id = _user_id; rating = _rating; date = _date;
            number_of_likes = _likes;
        }
        void show_review();

        Books* get_book(){ return book; }
        int get_user_id(){ return user_id; }
        int get_rating(){ return rating; }
        int get_number_of_likes(){ return number_of_likes; }
        int get_id(){ return id; }
        
    private:

        int id;
        int user_id;
        Books* book;
        int rating;
        std::string date;
        int number_of_likes;
};

#endif