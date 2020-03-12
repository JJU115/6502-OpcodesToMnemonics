# 6502-OpcodesToMnemonics
Reads files in the iNES format and outputs a listing of opcodes in their MOS 6502 mnemonic form.

<h2>To use</h2>
  Compile with mingw --> g++ 6502OCToMnemonics.cpp -o executable<br>
  Give a .nes file as a command line argument --> executable nes_file
  
An output file with the opcode mnemonics will be generated called nes_file_MNS.txt
