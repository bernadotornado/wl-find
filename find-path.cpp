#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[]){
    if(argc != 4){
        std::cerr << "Usage: " << argv[0] << " <map> <start> <destination>" << std::endl;
        return 1;
    }
    std::string map_path = argv[1];
    std::string start = argv[2];
    std::string destination = argv[3];
    std::cout << "Map: " << map_path << std::endl;
    std::cout << "Start: " << start << std::endl;
    std::cout << "Destination: " << destination << std::endl;

    std::ifstream map_file(map_path);
    if(!map_file){
        std::cerr << "Error: cannot open file '" << map_path << "'" << std::endl;
        return 1;
    }
    std::string line;
    if (map_file.is_open()){
        while (std::getline(map_file, line))
        {
            std::cout << line << std::endl;
        }
        map_file.close();
        
    }



    return 0;
}








