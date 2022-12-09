#include "BigInt.h"


#define PLUS 0
#define MINUS 1
#define DIGITS_BASE 9

BigInt::BigInt() {
    sign = PLUS;
    digits.push_back(0);
}

BigInt::BigInt(int number) {
    if  (number>=0) sign = PLUS;
    else {
        sign = MINUS;
        number = abs(number);
    }
    do {
        digits.push_back(number % radix);
        number /= radix;
    } while (number != 0);
    (*this).is_negative_zero();
}

BigInt::BigInt(std::string str){
    if (!input_check(str)) throw std::invalid_argument("Not a number\n");
    int counter = 1, vector_index = 0, rank = 1;
    digits.push_back(0);

    if (str[0] == '-') {
        sign = MINUS;
        str.erase(0,1);
    }
    else {
        sign = PLUS;
        if (str[0] == '+') str.erase(0,1);
    }

    for (int i = (int) str.size() - 1; i>=0; i--){

        if (counter>DIGITS_BASE){
            digits.push_back(0);
            vector_index++;
            counter=1;
            rank=1;
        }
        digits[vector_index] += (str[i] - '0') * rank;
        rank *= 10;
        counter++;
    }
    (*this).is_negative_zero();
}

BigInt &BigInt::operator=(const BigInt &other){
    this->digits=other.digits;
    this->sign=other.sign;
    return (*this);
}

BigInt& BigInt::operator++() { //префиксный и постфиксный ++ и --
    return (*this) += 1;
}

const BigInt BigInt::operator++(int) {
    BigInt tmp = *this;
    *this += 1;
    return tmp;
}

BigInt& BigInt::operator--() {
    return (*this) -= 1;
}

const BigInt BigInt::operator--(int) {
    BigInt tmp = *this;
    *this -= 1;
    return tmp;
}

BigInt& BigInt::operator+=(const BigInt& other) {
    int carry = 0;
    BigInt max_object,min_object;

    if (this->digits == max_digit(this->digits,other.digits)) {
        max_object = *this;
        min_object = other;
    }
    else {
        max_object = other;
        min_object = *this;
    }

    int digit_min_size = std::min ((int)this->digits.size(),(int)other.digits.size());
    int index = digit_min_size;


    if (this->sign == other.sign) {
        for (int i = 0; i < digit_min_size; i++) {
            max_object.digits[i] += min_object.digits[i] + carry;
            carry = max_object.digits[i] / radix;
            max_object.digits[i] %= radix;
        }
        if (carry !=0 && max_object.digits.size() != min_object.digits.size()) {
            do {
                max_object.digits[index] += carry;
                carry = max_object.digits[index] / radix;
                max_object.digits[index] %= radix;
                index++;
            } while (index < max_object.digits.size() && carry != 0);
            if (index == max_object.digits.size() - 1 && carry !=0) max_object.digits.push_back(carry);
        }
        else if (carry !=0 && max_object.digits.size() == min_object.digits.size()) max_object.digits.push_back(carry);
    }

    else {
        if (this->digits.size() != 1) {
            for (int i = 0; i < digit_min_size; i++) {
                max_object.digits[i] += radix - min_object.digits[i] - carry;

                if (max_object.digits[i] < radix) carry = 1;
                else {
                    max_object.digits[i] %= radix;
                    carry = 0;
                }
            }
            if (carry == 1) {
                do {
                    max_object.digits[index] += radix - carry;
                    if (max_object.digits[index] < radix) carry = 1;
                    else {
                        max_object.digits[index] %= radix;
                        carry = 0;
                    }
                    index++;
                } while (index < max_object.digits.size() && carry != 0);
            }
        }
        else max_object.digits[0] = abs(max_object.digits[0] - min_object.digits[0]);
    }

    this->digits = max_object.digits;
    this->sign = max_object.sign;

    (*this).remove_leading_zeros();
    (*this).is_negative_zero();

    return (*this);
}

BigInt & BigInt::operator-=(const BigInt & other) {

    return (*this) += (-other);
}

