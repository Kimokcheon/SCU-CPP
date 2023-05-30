#pragma once
#include <memory> // for std::addressof
#include <cassert>

namespace _Sb_tree {

struct _Sb_tree_node_base {
    using _Base_ptr = _Sb_tree_node_base*;
    using _Const_Base_ptr = const _Sb_tree_node_base*;
    using _Sb_tree_size = unsigned int;

    // node base

    _Sb_tree_size _M_size;
    _Base_ptr _M_parent;
    _Base_ptr _M_left;
    _Base_ptr _M_right;
    
    static _Base_ptr _S_minimum( _Base_ptr __x ) {
        while( __x -> _M_left != 0 ) __x = __x -> _M_left;
        return __x;
    }

    static _Const_Base_ptr _S_minimum( _Const_Base_ptr __x ) {
        while( __x -> _M_left != 0 ) __x = __x -> _M_left;
        return __x;
    }

    static _Base_ptr _S_maximum( _Base_ptr __x ) {
        while( __x -> _M_right != 0 ) __x = __x -> _M_right;
        return __x;
    }

    static _Const_Base_ptr _S_maximum( _Const_Base_ptr __x ) {
        while( __x -> _M_right != 0 ) __x = __x -> _M_right;
        return __x;
    }

};

template<typename _Val>
struct _Sb_tree_node : public _Sb_tree_node_base {
    using _Link_type = _Sb_tree_node<_Val>*;
    _Val _M_value_field;

    template<typename... _Args> 
    _Sb_tree_node( _Args&&... __args ) : _Sb_tree_node_base( ) , _M_value_field( std::forward<_Args>( __args )... ) {}

};

// in tree.cpp
_Sb_tree_node_base* 
_Sb_tree_increment( _Sb_tree_node_base* __x ) noexcept;

const _Sb_tree_node_base* 
_Sb_tree_increment( const _Sb_tree_node_base* __x ) noexcept;

_Sb_tree_node_base* 
_Sb_tree_decrement( _Sb_tree_node_base* __x ) noexcept;

const _Sb_tree_node_base* 
_Sb_tree_decrement( const _Sb_tree_node_base* __x ) noexcept;

void _Sb_tree_insert_and_rebalance( const bool __insert_left , 
_Sb_tree_node_base* __x , _Sb_tree_node_base* __p , 
_Sb_tree_node_base& __header ) noexcept;

_Sb_tree_node_base* 
_Sb_tree_rebalance_for_erase( _Sb_tree_node_base* const __z ,
_Sb_tree_node_base& __header ) noexcept;

size_t _S_size( _Sb_tree_node_base* __x );

_Sb_tree_node_base* 
_Sb_tree_increment( _Sb_tree_node_base *__x , size_t __k ) noexcept;

const _Sb_tree_node_base* 
_Sb_tree_increment( const _Sb_tree_node_base *__x , size_t __k ) noexcept;

_Sb_tree_node_base* 
_Sb_tree_decrement( _Sb_tree_node_base *__x , size_t __k ) noexcept;

const _Sb_tree_node_base* 
_Sb_tree_decrement( const _Sb_tree_node_base *__x , size_t __k ) noexcept;

size_t 
_Sb_tree_get_lower_size( _Sb_tree_node_base* __x ) noexcept;

const size_t 
_Sb_tree_get_lower_size( const _Sb_tree_node_base* __x ) noexcept;

// ---

template<typename _Tp>
struct _Sb_tree_iterator {
    using value_type = _Tp;
    using reference = _Tp&;
    using pointer = _Tp*;

    using _Self = _Sb_tree_iterator<_Tp>;
    using _Base_ptr = _Sb_tree_node_base::_Base_ptr; 
    using _Link_type = _Sb_tree_node<_Tp>*;

    _Base_ptr _M_node;

    _Sb_tree_iterator( ) : _M_node( ) { }
    explicit _Sb_tree_iterator( _Base_ptr __x ) : _M_node( __x ) { }
    
    // Basic options for iterator

    reference operator * ( ) const {
        return static_cast<_Link_type>( _M_node ) -> _M_value_field;
    } 

