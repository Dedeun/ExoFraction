#ifndef FRACTION_HPP_INCLUDED
#define FRACTION_HPP_INCLUDED

#include <iostream>
#include <ostream>
#include <cstdint>
#include "Contract.hpp"

///  \file   Fraction.hpp
///  \brief  This file is a short mathematical Fraction library.
///          The Fraction format is Num/Den (with "num" and "den" integer 32 bits)
///  \author Dedeun
///  \date   23 sept 2015
///  \version Beta 1.3

///  \class Fraction
///  \brief This class is the mathematical fraction, with the 4 operations (+, -, *, /)
///
namespace dd {
    template<typename T>
    class Fraction {
    public:
        /// \fn    Fraction ();
        /// \brief Constructor
        /// \param Numerator and denominator (integer 32 bits)
        /// \pre   Denominator shall be not null
        /// \invariant Denominator shall be not null
        Fraction<T> (T num, T den): m_num{num}
        {
            REQUIRE((den!=0), "Constructor of Fraction with null denominator");
            if (den > 0) {
                m_den=den;
            } else {
                m_den=-den;
                m_num *=-1;
            } //end if
            reduction ();
            CHECK_INVARIANTS;
        }
        /// \fn    isEqualAs
        /// \brief compare the equality
        /// \param the Fraction to be compare
        bool isEqualAs (Fraction<T> const& f)
        {
            return ((m_num == f.m_num) & (f.m_den == m_den));
        }
        /// \fn    isGreaterThan
        /// \brief compare the size
        /// \param the Fraction to be compare
        bool isGreaterThan (Fraction<T> const& f)
        {
            return ((m_num * f.m_den) < (f.m_num * m_den));
        }
        /// \fn    +=
        /// \brief Self addition
        /// \param the Fraction to be added
        /// \invariant Denominator shall be not null
        Fraction<T> operator+= (Fraction<T> const& f)
        {
            m_num = (m_num * f.m_den) + (f.m_num * m_den);
            m_den = m_den*f.m_den;
            CHECK_INVARIANTS;
            reduction();
            CHECK_INVARIANTS;
            return (*this);
        }
        /// \fn    -=
        /// \brief Self subtraction
        /// \param the Fraction to be subtract
        /// \invariant Denominator shall be not null
        Fraction<T> operator-= (Fraction<T> const& f)
        {
            m_num = (m_num * f.m_den) - (f.m_num * m_den);
            m_den = m_den*f.m_den;
            CHECK_INVARIANTS;
            reduction();
            CHECK_INVARIANTS;
            return (*this);
        }
        /// \fn    *=
        /// \brief Self multiplication
        /// \param the Fraction to be multiply
        /// \invariant Denominator shall be not null
        Fraction<T> operator*= (Fraction<T> const& f)
        {
            m_num = m_num * f.m_num;
            m_den = m_den*f.m_den;
            CHECK_INVARIANTS;
            reduction();
            CHECK_INVARIANTS;
            return (*this);
        }
        /// \fn    /=
        /// \brief Self division
        /// \param the Fraction to be divided
        /// \pre   Numerator of parameter function shall be not null
        /// \invariant Denominator shall be not null
        Fraction<T> operator/= (Fraction<T> const& f)
        {
            REQUIRE((f.m_num!=0), "Divided by a Fraction null");
            m_num = m_num * f.m_den;
            m_den = m_den * f.m_num;
            CHECK_INVARIANTS;
            reduction();
            CHECK_INVARIANTS;
            return (*this);
        }
        /// \fn    <<
        /// \brief Output on flux
        /// \param reference to the output flux
        /// \param reference of the Fraction
        friend std::ostream& operator<< (std::ostream& flux, Fraction<T>const& f)
        {
            flux << f.m_num << "/" << f.m_den;
            return flux;
        }
        /// \def INVARIANT
        /// \brief Contract programming "invariant check"
        BEGIN_INVARIANTS_BLOCK
        INVARIANT ((m_den!=0), "Fraction with null denominator");
        END_INVARIANTS_BLOCK
        /// \fn   bug()
        /// \brief Temporary function which activate the "invariant check"
        void bug ()
        {
            m_den=0;
        }
    protected:
    private:
        // This function compute the "greater commum divisor
        // (algorithm find on web: http://codes-sources.commentcamarche.net/source/10495
        T PGCD(T a, T b)
        {
            T r= a%b;
            while(r) {
                a=b;
                b=r;
                r=a%b;
            } // end while
            return b;
        }
        /// \fn    reduction()
        /// \brief Reduction of the fraction: Computation of PGDC and divide Numerator/denominator by this PGDC
        void reduction ()
        {
        // case negative denominator, change the numerator and denominator signs
            if (m_den < 0){
                m_num *= -1;
                m_den *= -1;
            } //end if
            // standard case compute PGDC, and divide num/den by PGDC
            T div {1};
            if (m_num >= 0){
                div = PGCD (m_num, m_den);
            } else {
                div = PGCD (-1*m_num, m_den);
            } // end if
            m_num /= div;
            m_den /= div;
        }
        /// \var   m_num
        /// \brief member variable: value of numerator
        T  m_num;
        /// \var   m_den
        /// \brief member variable: value of denominator
        T m_den;
    }; // end class

    /// \fn    +
    /// \brief Addition
    /// \param the Fraction to be added
    template<typename T>
    Fraction<T>& operator+ (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        Fraction<T> f {f1};
        return (f+=f2);
    }
    /// \fn    -
    /// \brief Subtraction
    /// \param the Fraction to be subtract
    template<typename T>
    Fraction<T> operator- (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        Fraction<T> f {f1};
        return (f-=f2);
    }
    /// \fn    *
    /// \brief Multiplication
    /// \param the Fraction to be multiplied
    template<typename T>
    Fraction<T> operator* (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        Fraction<T> f {f1};
        return (f*=f2);
    }
    /// \fn    /
    /// \brief Division
    /// \param the Fraction to be divided
    template<typename T>
    Fraction<T> operator/ (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        Fraction<T> f {f1};
        return (f/=f2);
    }
    /// \fn    ==
    /// \brief comparison: is equal to
    /// \param the Fraction to be compared
    template<typename T>
    bool operator== (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        return (f1.isEqualAs(f2));
    }
    /// \fn    >
    /// \brief comparison: is greater than
    /// \param the Fraction to be compared
    template<typename T>
    bool operator> (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        return (f1.isGreaterThan(f2));
    }
    /// \fn    >=
    /// \brief comparison: is greater or equal to
    /// \param the Fraction to be compared
    template<typename T>
    bool operator>= (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        return (f1.isGreaterThan(f2)||f1.isEqualAs(f2));
    }
    /// \fn    <
    /// \brief comparison: is smaller than
    /// \param the Fraction to be compared
    template<typename T>
    bool operator< (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        return (f2.isGreaterThan(f1));
    }
    /// \fn    <=
    /// \brief comparison: is smaller or equal to
    /// \param the Fraction to be compared
    template<typename T>
    bool operator<= (Fraction<T> const& f1, Fraction<T> const& f2)
    {
        return (f2.isGreaterThan(f1)||f2.isEqualAs(f1));
    }

} //end namespace
#endif // FRACTION_HPP_INCLUDED
