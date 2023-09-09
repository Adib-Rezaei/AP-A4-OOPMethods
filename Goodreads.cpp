#include "Main.hpp"
#include "Goodreads.hpp"
#include "Books.hpp"
#include "Authors.hpp"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>


#define ERROR 0

using namespace std;

void Goodreads::linking_process(){
    int total_likes = 0, total_reviews = 0;
    initialize_totals(total_likes, total_reviews);
    set_credit(total_likes, total_reviews);
    set_book_ratings();
}


Authors& Goodreads::find_author_by_id(int author_id){
    for(int i=0; i< author.size(); i++)
        if(author[i].get_id() == author_id)
            return author[i];
    return author[ERROR];
}

Books Goodreads::find_book_by_id(int book_id, BooksTable &book){
    for(int i=0; i<book.size(); i++){
        if(book[i].get_id() == book_id)
            return book[i];
    }
    return book[ERROR];
}

Users* Goodreads::find_user_by_id(int user_id){
    for(int i=0; i< user.size(); i++)
        if(user[i].get_id() == user_id)
            return &user[i];
    return NULL;
}

void Goodreads::update_author(BooksTable &book){
    for(int i=0; i< author.size(); i++){
        author[i].update_author(book);
    }
}

void Goodreads::show_suggest_book_2(stringstream &sstream){
    int user_id;
    sstream >> user_id;
    Users* user = find_user_by_id(user_id);
    UsersPtr visited_users;

    visited_users.push_back(user);
    vector<BooksPtr > best_books;

    for(int i=0; i< user->get_following().size(); i++){
        get_users_best_books(user->get_following()[i], best_books, visited_users);
    }
    Books* suggest = find_most_duplicate(best_books);
    
    show_suggest(*suggest);
}

Books* Goodreads::find_most_duplicate(vector<BooksPtr > best_books){
    int max_duplicate = 0;
    Books* suggest;

    for(int i=0; i< best_books.size(); i++){
        for(int j=0; j<best_books[i].size(); j++){
            int duplicate = duplicate_counter(best_books[i][j], best_books);
            if(duplicate > max_duplicate){
                max_duplicate = duplicate;
                suggest = best_books[i][j];
            }
            else if(duplicate == max_duplicate){
                if(best_books[i][j]->get_id() < suggest->get_id())
                    suggest = best_books[i][j];
            }
        }
    }
    return suggest;
}


void Goodreads::get_users_best_books(Users* user, vector<BooksPtr > &best_books, UsersPtr &visited_users){
    Users* next_user;
    if(is_duplicate(user, visited_users))
        return;

    visited_users.push_back(user);
    for(int i=0; i< user->get_following().size(); i++){
        
        next_user = find_user_by_id((user->get_following())[i]->get_id());
        
        get_users_best_books(next_user, best_books, visited_users);
    }

    BooksPtr read = user->get_read();
        
    sort(read.begin(), read.end(), compare_two_books);
    read.resize(3);
    best_books.push_back(read);
}

void Goodreads::update_user(string folder){
    ifstream follow_file(folder + "/follow_edges.csv");

    vector<string> row;
    UsersPtr following;
    UsersPtr follower;
    string line;
    
    getline(follow_file, line);
    while(getline(follow_file, line)){
        row.clear();
        following.clear();
        follower.clear();

        parse_line(row, line, ',');
        parse_flw(row, following, follower);
        Users* user = find_user_by_id(stoi(row[0]));
        user->initialize_follow_status(following, follower);
    }
}

void Goodreads::parse_flw(vector<string> row, UsersPtr &following, UsersPtr &follower){
    vector<string> flw, flwer;
    parse_line(flw, row[1], '$');
    if(row.size() == 3)   parse_line(flwer, row[2], '$');

    for(int i=0; i< flw.size(); i++){
        following.push_back(find_user_by_id(stoi(flw[i])));
    }
    for(int i=0; i< flwer.size(); i++){
        follower.push_back(find_user_by_id(stoi(flwer[i])));
    }
}

void Goodreads::show_suggest_book(stringstream &sstream){
    vector<string> fav_genres;
    
    int user_id;
    sstream >> user_id;
    for(int i=0; i< user.size(); i++){
        if(user[i].get_id() == user_id)
            fav_genres = user[i].get_fav_genres();
    }

    Books suggest_book = most_score(fav_genres);
    show_suggest(suggest_book);
}

