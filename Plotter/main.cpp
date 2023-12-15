#include <iostream>
#include "Graph.hh"
#include "Histo.hh"
#include <fstream>
#include <iomanip>
using namespace std;

int main(){
    /*
    cout<<"Graph:\n";
    Graph myGraph("myG");
    for(int i=0; i<5; ++i){
        myGraph.AddPoint(i, i, 1);
    }
    myGraph.Print();
    myGraph.SetPoint(7, 9, 9, 2);
    myGraph.Draw(1);

    cout<<"Histo:\n";
    Histo myHisto("myH", 9, 2, 20);
    myHisto.Fill(114);
    myHisto.Fi    myGraph.Print();
    myGraph.SetPoint(7, 9, 9, 2);
    myGraph.Draw(1);

    cout<<"Histo:\n";
    Histo myHisto("myH", 9, 2, 20);
    myHisto.Fill(114);
    myHisto.Fill(4.9);
    myHisto.Fill(16.0);
    myHisto.Fill(5.2);
    myHisto.Fill(6.3);
    myHisto.Fill(9.4);
    myHisto.Fill(13.2);
    myHisto.Fill(2.2);
    myHisto.Fill(8.9);
    myHisto.Fill(15);
    myHisto.Fill(5.01);
    myHisto.Draw(1);
    cout<<"Overflow: "<<myHisto.getfNoverflow()<<endl;
    cout<<"Underflow: "<<myHisto.getfNunderflow()<<endl;
    cout<<"Integral: "<<myHisto.Integral()<<endl;
    cout<<"GetMean: "<<myHisto.GetMean()<<endl;
    cout<<"GetRMS: "<<myHisto.GetRMS()<<endl;ll(4.9);
    myHisto.Fill(16.0);
    myHisto.Fill(5.2);
    myHisto.Fill(6.3);
    myHisto.Fill(9.4);
    myHisto.Fill(13.2);
    myHisto.Fill(2.2);
    myHisto.Fill(8.9);
    myHisto.Fill(15);
    myHisto.Fill(5.01);
    myHisto.Draw(1);
    cout<<"Overflow: "<<myHisto.getfNoverflow()<<endl;
    cout<<"Underflow: "<<myHisto.getfNunderflow()<<endl;
    cout<<"Integral: "<<myHisto.Integral()<<endl;
    cout<<"GetMean: "<<myHisto.GetMean()<<endl;
    cout<<"GetRMS: "<<myHisto.GetRMS()<<endl;
    */


    //read the file
    ifstream fin("channel1_old.bin3", ifstream::binary);

    //determine file size
    fin.seekg(0, fin.end);
    long size = fin.tellg() / 24; //3 double in each line (3*8=24), we get number of lines
    fin.seekg(0);
    cout<<"File size is: "<<size<<" bytes."<<endl;

    //initialize Graph
    cout<<"Graph: \n";
    Graph myG("myGraph");

    //initialize Histogram
    cout<<"Histo: \n";
    Histo myH1("from3000", 100, 0, 0.01);
    Histo myH2("flat", 100, 0, 0.01);
    double unixTime; bool k = false;
    for(int i=0; i<size; ++i){
        double x, y, yerr;
        if(k){
            fin.read((char*)&x, 8);
            x-=unixTime;
        }else{
            fin.read((char*)&x, 8);
            unixTime = x;
            x=0;
            k = true;
        }
        cout<<"x = "<<x;
        fin.read((char*)&y, 8);
        cout<<"\ty= "<<y;
        fin.read((char*)&yerr, 8);
        cout<<"\tyErr = "<<yerr<<endl;
        myG.AddPoint(x, y, yerr);
        if(x>3000)
            myH1.Fill(y-30);
        if(x>10000&&x<14000)
            myH2.Fill(y-30);
    }
    myG.Draw(0);
    myH1.Draw(0);
    myH2.Draw(0);

    cout<<"Mean of histo after 3000: "<<myH1.GetMean()<<endl;
    cout<<"RMS of histo after 3000: "<<myH1.GetRMS()<<endl;

    cout<<"Mean of histo on flat interval: "<<myH2.GetMean()<<endl;
    cout<<"RMS of histo on flat interval: "<<myH2.GetRMS()<<endl;
}
