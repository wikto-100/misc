#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

const int numChars = 26;
char VIGENERE[numChars][numChars];
void sl_putchar(char x) {
  putchar(x);
  fflush(stdout);
  usleep(2000);
}
void setup() {
  printf("\t\t   VIGENERE TABLE\n");

  sl_putchar('|');
  for (int i = 0; i < 2 * numChars + 2; i++) {
    sl_putchar('+');
  }
  sl_putchar('|');
  sl_putchar('\n');
  for (int i = 0; i < numChars; i++) {
    sl_putchar('|');
    sl_putchar(' ');
    for (int j = 0; j < numChars; j++) {
      VIGENERE[i][j] = 'A' + (j + i) % 26;
      sl_putchar(VIGENERE[i][j]);
      sl_putchar(' ');
      fflush(stdout);
    }
    sl_putchar(' ');
    sl_putchar('|');
    sl_putchar('\n');
  }

  sl_putchar('|');
  for (int i = 0; i < 2 * numChars + 2; i++) {
    sl_putchar('+');
  }
  sl_putchar('|');
  sl_putchar('\n');
}
void encrypt(string &plaintext, string password) {

  string crypt_phr = plaintext;
  int num_spaces = 0;
  for (int i = 0; i < crypt_phr.length(); i++) {
    if (crypt_phr[i] == ' ') {
      num_spaces++;
      crypt_phr[i] = ' ';
    } else
      crypt_phr[i] = password[(i - num_spaces) % password.length()];
  }
    cout << crypt_phr << '\n';

  for (int i = 0; i < plaintext.length(); i++) {
    if (plaintext[i] == 0x20)
      continue;
    if (plaintext[i] <= 0x7a && plaintext[i] >= 0x61)
      plaintext[i] -= 0x20;
    else if (plaintext[i] < 0x41 || plaintext[i] > 0x5a) {
      cerr << "Character out of [A-Z/a-z] range. Exiting.\n";
      exit(EXIT_FAILURE);
    }

    if (crypt_phr[i] <= 0x7a and crypt_phr[i] >= 0x61)
      crypt_phr[i] -= 0x20;
    else if (crypt_phr[i] < 0x41 || crypt_phr[i] > 0x5a) {
      cerr << "Charcter out of [A-Z/a-z] range. Exiting.\n";
      exit(EXIT_FAILURE);
    }
    plaintext[i] = VIGENERE[int(crypt_phr[i]) - 65][int(plaintext[i] - 65)];
  }
  cout << crypt_phr << '\n';
}

int main() {
  setup();
  string password, plaintext;
  cout << "Passphrase: ";
  cin >> password;

  cout << "Message to encrypt: ";
  cin.ignore();
  getline(cin, plaintext);
  encrypt(plaintext, password);
  cout << "Encrypted message: " << plaintext << '\n';
  return 0;
}