    pointer operator -> ( ) const {
        return std::addressof( static_cast<_Link_type> (_M_node) -> _M_value_field );
    }

    _Self &operator ++() {
        _M_node = _Sb_tree_increment( _M_node );
        return *this;
    }

    _Self operator ++( int ) {
        _Self __tmp = *this;
        _M_node = _Sb_tree_increment( _M_node );
        return __tmp;
    }

    _Self &operator --() {
        _M_node = _Sb_tree_decrement( _M_node );
        return *this;
    }

    _Self operator --( int ) {
        _Self __tmp = *this;
        _M_node = _Sb_tree_decrement( _M_node );
        return __tmp;
    }

    _Self& operator += ( size_t __k ) {
        _M_node = _Sb_tree_increment( _M_node , __k );
        return *this;
    }

    _Self& operator -= ( size_t __k ) {
        _M_node = _Sb_tree_decrement( _M_node , __k );
        return *this;
    }

    _Self operator + ( size_t __k ) {
        return _Sb_tree_iterator( static_cast<_Link_type>( _Sb_tree_increment( _M_node , __k ) ) );
    }

    _Self operator - ( size_t __k ) {
        return _Sb_tree_iterator( static_cast<_Link_type>( _Sb_tree_decrement( _M_node , __k ) ) );
    }

    friend _Self operator + ( size_t __k , _Self __x ) {
        return _Self( __x + __k );
    }

    bool operator == ( const _Self& __x ) const {
        return _M_node == __x._M_node;
    }

    bool operator != ( const _Self& __x ) const {
        return _M_node != __x._M_node;
    }

    int operator - ( const _Self& __x ) const {
        return _Sb_tree_get_lower_size( this -> _M_node ) - _Sb_tree_get_lower_size( __x._M_node );
    }

    bool operator < ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) < _Sb_tree_get_lower_size( __k._M_node );
    }

    bool operator > ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) > _Sb_tree_get_lower_size( __k._M_node );
    }

    bool operator <= ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) <= _Sb_tree_get_lower_size( __k._M_node );
    }

    bool operator >= ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) >= _Sb_tree_get_lower_size( __k._M_node );
    }

};

template<typename _Tp>
struct _Sb_tree_const_iterator {
    using value_type = _Tp;
    using reference = const _Tp&;
    using pointer = const _Tp*;

    using iterator = _Sb_tree_iterator<_Tp>;

    using _Self = _Sb_tree_const_iterator<_Tp>;
    using _Base_ptr = _Sb_tree_node_base::_Const_Base_ptr;
    using _Link_type = const _Sb_tree_node<_Tp>*;

    _Base_ptr _M_node;

    _Sb_tree_const_iterator( ) : _M_node( ) { }
    explicit _Sb_tree_const_iterator( _Base_ptr __x ) : _M_node( __x ) { }
    _Sb_tree_const_iterator( const iterator& __it ) : _M_node( __it._M_node ) { }
    
    iterator _M_const_cast( ) const {
        return iterator( const_cast<typename iterator::_Base_ptr>( _M_node ) );
    }

    reference operator * ( ) const {
        return static_cast<_Link_type>( _M_node ) -> _M_value_field;
    } 

    pointer operator -> ( ) const {
        return std::addressof( static_cast<_Link_type> (_M_node) -> _M_value_filed );
    }

    _Self &operator ++() {
        _M_node = _Sb_tree_increment( _M_node );
        return *this;
    }

    _Self operator ++( int ) {
        _Self __tmp = *this;
        _M_node = _Sb_tree_increment( _M_node );
        return __tmp;
    }

    _Self &operator --() {
        _M_node = _Sb_tree_decrement( _M_node );
        return *this;
    }

    _Self operator --( int ) {
        _Self __tmp = *this;
        _M_node = _Sb_tree_decrement( _M_node );
        return __tmp;
    }

    bool operator == ( const _Self& __x ) const {
        return _M_node == __x._M_node;
    }

    bool operator != ( const _Self& __x ) const {
        return _M_node != __x._M_node;
    }

    _Self& operator += ( size_t __k ) {
        _M_node = _Sb_tree_increment( _M_node , __k );
        return *this;
    }

