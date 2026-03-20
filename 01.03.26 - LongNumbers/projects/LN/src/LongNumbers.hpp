#pragma once

#include <iostream>

namespace pav {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;
		
		public:

			LongNumber();
			LongNumber(int length, int sign);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;
			
			bool is_negative() const noexcept;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);

			
		private:
			void normalize();
			int get_length(const char* const str) const noexcept;
	};
}