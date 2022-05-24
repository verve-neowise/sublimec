#include <iostream>
#include <fstream>
#include <string>

using namespace std;

inline bool exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

string readFile(char *file_name)
{
  std::ifstream t(file_name);
  string str;

  t.seekg(0, std::ios::end);
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(t)),
             std::istreambuf_iterator<char>());

  return str;
}

void writeFile(string file_name, string &content) {
  string out_name = file_name.substr(0, file_name.length() - 3);
  ofstream out_file;
  out_file.open(out_name + "compiled.css");
  out_file << content;
  out_file.close();
}

string compile_css(std::string &content) {
  string code = "";
  bool last_newline = true;
  for(unsigned i = 0; i < content.length(); i++) {
    char ch = content.at(i);
    if (last_newline) {
      code.push_back('.');
      last_newline = false;
    }
    if (ch == '\n') {
      last_newline = true;
    }
    code.push_back(ch);
  }
  return code;
}

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    cerr << "File not provided!" << endl;
    return 0;
  }

  if (!exists(argv[1])) {
    cerr << "File '" << argv[1] << "' not found." << endl;
    return 0;
  }

  string content = readFile(argv[1]);

  string compiled = compile_css(content);

  writeFile(argv[1], compiled);
  
  return 0;
}
