#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include "bit_reference.h"

namespace integers {

    template<size_t N>
    class bits {
    public:
        using difference_type = ptrdiff_t;

    protected:
        using self = bits;
        using storage_type = size_t;
        using storage_pointer = storage_type *;
        using const_storage_pointer = const storage_type *;
        using reference = bit_reference<bits>;
        using const_reference = bit_const_reference<bits>;
        using iterator = bit_iterator<bits, false>;
        using const_iterator = bit_iterator<bits, true>;
        static const unsigned n_words = ( N - 1 ) / ( sizeof( storage_type ) * 8 ) + 1;
        static const unsigned bits_per_word = static_cast<unsigned>( sizeof( storage_type ) * 8 );

        friend class bit_reference<bits>;
        friend class bit_const_reference<bits>;
        friend class bit_iterator<bits,false>;
        friend class bit_iterator<bits,true>;

        storage_type data[n_words];

        reference make_ref( size_t pos ) {
            return bit_reference<bits>( data + pos / bits_per_word , storage_type( 1 ) << pos % bits_per_word );
        }
        const_reference make_ref( size_t pos ) const {
            return const_reference( data + pos / bits_per_word , storage_type( 1 ) << pos % bits_per_word );
        }
        const_iterator make_iter( size_t pos ) const {
            return const_iterator( data + pos / bits_per_word , pos % bits_per_word );
        }
        iterator make_iter( size_t pos ) {
            return iterator( data + pos / bits_per_word , pos % bits_per_word );
        }

    public:

        // Constructors
        bits( );
        bits( unsigned long long );

        template<size_t M>
        bits( const bits<M>& v );

        template<class Char>
        bits( const Char* , size_t , Char zero , Char one );

        // Basic functions
        bool test( size_t ) const;
        bool all() const ;
        bool any() const ;
        bool none() const ;
        bits& flip( size_t );
        bits& flip( );
        bits& set( size_t );
        bits& set( );
        bits& reset( size_t );
        bits& reset( );
        size_t count() const ;
        size_t size() const ;

        // Operators
        reference operator []( size_t p ) {
            return make_ref( p );
        }
        bits& operator &= ( const bits& v );
        bits& operator |= ( const bits& v );
        bits& operator ^= ( const bits& v );
        bits& operator <<= ( size_t p );
        bits& operator >>= ( size_t p );

        bits operator ~ ( ) const ;

        bool operator == ( const bits<N>& rhs ) const ;
        bool operator != ( const bits<N>& rhs ) const ;
        bool operator < ( const bits<N>& rhs ) const ;
        bool operator > ( const bits<N>& rhs ) const ;
        bool operator <= ( const bits<N>& rhs ) const ;
        bool operator >= ( const bits<N>& rhs ) const ;
        bits operator & ( const bits& rhs ) const ;
        bits operator | ( const bits& rhs ) const ;
        bits operator ^ ( const bits& rhs ) const ;
        bits operator << ( const size_t rhs ) const ;
        bits operator >> ( const size_t rhs ) const;

        virtual std::string to_string( ) const ;

        iterator begin() { return make_iter( 0 ); }
        const_iterator begin() const { return make_iter( 0 ); }
        iterator end() { return make_iter( N ); }
        const_iterator end() const { return make_iter( N ); }

        friend class bits;

    };

    template<size_t N>
    bits<N>::bits() : data{ 0 } {
    }

    template<size_t N>
    bits<N>::bits( unsigned long long v ) : data{ v } {
    }

    template<size_t N>
    template<size_t M>
    bits<N>::bits( const bits<M>& v ) {
        if constexpr ( M <= N ) {
            for( size_t i = 0 ; i < v.n_words ; ++ i )
                data[i] = v.data[i];
        } else {
            for( size_t i = 0 ; i < n_words ; ++ i )
                data[i] = v.data[i];
            storage_type m = storage_type( -1 ) >> ( bits_per_word - N % bits_per_word );
            data[n_words - 1] &= m;
        }
    }

