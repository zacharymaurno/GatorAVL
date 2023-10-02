#include <iostream>
#include <string>
#include <vector>
#include "AVLTree.cpp"
#include <regex>

void parseInput(std::string input, AVLTree &treeL){
    std::string begin = input.substr(0, input.find(" "));
    if (begin == "insert") {
        bool success = false;
        std::string end = input.substr(input.find("\""));

        std::regex regexTest("\"[a-z\v A-Z]+\"");
        if (std::regex_search(end, regexTest)) {
            success = true;
        }

        std::regex regexp("[A-z]+");
        std::string name;
        std::smatch m;
        //std::regex_search(end, m, regexp);
        std::regex_search(end, m, regexp);
        for (auto x: m) {
            name += x;
        }

        std::string idNum;
        std::regex regexpN("[0-9]{8}");
        std::smatch p;
        std::regex regexTestN("\" [0-9]{8}$");
        if (std::regex_search(end, regexTestN) && success) {
            success = true;
        }
        else {
            success = false;
        }

        std::regex_search(end, p, regexpN);
        for (auto x: p) {
            idNum += x;
        }
        if(success){
            if(treeL.checkDuplicates(std::stoi(idNum))){
                success = false;
            }
        }
        if (success == true) {
            int idNum1 = std::stoi(idNum);
            std::cout << "successful" << std::endl;
            treeL.insertStudent(name, idNum1);
        }
        else {
            std::cout << "unsuccessful" << std::endl;
        }
    }
    else if (begin == "search") {
        std::string end = input.substr(input.find(" ") + 1);
        if (std::regex_match(end, std::regex("\"[A-z]+\""))) {
            std::regex regexp("[A-z]+");
            std::string name;
            std::smatch m;
            std::regex_search(end, m, regexp);
            for (auto x: m) {
                name += x;
            }
            treeL.searchName(name);
        }
        else if (std::regex_match(end, std::regex("[0-9]{8}"))) {
            int num = stoi(end);
            treeL.searchID(num);
        }
        else {
            std::cout << "unsuccessful" << std::endl;
            }
    }
    else if (begin == "remove") {
        std::string end = input.substr(input.find(" ") + 1);
        if (std::regex_match(end, std::regex("[0-9]{8}"))) {
            int num = stoi(end);
            treeL.removeID(num);
        }
        else {
            std::cout << "unsuccessful" << std::endl;
        }
    }
    else if (begin == "removeInorder") {
        std::string end = input.substr(input.find(" ") + 1);
        if (std::regex_match(end, std::regex("[0-9]+"))) {
            int num = stoi(end);
            treeL.removeInorder(num);
        }
        else {
            std::cout << "unsuccessful" << std::endl;
        }
    }
    else if(input == "printInorder"){
        treeL.printInorder();
    }
    else if(input == "printPreorder"){
        treeL.printPreorder();
    }
    else if(input == "printPostorder"){
        treeL.printPostorder();
    }
    else if(input == "printLevelCount"){
        treeL.printLevelCount();
    }
    else{
        std::cout << "unsuccessful" << std::endl;
    }
}

int main() {
    AVLTree avlTree;
    int numCommands;
    std::string line, command;
    std::getline(std::cin, line);
    numCommands = stoi(line);
    std::vector<std::string> commands;
    while (numCommands--){
        std::getline(std::cin, command);
        commands.push_back(command);
    }
    for(int i = 0; i < commands.size(); i++){
        parseInput(commands[i], avlTree);
    }
    return 0;
}
