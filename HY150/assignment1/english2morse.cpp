#include <iostream>
using namespace std;

int main() {
    char curchar;
    cin.get(curchar);

    while(curchar!='q'){ //an to epomeno char einai to 'q' termatizetai to programma
        switch (curchar){     //switch pou elenxei to input character
            case 'A':	      //kai an einai egkuros xarathras
                cout<<".- ";  //ton typonei sto output
                break;
            case 'B':
                cout<<"-... ";
                break;
            case 'C':
                cout<<"-.-. ";
                break;
            case 'D':
                cout<<"-.. ";
                break;
            case 'E':
                cout<<". ";
                break;
            case 'F':
                cout<<"..-. ";
                break;
            case 'G':
                cout<<"--. ";
                break;
            case 'H':
                cout<<".... ";
                break;
            case 'I':
                cout<<".. ";
                break;
            case 'J':
                cout<<".--- ";
                break;
            case 'K':
                cout<<"-.- ";
                break;
            case 'L':
                cout<<".-.. ";
                break;
            case 'M':
                cout<<"-- ";
                break;
            case 'N':
                cout<<"-. ";
                break;
            case 'O':
                cout<<"--- ";
                break;
            case 'P':
                cout<<".--. ";
                break;
            case 'Q':
                cout<<"--.- ";
                break;
            case 'R':
                cout<<".-. ";
                break;
            case 'S':
                cout<<"... ";
                break;
            case 'T':
                cout<<"- ";
                break;
            case 'U':
                cout<<"..- ";
                break;
            case 'V':
                cout<<"...- ";
                break;
            case 'W':
                cout<<".-- ";
                break;
            case 'X':
                cout<<"-..- ";
                break;
            case 'Y':
                cout<<"-.--";
                break;
            case 'Z':
                cout<<"--.. ";
                break;
            case '1':
                cout<<".---- ";
                break;
            case '2':
                cout<<"..--- ";
                break;
            case '3':
                cout<<"...-- ";
                break;
            case '4':
                cout<<"....- ";
                break;
            case '5':
                cout<<"..... ";
                break;
            case '6':
                cout<<"-.... ";
                break;
            case '7':
                cout<<"--... ";
                break;
            case '8':
                cout<<"---.. ";
                break;
            case '9':
                cout<<"----. ";
                break;
            case '0':
                cout<<"----- ";
                break;
            case ' ':
                cout<<"/ ";
                break;
            case '\n':
                cout<<"\n";
                break;
            default:					      //ean o xarakthras den anhkei stous egkyrous xarakthres
                cout<<"Invalid Character, exiting..."<<'\n';  //typonei minima lathous kai termatizei
             	return 0;                                     //kai termatizei to programma
                break;
        }
        cin.get(curchar); //diavazei ton xarakthra gia thn epomenh epanalipsi (an yparxei)
    }
    return 0;
}