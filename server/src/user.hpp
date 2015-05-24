#ifndef _user_hpp_
#define _user_hpp_

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "def.hpp"

struct XY{
	int X, Y;
	XY(){};
	XY( int _x, int _y ){
		this->X = _x;
		this->Y = _y;
	}
	void Set( int &_x, int &_y ){
		this->X = _x;
		this->Y = _y;
	}
};

class user{
public:
	user();
	user( int _socket, std::string _hostname );
	~user();
	int Send( std::string _input );
	int SendEx( std::string &_input );
	int Recv();
	std::string ReturnMsg();
	bool ReturnConnect();
	char ReturnDirection();
	bool ReturnInit();
	void SetDirection( char _input );
	void SetHead( int &_x, int &_y );
	void SetTail( int &_x, int &_y );
	void AddSnake( int &_x, int &_y );
	void AddSnake( std::vector<XY> &_input );
	void SetHeadTail( int &_x, int &_y );
	void SetInit( bool _input );
	void ClearSnake();
	void Action();
	//Snake
	std::vector <XY> Snake;
private:
	int Socket;
	std::string HostName;
	bool Connect, Init;
	char msg[MAX_RECV];
	std::string Msg;
	//Snake
	char Direction;
	XY Head, Tail;
	//error
	int ErrorSend, ErrorRecv;
	public:
	
	pthread_mutex_t Lock;
};

user *User[MAX_PLAYER] = { NULL };
//short map[10][10];

#endif