Books Goodreads::most_score(vector<string> fav_genres){
    double max = 0;
    Books suggest_book;

    for(int i=0; i< author.size(); i++){
        BooksTable book = author[i].get_books();
        for(int j=0; j< book.size(); j++){
            double score = book[j].is_favorite_genre(fav_genres) + book[j].get_credit_rating();
            if(score > max){
                max = score;
                suggest_book = book[j];
            }
        }
    }
    
    return suggest_book;
}

void Goodreads::show_suggest(Books suggest_book){
    ReviewsTable review_related;

    suggest_book.print_book_2(find_author_by_id(suggest_book.get_author()).get_name());
    cout << "Reviews:" << endl;
    for(int i=0; i< user.size(); i++){
        ReviewsTable review = user[i].get_review();
        for(int j=0; j< review.size(); j++){
            if(review[j].get_book()->get_id() == suggest_book.get_id())
                review_related.push_back(review[j]);
        }
    }

    sort(review_related.begin(), review_related.end(), compare_two_id);
    for(int i=0; i< review_related.size(); i++){
        review_related[i].show_review();
    }
}

void Goodreads::show_best_reviewer(){
    int count_likes = 0, max=0, likes;
    Users best_reviewer;

    for(int i=0; i< user.size(); i++){
        count_likes = 0;
        ReviewsTable review = user[i].get_review();
        for(int j=0; j< review.size(); j++){
            count_likes += review[j].get_number_of_likes();
        }
        if(count_likes > max){
            max = count_likes;
            best_reviewer = user[i];
            likes = count_likes;
        }
    }
    best_reviewer.show_best_reviewer(likes);
}

void Goodreads::show_best_book(){
    double max = 0;
    Books best_book;
    
    for(int i=0; i< user.size(); i++){
        ReviewsTable review = user[i].get_review();
        for(int j=0; j< review.size(); j++){
            if(review[j].get_book()->get_average_rating() > max){
                best_book = *review[j].get_book();
                max = review[j].get_book()->get_average_rating();
            }
        }
    }
    cout << "id: " << best_book.get_id() << endl << "Title: " << best_book.get_title() << endl
    << "Genre: " << best_book.get_genre() << endl << "Author: " << find_author_by_id(best_book.get_author()).get_name() << endl
    << "Average Rating: " << fixed << setprecision(2) << best_book.get_average_rating() << endl;
}

void Goodreads::show_credit(stringstream &sstream){
    int user_id;
    sstream >> user_id;
    Users user = *find_user_by_id(user_id);
    cout << fixed << setprecision(6) << user.get_credit() << endl;
}

void Goodreads::show_sorted_shelf(stringstream &sstream){
    int user_id;
    string shelf, genre, temp;

    sstream >> user_id >> shelf;
    while(sstream >> temp){
        genre += temp;
        if(!sstream.eof())
            genre += " ";
    }
    
    Users* user = find_user_by_id(user_id);
    user->sorting_books(shelf, genre, author);
}

void Goodreads::show_author_info(stringstream &sstream){
    int author_id;
    sstream >> author_id;
    Authors author = find_author_by_id(author_id);
    author.show_author_info();
}

void Goodreads::initialize_totals(int &total_likes, int &total_reviews){
    for(int i=0; i< user.size(); i++){
        ReviewsTable review = user[i].get_review();
        for(int j=0; j< review.size(); j++){
            total_likes += review[j].get_number_of_likes();
        }
        total_reviews += review.size();
    }
}

void Goodreads::set_credit(int total_likes, int total_reviews){
    for(int i=0; i< user.size(); i++){
        int count_likes = 0;
        ReviewsTable review = user[i].get_review();
        for(int j=0; j< review.size(); j++){
            count_likes += review[j].get_number_of_likes();
        }
        user[i].set_credit(count_likes, total_likes, review.size(), total_reviews);
    }
}

void Goodreads::set_book_ratings(){
    for(int i=0; i< user.size(); i++){
        ReviewsTable review = user[i].get_review();
        for(int j=0; j< review.size(); j++){
            double credit = review[j].get_rating() * user[i].get_credit();
            review[j].get_book()->increase_ratings(review[j].get_rating(), credit);
        }
    }
}