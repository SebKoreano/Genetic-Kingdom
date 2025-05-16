#include "Towers.hpp" 

class ArtilleryTower : public Tower {
public:
    ArtilleryTower(float cellSize, int row, int col)
        : Tower(/*cost=*/150,
            /*range=*/2.f,
            /*damage=*/40,
            /*reloadTime=*/2.0f,
            cellSize, row, col)
    {
        shape.setFillColor(sf::Color(128, 128, 128)); // Gris
    }
};