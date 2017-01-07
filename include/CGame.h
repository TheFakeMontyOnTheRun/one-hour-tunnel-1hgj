#ifndef CGAME_H
#define CGAME_H

namespace odb {
    class CGame {
    public:

      enum class EGameState{ kTitleScreen, kGame, kVictory, kGameOver };

      EGameState gameState = EGameState::kTitleScreen;

      int x = 0;
      int y = 0;
      int vx = 0;
      int vy = 0;
      explicit CGame();
      long timeEllapsed = 0;
      
      int map[ 12 ][ 12 ];
        void tick( long ms );
        CControlCallback getKeyPressedCallback();
        CControlCallback getKeyReleasedCallback();
    };
}
#endif
