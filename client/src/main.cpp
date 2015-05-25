#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <pthread.h>
#include <signal.h>
#include "client.cpp"

using namespace std;

client * Pointer = NULL;
bool running = true;

void CaughtSignal( int _signal );
void* Input( void* );

int main( int argc, char* argv[] ){
	cout<<clock()<<"\n";
	//bind ending signal
	//CTRL+C
	signal( SIGINT, CaughtSignal );
	//CTRL+Z
	signal( SIGTSTP, CaughtSignal );
	int Error = -1, Port = 0;
	string Host;
	if( argc < 3 ){
		cout<<RED_COLOR<<BOLD_TEXT<<"NON ARGUMENT: HOST PORT \n"<<DEFAULT_COLOR
			<<"\tHOST - server name\n"
			<<"\tPORT - server port\n";
		return 1;
	}
	Host = argv[1];
	Port = atoi( argv[2] );
	bool Debug = false;
	client Client( Host, Port );
	Pointer = &Client;
	if( ! Client.ReturnInit() ){
		return 2;
	}
	Client.SetDebug( Debug );
	pthread_t PID_Input;
	Error = pthread_create( &PID_Input, NULL, Input, NULL );		
	if( Error ){
		cout<<"pthread_create \'Input\' failed: "<<Error<<"\n";
		return 2;
	}
	//Reveice data
	while( Client.ReturnConnected() and running ){
		Client.ReveiceData();
	}
	running = false;
	pthread_cancel( PID_Input );
	pthread_join( PID_Input, NULL );
	return 0;
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
	Pointer->StopClient();
	exit( 0 );
}

void* Input( void* ){
	char _input;
	string _tmp;
	if( Pointer == NULL ){
		cout<<"Problem with connect!\n";
		running = false;
		pthread_exit( NULL );
	}
	do{
		cin.get( _input );
		switch( _input ){
			case 'w':
				_tmp = ":u";
				Pointer->Send( _tmp ); 
				break;
			case 's':
				_tmp = ":d";
				Pointer->Send( _tmp ); 
				break;
			case 'd':
				_tmp = ":r";
				Pointer->Send( _tmp ); 
				break;
			case 'a':
				_tmp = ":l";
				Pointer->Send( _tmp ); 				
				break;
			case 'n':
				_tmp = ":N";
				Pointer->SetDeath();
				Pointer->Send( _tmp ); 				
				break;
			case 'Q':
				Pointer->StopClient();
				break;
			default:
				break;
		}		
	}while( running );
	pthread_exit( NULL );
}
