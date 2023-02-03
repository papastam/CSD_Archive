#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define HOMEPC 10
#define GAMINGPC 11
#define WORKPC 12

#define SUCCESS 1
#define ERROR -1

using namespace std;

enum osen{Windows,Linux,MacOS};

int validityCheck(int ramSlots,int pcieSlots,int cpuCores,int activeRAM,int gbpRAM){
    int ramRange[4] = {2,4,6,8};
    int pcieRange[3] = {0,1,2};
    int cpuCoresRange[5] = {1,2,4,6,8};

    if (find(begin(ramRange), end(ramRange), ramSlots) == end(ramRange)) {
        cout << "Ram Slots should be 2,4,6 or 8 (" << ramSlots << ")" << endl;
        return ERROR;
    }else if(activeRAM>ramSlots){
        cout << "More active ram than available slots (" << activeRAM << ">" << ramSlots << ")" << endl;
        return ERROR;
    }else if(gbpRAM%2!=0 || gbpRAM>=128 || gbpRAM<=2){
        cout << "Ram capacity is not a power of 2 or is out of range(2-128gb) (" <<gbpRAM<< ")" << endl;
        return ERROR;
    }else if(find(begin(pcieRange), end(pcieRange), pcieSlots) == end(pcieRange)){
        cout << "PCIE slots should be 0,1 or 2 (" << pcieSlots << ")" << endl;
        return ERROR;
    }else if(find(begin(cpuCoresRange), end(cpuCoresRange), cpuCores) == end(cpuCoresRange)){
        cout << "CPU cores should be 1,2,4,6 or 8 (" << cpuCores << ")" << endl;
        return ERROR;
    }else{
        return SUCCESS;
    }
}

class PC{

protected:
    string model;
    osen os;
    int ramSlots;
    int pcieSlots;
    int cpuCores;
    int activeRAM;
    int gbpRAM;
    int ssdCapacity;
    int cost;

    int type;

    PC(int _type,string _model, int _os,int _ramSlots,int _pcieSlots,int _cpuCores,int _activeRAM,int _gbpRAM,int _ssdCapacity,int _cost){
        model=_model;
        os = osen(_os);
        ramSlots = _ramSlots;
        pcieSlots = _pcieSlots;
        cpuCores = _cpuCores;
        activeRAM = _activeRAM;
        gbpRAM = _gbpRAM;
        ssdCapacity = _ssdCapacity;
        cost = _cost;

        type= _type;
    }

public:
    string getModel(){return model;}
    int getType(){return type;}
    int getRamSlots(){return ramSlots;}
    int getPCIESlots(){return pcieSlots;}
    int getCpuCores(){return cpuCores;}
    int getSSDCapacity(){return ssdCapacity;}
    int getCost(){return cost;}

    int totalRamCapacity(){return activeRAM*gbpRAM;}

    virtual void printPC() = 0;
    virtual int upgrade(int _cpuCores,int _activeRam,int _gbpRAM) = 0;
    virtual int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu) = 0;
    virtual int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu,int _afterburner) = 0;
    virtual void compare(PC* other,bool reverse) = 0;
    virtual int getGPU()=0;
    virtual int getAfterburner()=0;

};

class HomePc: public PC{

public:
    HomePc(string _model): PC(HOMEPC,_model, MacOS,2,0,2,1,4,256,800){

    }

