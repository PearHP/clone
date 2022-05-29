#include <iostream>
#include <string>

using namespace std;

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
        n >= 1;
    }
    int len = bin.size();
    for (int i = 0; i < 8 - len; i++){
        string s(1, '0');
        bin.insert(0, s);
    }
    return bin;
}

int convertBinToDec(string bin){
    int n, digit, dec = 0, i = 0;
    if (bin[0] & 1)
        return -1 * convertBinToDec(intoTwosComplement(bin));
    else{
        n = stoi(bin);
        while(n > 0){
            digit = n % 10;
            dec += digit << i;
            n = n / 10;
            i++;
        }
        return dec;
    } 
}

string add(string a, string b){
    string result = ""; 
    int s = 0;        
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1){
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);
        result = char(s % 2 + '0') + result;
        s >>= 1;
        i--;j--;
    }

    int n = result.size();
    return result.substr(n - 8, 8);
}

string subtract(string a, string b){
    string b_into_two_complement = intoTwosComplement(b);
    return add(a, b_into_two_complement);
}
 
string MakeShifting(string str, int step){ //Left shift for binary string with N steps
    string shifted = str;
    for (int i = 0; i < step; i++)
        shifted = shifted + '0';

    int n = shifted.size();
    return shifted.substr(n - 8, 8);
}

string multiply(string str1, string str2){
    string allSum = "";
    for (int j = 0 ; j < str2.length(); j++){
            int secondDigit = str2[j] - '0';
            if (secondDigit == 1){
                string shifted = MakeShifting(str1,str2.size()-(j+1));
                allSum = add(shifted, allSum);
            }   
        }
    int n = allSum.size();
    return allSum.substr(n - 8, 8);
}

string divide(string dividend, string divisor, string &remainder){
    if (dividend[0] == '0'){
        remainder = "00000000";
    }
    else{
        remainder = "11111111";
    }
    for (int i = 0; i < 8; i++){
        remainder = MakeShifting(remainder, 1);
        remainder += dividend[0];
        remainder = remainder.substr(1, 8);
        dividend = MakeShifting(dividend, 1);
        remainder = subtract(remainder, divisor);
        if (remainder[0] == '1'){
            dividend[7] = '0';
            remainder = add(remainder, divisor);
        }
        else{
            dividend[7] = '1';
        }
    }
    return dividend;
}

int main(){
    int a, b;
    cout << "\nInput A (Decimal): ";
    cin >> a;
    cout << "\nInput B (Decimal): ";
    cin >> b;
    string s1 = convertDecToBin(a);
    string s2 = convertDecToBin(b);
    cout << "\nA (Binary): " << s1;
    cout << "\nB (Binary): " << s2;

    string ans1 = add(s1, s2);
    cout << "\nA + B (Binary): " << ans1;
    cout << "\nA + B (Decimal): " << convertBinToDec(ans1);
    string ans2 = subtract(s1, s2);
    cout << "\nA - B (Binary): " << ans2;
    cout << "\nA - B (Decimal): " << convertBinToDec(ans2); 
    string ans3 = multiply(s1, s2);
    cout << "\nA * B (Binary): " << ans3; 
    cout << "\nA * B (Decimal): " << convertBinToDec(ans3);
    string s3;
    string ans4 = divide(s1, s2, s3);
    cout << "\nA / B (Binary): " << ans4; 
    cout << "\nA / B (Decimal): " << convertBinToDec(ans4); 
    cout << "\nA % B (Binary): " << s3;
    cout << "\nA % B (Decimal): " << convertBinToDec(s3);
    return 0;
}