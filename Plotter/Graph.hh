#ifndef _GRAPH_HH_
#define _GRAPH_HH_

#include "Drawable.hh"

class Graph : public Drawable{
public:
    Graph(const char* name);
    void AddPoint(double x, double y, double yErr=0);
    void SetPoint(int i, double x, double y, double yErr=0);
    void Draw(bool is_err = false);

    void Sort();
};

#endif
