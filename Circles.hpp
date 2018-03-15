//
//  Circles.hpp
//  Lines98
//
//  Created by Шисыр Мухаммед Шарипович on 18.12.17.
//  Copyright © 2017 Шисыр Мухаммед Шарипович. All rights reserved.
//

#ifndef Circles_hpp
#define Circles_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Circles{
public:
    Circles(sf::RenderWindow& win);
    void draw(sf::RenderWindow& window);
    void init();
    void chooseColors();
    void newCircles();
    bool isEndOfGame();
    void setCircles(std::vector< std::vector<sf::CircleShape> > s);
    std::vector< std::vector<sf::CircleShape> > getCircles();
    
private:
    std::vector<sf::Color> colors;
    std::vector< std::vector<sf::CircleShape> > circles;
    int w;
    int h;
    int r;
};
#endif /* Circles_hpp */
