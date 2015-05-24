#ifndef _def_
#define _def_

#define SERVER_NAME "Simple_Snake"
#define MAX_LISTEN_QUEUE 5
#define MAX_PLAYER 4
#define MAX_PLAYER_EX 16
#if MAX_PLAYER >= MAX_PLAYER_EX
	#undef MAX_PLAYER_EX
	#define MAX_PLAYER_EX MAX_PLAYER
#endif

#define TIME_UPDATE 500

#endif
