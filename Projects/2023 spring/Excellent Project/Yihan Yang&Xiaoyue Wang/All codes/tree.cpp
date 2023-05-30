// implementations for Size Balanced Tree
#include "_SB_tree.h"

namespace _Sb_tree {

size_t _S_size( _Sb_tree_node_base* __x ) {
    return __x == 0 ? 0 : __x -> _M_size;
}

static _Sb_tree_node_base*
local_Sb_tree_increment( _Sb_tree_node_base* __x ) noexcept {
    if( __x -> _M_right != 0 ) {
        __x = __x -> _M_right;
        while( __x -> _M_left != 0 )
            __x = __x -> _M_left;
    } else {
        _Sb_tree_node_base *__y = __x -> _M_parent;
        while( __x == __y -> _M_right ) {
            __x = __y;
            __y = __y -> _M_parent;
        }
        if( __x -> _M_right != __y )
            __x = __y; // when root is the largest
    }
    return __x;
}

_Sb_tree_node_base* 
_Sb_tree_increment( _Sb_tree_node_base *__x ) noexcept {
    return local_Sb_tree_increment( __x );
}

const _Sb_tree_node_base* 
_Sb_tree_increment( const _Sb_tree_node_base *__x ) noexcept {
    return local_Sb_tree_increment( const_cast<_Sb_tree_node_base*>( __x ) );
}

static _Sb_tree_node_base*
local_Sb_tree_decrement( _Sb_tree_node_base *__x ) noexcept {
    if( __x -> _M_parent -> _M_parent == __x && __x -> _M_size == __x -> _M_parent -> _M_size + 1 ) 
        __x = __x -> _M_right;
    else if( __x -> _M_left != 0 ) {
        __x = __x -> _M_left;
        while( __x -> _M_right != 0 ) 
            __x = __x -> _M_right;
    } else {
        _Sb_tree_node_base *__y = __x -> _M_parent;
        while( __x == __y -> _M_left ) {
            __x = __y;
            __y = __y -> _M_parent;
        }
        __x = __y;
    }
    return __x;
}

_Sb_tree_node_base* 
_Sb_tree_decrement( _Sb_tree_node_base *__x ) noexcept {
    return local_Sb_tree_decrement( __x );
}

const _Sb_tree_node_base* 
_Sb_tree_decrement( const _Sb_tree_node_base *__x ) noexcept {
    return local_Sb_tree_decrement( const_cast<_Sb_tree_node_base*>( __x ) );
}

static _Sb_tree_node_base*
local_Sb_tree_increment( _Sb_tree_node_base *__x , size_t __k ) noexcept {
    _Sb_tree_node_base *__y;
    bool __f = true;

    while( !__f || __k > _S_size( __x -> _M_right ) ) {
        if( __f )
            __k -= _S_size( __x -> _M_right ) + 1;
        __y = __x -> _M_parent;
        __f = __y -> _M_left == __x;
        __x = __y;
        if( __x -> _M_parent -> _M_parent == __x && __x -> _M_parent -> _M_size + 1 == __x -> _M_size )
            return __x;
    }

    if( __k == 0 ) return __x;
    -- __k;
    __x = __x -> _M_right;
    while( __k != _S_size( __x -> _M_left ) ) {
        if( _S_size( __x -> _M_left ) > __k )
            __x = __x -> _M_left;
        else {
            __k -= _S_size( __x -> _M_left ) + 1;
            __x = __x -> _M_right;
        }
    }
    return __x;
}

_Sb_tree_node_base* 
_Sb_tree_increment( _Sb_tree_node_base *__x , size_t __k ) noexcept {
    return local_Sb_tree_increment( __x , __k );
}

const _Sb_tree_node_base* 
_Sb_tree_increment( const _Sb_tree_node_base *__x , size_t __k ) noexcept {
    return local_Sb_tree_increment( const_cast<_Sb_tree_node_base*>( __x ) , __k );
}

static _Sb_tree_node_base*
local_Sb_tree_decrement( _Sb_tree_node_base *__x , size_t __k ) noexcept {
    if( __k == 0 ) return __x;
    
    if( __x -> _M_parent -> _M_parent == __x && __x -> _M_size == __x -> _M_parent -> _M_size + 1 ) 
        -- __k , __x = __x -> _M_right;

    _Sb_tree_node_base *__y;
    bool __f = true;

    while( !__f || __k > _S_size( __x -> _M_left ) ) {
        if( __f )
            __k -= _S_size( __x -> _M_left ) + 1;
        __y = __x -> _M_parent;
        __f = __y -> _M_right == __x;
        __x = __y;
    }

    if( __k == 0 ) return __x;
    -- __k;
    __x = __x -> _M_left;
    while( __k != _S_size( __x -> _M_right ) ) {
        if( _S_size( __x -> _M_right ) > __k )
            __x = __x -> _M_right;
        else {
            __k -= _S_size( __x -> _M_right ) + 1;
            __x = __x -> _M_left;
        }
    }
    return __x;
}

_Sb_tree_node_base* 
_Sb_tree_decrement( _Sb_tree_node_base *__x , size_t __k ) noexcept {
    return local_Sb_tree_decrement( __x , __k );
}

const _Sb_tree_node_base* 
_Sb_tree_decrement( const _Sb_tree_node_base *__x , size_t __k ) noexcept {
    return local_Sb_tree_decrement( const_cast<_Sb_tree_node_base*>( __x ) , __k );
}

static void
local_Sb_tree_update_size( _Sb_tree_node_base* const __x ) {
    __x -> _M_size = _S_size( __x -> _M_left ) + _S_size( __x -> _M_right ) + 1;
}

static void 
local_Sb_tree_rotate_left( _Sb_tree_node_base* const __x , _Sb_tree_node_base*& __root ) {
    _Sb_tree_node_base *const __y = __x -> _M_right;
    __x -> _M_right = __y -> _M_left;
    if( __y -> _M_left != 0 )
        __y -> _M_left -> _M_parent = __x;
    __y -> _M_parent = __x -> _M_parent;
    
    if( __x == __root )
        __root = __y;
    else if( __x == __x -> _M_parent -> _M_left )
        __x -> _M_parent -> _M_left = __y;
    else 
        __x -> _M_parent -> _M_right = __y;

    __y -> _M_left = __x;
    __x -> _M_parent = __y;

    local_Sb_tree_update_size( __x );
    local_Sb_tree_update_size( __y );
}

static void 
local_Sb_tree_rotate_right( _Sb_tree_node_base* const __x , _Sb_tree_node_base*& __root ) {
    _Sb_tree_node_base *const __y = __x -> _M_left;
    __x -> _M_left = __y -> _M_right;
    if( __y -> _M_right != 0 )
        __y -> _M_right -> _M_parent = __x;
    __y -> _M_parent = __x -> _M_parent;
    
    if( __x == __root )
        __root = __y;
    else if( __x == __x -> _M_parent -> _M_right )
        __x -> _M_parent -> _M_right = __y;
    else 
        __x -> _M_parent -> _M_left = __y;

    __y -> _M_right = __x;
    __x -> _M_parent = __y;

    local_Sb_tree_update_size( __x );
    local_Sb_tree_update_size( __y );
}


void local_rebalance( _Sb_tree_node_base* __x , _Sb_tree_node_base*& __root ) {
    if( __x == 0 ) return;
    if( __x -> _M_left != 0 ) {
        if( _S_size( __x -> _M_left -> _M_left ) > _S_size( __x -> _M_right ) ) {
            local_Sb_tree_rotate_right( __x , __root );
            local_rebalance( __x -> _M_right , __root );
            local_rebalance( __x , __root );
            return;
        } else if( _S_size( __x -> _M_left -> _M_right ) > _S_size( __x -> _M_right ) ) {
            local_Sb_tree_rotate_left( __x -> _M_left , __root );
            local_Sb_tree_rotate_right( __x , __root );
            local_rebalance( __x -> _M_left , __root );
            local_rebalance( __x -> _M_right , __root );
            local_rebalance( __x , __root );
            return;
        }
    }

    if( __x -> _M_right != 0 ) {
        if( _S_size( __x -> _M_right -> _M_right ) > _S_size( __x -> _M_left ) ) {
            local_Sb_tree_rotate_left( __x , __root );
            local_rebalance( __x -> _M_left , __root );
            local_rebalance( __x , __root );
            return;
        } else if( _S_size( __x -> _M_right -> _M_left ) > _S_size( __x -> _M_left ) ) {
            local_Sb_tree_rotate_right( __x -> _M_right , __root );
            local_Sb_tree_rotate_left( __x , __root );
            local_rebalance( __x -> _M_left , __root );
            local_rebalance( __x -> _M_right , __root );
            local_rebalance( __x , __root );
            return;
        }
    }
}

// here this function only cares about insertion of node and structure( size , balance )
void _Sb_tree_insert_and_rebalance( const bool __insert_left , 
_Sb_tree_node_base* __x , _Sb_tree_node_base* __p , 
_Sb_tree_node_base& __header ) noexcept {
    _Sb_tree_node_base *& __root = __header._M_parent;

    // initialize
    __x -> _M_parent = __p;
    __x -> _M_left = 0;
    __x -> _M_right = 0;
    __x -> _M_size = 0;

    // insert
    if( __insert_left ) {
        __p -> _M_left = __x; // when __p == &_header, also sets leftmost

        if( __p == &__header ) {
            __header._M_parent = __x;
            __header._M_right = __x;
        } else if( __p == __header._M_left )
            __header._M_left = __x;
    } else {
        __p -> _M_right = __x;
        if( __p == __header._M_right )
            __header._M_right = __x;
    }

    // rebalance and maintain size
    _Sb_tree_node_base* __y = __x -> _M_parent;
    while( __x != &__header ) {
        __y = __x -> _M_parent;
        ++ __x -> _M_size;
        local_rebalance( __x , __root );
        __x = __y;
    }

    ++ __x -> _M_size;
}

_Sb_tree_node_base*
_Sb_tree_rebalance_for_erase( _Sb_tree_node_base* const __z , _Sb_tree_node_base& __header ) noexcept {
    _Sb_tree_node_base *& __root = __header._M_parent;
    _Sb_tree_node_base *& __leftmost = __header._M_left;
    _Sb_tree_node_base *& __rightmost = __header._M_right;
    _Sb_tree_node_base *__y = __z;
    _Sb_tree_node_base *__x = 0;
    _Sb_tree_node_base *__x_parent = 0;
    
    if( __y -> _M_left == 0 )
        __x = __y -> _M_right;
    else if( __y -> _M_right == 0 )
        __x = __y -> _M_left;
    else {
        __y = __y -> _M_right;
        while( __y -> _M_left != 0 )
            __y = __y -> _M_left;
        __x = __y -> _M_right;
    }

    if( __y != __z ) {
        __z -> _M_left -> _M_parent = __y;
        __y -> _M_left = __z -> _M_left;
        if( __y != __z -> _M_right ) {
            __x_parent = __y -> _M_parent;
            if( __x ) __x -> _M_parent = __y -> _M_parent;
            __y -> _M_parent -> _M_left = __x;
            __y -> _M_right = __z -> _M_right;
            __z -> _M_right -> _M_parent = __y;
        } else
            __x_parent = __y;
        if( __root == __z )
            __root = __y;
        else if( __z -> _M_parent -> _M_left == __z )
            __z -> _M_parent -> _M_left = __y;
        else if( __z -> _M_parent -> _M_right == __z )
            __z -> _M_parent -> _M_right = __y;
        __y -> _M_parent = __z -> _M_parent;
        __y = __z;
        // __y points to the node actually deleted.
    } else {
        __x_parent = __y -> _M_parent;
        if( __x )
            __x -> _M_parent = __y -> _M_parent;
        if( __root == __z )
            __root = __x;
        else if( __z -> _M_parent -> _M_left == __z )
            __z -> _M_parent -> _M_left = __x;
        else 
            __z -> _M_parent -> _M_right = __x;
        if( __leftmost == __z ) {
            if( __z -> _M_right == 0 )
                __leftmost = __z -> _M_parent; // if __z is __root then __leftmost is _M_header
            else 
                __leftmost = _Sb_tree_node_base::_S_minimum( __x );
        }
        if( __rightmost == __z ) {
            if( __z -> _M_left == 0 ) 
                __rightmost = __z -> _M_parent;
            else
                __rightmost = __z -> _Sb_tree_node_base::_S_maximum( __x );
        }
    }

    // rebalance and maintain size
    _Sb_tree_node_base *__t = 0 , *__s = __x_parent;
    while( __s != &__header ) {
        __t = __s -> _M_parent;
        __s -> _M_size = _S_size( __s -> _M_left ) + _S_size( __s -> _M_right ) + 1;
        local_rebalance( __s , __root );
        __s = __t;
    }
    __s -> _M_size = _S_size( __s -> _M_parent ) + 1;

    return __y;
}

static size_t local_Sb_tree_get_lower_size( _Sb_tree_node_base* __x ) {
    if( __x -> _M_parent -> _M_parent == __x && __x -> _M_size == __x -> _M_parent -> _M_size + 1 ) {
        return __x -> _M_size - 1;
    }
    size_t __ret = _S_size( __x -> _M_left );
    _Sb_tree_node_base* __y;
    while( __x -> _M_parent -> _M_parent != __x ) {
        __y = __x -> _M_parent;
        if( __x == __y -> _M_right )
            __ret += _S_size( __y -> _M_left ) + 1;
        __x = __y;
    }
    return __ret;
}

size_t _Sb_tree_get_lower_size( _Sb_tree_node_base* __x ) noexcept {
    return local_Sb_tree_get_lower_size( __x );
}

const size_t _Sb_tree_get_lower_size( const _Sb_tree_node_base* __x ) noexcept {
    return local_Sb_tree_get_lower_size( const_cast<_Sb_tree_node_base*>( __x ) );
}
    
}