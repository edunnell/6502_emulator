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
using std::bind; using std::function;
// 16-bit registers
unsigned short int pc;
// 8-bit registers
unsigned char sp, a, x, y, status;


typedef void(*PrintFcn)(string, string);
typedef function<void(string)> print_function;
typedef function<string(vector<unsigned char>::iterator&)> get_operand_function;

struct opcode_t{
  get_operand_function operand;
  print_function print;
};

void print_immediate(string opcode, string operand);
string get_operand(unsigned int length, vector<unsigned char>::iterator &it);

typedef map<unsigned char, opcode_t> opcodes_t;
opcodes_t opcodes_map = {
  {0x69, {
      bind(get_operand, 1, std::placeholders::_1),
      bind(print_immediate, "ADC", std::placeholders::_1)
    }
  }
  //  {0x69, {"ADC", 1, print_immediate,parse_word_operand,without_Register}} //working with print_function typedef
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




int main(int argc, char *argv[]) {
  ifstream rom(argv[1], std::ios::binary);
  noskipws(rom);
  vector<unsigned char> rom_data{istreambuf_iterator<char>{rom}, {}};
  auto rom_data_iter = rom_data.begin();
  while(rom_data_iter != rom_data.end()) {
    opcodes_t::iterator opcode_iter;
    if((opcode_iter=opcodes_map.find(*rom_data_iter))!=opcodes_map.end()) {
      string operand = opcode_iter->second.operand(rom_data_iter);
      opcode_iter->second.print(operand);
    }
    ++rom_data_iter;
  }
  
  return 0;
}

void print_immediate(string opcode, string operand) {
  cout << opcode << " #" << operand << endl;
}

string get_operand(unsigned int length, vector<unsigned char>::iterator &it) {
  std::stringstream operand;
  operand << std::hex << static_cast<int>(*(it+1));
  return operand.str();
}