BigInt& BigInt::operator*=(const BigInt& other) {
    long long int carry;
    long long int number_tmp;
    BigInt max_object,min_object,tmp,result;

    if (this->digits == max_digit(this->digits,other.digits)) {
        max_object = *this;
        min_object = other;
    }
    else {
        max_object = other;
        min_object = *this;
    }

    std::string min_object_str = std::string(min_object);
    if (min_object_str[0] == '-' || min_object_str[0] == '+') min_object_str.erase(0,1);

    int min_object_str_len = (int) min_object_str.size();
    int zero_add = min_object_str_len;
    int max_object_size = (int) max_object.digits.size();

    for (int i=0; i<min_object_str_len; i++){
        tmp = max_object;
        long long int number = min_object_str[i] - '0';
        carry = 0;

        for(int index = 0; index<max_object_size; index++){
            number_tmp = (long long int) tmp.digits[index];
            number_tmp = number_tmp * number + carry;
            carry = static_cast<int> (number_tmp / static_cast <long long int> (radix));
            tmp.digits[index] = static_cast<int> (number_tmp % radix);
        }
        if (carry !=0) tmp.digits.push_back(carry);

        std::string tmp_str = std::string(tmp);


        for (int zero_count = 0; zero_count < zero_add - 1; zero_count++) tmp_str+='0';

        tmp = BigInt(tmp_str);
        result+=tmp;
        zero_add--;
    }

    this->digits = result.digits;
    if (this->sign == other.sign) this->sign = PLUS;
    else this->sign = MINUS;
    (*this).is_negative_zero();

    return (*this);
}

BigInt& BigInt::operator/=(const BigInt& other) {
    if (other == BigInt(0)) throw std::invalid_argument("Divizion by zero");

    BigInt tmp, result, right_number = other;
    right_number.sign = PLUS;
    int this_sign = this->sign;

    result.digits.resize(this->digits.size());

    for (int i = (int) this->digits.size() - 1; i >= 0; i--) {
        tmp.shift_right();
        tmp.digits[0] = this->digits[i];
        tmp.remove_leading_zeros();

        int left = 0, right = radix, factor = 0;

        while (left <= right) {
            int middle = (left + right) / 2;
            BigInt selection_tmp =  BigInt(middle) * right_number;

            if (selection_tmp <= tmp) {

                factor = middle;
                left = middle + 1;
            }
            else right = middle - 1;
        }
        result.digits[i] = factor;
        tmp -= BigInt(factor) * right_number;
    }

    result.remove_leading_zeros();
    (*this) = result;
    if (this_sign == other.sign) this->sign = PLUS;
    else this->sign = MINUS;
    (*this).is_negative_zero();

    return (*this);

}

BigInt& BigInt::operator%=(const BigInt& other) {
    BigInt tmp = other;
    tmp.sign = PLUS;
    this->sign = PLUS;
    return (*this) -= ((*this) / tmp) * tmp;
}


bool BigInt::operator==(const BigInt&other) const{
    if (this->digits != other.digits) return false;

    if (this->sign != other.sign) return false;

    return true;
}

bool BigInt::operator!=(const BigInt&other) const {
    return (!((*this) == other));
}

bool BigInt::operator<(const BigInt&other) const {
    if (this->sign == other.sign) {
        if (this->digits == other.digits) return false;

        if (this->sign == MINUS){
            if (this->digits == max_digit(this->digits,other.digits)) return true;
            else if (other.digits == max_digit(this->digits,other.digits)) return false;
        }
        if (this->sign == PLUS) {

            if (this->digits == max_digit(this->digits,other.digits)) {
                return false;
            }
            else if (other.digits == max_digit(this->digits,other.digits)) {
                return true;
            }

        }
    }
    else {
        if (this->sign == MINUS) return true;
    }
    return false;

}

bool BigInt::operator>(const BigInt&other) const {
    return (!((*this) < other) && (*this) != other );
}

bool BigInt::operator<=(const BigInt&other) const {
    return ((*this) < other || (*this) == other );
}

bool BigInt::operator>=(const BigInt&other) const {
    return ((*this) > other || (*this) == other );
}

BigInt& BigInt::operator^=(const BigInt& other){
    BigInt result;

    std::string this_str = (*this).Bigint_to_binary_str();
    std::string other_str = other.Bigint_to_binary_str();
    std::string max_str;
    std::string min_str;

    if (this_str.size() >= other_str.size()){
        max_str = this_str;
        min_str=other_str;
    }
    else {
        min_str = this_str;
        max_str=other_str;
    }
    int min_index = (int) min_str.size() - 1;
    int max_index = (int) max_str.size() - 1;

    while (min_index >=0){
        if (max_str[max_index] == min_str[min_index]) max_str[max_index]='0';
        else max_str[max_index]='1';
        min_index--;
        max_index--;
    }


    result.binary_str_to_Bigint(max_str);
    if (this->sign == other.sign) result.sign = PLUS;
    else result.sign = MINUS;

    (*this) = result;
    (*this).is_negative_zero();

    return (*this);
}

