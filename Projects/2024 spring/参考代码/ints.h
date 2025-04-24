//
// Created by Yihan Yang on 2024/4/22.
//

#ifndef BITNUMBER_INTS_H
#define BITNUMBER_INTS_H

#include "bits.h"

namespace integers {
    template<size_t N>
    class uInt : public bits<N> {
        using storage_type = typename bits<N>::storage_type;
        using storage_pointer = typename bits<N>::storage_pointer;
        using const_storage_pointer = typename bits<N>::const_storage_pointer;

        using iterator = typename bits<N>::iterator;
        using const_iterator = typename bits<N>::const_iterator;

        using base = bits<N>;
        friend typename bits<N>::self;

        using bits<N>::n_words;
        using bits<N>::bits_per_word;
        using bits<N>::data;
        using bits<N>::flip;


    public:
        uInt( ) : bits<N>( ) {}
        uInt( unsigned long long v ) : bits<N>( v ) {}
        uInt( const bits<N>& t ) : bits<N>( t ) {}
        uInt( const std::string& t ) : uInt() {
            int p = 0;
            unsigned long long val = 0;
            for( ; p + 9 < t.size() ; p += 9 ) {
                val = 0;
                for( int j = p ; j < p + 9 ; ++ j )
                    val = val * 10 + t[j] - '0';
                ( *this ) *= 1000'000'000;
                *this += val;
            }
            val = 0; int bs = 1;
            for( int j = p ; j < t.size() ; ++ j ) {
                val = val * 10 + t[j] - '0';
                bs *= 10;
            }
            ( *this ) = ( *this ) * bs;
            *this += val;
        }

        uInt& operator ++ ( );
        uInt operator ++ ( ) const ;
        uInt operator ++ ( int );
        uInt& operator += ( const uInt& rhs );
        uInt& operator -= ( const uInt& rhs );
        uInt& operator *= ( const uInt& rhs );
        uInt& operator /= ( const uInt& rhs );
        uInt& operator /= ( size_t rhs );
        uInt& operator %= ( const uInt& rhs );
        uInt& operator %= ( size_t rhs );

        std::string to_string( ) const ;

        size_t operator % ( size_t rhs ) const ;
        uInt operator * ( const uInt<N>& rhs ) const ;
        uInt operator - ( const uInt<N>& rhs ) const ;
        uInt operator + ( const uInt<N>& rhs ) const ;
        uInt operator / ( const uInt<N>& rhs ) const ;

        uInt operator - ( ) const ;

        using bits<N>::to_string;

    protected:
        uInt& flip( ) {
            base::flip();
            return *this;
        }
        template<typename r_type>
        std::pair<uInt<N>,r_type> div( const r_type& rhs ) noexcept ;

    };

