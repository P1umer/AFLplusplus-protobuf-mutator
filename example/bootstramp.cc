#include <iostream>
#include <fstream>

#include <stddef.h>
#include "example/test.pb.h"
#include "google/protobuf/text_format.h"

using namespace std;
int main(int argc ,char**argv){
    Root proto;
    bool err;
    proto.set_test(123);

    std::string buffer; 
    // proto.SerializeToString(&buffer);
    proto.PrintDebugString();
    err = google::protobuf::TextFormat::PrintToString(proto, &buffer);
    if( ! err ){
        cout << "[+]Error: outputs to a string";
    }
    std::string filename = argv[1]; 
    std::ofstream OutFile(filename); 
    OutFile << buffer;  
    OutFile.close();  

    
    // fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    // std::string s;
    // proto.SerializeToString(&s);
    // cout << s;
    // output<<s;
}
