#include "ComputedChaining.h"
using namespace std;

ComputedChaining::ComputedChaining(int table_size){
        for (int i = 0; i < table_size; ++i) {
            data_vec.push_back(entry());
        }
}
 int ComputedChaining::hash(int key) {
        return key % data_vec.size();
}
int ComputedChaining::hash2(int key){
        int step=(key/data_vec.size())%data_vec.size();
        if(step==0)step=1;
        return step;
}

void ComputedChaining::insert(int key){
        int index=hash(key);
        
        if(data_vec[index].data != -1){//collision
                if(isThisYourHome(data_vec[index].data)){//Q1: Add to chain
                        //YOUR CODE
                    //LİNK DOLU İSE
                    int link_point = data_vec[index].link;
                    
                    if(link_point != -1){
                        int numForInc = data_vec[(link_point*(hash2(data_vec[index].data))+key)%7].data;
                        int incr = hash2(numForInc);
                        //YENİ YERE YOLLAYACAĞIZ
                        data_vec[find_index(numForInc)].link=1;
                        int newIndex = (find_index(numForInc) + hash2(numForInc))%7; 
                        
                       
                        while (data_vec[newIndex].data != -1) {
                            
                            newIndex = (newIndex + incr) % 7;
                            data_vec[find_index(numForInc)].link++;
                        }
                        data_vec[newIndex].data = key;
                        data_vec[newIndex].link = -1;
                    }else{//LİNK BOŞ İSE

                        int numForInc = data_vec[index].data;
                        int incr = hash2(numForInc);
                        //YENİ YERE YOLLAYACAĞIZ
                        
                        data_vec[find_index(numForInc)].link=1;
                        int newIndex = hash(key + hash2(numForInc));
                        
                       
                        while (data_vec[newIndex].data != -1) {
                            
                            newIndex = (newIndex + incr) % 7;
                            data_vec[find_index(numForInc)].link++;
                        }
                        data_vec[newIndex].data = key;
                        data_vec[newIndex].link = -1;


                    }

                }else{
                //YOUR CODE
                //collision move foreigners
                        //store the key that will be moved(moved_key)
                        //find the chain of the moved_key
                        //find the index of moved_key in the chain
                        //store the previous index of the moved_key to change the link of the entry
                        //store the keys after moved_key in the chain
                        //assign -1 to indexes of data_vec where moved_key and remaining -1
                        //insert new key to its original address
                        //recursively insert remaining of the chain

                    int moved_key = data_vec[hash(key)].data;
                    
                    vector<int> chain = find_chain(moved_key);
                    
                    int moved_key_index = find_index(moved_key);
                    
                    int prev_index = find_index(chain.size()-2);
                    data_vec[prev_index].link = -1;
                    
    
                    vector<int> remaining_keys;
                    for (size_t i = 0; i < chain.size(); ++i) {
                        remaining_keys.push_back(data_vec[chain[i]].data);
                        data_vec[chain[i]].data = -1; // Set the index to -1
                        data_vec[chain[i]].link = -1; // Reset the link
                    }
 
                    data_vec[moved_key_index].data = -1;
                    data_vec[moved_key_index].link = -1;

                    insert(key);
                    
                    for (size_t i = 0; i < remaining_keys.size(); ++i) {
                        insert(remaining_keys[i]);
                    }
                    
                    
                        
                }
        }else{//direct insertion
              data_vec[index].data = key;
              data_vec[index].link= -1;
        }
}

int ComputedChaining::find_index(int key){//find the index of
        int idx=hash(key);
        int inc=hash2(key);
                if(data_vec[idx].data==key)
                        return idx;
                else{
                        while(data_vec[idx].data != -1){
                                if(data_vec[idx].data != key){
                                        inc=hash2(data_vec[idx].data);
                                        idx=(idx+data_vec[idx].link*inc)%data_vec.size();
                                }else return idx;
                
                }
                }
        return -1;
}
bool ComputedChaining::isThisYourHome(int key){//If returns true if the hash of the key is same with the index of data_vec

    if(find_index(key) == hash(key)){
        return true;
    } else return false;
}

int ComputedChaining::first_of_my_chain(int key) {
        return data_vec[hash(key)].data;
}

int ComputedChaining::find_num_probes(int key) {
    int index = hash(key);
    int inc = hash2(key);
    int probes = 1; 

    while (data_vec[index].data != -1) {
        if (data_vec[index].data != key) {
            inc = hash2(data_vec[index].data);
            index = (index + data_vec[index].link * inc) % data_vec.size();
            probes++;
        } else {
            break;
        }
    }

    return probes;
}



vector<int> ComputedChaining::find_chain(int key){ //gives you chain whose member is the key
        vector<int> chain;
        int index=hash(key);
        int inc;//1
        while(data_vec[index].data != -1){
                chain.push_back(index);
                if(data_vec[index].link != -1){
                        inc=hash2(data_vec[index].data);//2
                        index=(index+data_vec[index].link*inc)%data_vec.size();

        }else
                        break;
        }
        return chain;
}
