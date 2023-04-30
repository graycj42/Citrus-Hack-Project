#include "password.hpp"
#include <iostream>

Password::Password(string userPassword){
    setSavedPassword(userPassword);
}

string Password::getSavedPassword(){
    return this->savedPassword;
}
void Password::setSavedPassword(string givenPassword){
    this->savedPassword = givenPassword;
}

bool Password::attemptLogin(string enteredPassword){
    return (savedPassword.compare(enteredPassword) == 0) ?  true : false;
}