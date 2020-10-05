#include "Tile.h"

// For å sette labelfarge i henhold til hvor mange miner som er rundt
const map<int, Color> minesToColor{ {1, Color::blue},
								   {2, Color::red},
								   {3,Color::dark_green},
								   {4, Color::dark_magenta},
								   {5, Color::dark_blue},
								   {6, Color::dark_cyan},
								   {7, Color::dark_red},
								   {8, Color::dark_yellow} };

// For å sette Tilelabel i henhold til state
const map<Cell, string> cellToSymbol{ {Cell::closed, ""},
									 {Cell::open, ""},
									 {Cell::flagged, "@<"} };

void Tile::open()
{
    if(state == Cell::flagged){
        return;
    }
	static_cast<Fl_Button*>(pw)->set();//Setter en button som trykket p�, tilsvarer �pnet rute
    state = Cell::open;
    if(isMine){
        set_label("X");
        set_label_color(minesToColor.at(2));
        redraw();
    }
}

void Tile::flag(){
    if(state == Cell::flagged){
        state = Cell::closed;
        set_label(cellToSymbol.at(state));
        return;
    }
    state = Cell::flagged;
    set_label(cellToSymbol.at(state));
}

void Tile::setAdjMines(int n){
    set_label(to_string(n));
    set_label_color(minesToColor.at(n));
}
