#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char *argv[]) {
    if(argc==1){cout << "Wrong input format!\nUse: .\\a.out -f <file.txt> <word>, or .\\a.out -p <file.txt> <encoded/decoded>\n";return 0;}

    int index = 1;
    bool f_exists=false;

    while (index < argc){
        string funct(argv[index]);
        if (!(funct.compare("-f"))) {
            if (argc-index >= 3) {
                string str(argv[index + 2]);
                string ret;

                auto itter = str.cbegin();
                while (itter < str.cend()) {
                    if (::tolower(int(*itter)) < 100) {
                        ret.append("0");
                    }
                    ret.append(to_string(int(::tolower(*itter))));
                    itter += 1;
                }

                string line;
                ifstream dupsfile(argv[index + 1]);
                while (getline(dupsfile, line)) {
                    if (!line.compare(ret)) {
                        cout << "The word \"" << str << "\" is already in the encoded file!\n";
                        f_exists = true;
                    }
                }

                if (f_exists) {
                    f_exists = false;
                } else {
                    ofstream fileout(argv[index + 1], ios_base::app);
                    fileout << ret << endl;
                    fileout.close();
                    cout<<"Added \""<<str<<"\" to the encoded file.\n";
                }

                index += 3;
            }else{
                cout << "Wrong input format!\nUse: .\\a.out -f <file.txt> <word>\n";

            }
            index+=3;
        } else if (!(funct.compare("-p"))){
            if (argc-index >= 3 ) {
                string mode(argv[index+2]);
                if(!mode.compare("encoded")){
                    string line;
                    ifstream ifile(argv[index + 1]);
                    while (getline(ifile, line)) {
                        cout << line << endl;
                    }
                }else if(!mode.compare("decoded")){
                    string line;
                    ifstream ifile(argv[index + 1]);
                    while (getline(ifile, line)) {
                        for(int i=0;i<line.length();i+=3){
                            char c='\0'+stoi(line.substr(i,3));
                            cout<< c;
                        }
                        cout << endl;
                    }
                }else{
                    cout << "Wrong input format!\nUse: .\\a.out -p <file.txt> <encoded/decoded>\n";
                }
            }else{
                cout << "Wrong input format!\nUse: .\\a.out -p <file.txt> <encoded/decoded>\n";
            }
            index+=3;
        }
    }

    return 0;
}
