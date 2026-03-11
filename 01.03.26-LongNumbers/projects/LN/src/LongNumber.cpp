
#include "LongNumbers.hpp"

using pav::LongNumber;
		
LongNumber::LongNumber() { //КпоУ
	numbers = nullptr; 
	length = 0;        
	sign = 1;          
}


LongNumber::LongNumber(int length, int sign = 1) { //Констурктор с параметрами 
	this->length = length;
	this->sign = sign;
	numbers = new int[length];
	for (int i = 0; i <length; ++i) numbers[i]=0;
}


LongNumber::LongNumber(const char* const str) {// Конструктор из строки.
    int start = 0;
    sign = 1;
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }
    length = 0;
    for (int i = start; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') throw std::invalid_argument("Invalid digit in input string");
        ++length;
    }
    numbers = new int[length];
    for (int i = 0; i < length; ++i) {
        numbers[i] = str[start + length - 1 - i] - '0';
    }
    if (length == 1 && numbers[0] == 0) sign = 1; // 0 всегда положительный
}


LongNumber::LongNumber(const LongNumber& x) { //КК
	length = x.length;
    sign = x.sign;
	numbers = new int[x.length];
	for ( int i = 0; i < x.length; ++i) {
		numbers[i] = x.numbers[i];
	}
}


LongNumber::LongNumber(LongNumber&& x) { //КП
    numbers = x.numbers;
    length = x.length;
    sign = x.sign;
    x.numbers = nullptr;
    x.length = 0;
    x.sign = 0;
}

LongNumber::~LongNumber() {// Деструктор. 
	delete [] numbers;
}



LongNumber& LongNumber::operator = (const char* const str) { // Оператор присваивания из строки. 
    if (numbers != nullptr) {
        delete[] numbers;
    }
    int start = 0;
    sign = 1;
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }
    length = 0;
    for (int i = start; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') throw std::invalid_argument("Invalid digit in input string");
        ++length;
    }
    numbers = new int[length];
    for (int i = 0; i < length; ++i) {
        numbers[i] = str[start + length - 1 - i] - '0';
    }
    if (length == 1 && numbers[0] == 0) sign = 1;
    normalize();
    return *this;
}


// Оператор копирующего присваивания. Копирует значение из другого длинного числа.
LongNumber& LongNumber::operator = (const LongNumber& x) { //ОКП
    if (this == &x) return *this;
    delete[] numbers;
    length = x.length;
    sign = x.sign;
    numbers = new int[length];
    for (int i = 0; i < length; ++i) {
        numbers[i] = x.numbers[i];
    }
    return *this;
}


// Оператор перемещающего присваивания. Перемещает ресурсы из временного объекта.
LongNumber& LongNumber::operator = (LongNumber&& x) { //ОПП
    if (this == &x) return *this;
    delete[] numbers;
    numbers = x.numbers;
    length = x.length;
    sign = x.sign;
    x.numbers = nullptr;
    x.length = 0;
    x.sign = 0;
    return *this;
}


bool LongNumber::operator == (const LongNumber& x) const {
	if (length != x.length) return false;
	if (sign != x.sign) return false;
	for (int i = 0; i < length; ++i) {
		if (numbers[i] != x.numbers[i]) return false;
	}
	return true;
}


bool LongNumber::operator != (const LongNumber& x) const {
	if (length != x.length) return true;
	if (sign != x.sign) return true;
	for (int i = 0; i < length; ++i) {
		if (numbers[i] != x.numbers[i]) return true;
	}
	return false;
}


bool LongNumber::operator > (const LongNumber& x) const {
    if (sign > x.sign) return true;
    if (sign < x.sign) return false;
    if (sign == 1) {
        if (length > x.length) return true;
        if (length < x.length) return false;
        for (int i = length - 1; i >= 0; --i) {
            if (numbers[i] > x.numbers[i]) return true;
            if (numbers[i] < x.numbers[i]) return false;
        }
        return false;
    } else {
        if (length > x.length) return false;
        if (length < x.length) return true;
        for (int i = length - 1; i >= 0; --i) {
            if (numbers[i] < x.numbers[i]) return true;
            if (numbers[i] > x.numbers[i]) return false;
        }
        return false;
    }
}


bool LongNumber::operator < (const LongNumber& x) const {
    if (sign > x.sign) return false;
    if (sign < x.sign) return true;
    if (sign == 1) {
        if (length > x.length) return false;
        if (length < x.length) return true;
        for (int i = length - 1; i >= 0; --i) {
            if (numbers[i] > x.numbers[i]) return false;
            if (numbers[i] < x.numbers[i]) return true;
        }
        return false;
    } else {
        if (length > x.length) return true;
        if (length < x.length) return false;
        for (int i = length - 1; i >= 0; --i) {
            if (numbers[i] < x.numbers[i]) return false;
            if (numbers[i] > x.numbers[i]) return true;
        }
        return false;
    }
}


