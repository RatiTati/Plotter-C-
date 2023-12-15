#ifndef _HISTO_HH_
#define _HISTO_HH_
#include "Drawable.hh"

class Histo : public Drawable{
private:
    double bw; //bar width
    double min, max;
    int fNunderflow = 0;
    int fNoverflow = 0;
public:
    Histo(const char* name, int n, double min, double max);

    void Fill(double x);

    int getfNunderflow()const{return fNunderflow;}

    int getfNoverflow()const{return fNoverflow;}

    void Clear();

    double Integral();

    double GetMean();

    double GetRMS();

    void Draw(bool is_err = false);

    void calcErr();

};

#endif
