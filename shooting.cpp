#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "engine/engine.hpp"
#include "components/components.hpp"

int main()
{
  SDL_Event event;
  float quit = false;
  CGame game;
  game.init("Invader Game", 500, 500);

  game.changeRoot(new CObject(CVector2(0.0f, 0.0f)));
  CObject *invaderGame = new CObject(CVector2(0.0f, 0.0f));
  invaderGame->addComponent(new CInvaderGame());
  game.addObject(invaderGame);

  while(!quit)
  {
    game.run();
    while(SDL_PollEvent(&event))
    {
      game.handleEventMessage(event);
      if(SDL_QUIT == event.type)
      {
        quit = true;
      }
    }
  }
}
