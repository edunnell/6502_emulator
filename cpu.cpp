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


enum operand_t { byte, word };

struct opcode_t{
  string       opcode;
  string       mode;
  operand_t    length;
};

typedef map<unsigned char, opcode_t> opcodes_t;
opcodes_t opcodes_map = {
  {0x69, {"ADC", "immediate", byte}},
  {0x29, {"AND", "immediate", byte}},
  {0xc9, {"CMP", "immediate", byte}},
   {0xe0, {"CPX", "immediate", byte}},
    {0xc0, {"CPY", "immediate", byte}},
     {0x49, {"EOR", "immediate", byte}},
      {0xa9, {"LDA", "immediate", byte}},
       {0xa2, {"LDX", "immediate", byte}},
        {0xa0, {"LDY", "immediate", byte}},
         {0x09, {"ORA", "immediate", byte}},
          {0xe9, {"SBC", "immediate", byte}}
};

// typedef map<unsigned char, string> opcodes_t;
// opcodes_t opcodes_map = {
//   {0x69, "ADC"},
//   {0x29, "AND"},
//   {0xc9, "CMP"},
//   {0xe0, "CPX"},
//   {0xc0, "CPY"},
//   {0x49, "EOR"},
//   {0xa9, "LDA"},
//   {0xa2, "LDX"},
//   {0xa0, "LDY"},
//   {0x09, "ORA"},
//   {0xe9, "SBC"}
// };

string format_immediate(string, vector<unsigned char>::iterator);

int main(int argc, char *argv[]) {
  ifstream rom(argv[1], std::ios::binary);
  noskipws(rom);
  vector<unsigned char> rom_data{istreambuf_iterator<char>{rom}, {}};
  auto rom_data_iter = rom_data.begin();
  while(rom_data_iter != rom_data.end()) {
    opcodes_t::iterator opcode_iter;
    if((opcode_iter=opcodes_map.find(*rom_data_iter))!=opcodes_map.end()) {
      std::stringstream operand;
      // operand << std::hex << static_cast<int>(*(rom_data_iter+1));
      // cout << format_immediate(opcode_iter->second.opcode) + operand.str() << endl; 
      cout << format_immediate(opcode_iter->second, rom_data_iter) << endl;
    }
    ++rom_data_iter;
  }
  
  return 0;
}

string format_immediate(string opcode, vector<unsigned char>::iterator current_iterator) {
  stringstream operand;
  operand << std::hex << static_cast<int>(*(current_iterator+1));
  return opcode + " #" + operand.str();
}
