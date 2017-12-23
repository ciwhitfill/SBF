/*
Filters.h
*/

#ifndef Filters_h
#define Filters_h

class HighPassFilter
// A first order high pass filter
{
    double output, state, g, G;
    
    void init()
    {
        output, state, g, G = 0;
    }
    
    public:

    void setParameters(float cutoffHz,  float sampleRate)
    {
    }

};

#endif /* Filters_h */
