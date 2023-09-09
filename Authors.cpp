#include "Authors.hpp"
#include <iostream>
#include <algorithm>
#include "Main.hpp"

using namespace std;

void Authors::show_author_info(){
    cout << "id: " << id << endl << "Name: " << name << endl << "Year of Birth: " << year_of_birth << endl
    << "Place of Birth: " << place_of_birth << endl << "Member Since: " << member_since << endl << "Genres: ";

    sort(genres.begin(), genres.end());
    for(int i=0; i< genres.size(); i++){
        cout << genres[i];
        if(i != genres.size() -1)
            cout << ", ";
    }

    sort(books.begin(), books.end(), compare_two_book_id);
    cout << endl << "Books:" << endl;
    for(int i=0; i< books.size(); i++)
        books[i].show_books();
}

Books Authors::find_book_by_id(int book_id, BooksTable &book){
    for(int i=0; i<book.size(); i++){
        if(book[i].get_id() == book_id)
            return book[i];
    }
    return book[0];
}

void Authors::update_author(BooksTable &book){
    for(int i=0; i< books.size(); i++){
        books[i] = find_book_by_id(books[i].get_id(), book);
    }
}