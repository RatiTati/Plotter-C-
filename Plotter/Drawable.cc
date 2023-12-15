#include <iostream>
#include "Drawable.hh"
#include <fstream>
#include <stdlib.h>

using namespace std;

Drawable::Drawable(const char* name){
    fName = name;
}

Drawable::Drawable(const char* name, int num){
    fName = name;
    fData.resize(num);
}

void Drawable::Print(){
    int size = fData.size();
    for(int i=0; i<size; ++i){
        cout<<"x: "<<fData[i].x<<"\ty: "<<fData[i].y<<"\tyErr: "<<fData[i].yErr;
        cout<<endl;
    }
    cout<<endl;
}

void Drawable::Draw(bool is_err){
    if(fName.size()!=0){
        fileName = fName;
        fileName+="_tmp.dat";
        ofstream fout(fileName);
        if(is_err){
            for(int i=0; i<fData.size(); ++i){
                fout<<fData[i].x<<" "<<fData[i].y<<" "<<fData[i].yErr<<endl;
            }
        }else{
            for(int i=0; i<fData.size(); ++i){
                fout<<fData[i].x<<" "<<fData[i].y<<" "<<endl;
            }
        }
        fout.close();
        if(is_err){
            string command = "kst2 " + fileName + DrawOption + " -x 1 -e 3 -y 2 &";
            system(command.c_str());
        }else{
            string command = "kst2 " + fileName + DrawOption + " -x 1 -y 2 &";
            system(command.c_str());
        }


    }else{
        cout<<"This object is already drawn."<<endl;
    }
}

bool Drawable::S = 1;

Drawable::~Drawable(){
    string k;
    char name[3];
    if(fileName.size()>0){
        if(S == 1){
            cin.getline(name, 3);
            string del = "rm -f ";
            del+=fileName;
            system(del.c_str());
            S = 0;
        }else{
            string del = "rm -f ";
            del+=fileName;
            system(del.c_str());
        }
    }
    k = "pkill -f 'kst2 ";
    k+=fileName+"'";
    system(k.c_str());
}
