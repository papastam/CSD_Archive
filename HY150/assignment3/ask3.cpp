#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

struct Vehicle{
    string licensePlate,vehicleType;
    int estFixDays;
    vector<string> damageType;

    Vehicle(string _licensePlate,string _vehicleType,vector<string> _damageType,int _estFixDays){
        licensePlate = _licensePlate;
        vehicleType = _vehicleType;
        estFixDays = _estFixDays;
        for (int i=0; i<_damageType.size(); i++) {
            damageType.push_back(_damageType[i]);
        }
    }

    string toString(){
        string retstr=licensePlate;
        retstr.append(",");
        retstr.append(vehicleType);
        retstr.append(",");
        retstr.append(damageType[0]);
        for (int i=1; i<damageType.size(); i++) {
            retstr.append("-");
            retstr.append(damageType[i]);
        }
        retstr.append(",");
        retstr.append(to_string(estFixDays));

        return retstr;
    }
};

struct DailyCustomers{
    vector<Vehicle> vehicleList;
    string date;

    string toString(){
        string ret = "";
        ret.append(date);
        ret.append("\n");
        for(int i=0;i<vehicleList.size();i++){
            ret.append(vehicleList[i].toString().c_str());
            ret.append((i==vehicleList.size())?"":"\n");
        }
        return ret;
    }
};

int validCheck(vector<Vehicle> vehicleList,string *array){
    if(array[1].compare("Motorcycle") && array[1].compare("Car") && array[1].compare("Van") && array[1].compare("Semitruck")){
        cout << "Vehicle with license plate " << array[0] << " is not a supported vehicle type (" << array[1] << ")\n";
        return 0;
    }
    if(stoi(array[3])<0){cout<<"Vehicle "<< array[0] << " estimated days is a negative number\n";return 0;}
    else if(stoi(array[3])>12){cout << "Vehicle with license plate "<<array[0]<<" needs many days. It can’t be fixe\n";return 0;}

    for(int i=0;i<vehicleList.size();i++){
        if(!vehicleList[i].licensePlate.compare(array[0])){
            cout << "Vehicle with licence plate " << array[0] << " is already registered\n";
            return 0;
        }
    }

    return 1;
}

int validDamageTypeCheck(string lp,string damageType){
    if(damageType.compare("Engine") && damageType.compare("Brakes") && damageType.compare("Transmission") && damageType.compare("Gearbox") && damageType.compare("Electrical")){
        cout << "Vehicle with license plate " << lp << " damage is not supported (" << damageType << ")\n";
        return 0;
    }
    return 1;
}

int split(string str,string *targetarray){ //This split function is exclusively for spliting lines with ',' as a delimiter
    for(int i=0;i<4;i++){
        if((str.find(',')==-1)  && (i!=3)){cout << "Please Insert 4 arguemets separated with a semicolumn <LicencePlates,VehicleType,DamageType,EstimatedFixDays>\n";return 0;}
        targetarray[i]=str.substr(0,str.find(','));
        str=str.substr(str.find(',')+1);
    }
    return 1;
}

int split(string str,string *targetarray,string lp){ //This split function is exclusively for spliting lines with '-' as a delimiter
    for(int i=0;i<5;i++){
        if(str.find('-')==-1){
            if(!validDamageTypeCheck(lp,str)){
                return 0;
            }
            targetarray[i]=str;
            break;
        }

        targetarray[i]=str.substr(0,str.find('-'));
        str=str.substr(str.find('-')+1);

        if(!validDamageTypeCheck(lp,targetarray[i])){
            return 0;
        }
    }
    return 1;
}

