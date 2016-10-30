#pragma once
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

typedef std::vector<unsigned char> uchar_vector_t;
typedef void(*PrintFcn)(string, string);
typedef function<void(string)> print_function;
typedef function<string(vector<unsigned char>::iterator&)> get_operand_function;

class implied{};
class zero_page{};
class absolute{};
class indirect_zp{};
class indexed_indirect_x_zp{};
class zp_indexed_x{};
class absolute_indexed_y{};
class absolute_indexed_x{};
class zp_indexed_y{};
class indirect_zp_indexed_y{};
class indirect_absolute{};