    template<size_t N>
    uInt<N>&
    uInt<N>::operator ++ ( ) {
        size_t n = N;
        storage_pointer p = data;
        for( ; n >= bits_per_word ; ++ p , n -= bits_per_word ) {
            if( ++ ( *p ) )
                break;
        }
        if( n < bits_per_word ) {
            ++ ( *p );
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - n );
            *p &= m;
        }
        return *this;
    }

    template<size_t N>
    uInt<N>
    uInt<N>::operator ++ ( ) const {
        uInt<N> t = *this;
        ++ t;
        return t;
    }

    template<size_t N>
    uInt<N>
    uInt<N>::operator ++ ( int ) {
        uInt<N> tmp = *this;
        ++ ( *this );
        return tmp;
    }

    template<size_t N>
    uInt<N>&
    uInt<N>::operator += ( const uInt<N>& rhs ) {
        size_t n = N;
        storage_pointer p = data;
        const_storage_pointer pr = rhs.data;
        storage_type cap = storage_type( 0 ) , tmp;
        for( ; n >= bits_per_word ; ++ p , ++ pr , n -= bits_per_word ) {
            tmp = ( ( *p ) + ( *pr ) + cap );
            cap = ( tmp < ( *p ) || ( !~*pr && cap ) );
            *p = tmp;
        }
        if( n > 0 ) {
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - n );
            *p = ( ( *p ) + ( *pr ) + cap );
            *p &= m;
        }
        return *this;
    }

    template<size_t N>
    uInt<N>
    uInt<N>::operator - ( ) const {
        uInt<N> t = *this;
        return ++ ( t.flip() );
    }

    template<size_t N>
    uInt<N>&
    uInt<N>::operator -= ( const uInt<N>& rhs ) {
        return ( *this ) += ( -rhs );
    }

    template<size_t N>
    template<typename r_type>
    std::pair<uInt<N>,r_type> uInt<N>::div( const r_type& rhs ) noexcept {
        // Assume rhs is not zero
        size_t bias = N;
        r_type rem = 0;
        uInt<N> ret = 0;
        for( const_iterator it = ( this -> end() ) - 1 ; bias ; -- it , -- bias ) {
            rem <<= 1;
            if constexpr ( std::is_same<r_type, uInt<N>>::value )
                rem[0] = *it;
            else
                rem |= *it;
            if( rem >= rhs )
                rem -= rhs , ret.set( bias - 1 );
        }
        return std::make_pair( ret , rem );
    }

    template<size_t N>
    uInt<N>&
    uInt<N>::operator *= ( const uInt<N>& rhs ) {
        uInt<N> ret( 0 );
        size_t bias = 0;
        for( const_iterator it = rhs.begin() ; it != rhs.end() ; ++ it , ++ bias ) {
            if( *it )
                ret += ( ( *this ) << bias );
        }
        return *this = ret;
    }

    template<size_t N>
    uInt<N>&
    uInt<N>::operator /= ( const uInt<N>& rhs ) {
        if( rhs.none( ) ) throw std::invalid_argument( "uInt division by zero" );
        auto ret = div( rhs );
        return *this = ret.first;
    }

    template<size_t N>
    uInt<N>&
    uInt<N>::operator /= ( size_t rhs ) {
        if( !rhs ) throw std::invalid_argument( "uInt division by zero" );
        auto ret = div( rhs );
        return *this = ret.first;
    }

    template<size_t N>
    uInt<N>&
    uInt<N>::operator %= ( const uInt<N>& rhs ) {
        if( rhs.none( ) ) throw std::invalid_argument( "uInt remainder by zero" );
        auto ret = div( rhs );
        return *this = ret.second;
    }

    template<size_t N>
    uInt<N>&
    uInt<N>::operator %= ( size_t rhs ) {
        if( !rhs ) throw std::invalid_argument( "uInt remainder by zero" );
        auto ret = div( rhs );
        return *this = ret.second;
    }

    template<size_t N>
    uInt<N>
    uInt<N>::operator + ( const uInt<N>& rhs ) const {
        uInt<N> tmp = *this;
        tmp += rhs;
        return tmp;
    }
    template<size_t N>
    uInt<N>
    uInt<N>::operator - ( const uInt<N>& rhs ) const {
        uInt<N> tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    // Specific implementation for module
    template<size_t N>
    size_t
    uInt<N>::operator % ( size_t rhs ) const {
        size_t bias = N;
        size_t rem = 0;
        for( const_iterator it = ( this -> end() ) - 1 ; bias ; -- it , -- bias ) {
            rem = rem << 1;
            rem |= *it;
            if( rem >= rhs )
                rem -= rhs;
        }
        return rem;
    }

    template<size_t N>
    uInt<N>
    uInt<N>::operator * ( const uInt<N>& rhs ) const {
        uInt<N> tmp = *this;
        tmp *= rhs;
        return tmp;
    }
    template<size_t N>
    uInt<N>
    uInt<N>::operator / ( const uInt<N>& rhs ) const {
        uInt<N> tmp = *this;
        tmp /= rhs;
        return tmp;
    }

    template<size_t N>
    std::string
    uInt<N>::to_string( ) const {
        std::string ret;
        uInt<N> val = *this;
        for( size_t i = 0 ; i < N ; ++ i ) {
            ret.push_back(val % 10 + '0');
            val /= 10;
        }
        while( ret.back() == '0' ) ret.pop_back();
        std::reverse( ret.begin() , ret.end() );
        return ret;
    }

    template<size_t N>
    std::ostream& operator << ( std::ostream& os , uInt<N>& v ) {
        os << v.to_string( );
        return os;
    }

}

#endif //BITNUMBER_INTS_H