    void printPC(){
        printf("----HOME PC \"%s\"----\nOS: MacOS\nRAM slots: %d\nPCIE slots: %d\nCPU cores: %d\nActive RAM slots: %d\nRAM stick capacity: %d GB\nSSD capacity: %d GB\nCost: %dE\n\n",model.c_str(),ramSlots,pcieSlots,cpuCores,activeRAM,gbpRAM,ssdCapacity,cost);
    }

    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM){
        cpuCores = _cpuCores;
        activeRAM = _activeRam;
        gbpRAM = _gbpRAM;
        return SUCCESS;
    }

    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu){cout << "wrong upgrade function in homepc";return ERROR;}
    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu,int _afterburner){cout << "wrong upgrade function in homepc";return ERROR;}
    int getGPU(){return ERROR;}
    int getAfterburner(){return ERROR;};

    void compare(PC* other,bool reverse){
        if(reverse){
            printf("CPU %d %c %d\nRAM %d %c %d\nSSD %d %c %d\nCost %d %c %d\n\n",other->getCpuCores(),cpuCores==other->getCpuCores()?'=':(cpuCores<other->getCpuCores()?'>':'<'),cpuCores,other->totalRamCapacity(),totalRamCapacity()==other->totalRamCapacity()?'=':(totalRamCapacity()<other->totalRamCapacity()?'>':'<'),totalRamCapacity(),other->getSSDCapacity(),ssdCapacity==other->getSSDCapacity()?'=':(ssdCapacity<other->getSSDCapacity()?'>':'<'),ssdCapacity,other->getCost(),cost==other->getCost()?'=':(cost<other->getCost()?'>':'<'),cost);
        }else{
            printf("CPU %d %c %d\nRAM %d %c %d\nSSD %d %c %d\nCost %d %c %d\n\n",cpuCores,cpuCores==other->getCpuCores()?'=':(cpuCores>other->getCpuCores()?'>':'<'),other->getCpuCores(),totalRamCapacity(),totalRamCapacity()==other->totalRamCapacity()?'=':(totalRamCapacity()>other->totalRamCapacity()?'>':'<'),other->totalRamCapacity(),ssdCapacity,ssdCapacity==other->getSSDCapacity()?'=':(ssdCapacity>other->getSSDCapacity()?'>':'<'),other->getSSDCapacity(),cost,cost==other->getCost()?'=':(cost>other->getCost()?'>':'<'),other->getCost());
        }
    }

};

class GamingPc: public PC{
protected:
    int gpu;


public:
    GamingPc(string _model): PC(GAMINGPC,_model, Windows,4,2,6,1,8,1024,1300){
        gpu=1;
    }

    void printPC(){
        printf("----GAMING PC \"%s\"----\nOS: Windows\nRAM slots: %d\nPCIE slots: %d\nCPU cores: %d\nActive RAM slots: %d\nRAM stick capacity: %d GB\nSSD capacity: %d GB\nGPU: %d\nCost: %dE\n\n",model.c_str(),ramSlots,pcieSlots,cpuCores,activeRAM,gbpRAM,ssdCapacity,gpu,cost);
    }

    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu){
        cpuCores = _cpuCores;
        activeRAM = _activeRam;
        gbpRAM = _gbpRAM;
        gpu = _gpu;
        return SUCCESS;
    }

    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM){cout << "wrong upgrade function in gamingpc";return ERROR;}
    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu,int _afterburner){cout << "wrong upgrade function in gamingpc";return ERROR;}
    int getGPU(){return gpu;}
    int getAfterburner(){return ERROR;};

    void compare(PC* other,bool reverse){
        if(other->getGPU()==ERROR){other->compare(this,!reverse);}
        else{
            if(reverse){
                printf("CPU %d %c %d\nRAM %d %c %d\nSSD %d %c %d\nCost %d %c %d\nGPU %d %c %d\n\n",other->getCpuCores(),cpuCores==other->getCpuCores()?'=':(cpuCores<other->getCpuCores()?'>':'<'),cpuCores,other->totalRamCapacity(),totalRamCapacity()==other->totalRamCapacity()?'=':(totalRamCapacity()<other->totalRamCapacity()?'>':'<'),totalRamCapacity(),other->getSSDCapacity(),ssdCapacity==other->getSSDCapacity()?'=':(ssdCapacity<other->getSSDCapacity()?'>':'<'),ssdCapacity,other->getCost(),cost==other->getCost()?'=':(cost<other->getCost()?'>':'<'),cost,other->getGPU(),gpu==other->getGPU()?'=':(gpu<other->getGPU()?'>':'<'),gpu);
            }else{
                printf("CPU %d %c %d\nRAM %d %c %d\nSSD %d %c %d\nCost %d %c %d\nGPU %d %c %d\n\n",cpuCores,cpuCores==other->getCpuCores()?'=':(cpuCores>other->getCpuCores()?'>':'<'),other->getCpuCores(),totalRamCapacity(),totalRamCapacity()==other->totalRamCapacity()?'=':(totalRamCapacity()>other->totalRamCapacity()?'>':'<'),other->totalRamCapacity(),ssdCapacity,ssdCapacity==other->getSSDCapacity()?'=':(ssdCapacity>other->getSSDCapacity()?'>':'<'),other->getSSDCapacity(),cost,cost==other->getCost()?'=':(cost>other->getCost()?'>':'<'),other->getCost(),gpu,gpu==other->getGPU()?'=':(gpu>other->getGPU()?'>':'<'),other->getGPU());
            }
        }
    }

};

