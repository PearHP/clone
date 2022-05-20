#include <iostream>

using namespace std;

// Returns '0' for '1' and '1' for '0'
char flip(char c){
    return (c == '0')? '1': '0';
}

string intoTwosComplement(string bin){
    int i, n = bin.size();
    string ones, twos;
    ones = twos = "";

    for (i = 0; i < n; i++)
        ones += flip(bin[i]);
    twos = ones;
    for (i = n - 1; i >= 0; i--){
        if (ones[i] == '1')
            twos[i] = '0';
        else{
            twos[i] = '1';
            break;
        }
    }
    if (i == -1)
        twos += '1';
    return twos;
}

string convertDecToBin(int n){
    if (n == 0)
        return "00000000";
    if (n < 0){
        n *= -1;
        return intoTwosComplement(convertDecToBin(n));
    }
    string bin = "";
    while (n > 0 && bin.size() <= 8){
        string s(1, ((n & 1)? '1' : '0'));
        bin.insert(0, s);
        n >>= 1;
    }
    int len = bin.size();
    for (int i = 0; i < 8 - len; i++){
        string s(1, '0');
        bin.insert(0, s);
    }
    return bin;
}

int convertBinToDec(string bin){
    int n,digit,dec = 0,i = 0;
    if (bin[0] == 1)
        return -1 * convertBinToDec(intoTwosComplement(bin));
    else{
        n = stoic(bin);

        while(n != 0){
            digit = n % 10;
            dec += digit << i;
            n = n / 10;
            i++;
        }
        return dec;
    } 
}

string addBitStrings(string first, string second){
    string result;
    int carry = 0; 

    for (int i = 7 ; i >= 0 ; i--){
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';
        int sum = (firstBit ^ secondBit ^ carry) + '0';
        result = (char)sum + result;
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }
    if (carry)  
        result += '1';

    if (result[0] & 1)
        return intoTwosComplement(result);
    else
        return result;
}
string add(string a, string b){
   string result = "";
   int temp = 0;
   int size_a = a.size() - 1;
   int size_b = b.size() - 1;
   while (size_a >= 0 || size_b >= 0 || temp == 1){
      temp += ((size_a >= 0)? a[size_a] - '0': 0);
      temp += ((size_b >= 0)? b[size_b] - '0': 0);
      result = char(temp % 2 + '0') + result;
      temp /= 2;
      size_a--; size_b--;
   }

   int n = result.size();
   return result.substr(n - 8, 8);
}

string subtractBitStrings(string first, string second){
    string second_two_complement = intoTwosComplement(second);
    return intoTwosComplement(add(first, second_two_complement));
}
 
int multiplySingleBit(string a, string b){
    return (a[0] - '0') * (b[0] - '0');
}
 
long int multiply(string X, string Y){
    int n = 7;
    if (n == 0) return 0;
    if (n == 1) return multiplySingleBit(X, Y);
    
    int fh = n/2;  
    int sh = (n-fh);
    string Xl = X.substr(0, fh);
    string Xr = X.substr(fh, sh);
    string Yl = Y.substr(0, fh);
    string Yr = Y.substr(fh, sh);
 
    long int P1 = multiply(Xl, Yl);
    long int P2 = multiply(Xr, Yr);
    long int P3 = multiply(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr));
 
    return P1*(1<<(2*sh)) + (P3 - P1 - P2)*(1<<sh) + P2;
}

int main(){
    // int a, b, t;
    // cout << "================================================";
    // cout << "\nEnter value for number A: ";
    // cin >> a;
    // cout << "\nEnter value for number B: ";
    // cin >> b;
    string s1 = convertDecToBin(5);
    string s2 = convertDecToBin(-33);
    string temp1 = add(s1, s2);
    cout << "\nThe answer of A + B = " << convertBinToDec(temp1);

    string temp2 = subtractBitStrings(s1, s2);
    cout << "\nThe answer of A - B = " << -1 * convertBinToDec(temp2);

    // cout << "\nThe answer of A * B = "<< multiply(s1, s2);

    // cout << convertDecToBin(-5);
    // 11111011 //-5
    // 00001010 //10

    // 00000101

    return 0;
}