#include <iostream>
#include "ComputedChaining.h"

using std::cout;
using std::endl;

void print_table(ComputedChaining & tbl){

    for(int i = 0; i < tbl.data_vec.size(); i++){
        cout << i << ":  " << tbl.data_vec[i].data << "  " << tbl.data_vec[i].link;
        
        if(tbl.data_vec[i].data != -1){
            cout <<"\t P(" << tbl.data_vec[i].data <<  ")    " << tbl.find_num_probes(tbl.data_vec[i].data);
        }
        
        cout << endl;
         
    }

}

int main() {
    // Manually insert values
    ComputedChaining tbl(7);
    tbl.insert(19);
    tbl.insert(90);
    //tbl.insert(4);
    tbl.insert(55);
    //tbl.insert(2);
    tbl.insert(11);
    tbl.insert(76);
    tbl.insert(65);
    tbl.insert(30);

    cout << endl << "---Table---" << endl;
    print_table(tbl);

    return 0;
}