LongNumber LongNumber::operator + (const LongNumber& x) const {
    if (sign == x.sign) {
        LongNumber res(std::max(length, x.length) + 1);
        int carry = 0;

        for (int i = 0; i < std::max(length, x.length); ++i) {
            int a = (i < length) ? numbers[i] : 0;
            int b = (i < x.length) ? x.numbers[i] : 0;
            int sum = a + b + carry;
            res.numbers[i] = sum % 10;
            carry = sum / 10;
        }
        res.numbers[std::max(length, x.length)] = carry;

        res.sign = sign;

        int new_len = std::max(length, x.length) + 1;
        while (new_len > 1 && res.numbers[new_len - 1] == 0) {
            --new_len;
        }
        res.length = new_len;
        return res;
    } else {
        if (sign == 1) {
            // A + (-B) = A - |B|
            LongNumber tmp = x;
            tmp.sign = 1;
            return *this - tmp;
        } else {
            // (-A) + B = B - |A|
            LongNumber tmp = *this;
            tmp.sign = 1;
            return x - tmp;
        }
    }
}
	

LongNumber LongNumber::operator - (const LongNumber& x) const {
    if (sign == x.sign) {
        bool abs_comp;
        if (length != x.length) {
            abs_comp = (length > x.length);
        } else {
            abs_comp = true;
            for (int i = length - 1; i >= 0; --i) {
                if (numbers[i] > x.numbers[i]) { abs_comp = true; break; }
                if (numbers[i] < x.numbers[i]) { abs_comp = false; break; }
            }
        }
        if (abs_comp) {
            LongNumber res(std::max(length, x.length) + 1);
            int borrow = 0;
            for (int i = 0; i < std::max(length, x.length); ++i) {
                int a = (i < length) ? numbers[i] : 0;
                int b = (i < x.length) ? x.numbers[i] : 0;
                int diff = a - b - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                res.numbers[i] = diff;
            }
            res.numbers[std::max(length, x.length)] = 0;

            int new_len = std::max(length, x.length) + 1;
            while (new_len > 1 && res.numbers[new_len - 1] == 0) --new_len;
            res.length = new_len;
            res.sign = (new_len == 1 && res.numbers[0] == 0) ? 1 : sign;
            return res;
        } else {
            LongNumber res(std::max(length, x.length) + 1);
            int borrow = 0;
            for (int i = 0; i < std::max(length, x.length); ++i) {
                int a = (i < x.length) ? x.numbers[i] : 0;
                int b = (i < length) ? numbers[i] : 0;
                int diff = a - b - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                res.numbers[i] = diff;
            }
            res.numbers[std::max(length, x.length)] = 0;

            int new_len = std::max(length, x.length) + 1;
            while (new_len > 1 && res.numbers[new_len - 1] == 0) --new_len;
            res.length = new_len;
            res.sign = -sign;
            if (new_len == 1 && res.numbers[0] == 0) res.sign = 1;
            return res;
        }
    } else {
        LongNumber tmp = x;
        tmp.sign *= -1;
        return *this + tmp;
    }
}


LongNumber LongNumber::operator * (const LongNumber& x) const {
    LongNumber res(length + x.length, sign * x.sign);
    for (int i = 0; i < res.length; ++i) res.numbers[i] = 0;

    for (int i = 0; i < length; ++i) {
        int carry = 0;
        for (int j = 0; j < x.length; ++j) {
            int mul = numbers[i] * x.numbers[j] + res.numbers[i + j] + carry;
            res.numbers[i + j] = mul % 10;
            carry = mul / 10;
        }
        res.numbers[i + x.length] += carry;
    }

    int new_len = res.length;
    while (new_len > 1 && res.numbers[new_len - 1] == 0) --new_len;
    res.length = new_len;
    if (new_len == 1 && res.numbers[0] == 0) res.sign = 1;
    return res;
}


LongNumber LongNumber::operator / (const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    LongNumber dividend(*this);  //делимое 
    dividend.sign = 1;
    LongNumber divisor(x); //делитель 
    divisor.sign = 1;

    if (dividend < divisor) {
        return LongNumber("0");
    }

    int n = dividend.length;
    LongNumber res(n, sign * x.sign);

    LongNumber remainder; //остаток 
    remainder.length = 0;
    remainder.numbers = new int[n];
    for (int i = 0; i < n; ++i) remainder.numbers[i] = 0;

    for (int i = n - 1; i >= 0; --i) {
        for (int j = remainder.length; j > 0; --j)
            remainder.numbers[j] = remainder.numbers[j - 1];
        if (remainder.length < n) ++remainder.length;
        remainder.numbers[0] = dividend.numbers[i];

        int q = 0;
        while (!(remainder < divisor)) {
            remainder = remainder - divisor;
            ++q;
        }
        res.numbers[i] = q;
    }

    int new_len = n;
    while (new_len > 1 && res.numbers[new_len - 1] == 0) --new_len;
    res.length = new_len;

    if (new_len == 1 && res.numbers[0] == 0) res.sign = 1;
        if (this->sign < 0 && (remainder.length != 1 || remainder.numbers[0] != 0)) {
        LongNumber one("1");
        if (res.sign > 0)
            res = res + one;
        else
            res = res - one;
    }

    return res;
}


LongNumber LongNumber::operator % (const LongNumber& x) const {
    return *this - *this / x * x;
}


bool LongNumber::is_negative() const noexcept {
	return sign < 0;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------

int LongNumber::get_length(const char* const str) const noexcept {
	int start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
	int res = 0;
	for ( int i = start; str[i] != '\0'; i++ ) res++;
	return res; 
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------

void LongNumber::normalize() {
    while (length > 1 && numbers[length - 1] == 0) --length;
    if (length == 1 && numbers[0] == 0) sign = 1;
}

namespace pav {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
    if (x.sign < 0) os << '-';
    for (int i = x.length - 1; i >= 0; --i) {
        os << x.numbers[i]; 
    }
    return os;
}
}



