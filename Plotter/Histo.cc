#include <iostream>
#include <cmath>
#include "Histo.hh"
using namespace std;


Histo::Histo(const char* name, int n, double min, double max):Drawable(name){
    DrawOption = " -b ";
    this->min = min;
    this->max = max;
    fData.resize(n);
    double xMidPoints = (max-min)/(n*1.0);
    this->bw = xMidPoints;
    double tempPoint = min+xMidPoints/2;
    for(int i=0; i<n; ++i){
        fData[i].x = tempPoint;
        tempPoint+=xMidPoints;
    }
}

void Histo::Fill(double x){
    if(x > max){
        ++fNoverflow;
    }else if(x < min){
        ++fNunderflow;
    }else{
        int i = (x-min)/bw;
        fData[i].y+=1;
    }
}

void Histo::Clear(){
    for(int i=0; i<fData.size(); ++i){
        fData[i].y = 0;
        fData[i].yErr = 0;
    }
}

double Histo::Integral(){
    int sum=0;
    for(int i=0; i<fData.size(); ++i){
        sum+=fData[i].y;
    }
    return sum;
}

double Histo::GetMean(){
    double sum=0, temp;
    for(int i=0; i<fData.size(); ++i){
        temp = fData[i].x * fData[i].y;
        sum+=temp;
    }
    double mean = sum/Integral();
    return mean;
}

double Histo::GetRMS(){
    double sum=0, temp;
    for(int i=0; i<fData.size(); ++i){
        temp = fData[i].x*fData[i].x * fData[i].y;
        sum+=temp;
    }
    double mean = sum/Integral();
    double sigma = sqrt(mean - GetMean()*GetMean());
    return sigma;
}

void Histo::calcErr(){
    for(int i=0; i<fData.size(); ++i){
        fData[i].yErr = sqrt(fData[i].y);
    }
}

void Histo::Draw(bool is_err){
    if(is_err)
        calcErr();
    Drawable::Draw(is_err);
}