    template<size_t N>
    template<class Char>
    bits<N>::bits( const Char* A , size_t n , Char zero , Char one ) {
        for( int i = 0 ; i < n ; ++ i ) if( A[i] != zero && A[i] != one )
            throw std::invalid_argument( "bitset string has invalid argument" );
        if( n > N ) throw std::invalid_argument( "bitset size less than string length" );
        for( size_t i = 0 ; i < n ; ++ i )
            (*this)[i] = ( A[n - 1 - i] == one );
        for( size_t i = n ; i < N ; ++ i )
            (*this)[i] = false;
    }

    template<size_t N>
    bool bits<N>::test( size_t pos ) const {
        if( pos >= N )
            throw std::out_of_range( "bitset test argument out of range" );
        return (*this)[pos];
    }

    template<size_t N>
    bool bits<N>::all( ) const {
        size_t n = N;
        const_storage_pointer p = data;
        for( ; n >= bits_per_word ; ++ p , n -= bits_per_word )
            if( ~*p )
                return false;
        if( n > 0 ) {
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - n );
            if( ~*p & m )
                return false;
        }
        return true;
    }

    template<size_t N>
    bool bits<N>::any( ) const {
        size_t n = N;
        const_storage_pointer p = data;
        for( ; n >= bits_per_word ; ++ p , n -= bits_per_word )
            if( *p )
                return true;
        if( n > 0 ) {
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - n );
            if( *p & m )
                return true;
        }
        return false;
    }

    template<size_t N>
    bool bits<N>::none( ) const {
        return !any();
    }

    template<size_t N>
    size_t bits<N>::count( ) const {
        size_t n = N;
        const_storage_pointer p = data;
        size_t ret = 0;
        for( ; n >= bits_per_word ; ++ p , n -= bits_per_word )
            ret += __builtin_popcountll( *p );
        if( n > 0 ) {
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - n );
            ret += __builtin_popcountll( *p & m );
        }
        return ret;
    }

    template<size_t N>
    size_t bits<N>::size( ) const {
        return N;
    }

    template<size_t N>
    bits<N>& bits<N>::flip( ) {
        size_t n = N;
        storage_pointer p = data;
        for( ; n >= bits_per_word ; ++ p , n -= bits_per_word )
            *p = ~*p;
        if( n > 0 ) {
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - n );
            storage_type b = *p & m;
            *p &= ~m;
            *p |= ~b & m;
        }
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::flip( size_t pos ) {
        if( pos > N )
            throw std::out_of_range( "bitset flip argument out of range" );

        reference r = make_ref( pos );
        r = ~r;
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::set( ) {
        size_t n = N;
        storage_pointer p = data;
        for( ; n >= bits_per_word ; ++ p , n -= bits_per_word )
            *p = ~storage_type( 0 );
        if( n > 0 ) {
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - n );
            *p = m;
        }
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::set( size_t pos ) {
        if( pos > N )
            throw std::out_of_range( "bitset set argument out of range" );

        reference r = make_ref( pos );
        r = true;
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::reset( ) {
        size_t n = N;
        storage_pointer p = data;
        for( ; n >= bits_per_word ; ++ p , n -= bits_per_word )
            *p = storage_type( 0 );
        if( n > 0 ) {
            *p = storage_type( 0 );
        }
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::reset( size_t pos ) {
        if( pos > N )
            throw std::out_of_range( "bitset reset argument out of range" );

        reference r = make_ref( pos );
        r = false;
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::operator &= ( const bits<N>& v ) {
        for( size_t i = 0 ; i < n_words ; ++ i )
            data[i] &= v.data[i];
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::operator |= ( const bits<N>& v ) {
        for( size_t i = 0 ; i < n_words ; ++ i )
            data[i] |= v.data[i];
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::operator ^= ( const bits<N>& v ) {
        for( size_t i = 0 ; i < n_words ; ++ i )
            data[i] ^= v.data[i];
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::operator <<= ( size_t p ) {
        if( p >= N ) {
            return reset();
        }
        if( p < bits_per_word ) {
            if( !p ) return *this;
            for( size_t i = n_words - 1 ; i > 0 ; -- i )
                data[i] = data[i - 1] >> ( bits_per_word - p ) | ( data[i] << p );
            data[0] = data[0] << p;
            storage_type m = ~storage_type( 0 ) >> ( bits_per_word - N % bits_per_word );
            data[n_words - 1] &= m;
            return *this;
        }
        p = std::min( p , N );
        ( *this ) <<= ( p % bits_per_word );
        size_t b = p / bits_per_word;
        for( size_t i = n_words - 1 ; i >= b ; -- i )
            data[i] = data[i - b];
        for( int i = 0 ; i < b ; ++ i ) data[i] = 0;
        storage_type m = ~storage_type( 0 ) >> ( bits_per_word - N % bits_per_word );
        data[n_words - 1] &= m;
        return *this;
    }

    template<size_t N>
    bits<N>& bits<N>::operator >>= ( size_t p ) {
        if( p >= N ) {
            return reset();
        }
        if( p < bits_per_word ) {
            for( size_t i = 0 ; i < n_words - 1 ; ++ i )
                data[i] = ( data[i + 1] << ( bits_per_word - p ) ) | ( data[i] >> p );
            data[n_words - 1] >>= p;
            return *this;
        }
        p = std::min( p , N );
        ( *this ) >>= ( p % bits_per_word );
        size_t b = p / bits_per_word;
        for( size_t i = 0 ; i < n_words - b ; ++ i )
            data[i] = data[i + b];
        for( size_t i = n_words - b ; i < n_words ; ++ i )
            data[i] = 0;
        return *this;
    }

    template<size_t N>
    bits<N> bits<N>::operator ~ () const {
        bits<N> tmp( *this );
        tmp.flip( );
        return tmp;
    }

    template<size_t N>
    std::string bits<N>::to_string( ) const {
        const_iterator e = make_iter( N - 1 );
        std::string ret;
        for( size_t i = 0 ; i < N ; ++ i )
            ret += ( ( *e ) + '0' ) , -- e;
        return ret;
    }

    template<size_t N>
    std::ostream& operator << ( std::ostream& os , const bits<N>& v ) {
        os << v.to_string( );
        return os;
    }



    template<size_t N>
    bool bits<N>::operator == ( const bits<N>& rhs ) const {
        const_storage_pointer p = data + n_words - 1 , q = rhs.data + n_words - 1;
        for( ; p >= data ; -- p , -- q ) {
            if( *p != *q ) return false;
        }
        return true;
    }

    template<size_t N>
    bool bits<N>::operator != ( const bits<N>& rhs ) const {
        return !( *this == rhs );
    }
    template<size_t N>
    bool bits<N>::operator < ( const bits<N>& rhs ) const {
        const_storage_pointer p = data + n_words - 1 , q = rhs.data + n_words - 1;
        for( ; p >= data ; -- p , -- q ) {
            if( *p < *q ) return true;
            if( *p > *q ) return false;
        }
        return false;
    }
    template<size_t N>
    bool bits<N>::operator > ( const bits<N>& rhs ) const {
        return rhs < *this;
    }
    template<size_t N>
    bool bits<N>::operator <= ( const bits<N>& rhs ) const {
        return !( rhs < *this );
    }
    template<size_t N>
    bool bits<N>::operator >= ( const bits<N>& rhs ) const {
        return !( *this < rhs );
    }

    template<size_t N>
    bits<N>
    bits<N>::operator & ( const bits<N>& rhs ) const {
        bits<N> tmp = *this;
        tmp &= rhs;
        return tmp;
    }
    template<size_t N>
    bits<N>
    bits<N>::operator | ( const bits<N>& rhs ) const {
        bits<N> tmp = *this;
        tmp |= rhs;
        return tmp;
    }
    template<size_t N>
    bits<N>
    bits<N>::operator ^ ( const bits<N>& rhs ) const {
        bits<N> tmp = *this;
        tmp ^= rhs;
        return tmp;
    }
    template<size_t N>
    bits<N>
    bits<N>::operator << ( const size_t rhs ) const {
        bits<N> tmp = *this;
        tmp <<= rhs;
        return tmp;
    }
    template<size_t N>
    bits<N>
    bits<N>::operator >> ( const size_t rhs ) const {
        bits<N> tmp = *this;
        tmp >>= rhs;
        return tmp;
    }


}
