#ifndef _BOOKS_HPP_
#define _BOOKS_HPP_ "_BOOKS_HPP_"

#include <string>
#include <vector>

class Books{
    public:

        Books(){}
        Books(int _id, std::string _title, int _author_id, std::string _genre);

        void increase_ratings(int inc_rating, double inc_credit_rating);
        void show_books();
        void print_book(std::string author_name);
        void print_book_2(std::string author_name);
        int is_favorite_genre(std::vector<std::string> fav_genre);

        double get_average_rating();
        double get_credit_rating();
        std::string get_title();
        std::string get_genre();
        int get_id();
        int get_author();

    private:

        int id;
        std::string title;
        int author_id;
        std::string genre;

        int rating_sum;             
        double credit_rating_sum;
        int number_of_reviews;
};

#endif