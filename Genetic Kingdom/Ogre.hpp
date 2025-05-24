class Ogre : public Enemy {  
public:  
    Ogre(GridMap& map, float cellSize, const Genes& g)
        : Enemy(map, cellSize, g.speed)
    {
        health = g.health;
        arrowResist = g.arrowResist;
        magicResist = g.magicResist;
        artilleryResist = g.artilleryResist;
        setColor({ 0, 100, 0 });
        goldDrop = 20;
    }
};