BigInt& BigInt::operator&=(const BigInt& other){
    BigInt result;
    BigInt tmp = other;
    int this_sign = PLUS;

    if(this->sign == MINUS){
        this_sign = MINUS;
        (*this) =  ~ (*this);
    }
    if(other.sign == MINUS){
        tmp =  ~tmp;
    }


    std::string this_str = (*this).Bigint_to_binary_str();
    std::string other_str = tmp.Bigint_to_binary_str();

    std::string max_str;
    std::string min_str;

    int max_str_sign, min_str_sign;

    if (this_str.size() >= other_str.size()){
        max_str = this_str;
        min_str=other_str;
        max_str_sign = this_sign;
        min_str_sign = other.sign;
    }
    else {
        min_str = this_str;
        max_str=other_str;
        max_str_sign = other.sign;
        min_str_sign = this_sign;
    }

    int max_index = (int) max_str.size() - 1;

    min_str.insert(0,max_str.size() - min_str.size(),'0');

    if (max_str_sign == MINUS) max_str = invert(max_str);
    if (min_str_sign == MINUS) min_str = invert(min_str);


    while (max_index >=0){
        if (max_str[max_index] == '1' && min_str[max_index] == '1') max_str[max_index] = '1';
        else max_str[max_index] = '0';
        max_index--;
    }


    if (this_sign == MINUS && other.sign == MINUS) {
        max_str = invert(max_str);
        result.binary_str_to_Bigint(max_str);
        result++;
        result.sign = MINUS;
    }
    else {
        result.binary_str_to_Bigint(max_str);
        result.sign = PLUS;
    }

    (*this) = result;
    (*this).is_negative_zero();

    return (*this);
}

BigInt& BigInt::operator|=(const BigInt& other){
    BigInt result;
    BigInt tmp = other;
    int this_sign = PLUS;

    if(this->sign == MINUS){
        this_sign = MINUS;
        (*this) =  ~ (*this);
    }
    if(other.sign == MINUS){
        tmp =  ~tmp;
    }

    std::string this_str = (*this).Bigint_to_binary_str();
    std::string other_str = tmp.Bigint_to_binary_str();

    std::string max_str;
    std::string min_str;

    int max_str_sign, min_str_sign;

    if (this_str.size() >= other_str.size()){
        max_str = this_str;
        min_str=other_str;
        max_str_sign = this_sign;
        min_str_sign = other.sign;
    }
    else {
        min_str = this_str;
        max_str=other_str;
        max_str_sign = other.sign;
        min_str_sign = this_sign;
    }

    int max_index = (int) max_str.size() - 1;

    min_str.insert(0,max_str.size() - min_str.size(),'0');

    if (max_str_sign == MINUS) max_str = invert(max_str);
    if (min_str_sign == MINUS) min_str = invert(min_str);


    while (max_index >=0){
        if (max_str[max_index] == '0' && min_str[max_index] == '0') max_str[max_index] = '0';
        else max_str[max_index] = '1';
        max_index--;
    }

    if (this_sign == MINUS || other.sign == MINUS) {
        max_str = invert(max_str);
        result.binary_str_to_Bigint(max_str);
        result.sign = PLUS;
        result++;
        result.sign = MINUS;
    }
    else {
        result.binary_str_to_Bigint(max_str);
    }

    (*this) = result;
    (*this).is_negative_zero();

    return (*this);
}

BigInt BigInt::operator~() const {
    BigInt result = (*this);
    if (result.sign == MINUS)   {
        result++;
        result.sign = PLUS;
    }
    else {
        result++;
        result.sign = MINUS;
    }
    result.is_negative_zero();
    return result;
}


BigInt::~BigInt() { //
    this->digits.clear();
}

BigInt::BigInt(const BigInt& other){
    this->digits=other.digits;
    this->sign=other.sign;

}

BigInt::operator int() const {
    if (this->digits.size() == 1) {
        int tmp = (*this).digits[0];
        if (this->sign == MINUS) tmp = -tmp;
        return tmp;
    }

    std::string str((*this));
    std::string str_tmp;

    if (str[0] == '-') str.erase(0,1);
    str_tmp.append(str,0,9);
    const char* c_str_temp = str_tmp.c_str();

    int result = atoi(c_str_temp);

    if (this->sign == MINUS) result = -result;

    return result;
}

