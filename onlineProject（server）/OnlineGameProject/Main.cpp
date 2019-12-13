#include "Game.h"

int main(int argc, char* argv[]) {
	//int random = rand() % 2;
	//Server MyServer(1111); //Create server on port 100

	//Game* game;
	//game = new Game(MyServer, random);

	//if (random == 0) {
	//	MyServer.ListenForNewConnection(false);
	//}
	//else {
	//	MyServer.ListenForNewConnection(true);
	//}

	//game->run();

	Game game;
	game.run();

	return 0;

}