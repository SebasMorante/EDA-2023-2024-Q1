#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef pair<string, string> Pair;

int main(){
    int n;
    while (cin >> n){
        string per, pro;
        map<string,string> piaut;
        for (int i = 0; i < n; ++i){
            cin >> per >> pro;
            piaut[pro] = per;
        }
        int m;
        string vot;
        map <Pair, string> re;
        cin >> m;
        for (int j = 0; j < m; ++j){
            cin >> per >> vot >> pro;
            Pair aux = {pro, per};
            re[aux] = vot;
        }

        int conts = 0;
        int contn = 0;
        auto it = re.begin();

        while (it != re.end()){
            if (it != re.begin()){
                auto itant = it;
                itant = --itant;

                if (it->first.first != itant->first.first){
                    if (conts > contn) cout << itant->first.first << ", de " << piaut[itant->first.first] << ", que ha guanyat " << conts << "-" << contn << endl;
                    conts = 0;
                    contn = 0;
                }
            }
            if (it->second == "SI") ++conts;
            else ++contn;
            ++it;
        }
        it = --it;
        if (conts > contn) cout << it->first.first << ", de " << piaut[it->first.first] << ", que ha guanyat " << conts << "-" << contn << endl;
        cout << string(10,'-') << endl;
    }
}