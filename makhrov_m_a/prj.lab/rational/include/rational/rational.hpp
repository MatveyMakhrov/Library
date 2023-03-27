#include <iosfwd>
#include <cstdint>
#include <stdexcept>

class Rational {
public:
    Rational();
    Rational(const int32_t numberInp);
    Rational(const Rational& myRat);
    Rational(const int32_t num, const int32_t denom);

    ~Rational() = default;

    Rational& operator=(const Rational& rhs);
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    Rational& operator%=(const Rational& rhs);

    bool isPositive() const;
    bool isZero() const;
    bool isNegative() const;

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);

private:
    int32_t gcd(int32_t a, int32_t b) const;
    void reducing();
private:
    int32_t num_{ 0 };
    int32_t denum_{ 1 };

    static const char slash{ '/' };
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);

Rational& operator+(Rational& rhs);
Rational& operator-(Rational& rhs);

Rational operator+(Rational lhs, const Rational& rhs);
Rational operator-(Rational lhs, const Rational& rhs);
Rational operator*(Rational lhs, const Rational& rhs);
Rational operator/(Rational lhs, const Rational& rhs);
Rational sqr(Rational myRat);
Rational pow(Rational myRat, const int32_t power);

Rational operator%(Rational lhs, const Rational& rhs);

bool operator==(Rational lhs, const Rational& rhs);
bool operator>(Rational lhs, const Rational& rhs);
bool operator<(Rational lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);