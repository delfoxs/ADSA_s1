#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string reverseString(string str) {
  reverse(str.begin(), str.end());
  return str;
}
// recursive additon
string addBase(const string& firstNum, const string& secondNum, int base) {
  string result = "";
  int carry = 0;
  int i = firstNum.length() - 1;
  int j = secondNum.length() - 1;

  while (i >= 0 || j >= 0 || carry) {
    int firstDigit = i >= 0 ? firstNum[i--] - '0' : 0;
    int secondDigit = j >= 0 ? secondNum[j--] - '0' : 0;
    int sum = firstDigit + secondDigit + carry;
    result += (sum % base) + '0';
    carry = sum / base;
  }
  reverse(result.begin(), result.end());
  if (result.empty()) {
        return "0";  // Return "0" instead of an empty string when there's no input.
  }
  return result;
}

// recursive subtraction
string subBase(const string& firstNum, const string& secondNum, int base) {
  string result = "";
  int carry = 0;
  int i = firstNum.length() - 1;
  int j = secondNum.length() - 1;

  while (i >= 0 || j >= 0 || carry) {
    int firstDigit = i >= 0 ? firstNum[i--] - '0' : 0;
    int secondDigit = j >= 0 ? secondNum[j--] - '0' + carry : carry;
    int sub = firstDigit - secondDigit;
    if (sub < 0) {
      sub += base;
      carry = 1;
    } else {
      carry = 0;
    }
    result += sub + '0';
  }
  while (result.size() > 1 && result.back() == '0') result.pop_back();
  reverse(result.begin(), result.end());
  return result;
}

// Karatsuba Multiplication
string multKaratsuba(string x, string y, int base) {
  if (x.size() == 1 && y.size() == 1) {
    int result((x[0] - '0') * (y[0] - '0'));
    return to_string(result);
  }
  int n = max(x.size(), y.size());
  int half = n / 2;

  if (x.size() < half + 1) x = string(half + 1 - x.size(), '0') + x;
  if (y.size() < half + 1) y = string(half + 1 - y.size(), '0') + y;

  string xh = x.substr(0, x.size() - half);
  string xl = x.substr(x.size() - half);
  string yh = y.substr(0, y.size() - half);
  string yl = y.substr(y.size() - half);

  string a = multKaratsuba(xh, yh, base);
  string b = multKaratsuba(xl, yl, base);
  string c = multKaratsuba(addBase(xh, xl, base), addBase(yh, yl, base), base);
  string m = subBase(subBase(c, a, base), b, base);
  for (int i = 0; i < 2 * half; i++) a += '0';
  for (int i = 0; i < half; i++) m += '0';

  return addBase(addBase(a, m, base), b, base);
}
int main() {
  string N1, N2;
  int B;

  cout << "Enter two numbers and the base (for example: 110 112 10): ";
  cin >> N1 >> N2 >> B;

  string sum = addBase(N1, N2, B);
  string product = multKaratsuba(N1, N2, B);

  cout << "Sum: " << sum << " Product: " << product << endl;

  return 0;
}
