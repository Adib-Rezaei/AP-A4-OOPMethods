#include "Main.hpp"
#include "Goodreads.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

#define NUMBER_OF_USER_DATA 5
#define NUMBER_OF_SHELVES 3

using namespace std;

int duplicate_counter(Books* book, vector<BooksPtr > best_books){
    int count = 0;
    for(int i=0; i< best_books.size(); i++){
        for(int j=0; j<best_books[i].size(); j++){
            if(book->get_id() == best_books[i][j]->get_id())
                count++;
        }
    }
    return count;
}

bool is_duplicate(Users* user, UsersPtr visited_users){
    for(int i=0; i< visited_users.size(); i++){
        if(visited_users[i]->get_id() == user->get_id())
            return true;
    }
    return false;
}

bool compare_two_books(Books* book1, Books* book2){
    if(book1->get_credit_rating() != book2->get_credit_rating())
        return book1->get_credit_rating() > book2->get_credit_rating();
    return book1->get_id() < book2->get_id();
}



bool compare_two_id(Reviews review1, Reviews review2){
    if(review1.get_id() != review2.get_id())
        return review1.get_id() < review2.get_id();
    return true;
}



bool compare_two_author(Authors* author1, Authors* author2){
    return author1->get_name() < author2->get_name();
}




bool compare_two_string(Books* book1, Books* book2){
    if(book1->get_title() != book2->get_title())
        return book1->get_title() < book2->get_title();
    return true;
}



bool compare_two_book_id(Books book1, Books book2){
    return book1.get_id() < book2.get_id();
}

void parse_line(vector<string> &row, string line, char format){
    string word;
    stringstream sstream(line);
    
    while (getline(sstream, word, format)){
        row.push_back(word);
    }
}

BooksTable read_book(string folder){
    ifstream book_file(folder + "/books.csv");

    BooksTable book;
    vector<string> row;
    string line;
    
    getline(book_file, line);
    while(getline(book_file, line)){
        row.clear();
        parse_line(row, line, ',');
        book.push_back(Books(stoi(row[0]), row[1], stoi(row[2]), row[3]));
    }
    return book;
}

AuthorsTable read_author(string folder, BooksTable &book){
    ifstream author_file(folder + "/authors.csv");

    AuthorsTable author;
    
    vector<string> row;
    vector<string> genres;
    string line;

    getline(author_file, line);
    while(getline(author_file, line)){
        row.clear();
        genres.clear();
        parse_line(row, line, ',');
        parse_line(genres, row[6], '$');
        BooksTable author_books = find_books_by_author_id(stoi(row[0]), book);
        author.push_back(Authors(stoi(row[0]), row[1], row[2], row[3], stoi(row[4]), row[5], genres, author_books));
    }
    return author;
}

BooksTable find_books_by_author_id(int id, BooksTable &book){
    BooksTable author_books;
    for(int i=0; i<book.size(); i++){
        if(id == book[i].get_author())
            author_books.push_back(book[i]);
    }
    return author_books;
}

ReviewsTable read_review(string folder, BooksTable &book){
    ifstream review_file(folder + "/reviews.csv");

    ReviewsTable review;
    vector<string> row;
    string line;
    
    getline(review_file, line);
    while(getline(review_file, line)){
        row.clear();
        parse_line(row, line, ',');
        Books* book_ptr = find_book_by_id(stoi(row[1]), book);
        review.push_back(Reviews(stoi(row[0]), book_ptr, stoi(row[2]), stoi(row[3]), row[4], stoi(row[5])));
    }
    return review;
}

Books* find_book_by_id(int book_id, BooksTable &book){
    for(int i=0; i<book.size(); i++){
        if(book[i].get_id() == book_id)
            return &book[i];
    }
    return NULL;
}

Authors* find_author_by_id(int author_id, AuthorsTable &author){
    for(int i=0; i<author.size(); i++)
        if(author_id == author[i].get_id())
            return &author[i];
    return NULL;
}

UsersTable read_user(string folder, ReviewsTable &review, BooksTable &book, AuthorsTable &author){
    ifstream user_file(folder + "/users.csv");

    UsersTable user;
    vector<string> row;
    vector<vector<string> > user_data(NUMBER_OF_USER_DATA, vector<string>());
    vector<BooksPtr > books_ptr(NUMBER_OF_SHELVES, BooksPtr());
    AuthorsPtr author_ptr;
    string line;
    
    getline(user_file, line);
    while(getline(user_file, line)){
        row.clear();
        author_ptr.clear();
        for(int i=0; i< books_ptr.size(); i++)  books_ptr[i].clear();
        for(int i=0; i< user_data.size(); i++)  user_data[i].clear();

        parse_line(row, line, ',');
        parse_user_details(user_data, row);
        parse_user_authors(author_ptr, user_data, author);
        parse_user_shelves(books_ptr, user_data, book);
        ReviewsTable user_review = set_user_reviews(stoi(row[0]) ,review);
        
        user.push_back(Users(stoi(row[0]), row[1], row[2], row[3], author_ptr, user_data[1], books_ptr[0],
        books_ptr[1], books_ptr[2], user_review));
    }
    return user;
}

ReviewsTable set_user_reviews(int user_id , ReviewsTable review){
    ReviewsTable user_review;
    for(int i=0; i<review.size(); i++){
        if(review[i].get_user_id() == user_id)
            user_review.push_back(review[i]);
    }
    return user_review;
}

void parse_user_details(vector<vector<string> > &user_data, vector<string> &row){
    for(int i=0; i< NUMBER_OF_USER_DATA; i++)
        parse_line(user_data[i], row[i+4], '$');
}

void parse_user_authors(AuthorsPtr &author_ptr, vector<vector<string> > &user_data, AuthorsTable &author){
    for(int i=0; i<user_data[0].size(); i++){
        author_ptr.push_back(find_author_by_id(stoi(user_data[0][i]), author));
    }
}

void parse_user_shelves(vector<BooksPtr > &books_ptr, vector<vector<string> > &user_data, BooksTable &book){
    for(int j =2; j<NUMBER_OF_USER_DATA; j++){
        for(int i=0; i<user_data[j].size(); i++){
            books_ptr[j-2].push_back(find_book_by_id(stoi(user_data[j][i]), book));
        }
    }
}

