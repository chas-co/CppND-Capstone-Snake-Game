#ifndef MENU_H
#define MENU_H

#include <vector>
#include <SDL2>

class Menu
{
   public:
    void Menu();

    int renderMenu(SDL_Surface* screen, TTF_Font* font);

   private:
    int _numMenuItems;
    vector<char>* _MenuItems;
    SDL_Surface _menu;
    bool _selected;
    SDL_color _colour;



};
#endif