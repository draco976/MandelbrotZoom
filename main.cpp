#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <stack>
#include <string>

#include "textbox.h"
#include "button.h"
#include "color.h"
#include "history.h"


#define double long double  // for greater precision

using namespace std ;


const double E = 2.71828182845904523536;
int MAX_ITER = 1000 ;
int N = 500 ;
double ZOOM_IN_FACTOR = 1.5 ;

const double ORIG_X = -0.5 ;
const double ORIG_Y = 0 ;
const double ORIG_SZ = 2 ;

const double SIZE = 2000 ;
const double OPTIONS_SIZE = 700 ;
const double OPTIONS_CENTRE = SIZE + OPTIONS_SIZE/2 ;


RGB pixel_data[2000][2000] ;



// Calculating the number of iterations z = z^2 + z0 to estimate color at point
double count_iterations (double x0, double y0) {
    double x=0 ;
    double y=0 ;
    double n = 0 ;
    double xtemp ;
    
    while (x*x + y*y <= 1<<20 and n < MAX_ITER) {
        xtemp = x*x-y*y + x0;
        y = 2*x*y + y0;
        x = xtemp ;
        n += 1 ;
    }
    
    if(n==MAX_ITER) {
        return n ;
    }
    
    double nu = log(log(x*x+y*y)/2 / log(2)) / log(2) ;
    n += 1-nu ;
    return n ;
}

// Draw the Mandelbrot pattern on canvas
void draw_image(sf::RenderWindow &window) {
    
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            RGB rgb = pixel_data[i][j] ;
            
            sf::RectangleShape r ;
            r.setPosition(i * SIZE/N, j * SIZE/N) ;
            r.setSize(sf::Vector2f(SIZE/N, SIZE/N)) ;
            r.setFillColor(sf::Color(rgb.r, rgb.g, rgb.b)) ;
            
            window.draw(r);
        }
        
//        window.display() ;
        
    }
    
}

void store_pixel_data(double X, double Y, double sz) {
    
    double l = X-sz/2 ;
    double r = X+sz/2 ;
    double d = Y-sz/2 ;
    double u = Y+sz/2 ;
    
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
        
            double m=count_iterations((r*i+l*(N-i))/N,(u*j+d*(N-j))/N) ;
            
            double hue = 360 * m / MAX_ITER ;
            int saturation = 100 ;
            int value = 0 ;
            if (m < MAX_ITER) value = 100 ;
            
            pixel_data[i][j] = HSVtoRGB(hue, saturation, value) ;
            
        }
    }
}


// Sets value to textBoxes containing info on X,Y,size
void set_X_Y_size(sf::Text &cordX ,
                  sf::Text &cordY ,
                  sf::Text &sizeS ,
                  double X, double Y, double size) {
    
    
    std::ostringstream streamObj1;
    streamObj1 << std::fixed;
    streamObj1 << std::setprecision(10);
    streamObj1 << X;
    std::string strObj1 = streamObj1.str();
    
    std::ostringstream streamObj2;
    streamObj2 << std::fixed;
    streamObj2 << std::setprecision(10);
    streamObj2 << Y;
    std::string strObj2 = streamObj2.str();
    
    std::ostringstream streamObj3;
    streamObj3 << std::fixed;
    streamObj3 << std::setprecision(10);
    streamObj3 << size;
    std::string strObj3 = streamObj3.str();
    
    cordX.setString("X : " + strObj1) ;
    cordY.setString("Y : " + strObj2) ;
    sizeS.setString("Size : " + strObj3) ;
}


