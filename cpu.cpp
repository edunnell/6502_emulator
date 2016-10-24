#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout; using std::endl; using std::string;
using std::ifstream; using std::istreambuf_iterator; using std::noskipws;
using std::vector; using std::for_each;

// 16-bit registers
unsigned short int pc;
// 8-bit registers
unsigned char sp, a, x, y, status;

int main(int argc, char *argv[]) {

  cout << "argv[1]: " << argv[1] << endl;
  ifstream rom(argv[1], std::ios::binary);
  noskipws(rom);
  //  string rom_data{istreambuf_iterator<char>{rom}, {}};
  vector<unsigned char> rom_data{istreambuf_iterator<char>{rom}, {}};
  cout << "rom_data: "<< endl;
  //  cout << rom_data << endl;
  for_each(rom_data.begin(), rom_data.end(), [](uint8_t &byte) { cout << std::hex << byte; });
  cout << "rom_data[0]: " << rom_data[0] << endl;
  
  return 0;
}
