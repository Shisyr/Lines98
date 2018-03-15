
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Circles.hpp"

using namespace sf;
using namespace std;


bool isButton = false;
bool isNewCircle = false;
CircleShape circle;
const int W = 10;
const int H = 10;
int score = 0;
int nx;
int ny;
Text text;
RectangleShape screen[H][W];
RenderWindow window(VideoMode(1500, 1000), "SFML window");
Circles circles(window);

struct Cell{
    int row;
    int col;
    Cell(int aRow = 0, int aCol = 0) : row(aRow), col(aCol){}
};
void init(){
    int size = window.getSize().x / 17;
    int sY = window.getSize().y / 12;
    for(int i = 0;i < H;i++){
        int sX = window.getSize().x / 5;
        for(int j = 0;j < W;j++){
            RectangleShape s(Vector2f(size, size));
            s.setPosition(sX, sY);
            s.setFillColor(Color::White);
            s.setOutlineThickness(2);
            s.setOutlineColor(Color::Cyan);
            screen[i][j] = s;
            sX += size;
        }
        sY += size;
    }
}

void drawScreen(){
    for(int i = 0;i < H;i++){
        for(int j = 0;j < W;j++){
            window.draw(screen[i][j]);
        }
    }
}
void parseToInt(vector< vector<int> >& c){
    vector< vector<CircleShape> > cr = circles.getCircles();
    for(int i = 0;i < cr.size();i++){
        for(int j = 0;j < cr[i].size();j++){
            if(cr[i][j].getFillColor() != Color::White){
                c[i][j] = -1;
            }
        }
    }
}
bool isPossibleToMove(int sRow, int sCol, int fRow, int fCol){
    vector< vector<int> > c{H, vector<int>(W)};
    parseToInt(c);
    queue<Cell> q;
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, 1, 0, -1};
    q.push(Cell(sRow, sCol));
    c[sRow][sCol] = 1;
    while(not q.empty()){
        Cell u = q.front();
        q.pop();
        for(int i = 0;i < dr.size();i++){
            int tr = u.row + dr[i];
            int tc = u.col + dc[i];
            if(tr < 0 or tr >= H or tc < 0 or tc >= W){
                continue;
            }
            if(c[tr][tc] == 0){
                c[tr][tc] = c[u.row][u.col] + 1;
                q.push(Cell(tr,tc));
                if(tr == fRow and tc == fCol){
                    return true;
                }
            }
        }
    }
    return false;
}

void updateScore(){
    text.setString("Score: " + to_string(score));
}


void getScore(){
    vector< vector<CircleShape> > c = circles.getCircles();
    vector<CircleShape> other;
    for(int i = 0;i < c.size();i++){
        for(int j = 0;j < c[i].size();j++){
            int countX = 1;
            int countY = 1;
            if(c[i][j].getFillColor() != Color::White){
                if(i + 4 < c.size()){
                    int i1 = i;
                    int j1 = j;
                    while(c[i1][j1].getFillColor() == c[i1 + 1][j1].getFillColor()){
                        countY++;
                        i1++;
                        if(i1 + 1 >= c.size()){
                            break;
                        }
                    }
                    if(countY >= 5){
                        while(i1 >= i){
                            c[i1][j1].setFillColor(Color::White);
                            i1--;
                        }
                        score += 10;
                        updateScore();
                    }
                }
                if(j + 4 < c.size()){
                    int i1 = i;
                    int j1 = j;
                    while(c[i1][j1].getFillColor() == c[i1][j1 + 1].getFillColor()){
                        countX++;
                        j1++;
                        if(j1 + 1 >= c.size()){
                            break;
                        }
                    }
                    if(countX >= 5){
                        while(j1 >= j){
                            c[i1][j1].setFillColor(Color::White);
                            j1--;
                        }
                        score += 10;
                        updateScore();
                    }
                }
            }
        }
    }
    circles.setCircles(c);
}
void button(Event& event){
    if(event.type == Event::MouseButtonPressed){
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        vector< vector<CircleShape> > c = circles.getCircles();
        for(int i = 0;i < c.size();i++){
            for(int j = 0;j < c[i].size();j++){
                int cX = c[i][j].getPosition().x;
                int cY = c[i][j].getPosition().y;
                int cR = c[i][j].getRadius() * 2;
                if(x >= cX and x < cX + cR and y >= cY and y < cY + cR){
                    if(c[i][j].getFillColor() != Color::White){
                        isButton = true;
                        circle = c[i][j];
                        nx = i;
                        ny = j;
                        cout << nx << " " << ny << endl;
                    }
                    else{
                        if(isButton){
                            if(isPossibleToMove(nx, ny, i, j)){
                                CircleShape cir = c[i][j];
                                c[i][j].setFillColor(circle.getFillColor());
                                c[nx][ny].setFillColor(cir.getFillColor());
                                isButton = false;
                                isNewCircle = true;
                            }
                        }
                    }
                }
            }
        }
        circles.setCircles(c);
        getScore();
    }
}

//void getScore(){
//    
//}
int main(int, char const**)
{
    Font font;
    if(!font.loadFromFile("/Users/Mukhamed/Downloads/fonts/Black.ttf")){ // write your directory for format of string
        
    }
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setString("Score: " + to_string(score));
    text.setPosition(window.getSize().x / 12, window.getSize().y / 5);
    circles.init();
    init();
    circles.newCircles();
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }
            button(event);
            if(isNewCircle){
                circles.newCircles();
                isNewCircle = false;
            }
            if(event.type == Event::KeyPressed and event.key.code == Keyboard::Space){
                circles.newCircles();
                
            }

            // Escape pressed: exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();
        drawScreen();
        window.draw(text);
        circles.draw(window);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
