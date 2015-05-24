#ifndef _def_
#define _def_

#define SERVER_NAME "Simple_Snake"
#define MAX_LISTEN_QUEUE 5
#define MAX_RECV 4048
#define MAX_PLAYER 4
#define WIDTH 35
#define HEIGHT 35


#define MAX_PLAYER_EX 16
#if MAX_PLAYER >= MAX_PLAYER_EX
	#undef MAX_PLAYER_EX
	#define MAX_PLAYER_EX MAX_PLAYER
#endif

#define BASE_TIME_UPDATE 700
#define TIME_UPDATE BASE_TIME_UPDATE * CLOCKS_PER_SEC / 1000

#endif
