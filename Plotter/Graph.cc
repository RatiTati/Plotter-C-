#include <iostream>
#include "Graph.hh"
#include <algorithm>

using namespace std;

Graph::Graph(const char* name):Drawable(name){}

void Graph::AddPoint(double x, double y, double yErr){
    Point p{x, y, yErr};
    fData.push_back(p);
}

void Graph::SetPoint(int i, double x, double y, double yErr){
    if(i>=0&&i<fData.size()){
        fData[i].x = x;
        fData[i].y = y;
        fData[i].yErr = yErr;
    }else if(i>=fData.size()){
        int k = i - fData.size();
        for(int j=0; j<k-1; ++j){
            AddPoint(0, 0, 0);
        }
        AddPoint(x, y, yErr);
    }
}

void Graph::Draw(bool is_err){
    Drawable::Draw(is_err);
}

void Graph::Sort(){
    std::sort(fData.begin(), fData.end(),
              [](Point a, Point b){return(a.x<b.x);}); //delta function
}

