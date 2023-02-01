#include <iostream>
using namespace std;

int main() {
    string str,comp;
    cin>>str;
    
    while(true){ //infinite loop pou kanei break otan diavasei ton xarakthra 'q'
        if(!str.compare(".-")){		//an to input tairiazei me ena egkyro morse code
            cout<<"A";	       		//to programma ektiponei sto output to antistixo xaralthra
        }else if(!str.compare("-...")){
            cout<<"B";
        }else if(!str.compare("-.-.")){
            cout<<"C";
        }else if(!str.compare("-..")){
            cout<<"D";
        }else if(!str.compare(".")){
            cout<<"E";
        }else if(!str.compare("..-.")){
            cout<<"F";
        }else if(!str.compare("--.")){
            cout<<"G";
        }else if(!str.compare("....")){
            cout<<"H";
        }else if(!str.compare("..")){
            cout<<"I";
        }else if(!str.compare(".---")){
            cout<<"J";
        }else if(!str.compare("-.-")){
            cout<<"K";
        }else if(!str.compare(".-..")){
            cout<<"L";
        }else if(!str.compare("--")){
            cout<<"M";
        }else if(!str.compare("-.")){
            cout<<"N";
        }else if(!str.compare("---")){
            cout<<"O";
        }else if(!str.compare(".--.")){
            cout<<"P";
        }else if(!str.compare("--.-")){
            cout<<"Q";
        }else if(!str.compare(".-.")){
            cout<<"R";
        }else if(!str.compare("...")){
            cout<<"S";
        }else if(!str.compare("-")){
            cout<<"T";
        }else if(!str.compare("..-")){
            cout<<"U";
        }else if(!str.compare("...-")){
            cout<<"V";
        }else if(!str.compare(".--")){
            cout<<"W";
        }else if(!str.compare("-..-")){
            cout<<"X";
        }else if(!str.compare("-.--")){
            cout<<"Y";
        }else if(!str.compare("--..")){
            cout<<"Z";
        }else if(!str.compare(".----")){
            cout<<"1";
        }else if(!str.compare("..---")){
            cout<<"2";
        }else if(!str.compare("...--")){
            cout<<"3";
        }else if(!str.compare("....-")){
            cout<<"4";
        }else if(!str.compare(".....")){
            cout<<"5";
        }else if(!str.compare("-....")){
            cout<<"6";
        }else if(!str.compare("--...")){
            cout<<"7";
        }else if(!str.compare("---..")){
            cout<<"8";
        }else if(!str.compare("----.")){
            cout<<"9";
        }else if(!str.compare("-----")){
            cout<<"0";
        }else if(!str.compare("/")){
            cout<<" ";
        }else if(!str.compare("q") || str.empty()) {   //an to input einai 'q' tote spaei to loop kai termatizetai to programma
            break;
        }else{					       //an to input den tairiazei me kapoio apo ta egkura codes, ektiponei minima lathous kai termatizetai 
            cout<<"Invalid morse code, exiting..."<<endl;
            break;
        }
        if (cin.get()=='\n') {
            cout << endl;
        }

        cin>>str; //diavazei to epomeno code gia to epomeno loop
    }
    return 0;
}
