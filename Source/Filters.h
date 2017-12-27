//
//  Filters.h
//
//  Created by Chris Whitfill on 5/3/17.
//

#ifndef Filters_h
#define Filters_h

class Filter
/*
    Based off of Urs Heckmann's ZDF analog modeled filters.
    Instead of using the bilinear transform, they model a
    capacitor as a conductance and a current source.
    If trapazoidally integrated, the end result is functionally
    equivalent to the bilinear transform.
 
    See here for more:
    https://urs.silvrback.com/analogue-modeling
*/
{
public:
    double output;
    double s;
    double g;
    double G;
    
    void init()
    {
        g = G = output = s = 0;
    }
    
    void setParams(float cutoffHz,  float sampleRate)
    /* Calculate parameters with prewarping */
    {
        g = std::tan(double_Pi*cutoffHz/sampleRate);
        G = 1 / (1 + g);
    }
    
    void updateState()
    /* Trapezoidally integrate. */
    {
        s = 2 * output - s;
    }
    
    double linearLowPass (double input)
    {
        
        output = (g * input + s) * G;
        updateState();
        return output;
    }
    
    double linearHighPass (double input)
    /* 
        Does same calculation as low pass, and then uses KVL
        to determine "voltage" across "resistor."
    */
    {
        output = (g * input + s) * G;
        updateState();
        return input - output;
    }
    
};

typedef std::vector<Filter> FilterBank;

#endif /* Filters_h */
