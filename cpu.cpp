#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <functional>

using std::cout; using std::endl; using std::hex;
using std::ifstream; using std::istreambuf_iterator; using std::noskipws;
using std::vector; using std::map; using std::for_each;
using std::string; using std::stringstream;
using std::bind;
// 16-bit registers
unsigned short int pc;
// 8-bit registers
unsigned char sp, a, x, y, status;


typedef void(*PrintFcn)(string, string);

struct opcode_t{
  string       opcode;
  unsigned int length;
  PrintFcn     print_function;
};



void print_immediate(string opcode, string operand);

typedef map<unsigned char, opcode_t> opcodes_t;
opcodes_t opcodes_map = {
  {0x69, {"ADC", 1, print_immediate}}
  // {0x69, {"ADC", "immediate", 1}},
  // // {0x29, {"AND", "immediate", 1}},
  // // {0xc9, {"CMP", "immediate", 1}},
  // // {0xe0, {"CPX", "immediate", 1}},
  // // {0xc0, {"CPY", "immediate", 1}},
  // // {0x49, {"EOR", "immediate", 1}},
  // // {0xa9, {"LDA", "immediate", 1}},
  // // {0xa2, {"LDX", "immediate", 1}},
  // // {0xa0, {"LDY", "immediate", 1}},
  // // {0x09, {"ORA", "immediate", 1}},
  // // {0xe9, {"SBC", "immediate", 1}}
};


void print_opcode(opcode_t, vector<unsigned char>::iterator);
string operand_format(string, unsigned int, vector<unsigned char>::iterator);


int main(int argc, char *argv[]) {
  ifstream rom(argv[1], std::ios::binary);
  noskipws(rom);
  vector<unsigned char> rom_data{istreambuf_iterator<char>{rom}, {}};
  auto rom_data_iter = rom_data.begin();
  while(rom_data_iter != rom_data.end()) {
    opcodes_t::iterator opcode_iter;
    if((opcode_iter=opcodes_map.find(*rom_data_iter))!=opcodes_map.end()) {
      std::stringstream operand;
      operand << std::hex << static_cast<int>(*(rom_data_iter+1));
      opcode_iter->second.print_function(opcode_iter->second.opcode, operand.str());

    }
    ++rom_data_iter;
  }
  
  return 0;
}


void print_immediate(string opcode, string operand) {
  cout << opcode << " #" << operand << endl;
}
