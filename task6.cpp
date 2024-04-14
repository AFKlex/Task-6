
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include <algorithm>

class fileHandling{
    public:
    static std::vector<std::string> readFileWordByWord(std::string filePath){
        std::vector<std::string>  stringsInFile; 
        std::ifstream inputFile(filePath); 
        
        if (!inputFile.is_open()) {  // Check if the file is successfully opened 
            std::cerr << "Error opening the file!" << std::endl;
            return stringsInFile;    
        } 

        std::string currentWord; 
        while (inputFile >> currentWord) {  // Loop all lines in file 
            
            stringsInFile.push_back(standardizeString(currentWord));
            
        } 
    
        // Close the file 
        inputFile.close(); 
        return stringsInFile; 
    }

    private:
    static std::string standardizeString(std::string inputString){

        std::string specialCharacters = "!\"@#$%^&*()-_+={}[]|\\:;'\",.<>/?";

        for(const auto &ch : specialCharacters){

            std::replace( inputString.begin(), inputString.end(), ch, ' ');
            
        }

        for (auto& ch : inputString) { 
        ch = tolower(ch); 
        } 
        inputString.erase(remove(inputString.begin(), inputString.end(), ' '), inputString.end());

        return inputString;
    }


};

class StringFrequencyHashMap{
    private:
    std::map<std::string,unsigned int> hashMap;

    public: 
    void addWord(std::string string){
         if(hashMap.find(string) != hashMap.end()){
                hashMap[string]++; 
         }else{
                hashMap[string] = 1; 
         }
    } 

    public:
    void batchAdd(std::vector<std::string> stringVector){

        for(int i=0; i<stringVector.size();i++){
            addWord(stringVector[i]);
        }

    }

    public:
    void print(){
        for (const auto& pair : hashMap) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }

    }
    public:
    void print_sorted() const {
    std::vector<std::pair<std::string, unsigned int>> sortedPairs(hashMap.begin(), hashMap.end());
    std::sort(sortedPairs.begin(), sortedPairs.end(), 
              [](const auto& a, const auto& b) {
                  return a.second > b.second; // Sort by value in descending order
              });

        for(const auto& pair : sortedPairs) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
            }
    }

   

};

int main(int argc, char *argv[]){
    
    std::string filePath;
    if (argc == 1){
        std::cout << "\nNo Extra Command Line Argument Passed!\nPlease provide the path to the File!" << std::endl;

        return 0;

    }else{
        filePath= argv[1];  // Assainging Path to command line arguement. 
    }

    std::vector<std::string> file = fileHandling::readFileWordByWord(filePath); // Read content of File
    StringFrequencyHashMap map;  // Create Map 
    map.batchAdd(file); // Add all Strings to map
    map.print_sorted();  // print map sorted
    
    return 0; 
}