    _Self& operator -= ( size_t __k ) {
        _M_node = _Sb_tree_decrement( _M_node , __k );
        return *this;
    }

    _Self operator + ( size_t __k ) {
        return _Self( static_cast<_Link_type>( _Sb_tree_increment( _M_node , __k ) ) );
    }

    _Self operator - ( size_t __k ) {
        return _Self( static_cast<_Link_type>( _Sb_tree_decrement( _M_node , __k ) ) );
    }

    friend _Self operator + ( size_t __k , _Self __x ) {
        return _Self( __x + __k );
    }

    bool operator < ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) < _Sb_tree_get_lower_size( __k._M_node );
    }

    bool operator > ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) > _Sb_tree_get_lower_size( __k._M_node );
    }

    bool operator <= ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) <= _Sb_tree_get_lower_size( __k._M_node );
    }

    bool operator >= ( const _Self& __k ) {
        return _Sb_tree_get_lower_size( this -> _M_node ) >= _Sb_tree_get_lower_size( __k._M_node );
    }

};

template<typename _Val>
inline bool operator == ( const _Sb_tree_iterator<_Val>& __x , const _Sb_tree_const_iterator<_Val>& __y ) {
    return __x._M_node == __y._M_node;
}

template<typename _Val>
inline bool operator != ( const _Sb_tree_iterator<_Val>& __x , const _Sb_tree_const_iterator<_Val>& __y ) {
    return __x._M_node != __y._M_node;
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc = std::allocator<_Val>>
class _Sb_tree {
    using _Node_allocator = typename _Alloc::template rebind<_Sb_tree_node<_Val>>::other;

protected:
    using _Base_ptr = _Sb_tree_node_base*;
    using _Const_Base_ptr = const _Sb_tree_node_base*;
    using _Link_type = _Sb_tree_node<_Val>*;
    using _Const_Link_type = const _Sb_tree_node<_Val>*;

private:
    struct _Alloc_node {
        _Alloc_node( _Sb_tree& __t ) : _M_t( __t ) {}

        template<typename _Arg>
        _Link_type operator( ) ( _Arg&& __arg ) const {
            return _M_t._M_create_node( std::forward<_Arg>( __arg ) );
        }  

    private:
        _Sb_tree& _M_t;
    };

public:
    using key_type = _Key;
    using value_type = _Val;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using allocator_type = _Alloc;

    _Node_allocator& _M_get_Node_allocator( ) noexcept {
        return *static_cast<_Node_allocator*>( & this -> _M_impl ); 
    }

    const _Node_allocator& _M_get_Node_allocator( ) const noexcept {
        return *static_cast<const _Node_allocator*>( & this -> _M_impl ); 
    }

    allocator_type get_allocator( ) const noexcept {
        return allocator_type( _M_get_Node_allocator() );
    }

protected:

    _Link_type _M_get_node() {
        return _M_impl._Node_allocator::allocate( 1 );
    }

    void _M_put_node( _Link_type __p ) {
        _M_impl._Node_allocator::deallocate( __p , 1 );
    }

    template<typename... _Args> 
    _Link_type _M_create_node( _Args&&... __args ) {
        _Link_type __tmp = _M_get_node();
        try {
            std::allocator_traits<_Node_allocator>::construct( _M_get_Node_allocator() , __tmp , std::forward<_Args>( __args )... );
        } catch( ... ) {
            _M_put_node( __tmp );
            throw;
        }
        return __tmp;
    }

    void _M_destroy_node( _Link_type __p ) {
        _M_get_Node_allocator().destroy( __p );
        _M_put_node( __p );
    }

    // void _M_drop_node( _Link_type __p ) noexcept {
    //     _M_destroy_node( __p );
    //     _M_put_node( __p );
    // }

    _Link_type _M_clone_node( _Const_Link_type __x ) { // clone
        _Link_type __tmp = _M_create_node( __x -> _M_value_field );
        __tmp -> _M_size = 1;
        __tmp -> _M_left = 0;
        __tmp -> _M_right = 0;
        return __tmp;
    }

protected:
    template<typename _Key_compare> 
    struct _Sb_tree_impl : public _Node_allocator {
        _Key_compare _M_key_compare;
        _Sb_tree_node_base _M_header;
        
        _Sb_tree_impl( ) : _Node_allocator( ) , _M_key_compare( ) , _M_header( ) {
            _M_initialize( );
        }

        _Sb_tree_impl( const _Key_compare& __comp , const _Node_allocator& __a ) : _Node_allocator( __a ) , _M_key_compare( __comp ) , _M_header( ) {
            _M_initialize( );
        }

        _Sb_tree_impl( const _Key_compare& __comp , const _Node_allocator&& __a ) : _Node_allocator( std::move( __a ) ) , _M_key_compare( __comp ) , _M_header( ) {
            _M_initialize( );
        }

        private:

        void _M_initialize( ) {
            this -> _M_header._M_size = 1;
            this -> _M_header._M_parent = 0;
            this -> _M_header._M_left = &this -> _M_header;
            this -> _M_header._M_right = &this -> _M_header;
        }
    };

    _Sb_tree_impl<_Compare> _M_impl;

protected:
    
    _Base_ptr& _M_root( ) {
        return this -> _M_impl._M_header._M_parent;
    }
    _Const_Base_ptr _M_root( ) const {
        return this -> _M_impl._M_header._M_parent;
    }

    _Base_ptr& _M_leftmost( ) {
        return this -> _M_impl._M_header._M_left;
    }
    _Const_Base_ptr _M_leftmost( ) const {
        return this -> _M_impl._M_header._M_left;
    }
    
    _Base_ptr& _M_rightmost( ) {
        return this -> _M_impl._M_header._M_right;
    }
    _Const_Base_ptr _M_rightmost( ) const {
        return this -> _M_impl._M_header._M_right;
    }

    _Link_type _M_begin( ) {
        return static_cast<_Link_type>( this -> _M_impl._M_header._M_parent );
    }

    _Const_Link_type _M_begin( ) const {
        return static_cast<_Const_Link_type>( this -> _M_impl._M_header._M_parent );
    }

    _Link_type _M_end( ) {
        return static_cast<_Link_type>( &this -> _M_impl._M_header );
    }

    _Const_Link_type _M_end( ) const {
        return static_cast<_Const_Link_type>( &this -> _M_impl._M_header );
    }

    static const_reference _S_value( _Const_Link_type __x ) {
        return __x -> _M_value_field;
    }

    static const _Key& _S_key( _Const_Link_type __x ) {
        return _KeyOfValue()( _S_value( __x ) );
    }

    static _Link_type _S_left( _Base_ptr __x ) {
        return static_cast<_Link_type>( __x -> _M_left );
    }

    static _Const_Link_type _S_left( _Const_Base_ptr __x ) {
        return static_cast<_Const_Link_type>( __x -> _M_left );
    }

    static _Link_type _S_right( _Base_ptr __x ) {
        return static_cast<_Link_type>( __x -> _M_right );
    }

    static _Const_Link_type _S_right( _Const_Base_ptr __x ) {
        return static_cast<_Const_Link_type>( __x -> _M_right );
    }

    static const_reference _S_value( _Const_Base_ptr __x ) {
        return static_cast<_Const_Link_type>( __x ) -> _M_value_field;
    }

    static const _Key& _S_key( _Const_Base_ptr __x ) {
        return _KeyOfValue()( _S_value( __x ) );
    }

    static _Base_ptr _S_minimum( _Base_ptr __x ) {
        return _Sb_tree_node_base::_S_minimum( __x );
    }

    static _Const_Base_ptr _S_minimum( _Const_Base_ptr __x ) {
        return _Sb_tree_node_base::_S_minimum( __x );
    }

    static _Base_ptr _S_maximum( _Base_ptr __x ) {
        return _Sb_tree_node_base::_S_maximum( __x );
    }

    static _Const_Base_ptr _S_maximum( _Const_Base_ptr __x ) {
        return _Sb_tree_node_base::_S_maximum( __x );
    }

public:
    using iterator = _Sb_tree_iterator<value_type>;
    using const_iterator = _Sb_tree_const_iterator<value_type>;

    std::pair<_Base_ptr, _Base_ptr> _M_get_insert_unique_pos( const key_type& __k );
    // pair<_Base_ptr, _Base_ptr> _M_get_insert_unique_pos( const key_type& __k );

    std::pair<_Base_ptr, _Base_ptr> _M_get_insert_hint_unique_pos( const_iterator __pos , const key_type& __k );

private:
    template<typename _Arg , typename _Node_gen> 
    iterator _M_insert_( _Base_ptr __x , _Base_ptr __y , _Arg&& __v , _Node_gen& );
    // insert a node on __x whose father is __y

    _Link_type _M_copy( _Const_Link_type __x , _Link_type __p );

    void _M_erase( _Link_type __x );

    iterator _M_lower_bound( _Link_type __x , _Link_type __y , const _Key& __k );

    const_iterator _M_lower_bound( _Const_Link_type __x , _Const_Link_type __y , const _Key& __k ) const ;

    iterator _M_upper_bound( _Link_type __x , _Link_type __y , const _Key& __k );

    const_iterator _M_upper_bound( _Const_Link_type __x , _Const_Link_type __y , const _Key& __k ) const ;

    size_type _M_get_pos( _Base_ptr __x );
    
    const size_type _M_get_pos( _Const_Base_ptr __x ) const ;

public:
    _Sb_tree( ) {}

    _Sb_tree( const _Compare& __comp , const allocator_type& __a = allocator_type() ) : _M_impl( __comp , _Node_allocator( __a ) ) { } 

    // copy & move constructor needs to do

    ~_Sb_tree( ) {
        _M_erase( _M_begin() );
    }

    _Sb_tree( const _Sb_tree& __x ) : _M_impl( __x._M_impl ) {
        if( __x._M_root() != 0 ) {
            _M_root( ) = _M_copy( __x._M_begin() , _M_end() );
            _M_leftmost( ) = _S_minimum( _M_root() );
            _M_rightmost( ) = _S_maximum( _M_root() );
            _M_impl._M_header._M_size = __x._M_impl._M_header._M_size;
        }
    }

    _Sb_tree& operator = ( const _Sb_tree& __x );

    // Accessors

    _Compare key_comp( ) const {
        return _M_impl._M_key_compare;
    }

    iterator begin() noexcept {
        return iterator( static_cast<_Link_type>( this -> _M_impl._M_header._M_left ) );
    }

    const_iterator begin() const noexcept {
        return const_iterator( static_cast<_Const_Link_type>( this -> _M_impl._M_header._M_left ) );
    }

    iterator end() noexcept {
        return iterator( static_cast<_Link_type>( & this -> _M_impl._M_header ) );
    }

    const_iterator end() const noexcept {
        return const_iterator( static_cast<_Const_Link_type>( & this -> _M_impl._M_header ) );
    }

    // reverse iterator

    bool empty( ) const {
        return _M_impl._M_header._M_size == 1;
    }

    size_type size( ) const {
        return _M_impl._M_header._M_size - 1;
    }

    size_type max_size() const {
        return _M_get_Node_allocator( ).max_size( );
    }

    // swap...

    template<typename _Arg> 
    std::pair<iterator,bool> _M_insert_unique( _Arg&& __x );

    template<typename _Arg, typename _NodeGen> 
    iterator _M_insert_unique_( const_iterator __pos , _Arg&& __x , _NodeGen& __node_gen );

    template<typename _Arg> 
    iterator _M_insert_unique_( const_iterator __pos , _Arg&& __x ) {
        _Alloc_node __an( *this );
        return _M_insert_unique_( __pos , std::forward<_Arg>( __x ) , __an );
    }

    // insert equal , insert_unique_

    // template<typename... _Args>
    // pair<iterartor,bool> _M_emplace_unique( _Args&&... __args );

    // hint unique

private:

    void _M_erase_aux( const_iterator __position );

    // void _M_erase_aux( const_iterator __first , const_iterator __end );

public:

    iterator erase( const_iterator __position ) {
        const_iterator __result = __position;
        ++ __result;
        _M_erase_aux( __position );
        return __result._M_const_cast( );
    }

    iterator erase( iterator __position ) {
        iterator __result = __position;
        ++ __result;
        _M_erase_aux( __position );
        return __result;
    }

    size_type erase( const key_type& __x ); // No range erase!

    void clear( ) {
        _M_erase( _M_begin() );
        _M_leftmost() = _M_end();
        _M_root() = 0;
        _M_rightmost() = _M_end();
        _M_impl._M_header._M_size = 1;
    }

    iterator find( const key_type& __k );

    const_iterator find( const key_type& __k ) const;

    size_type count( const key_type& __k ) const;

    iterator lower_bound( const key_type& __k ) {
        return _M_lower_bound( _M_begin() , _M_end() , __k );
    }

    const_iterator lower_bound( const key_type& __k ) const {
        return _M_lower_bound( _M_begin() , _M_end() , __k );
    }

    iterator upper_bound( const key_type& __k ) {
        return _M_upper_bound( _M_begin() , _M_end() , __k );
    }

    const_iterator upper_bound( const key_type& __k ) const {
        return _M_upper_bound( _M_begin() , _M_end() , __k );
    }

    size_type get_pos( iterator __k ) {
        return _M_get_pos( __k._M_node );
    }

    size_type get_pos( const_iterator __k ) const {
        return _M_get_pos( __k -> _M_node );
    }

    void try_debug( _Base_ptr __x ) {
        auto __l = __x -> _M_left , __r = __x -> _M_right;
        assert( !__l || __l -> _M_parent == __x );
        assert( !__r || __r -> _M_parent == __x );
        if( __l ) try_debug( __l );
        if( __r ) try_debug( __r );
    }
    void try_debug( ) {
        if( size() == 0 ) return;
        auto __x = _M_begin();
        try_debug( __x );
    }

    // equal range

};

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
inline bool operator == ( const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x , const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y ) {
    return __x.size() == __y.size() && std::equal( __x.begin() , __x.end() , __y.begin() );
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
inline bool operator < ( const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x , const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y ) {
    return std::lexicographical_compare( __x.begin() , __x.end() , __y.begin() , __y.end() );
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
inline bool operator != ( const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x , const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y ) {
    return !( __x == __y );
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
inline bool operator > ( const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x , const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y ) {
    return __y < __x;
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
inline bool operator <= ( const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x , const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y ) {
    return !( __y < __x );
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
inline bool operator >= ( const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x , const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y ) {
    return !( __x < __y );
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc>
_Sb_tree<_Key,_Val, _KeyOfValue, _Compare, _Alloc>&
_Sb_tree<_Key,_Val, _KeyOfValue, _Compare, _Alloc>::operator = ( const _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x ) {
    /*
     * if two trees are not the same, clear current tree and copy the whole structure.
     */
    if( this != &__x ) {
        clear();
        _M_impl._M_key_compare = __x._M_impl._M_key_compare;
        if( __x._M_root() != 0 ) {
            _M_root() = _M_copy( __x._M_begin() , _M_end() );
            _M_leftmost() = _S_minimum( _M_root() );
            _M_rightmost() = _S_maximum( _M_root() );
            _M_impl._M_header._M_size = __x._M_impl._M_header._M_size;
        }
    }
    return *this;
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
typename _Compare , typename _Alloc>
typename _Sb_tree<_Key,_Val, _KeyOfValue, _Compare, _Alloc>::_Link_type
_Sb_tree<_Key,_Val, _KeyOfValue, _Compare, _Alloc>::_M_copy( _Const_Link_type __x , _Link_type __p ) {
    _Link_type __top = _M_clone_node( __x );
    __top -> _M_parent = __p;
    try {
        if( __x -> _M_right ) 
            __top -> _M_right = _M_copy( _S_right( __x ) , __top );
        __p = __top;
        __x = _S_left( __x );
        while( __x != 0 ) {
            _Link_type __y = _M_clone_node( __x );
            __p -> _M_left = __y;
            __y -> _M_parent = __p;
            if( __x -> _M_right )
                __y -> _M_right = _M_copy( _S_right( __x ) , __y );
            __p = __y;
            __x = _S_left( __x );
        }
    } catch( ... ) {
        _M_erase( __top );
        throw;
    }
    return __top;
}


template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
std::pair<typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_Base_ptr,
    typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_Base_ptr> 
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_M_get_insert_unique_pos( const key_type& __k ) {
    using _Res = std::pair<_Base_ptr,_Base_ptr>;
    _Link_type __x = _M_begin();
    _Link_type __y = _M_end(); // __y is always father of __x
    bool __comp = true;
    while( __x ) {
        __y = __x;
        __comp = _M_impl._M_key_compare( __k , _S_key( __x ) );
        __x = __comp ? _S_left( __x ) : _S_right( __x );
    }
    // __y is the node upper than __k , check if there is the node equals to __k
    iterator __j = iterator( __y );
    if( __comp ) {
        if( __j == begin() )
            return _Res( __x , __y );
        else 
            -- __j;
    }
    if( _M_impl._M_key_compare( _S_key( __j._M_node ) , __k ) )
        return _Res( __x , __y );
    return _Res( __j._M_node , 0 );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
std::pair<typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_Base_ptr,
    typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_Base_ptr> 
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
_M_get_insert_hint_unique_pos( const_iterator __position , const key_type& __k ) {
    iterator __pos = __position._M_const_cast( );
    typedef std::pair<_Base_ptr, _Base_ptr> _Res;

    if( __pos._M_node == _M_end( ) ) {
        if( size() > 0 && _M_impl._M_key_compare( _S_key( _M_rightmost() ) , __k ) )
            return _Res( 0 , _M_rightmost() );
        else
            return _M_get_insert_unique_pos( __k );
    } else if( _M_impl._M_key_compare( __k , _S_key( __pos._M_node ) ) ) {
        iterator __before = __pos;
        if( __pos._M_node == _M_leftmost() ) {
            return _Res( _M_leftmost() , _M_leftmost() );
        } else if( _M_impl._M_key_compare( _S_key( ( -- __before )._M_node ) , __k ) ) {
            if( _S_right( __before._M_node ) == 0 )
                return _Res( 0 , __before._M_node );
            else 
                return _Res( __pos._M_node , __pos._M_node );
        } else 
            return _M_get_insert_unique_pos( __k );
    } else if( _M_impl._M_key_compare( _S_key( __pos._M_node ) , __k ) ) {
        iterator __after = __pos;
        if( __pos._M_node == _M_rightmost( ) )
            return _Res( 0 , _M_rightmost( ) );
        else if( _M_impl._M_key_compare( __k , _S_key( ( ++__after )._M_node ) ) ) {
            if( _S_right( __pos._M_node ) == 0 )
                return _Res( 0 , __pos._M_node );
            else 
                return _Res( __after._M_node ,  __after._M_node );
        } else
            return _M_get_insert_unique_pos( __k );
    } else 
        return _Res( __pos._M_node , 0 );
}

/*
 * Insert __v
 * Return value: pair of insert place(iterator) and state of insertion(true:success, false:fail)
 * Get insert place and judge if it is a unique place
 */
template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
template<typename _Arg> 
std::pair<typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator,bool> 
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_M_insert_unique( _Arg&& __v ) {
    using _Res = std::pair<iterator,bool>;
    std::pair<_Base_ptr,_Base_ptr> __res = _M_get_insert_unique_pos( _KeyOfValue()( __v ) );
    if( __res.second ) {
        _Alloc_node _an( *this );
        return _Res( _M_insert_( __res.first , __res.second , std::forward<_Arg>( __v ) , _an ) , true );
    }
    return _Res( iterator( static_cast<_Link_type>( __res.first ) ) , false );
}

template<typename _Key , typename _Val , typename _KeyOfValue , typename _Compare , typename _Alloc> 
template<typename _Arg , typename _NodeGen>
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator 
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_M_insert_unique_( const_iterator __position , _Arg&& __v , _NodeGen& __node_gen ) {
    using _Res = std::pair<iterator,bool>;
    std::pair<_Base_ptr,_Base_ptr> __res = _M_get_insert_hint_unique_pos( __position , _KeyOfValue()( __v ) );
    if( __res.second ) {
        return _M_insert_( __res.first , __res.second , std::forward<_Arg>( __v ) , __node_gen );
    }
    return iterator( __res.first );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_M_lower_bound( _Link_type __x , _Link_type __y , const _Key& __k ) {
    while( __x != 0 ) {
        if( !_M_impl._M_key_compare( _S_key( __x ) , __k ) )
            __y = __x , __x = _S_left( __x );
        else 
            __x = _S_right( __x );
    }
    return iterator( __y );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::const_iterator
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_M_lower_bound( _Const_Link_type __x , _Const_Link_type __y , const _Key& __k ) const {
    while( __x != 0 ) {
        if( !_M_impl._M_key_compare( _S_key( __x ) , __k ) )
            __y = __x , __x = _S_left( __x );
        else 
            __x = _S_right( __x );
    }
    return const_iterator( __y );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_M_upper_bound( _Link_type __x , _Link_type __y , const _Key& __k ) {
    while( __x != 0 ) {
        if( _M_impl._M_key_compare( __k , _S_key( __x ) ) )
            __y = __x , __x = _S_left( __x );
        else 
            __x = _S_right( __x );
    }
    return iterator( __y );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::const_iterator
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::_M_upper_bound( _Const_Link_type __x , _Const_Link_type __y , const _Key& __k ) const {
    while( __x != 0 ) {
        if( _M_impl._M_key_compare( __k , _S_key( __x ) ) )
            __y = __x , __x = _S_left( __x );
        else 
            __x = _S_right( __x );
    }
    return const_iterator( __y );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
template<typename _Arg , typename _Node_gen>
typename _Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Sb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_M_insert_( _Base_ptr __x , _Base_ptr __p , _Arg&& __v , _Node_gen& __node_gen ) {
    // ? when __x not 0
    bool __insert_left = ( __x != 0 || __p == _M_end() || 
        _M_impl._M_key_compare( _KeyOfValue()( __v ) , _S_key( __p ) ) );
    _Link_type __z = __node_gen( std::forward<_Arg>( __v ) );

    _Sb_tree_insert_and_rebalance( __insert_left , __z , __p , this -> _M_impl._M_header );
    // insert & rebalance & maintain size
    return iterator( __z );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
void
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
_M_erase_aux( const_iterator __position ) {
    _Link_type __y = static_cast<_Link_type>( _Sb_tree_rebalance_for_erase( const_cast<_Base_ptr>( __position._M_node ) , this -> _M_impl._M_header ) );
    _M_destroy_node( __y );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::size_type 
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
erase( const key_type& __x ) {
    // no equal range
    iterator __p = find( __x );
    if( __p == end() ) return 0;
    const size_type __old_size = _M_end() -> _M_size;
    _M_erase_aux( __p );
    return __old_size - size();
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
void
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
_M_erase( _Link_type __x ) {
    // destroy the whole subtree without rebalancing.
    while( __x != 0 ) {
        _M_erase( _S_right( __x ) );
        _Link_type __y = _S_left( __x );
        _M_destroy_node( __x );
        __x = __y;
    }
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator 
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
find( const _Key& __k ) {
    iterator __j = _M_lower_bound( _M_begin() , _M_end() , __k );
    return ( __j == end( ) || _M_impl._M_key_compare( __k , _S_key( __j._M_node ) ) ? end() : __j );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
find( const _Key& __k ) const {
    const_iterator __j = _M_lower_bound( _M_begin() , _M_end() , __k );
    return ( __j == end( ) || _M_impl._M_key_compare( __k , _S_key( __j._M_node ) ) ? end() : __j );
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::size_type
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
count( const _Key& __k ) const {
    if( find( __k ) != end() ) return 1;
    return 0;
}

template<typename _Key , typename _Val , typename _KeyOfValue , 
    typename _Compare , typename _Alloc> 
typename _Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::size_type
_Sb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::
_M_get_pos( _Base_ptr __x ) {
    return _Sb_tree_get_lower_size( __x );
}

}