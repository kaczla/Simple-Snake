#ifndef _client_hpp_
#define _client_hpp_

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cerrno>
#include <cstdlib>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include "def.hpp"

using namespace std;

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

class client{
public:
	client( string _host, int _port );
	~client();
	bool ReturnInit();
	bool ReturnConnected();
	bool Send( string &_input );
	void ReveiceData();
	void StopClient();
	void SetDebug( bool _input );
	string ReturnTime_();
private:
	bool Init;
	int Error;
	//Connect to server
	int Port;
	string Host;
	int Socket;
	bool Connected;
	void SetPort( int &_port );
	void SetHost( string &_host );
	bool StartConnection();
	void Disconnect();
	//Send, Reveice
	int ErrorSend, ErrorReveice;
	char Buffer[MAX_RECV_BUFFER];
	string ReveiceText;
	istringstream Lines;
	string Line;
	size_t Find;
	bool Reveice();
	//time
	time_t Time;
	struct tm * TimeInfo;
	char TimeBuffer[16];
	string ReturnTime();
	//other
	bool Debug;
	size_t Find1, Find2;
	string TMP, TMP_XY;
	XY _xy;
	//Snake
	void CheckSnakeInit();
	void PrintMap();
	void ClearMap();
	bool SnakeInit;
	int Width, Height, Player, SnakeTime, MyID, Other;
	int Map[100][100];
	int _i,_j;
	string TopMap, BottomMap, LRMap;
};

#endif
