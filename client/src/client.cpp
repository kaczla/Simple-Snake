#include "client.hpp"

client::client( string _host, int _port ){
	this->Init = true;
	this->SnakeInit = false;
	this->Death = false;
	this->Width = -1;
	this->Height = -1;
	this->Player = -1;
	this->SnakeTime = -1;
	this->MyID = -1;
	for( int i=0; i<100; ++i ){
		for( int j=0; j<100; ++j ){
			this->Map[i][j] = -1;
		}
	}
	this->SnakeChar = {
		//FOOD
		{ 0, 'O' },
		//SNAKE
		{ 1, '1' }, { 2, '2' }, { 3, '3' }, { 4, '4' }, { 5, '5' },
		{ 6, '6' }, { 7, '7' }, { 8, '8' }, { 9, '9' }, { 10, '@' },
		{ 11, '#' }, { 12, '$' }, { 13, '%' }, { 14, '&' }, { 15, '=' },
		{ 16, '+' }
	};
	this->SetPort( _port );
	this->SetHost( _host );
	this->Init = this->StartConnection();
}

client::~client(){
	this->Disconnect();
}

void client::SetPort( int &_port ){
	if( _port > 1024 and _port <= 65535 ){
		this->Port = _port;
	}
	else{
		this->Init = false;
		cout<<RED_ERROR<<" Wrong PORT: "<<_port<<"\n";
	}
	
}

void client::SetHost( string &_host ){
	if( _host.empty() ){
		this->Init = false;
		cout<<RED_ERROR<<" HOST is empty!\n";
	}
	else{
		this->Host = _host;
	}	
}

bool client::ReturnInit(){
	return this->Init;
}

bool client::StartConnection(){
	this->Debug = false;
	this->Connected = false;
	if( this->Init ){
		this->Socket = -1;
		//CREATIN SOCKET
		cout<<"WAIT: Creating socket";
		this->Socket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( this->Socket < 0 ){
			this->Init = false;
			cout<<RED_ERROR<<" Creating socket (socket):"<<this->Socket<<"\n\n"
				<<RED_COLOR<<"### APPLICATION ABORTED ###"
				<<DEFAULT_COLOR<<"\n";
			return false;
		}
		cout<<"\r[1/6] Created socket: "<<this->Socket<<"\n";
	
		//FOR BIND IP AND PORT WITH SOCKET ( WHEN IP AND PORT IS USED )
		cout<<"WAIT: setsockopt";
		int _tmp = 1;
		this->Error = setsockopt( this->Socket, SOL_SOCKET, SO_REUSEADDR, (char const*)&_tmp, sizeof( _tmp ) );
		if( this->Error < 0 ){
			this->Init = false;
			cout<<RED_ERROR<<" Creating socket (setsockopt):"<<this->Error<<"\n\n"
				<<RED_COLOR<<"### APPLICATION ABORTED ###"
				<<DEFAULT_COLOR<<"\n";
			return false;
		}
		cout<<"\r[2/6] setsockopt\n";
		
		//NONBLOCK SOCKET
		cout<<"WAIT: fcntl O_NONBLOCK";
		this->Error = fcntl( this->Socket, F_SETFL, O_NONBLOCK );
		if( this->Error < 0 ){
			this->Init = false;
			cout<<RED_ERROR<<" fcntl O_NONBLOCK:"<<this->Error<<"\n\n"
				<<RED_COLOR<<"### APPLICATION ABORTED ###"
				<<DEFAULT_COLOR<<"\n";
			return false;
		}
		cout<<"\r[3/6] fcntl O_NONBLOCK\n";
		
		//ASYNC
		cout<<"WAIT: fcntl O_ASYNC";
		this->Error = fcntl( this->Socket, F_SETFL, O_ASYNC );
		if( this->Error < 0 ){
			this->Init = false;
			cout<<RED_ERROR<<" fcntl O_ASYNC:"<<this->Error<<"\n\n"
				<<RED_COLOR<<"### APPLICATION ABORTED ###"
				<<DEFAULT_COLOR<<"\n";
			return false;
		}
		cout<<"\r[4/6] fcntl O_ASYNC\n";
		
		//GETHOSTBTNAME
		cout<<"WAIT: gethostbyname";
		hostent* _host = NULL;
		_host = gethostbyname( this->Host.c_str() );
		if( _host == NULL ){
			this->Init = false;
			cout<<RED_ERROR<<" Host = "<<this->Host<<"\n"<<RED_ERROR;
			herror( " h_errno: " );
			cout<<"\n\n"<<RED_COLOR<<"### APPLICATION ABORTED ###"
				<<DEFAULT_COLOR<<"\n";
			return false;
		}
		cout<<"\r[5/6] gethostbyname\n";
		
		//Connecting with host
		cout<<"WAIT: Conneting "<<this->Host<<":"<<this->Port;
		sockaddr_in _server;
		_server.sin_family = AF_INET;
		_server.sin_port = htons( this->Port );
		_server.sin_addr = *( ( const in_addr* ) _host->h_addr );
		memset( &_server.sin_zero, '\0', 8 );
		this->Error = connect( this->Socket, (sockaddr*)&_server, sizeof(_server) );
		if( this->Error < 0 ){
			this->Init = false;
			cout<<RED_ERROR<<" connect: "<<strerror( errno )<<"\n\n"
				<<RED_COLOR<<"### APPLICATION ABORTED ###"
				<<DEFAULT_COLOR<<"\n";
			return false;
		}
		cout<<"\r[6/6] Connected with "<<this->Host<<":"<<this->Port<<"\n";
		this->Connected = true;
		
		this->Error = 0;
		return true;
	}
	return false;
}