int main() {
    
//    Creating the window
    sf::RenderWindow window = sf::RenderWindow (sf::VideoMode(SIZE + OPTIONS_SIZE, SIZE), "Mandelbrot Zoom") ;
    window.setKeyRepeatEnabled(true) ;
    
    
//    Loading Font Style
    sf::Font monaco ;
    monaco.loadFromFile("Monaco.ttf") ;
    
    
    double X = ORIG_X ;
    double Y = ORIG_Y ;
    double size = ORIG_SZ ;
    
    
//    Setting title of Window
    sf::Text title ;
    title.setFont(monaco) ;
    title.setString("Mandelbrot Zoom") ;
    title.setCharacterSize(65) ;
    title.setStyle(sf::Text::Bold) ;
    title.setPosition({(float)OPTIONS_CENTRE - title.getLocalBounds().width/2, 20}) ;
    title.setFillColor(sf::Color::Black) ;
    
    
//    Coordinates of Centre and Screen Size
    sf::Text cordX ;
    sf::Text cordY ;
    sf::Text sizeS ;
    
    cordX.setFont(monaco) ;
    cordX.setCharacterSize(30) ;
    cordX.setPosition({(float)SIZE + 50, 150}) ;
    cordX.setFillColor(sf::Color::Black) ;
    
    cordY.setFont(monaco) ;
    cordY.setCharacterSize(30) ;
    cordY.setPosition({(float)SIZE + 50, 200}) ;
    cordY.setFillColor(sf::Color::Black) ;
    
    sizeS.setFont(monaco) ;
    sizeS.setCharacterSize(30) ;
    sizeS.setPosition({(float)SIZE + 50, 250}) ;
    sizeS.setFillColor(sf::Color::Black) ;
    
    set_X_Y_size(cordX, cordY, sizeS, X, Y, size) ;

    
    
//    Setting Background
    sf::RectangleShape background ;
    background.setSize(sf::Vector2f(SIZE+OPTIONS_SIZE, SIZE)) ;
    background.setFillColor(sf::Color(235, 235, 235)) ; // Off-white color
    
    
//    Line Between Canvas and Options
    sf::RectangleShape line ;
    line.setPosition(SIZE, 0) ;
    line.setSize(sf::Vector2f(10, SIZE)) ;
    line.setFillColor(sf::Color::Black) ; // Off-white color
    
    
//    History of View Data
    History history ;
    
    
//    Home button
    Button home("Home", {200,60}, 40, sf::Color::White, sf::Color::Black) ;
    home.setFont(monaco) ;
    home.setPosition({2050, 320}) ;
    
//    Undo button
    Button undo("Undo", {200,60}, 40, sf::Color::White, sf::Color::Black) ;
    undo.setFont(monaco) ;
    undo.setPosition({2300, 320}) ;
    
//    to change Zoom In Factor
    Textbox zoomInText(40, sf::Color::Black, false, "Zoom in factor : ", to_string(ZOOM_IN_FACTOR)) ;
    zoomInText.setFont(monaco) ;
    zoomInText.setPosition({2050, 500}) ;
    zoomInText.setLimit(true, 7) ;
    
    Button zoomInBtn("Set", {200,60}, 40, sf::Color::White, sf::Color::Black) ;
    zoomInBtn.setFont(monaco) ;
    zoomInBtn.setPosition({2050, 570}) ;
    
    
//    to change Maximum Iteration
    Textbox maxIterText(40, sf::Color::Black, false, "Max Iterations : ", to_string(MAX_ITER)) ;
    maxIterText.setFont(monaco) ;
    maxIterText.setPosition({2050, 700}) ;
    maxIterText.setLimit(true, 7) ;
    
    Button maxIterBtn("Set", {200,60}, 40, sf::Color::White, sf::Color::Black) ;
    maxIterBtn.setFont(monaco) ;
    maxIterBtn.setPosition({2050, 770}) ;
    
    
//  to change Resolution
    Textbox resolutionTxt(40, sf::Color::Black, false, "Resolution : ", to_string(N)) ;
    resolutionTxt.setFont(monaco) ;
    resolutionTxt.setPosition({2050, 900}) ;
    resolutionTxt.setLimit(true, 7) ;
    
    Button resolutionBtn("Set", {200,60}, 40, sf::Color::White, sf::Color::Black) ;
    resolutionBtn.setFont(monaco) ;
    resolutionBtn.setPosition({2050, 970}) ;
    
    
//    initial data
    store_pixel_data(X, Y, size) ;
    
    
    window.clear() ;
    
    window.draw(background) ;
    window.draw(title) ;
    window.draw(line) ;
    
    zoomInText.drawTo(window) ;
    zoomInBtn.drawTo(window) ;
    
    maxIterBtn.drawTo(window) ;
    maxIterText.drawTo(window) ;
    
    resolutionTxt.drawTo(window) ;
    resolutionBtn.drawTo(window) ;
    
    home.drawTo(window) ;
    undo.drawTo(window) ;
    
    window.draw(cordX) ;
    window.draw(cordY) ;
    window.draw(sizeS) ;
    
    draw_image(window) ;
    
    window.display() ;
    
    
    while(window.isOpen()) {
        sf::Event event ;

        if(window.waitEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            else if (event.type == sf::Event::TextEntered) {
                zoomInText.typedOn(event) ;
                maxIterText.typedOn(event) ;
                resolutionTxt.typedOn(event) ;
            }
            
            else if (event.type == sf::Event::MouseButtonPressed) {
                
                
                double mouseX = event.mouseButton.x ;
                double mouseY = event.mouseButton.y ;
                
                bool redraw = false ;
                
                
                if(!zoomInText.isClicked(mouseX, mouseY)) {
                    if(zoomInText.isSelected) {
                        zoomInText.setSelected(false) ;
                        redraw = true ;
                    }
                }
                
                if(!maxIterText.isClicked(mouseX, mouseY)) {
                    if(maxIterText.isSelected) {
                        maxIterText.setSelected(false) ;
                        redraw = true ;
                    }
                }
                
                if(!resolutionTxt.isClicked(mouseX, mouseY)) {
                    if(resolutionTxt.isSelected) {
                        resolutionTxt.setSelected(false) ;
                        redraw = true ;
                    }
                }
                
//                Canvas
                if(mouseX <= SIZE) {
                    history.enterViewData(X, Y, size) ;
                    
                    X = mouseX/SIZE * size + X - size/2 ;
                    Y = mouseY/SIZE * size + Y - size/2 ;
                    size = size/ZOOM_IN_FACTOR ;
                    
                    set_X_Y_size(cordX, cordY, sizeS, X, Y, size) ;
    
                    store_pixel_data(X, Y, size) ;
                }
                
//                Home button
                else if(home.isClicked(mouseX, mouseY)) {
                    history.clearViewData() ;
                    
                    X = ORIG_X ;
                    Y = ORIG_Y ;
                    size = ORIG_SZ ;
                    
                    set_X_Y_size(cordX, cordY, sizeS, X, Y, size) ;
                    
                    store_pixel_data(X, Y, size) ;
                }
                
//                Undo button
                else if(undo.isClicked(mouseX, mouseY)) {
                    if(!history.viewDataSize()) continue ;
                    
                    View_data view_data = history.getViewData();
                
                    X = view_data.X ;
                    Y = view_data.Y ;
                    size = view_data.size ;
                    
                    set_X_Y_size(cordX, cordY, sizeS, X, Y, size) ;
                    
                    store_pixel_data(X, Y, size) ;
                }
                
//                Zoom In Text
                else if(zoomInText.isClicked(mouseX, mouseY)) {
                    zoomInText.setSelected(true) ;
                }
                
//                Zoom In Button
                else if(zoomInBtn.isClicked(mouseX, mouseY)) {
                    ZOOM_IN_FACTOR = stod(zoomInText.getText()) ;
                }
                
//                Max Iterations Text
                else if(maxIterText.isClicked(mouseX, mouseY)) {
                    maxIterText.setSelected(true) ;
                }
                
//                Max Iterations Button
                else if(maxIterBtn.isClicked(mouseX, mouseY)) {
                    MAX_ITER = stoi(maxIterText.getText()) ;
                    store_pixel_data(X, Y, size) ;
                }
                
//                Resolution Text
                else if(resolutionTxt.isClicked(mouseX, mouseY)) {
                    resolutionTxt.setSelected(true) ;
                }
                
//                Resolution Button
                else if(resolutionBtn.isClicked(mouseX, mouseY)) {
                    N = stoi(resolutionTxt.getText()) ;
                    store_pixel_data(X, Y, size) ;
                }
                
                else {
                    if(!redraw) continue ;
                }
                
                
                
            }
            else if (event.type == sf::Event::KeyPressed) {
                
//                Set the home view
                if(event.key.code == 'h'-'a') {
                    history.clearViewData() ;
                    
                    X = ORIG_X ;
                    Y = ORIG_Y ;
                    size = ORIG_SZ ;
                    
                    set_X_Y_size(cordX, cordY, sizeS, X, Y, size) ;
                    
                    store_pixel_data(X, Y, size) ;
                }
                
                
                else if(event.key.code == 'z'-'a') {
                    
                    if(!history.viewDataSize()) continue ;
                    
                    View_data view_data = history.getViewData();
                
                    X = view_data.X ;
                    Y = view_data.Y ;
                    size = view_data.size ;
                    
                    set_X_Y_size(cordX, cordY, sizeS, X, Y, size) ;
                    
                    store_pixel_data(X, Y, size) ;
                }
            }
            
            else {
                continue ;
            }
            
        }
        
        window.clear() ;
        
        window.draw(background) ;
        window.draw(title) ;
        window.draw(line) ;
        
        zoomInText.drawTo(window) ;
        zoomInBtn.drawTo(window) ;
        
        maxIterBtn.drawTo(window) ;
        maxIterText.drawTo(window) ;
        
        resolutionTxt.drawTo(window) ;
        resolutionBtn.drawTo(window) ;
        
        home.drawTo(window) ;
        undo.drawTo(window) ;
        
        window.draw(cordX) ;
        window.draw(cordY) ;
        window.draw(sizeS) ;
        
        draw_image(window) ;
        
        window.display() ;
        
    }
}
