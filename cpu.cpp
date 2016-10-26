#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>

using std::cout; using std::endl; using std::hex;
using std::ifstream; using std::istreambuf_iterator; using std::noskipws;
using std::vector; using std::map; using std::for_each;
using std::string; using std::stringstream;
// 16-bit registers
unsigned short int pc;
// 8-bit registers
unsigned char sp, a, x, y, status;

struct opcode_t{
  string       opcode;
  string       mode;
  unsigned int length;
};

typedef map<unsigned char, opcode_t> opcodes_t;
opcodes_t opcodes_map = {
  {0x69, {"ADC", "immediate", 1}},
  {0x29, {"AND", "immediate", 1}},
  {0xc9, {"CMP", "immediate", 1}},
  {0xe0, {"CPX", "immediate", 1}},
  {0xc0, {"CPY", "immediate", 1}},
  {0x49, {"EOR", "immediate", 1}},
  {0xa9, {"LDA", "immediate", 1}},
  {0xa2, {"LDX", "immediate", 1}},
  {0xa0, {"LDY", "immediate", 1}},
  {0x09, {"ORA", "immediate", 1}},
  {0xe9, {"SBC", "immediate", 1}}
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
      print_opcode(opcode_iter->second, rom_data_iter);
    }
    ++rom_data_iter;
  }
  
  return 0;
}

void print_opcode(opcode_t opcode, vector<unsigned char>::iterator current_iterator) {
  cout << opcode.opcode + operand_format(opcode.mode, opcode.length, current_iterator) << endl;
}

string operand_format(string mode, unsigned int length, vector<unsigned char>::iterator current_iterator) {
  stringstream operand;
  int operand_counter = 0;
  while(operand_counter < length) {
    operand << std::hex << static_cast<int>(*(current_iterator+1));
    ++operand_counter;
  }
  if(mode == "immediate")
    return " #" + operand.str();
}