class WorkPc:public PC{
protected:
    int gpu;
    bool afterburner;

public:
    WorkPc(string _model): PC(WORKPC,_model,Linux,8,1,6,4,16,2048,1600){
        gpu=0;
        afterburner=false;
    }

    void printPC(){
        printf("----WORKSTATION PC \"%s\"----\nOS: Linux\nRAM slots: %d\nPCIE slots: %d\nCPU cores: %d\nActive RAM slots: %d\nRAM stick capacity: %d GB\nSSD capacity: %d GB\nGPU: %d\nAfterburner: %s\nCost: %dE\n\n",model.c_str(),ramSlots,pcieSlots,cpuCores,activeRAM,gbpRAM,ssdCapacity,gpu,afterburner?"Yes":"No",cost);
    }

    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu,int _afterburner){
        cpuCores = _cpuCores;
        activeRAM = _activeRam;
        gbpRAM = _gbpRAM;
        gpu = _gpu;
        if(gpu){afterburner = _afterburner;}
        return SUCCESS;
    }

    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM){cout << "wrong upgrade function in workstationpc";return ERROR;}
    int upgrade(int _cpuCores,int _activeRam,int _gbpRAM,int _gpu){cout << "wrong upgrade function in workstationpc";return ERROR;}
    int getGPU(){return gpu;}
    int getAfterburner(){return afterburner;};

    void compare(PC* other,bool reverse){
        if(other->getAfterburner()==ERROR){other->compare(this,!reverse);}
        else{
            if(reverse){
                printf("CPU %d %c %d\nRAM %d %c %d\nSSD %d %c %d\nCost %d %c %d\nGPU %d %c %d\nAfterburner %d %c %d\n\n",other->getCpuCores(),cpuCores==other->getCpuCores()?'=':(cpuCores<other->getCpuCores()?'>':'<'),cpuCores,other->totalRamCapacity(),totalRamCapacity()==other->totalRamCapacity()?'=':(totalRamCapacity()<other->totalRamCapacity()?'>':'<'),totalRamCapacity(),other->getSSDCapacity(),ssdCapacity==other->getSSDCapacity()?'=':(ssdCapacity<other->getSSDCapacity()?'>':'<'),ssdCapacity,other->getCost(),cost==other->getCost()?'=':(cost<other->getCost()?'>':'<'),cost,other->getGPU(),gpu==other->getGPU()?'=':(gpu<other->getGPU()?'>':'<'),gpu,other->getAfterburner(),afterburner==other->getAfterburner()?'=':(afterburner<other->getAfterburner()?'>':'<'),afterburner);
            }else{
                printf("CPU %d %c %d\nRAM %d %c %d\nSSD %d %c %d\nCost %d %c %d\nGPU %d %c %d\nAfterburner %d %c %d\n\n",cpuCores,cpuCores==other->getCpuCores()?'=':(cpuCores>other->getCpuCores()?'>':'<'),other->getCpuCores(),totalRamCapacity(),totalRamCapacity()==other->totalRamCapacity()?'=':(totalRamCapacity()>other->totalRamCapacity()?'>':'<'),other->totalRamCapacity(),ssdCapacity,ssdCapacity==other->getSSDCapacity()?'=':(ssdCapacity>other->getSSDCapacity()?'>':'<'),other->getSSDCapacity(),cost,cost==other->getCost()?'=':(cost>other->getCost()?'>':'<'),other->getCost(),gpu,gpu==other->getGPU()?'=':(gpu>other->getGPU()?'>':'<'),other->getGPU(),afterburner,afterburner==other->getAfterburner()?'=':(afterburner>other->getAfterburner()?'>':'<'),other->getAfterburner());
            }
        }
    }
};

