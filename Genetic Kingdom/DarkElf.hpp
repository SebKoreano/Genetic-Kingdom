class DarkElf : public Enemy {  
public:  
  DarkElf(GridMap& m, float cellSize, const Genes& g)
      : Enemy(m, cellSize, g.speed) {

      health = g.health;
      arrowResist = g.arrowResist;
      magicResist = g.magicResist;
      artilleryResist = g.artilleryResist;
      setColor(sf::Color(135, 206, 235));
      goldDrop = 50;
  }  
};
