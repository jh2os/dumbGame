#ifndef MENU_H
#define MENU_H

enum MenuItemType {
  MENU_BUTTON,
  MENU_SLIDER,
  MENU_TEXTBOX,
};

struct ManuItem {

}

class Menu {
public:
  Menu();
  float width;
  float height;
  glm::vec4 menuBorderColor;
  glm::vec4 backgroundColor;
  glm::vec4 buttonColor;
  glm::vec4 textColor;
  glm::vec4 highlightColor;
  float highlightSize;
};


#endif
