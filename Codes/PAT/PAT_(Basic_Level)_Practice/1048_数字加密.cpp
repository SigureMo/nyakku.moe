#include <iostream>

using namespace std;

int main() {
  string crypto_string, origin_string;
  string crypto_dict = "0123456789JQK";
  string out_string = "";
  cin >> crypto_string >> origin_string;
  int crypto_length = crypto_string.length();
  int origin_length = origin_string.length();

  for (int i = 0; i < crypto_length - origin_length; i++) {
    origin_string = '0' + origin_string;
  }
  for (int i = 0; i < origin_length - crypto_length; i++) {
    crypto_string = '0' + crypto_string;
  }

  for (int i = 0; i < origin_string.length(); i++) {
    char c;
    int origin_int = origin_string[i] - '0';
    int crypto_int = crypto_string[i] - '0';
    if ((origin_string.length() - i) % 2 == 0) {
      c = (origin_int - crypto_int + 10) % 10 + '0';
    }
    else {
      c = crypto_dict[(origin_int + crypto_int) % 13];
    }
    out_string += c;
  }
  cout << out_string;
  return 0;
}
