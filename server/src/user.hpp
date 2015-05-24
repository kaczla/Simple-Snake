#ifndef _user_hpp_
#define _user_hpp_

#include <iostream>
#include "def.hpp"
#include "user.hpp"


class user{
public:
	user();
	user( int _socket, std::string _hostname );
	~user();
	
private:
	int Socket;
	std::string HostName;
};

user *User[MAX_PLAYER] = { NULL };
//short map[10][10];

#endif
