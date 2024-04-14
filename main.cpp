#include <iostream>
#include "encrypt.h"
#include <fstream>  
#include <cctype>
#include <iterator> 
using namespace std;

bool performCeaserCipher(string& content, bool encrypt, int key) {
    int shift = encrypt ? key : -key;
    for (char& ch : content) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = static_cast<char>((ch - base + shift + 26) % 26 + base); 
        }
    }
    return true;
}
bool encryptfile(const string& filename, bool encrypt, int key) {
    // Open the file
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return false;
    }

    // Read Content of file
    string content((istreambuf_iterator<char>(inFile)), {});
    inFile.close();

    if (performCeaserCipher(content, encrypt, key)) {
        // Create an Output file and Modify Content
        ofstream outFile(encrypt ? "encrypted_" + filename : "decrypted_" + filename);
        if (!outFile) {
            cerr << "Error: Unable to create output file." << endl;
            return false;
        }
        outFile << content;
        outFile.close();
        return true;
    }

    cerr << "Error: Encryption/Decryption failed." << endl;
    return false; 
}

int main() {
    string filename;
    char mode;
    int key;
    cout << "Enter filename: ";
    getline(cin >> ws, filename);
    cout << "Encrypt(e) or Decrypt(d)?  ";
    cin >> mode;
    cout << "Enter the Key: ";
    cin >> key;

    switch (mode) {
        case 'e':
        case 'E':
            if (encryptfile(filename, true, key)) {
                cout << "Encryption completed successfully." << endl;
            } else {
                cerr << "Error: Unable to perform encryption." << endl;
            }
            break;
        case 'd':
        case 'D':
            if (encryptfile(filename, false, key)) {
                cout << "Decryption completed successfully." << endl;
            } else {
                cerr << "Error: Unable to perform decryption." << endl;
            }
            break;
        default:
            cerr << "Error: Invalid Mode Selection. Use (e) for encrypt and (d) for decrypt." << endl;
            break;
    }

    return 0;
}

