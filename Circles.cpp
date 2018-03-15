//
//  Circles.cpp
//  Lines98
//
//  Created by Шисыр Мухаммед Шарипович on 18.12.17.
//  Copyright © 2017 Шисыр Мухаммед Шарипович. All rights reserved.
//

#include "Circles.hpp"
#include <iostream>
using namespace std;
using namespace sf;

Circles::Circles(RenderWindow& win){
    h = win.getSize().y;
    w = win.getSize().x;
    r = 35;
}
void Circles::chooseColors(){
    for(int i = 0;i < 3;i++){
        int r = rand() % 5;
        switch(r){
            case 0:
                colors.push_back(Color::Red);
                break;
            case 1:
                colors.push_back(Color::Green);
                break;
            case 2:
                colors.push_back(Color::Blue);
                break;
            case 3:
                colors.push_back(Color::Yellow);
                break;
            case 4:
                colors.push_back(Color::Magenta);
                break;
        }
    }
}

void Circles::init(){
    int size = w / 17;
    int cY = h / 12 + 6;
    for(int i = 0;i < 10;i++){
        vector<CircleShape> row;
        int cX = w / 5 + 6;
        for(int j = 0;j < 10;j++){
            CircleShape c(r);
            c.setPosition(cX, cY);
            c.setFillColor(Color::White);
            row.push_back(c);
            cX += size;
        }
        cY += size;
        circles.push_back(row);
    }
}
vector< vector<CircleShape> > Circles::getCircles(){
    return circles;
}
void Circles::newCircles(){
    chooseColors();
    while(not colors.empty()){
        int x = rand() % 10;
        int y = rand() % 10;
        if(circles[x][y].getFillColor() == Color::White){
            circles[x][y].setFillColor(colors.back());
            colors.pop_back();
            if(isEndOfGame()){
                break;
            }
        }
    }
}
void Circles::setCircles(std::vector< std::vector<sf::CircleShape> > s){
    circles = s;
}
bool Circles::isEndOfGame(){
    int count = 0;
    for(int i = 0;i < circles.size();i++){
        for(int j = 0;j < circles[i].size();j++){
            if(circles[i][j].getFillColor() == Color::White){
                count++;
            }
        }
    }
    if(count == 1){
        return true;
    }
    return false;
}

void Circles::draw(sf::RenderWindow& window){
    for(int i = 0;i < circles.size();i++){
        for(int j = 0;j < circles[i].size();j++){
            window.draw(circles[i][j]);
        }
    }
}
