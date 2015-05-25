#ifndef _user_hpp_
#define _user_hpp_

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
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
	void Close();
	int Send( std::string _input );
	int SendEx( std::string &_input );
	int Recv();
	std::string ReturnMsg();
	bool ReturnConnect();
	char ReturnDirection();
	bool ReturnInit();
	bool ReturnSnakeInit();
	bool ReturnNewGame();
	std::string ToString();
	void SetDirection( char _input );
	void AddSnake( int &_x, int &_y );
	void AddSnake( std::vector<XY> &_input );
	void SetHeadTail( int &_x, int &_y );
	void SetInit( bool _input );
	void SetSnakeInit( bool _input );
	void SetNewGame( bool _input );
	void ClearSnake();
	void GameOver();
	void Action();
	//Snake
	std::vector <XY> Snake;
	
	pthread_mutex_t Lock;
private:
	int Socket;
	std::string HostName;
	bool Connect, Init, SnakeInit;
	char msg[MAX_RECV];
	std::string Msg;
	//Snake
	char Direction;	
	std::vector<XY>::iterator it;
	bool NewGame;
	//Recv
	std::istringstream Lines;
	std::string Line;
	char Front;
	std::string tmp;
	//error
	int ErrorSend, ErrorRecv;
};

user *User[MAX_PLAYER] = { NULL };

#endif
