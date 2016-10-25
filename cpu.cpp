#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using std::cout; using std::endl; using std::hex;
using std::ifstream; using std::istreambuf_iterator; using std::noskipws;
using std::vector; using std::map; using std::for_each;
using std::string;
// 16-bit registers
unsigned short int pc;
// 8-bit registers
unsigned char sp, a, x, y, status;


enum operand_t { byte, word };

struct opcode_t{
  string       opcode;
  operand_t    length;
};

typedef map<unsigned char, opcode_t> opcodes_t;
opcodes_t opcodes_map = {
  {0xa9, {"LDA", byte}} // lda immediate
};

int main(int argc, char *argv[]) {
  ifstream rom(argv[1], std::ios::binary);
  noskipws(rom);
  vector<unsigned char> rom_data{istreambuf_iterator<char>{rom}, {}};
  auto rom_data_iter = rom_data.begin();
  while(rom_data_iter != rom_data.end()) {
    opcodes_t::iterator opcode_iter;
    if((opcode_iter=opcodes_map.find(*rom_data_iter))!=opcodes_map.end()) {
      cout << opcode_iter->second.opcode << " #" << std::hex << static_cast<int>(*(rom_data_iter+1))  << endl;
    }
    ++rom_data_iter;
  }
  
  return 0;
}
