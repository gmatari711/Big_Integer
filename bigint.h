#ifndef BIGINT_H_
#define BIGINT_H_

#include<string>
#include <iostream>
#include <inttypes.h>
#include <vector>

class BigInt
{
private:
    static const char           POS = '+',
                                NEG = '-',
                                ZERO ='0';
    static const uint32_t       BASE = 10000;
    std::vector<int32_t>       m_big_integer_number;
    uint8_t                     m_sign;

    // Util Func
    static bool is_valid_text_input(const std::string& text);
    BigInt add(const BigInt& val)const;
    BigInt sub(const BigInt& val)const;

    static BigInt sub(const BigInt& lhs, const BigInt& rhs);
    inline int32_t& operator[](size_t index);
    inline int32_t operator[](size_t index)const;
    bool less_than_diff_sign(const BigInt& val)const;
    bool less_than_same_sign(const BigInt& val)const;
    BigInt multiplication(const BigInt& val)const;
    BigInt fast_multiplication(const BigInt& val)const; //Karatsuba

//think about the private data members
public:
    BigInt(int val = 0);
    BigInt(const std::string& text);
    BigInt(const BigInt& copy); // copy constructor

// Mathematical Operations
    BigInt abs()const;

// Binary Operators
// Arithmetic Operators
    BigInt operator+(const BigInt& val) const;
    BigInt operator+(int val) const;
    BigInt operator-(const BigInt& val) const;
    BigInt operator-(int val) const;
    BigInt operator*(const BigInt& val) const;
// Compound Assignment Operators
    BigInt operator+=(const BigInt& rhs);
    BigInt operator-=(const BigInt& rhs);
    BigInt operator*=(const BigInt& rhs);
// Logical Operators
    bool operator==(const BigInt& val) const;
    bool operator!=(const BigInt& val) const;
    bool operator<(const BigInt& val) const;
    bool operator<=(const BigInt& val) const;
    bool operator>(const BigInt& val) const;
    bool operator>=(const BigInt& val) const;

// Unary Operators
    BigInt operator-()const; // Negation Operator
    BigInt& operator++(); // Pre-increment Operator
    BigInt operator++(int); // Post-increment Operator
    BigInt& operator--(); // Pre-decrement Operator
    BigInt operator--( int ); // Post-decrement Operator

//Conversion Operator
    operator std::string(); // return value of the BigInt as string
    ~BigInt(); // destructor
};

std::ostream& operator<<(std::ostream& output, const BigInt& val); // outputs the BigInt
std::istream& operator>>(std::istream& input, BigInt& val); // inputs the BigInt


#endif /* BIGINT_H_ */