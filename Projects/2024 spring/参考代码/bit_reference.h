//
// Created by Yihan Yang on 2024/3/30.
//

#ifndef BITNUMBER_BIT_REFERENCE_H
#define BITNUMBER_BIT_REFERENCE_H

#endif //BITNUMBER_BIT_REFERENCE_H

#include <iterator>
#include <type_traits>

template<class origin, bool is_const = false> class bit_iterator;
template<class origin> class bit_const_reference;

template<class origin>
class bit_reference {
    using storage_type = typename origin::storage_type;
    using storage_pointer = typename origin::storage_pointer;

    friend typename origin::self;

    friend class bit_const_reference<origin>;
    friend class bit_iterator<origin>;

    storage_pointer seg;
    storage_type mask;

public:
    bit_reference( const bit_reference& ) = default;

    operator bool() const
    { return static_cast<bool>( *seg & mask ); }
    bool operator ~() const
    { return !static_cast<bool>( *this ); }

    bit_reference& operator = ( bool x ) {
        if( x )
            *seg |= mask;
        else
            *seg &= ~mask;
        return *this;
    }

    bit_reference& operator = ( const bit_reference& x )
    { return operator = ( static_cast<bool>( x ) ); }

    bit_reference& operator = ( const bit_const_reference<origin>& x )
    { return operator = ( static_cast<bool>( x ) ); }

    void flip( ) { *seg ^= mask; }

    bit_iterator<origin> operator &( ) const
    { return bit_iterator<origin>( seg , static_cast<unsigned>( __builtin_ctz( mask ) ) ); }

private:
    explicit bit_reference( storage_pointer s , storage_type m ) : seg( s ) , mask( m ) {}
};

template<class origin>
class bit_const_reference {
    using storage_type = typename origin::storage_type;
    using storage_pointer = typename origin::const_storage_pointer;

    friend typename origin::self;
    friend class bit_iterator<origin, true>;

    storage_pointer seg;
    storage_type mask;

public:
    bit_const_reference( const bit_const_reference& ) = default;
    bit_const_reference( const bit_reference<origin>& x )
    : seg( x.seg ) , mask( x.mask ) {}

    operator bool() const
    { return static_cast<bool>( *seg & mask ); }
    bool operator ~() const
    { return !static_cast<bool>( *this ); }

    bit_iterator<origin, true> operator &( ) const
    { return bit_iterator<origin, true>( seg , static_cast<unsigned>( __builtin_ctz( mask ) ) ); }

private:
    explicit bit_const_reference( storage_pointer s , storage_type m ) : seg( s ) , mask( m ) {}

    bit_const_reference& operator = ( const bit_const_reference& ) = delete;
};

template<class origin, bool is_const>
class bit_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = bool;
    using difference_type = typename origin::difference_type;
    using pointer = bit_iterator;
    using reference = std::conditional_t<is_const, bit_const_reference<origin>, bit_reference<origin>>;
private:
    using storage_type = typename origin::storage_type;
    using storage_pointer = std::conditional_t<is_const, typename origin::const_storage_pointer, typename origin::storage_pointer>;
    static const unsigned bits_per_word = origin::bits_per_word;

    storage_pointer seg;
    unsigned ctz;
public:
    bit_iterator() : seg( nullptr ) , ctz( 0 ) {}
    bit_iterator( const bit_iterator<origin, false>& it ) : seg( it.seg ) , ctz( it.ctz ) {}
    bit_iterator& operator = ( const bit_iterator<origin, false>& it ) {
        seg = it.seg;
        ctz = it.ctz;
        return *this;
    }

    reference operator * () const {
        return std::conditional_t<is_const, bit_const_reference<origin>, bit_reference<origin>>
        ( seg , storage_type( 1 ) << ctz );
    }

    bit_iterator& operator ++ () {
        if( ctz != bits_per_word - 1 )
            ++ ctz;
        else
            ctz = 0 , ++ seg;
        return *this;
    }

    bit_iterator operator ++ ( int ) {
        bit_iterator tmp = *this;
        ++ ( *this );
        return tmp;
    }

    bit_iterator& operator -- () {
        if( ctz != 0 )
            -- ctz;
        else
            ctz = bits_per_word - 1 , -- seg;
        return *this;
    }

    bit_iterator operator --( int ) {
        bit_iterator tmp = *this;
        -- ( *this );
        return tmp;
    }

    bit_iterator & operator += ( difference_type n ) {
        if( n >= 0 )
            seg += ( n + ctz ) / bits_per_word;
        else
            seg += ( static_cast<difference_type>( n - bits_per_word ) + ctz + 1 ) / static_cast<difference_type>( bits_per_word );
        n &= ( bits_per_word - 1 );
        ctz = static_cast<unsigned>( ( n + ctz ) % bits_per_word );
        return *this;
    }

    bit_iterator & operator -= ( difference_type n ) {
        return *this += - n;
    }

    bit_iterator operator + ( difference_type n ) const {
        bit_iterator tmp( *this );
        tmp += n;
        return tmp;
    }

    bit_iterator operator - ( difference_type n ) const {
        bit_iterator tmp( *this );
        tmp -= n;
        return tmp;
    }

    friend bit_iterator operator + ( difference_type n , const bit_iterator& it ) { return it + n; }
    friend difference_type operator - ( const bit_iterator& x , const bit_iterator& y ) {
        return ( x.seg - y.seg ) * bits_per_word + x.ctz - y.ctz;
    }

    reference operator []( difference_type n ) const {
        return *( *this + n );
    }

    friend bool operator == ( const bit_iterator& x , const bit_iterator& y ) {
        return x.seg == y.seg && x.ctz == y.ctz;
    }

    friend bool operator != ( const bit_iterator& x , const bit_iterator& y ) {
        return !( x == y );
    }

    friend bool operator < ( const bit_iterator& x , const bit_iterator& y ) {
        return x.seg < y.seg || ( x.seg == y.seg && x.ctz < y.ctz );
    }

    friend bool operator > ( const bit_iterator& x , const bit_iterator& y ) {
        return y < x;
    }

    friend bool operator <= ( const bit_iterator& x , const bit_iterator& y ) {
        return !( y < x );
    }

    friend bool operator >= ( const bit_iterator& x , const bit_iterator& y ) {
        return !( x < y );
    }

private:
    explicit bit_iterator( storage_pointer s , unsigned ctz ) : seg( s ) , ctz( ctz ) {}

    friend class bit_iterator<origin, true>;
    friend class bit_const_reference<origin>;
    friend class bit_reference<origin>;
    friend typename origin::self;

};
