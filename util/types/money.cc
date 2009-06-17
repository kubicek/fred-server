#include <iomanip>

#include "money.h"
#include "stringify.h"


namespace Database {

/*
 * string construct and getter
 */

void Money::from_string(const std::string& _value) {
  value_ = unstringify<value_type>(_value);
}


const std::string Money::to_string() const {
  return stringify(value_);
}


/*
 * output operator
 */

std::ostream& operator<<(std::ostream &_os, const Money& _v) {
  return _os << _v.value_;
}

std::istream& operator>>(std::istream &_is, Money& _v) {
    std::string tmp;
    _is >> tmp;
    _v.from_string(tmp);
    return _is;
}



/*
 * comparison operators
 */

bool operator<(const Money& _left, const Money& _right) {
  return _left.value_ < _right.value_;
}


bool operator>(const Money& _left, const Money& _right) {
  return _left.value_ > _right.value_;
}


bool operator<=(const Money& _left, const Money& _right) {
  return !(_left > _right);
}

bool operator>=(const Money& _left, const Money& _right) {
  return !(_left < _right);
}


bool operator==(const Money& _left, const Money& _right) {
  return _left.value_ == _right.value_;
}


bool operator!=(const Money& _left, const Money& _right) {
  return !(_left == _right);
}


Money operator+(const Money& _left, const Money& _right) {
  return Money(_left.value_ + _right.value_);
}


Money operator-(const Money& _left, const Money& _right) {
  return Money(_left.value_ - _right.value_);
}

}

