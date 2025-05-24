class Harpy : public Enemy {  
public:  
    Harpy(GridMap& m, float cellSize, const Genes& g)  
        : Enemy(m, cellSize, g.speed) {  
        health = g.health;  
        arrowResist = g.arrowResist;  
        magicResist = g.magicResist;  
        artilleryResist = g.artilleryResist;  
        setColor(sf::Color(139, 69, 19));  
        goldDrop = 30;  
    }  
};