int main(){
    bool exit =0;
    vector<PC*> pcVec;

    while(!exit){
        string choise,a1,a2,a3,a4,a5,a6;
        cin >> choise;

        if(!choise.compare("new")){
            cin >> a1;
            cin >> a2;
            if(!a1.compare("homepc")){
                pcVec.push_back(new HomePc(a2));
                cout << "Home PC \"" << a2 << "\" was succesfully added!" << endl;

            }else if(!a1.compare("gamingpc")){
                pcVec.push_back(new GamingPc(a2));
                cout << "Gaming PC \"" << a2 << "\" was succesfully added!" << endl;

            }else if(!a1.compare("workstationpc")){
                pcVec.push_back(new WorkPc(a2));
                cout << "Workstation PC \"" << a2 << "\" was succesfully added!" << endl;

            }else{
                cout << "Please enter a valid PC type <homepc/gamingpc/workstationpc>" << endl;

            }
            cout << endl;

        }else if(!choise.compare("upgrade")){
            cin >> a1;
            cin >> a2;
            cin >> a3;
            cin >> a4;
            PC* pcptr;
            bool found = false;

            for(int i=0;i<pcVec.size();i++){
                if(!pcVec[i]->getModel().compare(a1)){
                    pcptr = pcVec[i];
                    found = true;
                }
            }
            if(!found){cout << "PC \"" << a1 <<"\" was not found" << endl << endl;cin.ignore(256);continue;}

            int vcres = validityCheck(pcptr->getRamSlots(),pcptr->getPCIESlots(),stoi(a2),stoi(a3),stoi(a4));
            if(vcres==ERROR){
                cout << "Upgrade wasn't registered" << endl;
                continue;
            }

            if(pcptr->getType()==HOMEPC){
                if(pcptr->upgrade(stoi(a2),stoi(a3),stoi(a4))==ERROR){
                    cout << "Upgrade was unsuccesfull" << endl << endl;
                }

            }else if(pcptr->getType()==GAMINGPC){
                cin >> a5;

                if(pcptr->upgrade(stoi(a2),stoi(a3),stoi(a4),stoi(a5))==ERROR){
                    cout << "Upgrade was unsuccesfull" << endl << endl;
                }


            }else if(pcptr->getType()==WORKPC){
                cin >> a5;
                cin >> a6;

                if(pcptr->upgrade(stoi(a2),stoi(a3),stoi(a4),stoi(a5),stoi(a6))==ERROR){
                    cout << "Upgrade was unsuccesfull" << endl << endl;
                }

            }
            cout << "upgrade of \"" << a1 << "\" succesfull" << endl << endl;


        }else if(!choise.compare("print")){
            cin >> a1;
            int desType;
            bool found=false;

            if(!a1.compare("homepc")){desType=HOMEPC;}
            else if(!a1.compare("gamingpc")){desType=GAMINGPC;}
            else if(!a1.compare("workstationpc")){desType=WORKPC;}
            else{
                cout << "Please enter a valid PC type <homepc/gamingpc/workstationpc>" << endl << endl;
                continue;
            }

            for(int i=0;i<pcVec.size();i++){
                if(pcVec[i]->getType()==desType){
                    found=true;
                    pcVec[i]->printPC();
                }
            }
            if(!found){
                printf("No %s found\n\n",a1.c_str());
            }

        }else if(!choise.compare("delete")){
            cin >> a1;
            bool found = false;


        for(int i=0;i<pcVec.size();i++){
            if(!pcVec[i]->getModel().compare(a1)){
                pcVec.erase(pcVec.begin()+i);
                found = true;
                cout << "PC \"" << a1 << "\" was succesfully removed!" << endl << endl;
            }
        }
        if(!found){cout << "PC \"" << a1 <<"\" was not found" << endl << endl;continue;}


        }else if(!choise.compare("compare")){
            cin >> a1;
            cin >> a2;
            PC *pcptr1,*other;
            bool found = false;

            for(int i=0;i<pcVec.size();i++){
                if(!pcVec[i]->getModel().compare(a1)){
                    pcptr1 = pcVec[i];
                    found = true;
                }
            }
            if(!found){cout << "PC \"" << a1 <<"\" was not found" << endl << endl;continue;}

            found = false;
            for(int i=0;i<pcVec.size();i++){
                if(!pcVec[i]->getModel().compare(a2)){
                    other = pcVec[i];
                    found = true;
                }
            }
            if(!found){cout << "PC \"" << a2 <<"\" was not found" << endl << endl;continue;}

            pcptr1->compare(other,false);

        }else if(!choise.compare("exit")){
            exit=1;
        }else{
            cout << "invalid command, please use the following\nnew <pcType> <uniquePcModel>\nupgrade <pcModel> <cpu_cores> <number_of_ram_sticks> <GB_per_ram> <number_of_GPUs>\ndelete <pcModel>\nprint <pcModel>\ncompare <pcModel1> <pcModel2>\nexit\n\n";
        }
    }
}
