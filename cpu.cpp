#include "cpu.h"
#include "instructions.h"
#include <iomanip>

// 16-bit registers
unsigned short int pc;
// 8-bit registers
unsigned char sp, a, x, y, status;

template<> void print_instruction<implied>(const std::string mneumonic, uchar_vector_t::iterator i)
{
  std::cout << mneumonic << std::endl;
};

template<> void print_instruction<zero_page>(const std::string mneumonic, uchar_vector_t::iterator i)
{
  // heh, this is a bit of a problem, we need to get the new incremented iterator back
  // I suppose that could be a return of this function?
  std::cout << mneumonic << " #$" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)*i << std::endl;
  
};
template<> void print_instruction<zp_indexed_x>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};
template<> void print_instruction<zp_indexed_y>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};
template<> void print_instruction<indirect_zp_indexed_y>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};

template<> void print_instruction<absolute>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};
template<> void print_instruction<absolute_indexed_y>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};
template<> void print_instruction<absolute_indexed_x>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};

template<> void print_instruction<indirect_zp>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};
template<> void print_instruction<indexed_indirect_x_zp>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};
template<> void print_instruction<indirect_absolute>(const std::string mneumonic, uchar_vector_t::iterator i)
{
};

int main(int argc, char *argv[]) {
  
  uchar_vector_t test_data;
  //  test_data.push_back(0x0);
  test_data.push_back(0x65);
  test_data.push_back(0xa);
  auto iter = test_data.begin();
  opcodes_map[*iter++](iter);

  exit(0);
  
  ifstream rom(argv[1], std::ios::binary);
  noskipws(rom);
  vector<unsigned char> rom_data{istreambuf_iterator<char>{rom}, {}};
  auto rom_data_iter = rom_data.begin();
  while(rom_data_iter != rom_data.end()) {

    opcodes_t::iterator opcode_iter;
    if((opcode_iter=opcodes_map.find(*rom_data_iter))!=opcodes_map.end()) {
      //      string operand = opcode_iter->second.operand(rom_data_iter);
      //opcode_iter->second.print(operand);
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
