//
//  textbox.hpp
//  Mandelbrot
//
//  Created by Harshvardhan Agarwal on 18/11/21.
//

#ifndef textbox_h
#define textbox_h

#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
    bool isSelected = false ;
    
    Textbox() {
        
    }
    
    Textbox(int size, sf::Color color, bool sel, std::string t="", std::string value="") {
        textbox.setCharacterSize(size) ;
        textbox.setFillColor(color) ;
        isSelected = sel ;
        baseStr = t ;
        
        for (int i=0;i<value.size();i++) {
            text << value[i] ;
        }
        
        std::string txt = text.str() ;
        
        if(sel) {
            textbox.setString(baseStr+txt+"_") ;
        }
        else {
            textbox.setString(baseStr+txt) ;
        }
    }
    
    void setFont(sf::Font &font) {
        textbox.setFont(font) ;
    }
    
    void setPosition(sf::Vector2f pos) {
        textbox.setPosition(pos) ;
    }
    
    void setLimit(bool ToF) {
        hasLimit = ToF ;
    }
    
    void setLimit(bool ToF, int lim) {
        hasLimit = ToF ;
        limit = lim ;
    }
    
    void setSelected(bool sel) {
        isSelected = sel ;
        if(!sel) {
            std::string t = text.str() ;
            std::string newT = "" ;
            for (int i=0;i<(int)t.length()-1;i++) {
                newT += t[i] ;
            }
            textbox.setString(baseStr+t) ;
        }
        else {
            std::string t = text.str() ;
            textbox.setString(baseStr+t+"_") ;
        }
    }
    
    std::string getText() {
        return text.str() ;
    }
    
    void drawTo(sf::RenderWindow &window) {
        window.draw(textbox) ;
    }
    
    void typedOn(sf::Event input) {
        if(isSelected) {
            int charTyped = input.text.unicode ;
            if(charTyped < 128) {
                if(hasLimit) {
                    if(text.str().length() <= limit) {
                        inputLogic(charTyped) ;
                    }
                    else if
                        (text.str().length() > limit && charTyped == DELETE_KEY) {
                            deleteLastChar() ;
                    }
                }
                else {
                    inputLogic(charTyped) ;
                }
            }
        }
    }
    
    bool isClicked(float MouseX, float MouseY) {
        
        float txtPosX = textbox.getPosition().x ;
        float txtPosY = textbox.getPosition().y ;
        
        float txtxPosWidth = textbox.getPosition().x + textbox.getLocalBounds().width ;
        float txtyPosHeight = textbox.getPosition().y + textbox.getLocalBounds().height ;
        
        if(MouseX < txtxPosWidth && MouseX > txtPosX &&
           MouseY < txtyPosHeight && MouseY > txtPosY) {
            return true ;
        }
        else return false ;
    }
    
private:
    sf::Text textbox ;
    std::ostringstream text ;
    bool hasLimit = false ;
    int limit ;
    std::string baseStr ;
    
    void inputLogic(int charTyped) {
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped) ;
        }
        else if (charTyped == DELETE_KEY) {
            if(text.str().length() > 0) {
                deleteLastChar() ;
            }
        }
        textbox.setString(baseStr+text.str() + "_") ;
    }
    
    void deleteLastChar() {
        std::string t = text.str() ;
        std::string newT = "" ;
        for (int i=0;i<t.length()-1;i++) {
            newT += t[i] ;
        }
        text.str("") ;
        text << newT ;
        
        textbox.setString(baseStr+text.str()) ;
    }
} ;


#endif /* textbox_h */
