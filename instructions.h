#include <map>
#include "cpu.h"
#include <string>

typedef std::map<  unsigned char, std::function<void(uchar_vector_t::iterator)>   > opcodes_t;

extern opcodes_t opcodes_map;

template<typename T> void print_instruction(const std::string mneumonic, uchar_vector_t::iterator);

