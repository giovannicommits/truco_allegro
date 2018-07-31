#pragma once
#include <iostream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include <string>

using namespace std;

class Button {
private:
	int id;
	int altura;
	int largura;
	int x;
	int y;
	bool active;
	string texto;
	int cor;
	ALLEGRO_FONT* font16;

public:
	Button(int c_largura, int c_altura, int c_x, int c_y, int id, string ctexto, int ccor);
	~Button();
	bool isClicked(ALLEGRO_MOUSE_STATE mouse_state);
	void draw();
	int getId();
	void deactivate();
	void activate();
	bool isActive();
};
