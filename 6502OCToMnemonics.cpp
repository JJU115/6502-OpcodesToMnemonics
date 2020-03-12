#include <iostream>
#include <fstream>
#include <string>
#include "6502Mnemonics.hpp"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "No input file. Quitting...";
        exit(-1);
    }

    std::ifstream In(argv[1], std::ios::binary | std::ios::in);
    if (!In.is_open()) {
        std::cout << "Could not open input file. Quitting...";
        exit(-1);
    }
    
    std::string Name (argv[1]);
    Name.replace(Name.length()-4, 4, "_MNS.txt");
    std::ofstream Out(Name);
    if (!Out.is_open()) {
        std::cout << "Could not open output file. Quitting...";
        exit(-1); 
    }

    char *Header = new char[16];
    char *Buf = new char[3];
    In.read(Header, 16);
    if ((Header[0] == 0x4E) && (Header[1] == 0x45) && (Header[2] == 0x53) && (Header[3] == 0x1A)) {
        //Accept
    } else {
        std::cout << "Input file not in iNES format. Quitting...";
        exit(-1);  
    }

    Out << "PRG ROM Size: " << int(Header[4])*16 << " KB\n";
    Out << "CHR ROM Size: " << int(Header[5])*8 << " KB\n";
    Out << "iNES Mapper #: " << ((Header[6] >> 4) | (Header[7] & 0xF0)) << '\n' << '\n';
    delete Header;

    if ((Header[6] & 0x04) != 0)
        In.seekg(512); 
    
    while (!In.eof()) {
        In.read(Buf, 1);
        Out << OPCODES[Buf[0]] << " ";
        Out << '\n';
    }
    
    In.close();
    Out.close();
    return 0;
}