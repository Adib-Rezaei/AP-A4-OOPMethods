#include "Books.hpp"
#include <iostream>

using namespace std;

Books::Books(int _id, std::string _title, int _author_id, std::string _genre){
    id = _id;   title = _title;    author_id = _author_id;    genre = _genre;
    rating_sum = 0;    credit_rating_sum = 0;   number_of_reviews = 0;
}

void Books::increase_ratings(int inc_rating, double inc_credit_rating){ 
    rating_sum += inc_rating;
    credit_rating_sum += inc_credit_rating;
    number_of_reviews += 1;
}
void Books::show_books(){
    cout << "id: " << id << " Title: " << title << endl;
}
void Books::print_book(string author_name){
    cout << "id: " << id << endl << "Title: " << title << endl
    << "Genre: " << genre << endl << "Author: " << author_name << endl <<  "***" << endl;
}
void Books::print_book_2(string author_name){
    cout << "id: " << id << endl << "Title: " << title << endl
    << "Genre: " << genre << endl << "Author: " << author_name << endl;
}
int Books::is_favorite_genre(vector<string> fav_genre){
    int flag = 0;
    for(int i=0; i< fav_genre.size(); i++){
        if(fav_genre[i] == genre){
            flag = 1;
        }
    }
    return flag ? 5 : 0;
}

double Books::get_average_rating(){ return (double)rating_sum/(double)number_of_reviews; }
double Books::get_credit_rating(){ return credit_rating_sum/number_of_reviews; }
std::string Books::get_title(){ return title; }
std::string Books::get_genre(){ return genre; }
int Books::get_id(){ return id; }
int Books::get_author(){ return author_id; }