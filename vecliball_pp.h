namespace veclib
{
   typedef unsigned int    uint;
   typedef int             i32;
   typedef unsigned int    u32;
   typedef unsigned char   u8;
   typedef char            i8;

   union UValue
   {
      UValue(uint v) : u(v)
      {
      }
      UValue(int v) : i(v)
      {
      }
      UValue(float v) : f(v)
      {
      }

      float f;
      int   i;
      uint  u;
   };



   template <class base, int m, int n = 1>
   class Const {
      static const base value;
public:
      INLINE static base Value()
      {
         return(value);
      }
   };



   template <class T>
   struct ScalarInfo
   {
      enum {
         Multiplicity = 1
      };
      typedef bool   TBool;


      INLINE static bool ElementMask(int n)
      {
         return(1);
      }
   };

   template <class base, int m, int n>
   const base Const <base, m, n>::value = base(m) / base(n);

   template <class base> struct ConstPI : public      Const <base, 75948, 24175> { };
   template <class base> struct Const2PI : public     Const <base, 2 *75948, 24175> { };
   template <class base> struct ConstInvPI : public   Const <base, 24175, 75948> { };
   template <class base> struct ConstInv2PI : public  Const <base, 24175, 2 *75948> { };
   template <class base> struct ConstEpsilon : public Const <base, 1, 100000> { };

   INLINE float Sqrt(const float&v)
   {
      return(sqrt(v));
   }

   INLINE float Inv(const float&v)
   {
      return(Const <float, 1>::Value() / v);
   }

   INLINE float RSqrt(const float&v)
   {
      return(Const <float, 1>::Value() / Sqrt(v));
   }

   INLINE float FastInv(const float&v)
   {
      return(Const <float, 1>::Value() / v);
   }

   INLINE float FastRSqrt(const float&v)
   {
      return(Const <float, 1>::Value() / Sqrt(v));
   }

   INLINE float Abs(const float&v)
   {
      return(v < Const <float, 0>::Value() ? v : -v);
   }

   INLINE float Min(const float&a, const float&b)
   {
      return(a < b ? a : b);
   }

   INLINE float Max(const float&a, const float&b)
   {
      return(a > b ? a : b);
   }

   INLINE float Condition(bool expr, float a, float b)
   {
      return(expr ? a : b);
   }

   INLINE float Condition(bool expr, float v)
   {
      return(expr ? v : 0.0f);
   }

   INLINE int SignMask(const float&v)
   {
      return(v < 0 ? 1 : 0);
   }

   INLINE float Sin(const float rad)
   {
      return(sin(rad));
   }

   INLINE float Cos(const float rad)
   {
      return(cos(rad));
   }

   INLINE float FRand()
   {
      return(float (rand()) / float (RAND_MAX));
   }

   INLINE bool ForAny(bool expr)
   {
      return(expr);
   }

   INLINE bool ForAll(bool expr)
   {
      return(expr);
   }

   INLINE int ForWhich(bool expr)
   {
      return(expr);
   }

   template <class T>
   T Clamp(const T&obj, const T&min, const T&max)
   {
      return(Min(Max(obj, min), max));
   }

   template <uint mask>
   __m128 _mm_shuffle_(const __m128&v)
   {
      return(_mm_shuffle_ps(v, v, mask));
   }

   template <int m, int n>
   struct Const <__m128, m, n>
   {
      template <class T, int a, int b> friend class Const;
      static const __m128                           value;
public:
      INLINE static __m128 Value()
      {
         return(value);
      }
   };

   template <int m, int n>
   const __m128 Const <__m128, m, n> :: value = _mm_set1_ps(float (m) / float (n));

   template <int n>
   struct Const <__m128, 0, n>
   {
      INLINE static __m128 Value()
      {
         return(_mm_setzero_ps());
      }
   };


   INLINE __m128 _mm_load4a(const float arr[4])
   {
      __m128 out;

      out = _mm_load_ps(arr);
      return(out);
   }

   INLINE __m128 _mm_load4(const float arr[4])
   {
      __m128 out;

      out = _mm_loadu_ps(arr);



      return(out);
   }

   INLINE void _mm_store4a(__m128 v, float arr[4])
   {
      _mm_store_ps(arr, v);
   }
   INLINE void _mm_store4(__m128 v, float arr[4])
   {
      _mm_storeu_ps(arr, v);
   }



   INLINE __m128 _mm_load3(const float arr[3])
   {
      __m128 out;

      out = _mm_shuffle_ps(
         _mm_shuffle_ps(
            _mm_load_ss(arr + 0),
            _mm_load_ss(arr + 1), 0),
         _mm_load_ss(arr + 2),
         0 + (2 << 2) + (0 << 4) + (0 << 6));
      return(out);
   }

   INLINE void _mm_store3(__m128 v, float arr[3])
   {
      _mm_store_ss(arr + 0, v);
      _mm_store_ss(arr + 1, _mm_shuffle_ps(v, v, 1));
      _mm_store_ss(arr + 2, _mm_shuffle_ps(v, v, 2));
   }

   INLINE __m128 _mm_load2(const float arr[2])
   {
      __m128 out;

      out = _mm_shuffle_ps(_mm_load_ss(arr + 0), _mm_load_ss(arr + 1), 0);
      out = _mm_shuffle_ps(out, out, 0 + (3 << 2) + (0 << 4) + (3 << 6));
      return(out);
   }

   INLINE void _mm_store2(__m128 v, float arr[2])
   {
      _mm_store_ss(arr + 0, v);
      _mm_store_ss(arr + 1, _mm_shuffle_ps(v, v, 1));
   }

   INLINE __m128 _mm_load1(float v)
   {
      __m128 out;

      out = _mm_load_ss(&v);
      out = _mm_shuffle_ps(out, out, 0);
      return(out);
   }

   INLINE float _mm_store1(__m128 v)
   {
      float out;

      _mm_store_ss(&out, v);
      return(out);
   }

   INLINE __m128 _mm_nrrcp_ps(const __m128&v)
   {
      __m128 out;
      __m128 t = _mm_rcp_ps(v);

      out = _mm_sub_ps(_mm_add_ps(t, t), _mm_mul_ps(_mm_mul_ps(v, t), t));
      return(out);
   }

   INLINE __m128 _mm_nrrsqrt_ps(const __m128&v)
   {
      __m128 out;
      __m128 t = _mm_rsqrt_ps(v);

      out = _mm_mul_ps(_mm_mul_ps(Const <__m128, 1, 2>::Value(), t),
                       _mm_sub_ps(Const <__m128, 3>::Value(), _mm_mul_ps(_mm_mul_ps(v, t), t)));
      return(out);
   }

   INLINE void _mm_transpose(const __m128&x, const __m128&y, const __m128&z, const __m128&w,
                             __m128&ox, __m128&oy, __m128&oz, __m128&ow)
   {
      __m128 tmp3, tmp2, tmp1, tmp0;

      tmp0 = _mm_shuffle_ps(x, y, 0x44);
      tmp2 = _mm_shuffle_ps(x, y, 0xEE);
      tmp1 = _mm_shuffle_ps(z, w, 0x44);
      tmp3 = _mm_shuffle_ps(z, w, 0xEE);

      ox = _mm_shuffle_ps(tmp0, tmp1, 0x88);
      oy = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
      oz = _mm_shuffle_ps(tmp2, tmp3, 0x88);
      ow = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
   }

   INLINE void _mm_transpose(__m128&x, __m128&y, __m128&z, __m128&w)
   {
      _mm_transpose(x, y, z, w, x, y, z, w);
   }

   class SSEMaskNeg;

   class SSEMask
   {
public:
      INLINE SSEMask()
      {
      }

      INLINE SSEMask(const __m128&v) : m(v)
      {
      }

      INLINE SSEMask operator^(const SSEMask&v) const
      {
         return(_mm_xor_ps(m, v.m));
      }

      INLINE SSEMask operator&&(const SSEMask&v) const
      {
         return(_mm_and_ps(m, v.m));
      }

      INLINE SSEMask operator||(const SSEMask&v) const
      {
         return(_mm_or_ps(m, v.m));
      }

      __m128 m;
   };

   template <int mask> class Const <SSEMask, mask, 1> {
      static const SSEMask value;
public:
      INLINE static SSEMask Value()
      {
         return(value);
      }
   };
   template <int mask> const SSEMask Const <SSEMask, mask, 1>::value = _mm_set1_ps(UValue(mask).f);


   class SSEMaskNeg
   {
public:
      INLINE SSEMaskNeg(const __m128&v) : m(v)
      {
      }

      INLINE SSEMaskNeg operator^(const SSEMask&v) const
      {
         return(_mm_xor_ps(m, v.m));
      }

      INLINE SSEMask operator^(const SSEMaskNeg&v) const
      {
         return(_mm_xor_ps(m, v.m));
      }

      INLINE SSEMask operator!() const
      {
         return(SSEMask(m));
      }

      INLINE SSEMask operator&&(const SSEMask&v) const
      {
         return(_mm_andnot_ps(m, v.m));
      }

      INLINE SSEMaskNeg operator&&(const SSEMaskNeg&v) const
      {
         return(_mm_or_ps(m, v.m));
      }

      INLINE SSEMaskNeg operator||(const SSEMaskNeg&v) const
      {
         return(_mm_and_ps(m, v.m));
      }

      INLINE SSEMask operator||(const SSEMask&v) const
      {
         return(_mm_or_ps(_mm_andnot_ps(m, Const <SSEMask, 0xffffffff>::Value().m), v.m));
      }

      operator SSEMask() const
      {
         return(_mm_andnot_ps(m, Const <SSEMask, 0xffffffff>::Value().m));
      }

      __m128 m;
   };

   INLINE SSEMaskNeg operator!(const SSEMask&v)
   {
      return(SSEMaskNeg(v.m));
   }

   INLINE SSEMaskNeg operator^(const SSEMask&a, const SSEMaskNeg&b)
   {
      return(_mm_xor_ps(a.m, b.m));
   }

   INLINE SSEMask operator&&(const SSEMask&a, const SSEMaskNeg&b)
   {
      return(_mm_andnot_ps(b.m, a.m));
   }

   INLINE SSEMask operator||(const SSEMask&a, const SSEMaskNeg&b)
   {
      return(_mm_or_ps(a.m, _mm_andnot_ps(b.m, Const <SSEMask, 0xffffffff>::Value().m)));
   }

   class SSEPMaskNeg;

   class SSEPMask
   {
public:
      INLINE SSEPMask()
      {
      }

      INLINE SSEPMask(const __m128&v) : m(v)
      {
      }

      INLINE SSEPMask operator^(const SSEPMask&v) const
      {
         return(_mm_xor_ps(m, v.m));
      }

      INLINE SSEPMask operator&&(const SSEPMask&v) const
      {
         return(_mm_and_ps(m, v.m));
      }

      INLINE SSEPMask operator||(const SSEPMask&v) const
      {
         return(_mm_or_ps(m, v.m));
      }

      INLINE operator SSEMask() const
      {
         SSEMask out(m);
         return(out);
      }

      __m128 m;
   };

   template <int mask> class Const <SSEPMask, mask, 1> {
      static const SSEPMask value;
public:
      INLINE static SSEPMask Value()
      {
         return(value);
      }
   };
   template <int mask> const SSEPMask Const <SSEPMask, mask, 1>::value = _mm_set1_ps(UValue(mask).f);


   class SSEPMaskNeg
   {
public:
      INLINE SSEPMaskNeg(const __m128&v) : m(v)
      {
      }

      INLINE SSEPMaskNeg operator^(const SSEPMask&v) const
      {
         return(_mm_xor_ps(m, v.m));
      }

      INLINE SSEPMask operator^(const SSEPMaskNeg&v) const
      {
         return(_mm_xor_ps(m, v.m));
      }

      INLINE SSEPMask operator!() const
      {
         return(SSEPMask(m));
      }

      INLINE SSEPMask operator&&(const SSEPMask&v) const
      {
         return(_mm_andnot_ps(m, v.m));
      }

      INLINE SSEPMaskNeg operator&&(const SSEPMaskNeg&v) const
      {
         return(_mm_or_ps(m, v.m));
      }

      INLINE SSEPMaskNeg operator||(const SSEPMaskNeg&v) const
      {
         return(_mm_and_ps(m, v.m));
      }

      INLINE SSEPMask operator||(const SSEPMask&v) const
      {
         return(_mm_or_ps(_mm_andnot_ps(m, Const <SSEPMask, 0xffffffff>::Value().m), v.m));
      }

      operator SSEPMask() const
      {
         return(_mm_andnot_ps(m, Const <SSEPMask, 0xffffffff>::Value().m));
      }

      INLINE operator SSEMask() const
      {
         SSEMask out(_mm_andnot_ps(m, Const <SSEPMask, 0xffffffff>::Value().m));
         return(out);
      }
      INLINE operator SSEMaskNeg() const
      {
         SSEMaskNeg out(m);
         return(out);
      }

      __m128 m;
   };

   INLINE SSEPMaskNeg operator!(const SSEPMask&v)
   {
      return(SSEPMaskNeg(v.m));
   }

   INLINE SSEPMaskNeg operator^(const SSEPMask&a, const SSEPMaskNeg&b)
   {
      return(_mm_xor_ps(a.m, b.m));
   }

   INLINE SSEPMask operator&&(const SSEPMask&a, const SSEPMaskNeg&b)
   {
      return(_mm_andnot_ps(b.m, a.m));
   }

   INLINE SSEPMask operator||(const SSEPMask&a, const SSEPMaskNeg&b)
   {
      return(_mm_or_ps(a.m, _mm_andnot_ps(b.m, Const <SSEPMask, 0xffffffff>::Value().m)));
   }

   INLINE bool ForAny(const SSEMask&v)
   {
      return(_mm_movemask_ps(v.m) ? 1 : 0);
   }
   INLINE bool ForAll(const SSEMask&v)
   {
      return(_mm_movemask_ps(v.m) == 15);
   }
   INLINE int ForWhich(const SSEMask&v)
   {
      return(_mm_movemask_ps(v.m));
   }

   INLINE bool ForAny(const SSEPMask&v)
   {
      return(_mm_movemask_ps(v.m) ? 1 : 0);
   }
   INLINE bool ForAll(const SSEPMask&v)
   {
      return(_mm_movemask_ps(v.m) == 15);
   }
   INLINE int ForWhich(const SSEPMask&v)
   {
      return(_mm_movemask_ps(v.m) & 1);
   }



   class SSEMask;

   class SSEReal
   {
public:
      INLINE SSEReal()
      {
      }

      INLINE SSEReal(const __m128&v) : m(v)
      {
      }

      INLINE SSEReal(float v) : m(_mm_set1_ps(v))
      {
      }

      INLINE const SSEReal&operator +=(const SSEReal&v)
      {
         m = _mm_add_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEReal&operator -=(const SSEReal&v)
      {
         m = _mm_sub_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEReal&operator *=(const SSEReal&v)
      {
         m = _mm_mul_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEReal&operator /=(const SSEReal&v)
      {
         m = _mm_div_ps(m, v.m);
         return(*this);
      }


      INLINE SSEReal operator-() const
      {
         return(_mm_sub_ps(_mm_setzero_ps(), m));
      }

      INLINE SSEReal(float a, float b, float c, float d) : m(_mm_set_ps(a, b, c, d))
      {
      } INLINE SSEReal(const float *ptr) : m(_mm_load_ps(ptr))
      {
      }

      __m128 m;
   };


   INLINE SSEMask operator ==(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_cmpeq_ps(a.m, b.m));
   }
   INLINE SSEMask operator !=(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_cmpneq_ps(a.m, b.m));
   }
   INLINE SSEMask operator <=(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_cmple_ps(a.m, b.m));
   }
   INLINE SSEMask operator >=(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_cmpge_ps(a.m, b.m));
   }
   INLINE SSEMask operator <(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_cmplt_ps(a.m, b.m));
   }
   INLINE SSEMask operator >(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_cmpgt_ps(a.m, b.m));
   }

   INLINE SSEReal operator +(const SSEReal&a, const SSEReal&b)
   {
      SSEReal out(a);
      out += b;
      return(out);
   }

   INLINE SSEReal operator -(const SSEReal&a, const SSEReal&b)
   {
      SSEReal out(a);
      out -= b;
      return(out);
   }

   INLINE SSEReal operator *(const SSEReal&a, const SSEReal&b)
   {
      SSEReal out(a);
      out *= b;
      return(out);
   }

   INLINE SSEReal operator /(const SSEReal&a, const SSEReal&b)
   {
      SSEReal out(a);
      out /= b;
      return(out);
   }

   INLINE SSEReal Sqrt(const SSEReal&v)
   {
      return(_mm_sqrt_ps(v.m));
   }
   INLINE SSEReal Inv(const SSEReal&v)
   {
      return(_mm_nrrcp_ps(v.m));
   }
   INLINE SSEReal RSqrt(const SSEReal&v)
   {
      return(_mm_nrrsqrt_ps(v.m));
   }
   INLINE SSEReal FastInv(const SSEReal&v)
   {
      return(_mm_rcp_ps(v.m));
   }
   INLINE SSEReal FastRSqrt(const SSEReal&v)
   {
      return(_mm_rsqrt_ps(v.m));
   }



   template <int m, int n> class Const <SSEReal, m, n> {
public:
      INLINE static SSEReal Value()
      {
         return(SSEReal(Const <__m128, m, n>::Value()));
      }
   };

   INLINE SSEReal Abs(const SSEReal&v)
   {
      return(_mm_and_ps(Const <SSEMask, 0x7fffffff>::Value().m, v.m));
   }

   INLINE SSEReal Min(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_min_ps(a.m, b.m));
   }

   INLINE SSEReal Max(const SSEReal&a, const SSEReal&b)
   {
      return(_mm_max_ps(a.m, b.m));
   }

   INLINE int SignMask(const SSEReal&v)
   {
      return(_mm_movemask_ps(v.m));
   }

   INLINE SSEReal Condition(const SSEMask&test, const SSEReal&v1, const SSEReal&v2)
   {
      return(_mm_or_ps(_mm_and_ps(test.m, v1.m), _mm_andnot_ps(test.m, v2.m)));
   }

   INLINE SSEReal Condition(const SSEMaskNeg&test, const SSEReal&v1, const SSEReal&v2)
   {
      return(_mm_or_ps(_mm_andnot_ps(test.m, v1.m), _mm_and_ps(test.m, v2.m)));
   }

   INLINE SSEReal Condition(const SSEMask&test, const SSEReal&v1)
   {
      return(_mm_and_ps(test.m, v1.m));
   }

   INLINE SSEReal Condition(const SSEMaskNeg&test, const SSEReal&v1)
   {
      return(_mm_andnot_ps(test.m, v1.m));
   }

   class SSEPMask;

   class SSEPReal
   {
public:
      INLINE SSEPReal()
      {
      }

      INLINE SSEPReal(const __m128&v) : m(v)
      {
      }

      INLINE SSEPReal(float v) : m(_mm_set1_ps(v))
      {
      }

      INLINE const SSEPReal&operator +=(const SSEPReal&v)
      {
         m = _mm_add_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPReal&operator -=(const SSEPReal&v)
      {
         m = _mm_sub_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPReal&operator *=(const SSEPReal&v)
      {
         m = _mm_mul_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPReal&operator /=(const SSEPReal&v)
      {
         m = _mm_div_ps(m, v.m);
         return(*this);
      }


      INLINE SSEPReal operator-() const
      {
         return(_mm_sub_ps(_mm_setzero_ps(), m));
      }

      operator SSEReal() const
      {
         SSEReal out;
         out.m = m;
         return(out);
      }

      __m128 m;
   };


   INLINE SSEPMask operator ==(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_cmpeq_ps(a.m, b.m));
   }
   INLINE SSEPMask operator !=(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_cmpneq_ps(a.m, b.m));
   }
   INLINE SSEPMask operator <=(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_cmple_ps(a.m, b.m));
   }
   INLINE SSEPMask operator >=(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_cmpge_ps(a.m, b.m));
   }
   INLINE SSEPMask operator <(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_cmplt_ps(a.m, b.m));
   }
   INLINE SSEPMask operator >(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_cmpgt_ps(a.m, b.m));
   }

   INLINE SSEPReal operator +(const SSEPReal&a, const SSEPReal&b)
   {
      SSEPReal out(a);
      out += b;
      return(out);
   }

   INLINE SSEPReal operator -(const SSEPReal&a, const SSEPReal&b)
   {
      SSEPReal out(a);
      out -= b;
      return(out);
   }

   INLINE SSEPReal operator *(const SSEPReal&a, const SSEPReal&b)
   {
      SSEPReal out(a);
      out *= b;
      return(out);
   }

   INLINE SSEPReal operator /(const SSEPReal&a, const SSEPReal&b)
   {
      SSEPReal out(a);
      out /= b;
      return(out);
   }

   INLINE SSEPReal Sqrt(const SSEPReal&v)
   {
      return(_mm_sqrt_ps(v.m));
   }
   INLINE SSEPReal Inv(const SSEPReal&v)
   {
      return(_mm_nrrcp_ps(v.m));
   }
   INLINE SSEPReal RSqrt(const SSEPReal&v)
   {
      return(_mm_nrrsqrt_ps(v.m));
   }
   INLINE SSEPReal FastInv(const SSEPReal&v)
   {
      return(_mm_rcp_ps(v.m));
   }
   INLINE SSEPReal FastRSqrt(const SSEPReal&v)
   {
      return(_mm_rsqrt_ps(v.m));
   }



   template <int m, int n> class Const <SSEPReal, m, n> {
public:
      INLINE static SSEPReal Value()
      {
         return(SSEPReal(Const <__m128, m, n>::Value()));
      }
   };

   INLINE SSEPReal Abs(const SSEPReal&v)
   {
      return(_mm_and_ps(Const <SSEPMask, 0x7fffffff>::Value().m, v.m));
   }

   INLINE SSEPReal Min(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_min_ps(a.m, b.m));
   }

   INLINE SSEPReal Max(const SSEPReal&a, const SSEPReal&b)
   {
      return(_mm_max_ps(a.m, b.m));
   }

   INLINE int SignMask(const SSEPReal&v)
   {
      return(_mm_movemask_ps(v.m));
   }

   INLINE SSEPReal Condition(const SSEPMask&test, const SSEPReal&v1, const SSEPReal&v2)
   {
      return(_mm_or_ps(_mm_and_ps(test.m, v1.m), _mm_andnot_ps(test.m, v2.m)));
   }

   INLINE SSEPReal Condition(const SSEPMaskNeg&test, const SSEPReal&v1, const SSEPReal&v2)
   {
      return(_mm_or_ps(_mm_andnot_ps(test.m, v1.m), _mm_and_ps(test.m, v2.m)));
   }

   INLINE SSEPReal Condition(const SSEPMask&test, const SSEPReal&v1)
   {
      return(_mm_and_ps(test.m, v1.m));
   }

   INLINE SSEPReal Condition(const SSEPMaskNeg&test, const SSEPReal&v1)
   {
      return(_mm_andnot_ps(test.m, v1.m));
   }

   template <>
   struct ScalarInfo <SSEReal>
   {
      enum {
         Multiplicity = 4
      };
      typedef SSEMask   TBool;

      INLINE static SSEMask ElementMask(int n)
      {
         static SSEMask elems[4] =
         {
            SSEMask(_mm_set_ps(UValue(0).f,          UValue(0).f,          UValue(0).f,          UValue(0xffffffff).f)),
            SSEMask(_mm_set_ps(UValue(0).f,          UValue(0).f,          UValue(0xffffffff).f, UValue(0).f)),
            SSEMask(_mm_set_ps(UValue(0).f,          UValue(0xffffffff).f, UValue(0).f,          UValue(0).f)),
            SSEMask(_mm_set_ps(UValue(0xffffffff).f, UValue(0).f,          UValue(0).f,          UValue(0).f)),
         };

         return(elems[n]);
      }
   };

   template <>
   struct ScalarInfo <SSEPReal>
   {
      enum {
         Multiplicity = 1
      };
      typedef SSEPMask   TBool;

      INLINE static SSEPMask ElementMask(int n)
      {
         return(Const <SSEPMask, 0xffffffff>::Value());
      }
   };

   INLINE void Broadcast(const float&in, SSEReal&out)
   {
      out = _mm_load1(in);
   }

   INLINE void Convert(const float in[4], SSEReal&out)
   {
      out = _mm_load4(in);
   }

   INLINE void Convert(const SSEReal&in, float out[4])
   {
      _mm_store4(in.m, out);
   }

   INLINE void Convert(float inX, float inY, float inZ, float inW, SSEReal&out)
   {
      out = _mm_set_ps(inW, inZ, inY, inX);
   }

   INLINE void Convert(const SSEReal&in, float&outX, float&outY, float&outZ, float&outW)
   {
      _mm_store_ss(&outX, in.m);
      _mm_store_ss(&outY, _mm_shuffle_ <1>(in.m));
      _mm_store_ss(&outZ, _mm_shuffle_ <2>(in.m));
      _mm_store_ss(&outW, _mm_shuffle_ <3>(in.m));
   }

   INLINE void Convert(const float&in, SSEPReal&out)
   {
      out = _mm_load1(in);
   }

   INLINE void Convert(const SSEPReal&in, float&out)
   {
      _mm_store_ss(&out, in.m);
   }

   template <class base> class Vec3;
   template <class base> class Vec4;

   template <class base>
   class Vec2 {
public:
      typedef base                                TScalar;
      typedef typename ScalarInfo <base>::TBool   TBool;

      INLINE Vec2()
      {
      }

      INLINE Vec2(const base&t) : x(t), y(t)
      {
      }

      INLINE Vec2(const base arr[2]) : x(arr[0]), y(arr[1])
      {
      }

      INLINE Vec2(const base&tx, const base&ty) : x(tx), y(ty)
      {
      }

      explicit INLINE Vec2(const Vec3 <base>&);
      explicit INLINE Vec2(const Vec4 <base>&);


      template <class GenericVec3> INLINE const Vec2&operator +=(const GenericVec3&v)
      {
         x += v.X();
         y += v.Y();
         return(*this);
      }
      template <class GenericVec3> INLINE const Vec2&operator -=(const GenericVec3&v)
      {
         x -= v.X();
         y -= v.Y();
         return(*this);
      }
      template <class GenericVec3> INLINE const Vec2&operator *=(const GenericVec3&v)
      {
         x *= v.X();
         y *= v.Y();
         return(*this);
      }
      template <class GenericVec3> INLINE const Vec2&operator /=(const GenericVec3&v)
      {
         x /= v.X();
         y /= v.Y();
         return(*this);
      }


      INLINE const Vec2&operator*=(const base&s)
      {
         x *= s;
         y *= s;
         return(*this);
      }

      INLINE const Vec2&operator/=(const base&s)
      {
         base inv = Const <base, 1>::Value() / s;

         x *= inv;
         y *= inv;
         return(*this);
      }

      INLINE Vec2 operator-() const
      {
         Vec2 out;

         out.x = -x;
         out.y = -y;
         return(out);
      }

      INLINE base& X()
      {
         return(x);
      }
      INLINE base& Y()
      {
         return(y);
      }
      INLINE const base& X() const
      {
         return(x);
      }
      INLINE const base& Y() const
      {
         return(y);
      }



      base x, y;
   };


   template <class base>
   Vec2 <base>::Vec2(const Vec3 <base>&v) : x(v.X()), y(v.Y())
   {
   }

   template <class base>
   Vec2 <base>::Vec2(const Vec4 <base>&v) : x(v.X()), y(v.Y())
   {
   }

   template <class base, class GenericVec> INLINE Vec2 <base> operator +(const Vec2 <base>&a, const GenericVec&b)
   {
      Vec2 <base> out(a);
      out += b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec2 <base> operator -(const Vec2 <base>&a, const GenericVec&b)
   {
      Vec2 <base> out(a);
      out -= b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec2 <base> operator *(const Vec2 <base>&a, const GenericVec&b)
   {
      Vec2 <base> out(a);
      out *= b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec2 <base> operator /(const Vec2 <base>&a, const GenericVec&b)
   {
      Vec2 <base> out(a);
      out /= b;
      return(out);
   }

   template <class base> INLINE Vec2 <base> operator *(const Vec2 <base>&a, const base&s)
   {
      Vec2 <base> out(a);
      out *= s;
      return(out);
   }
   template <class base> INLINE Vec2 <base> operator /(const Vec2 <base>&a, const base&s)
   {
      Vec2 <base> out(a);
      out /= s;
      return(out);
   }


   template <class base, class GenericVec>
   INLINE base operator|(const Vec2 <base>&a, const GenericVec&b)
   {
      base out = a.X() * b.X() + a.Y() * b.Y();

      return(out);
   }

   template <class base>
   INLINE base Sum(const Vec2 <base>&v)
   {
      base out = v.X() + v.Y();

      return(out);
   }

   template <class base> INLINE Vec2 <base> Inv(const Vec2 <base>&v)
   {
      Vec2 <base> out;
      out.X() = Inv(v.X());
      out.Y() = Inv(v.Y());
      return(out);
   }
   template <class base> INLINE Vec2 <base> Sqrt(const Vec2 <base>&v)
   {
      Vec2 <base> out;
      out.X() = Sqrt(v.X());
      out.Y() = Sqrt(v.Y());
      return(out);
   }
   template <class base> INLINE Vec2 <base> RSqrt(const Vec2 <base>&v)
   {
      Vec2 <base> out;
      out.X() = RSqrt(v.X());
      out.Y() = RSqrt(v.Y());
      return(out);
   }
   template <class base> INLINE Vec2 <base> Abs(const Vec2 <base>&v)
   {
      Vec2 <base> out;
      out.X() = Abs(v.X());
      out.Y() = Abs(v.Y());
      return(out);
   }
   template <class base> INLINE Vec2 <base> FastInv(const Vec2 <base>&v)
   {
      Vec2 <base> out;
      out.X() = FastInv(v.X());
      out.Y() = FastInv(v.Y());
      return(out);
   }
   template <class base> INLINE Vec2 <base> FastRSqrt(const Vec2 <base>&v)
   {
      Vec2 <base> out;
      out.X() = FastRSqrt(v.X());
      out.Y() = FastRSqrt(v.Y());
      return(out);
   }

   template <class base> INLINE Vec2 <base> Max(const Vec2 <base>&a, const Vec2 <base>&b)
   {
      Vec2 <base> out;
      out.X() = Max(a.X(), b.X());
      out.Y() = Max(a.Y(), b.Y());
      return(out);
   }
   template <class base> INLINE Vec2 <base> Min(const Vec2 <base>&a, const Vec2 <base>&b)
   {
      Vec2 <base> out;
      out.X() = Min(a.X(), b.X());
      out.Y() = Min(a.Y(), b.Y());
      return(out);
   }


   template <class base>
   base Length(const Vec2 <base>&v)
   {
      return(Sqrt(v | v));
   }

   template <class base>
   INLINE Vec2 <base> Condition(bool expr, const Vec2 <base>&a, const Vec2 <base>&b)
   {
      return(expr ? a : b);
   }

   template <class base>
   INLINE Vec2 <base> Condition(bool expr, const Vec2 <base>&v)
   {
      return(expr ? v : Vec2 <base>(Const <base, 0>::Value()));
   }

   template <class base>
   INLINE void Convert(const Vec2 <base>&in, Vec2 <base>&out)
   {
      out = in;
   }

   template <class base> class Vec4;

   template <class base>
   class Vec3 {
public:
      typedef base                                TScalar;
      typedef typename ScalarInfo <base>::TBool   TBool;

      INLINE Vec3()
      {
      }

      INLINE Vec3(const base&t) : x(t), y(t), z(t)
      {
      }

      INLINE Vec3(const base arr[3]) : x(arr[0]), y(arr[1]), z(arr[2])
      {
      }

      INLINE Vec3(const base&tx, const base&ty, const base&tz) : x(tx), y(ty), z(tz)
      {
      }

      explicit INLINE Vec3(const Vec2 <base>&v) : x(v.X()), y(v.Y()), z(Const <base, 0>::Value())
      {
      }

      explicit INLINE Vec3(const Vec4 <base>&);


      template <class GenericVec3> INLINE const Vec3&operator +=(const GenericVec3&v)
      {
         x += v.X();
         y += v.Y();
         z += v.Z();
         return(*this);
      }
      template <class GenericVec3> INLINE const Vec3&operator -=(const GenericVec3&v)
      {
         x -= v.X();
         y -= v.Y();
         z -= v.Z();
         return(*this);
      }
      template <class GenericVec3> INLINE const Vec3&operator *=(const GenericVec3&v)
      {
         x *= v.X();
         y *= v.Y();
         z *= v.Z();
         return(*this);
      }
      template <class GenericVec3> INLINE const Vec3&operator /=(const GenericVec3&v)
      {
         x /= v.X();
         y /= v.Y();
         z /= v.Z();
         return(*this);
      }


      INLINE const Vec3&operator*=(const base&s)
      {
         x *= s;
         y *= s;
         z *= s;
         return(*this);
      }

      INLINE const Vec3&operator/=(const base&s)
      {
         base inv = Const <base, 1>::Value() / s;

         x *= inv;
         y *= inv;
         z *= inv;
         return(*this);
      }

      INLINE Vec3 operator-() const
      {
         Vec3 out;

         out.x = -x;
         out.y = -y;
         out.z = -z;
         return(out);
      }

      INLINE base& X()
      {
         return(x);
      }
      INLINE base& Y()
      {
         return(y);
      }
      INLINE base& Z()
      {
         return(z);
      }
      INLINE const base& X() const
      {
         return(x);
      }
      INLINE const base& Y() const
      {
         return(y);
      }
      INLINE const base& Z() const
      {
         return(z);
      }



      base x, y, z;
   };


   template <class base>
   Vec3 <base>::Vec3(const Vec4 <base>&v) : x(v.X()), y(v.Y()), z(v.Z())
   {
   }

   template <class base, class GenericVec> INLINE Vec3 <base> operator +(const Vec3 <base>&a, const GenericVec&b)
   {
      Vec3 <base> out(a);
      out += b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec3 <base> operator -(const Vec3 <base>&a, const GenericVec&b)
   {
      Vec3 <base> out(a);
      out -= b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec3 <base> operator *(const Vec3 <base>&a, const GenericVec&b)
   {
      Vec3 <base> out(a);
      out *= b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec3 <base> operator /(const Vec3 <base>&a, const GenericVec&b)
   {
      Vec3 <base> out(a);
      out /= b;
      return(out);
   }

   template <class base> INLINE Vec3 <base> operator *(const Vec3 <base>&a, const base&s)
   {
      Vec3 <base> out(a);
      out *= s;
      return(out);
   }
   template <class base> INLINE Vec3 <base> operator /(const Vec3 <base>&a, const base&s)
   {
      Vec3 <base> out(a);
      out /= s;
      return(out);
   }


   template <class base, class GenericVec>
   INLINE base operator|(const Vec3 <base>&a, const GenericVec&b)
   {
      base out = a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z();

      return(out);
   }

   template <class base>
   INLINE base Sum(const Vec3 <base>&v)
   {
      base out = v.X() + v.Y() + v.Z();

      return(out);
   }

   template <class base, class GenericVec>
   INLINE Vec3 <base> operator^(const Vec3 <base>&b, const GenericVec&c)
   {
      Vec3 <base> out;
      out.X() = b.Y() * c.Z() - b.Z() * c.Y();
      out.Y() = b.Z() * c.X() - b.X() * c.Z();
      out.Z() = b.X() * c.Y() - b.Y() * c.X();
      return(out);
   }

   template <class base> INLINE Vec3 <base> Inv(const Vec3 <base>&v)
   {
      Vec3 <base> out;
      out.X() = Inv(v.X());
      out.Y() = Inv(v.Y());
      out.Z() = Inv(v.Z());
      return(out);
   }
   template <class base> INLINE Vec3 <base> Sqrt(const Vec3 <base>&v)
   {
      Vec3 <base> out;
      out.X() = Sqrt(v.X());
      out.Y() = Sqrt(v.Y());
      out.Z() = Sqrt(v.Z());
      return(out);
   }
   template <class base> INLINE Vec3 <base> RSqrt(const Vec3 <base>&v)
   {
      Vec3 <base> out;
      out.X() = RSqrt(v.X());
      out.Y() = RSqrt(v.Y());
      out.Z() = RSqrt(v.Z());
      return(out);
   }
   template <class base> INLINE Vec3 <base> Abs(const Vec3 <base>&v)
   {
      Vec3 <base> out;
      out.X() = Abs(v.X());
      out.Y() = Abs(v.Y());
      out.Z() = Abs(v.Z());
      return(out);
   }
   template <class base> INLINE Vec3 <base> FastInv(const Vec3 <base>&v)
   {
      Vec3 <base> out;
      out.X() = FastInv(v.X());
      out.Y() = FastInv(v.Y());
      out.Z() = FastInv(v.Z());
      return(out);
   }
   template <class base> INLINE Vec3 <base> FastRSqrt(const Vec3 <base>&v)
   {
      Vec3 <base> out;
      out.X() = FastRSqrt(v.X());
      out.Y() = FastRSqrt(v.Y());
      out.Z() = FastRSqrt(v.Z());
      return(out);
   }

   template <class base> INLINE Vec3 <base> Max(const Vec3 <base>&a, const Vec3 <base>&b)
   {
      Vec3 <base> out;
      out.X() = Max(a.X(), b.X());
      out.Y() = Max(a.Y(), b.Y());
      out.Z() = Max(a.Z(), b.Z());
      return(out);
   }
   template <class base> INLINE Vec3 <base> Min(const Vec3 <base>&a, const Vec3 <base>&b)
   {
      Vec3 <base> out;
      out.X() = Min(a.X(), b.X());
      out.Y() = Min(a.Y(), b.Y());
      out.Z() = Min(a.Z(), b.Z());
      return(out);
   }


   template <class base>
   base Length(const Vec3 <base>&v)
   {
      return(Sqrt(v | v));
   }

   template <class base>
   INLINE Vec3 <base> Condition(bool expr, const Vec3 <base>&a, const Vec3 <base>&b)
   {
      return(expr ? a : b);
   }

   template <class base>
   INLINE Vec3 <base> Condition(bool expr, const Vec3 <base>&v)
   {
      return(expr ? v : Vec3 <base>(Const <base, 0>::Value()));
   }

   template <class base>
   INLINE void Convert(const Vec3 <base>&in, Vec3 <base>&out)
   {
      out = in;
   }

   template <class base>
   class Vec4 {
public:
      typedef base                                TScalar;
      typedef typename ScalarInfo <base>::TBool   TBool;

      INLINE Vec4()
      {
      }

      INLINE Vec4(const base&t) : x(t), y(t), z(t), w(t)
      {
      }

      INLINE Vec4(const base arr[4]) : x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3])
      {
      }

      INLINE Vec4(const base&tx, const base&ty, const base&tz, const base&tw) : x(tx), y(ty), z(tz), w(tw)
      {
      }

      explicit INLINE Vec4(const Vec2 <base>&v) : x(v.X()), y(v.Y()), z(Const <base, 0>::Value()), w(Const <base, 0>::Value())
      {
      }

      explicit INLINE Vec4(const Vec3 <base>&v) : x(v.X()), y(v.Y()), z(v.Z()), w(Const <base, 0>::Value())
      {
      }

      template <class GenericVec> INLINE const Vec4&operator +=(const GenericVec&v)
      {
         x += v.X();
         y += v.Y();
         z += v.Z();
         w += v.W();
         return(*this);
      }
      template <class GenericVec> INLINE const Vec4&operator -=(const GenericVec&v)
      {
         x -= v.X();
         y -= v.Y();
         z -= v.Z();
         w -= v.W();
         return(*this);
      }
      template <class GenericVec> INLINE const Vec4&operator *=(const GenericVec&v)
      {
         x *= v.X();
         y *= v.Y();
         z *= v.Z();
         w *= v.W();
         return(*this);
      }
      template <class GenericVec> INLINE const Vec4&operator /=(const GenericVec&v)
      {
         x /= v.X();
         y /= v.Y();
         z /= v.Z();
         w /= v.W();
         return(*this);
      }


      INLINE const Vec4&operator*=(const base&s)
      {
         x *= s;
         y *= s;
         z *= s;
         w *= s;
         return(*this);
      }

      INLINE const Vec4&operator/=(const base&s)
      {
         base inv = Const <base, 1>::Value() / s;

         x *= inv;
         y *= inv;
         z *= inv;
         w *= inv;
         return(*this);
      }

      INLINE Vec4 operator-() const
      {
         Vec4 out;

         out.x = -x;
         out.y = -y;
         out.z = -z;
         out.w = -w;
         return(out);
      }

      INLINE base& X()
      {
         return(x);
      }
      INLINE base& Y()
      {
         return(y);
      }
      INLINE base& Z()
      {
         return(z);
      }
      INLINE base& W()
      {
         return(w);
      }
      INLINE const base& X() const
      {
         return(x);
      }
      INLINE const base& Y() const
      {
         return(y);
      }
      INLINE const base& Z() const
      {
         return(z);
      }
      INLINE const base& W() const
      {
         return(w);
      }


      base x, y, z, w;
   };


   template <class base, class GenericVec> INLINE Vec4 <base> operator +(const Vec4 <base>&a, const GenericVec&b)
   {
      Vec4 <base> out(a);
      out += b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec4 <base> operator -(const Vec4 <base>&a, const GenericVec&b)
   {
      Vec4 <base> out(a);
      out -= b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec4 <base> operator *(const Vec4 <base>&a, const GenericVec&b)
   {
      Vec4 <base> out(a);
      out *= b;
      return(out);
   }
   template <class base, class GenericVec> INLINE Vec4 <base> operator /(const Vec4 <base>&a, const GenericVec&b)
   {
      Vec4 <base> out(a);
      out /= b;
      return(out);
   }

   template <class base> INLINE Vec4 <base> operator *(const Vec4 <base>&a, const base&s)
   {
      Vec4 <base> out(a);
      out *= s;
      return(out);
   }
   template <class base> INLINE Vec4 <base> operator /(const Vec4 <base>&a, const base&s)
   {
      Vec4 <base> out(a);
      out /= s;
      return(out);
   }


   template <class base, class GenericVec>
   INLINE base operator|(const Vec4 <base>&a, const GenericVec&b)
   {
      base out = a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z() + a.W() * b.W();

      return(out);
   }

   template <class base>
   INLINE base Sum(const Vec4 <base>&v)
   {
      base out = v.X() + v.Y() + v.Z() + v.W();

      return(out);
   }

   template <class base> INLINE Vec4 <base> Inv(const Vec4 <base>&v)
   {
      Vec4 <base> out;
      out.X() = Inv(v.X());
      out.Y() = Inv(v.Y());
      out.Z() = Inv(v.Z());
      out.W() = Inv(v.W());
      return(out);
   }
   template <class base> INLINE Vec4 <base> Sqrt(const Vec4 <base>&v)
   {
      Vec4 <base> out;
      out.X() = Sqrt(v.X());
      out.Y() = Sqrt(v.Y());
      out.Z() = Sqrt(v.Z());
      out.W() = Sqrt(v.W());
      return(out);
   }
   template <class base> INLINE Vec4 <base> RSqrt(const Vec4 <base>&v)
   {
      Vec4 <base> out;
      out.X() = RSqrt(v.X());
      out.Y() = RSqrt(v.Y());
      out.Z() = RSqrt(v.Z());
      out.W() = RSqrt(v.W());
      return(out);
   }
   template <class base> INLINE Vec4 <base> Abs(const Vec4 <base>&v)
   {
      Vec4 <base> out;
      out.X() = Abs(v.X());
      out.Y() = Abs(v.Y());
      out.Z() = Abs(v.Z());
      out.W() = Abs(v.W());
      return(out);
   }
   template <class base> INLINE Vec4 <base> FastInv(const Vec4 <base>&v)
   {
      Vec4 <base> out;
      out.X() = FastInv(v.X());
      out.Y() = FastInv(v.Y());
      out.Z() = FastInv(v.Z());
      out.W() = FastInv(v.W());
      return(out);
   }
   template <class base> INLINE Vec4 <base> FastRSqrt(const Vec4 <base>&v)
   {
      Vec4 <base> out;
      out.X() = FastRSqrt(v.X());
      out.Y() = FastRSqrt(v.Y());
      out.Z() = FastRSqrt(v.Z());
      out.W() = FastRSqrt(v.W());
      return(out);
   }

   template <class base> INLINE Vec4 <base> Max(const Vec4 <base>&a, const Vec4 <base>&b)
   {
      Vec4 <base> out;
      out.X() = Max(a.X(), b.X());
      out.Y() = Max(a.Y(), b.Y());
      out.Z() = Max(a.Z(), b.Z());
      out.W() = Max(a.W(), b.W());
      return(out);
   }
   template <class base> INLINE Vec4 <base> Min(const Vec4 <base>&a, const Vec4 <base>&b)
   {
      Vec4 <base> out;
      out.X() = Min(a.X(), b.X());
      out.Y() = Min(a.Y(), b.Y());
      out.Z() = Min(a.Z(), b.Z());
      out.W() = Min(a.W(), b.W());
      return(out);
   }


   template <class base>
   base Length(const Vec4 <base>&v)
   {
      return(Sqrt(v | v));
   }

   template <class base>
   INLINE Vec4 <base> Condition(bool expr, const Vec4 <base>&a, const Vec4 <base>&b)
   {
      return(expr ? a : b);
   }

   template <class base>
   INLINE Vec4 <base> Condition(bool expr, const Vec4 <base>&v)
   {
      return(expr ? v : Vec4 <base>(Const <base, 0>::Value()));
   }

   template <class base>
   INLINE void Convert(const Vec4 <base>&in, Vec4 <base>&out)
   {
      out = in;
   }

   typedef Vec2 <SSEReal>   SSEVec2;
   typedef Vec3 <SSEReal>   SSEVec3;
   typedef Vec4 <SSEReal>   SSEVec4;

   INLINE SSEVec2 Condition(const SSEMask&test, const SSEVec2&v1, const SSEVec2&v2)
   {
      SSEVec2 out;

      out.X() = Condition(test, v1.X(), v2.X());
      out.Y() = Condition(test, v1.Y(), v2.Y());
      return(out);
   }

   INLINE SSEVec2 Condition(const SSEMaskNeg&test, const SSEVec2&v1, const SSEVec2&v2)
   {
      SSEVec2 out;

      out.X() = Condition(test, v1.X(), v2.X());
      out.Y() = Condition(test, v1.Y(), v2.Y());
      return(out);
   }

   INLINE SSEVec2 Condition(const SSEMask&test, const SSEVec2&v1)
   {
      SSEVec2 out;

      out.X() = Condition(test, v1.X());
      out.Y() = Condition(test, v1.Y());
      return(out);
   }

   INLINE SSEVec2 Condition(const SSEMaskNeg&test, const SSEVec2&v1)
   {
      SSEVec2 out;

      out.X() = Condition(test, v1.X());
      out.Y() = Condition(test, v1.Y());
      return(out);
   }

   INLINE SSEVec3 Condition(const SSEMask&test, const SSEVec3&v1, const SSEVec3&v2)
   {
      SSEVec3 out;

      out.X() = Condition(test, v1.X(), v2.X());
      out.Y() = Condition(test, v1.Y(), v2.Y());
      out.Z() = Condition(test, v1.Z(), v2.Z());
      return(out);
   }

   INLINE SSEVec3 Condition(const SSEMaskNeg&test, const SSEVec3&v1, const SSEVec3&v2)
   {
      SSEVec3 out;

      out.X() = Condition(test, v1.X(), v2.X());
      out.Y() = Condition(test, v1.Y(), v2.Y());
      out.Z() = Condition(test, v1.Z(), v2.Z());
      return(out);
   }

   INLINE SSEVec3 Condition(const SSEMask&test, const SSEVec3&v1)
   {
      SSEVec3 out;

      out.X() = Condition(test, v1.X());
      out.Y() = Condition(test, v1.Y());
      out.Z() = Condition(test, v1.Z());
      return(out);
   }

   INLINE SSEVec3 Condition(const SSEMaskNeg&test, const SSEVec3&v1)
   {
      SSEVec3 out;

      out.X() = Condition(test, v1.X());
      out.Y() = Condition(test, v1.Y());
      out.Z() = Condition(test, v1.Z());
      return(out);
   }

   INLINE SSEVec4 Condition(const SSEMask&test, const SSEVec4&v1, const SSEVec4&v2)
   {
      SSEVec4 out;

      out.X() = Condition(test, v1.X(), v2.X());
      out.Y() = Condition(test, v1.Y(), v2.Y());
      out.Z() = Condition(test, v1.Z(), v2.Z());
      out.W() = Condition(test, v1.W(), v2.W());
      return(out);
   }

   INLINE SSEVec4 Condition(const SSEMaskNeg&test, const SSEVec4&v1, const SSEVec4&v2)
   {
      SSEVec4 out;

      out.X() = Condition(test, v1.X(), v2.X());
      out.Y() = Condition(test, v1.Y(), v2.Y());
      out.Z() = Condition(test, v1.Z(), v2.Z());
      out.W() = Condition(test, v1.W(), v2.W());
      return(out);
   }

   INLINE SSEVec4 Condition(const SSEMask&test, const SSEVec4&v1)
   {
      SSEVec4 out;

      out.X() = Condition(test, v1.X());
      out.Y() = Condition(test, v1.Y());
      out.Z() = Condition(test, v1.Z());
      out.W() = Condition(test, v1.W());
      return(out);
   }

   INLINE SSEVec4 Condition(const SSEMaskNeg&test, const SSEVec4&v1)
   {
      SSEVec4 out;

      out.X() = Condition(test, v1.X());
      out.Y() = Condition(test, v1.Y());
      out.Z() = Condition(test, v1.Z());
      out.W() = Condition(test, v1.W());
      return(out);
   }

   INLINE void Broadcast(const Vec2 <float>&in, SSEVec2&out)
   {
      out = SSEVec2(SSEReal(in.X()), SSEReal(in.Y()));
   }

   INLINE void Convert(const Vec2 <float> in[4], SSEVec2&out)
   {
      Convert(in[0].X(), in[1].X(), in[2].X(), in[3].X(), out.X());
      Convert(in[0].Y(), in[1].Y(), in[2].Y(), in[3].Y(), out.Y());
   }

   INLINE void Convert(const SSEVec2&in, Vec2 <float> out[4])
   {
      Convert(in.X(), out[0].X(), out[1].X(), out[2].X(), out[3].X());
      Convert(in.Y(), out[0].Y(), out[1].Y(), out[2].Y(), out[3].Y());
   }

   INLINE void Convert(const Vec2 <float>&a, const Vec2 <float>&b, const Vec2 <float>&c, const Vec2 <float>&d, SSEVec2&out)
   {
      Convert(a.X(), b.X(), c.X(), d.X(), out.X());
      Convert(a.Y(), b.Y(), c.Y(), d.Y(), out.Y());
   }

   INLINE void Convert(const SSEVec2&in, Vec2 <float>&outA, Vec2 <float>&outB, Vec2 <float>&outC, Vec2 <float>&outD)
   {
      Convert(in.X(), outA.X(), outB.X(), outC.X(), outD.X());
      Convert(in.Y(), outA.Y(), outB.Y(), outC.Y(), outD.Y());
   }

   INLINE void Broadcast(const Vec3 <float>&in, SSEVec3&out)
   {
      out = SSEVec3(SSEReal(in.X()), SSEReal(in.Y()), SSEReal(in.Z()));
   }

   INLINE void Convert(const Vec3 <float> in[4], SSEVec3&out)
   {
      Convert(in[0].X(), in[1].X(), in[2].X(), in[3].X(), out.X());
      Convert(in[0].Y(), in[1].Y(), in[2].Y(), in[3].Y(), out.Y());
      Convert(in[0].Z(), in[1].Z(), in[2].Z(), in[3].Z(), out.Z());
   }

   INLINE void Convert(const SSEVec3&in, Vec3 <float> out[4])
   {
      Convert(in.X(), out[0].X(), out[1].X(), out[2].X(), out[3].X());
      Convert(in.Y(), out[0].Y(), out[1].Y(), out[2].Y(), out[3].Y());
      Convert(in.Z(), out[0].Z(), out[1].Z(), out[2].Z(), out[3].Z());
   }

   INLINE void Convert(const Vec3 <float>&a, const Vec3 <float>&b, const Vec3 <float>&c, const Vec3 <float>&d, SSEVec3&out)
   {
      Convert(a.X(), b.X(), c.X(), d.X(), out.X());
      Convert(a.Y(), b.Y(), c.Y(), d.Y(), out.Y());
      Convert(a.Z(), b.Z(), c.Z(), d.Z(), out.Z());
   }

   INLINE void Convert(const SSEVec3&in, Vec3 <float>&outA, Vec3 <float>&outB, Vec3 <float>&outC, Vec3 <float>&outD)
   {
      Convert(in.X(), outA.X(), outB.X(), outC.X(), outD.X());
      Convert(in.Y(), outA.Y(), outB.Y(), outC.Y(), outD.Y());
      Convert(in.Z(), outA.Z(), outB.Z(), outC.Z(), outD.Z());
   }

   INLINE void Broadcast(const Vec4 <float>&in, SSEVec4&out)
   {
      out = SSEVec4(SSEReal(in.X()), SSEReal(in.Y()), SSEReal(in.Z()), SSEReal(in.W()));
   }

   INLINE void Convert(const Vec4 <float> in[4], SSEVec4&out)
   {
      Convert(in[0].X(), in[1].X(), in[2].X(), in[3].X(), out.X());
      Convert(in[0].Y(), in[1].Y(), in[2].Y(), in[3].Y(), out.Y());
      Convert(in[0].Z(), in[1].Z(), in[2].Z(), in[3].Z(), out.Z());
      Convert(in[0].W(), in[1].W(), in[2].W(), in[3].W(), out.W());
   }

   INLINE void Convert(const SSEVec4&in, Vec4 <float> out[4])
   {
      Convert(in.X(), out[0].X(), out[1].X(), out[2].X(), out[3].X());
      Convert(in.Y(), out[0].Y(), out[1].Y(), out[2].Y(), out[3].Y());
      Convert(in.Z(), out[0].Z(), out[1].Z(), out[2].Z(), out[3].Z());
      Convert(in.W(), out[0].W(), out[1].W(), out[2].W(), out[3].W());
   }

   INLINE void Convert(const Vec4 <float>&a, const Vec4 <float>&b, const Vec4 <float>&c, const Vec4 <float>&d, SSEVec4&out)
   {
      Convert(a.X(), b.X(), c.X(), d.X(), out.X());
      Convert(a.Y(), b.Y(), c.Y(), d.Y(), out.Y());
      Convert(a.Z(), b.Z(), c.Z(), d.Z(), out.Z());
      Convert(a.W(), b.W(), c.W(), d.W(), out.W());
   }

   INLINE void Convert(const SSEVec4&in, Vec4 <float>&outA, Vec4 <float>&outB, Vec4 <float>&outC, Vec4 <float>&outD)
   {
      Convert(in.X(), outA.X(), outB.X(), outC.X(), outD.X());
      Convert(in.Y(), outA.Y(), outB.Y(), outC.Y(), outD.Y());
      Convert(in.Z(), outA.Z(), outB.Z(), outC.Z(), outD.Z());
      Convert(in.W(), outA.W(), outB.W(), outC.W(), outD.W());
   }

   class SSEPVec2;
   class SSEPVec3;
   class SSEPVec4;



   class SSEPVec2 {
public:
      typedef SSEPReal   TScalar;
      typedef SSEPMask   TBool;

      INLINE SSEPVec2()
      {
      }

      INLINE SSEPVec2(const __m128&v) : m(v)
      {
      }

      INLINE SSEPVec2(const SSEPReal&v) : m(v.m)
      {
      }

      INLINE explicit SSEPVec2(const SSEPMask&v) : m(v.m)
      {
      }

      INLINE SSEPVec2 operator-() const
      {
         return(_mm_sub_ps(_mm_setzero_ps(), m));
      }

      INLINE const SSEPVec2&operator +=(const SSEPVec2&v)
      {
         m = _mm_add_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec2&operator -=(const SSEPVec2&v)
      {
         m = _mm_sub_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec2&operator *=(const SSEPVec2&v)
      {
         m = _mm_mul_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec2&operator /=(const SSEPVec2&v)
      {
         m = _mm_div_ps(m, v.m);
         return(*this);
      }


      INLINE const SSEPVec2&operator*=(const SSEPReal&s)
      {
         m = _mm_mul_ps(m, s.m);
         return(*this);
      }

      INLINE const SSEPVec2&operator/=(const SSEPReal&s)
      {
         m = _mm_div_ps(m, s.m);
         return(*this);
      }

      INLINE explicit SSEPVec2(const SSEPVec3&v);
      INLINE explicit SSEPVec2(const SSEPVec4&v);
      INLINE SSEPVec2(const SSEPReal&x, const SSEPReal&y)
      {
         m = _mm_shuffle_ < 0 + (3 << 2) + (0 << 4) + (3 << 6) > (_mm_shuffle_ps(x.m, y.m, 0));
      } INLINE SSEPReal X() const
      {
         return(_mm_shuffle_ <0>(m));
      }
      INLINE SSEPReal Y() const
      {
         return(_mm_shuffle_ < 1 + (1 << 2) + (1 << 4) + (1 << 6) > (m));
      }
      INLINE operator SSEVec2() const
      {
         SSEVec2 out;
         out = SSEVec2(X(), Y());
         return(out);
      }

      __m128 m;
   };



   INLINE SSEPVec2 Sqrt(const SSEPVec2&v)
   {
      return(_mm_sqrt_ps(v.m));
   }
   INLINE SSEPVec2 Inv(const SSEPVec2&v)
   {
      return(_mm_nrrcp_ps(v.m));
   }
   INLINE SSEPVec2 RSqrt(const SSEPVec2&v)
   {
      return(_mm_nrrsqrt_ps(v.m));
   }
   INLINE SSEPVec2 FastInv(const SSEPVec2&v)
   {
      return(_mm_rcp_ps(v.m));
   }
   INLINE SSEPVec2 FastRSqrt(const SSEPVec2&v)
   {
      return(_mm_rsqrt_ps(v.m));
   }

   INLINE SSEPVec2 Min(const SSEPVec2&a, const SSEPVec2&b)
   {
      return(_mm_min_ps(a.m, b.m));
   }
   INLINE SSEPVec2 Max(const SSEPVec2&a, const SSEPVec2&b)
   {
      return(_mm_max_ps(a.m, b.m));
   }

   INLINE SSEPVec2 operator +(const SSEPVec2&a, const SSEPVec2&b)
   {
      SSEPVec2 out(a);
      out += b;
      return(out);
   }

   INLINE SSEPVec2 operator -(const SSEPVec2&a, const SSEPVec2&b)
   {
      SSEPVec2 out(a);
      out -= b;
      return(out);
   }

   INLINE SSEPVec2 operator *(const SSEPVec2&a, const SSEPVec2&b)
   {
      SSEPVec2 out(a);
      out *= b;
      return(out);
   }

   INLINE SSEPVec2 operator /(const SSEPVec2&a, const SSEPVec2&b)
   {
      SSEPVec2 out(a);
      out /= b;
      return(out);
   }

   template <class base> INLINE SSEPVec2 operator *(const SSEPVec2&a, const SSEPReal&s)
   {
      SSEPVec2 out(a);
      out *= s;
      return(out);
   }

   template <class base> INLINE SSEPVec2 operator /(const SSEPVec2&a, const SSEPReal&s)
   {
      SSEPVec2 out(a);
      out /= s;
      return(out);
   }


   INLINE SSEPVec2 Condition(const SSEPMask&test, const SSEPVec2&v1, const SSEPVec2&v2)
   {
      return(_mm_or_ps(_mm_and_ps(test.m, v1.m), _mm_andnot_ps(test.m, v2.m)));
   }

   INLINE SSEPVec2 Condition(const SSEPMaskNeg&test, const SSEPVec2&v1, const SSEPVec2&v2)
   {
      return(_mm_or_ps(_mm_andnot_ps(test.m, v1.m), _mm_and_ps(test.m, v2.m)));
   }

   INLINE SSEPVec2 Condition(const SSEPMask&test, const SSEPVec2&v1)
   {
      return(_mm_and_ps(test.m, v1.m));
   }

   INLINE SSEPVec2 Condition(const SSEPMaskNeg&test, const SSEPVec2&v1)
   {
      return(_mm_andnot_ps(test.m, v1.m));
   }

   INLINE SSEPVec2 Abs(const SSEPVec2&v)
   {
      return(_mm_and_ps(Const <SSEPMask, 0x7fffffff>::Value().m, v.m));
   }

   class SSEPVec3 {
public:
      typedef SSEPReal   TScalar;
      typedef SSEPMask   TBool;

      INLINE SSEPVec3()
      {
      }

      INLINE SSEPVec3(const __m128&v) : m(v)
      {
      }

      INLINE SSEPVec3(const SSEPReal&v) : m(v.m)
      {
      }

      INLINE explicit SSEPVec3(const SSEPMask&v) : m(v.m)
      {
      }

      INLINE SSEPVec3 operator-() const
      {
         return(_mm_sub_ps(_mm_setzero_ps(), m));
      }

      INLINE const SSEPVec3&operator +=(const SSEPVec3&v)
      {
         m = _mm_add_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec3&operator -=(const SSEPVec3&v)
      {
         m = _mm_sub_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec3&operator *=(const SSEPVec3&v)
      {
         m = _mm_mul_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec3&operator /=(const SSEPVec3&v)
      {
         m = _mm_div_ps(m, v.m);
         return(*this);
      }


      INLINE const SSEPVec3&operator*=(const SSEPReal&s)
      {
         m = _mm_mul_ps(m, s.m);
         return(*this);
      }

      INLINE const SSEPVec3&operator/=(const SSEPReal&s)
      {
         m = _mm_div_ps(m, s.m);
         return(*this);
      }

      INLINE explicit SSEPVec3(const SSEPVec2&v);
      INLINE explicit SSEPVec3(const SSEPVec4&v);
      INLINE SSEPVec3(const SSEPReal&x, const SSEPReal&y, const SSEPReal&z)
      {
         m = _mm_shuffle_ps(_mm_shuffle_ps(x.m, y.m, 0), z.m, 0 + (2 << 2) + (0 << 4) + (0 << 6));
      } INLINE SSEPReal X() const
      {
         return(_mm_shuffle_ <0>(m));
      }
      INLINE SSEPReal Y() const
      {
         return(_mm_shuffle_ < 1 + (1 << 2) + (1 << 4) + (1 << 6) > (m));
      }
      INLINE SSEPReal Z() const
      {
         return(_mm_shuffle_ < 2 + (2 << 2) + (2 << 4) + (2 << 6) > (m));
      }
      INLINE operator SSEVec3() const
      {
         SSEVec3 out;
         out = SSEVec3(X(), Y(), Z());
         return(out);
      }

      __m128 m;
   };



   INLINE SSEPVec3 Sqrt(const SSEPVec3&v)
   {
      return(_mm_sqrt_ps(v.m));
   }
   INLINE SSEPVec3 Inv(const SSEPVec3&v)
   {
      return(_mm_nrrcp_ps(v.m));
   }
   INLINE SSEPVec3 RSqrt(const SSEPVec3&v)
   {
      return(_mm_nrrsqrt_ps(v.m));
   }
   INLINE SSEPVec3 FastInv(const SSEPVec3&v)
   {
      return(_mm_rcp_ps(v.m));
   }
   INLINE SSEPVec3 FastRSqrt(const SSEPVec3&v)
   {
      return(_mm_rsqrt_ps(v.m));
   }

   INLINE SSEPVec3 Min(const SSEPVec3&a, const SSEPVec3&b)
   {
      return(_mm_min_ps(a.m, b.m));
   }
   INLINE SSEPVec3 Max(const SSEPVec3&a, const SSEPVec3&b)
   {
      return(_mm_max_ps(a.m, b.m));
   }

   INLINE SSEPVec3 operator +(const SSEPVec3&a, const SSEPVec3&b)
   {
      SSEPVec3 out(a);
      out += b;
      return(out);
   }

   INLINE SSEPVec3 operator -(const SSEPVec3&a, const SSEPVec3&b)
   {
      SSEPVec3 out(a);
      out -= b;
      return(out);
   }

   INLINE SSEPVec3 operator *(const SSEPVec3&a, const SSEPVec3&b)
   {
      SSEPVec3 out(a);
      out *= b;
      return(out);
   }

   INLINE SSEPVec3 operator /(const SSEPVec3&a, const SSEPVec3&b)
   {
      SSEPVec3 out(a);
      out /= b;
      return(out);
   }

   template <class base> INLINE SSEPVec3 operator *(const SSEPVec3&a, const SSEPReal&s)
   {
      SSEPVec3 out(a);
      out *= s;
      return(out);
   }

   template <class base> INLINE SSEPVec3 operator /(const SSEPVec3&a, const SSEPReal&s)
   {
      SSEPVec3 out(a);
      out /= s;
      return(out);
   }


   INLINE SSEPVec3 Condition(const SSEPMask&test, const SSEPVec3&v1, const SSEPVec3&v2)
   {
      return(_mm_or_ps(_mm_and_ps(test.m, v1.m), _mm_andnot_ps(test.m, v2.m)));
   }

   INLINE SSEPVec3 Condition(const SSEPMaskNeg&test, const SSEPVec3&v1, const SSEPVec3&v2)
   {
      return(_mm_or_ps(_mm_andnot_ps(test.m, v1.m), _mm_and_ps(test.m, v2.m)));
   }

   INLINE SSEPVec3 Condition(const SSEPMask&test, const SSEPVec3&v1)
   {
      return(_mm_and_ps(test.m, v1.m));
   }

   INLINE SSEPVec3 Condition(const SSEPMaskNeg&test, const SSEPVec3&v1)
   {
      return(_mm_andnot_ps(test.m, v1.m));
   }

   INLINE SSEPVec3 Abs(const SSEPVec3&v)
   {
      return(_mm_and_ps(Const <SSEPMask, 0x7fffffff>::Value().m, v.m));
   }

   class SSEPVec4 {
public:
      typedef SSEPReal   TScalar;
      typedef SSEPMask   TBool;

      INLINE SSEPVec4()
      {
      }

      INLINE SSEPVec4(const __m128&v) : m(v)
      {
      }

      INLINE SSEPVec4(const SSEPReal&v) : m(v.m)
      {
      }

      INLINE explicit SSEPVec4(const SSEPMask&v) : m(v.m)
      {
      }

      INLINE SSEPVec4 operator-() const
      {
         return(_mm_sub_ps(_mm_setzero_ps(), m));
      }

      INLINE const SSEPVec4&operator +=(const SSEPVec4&v)
      {
         m = _mm_add_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec4&operator -=(const SSEPVec4&v)
      {
         m = _mm_sub_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec4&operator *=(const SSEPVec4&v)
      {
         m = _mm_mul_ps(m, v.m);
         return(*this);
      }
      INLINE const SSEPVec4&operator /=(const SSEPVec4&v)
      {
         m = _mm_div_ps(m, v.m);
         return(*this);
      }


      INLINE const SSEPVec4&operator*=(const SSEPReal&s)
      {
         m = _mm_mul_ps(m, s.m);
         return(*this);
      }

      INLINE const SSEPVec4&operator/=(const SSEPReal&s)
      {
         m = _mm_div_ps(m, s.m);
         return(*this);
      }

      INLINE explicit SSEPVec4(const SSEPVec2&v)
      {
         m = _mm_shuffle_ps(v.m, _mm_setzero_ps(), 0 + (1 << 2));
      } INLINE explicit SSEPVec4(const SSEPVec3&v)
      {
         __m128 zzww = _mm_shuffle_ps(v.m, _mm_setzero_ps(), 0);
         m = _mm_shuffle_ps(v.m, zzww, 0 + (1 << 2) + (0 << 4) + (2 << 6));
      } INLINE SSEPVec4(const SSEPReal&x, const SSEPReal&y, const SSEPReal&z, const SSEPReal&w)
      {
         __m128 xy = _mm_shuffle_ps(x.m, y.m, 0), zw = _mm_shuffle_ps(z.m, w.m, 0);
         m = _mm_shuffle_ps(xy, zw, 0 + (2 << 2) + (0 << 4) + (2 << 6));
      } INLINE SSEPReal X() const
      {
         return(_mm_shuffle_ <0>(m));
      }
      INLINE SSEPReal Y() const
      {
         return(_mm_shuffle_ < 1 + (1 << 2) + (1 << 4) + (1 << 6) > (m));
      }
      INLINE SSEPReal Z() const
      {
         return(_mm_shuffle_ < 2 + (2 << 2) + (2 << 4) + (2 << 6) > (m));
      }
      INLINE SSEPReal W() const
      {
         return(_mm_shuffle_ < 3 + (3 << 2) + (3 << 4) + (3 << 6) > (m));
      }
      INLINE operator SSEVec4() const
      {
         SSEVec4 out;
         out = SSEVec4(X(), Y(), Z(), W());
         return(out);
      }

      __m128 m;
   };



   INLINE SSEPVec4 Sqrt(const SSEPVec4&v)
   {
      return(_mm_sqrt_ps(v.m));
   }
   INLINE SSEPVec4 Inv(const SSEPVec4&v)
   {
      return(_mm_nrrcp_ps(v.m));
   }
   INLINE SSEPVec4 RSqrt(const SSEPVec4&v)
   {
      return(_mm_nrrsqrt_ps(v.m));
   }
   INLINE SSEPVec4 FastInv(const SSEPVec4&v)
   {
      return(_mm_rcp_ps(v.m));
   }
   INLINE SSEPVec4 FastRSqrt(const SSEPVec4&v)
   {
      return(_mm_rsqrt_ps(v.m));
   }

   INLINE SSEPVec4 Min(const SSEPVec4&a, const SSEPVec4&b)
   {
      return(_mm_min_ps(a.m, b.m));
   }
   INLINE SSEPVec4 Max(const SSEPVec4&a, const SSEPVec4&b)
   {
      return(_mm_max_ps(a.m, b.m));
   }

   INLINE SSEPVec4 operator +(const SSEPVec4&a, const SSEPVec4&b)
   {
      SSEPVec4 out(a);
      out += b;
      return(out);
   }

   INLINE SSEPVec4 operator -(const SSEPVec4&a, const SSEPVec4&b)
   {
      SSEPVec4 out(a);
      out -= b;
      return(out);
   }

   INLINE SSEPVec4 operator *(const SSEPVec4&a, const SSEPVec4&b)
   {
      SSEPVec4 out(a);
      out *= b;
      return(out);
   }

   INLINE SSEPVec4 operator /(const SSEPVec4&a, const SSEPVec4&b)
   {
      SSEPVec4 out(a);
      out /= b;
      return(out);
   }

   template <class base> INLINE SSEPVec4 operator *(const SSEPVec4&a, const SSEPReal&s)
   {
      SSEPVec4 out(a);
      out *= s;
      return(out);
   }

   template <class base> INLINE SSEPVec4 operator /(const SSEPVec4&a, const SSEPReal&s)
   {
      SSEPVec4 out(a);
      out /= s;
      return(out);
   }


   INLINE SSEPVec4 Condition(const SSEPMask&test, const SSEPVec4&v1, const SSEPVec4&v2)
   {
      return(_mm_or_ps(_mm_and_ps(test.m, v1.m), _mm_andnot_ps(test.m, v2.m)));
   }

   INLINE SSEPVec4 Condition(const SSEPMaskNeg&test, const SSEPVec4&v1, const SSEPVec4&v2)
   {
      return(_mm_or_ps(_mm_andnot_ps(test.m, v1.m), _mm_and_ps(test.m, v2.m)));
   }

   INLINE SSEPVec4 Condition(const SSEPMask&test, const SSEPVec4&v1)
   {
      return(_mm_and_ps(test.m, v1.m));
   }

   INLINE SSEPVec4 Condition(const SSEPMaskNeg&test, const SSEPVec4&v1)
   {
      return(_mm_andnot_ps(test.m, v1.m));
   }

   INLINE SSEPVec4 Abs(const SSEPVec4&v)
   {
      return(_mm_and_ps(Const <SSEPMask, 0x7fffffff>::Value().m, v.m));
   }

   SSEPVec3::SSEPVec3(const SSEPVec2&v)
   {
      m = _mm_shuffle_ps(v.m, _mm_setzero_ps(), 0 + (1 << 2));
   }
   SSEPVec3::SSEPVec3(const SSEPVec4&v)
   {
      m = v.m;
   }
   SSEPVec2::SSEPVec2(const SSEPVec3&v)
   {
      m = v.m;
   }
   SSEPVec2::SSEPVec2(const SSEPVec4&v)
   {
      m = v.m;
   }


   INLINE SSEPReal operator|(const SSEPVec2&a, const SSEPVec2&b)
   {
      SSEPReal out;
      __m128   t = _mm_mul_ps(a.m, b.m);

      t     = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));
      out.m = _mm_shuffle_ <0>(t);
      return(out);
   }

   INLINE SSEPReal operator|(const SSEPVec3&a, const SSEPVec3&b)
   {
      SSEPReal out;
      __m128   t = _mm_mul_ps(a.m, b.m);

      t     = _mm_add_ss(_mm_movehl_ps(t, t), _mm_add_ss(t, _mm_shuffle_ps(t, t, 1)));
      out.m = _mm_shuffle_ <0>(t);
      return(out);
   }

   INLINE SSEPReal operator|(const SSEPVec4&a, const SSEPVec4&b)
   {
      SSEPReal out;
      __m128   t = _mm_mul_ps(a.m, b.m);

      t     = _mm_add_ps(t, _mm_shuffle_ps(t, t, 0x4E));
      t     = _mm_add_ps(t, _mm_shuffle_ps(t, t, 0x11));
      out.m = t;
      return(out);
   }

   INLINE SSEPVec3 operator^(const SSEPVec3&a, const SSEPVec3&b)
   {
      SSEPVec3 out;



      __m128 a1 = _mm_shuffle_ps(a.m, a.m, 201);
      __m128 b1 = _mm_shuffle_ps(b.m, b.m, 210);
      __m128 a2 = _mm_shuffle_ps(a.m, a.m, 210);
      __m128 b2 = _mm_shuffle_ps(b.m, b.m, 201);

      out.m = _mm_sub_ps(_mm_mul_ps(a1, b1), _mm_mul_ps(a2, b2));
      ;
      return(out);
   }

   INLINE void Convert(const Vec2 <float>&v, SSEPVec2&out)
   {
      out.m = _mm_load2(&v.X());
   }
   INLINE void Convert(const float v[2], SSEPVec2&out)
   {
      out.m = _mm_load2(v + 0);
   }
   INLINE void Convert(const SSEPVec2&v, Vec2 <float>&out)
   {
      _mm_store2(v.m, &out.X());
   }
   INLINE void Convert(const SSEPVec2&v, float out[2])
   {
      _mm_store2(v.m, out + 0);
   }

   INLINE void Convert(const Vec3 <float>&v, SSEPVec3&out)
   {
      out.m = _mm_load3(&v.X());
   }
   INLINE void Convert(const float v[3], SSEPVec3&out)
   {
      out.m = _mm_load3(v + 0);
   }
   INLINE void Convert(const SSEPVec3&v, Vec3 <float>&out)
   {
      _mm_store3(v.m, &out.X());
   }
   INLINE void Convert(const SSEPVec3&v, float out[3])
   {
      _mm_store3(v.m, out + 0);
   }

   INLINE void Convert(const Vec4 <float>&v, SSEPVec4&out)
   {
      out.m = _mm_load4(&v.X());
   }
   INLINE void Convert(const float v[4], SSEPVec4&out)
   {
      out.m = _mm_load4(v + 0);
   }
   INLINE void Convert(const SSEPVec4&v, Vec4 <float>&out)
   {
      _mm_store4(v.m, &out.X());
   }
   INLINE void Convert(const SSEPVec4&v, float out[4])
   {
      _mm_store4(v.m, out + 0);
   }

   INLINE void Convert(const SSEVec3&in, SSEPVec3 out[4])
   {
      _mm_transpose(in.X().m, in.Y().m, in.Z().m, in.Z().m,
                    out[0].m, out[1].m, out[2].m, out[3].m);
   }

   INLINE void Convert(const SSEPVec3 in[4], SSEVec3&out)
   {
      __m128 tmp3, tmp2, tmp1, tmp0;

      tmp0 = _mm_shuffle_ps(in[0].m, in[1].m, 0x44);
      tmp2 = _mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
      tmp1 = _mm_shuffle_ps(in[2].m, in[3].m, 0x44);
      tmp3 = _mm_shuffle_ps(in[2].m, in[3].m, 0xEE);

      out.X().m = _mm_shuffle_ps(tmp0, tmp1, 0x88);
      out.Y().m = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
      out.Z().m = _mm_shuffle_ps(tmp2, tmp3, 0x88);
   }

   INLINE void Convert(const SSEVec4&in, SSEPVec4 out[4])
   {
      _mm_transpose(in.X().m, in.Y().m, in.Z().m, in.W().m,
                    out[0].m, out[1].m, out[2].m, out[3].m);
   }

   INLINE void Convert(const SSEPVec4 in[4], SSEVec4&out)
   {
      __m128 tmp3, tmp2, tmp1, tmp0;

      tmp0 = _mm_shuffle_ps(in[0].m, in[1].m, 0x44);
      tmp2 = _mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
      tmp1 = _mm_shuffle_ps(in[2].m, in[3].m, 0x44);
      tmp3 = _mm_shuffle_ps(in[2].m, in[3].m, 0xEE);

      out.X().m = _mm_shuffle_ps(tmp0, tmp1, 0x88);
      out.Y().m = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
      out.Z().m = _mm_shuffle_ps(tmp2, tmp3, 0x88);
      out.W().m = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
   }

   template <class vbase>
   class Matrix
   {
public:
      typedef typename vbase::TScalar   TScalar;
      typedef vbase                     TVector;

      INLINE Matrix()
      {
      }

      INLINE Matrix(const vbase&a, const vbase&b, const vbase&c, const vbase&d) : x(a), y(b), z(c), w(d)
      {
      }

      INLINE const Matrix&operator*=(const Matrix&m)
      {
         Matrix t  = Transpose(m);
         vbase  x_ = x, y_ = y, z_ = z;

         x = x_ | t.x, x_ | t.y, x_ | t.z, x_ | t.w;
         y = y_ | t.x, y_ | t.y, y_ | t.z, y_ | t.w;
         z = z_ | t.x, z_ | t.y, z_ | t.z, z_ | t.w;
         w = w | t.x, w | t.y, w | t.z, w | t.w;
         return(*this);
      }

      INLINE const Matrix&operator+=(const Matrix&m)
      {
         x += m.x;
         y += m.y;
         z += m.z;
         w += m.w;
         return(*this);
      }

      INLINE const Matrix&operator-=(const Matrix&m)
      {
         x -= m.x;
         y -= m.y;
         z -= m.z;
         w -= m.w;
         return(*this);
      }

      INLINE Matrix operator-() const
      {
         Matrix out;

         out.x = -x;
         out.y = -y;
         out.z = -z;
         out.w = -w;
         return(out);
      }

      INLINE vbase& X()
      {
         return(x);
      }
      INLINE vbase& Y()
      {
         return(y);
      }
      INLINE vbase& Z()
      {
         return(z);
      }
      INLINE vbase& W()
      {
         return(w);
      }
      INLINE const vbase& X() const
      {
         return(x);
      }
      INLINE const vbase& Y() const
      {
         return(y);
      }
      INLINE const vbase& Z() const
      {
         return(z);
      }
      INLINE const vbase& W() const
      {
         return(w);
      }

      vbase x, y, z, w;
   };

   template <class vbase>
   INLINE Matrix <vbase> operator*(const Matrix <vbase>&a, const Matrix <vbase>&b)
   {
      Matrix <vbase> out;
      out  = a;
      out *= b;
      return(out);
   }

   template <class vbase>
   INLINE Matrix <vbase> Identity()
   {
      Matrix <vbase> out;
      typename vbase::TScalar zero = Const < typename vbase::TScalar, 0 > ::Value(), one = Const < typename vbase::TScalar, 1 > ::Value();
      out.x = vbase(one, zero, zero, zero);
      out.y = vbase(zero, one, zero, zero);
      out.z = vbase(zero, zero, one, zero);
      out.w = vbase(zero, zero, zero, one);
      return(out);
   }

   template <class vbase>
   INLINE Matrix <vbase> Transpose(const Matrix <vbase>&m)
   {
      Matrix <vbase> out;
      out.x = vbase(m.x.X(), m.y.X(), m.z.X(), m.w.X());
      out.y = vbase(m.x.Y(), m.y.Y(), m.z.Y(), m.w.Y());
      out.z = vbase(m.x.Z(), m.y.Z(), m.z.Z(), m.w.Z());
      out.w = vbase(m.x.W(), m.y.W(), m.z.W(), m.w.W());
      return(out);
   }

   template <class vbase>
   INLINE Vec4 < typename vbase::TScalar > operator*(const Matrix <vbase>&m, const Vec4 < typename vbase::TScalar >&v)
   {
      Vec4 <vbase> out;
      out.X() = m.X() | v;
      out.Y() = m.Y() | v;
      out.Z() = m.Z() | v;
      out.W() = m.W() | v;
      return(out);
   }

   template <class vbase>
   INLINE Vec3 < typename vbase::TScalar > operator*(const Matrix <vbase>&m, const Vec3 < typename vbase::TScalar >&v)
   {
      Vec3 < typename vbase::TScalar > out;

      out.X() = m.X().X() * v.X() + m.X().Y() * v.Y() + m.X().Z() * v.Z();
      out.Y() = m.Y().X() * v.X() + m.Y().Y() * v.Y() + m.Y().Z() * v.Z();
      out.Z() = m.Z().X() * v.X() + m.Z().Y() * v.Y() + m.Z().Z() * v.Z();
     // out    *= Inv(Sum(m.W()));

      return(out);
   }

   template <class vbase>
   INLINE Vec2 < typename vbase::TScalar > operator*(const Matrix <vbase>&m, const Vec2 < typename vbase::TScalar >&v)
   {
      Vec2 < typename vbase::TScalar > out;

      out.X() = m.X().X() * v.X() + m.X().Y() * v.Y();
      out.Y() = m.Y().X() * v.X() + m.Y().Y() * v.Y();
      out    *= Inv(Sum(m.W()));

      return(out);
   }

   INLINE Matrix <Vec4 <float> > RotateX(float angle)
   {
      float c = cos(angle), s = sin(angle);

      Matrix <Vec4 <float> > out = Identity <Vec4 <float> >();

      out.y.Y() = c;
      out.y.Z() = s;
      out.z.Y() = -s;
      out.z.Z() = c;
      return(out);
   }

   INLINE Matrix <Vec4 <float> > RotateY(float angle)
   {
      float c = cos(angle), s = sin(angle);

      Matrix <Vec4 <float> > out = Identity <Vec4 <float> >();

      out.x.X() = c;
      out.x.Z() = s;
      out.z.X() = -s;
      out.z.Z() = c;
      return(out);
   }

   INLINE Matrix <Vec4 <float> > RotateZ(float angle)
   {
      float c = cos(angle), s = sin(angle);

      Matrix <Vec4 <float> > out = Identity <Vec4 <float> >();

      out.x.X() = c;
      out.x.Y() = -s;
      out.y.X() = s;
      out.y.Y() = c;
      return(out);
   }

   INLINE Matrix <Vec4 <float> > Rotate(float yaw, float pitch, float roll)
   {
      return(RotateZ(roll) * RotateX(pitch) * RotateY(pitch));
   }
}
