#include <iostream>
#include <map>

std::map<std::string,std::string> addr_mode={
  {std::string("rel"),std::string("implied")},
  {std::string("imm"),std::string("implied")},
  {std::string("acc"),std::string("implied")},
  {std::string("imp"),std::string("implied")},
  {std::string("zp"),std::string("zero_page")},
  {std::string("abs"),std::string("absolute")},
  {std::string("(zp)"),std::string("indirect_zp")},
  {std::string("(zp,x)"),std::string("indexed_indirect_x_zp")},
  {std::string("zp,x"),std::string("zp_indexed_x")},
  {std::string("abs,y"),std::string("absolute_indexed_y")},
  {std::string("abs,x"),std::string("absolute_indexed_x")},
  {std::string("zp,y"),std::string("zp_indexed_y")},
  {std::string("(zp),y"),std::string("indirect_zp_indexed_y")},
  {std::string("(abs)"),std::string("indirect_absolute")}
};

int main() {
  std::cout << "#include \"instructions.h\"\n";
  std::cout<< "opcodes_t opcodes_map = {\n";
  unsigned int count = 0;
  while(!std::cin.eof()) {
    std::string opcode;
    std::cin>>opcode;
    
    if(std::cin.eof())
      break;
    
    std::string mneumonic;
    std::cin>>mneumonic;
  
    std::string addressing_mode;
    std::cin>>addressing_mode;
  
    unsigned int cycle_count;
    std::cin>>cycle_count;


    std::cout<<"  " << (count++ ? ",{" : " {" ) << " 0x" << opcode <<
      ", bind(print_instruction<" << addr_mode[addressing_mode] << "> , \"" << mneumonic << "\" , std::placeholders::_1) }" << std::endl;

  }
  std::cout<<"};";
  exit(0);
}

