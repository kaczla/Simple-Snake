#include "user.hpp"

user::user(){
	this->Socket = -1;
}

user::user( int _socket, std::string _hostname ){
	this->Socket = _socket;
	this->HostName = _hostname;
}

user::~user(){
	
}
