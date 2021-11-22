//
//  dynamic2DArray.h
//  Mandelbrot
//
//  Created by Harshvardhan Agarwal on 19/11/21.
//

#ifndef dynamic2DArray_h
#define dynamic2DArray_h

#include "color.h"

class Dynamic2DArray {
    
private:
    RGB** array ;
    int size ;
    
public:
    Dynamic2DArray() {
        array = new RGB*[1000] ;
        size = 1000 ;
    }
    
    Dynamic2DArray(const int size) {
        array = new RGB*[size] ;
        for(int i=0;i<size;i++) {
            array[i] = new RGB[size] ;
        }
        
        this->size = size ;
    }
    
    void changeSize(int size) {
        delete array ;
        array = new RGB*[size] ;
        for(int i=0;i<size;i++) {
            array[i] = new RGB[size] ;
        }
        
        this->size = size ;
    }
    
    void enterData(int i, int j, RGB data) {
        array[i][j] = data ;
    }
    
    RGB getData(int i, int j) {
        return array[i][j] ;
    }
    
} ;


#endif /* dynamic2DArray_h */
