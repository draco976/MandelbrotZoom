//
//  history.h
//  Mandelbrot
//
//  Created by Harshvardhan Agarwal on 19/11/21.
//

#ifndef history_h
#define history_h

#include <stack>

using namespace std ;

struct View_data {
    
    double X ;
    double Y ;
    double size ;
    
    View_data(double X, double Y, double size) {
        this->X = X ;
        this->Y = Y ;
        this->size = size ;
    }
    
};

// The class will store a stack of previous view data
// to implement undo command
class History {
    
    stack<View_data> undo_stack ;
    stack<View_data> redo_stack ;
    
public:
    void enterUndoData(double X, double Y, double size) {
        undo_stack.push(View_data(X, Y, size)) ;
        while(!redo_stack.empty()) {
            redo_stack.pop() ;
        }
    }
    
    int getUndoDataSize() {
        return (int)undo_stack.size() ;
    }
    
    int getRedoDataSize() {
        return (int)redo_stack.size() ;
    }
    
    View_data getUndoData(double X, double Y, double size) {
        View_data view_data = undo_stack.top() ;
        redo_stack.push(View_data(X, Y, size)) ;
        undo_stack.pop() ;
        return view_data ;
    }
    
    View_data getRedoData(double X, double Y, double size) {
        View_data view_data = redo_stack.top() ;
        undo_stack.push(View_data(X, Y, size)) ;
        redo_stack.pop() ;
        return view_data ;
    }
    
    void clearUndoData() {
        while(!undo_stack.empty()) {
            undo_stack.pop() ;
        }
    }
    
} ;

#endif /* history_h */
