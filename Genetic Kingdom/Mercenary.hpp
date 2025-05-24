class Mercenary : public Enemy {  
public:  
    Mercenary(GridMap& m, float cellSize, const Genes& g)  
        : Enemy(m, cellSize, g.speed) {  
        health = g.health;  
        arrowResist = g.arrowResist;  
        magicResist = g.magicResist;  
        artilleryResist = g.artilleryResist;  
        setColor(sf::Color(128, 128, 128));  
        goldDrop = 40;  
    }  
};
