#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <pthread.h>
#include <ctime>
#include <sys/socket.h>
//#include <sys/types.h>
#include <netdb.h>
//#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "def.hpp"
#include "user.cpp"

using namespace std;

struct ClientInfo_{
	int Socket;
	string HostName;
} ClientInfo;

int InitSocket( int _port, string _hostname );
void CaughtSignal( int _signal );
void* StartConnection( void* _user);
void* CheckMap( void* );
int GetFirst();

int Socket = -1;
extern user *User[MAX_PLAYER];
int UserSize = 0;

int main( int argc, char* argv[] ){
	//bind ending signal
	//CTRL+C
	signal( SIGINT, CaughtSignal );
	//CTRL+Z
	signal( SIGTSTP, CaughtSignal );
	int Error = -1, Port = 0;
	if( argc < 2 ){
		cout<<"RUN: "<<argv[0]<<" PORT\n";
		return 1;
	}
	Port = atoi( argv[1] );
	Socket = InitSocket( Port, SERVER_NAME );
	if( Socket < 0 ){
		return 2;
	}
	//
	pthread_t TID_0;
	Error = pthread_create( &TID_0, NULL, CheckMap, NULL );
	if( Error ){
		cout<<"[ERROR] pthread_create (CheckMap): "<<Error<<"\n";
		CaughtSignal( 0 );
	}
	//NEW USER:
	sockaddr_in Client;
	socklen_t ClientSize = sizeof( sockaddr_in );
	hostent *Target = NULL;
	pthread_t TID;
	while( true ){
		do{
			Error = accept( Socket, (sockaddr *) &Client, &ClientSize );
		}while( Error < 0 );
		Target = gethostbyaddr( &Client.sin_addr.s_addr, sizeof( Client.sin_addr.s_addr ), Client.sin_family );
		if( Target == NULL ){
			perror( "[ERROR] gethostbyaddr" );
			CaughtSignal( 0 );
		}
		ClientInfo.Socket = Error;
		ClientInfo.HostName = Target->h_name;
		Error = pthread_create( &TID, NULL, StartConnection, (void*)&ClientInfo );
		if( Error ){
			cout<<"[ERROR] pthread_create (StartConnection): "<<Error<<"\n";
			CaughtSignal( 0 );
		}
	}	
	close( Socket );
	return 0;
}

int InitSocket( int _port, string _hostname ){
	int _Error = -1;
	sockaddr_in Server;
	int _Socket = socket( PF_INET, SOCK_STREAM, 0 );
	if( _Socket < 0 ){
		perror( "[ERROR] socket" );
		return -1;
	}
	/*
	_Error = fcntl( _Socket, F_SETFL, O_NONBLOCK );
	if( _Error < 0 ){
		perror( "[ERROR] fcntl" );
		return -1;
	}
	*/
	Server.sin_family = PF_INET;
	Server.sin_addr.s_addr = htonl( INADDR_ANY );
	Server.sin_port = htons( _port );
	_Error = bind( _Socket, (sockaddr *) &Server, sizeof(Server) );
	if( _Error < 0 ){
		perror( "[ERROR] bind" );
		return -1;
	}
	_Error = listen( _Socket, MAX_LISTEN_QUEUE );
	if( _Error < 0 ){
		perror( "[ERROR] listen" );
		return -1;
	}	
	return _Socket;
}

void CaughtSignal( int _signal ){
	if( _signal == SIGINT ){
		cout<<"\nCaught signal SIGINT!\nEXIT\n";
	}
	else if( _signal == SIGTSTP ){
		cout<<"\nCaught signal SIGTSTP!\nEXIT\n";
	}
	else{
		cout<<"\nCaught signal number: "<<_signal<<"\nEXIT\n";
	}
	close( Socket );
	exit( 0 );
}

void* StartConnection( void* _user ){
	ClientInfo_ ClientInfo = *(ClientInfo_ *) _user;
	int Num = GetFirst();
	if( Num < 0 ){
		cout<<"Too many users!\n";
		send( ClientInfo.Socket, "Too many users!", 15, 0 );
		close( ClientInfo.Socket );
		pthread_exit( NULL );
	}
	User[Num] = new user( );
	++UserSize;
	
	while( true ){
		
	}
	--UserSize;
	pthread_exit( NULL );
}

int GetFirst(){
	for( int i=0; i<MAX_PLAYER; ++i ){
		if( User[i] == NULL ){
			return i;
		}
	}
	return -1;
}

void* CheckMap( void* ){
	clock_t _now, _next;
	_now = clock();
	_next = _now + TIME_UPDATE;
	while( true ){
		if( UserSize > 0 and _now > _next ){
			
		}
		_now = clock();
		_next = _now + TIME_UPDATE;
	}
	pthread_exit( NULL );
}
