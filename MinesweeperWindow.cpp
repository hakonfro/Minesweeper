#include "MinesweeperWindow.h"

MinesweeperWindow::MinesweeperWindow(Point xy, int width, int height, int mines, const string& title) :
	Graph_lib::Window(xy, width * cellSize, height*cellSize, title), width(width), height(height), mines(mines)
	//Initialiser medlemsvariabler, bruker også konstruktøren til Windowsklassen
{
    srand(static_cast<unsigned int>(time(NULL)));
	// Legg til alle tiles på vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int y = i* cellSize,
				x = j * cellSize;
			tiles.push_back(new Tile{Point{x, y},cellSize,cb_click});
            //cout << tiles[str-1].isMine << endl;
			attach(tiles.back());
		}
	}

    for(int i = mines; i > 0; i--){
        int x = 0 + ( std::rand() % ( tiles.size() - 0 + 1 ) );
        if(tiles[x].isMine){
            cout << "Crash\n";
            i++;
        }
        else{
            cout << "Mine paa: " << x << "\n";
            tiles[x].isMine = true;
        }
    }

	// Fjern window reskalering
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());
}

int MinesweeperWindow::countMines(vector<Point> points) const {
    int sumMines = 0;
    for(Point p : points){
        if(at(p).isMine){
            sumMines++;
        }
    }
	return sumMines;
};
vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}

	return points;
}

void MinesweeperWindow::openTile(Point xy) {
    Tile& t = at(xy);
    if(t.state == Cell::open || t.state == Cell::flagged){
        return;
    }
    t.open();
    if(!t.isMine){
        vector<Point> tmp = adjacentPoints(xy);
        if(0 < countMines(tmp)){
            t.setAdjMines(countMines(tmp));
        } else{
            for(Point p : adjacentPoints(xy)){
                openTile(p);
            }
        }
    }
}

void MinesweeperWindow::flagTile(Point xy) {
    Tile& t = at(xy);
    if(t.state == Cell::open){
        return;
    }
    at(xy).flag();
}

//Kaller opentile ved venstreklikk og flagTile ved høyreklikk
void MinesweeperWindow::cb_click(Address, Address pw)
{
	Point xy{ Fl::event_x(),Fl::event_y() };
	MouseButton mb = static_cast<MouseButton>(Fl::event_button());
	auto& win = reference_to<MinesweeperWindow>(pw);

	if (!win.inRange(xy)) {
		return;
	}

	switch (mb) {
	case MouseButton::left:
		win.openTile(xy);
		break;
	case MouseButton::right:
		win.flagTile(xy);
		break;
	}
	win.flush();
}
