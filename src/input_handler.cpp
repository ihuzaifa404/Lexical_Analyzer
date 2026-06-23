#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class InputHandler {
public:
    // Read file line by line and return full code
    string readFile(const string& fileName) {
        ifstream file(fileName);
        string line;
        string code = "";

        if (!file.is_open()) {
            cout << "Error: Cannot open file!" << endl;
            return "";
        }

        while (getline(file, line)) {
            code += line + "\n";   // keep line structure
        }

        file.close();
        return code;
    }

    // Clean each line (basic preprocessing)
    string preprocessLine(const string& line) {
        string cleaned = "";
        bool space = false;

        for (char c : line) {
            if (c == '\t') c = ' ';

            if (c == ' ') {
                if (!space) {
                    cleaned += ' ';
                    space = true;
                }
            }
            else {
                cleaned += c;
                space = false;
            }
        }

        return cleaned;
    }

    // Process full code line by line
    string processCode(const string& code) {
        string result = "";
        string line = "";

        for (char c : code) {
            if (c == '\n') {
                result += preprocessLine(line) + "\n";
                line = "";
            } else {
                line += c;
            }
        }

        return result;
    }
};

int main() {
    InputHandler input;

    string code = input.readFile("input.txt");

    if (code.empty()) return 0;

    string processed = input.processCode(code);

    cout << "Processed Code:\n";
    cout << processed;

    return 0;
}