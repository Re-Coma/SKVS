#include "User.hpp"
#include "../Exception.hpp"

#include <string>
using namespace std;

User::User( const string _ID, const string _password, const UserLevel _userLV ) {

	if( _ID.length() > MAX_ID_LENGTH || _ID.length() < MIN_ID_LENGTH )
		throw new UserLengthException("ID length must be 4 ~ 16.");
	if( _password.length() > MAX_PSWD_LENGTH || _password.length() < MIN_PSWD_LENGTH )
		throw new UserLengthException("pswd length must be 8 ~ 16.");

	this->ID = _ID; this->password = _password; this->userLV = _userLV;

}

string User::getID(void) { return this->ID; }
string User::getPassword(void) { return this->password; }
UserLevel User::getUserLevel(void) { return this->userLV; }

void User::setID(string _newID) {

	if( _newID.length() > MAX_ID_LENGTH || _newID.length() < MIN_ID_LENGTH )
		throw new UserLengthException("ID length must be 4 ~ 16.");
	this->ID = _newID;
}

void User::setPassword( string _newPassword ) {
	if( _newPassword.length() > MAX_PSWD_LENGTH || _newPassword.length() < MIN_PSWD_LENGTH )
		throw new UserLengthException("pswd length must be 8 ~ 16.");
	this->password = _newPassword;
}

void User::setUserLevel( UserLevel _newUserLV ) {
	
	this->userLV = _newUserLV;
}

bool User::operator==(User arg) {

	return ( (this->getID().compare(arg.getID()) == 0) );

}

UserLevel User::userLevelConverter(string _str) {

	if( _str.compare("CLIENT") == 0)
		return USERLEVEL_CLIENT;
	else if( _str.compare("ADMIN") == 0)
		return USERLEVEL_ADMIN;
	else if( _str.compare("ROOT") == 0)
		return USERLEVEL_ROOT;
	else
		throw new DataConvertException("String Data is not UserLevel");

}

string User:: userLevelDeConverter(UserLevel _level) {

	if( _level == USERLEVEL_CLIENT)
		return "CLIENT";
	else if( _level == USERLEVEL_ADMIN)
		return "ADMIN";
	else
		return "ROOT";


}
