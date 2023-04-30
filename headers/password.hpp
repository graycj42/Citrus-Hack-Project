#ifndef PASSWORD_H
#define PASSWORD_H
#include <string>

using std::string;

class Password
{
private:
string savedPassword = "";

public:
Password::Password(string userPassword);

string Password::getSavedPassword();
void Password::setSavedPassword(string givenPassword);

bool Password::attemptLogin(string enteredPassword);

};

#endif