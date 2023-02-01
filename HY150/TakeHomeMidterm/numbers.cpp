#include <iostream>
#include <fstream>

#define FILEPATH "/home/ugrads/class19/csd4569/Classes/hy150/TakeHomeMidterm/regs.txt"

using namespace std;

int isnum(string str){

    for(int i=0;i<str.length();i++){
        if(str.at(i)<'0' || str.at(i)>'9'){
            return 0;
        }
    }
    return 1;
}

int main() {
    int foundf=0;
    string usernum,readnum,readstr;

    ifstream is(FILEPATH, ios::in);

    while(1){

        foundf=0;
        is.seekg(0,ios_base::beg);
        cin >> usernum;
        if(!usernum.compare("0")){
            break;
        }else  if(!isnum(usernum)){
            cout<< "String must consist of a 5-digit number" << endl;
            continue;
        }else if(usernum.length()>5){
            cout<< "Number too long" << endl;
            continue;
        }else if(usernum.length()<5){
            cout<< "Number too short" << endl;
            continue;
        }

        while (!is.eof()){
            is >> readnum;
            is >> readstr;

            if(!usernum.compare(readnum)){
                cout << readstr << endl;
                foundf=1;
                break;
            }
        }

        if(!foundf){
            cout<<"Registry not found"<<endl;
        }
    }

    is.close();

}
