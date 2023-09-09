#ifndef _USERS_HPP_
#define _USERS_HPP_ "_USERS_HPP_"

#include <string>
#include <vector>
#include "Authors.hpp"
#include "Books.hpp"
#include "Reviews.hpp"

typedef std::vector<Books> BooksTable;
typedef std::vector<Books*> BooksPtr;
typedef std::vector<Reviews> ReviewsTable;
typedef std::vector<Reviews*> ReviewsPtr;
typedef std::vector<Authors> AuthorsTable;
typedef std::vector<Authors*> AuthorsPtr;


class Users{
    public:
        typedef std::vector<Users*> UsersPtr;

        Users(){}
        Users(int _id, std::string _name, std::string _place, std::string _member,
        AuthorsPtr _aut, std::vector<std::string> _gen, BooksPtr _want, BooksPtr _curr,
        BooksPtr _read, ReviewsTable _rev){
            id = _id; name = _name; place_of_birth = _place; member_since = _member; credit = 0;
            favorite_authors = _aut; favorite_genres = _gen; want_to_read = _want; currently_reading = _curr;
            read = _read; review = _rev;
        }
        void initialize_follow_status(UsersPtr flw, UsersPtr flwer);

        void set_credit(int count_likes, int total_likes, int count_reviews, int total_reviews);
        void initialize_follow_status(int id);
        void show_best_reviewer(int count_likes);
        void sorting_books(std::string shelf, std::string genre, AuthorsTable author);

        double get_credit(){ return credit; }
        int get_id(){ return id; }
        ReviewsTable get_review(){ return review; }
        std::vector<std::string> get_fav_genres(){ return favorite_genres; }
        UsersPtr get_following(){ return following; }
        UsersPtr get_follower(){ return follower; }
        BooksPtr get_read(){ return read; }

    private:

        int id;
        std::string name;
        std::string place_of_birth;
        std::string member_since;
        double credit;                      
        AuthorsPtr favorite_authors;
        std::vector<std::string> favorite_genres;
        BooksPtr want_to_read;
        BooksPtr currently_reading;
        BooksPtr read;
        ReviewsTable review;

        UsersPtr following;
        UsersPtr follower;
};

#endif