#include "stdafx.h"
#include "Button.h"


Button::Button(int c_largura, int c_altura, int c_x, int c_y, int c_id, string ctexto, int ccor) : altura(c_altura),
largura(c_largura), x(c_x), y(c_y), id(c_id), active(true), texto(ctexto), cor(ccor) {
	font16 = al_load_font("arial.ttf", 16, 0);
}


Button::~Button() {
	al_destroy_font(font16);
}

/*
	confere se o botao foi clicado
*/
bool Button::isClicked(ALLEGRO_MOUSE_STATE mouse_state) {
	if (mouse_state.x < x + largura && mouse_state.x > x &&
		mouse_state.y < y + altura && mouse_state.y > y)
		return true;
	else
		return false;
}

/*
	desenha o botao
*/
void Button::draw() {
	if(cor > 255/2)
		al_draw_filled_rectangle(x, y, x + largura, y + altura, al_map_rgb(0, 0, 0));
	else
		al_draw_filled_rectangle(x, y, x + largura, y + altura, al_map_rgb(255, 255, 255));
	al_draw_text(font16, al_map_rgb(cor, cor, cor), x + largura / 2, y + altura / 2 - al_get_font_line_height(font16)/2, ALLEGRO_ALIGN_CENTRE, texto.c_str());
	
}

int Button::getId() { return id; }
void Button::deactivate() { active = false;  }
void Button::activate() { active = true;  }
bool Button::isActive() {  return active;  }