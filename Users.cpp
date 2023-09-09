#include "Users.hpp"
#include <iostream>
#include <algorithm>
#include "Main.hpp"

using namespace std;


void Users::initialize_follow_status(UsersPtr flw, UsersPtr flwer){
    following = flw;
    follower = flwer;
}

void Users::set_credit(int count_likes, int total_likes, int count_reviews, int total_reviews){ 
    double var1 = 0, var2 = 0;
    if(total_likes != 0)  var1 = (double)count_likes/(double)total_likes;
    if(total_reviews != 0)  var2 = (double)count_reviews/(double)total_reviews;
    credit = (0.5) * ( var1 + var2 );
}
void Users::show_best_reviewer(int count_likes){
    cout << "id: " << id << endl << "Name: " << name << endl << "Place of Birth: "
    << place_of_birth << endl << "Member Since: " << member_since << endl << "Favorite Genres: ";
    
    sort(favorite_genres.begin(), favorite_genres.end());
    for(int i=0; i<favorite_genres.size(); i++){
        cout << favorite_genres[i];
        if(i != favorite_genres.size()-1)   cout << ", ";
    }
    
    sort(favorite_authors.begin(), favorite_authors.end(), compare_two_author);
    cout << endl << "Favorite Authors: ";
    for(int i=0; i<favorite_authors.size(); i++){
        cout << favorite_authors[i]->get_name();
        if(i != favorite_authors.size()-1)  cout << ", ";
    }
    
    cout << endl << "Number of Books in Read Shelf: " << read.size() << endl
    << "Number of Books in Want to Read Shelf: " << want_to_read.size() << endl
    << "Number of Books in Currently Reading Shelf: " << currently_reading.size() << endl
    << "Number of Likes: " << count_likes << endl;
}


void Users::sorting_books(string shelf, string genre, AuthorsTable author){

    BooksPtr book;
    if(shelf == "want_to_read") book = want_to_read;
    else if(shelf == "currently_reading") book = currently_reading;
    else if(shelf == "read") book = read;

    int last_swap=0;
    for(int i=0; i< book.size(); i++){
        if(book[i]->get_genre() == genre){
            swap(book[i], book[last_swap]);
            last_swap++;
        }
    }

    if(last_swap == 0) sort(book.begin(), book.end(), compare_two_string);
    else{
        sort(book.begin(), book.begin() + last_swap, compare_two_string);
        sort(book.begin() + last_swap, book.end(), compare_two_string);
    }
    
    for(int i=0; i< book.size(); i++){
        Authors* author_ptr = find_author_by_id(book[i]->get_author(), author);
        book[i]->print_book(author_ptr->get_name());
    }
}

