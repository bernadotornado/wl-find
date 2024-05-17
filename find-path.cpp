#include <iostream>


int main(int argc, char* argv[]){
    if(argc != 4){
        std::cerr << "Usage: " << argv[0] << " <map> <start> <destination>" << std::endl;
        return 1;
    }
    std::string map = argv[1];
    std::string start = argv[2];
    std::string destination = argv[3];
    std::cout << "Map: " << map << std::endl;
    std::cout << "Start: " << start << std::endl;
    std::cout << "Destination: " << destination << std::endl;
}








