
#include "Goodreads.hpp"
#include "Main.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FIRST_ARGUMENT 1

using namespace std;


typedef vector<Books> BooksTable;
typedef vector<Books*> BooksPtr;
typedef vector<Reviews> ReviewsTable;
typedef vector<Reviews*> ReviewsPtr;
typedef vector<Authors> AuthorsTable;
typedef vector<Authors*> AuthorsPtr;
typedef vector<Users*> UsersPtr;
typedef vector<Users> UsersTable;


int main(int argc, char* argv[]){
    
    BooksTable book = read_book(argv[FIRST_ARGUMENT]);
    AuthorsTable author = read_author(argv[FIRST_ARGUMENT], book);
    ReviewsTable review = read_review(argv[FIRST_ARGUMENT], book);
    UsersTable user = read_user(argv[FIRST_ARGUMENT], review, book, author);
    
    Goodreads goodreads(author, user);
    goodreads.linking_process();
    goodreads.update_author(book);
    goodreads.update_user(argv[FIRST_ARGUMENT]);

    string line, command;
    getline(cin, line);
    stringstream sstream(line);


    sstream >> command;
    if(command == "show_author_info"){
        goodreads.show_author_info(sstream);
    }
    else if(command == "show_sorted_shelf"){
        goodreads.show_sorted_shelf(sstream);
    }
    else if(command == "credit"){
        goodreads.show_credit(sstream);
    }
    else if(command == "best_book"){
        goodreads.show_best_book();
    }
    else if(command == "best_reviewer"){
        goodreads.show_best_reviewer();
    }
    else if(command == "recommend_first_approach"){
        goodreads.show_suggest_book(sstream);
    }
    else if(command == "recommend_second_approach"){
        goodreads.show_suggest_book_2(sstream);
    }
}