void client::Disconnect(){
	if( this->Connected ){
		this->TMP = ":Q";
		this->Send( this->TMP );
		cout<<this->ReturnTime()<<"Disconnected\n";
		close( this->Socket );
		this->Connected = false;
	}
}

bool client::Reveice(){
	if( this->Connected ){
		memset( this->Buffer, 0, MAX_RECV_BUFFER );
		this->ErrorReveice = recv( this->Socket, Buffer, MAX_RECV_BUFFER-1, 0 );
		if( this->ErrorReveice > 0 ){
			this->ReveiceText = this->Buffer;
			if( this->Debug ){
				cout<<MAGENTA_COLOR<<">> "<<this->ReveiceText<<DEFAULT_COLOR<<"\n";
			}
			return true;
		}
		else{
			return false;
		}		
	}
	return false;
}

bool client::Send( string &_input ){
	if( this->Connected ){
		if( _input.back() != '\n' ){
			_input += '\n';
		}
		this->ErrorSend = send( this->Socket, _input.c_str(), _input.size(), 0 );
		if( this->ErrorSend < 0 ){
			return false;
		}
		else{
			if( this->Debug ){
				cout<<BLUE_COLOR<<"<< "<<_input<<DEFAULT_COLOR<<"\n";
			}
			return true;
		}
	}
	return false;
}

bool client::ReturnConnected(){
	return this->Connected;
}

void client::SetDebug( bool _input ){
	this->Debug = _input;
}

void client::StopClient(){
	this->Disconnect();
	cout<<this->ReturnTime()<<RED_COLOR<<"STOP CLIENT"<<DEFAULT_COLOR<<"\n";
}

