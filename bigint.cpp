#include "bigint.h"
#include <cctype>
#include <cassert>

BigInt::BigInt(int val):m_sign(ZERO) {
    if(val < 0){
        m_sign = NEG;
        val*= -1;
    }
    while(val > 0){
        if(m_sign == ZERO)
            m_sign = POS;
        m_big_integer_number.push_back(val % BASE);
        val/=BASE;
    }
}

BigInt::BigInt(const std::string &text):m_sign(ZERO){
    assert(is_valid_text_input(text));
    uint16_t digit_base_10k = 0;
    uint32_t number_of_digits = 0;
    // Extract integer from string.
    for(int64_t i =static_cast<int32_t>( text.size()) - 1 ; i >= 0 ; --i){
        if(isdigit(text[i])){
            uint8_t  digit = text[i] - '0';                     // current digit.
            digit_base_10k = (digit_base_10k * 10) + digit;     // shift digit to next pos.
            if(++number_of_digits % 4 == 0){                    // counter for 10k base.
                m_big_integer_number.push_back(digit_base_10k); // push next 10k base digit to number.
                digit_base_10k = 0;                             // reset buffer.
            }
        }
    }
    m_big_integer_number.push_back(digit_base_10k);

    int64_t i = m_big_integer_number.size() - 1;
    // clean zero prefix.
    while (i >= 0 && !m_big_integer_number[i--]){
        m_big_integer_number.pop_back();
    }
    // set sign.
    if(!m_big_integer_number.empty()){
        m_sign = (text[0] == NEG)? NEG: POS;
    }
}

BigInt::BigInt(const BigInt &copy):
m_big_integer_number(copy.m_big_integer_number),m_sign(copy.m_sign)
{}

bool BigInt::is_valid_text_input(const std::string &text)  {
    size_t i = 0;
    bool result = true;
    if(text[i] != POS && text[i]!= NEG && !isdigit(text[i]))
        result = false;
    ++i;
    while(i < text.size() && result){
        if(!isdigit(text[i]))
            result = false;
    }
    return result;
}

BigInt BigInt::operator+(const BigInt &val) const {
    if(this->m_sign == val.m_sign)
        return add(*this,val);

    else if(this->m_sign == POS)
        return sub(*this, val);
    return sub(val , *this);
}

BigInt BigInt::operator+(int val) const {
    return *this - BigInt(val);
}

BigInt BigInt::operator-(const BigInt &val) const {
    if(this->m_sign != val.m_sign){
        if(this->m_sign == POS)
            return add(*this, -val);
        return add(-*this,val);
    }
    else if(this->m_sign == POS)
        return sub(*this, val);
    return sub(val, *this);
}

BigInt BigInt::operator-() const {
    BigInt result(*this);
    result.m_sign = (m_sign == NEG)? POS : NEG;
    return result;
}
// Assume same sign
BigInt BigInt::add(const BigInt &lhs, const BigInt &rhs) {
    size_t              i = 0;
    uint8_t             carry = 0;
    BigInt              result = 0;

    while (i < std::max(lhs.m_big_integer_number.size() ,rhs.m_big_integer_number.size())){
        uint32_t  current = carry;
        if(i < lhs.m_big_integer_number.size()){
            current+= lhs.m_big_integer_number[i];
        }
        if(i < rhs.m_big_integer_number.size()){
            current+= rhs.m_big_integer_number[i];
        }
        result.m_big_integer_number.push_back(current % BASE);
        carry = current / BASE;
    }
    if(carry){
        result.m_big_integer_number.push_back(carry);
    }
    return result;
}

BigInt BigInt::sub(const BigInt &lhs, const BigInt &rhs) {
    size_t              max_len = std::max(lhs.m_big_integer_number.size(), rhs.m_big_integer_number.size());
    BigInt              result(lhs);

    for(size_t i = result.m_big_integer_number.size() ; i < max_len ; ++i)
        result.m_big_integer_number.push_back(0);

    for(size_t i = 0 ; i < max_len ; ++i){
        if(result[i] < rhs[i] && lhs.m_big_integer_number.size() < i + 1){
            for(size_t k = i + 1 ; lhs[k] ; ++k){
                result[k]-=1;
                result[k-1]+=BASE;
            }
        }
        result[i] -= rhs[i];
    }


    return result;
}

int32_t &BigInt::operator[](size_t index) {
    return this->m_big_integer_number[index];
}

int32_t BigInt::operator[](size_t index) const {
    return this->m_big_integer_number[index];
}

bool BigInt::operator==(const BigInt &val) const {
    bool result = true;
    if(m_sign != val.m_sign){
        result = false;
    }
    if(result && m_big_integer_number.size() != val.m_big_integer_number.size()){
        result = false;
    }
    for(size_t i = 0 ; result && i < val.m_big_integer_number.size(); ++i){
        if((*this)[i] != val[i]){
            result = false;
        }
    }
    return result;
}

bool BigInt::operator!=(const BigInt &val) const {
    return !(*this == val);
}


