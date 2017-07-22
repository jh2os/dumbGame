#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu : public Gamestate {
public:
  MainMenu();
  void init();
  void event(SDL_Event &ev);
  void logic();
  void render();
};

#endif
