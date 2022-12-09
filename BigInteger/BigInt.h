#pragma once
#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>
#include <climits>

class BigInt {
public:
    BigInt(); //done
    BigInt(int); //done
    BigInt(std::string); //done
    BigInt(const BigInt&); //done
    ~BigInt(); //done

    BigInt& operator=(const BigInt&);  //done

    BigInt operator~() const; //3

    BigInt& operator++(); //done
    const BigInt operator++(int); //done
    BigInt& operator--(); //done
    const BigInt operator--(int); //done

    BigInt& operator+=(const BigInt&); //done
    BigInt& operator*=(const BigInt&); //done
    BigInt& operator-=(const BigInt&); //done
    BigInt& operator/=(const BigInt&); //done
    BigInt& operator^=(const BigInt&); //done
    BigInt& operator%=(const BigInt&); //done
    BigInt& operator&=(const BigInt&); //done
    BigInt& operator|=(const BigInt&); //done

    BigInt operator+() const;  //done
    BigInt operator-() const;  //done

    bool operator==(const BigInt&) const; //done
    bool operator!=(const BigInt&) const; //done
    bool operator<(const BigInt&) const; //done
    bool operator>(const BigInt&) const; //done
    bool operator<=(const BigInt&) const; //done
    bool operator>=(const BigInt&) const; //done

    operator int() const; //done
    operator std::string() const; //done

    size_t size() const;  // done

    std::vector<int> digits;
    const int radix = 1000000000;
    bool sign;


    bool input_check(std::string);
    std::vector<int> max_digit(std::vector<int>,std::vector<int>) const;
    void shift_right();
    void remove_leading_zeros ();
    std::string Bigint_to_binary_str() const;
    void binary_str_to_Bigint(std::string str);
    void is_negative_zero();
    std::string invert(std::string);
};

BigInt operator+(const BigInt&, const BigInt&); //done
BigInt operator-(const BigInt&, const BigInt&); //done
BigInt operator*(const BigInt&, const BigInt&); //done
BigInt operator/(const BigInt&, const BigInt&); //done
BigInt operator^(const BigInt&, const BigInt&); //done
BigInt operator%(const BigInt&, const BigInt&); //done
BigInt operator&(const BigInt&, const BigInt&); //done
BigInt operator|(const BigInt&, const BigInt&); //done


std::ostream& operator<<(std::ostream& o, const BigInt& i); //done

#endif
