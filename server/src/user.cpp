#include "user.hpp"

user::user(){
	this->Socket = -1;
	this->Connect = false;
	this->Init = false;
	this->Direction = 'u';
	pthread_mutex_init( &this->Lock, NULL );
}

user::user( int _socket, std::string _hostname ){
	this->Socket = _socket;
	this->HostName = _hostname;
	this->Connect = true;
	this->Init = false;
	this->Direction = 'u';
	pthread_mutex_init( &this->Lock, NULL );
}

user::~user(){
	pthread_mutex_unlock( &this->Lock );
	pthread_mutex_destroy( &this->Lock );
	std::cout<<"Leaving user: "<<this->Socket<<"\n";
	send( this->Socket, ":Q", 2, 0 );
	close( this->Socket );
}

void user::Close(){
	send( this->Socket, ":Q", 2, 0 );
	close( this->Socket );
}

/*
 * TO CLIENT ( beginning ':' = COMMAND ):
 * 
 * :W[Number] - WIDTH [Number]
 * :H[Number] - HEIGHT [Number]
 * :X[Players] - NUMBER OF PLAYERS [Players]
 * :T[Time] - REFRESH TIME [Time]
 * :P[Number] - YOUR NUMBER [Number]
 * :p[Number] [X;Y] ... [X;Y] - PLAYER NUMBER [Number] COORDINATES [X;Y] ...
 * :G - GameOver - u can watch
 * :Q - QUIT
 * :R - Refresh ( map )
 * 
 * ( without ':' = MSG )
 * Message
 */
int user::Send( std::string _input ){
	if( _input.empty() ){
		return -1;
	}
	else{
		_input.append( "\n" );
		this->ErrorSend = send( this->Socket, _input.c_str(), _input.size(), 0 );
		return this->ErrorSend;
	}
}

int user::SendEx( std::string &_input ){
	if( _input.empty() ){
		return -1;
	}
	else{
		if( _input.back() != '\n' ){
			_input += '\n';
		}
		this->ErrorSend = send( this->Socket, _input.c_str(), _input.size(), 0 );
		return this->ErrorSend;
	}
}

int user::Recv(){
	memset( this->msg, 0, MAX_RECV );
	this->ErrorRecv = recv( this->Socket, this->msg, MAX_RECV, 0 );
	return this->ErrorRecv;
}

std::string user::ReturnMsg(){
	this->Msg = this->msg;
	return this->Msg;
}

std::string user::ToString(){
	this->tmp.clear();
	for( this->it = this->Snake.begin(); it != this->Snake.end(); it++ ){
		this->tmp += std::to_string( it->X ) + ';' + std::to_string( it->Y ) + ' ';
	}
	//std::cout<<"tmp:\'"<<tmp<<"\'\n";
	this->tmp.append( "\n" );	
	return this->tmp;
}

/*
 * FROM CLIENT ( beginning ':' ):
 * Example: ":u"
 *  
 * Direction:
 * u - UP
 * d - DOWN
 * l - LEFT
 * r - RIGHT
 * 
 * Other
 * Q - QUIT
 */
void user::Action(){
	this->Msg = this->msg;
	this->Lines.clear();
	this->Line.clear();
	this->Lines.str( this->Msg );
	while( getline( this->Lines, this->Line ) ){
		this->Front = this->Line.front();
		if( this->Front == ':' ){
			this->Line.erase( this->Line.begin() );
			this->Front = this->Line.front();
			switch( this->Front ){
				case 'u':
					this->Direction = 'u';
					break;
				case 'd':
					this->Direction = 'd';
					break;
				case 'l':
					this->Direction = 'l';
					break;
				case 'r':
					this->Direction = 'r';
					break;
				case 'Q':
					this->Init = false;
					this->Connect = false;
					this->Snake.clear();
					break;
				default:
					break;
			}
		}
	}
}

void user::SetDirection( char _input ){
	this->Direction = _input;
}

void  user::AddSnake( int &_x, int &_y ){
	this->Snake.push_back( XY( _x, _y ) );
}

void  user::AddSnake( std::vector<XY> &_input ){
	this->Snake = _input;
}

void user::SetHeadTail( int &_x, int &_y ){
	this->Snake.clear();
	this->Snake.push_back( XY( _x, _y ) );	
}

void user::SetInit( bool _input ){
	this->Init = _input;
}

void user::ClearSnake(){
	this->Snake.clear();
}

char user::ReturnDirection(){
	return this->Direction;
}

bool user::ReturnConnect(){
	return this->Connect;
}

bool user::ReturnInit(){
	return this->Init;
}

void user::GameOver(){
	this->Init = false;
	this->Snake.clear();
	this->Send( ":G" );
}
