//
//  color.h
//  Mandelbrot
//
//  Created by Harshvardhan Agarwal on 19/11/21.
//

#ifndef color_h
#define color_h

class RGB {
public:
    
    double r ;
    double g ;
    double b ;
    
    RGB () {
        r = g = b = 0 ;
    }
    
    RGB (double r, double g, double b) {
        this->r = r ;
        this->g = g ;
        this->b = b ;
    }
};


struct RGB HSVtoRGB(double H, double S,double V){
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        std::cout<<"The given HSV values are not in valid range"<<std::endl;
        return RGB(0,0,0);
    }
    double s = S/100;
    double v = V/100;
    double C = s*v;
    double X = C*(1-abs(fmod(H/60.0, 2)-1));
    double m = v-C;
    double r,g,b;
    if(H >= 0 && H < 60){
        r = C;g = X;b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X;g = C;b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0;g = C;b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0;g = X;b = C;
    }
    else if(H >= 240 && H < 300){
        r = X;g = 0;b = C;
    }
    else{
        r = C;g = 0;b = X;
    }
    double R = (r+m)*255;
    double G = (g+m)*255;
    double B = (b+m)*255;
    
    return RGB(R,G,B) ;
}


#endif /* color_h */