int main(int agrs,char *argv[]) {
    bool exit = false, found = false;
    string funct,argum,argum2,line,splitedline[4];
    int count,pdtarr[4];
    DailyCustomers dc;

    if(agrs!=2){
        cout << "Invalid syntax!\nUse \"a.out <FILEPATH>\"" << endl;
        return 0;
    }
    ifstream ist(argv[1]);
    if (!ist){printf("can\'t open input file (%s)\n", argv[1]);return 0;}

    getline(ist,line);
    dc.date=line;

    while(getline(ist,line)){
        string arrDT[5];
        vector<string> splitedDT;

        if(!split(line,splitedline)){continue;}

        if(split(splitedline[2],arrDT,splitedline[0])) {
            for (int i = 0; i < 5; i++) {
                if (arrDT[i].compare("")) {
                    splitedDT.push_back(arrDT[i]);
                } else {
                    break;
                }
            }
        }

        dc.vehicleList.push_back(Vehicle(splitedline[0],splitedline[1],splitedDT,stoi(splitedline[3])));
    }
    ist.close();

    while(!exit){
//        cout << '>';
        cin >> funct;
        if(!funct.compare("q")){

            ofstream ofs(argv[1]);
            if (!ofs){printf("can’t open input file (%s)", argv[1]);return 0;}

            ofs.write(dc.toString().c_str(),dc.toString().length());

            ofs.close();

            exit=true;
        }else if (!funct.compare("a")){
            vector<string> splitedDT;
            string arrDT[5];

            cin >> argum;
            if(!split(argum,splitedline)){continue;};

            if(split(splitedline[2],arrDT,splitedline[0])) {
                for (int i = 0; i < 5; i++) {
                    if (arrDT[i].compare("")) {
                        splitedDT.push_back(arrDT[i]);
                    } else {
                        break;
                    }
                }

                if(validCheck(dc.vehicleList,splitedline)){
                    dc.vehicleList.push_back(Vehicle(splitedline[0],splitedline[1],splitedDT,stoi(splitedline[3])));
                }
            }



        }else if (!funct.compare("d")){
            found = false;
            cin >> argum;
            for(int i=0;i<dc.vehicleList.size();i++){
                if(!dc.vehicleList[i].licensePlate.compare(argum)){
                    dc.vehicleList.erase(dc.vehicleList.begin()+i);
                    found = true;
                }
            }
            if(!found){
                cout << "Vehicle with licence plates " << argum << " wasn't found\n";
            }else{
                cout << "Vehicle removed\n";
            }
        }else if (!funct.compare("pd")){
            count = 0;
            for(int i=0;i<dc.vehicleList.size();i++){
                count+= dc.vehicleList[i].estFixDays;
            }

            cout << count << " days in total\n";
        }else if (!funct.compare("pv")){
            found = false;
            count =0;
            cin >> argum;

            for(int i=0;i<dc.vehicleList.size();i++){
                if(!dc.vehicleList[i].vehicleType.compare(argum)){
                    count +=1;
                    found=true;
                }
            }
            if(!found){cout << "There are no " << argum << " vehicles registered\n";}
            else{cout << count << " " << argum << ((count==1)? "\n": "s\n");}
        }else if(!funct.compare("pdt")){
            found = false;
            cin >> argum;
            for(int i=0;i<4;i++){pdtarr[i]=0;}

            for(int i=0;i<dc.vehicleList.size();i++){
                for(int j=0;j<dc.vehicleList[i].damageType.size();j++){
                    if (!dc.vehicleList[i].damageType[j].compare(argum)) {
                        if (!dc.vehicleList[i].vehicleType.compare("Motorcycle")) { pdtarr[0] += 1; }
                        else if (!dc.vehicleList[i].vehicleType.compare("Car")) { pdtarr[1] += 1; }
                        else if (!dc.vehicleList[i].vehicleType.compare("Van")) { pdtarr[2] += 1; }
                        else if (!dc.vehicleList[i].vehicleType.compare("Semitruck")) { pdtarr[3] += 1; }
                        found = true;
                    }
                }
            }
            if(!found){cout << "There are no vehicles with " << argum << " damage\n";}
            else{cout << argum << " damage in: " << pdtarr[0] <<  " Motorcycle, "<< pdtarr[1] <<" Car, " << pdtarr[2] << " Vans, "<< pdtarr[3] << " Semitrucks\n";}
        }else if(!funct.compare("rd")){
            found=false;
            cin >> argum;
            cin >> argum2;

            for(int i=0;i<dc.vehicleList.size();i++){
                if(!dc.vehicleList[i].licensePlate.compare(argum)){
                    found=true;
                    for(int j=0;j<dc.vehicleList[i].damageType.size();j++){
                        if(!dc.vehicleList[i].damageType[j].compare(argum2)){
                            dc.vehicleList[i].damageType.erase(dc.vehicleList[i].damageType.begin()+j);
                            break;
                        }
                    }

                    if(dc.vehicleList[i].damageType.size()>0) {
                        for (int j = 0; j < dc.vehicleList[i].damageType.size(); j++) {
                            cout << dc.vehicleList[i].damageType[j]
                                 << ((j == dc.vehicleList[i].damageType.size() - 1) ? "\n" : ",");
                        }
                    }else{
                        cout << "Fixed\n";
                        dc.vehicleList.erase(dc.vehicleList.begin()+i);
                    }
                    break;
                }
            }
            if(!found){cout << "Vehicle " << argum << " was not found" << endl;}

        }else{
            cout << "Invalid command!\n---Command List---\n>a <Licence Plates,Vehicle Type,Damage Type,Estimated Fix Days> (Add vehicle)\n>d <Licence Plates> (Delete vehicle)\n>pd (Print total fix days)\n>pvt <Vehicle Type> (Print all cars with the same vehicle type)\n>pdt <Damage Type> (Print all cars with the same damage type)\n>rd <Licence Plates> <Damage Type> {Remove damage type)\n>q (Save and quit)\n";
        }


    }

    return 0;
}
