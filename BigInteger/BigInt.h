#pragma once
#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>


namespace bigint {
    class BigInt {
    private:
        std::vector<int> digits;
        const int radix = 1000000000;
        bool sign;

        const bool PLUS = false;
        const bool MINUS = true;
        const int DIGITS_BASE = 9;
        const int MAX_STR_ID = 0;
        const int MIN_STR_ID = 1;
    public:
        BigInt();
        BigInt(int);
        BigInt(std::string);
        BigInt(const BigInt &);
        ~BigInt();

        BigInt &operator=(const BigInt &);

        BigInt operator~() const;

        BigInt &operator++();
        const BigInt operator++(int);
        BigInt &operator--();
        const BigInt operator--(int);

        BigInt &operator+=(const BigInt &);
        BigInt &operator*=(const BigInt &);
        BigInt &operator-=(const BigInt &);
        BigInt &operator/=(const BigInt &);
        BigInt &operator^=(const BigInt &);
        BigInt &operator%=(const BigInt &);
        BigInt &operator&=(const BigInt &);
        BigInt &operator|=(const BigInt &);

        BigInt operator+() const;
        BigInt operator-() const;

        bool operator==(const BigInt &) const;
        bool operator!=(const BigInt &) const;
        bool operator<(const BigInt &) const;
        bool operator>(const BigInt &) const;
        bool operator<=(const BigInt &) const;
        bool operator>=(const BigInt &) const;

        operator int() const;
        operator std::string() const;

        size_t size() const;

        bool input_check(std::string);

        std::vector<int> max_digit(std::vector<int>, std::vector<int>) const;

        void shift_right();

        void remove_leading_zeros();

        std::string Bigint_to_binary_str() const;

        std::string get_max_str(const BigInt &) const;

        void bit_neg_check();
        std::string str_invert_check(std::string,int);

        std::vector<std::string> get_result_str(BigInt &, int, int);

        void binary_str_to_Bigint(std::string str);

        void is_negative_zero();

        std::string invert(std::string);

    };

    BigInt operator+(const BigInt &, const BigInt &);
    BigInt operator-(const BigInt &, const BigInt &);
    BigInt operator*(const BigInt &, const BigInt &);
    BigInt operator/(const BigInt &, const BigInt &);
    BigInt operator^(const BigInt &, const BigInt &);
    BigInt operator%(const BigInt &, const BigInt &);
    BigInt operator&(const BigInt &, const BigInt &);
    BigInt operator|(const BigInt &, const BigInt &);


    std::ostream &operator<<(std::ostream &o, const BigInt &i);
}
#endif
