//=====================================================================
//
// ScriptConverter.cpp - Python Script to C++ Header Converter Tool
//
//=====================================================================
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Replace specific characters in a string
std::string ReplaceAll(const std::string &source, const std::string &from,
                       const std::string &to) {
  std::string result = source;
  size_t pos = 0;
  while ((pos = result.find(from, pos)) != std::string::npos) {
    result.replace(pos, from.length(), to);
    pos += to.length();
  }
  return result;
}

// Convert Python file to header file
bool ConvertPythonToHeader(const std::string &inputFile,
                           const std::string &outputFile) {
  // Open input file
  std::ifstream inFile(inputFile);
  if (!inFile.is_open()) {
    std::cerr << "Error: Cannot open input file: " << inputFile << std::endl;
    return false;
  }

  // Read entire file content
  std::stringstream buffer;
  buffer << inFile.rdbuf();
  inFile.close();
  std::string content = buffer.str();

  // Process special characters
  content = ReplaceAll(content, "\\", "\\\\");          // Backslash
  content = ReplaceAll(content, "\"", "\\\"");          // Double quote
  content = ReplaceAll(content, "\n", "\\n\"\n    \""); // Newline

  // Create output file
  std::ofstream outFile(outputFile);
  if (!outFile.is_open()) {
    std::cerr << "Error: Cannot create output file: " << outputFile
              << std::endl;
    return false;
  }

  // Write header file content
  outFile << "// Auto-generated file - Do not modify manually\n";
  outFile << "// Source file: " << inputFile << "\n\n";
  outFile << "#ifndef EMBEDDED_PYTHON_SCRIPT_H\n";
  outFile << "#define EMBEDDED_PYTHON_SCRIPT_H\n\n";
  outFile << "const char* EMBEDDED_PYTHON_SCRIPT = \n";
  outFile << "    \"" << content << "\\n\";\n\n";
  outFile << "#endif // EMBEDDED_PYTHON_SCRIPT_H\n";

  outFile.close();
  return true;
}

int main(int argc, char *argv[]) {
  // Check parameters
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " input_file.py output_file.h"
              << std::endl;
    return 1;
  }

  std::string inputFile = argv[1];
  std::string outputFile = argv[2];

  if (ConvertPythonToHeader(inputFile, outputFile)) {
    std::cout << "Successfully converted " << inputFile << " to " << outputFile
              << std::endl;
    return 0;
  } else {
    return 1;
  }
}