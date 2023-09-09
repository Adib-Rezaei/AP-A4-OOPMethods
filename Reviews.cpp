#include "Reviews.hpp"
#include <iostream>

using namespace std;

void Reviews::show_review(){
    cout << "id: " << id << " Rating: " << rating << " Likes: " << number_of_likes
        << " Date: " << date << endl;
}