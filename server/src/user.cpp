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
	send( this->Socket, ":quit", 5, 0 );
	close( this->Socket );
}

int user::Send( std::string _input ){
	if( _input.empty() ){
		return -1;
	}
	else{
		_input.append( "\n" );
		this->ErrorSend = send( this->Socket, _input.c_str(), _input.size(), 0 );
		std::cout<<"TEXT: "<<_input<<": "<<this->ErrorSend<<"\n";
		std::cout<<this->Socket<<"\n";
		return this->ErrorSend;
	}
}

int user::SendEx( std::string &_input ){
	if( _input.empty() ){
		return -1;
	}
	else{
		_input.append( "\n" );
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

void user::Action(){
	this->Msg = this->msg;
	//TO DO
	if( this->Msg.front() == ':' ){
		this->Msg.erase( this->Msg.begin() );
	}
}

void user::SetDirection( char _input ){
	this->Direction = _input;
}

void  user::SetHead( int &_x, int &_y ){
	this->Head.Set( _x, _y );
}

void  user::SetTail( int &_x, int &_y ){
	this->Tail.Set( _x, _y );
}

void  user::AddSnake( int &_x, int &_y ){
	this->Snake.push_back( XY( _x, _y ) );
}

void  user::AddSnake( std::vector<XY> &_input ){
	this->Snake = _input;
}

void user::SetHeadTail( int &_x, int &_y ){
	this->Head.Set( _x, _y );
	this->Tail.Set( _x, _y );
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