BigInt::operator std::string() const{
    std::string str;
    if (this->sign == MINUS){
        str += "-";
    }
    int digits_size = (int) this->digits.size() - 1;

    for (int index = digits_size; index>=0; index--){
        int tmp = this->digits[index], digits_count=0, zero_count;
        std::string str_tmp;

        do {
            str_tmp.insert(0,1,(char)('0' + tmp % 10));
            tmp /= 10;
            digits_count++;
        } while (tmp!=0);
        zero_count = DIGITS_BASE-digits_count;

        if (index!=digits_size) for (int k=1; k<=zero_count; k++) str+="0";
        str+=str_tmp;
    }
    return str;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i){
    std::string res(i);
    o << res;
    return o;
}

size_t BigInt::size() const {
    return (*this).digits.size() * sizeof(int) + sizeof(bool) + sizeof(int);
}

BigInt BigInt::operator+() const {
    return (*this);
}


BigInt BigInt::operator-() const {
    BigInt tmp = *this;
    if (tmp.sign == PLUS) tmp.sign= MINUS;
    else tmp.sign = PLUS;
    tmp.is_negative_zero();
    return tmp;
}

bool BigInt::input_check(std::string str) {
    int str_length = (int) str.size();

    if (!std::isdigit(str[0]) && str[0]!='+' && str[0]!='-') return false;
    for (int i=1; i<str_length; i++){
        if (!std::isdigit(str[i])) return false;
    }

    return true;

}
std::vector<int> BigInt::max_digit(std::vector<int> vector1, std::vector<int> vector2) const {
    if (vector1 == vector2 || vector1.size() > vector2.size()) {
        return vector1;
    }
    else if (vector1.size() < vector2.size()) return vector2;

    if (vector1.size() == vector2.size()) {

        int vector_index = (int) vector1.size() - 1;

        for (int i=vector_index; i>=0; i--) {
            if (vector1[i] < vector2[i]) {
                return vector2;
            }
            else if(vector1[i] > vector2[i]) return vector1;
        }


    }
    return vector1;
}
void BigInt::shift_right() {
    this->digits.push_back(0);
    for (int i = (int) this->digits.size() - 1 ; i > 0; i--) this->digits[i] = this->digits[i - 1];
}
void BigInt::remove_leading_zeros() {
    int digit_index= (int) this->digits.size() - 1;
    while (this->digits[digit_index] == 0 && digit_index>0){
        this->digits.pop_back();
        digit_index--;
    }
}

std::string BigInt::Bigint_to_binary_str() const {
    BigInt tmp = (*this), two = 2, zero = 0;
    tmp.sign = PLUS;
    std::string str_tmp;

    while (tmp != zero){
        str_tmp.insert(0,1,(char)((int)(tmp % two) + '0'));
        tmp /= two;
    }
    return str_tmp;
}

void BigInt::binary_str_to_Bigint (std::string str){

    BigInt result, two_tmp = 1, two = 2;

    for (int i = (int) str.size() - 1; i>=0; i--){
        int number = str[i] - '0';
        result+= BigInt(number) * two_tmp;
        two_tmp *= two;
    }
    (*this) = result;
}
void BigInt::is_negative_zero() {
    if (this->digits.size() == 1 && this->digits[0] == 0 && this->sign == MINUS) this->sign = PLUS;
}
std::string BigInt::invert(std::string str){
    for (int i = (int) str.size() - 1; i>=0; i--){
        if (str[i] == '0') str[i] = '1';
        else str[i] = '0';
    }
    return str;
}


BigInt operator+(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp += second_object;
    return tmp;

}
BigInt operator-(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp -= second_object;
    return tmp;
}

BigInt operator/(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp /= second_object;
    return tmp;
}

BigInt operator%(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp %= second_object;
    return tmp;
}

BigInt operator*(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp *= second_object;
    return tmp;
}
BigInt operator^(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp ^= second_object;
    return tmp;
}
BigInt operator&(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp &= second_object;
    return tmp;
}
BigInt operator|(const BigInt& first_object, const BigInt& second_object) {
    BigInt tmp = first_object;
    tmp |= second_object;
    return tmp;
}

