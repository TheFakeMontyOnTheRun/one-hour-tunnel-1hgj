#include <functional>

#include <iostream>

#include "Common.h"
#include "CGame.h"

namespace odb {

  CGame::CGame() {
    gameState = EGameState::kGame;
    x = y = 1;
    timeEllapsed = vx = vy = 0;

    for ( int y = 1; y < 12; ++y ) {
      for ( int x = 0; x < 12; ++x ) {
	map[ y ][ x ] = 1;

	if ( x == y ) {
	  map[ y ][ x ] = 0;

	  if ( x % 2 == 0 ) {
	    map[ y - 1][ x ] = 0;
	  } else {
	    map[ y ][ x - 1 ] = 0;
	  }
	}
      }
    }

    map[ 1 ][ 1 ] = 0;
    map[ 2 ][ 1 ] = 0;
    map[ 2 ][ 2 ] = 0;

    map[ 11 ][ 10 ] = 0;
    map[ 10 ][ 10 ] = 0;
    map[ 11 ][ 11 ] = 2;
  }



    void CGame::tick( long ms ) {

      if (gameState == EGameState::kVictory ) {
	if ( x > 0 && y > 0) {
	  x --;
	  y --;
	}
	return;
      }
      x += vx;
      y += vy;
      timeEllapsed += ms;




      if ( timeEllapsed >= 60000 ) {
	gameState = EGameState::kGameOver;
      }


      if ( x > 440 ) {
	x = 440;
      }

      if ( y > 440 ) {
	y = 440;
      }

      if ( x < 40 ) {
	x = 40;
      }

      if ( y < 40 ) {
	y = 40;
      }

      if ( map[ ( y / 40 ) ][ ( x / 40 ) ] == 1 ) {
	gameState = EGameState::kGameOver;
      }

      if ( map[ ( (35 + y) / 40 )  ][ ( x / 40 ) ] == 1 ) {
	gameState = EGameState::kGameOver;
      }

      if ( map[ ( y / 40 ) ][ ( (x + 35) / 40 ) ] == 1 ) {
	gameState = EGameState::kGameOver;
      }

      if ( map[ ( ( y + 35) / 40 ) ][ ( (x + 35) / 40 ) ] == 1 ) {
	gameState = EGameState::kGameOver;
      }

      if ( map[ ( y / 40 ) ][ ( x / 40 ) ] == 2 ) {
	gameState = EGameState::kVictory;
      }

      if ( map[ ( (35 + y) / 40 )  ][ ( x / 40 ) ] == 2 ) {
	gameState = EGameState::kVictory;
      }

      if ( map[ ( y / 40 ) ][ ( (x + 35) / 40 ) ] == 2 ) {
	gameState = EGameState::kVictory;
      }

      if ( map[ ( ( y + 35) / 40 ) ][ ( (x + 35) / 40 ) ] == 2 ) {
	gameState = EGameState::kVictory;
      }
    }

    CControlCallback CGame::getKeyPressedCallback() {
        return [&](ECommand command) {
            if ( command == ECommand::kLeft ) {
                std::cout << "left pressed" << std::endl;
		vx = -1;
            }

          if ( command == ECommand::kRight ) {
                std::cout << "Right pressed" << std::endl;
		vx = 1;
	  }
            if ( command == ECommand::kUp ) {
                std::cout << "up pressed" << std::endl;
		vy = -1;
	    }

          if ( command == ECommand::kDown ) {
                std::cout << "down pressed" << std::endl;
		vy = 1;
            }
        };
    }

    CControlCallback CGame::getKeyReleasedCallback() {
        return [&](ECommand command) {


	    switch (gameState ) {
	    case EGameState::kGame:
	      if ( command == ECommand::kLeft ) {
                std::cout << "left released" << std::endl;
		vx = 0;
	      }
	      
	      if ( command == ECommand::kRight ) {
                std::cout << "right released" << std::endl;
		vx = 0;
	      }
	      
	      if ( command == ECommand::kUp ) {
                std::cout << "up released" << std::endl;
		vy = 0;
	      }
	      
	      if ( command == ECommand::kDown ) {
                std::cout << "down released" << std::endl;
		vy = 0;
	      }
	      return;


	    case EGameState::kGameOver:
	      gameState = EGameState::kTitleScreen;


	    case EGameState::kTitleScreen:
	      gameState = EGameState::kGame;
	      x = y = 1;
	      timeEllapsed = vx = vy = 0;
	      return;
	    }



        };
    }
}
