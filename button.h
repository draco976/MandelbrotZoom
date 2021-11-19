//
//  button.h
//  Mandelbrot
//
//  Created by Harshvardhan Agarwal on 19/11/21.
//

#ifndef button_h
#define button_h

#include<iostream>
#include<SFML/Graphics.hpp>


class Button {
    
public:
    
    Button() {
        
    }
    
    Button(std::string t, sf::Vector2f size, int charSize , sf::Color bgColor, sf::Color textColor) {
        
        button.setOutlineThickness(5) ;
        button.setOutlineColor(sf::Color::Black) ;
        button.setSize(size) ;
        button.setFillColor(bgColor) ;
        
        text.setString(t) ;
        text.setFillColor(textColor) ;
        text.setCharacterSize(charSize) ;
    }
    
    void setFont(sf::Font &font) {
        text.setFont(font) ;
    }
    
    void setBackColor(sf::Color color) {
        button.setFillColor(color) ;
    }
    
    void setTextColor(sf::Color color) {
        text.setFillColor(color) ;
    }
    
    void setPosition(sf::Vector2f pos) {
        button.setPosition(pos) ;
        
        float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width/2) ;
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height) ;
        text.setPosition(xPos, yPos) ;
    }
    
    void drawTo(sf::RenderWindow &window) {
        window.draw(button) ;
        window.draw(text) ;
    }
    
    bool isClicked(float MouseX, float MouseY) {
        
        float btnPosX = button.getPosition().x ;
        float btnPosY = button.getPosition().y ;
        
        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width ;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height ;
        
        if(MouseX < btnxPosWidth && MouseX > btnPosX &&
           MouseY < btnyPosHeight && MouseY > btnPosY) {
            return true ;
        }
        else return false ;
    }
    
private:
    
    sf::RectangleShape button ;
    sf::Text text ;
};

#endif /* button_h */