void client::ReveiceData(){
	if( this->Reveice() ){
		this->Lines.clear();
		this->Lines.str( this->ReveiceText );
		while( getline( this->Lines, this->Line ) ){
			if( this->Line.find( '\r' ) != string::npos ){
				this->Line.substr( 0, this->Line.size() -1 );
			}
			if( this->Line.size() < 1 ){
				continue;
			}
			if( this->Line.front() == ':' ){
				this->Line.erase( this->Line.begin() );
				switch( this->Line.front() ){
					case 'W':
						this->Line.erase( this->Line.begin() );
						this->Width = stoi( this->Line );
						this->CheckSnakeInit();
						break;
					case 'H':
						this->Line.erase( this->Line.begin() );
						this->Height = stoi( this->Line );
						this->CheckSnakeInit();
						break;
					case 'X':
						this->Line.erase( this->Line.begin() );
						this->Player = stoi( this->Line );
						this->CheckSnakeInit();
						break;
					case 'T':
						this->Line.erase( this->Line.begin() );
						this->SnakeTime = stoi( this->Line );
						this->SnakeTime = SnakeTime * CLOCKS_PER_SEC / 1000;
						this->CheckSnakeInit();
						break;
					case 'P':
						this->Line.erase( this->Line.begin() );
						this->MyID = stoi( this->Line );
						this->CheckSnakeInit();
						break;
					case 'p':
						//cout<<"Line:\'"<<Line<<"\'\n";
						this->Line.erase( this->Line.begin() );
						while( this->Line.front() == ' ' ){
							this->Line.erase( this->Line.begin() );
						}
						this->TMP = this->Line.front();
						//erase iterator: [ begin, end )
						this->Line.erase( this->Line.begin(), this->Line.begin() + 2 );
						this->Other = stoi( this->TMP ); 
						while( this->Line.front() == ' ' ){
							this->Line.erase( this->Line.begin() );
						}
						this->Find1 = 0;
						while( ( Find2 = Line.find( ' ', Find1 ) ) != string::npos ){ 
							this->TMP = Line.substr( Find1, Find2 - Find1 );
							Find1 = Find2 + 1 ;
							this->Find = this->TMP.find( ';' );
							this->TMP_XY = this->TMP.substr( 0, this->Find );
							this->_xy.X = stoi( this->TMP_XY );
							this->TMP_XY = this->TMP.substr( this->Find + 1, this->TMP.size() - this->Find - 1  );
							this->_xy.Y = stoi( this->TMP_XY );
							this->Map[_xy.Y][_xy.X] = this->Other;
						}
						break;
					case 'R':
						this->PrintMap();
						this->ClearMap();
						break;
					case 'G':
						cout<<this->ReturnTime()<<RED_COLOR<<BOLD_TEXT<<"GAME OVER!"<<DEFAULT_COLOR<<"\n";
						cout<<this->ReturnTime()<<RED_COLOR<<BOLD_TEXT<<"GAME OVER!"<<DEFAULT_COLOR<<"\n";
						cout<<this->ReturnTime()<<RED_COLOR<<BOLD_TEXT<<"GAME OVER!"<<DEFAULT_COLOR<<"\n";
						this->Death = true;
						break;
					case 'Q':
							cout<<this->ReturnTime()<<"Disconnected\n";
							close( this->Socket );
							this->Connected = false;
							return;
						break;
					default:
						break;
				}
			}
			else{
				cout<<this->ReturnTime()<<this->Line<<"\n";
			}
		}
	}
}

void client::CheckSnakeInit(){
	if( Width != -1 and Height != -1 and Player != -1 and SnakeTime != -1 and MyID != -1 ){
		this->SnakeInit = true;
		this->LRMap = "║";
		this->TopMap = "╔";
		this->BottomMap = "╚";
		for( this->_i = 0; this->_i < this->Width; ++this->_i ){ 
			this->TopMap += "═";
			this->BottomMap += "═";
		}
		this->TopMap += "╗";
		this->BottomMap += "╝";
	}
}

void client::PrintMap(){
	if( this->SnakeInit ){
		cout<<'\r'<<this->ReturnTime()
			<<BOLD_TEXT<<"YOUR NUMBER: "<<this->MyID
			<<" CHAR: "<<this->SnakeChar[this->MyID];
		if( this->Death ){
			cout<<RED_COLOR<<"  YOU ARE DEATH"<<DEFAULT_COLOR<<"  "<<GREEN_COLOR<<"TRY AGAIN!";
		}
		cout<<DEFAULT_COLOR<<"\n";
		cout<<this->TopMap<<"\n";
		for( this->_i = 0; this->_i < this->Height; ++this->_i ){
			cout<<this->LRMap;
			for( this->_j = 0; this->_j < this->Width; ++this->_j ){
				if( this->Map[_i][_j] < 0 ){
					cout<<" ";
				}
				else{
					cout<<this->SnakeChar[this->Map[_i][_j]];
				}
			}
			cout<<this->LRMap<<"\n";
		}
		cout<<this->BottomMap<<"\n";
	}
}

void client::ClearMap(){
	for( this->_i = 0; this->_i < this->Height; ++this->_i ){
		for( this->_j = 0; this->_j < this->Width; ++this->_j ){
			this->Map[_i][_j] = -1;
		}
	}
}

string client::ReturnTime(){
	time( &this->Time );
	TimeInfo = localtime( &this->Time );
	strftime( this->TimeBuffer, 16, "[%T] ", this->TimeInfo );
	return this->TimeBuffer ;
}

string client::ReturnTime_(){
	return this->ReturnTime();
}

void client::SetDeath(){
	this->Death = false;
}
