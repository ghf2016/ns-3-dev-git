#ifndef UINT64X64_128_H
#define UINT64X64_128_H

#include "ns3/simulator-config.h"
#include <stdint.h>
#include <math.h>

#if defined(HAVE___UINT128_T) and !defined(HAVE_UINT128_T)
typedef __uint128_t uint128_t;
typedef __int128_t int128_t;
#endif

namespace ns3 {

#define HP128_MAX_64 18446744073709551615.0
#define HP128_MASK_LO ((((int128_t)1)<<64)-1)

class uint64x64_t
{
public:
  inline uint64x64_t ()
    : _v (0)
  {}
  explicit inline uint64x64_t (double value)
  {
    bool is_negative = value < 0;
    value = is_negative?-value:value;
    double hi = floor (value);
    double lo = (value - hi) * HP128_MAX_64;
    _v = (int128_t)hi;
    _v <<= 64;
    _v += (int128_t)lo;
    _v = is_negative?-_v:_v;
  }
  explicit inline uint64x64_t (int v)
    : _v (v)
  {
    _v <<= 64;
  }
  explicit inline uint64x64_t (long int v)
    : _v (v) 
  {
    _v <<= 64;
  }
  explicit inline uint64x64_t (long long int v)
    : _v (v) 
  {
    _v <<= 64;
  }
  explicit inline uint64x64_t (unsigned int v)
    : _v (v)
  {
    _v <<= 64;
  }
  explicit inline uint64x64_t (unsigned long int v)
    : _v (v) 
  {
    _v <<= 64;
  }
  explicit inline uint64x64_t (unsigned long long int v)
    : _v (v) 
  {
    _v <<= 64;
  }
  explicit inline uint64x64_t (int64_t hi, uint64_t lo)
  {
    bool is_negative = hi<0;
    _v = is_negative?-hi:hi;
    _v <<= 64;
    _v += lo;
    _v = is_negative?-_v:_v;
  }

  inline uint64x64_t (const uint64x64_t &o)
    : _v (o._v) {}
  inline uint64x64_t &operator = (const uint64x64_t &o)
    {
      _v = o._v;
      return *this;
    }

  inline double GetDouble (void) const
  {
    bool is_negative = _v < 0;
    uint128_t value = is_negative ? -_v:_v;
    uint64_t hi = value >> 64;
    uint64_t lo = value;
    double flo = lo;
    flo /= HP128_MAX_64;
    double retval = hi;
    retval += flo;
    retval = is_negative ? -retval : retval;
    return retval;
  }
  inline int64_t GetHigh (void) const
  {
    bool negative = _v < 0;
    int128_t v = negative?-_v:_v;
    v >>= 64;
    int64_t retval = v;
    return negative?-retval:retval;
  }
  inline uint64_t GetLow (void) const
  {
    bool negative = _v < 0;
    int128_t v = negative?-_v:_v;
    int128_t low = v & HP128_MASK_LO;
    uint64_t retval = low;
    return retval;
  }
#undef HP128_MAX_64
#undef HP128_MASK_LO

  void MulByInvert (const uint64x64_t &o);

  static uint64x64_t Invert (uint64_t v);

private:
  friend bool operator == (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend bool operator != (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend bool operator <= (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend bool operator >= (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend bool operator < (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend bool operator > (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t &operator += (uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t &operator -= (uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t &operator *= (uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t &operator /= (uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t operator + (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t operator - (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t operator * (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t operator / (const uint64x64_t &lhs, const uint64x64_t &rhs);
  friend uint64x64_t operator + (const uint64x64_t &lhs);
  friend uint64x64_t operator - (const uint64x64_t &lhs);
  friend uint64x64_t operator ! (const uint64x64_t &lhs);
  void Mul (const uint64x64_t &o);
  void Div (const uint64x64_t &o);
  static uint128_t UmulByInvert (uint128_t a, uint128_t b);
  static uint128_t Umul (uint128_t a, uint128_t b);
  static uint128_t Divu (uint128_t a, uint128_t b);
  inline uint64x64_t (int128_t v)
    : _v (v) {}

  int128_t _v;
};

inline bool operator == (const uint64x64_t &lhs, const uint64x64_t &rhs)
{
  return lhs._v == rhs._v;
}

inline bool operator != (const uint64x64_t &lhs, const uint64x64_t &rhs)
{
  return lhs._v != rhs._v;
}

inline bool operator < (const uint64x64_t &lhs, const uint64x64_t &rhs)
{
  return lhs._v < rhs._v;
}
inline bool operator <= (const uint64x64_t &lhs, const uint64x64_t &rhs)
{
  return lhs._v <= rhs._v;
}

inline bool operator >= (const uint64x64_t &lhs, const uint64x64_t &rhs)
{
  return lhs._v >= rhs._v;
}
inline bool operator > (const uint64x64_t &lhs, const uint64x64_t &rhs)
{
  return lhs._v > rhs._v;
}
inline uint64x64_t &operator += (uint64x64_t &lhs, const uint64x64_t &rhs)
{
  lhs._v += rhs._v;
  return lhs;
}
inline uint64x64_t &operator -= (uint64x64_t &lhs, const uint64x64_t &rhs)
{
  lhs._v -= rhs._v;
  return lhs;
}
inline uint64x64_t &operator *= (uint64x64_t &lhs, const uint64x64_t &rhs)
{
  lhs.Mul (rhs);
  return lhs;
}
inline uint64x64_t &operator /= (uint64x64_t &lhs, const uint64x64_t &rhs)
{
  lhs.Div (rhs);
  return lhs;
}

inline uint64x64_t operator + (const uint64x64_t &lhs)
{
  return lhs;
}

inline uint64x64_t operator - (const uint64x64_t &lhs)
{
  return uint64x64_t (-lhs._v);
}

inline uint64x64_t operator ! (const uint64x64_t &lhs)
{
  return uint64x64_t (!lhs._v);
}

} // namespace ns3

#endif /* UINT64X64_128_H */