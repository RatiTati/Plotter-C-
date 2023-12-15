#ifndef _DRAWABLE_HH_
#define _DRAWABLE_HH_

#include <string>
#include <vector>


struct Point {
    double x, y, yErr;
};

class Drawable{
protected:
    std::string fName;
    std::string fileName;
    std::vector <Point> fData;
    static bool S;
    std::string DrawOption;
public:
    Drawable(const char* name);
    Drawable(const char* name, int num);
    void Print();
    virtual void Draw(bool is_err);
    virtual ~Drawable();
};

#endif
