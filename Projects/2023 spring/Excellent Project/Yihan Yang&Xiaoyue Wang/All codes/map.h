#pragma once
#include <tuple>
#include <functional>

// Used in official documents
// But I replace it with #include <exception>
// #include <bits/functexcept.h>
// #include <bits/concept_check.h>

//using _Sb_tree
#include <_SB_tree.h>
//using std::_Select1st<>
// #include <bits/stl_function.h>
//using std::logic_error
#include <stdexcept>

namespace Project{

template<typename _Key,typename _Tp,typename _Compare=std::less<_Key>,typename _Alloc=std::allocator<std::pair<const _Key,_Tp>>>

class map{
    public:
        //define type
        typedef _Key					        key_type;
        typedef _Tp					            mapped_type;
        typedef std::pair<const _Key,_Tp>		value_type;
        typedef _Compare					    key_compare;
        typedef _Alloc					        allocator_type;

        //define a functor to compare value
        //It is derived from std::binary_function
        //When the key is the same, it returns true
        //else it returns false
        class value_compare:public std::binary_function<value_type,value_type,bool>{
            friend class map<_Key,_Tp,_Compare,_Alloc>;
            protected:
                _Compare comp;
                value_compare(_Compare _c):comp(_c){};
            public:
                bool operator()(const value_type& _x,const value_type& _y)const{
                    return comp(_x.first,_y.first);
                }
        };

    private:
        //define type
        typedef _Sb_tree::_Sb_tree<key_type,value_type,
        std::_Select1st<value_type>,key_compare,allocator_type> rep_type;
        //using _Sb_tree
        rep_type t;

    public:
        //define type
        //To use types in _Sb_tree,
        //like iterator,const iterator,etc. 
        typedef typename rep_type::pointer pointer;
        typedef typename rep_type::const_pointer const_pointer;
        typedef typename rep_type::reference reference;
        typedef typename rep_type::const_reference const_reference;
        typedef typename rep_type::iterator iterator;
        typedef typename rep_type::const_iterator const_iterator;
        // typedef typename rep_type::reverse_iterator reverse_iterator;
        // typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
        typedef typename rep_type::size_type size_type;
        // typedef typename rep_type::difference_type difference_type;
        
        //constructor & destructor

        //default constructor
        map()=default;

        //constructor for custom types
        //When you need to construct by all parameters,
        //it will call this constructor below
        explicit map(const _Compare& comp,
        const allocator_type& a=allocator_type())
        :t(comp,a){}

        //default copy constructor
        map(const map&)=default;

        //default move constructor
        map(map&&)=default;

        //initializer_list constructor
        //By calling the method from _Sb_tree
        map(std::initializer_list<value_type> list,
	    const _Compare& comp=_Compare(),
	    const allocator_type& a=allocator_type())
        :t(comp,a)
        {t._M_insert_range_unique(list.begin(),list.end());}

        //allocator constructor
        explicit map(const allocator_type& a):t(a){}

        //iterator constructor
        template<typename _InputIterator>
	    map(_InputIterator first,_InputIterator last):t()
	    {t._M_insert_range_unique(first,last);}

        template<typename _InputIterator>
	    map(_InputIterator first,_InputIterator last,
	    const _Compare& comp,
	    const allocator_type& a=allocator_type())
	    :t(comp,a){t._M_insert_range_unique(first,last);}

        //default destructor
        ~map()=default;

        //overload = to copy
        map& operator=(const map&)=default;

        //overload = to move
        map& operator=(map&&)=default;

        //overload = to initialize by initializer_list
        map& operator=(std::initializer_list<value_type> list){
	        t._M_assign_unique(list.begin(),list.end());
	        return *this;
        }

        //overload []

        // insert()'s efficiency is poorer than emplce
        // I don't desire to call this method below.  
        mapped_type& operator[](const key_type& k){
            iterator i=lower_bound(k);
            if(i==end()||key_comp()(k,(*i).first))
                return (*(insert(value_type(k,_Tp()))).first).second;
            return (*i).second;
        }

        //overload []
        // mapped_type& operator[](const key_type& k){
        //     iterator i=lower_bound(k);
        //     if(i==end()||key_comp()(k,(*i).first))
        //     //avoid using std::make_pair,
        //     //can avoid copy and move
        //     //std::piecewise_construct tells the compiler to 
        //     //pass the key and value seperately.
        //     //In this way it will improve a lot of efficiency
        //     i=t._M_emplace_hint_unique(i,std::piecewise_construct,std::tuple<const key_type&>(k),std::tuple<>());
        //     return (*i).second;
        // }

        //overload [],pass the key by moving(pass a rvalue)
        mapped_type& operator[](key_type&& k){
            iterator i=lower_bound(k);
            if(i==end()||key_comp()(k,(*i).first))
            //perfect forwarding
            i=insert(i,value_type( k , mapped_type( ) ));
            return (*i).second;
        }

        //use tree's iterator
        iterator begin(){return t.begin();}
        const_iterator begin()const{return t.begin();}
        iterator end(){return t.end();}
        const_iterator end()const{return t.end();}
        iterator rbegin(){return t.rbegin();}
        const_iterator rbegin()const{return t.rbegin();}
        iterator rend(){return t.rend();}
        const_iterator rend()const{return t.rend();}

        //empty
        bool empty()const{return t.empty();}

        //size
        size_type size()const{return t.size();}
        
        size_type max_size()const{return t.max_size();}
        
        //insert
        //call the tree's method _M_insert_unique()
        std::pair<iterator,bool> insert(const value_type& x){
            return t._M_insert_unique(x);
        }

        std::pair<iterator, bool> insert(value_type&& x){
            return t._M_insert_unique(std::move(x));
        }

        iterator insert(iterator pos,const value_type& x){
            return t._M_insert_unique_(pos,x);
        }

        iterator insert(iterator pos,value_type&& x){
            return t._M_insert_unique_(pos,std::move(x));
        }

        void insert(const value_type* first,const value_type* last){
            t._M_insert_unique(first,last);
        }

        void insert(const_iterator first,const_iterator last){
            t._M_insert_unique(first,last);
        }

        void insert(std::initializer_list<value_type> list){
            insert(list.begin(), list.end());
        }

        //erase
        //call the tree's method
        //three ways to erase
        //1. by iterator
        //2. by key
        //3. scope deletion
        iterator erase(iterator pos){return t.erase(pos);}

        size_type erase(const key_type& k){return t.erase(k);}

        iterator erase(iterator first,iterator last){return t.erase(first,last);}

        //find
        //in a normal obj and in a const obj
        iterator find(const key_type& k){return t.find(k);}

        const_iterator find(const key_type& k)const{return t.find(k);}

        //count
        size_type count(const key_type& k)const{return t.count(k);}

        //swap
        void swap(map<_Key,_Tp,_Compare,_Alloc>& x){t.swap(x.t);}

        //lowerbound
        iterator lower_bound(const key_type& k){return t.lower_bound(k);}
        const_iterator lower_bound(const key_type& k)const{return t.lower_bound(k);}

        //upper_bound
        iterator upper_bound(const key_type& k){return t.upper_bound(k);}
        const_iterator upper_bound(const key_type& k)const{return t.upper_bound(k);}

        // //equal_range
        // map don't need this method
        // std::pair<iterator,iterator> equal_range(const key_type& k){return t.equal_range(k);}
        // std::pair<const_iterator,const_iterator> equal_range(const key_type& k)const{return t.equal_range(k);}

        //overload ==
        template<typename _K,typename _T,typename _C,typename _A>
        friend inline bool operator==(const map<_K,_T,_C,_A>&,const map<_K,_T,_C,_A>&);
        //overload <
        template<typename _K,typename _T,typename _C,typename _A>
        friend inline bool operator<(const map<_K,_T,_C,_A>&,const map<_K,_T,_C,_A>&);

        //at
        mapped_type& at(const key_type& k){
            iterator it=lower_bound(k);
            //use a functor to check
            //In default situation, When k==it->first, it returns ture
            //else it returns false 
            if(it==end()||key_comp()(k,it->first)){
                //in bits/functexpect.h
                // __throw_out_of_range(__N("map::at"));
                //I use a more ordinary way to realise the same function
                throw std::logic_error("Not Found");
            }
            return it->second;
        }
        
        //used in const obj
        const mapped_type& at(const key_type& k)const{
            const_iterator it=lower_bound(k);
            if(it==end()||key_comp()(k,it->first)){
                //in bits/functexpect.h
                // __throw_out_of_range(__N("map::at"));
                throw std::logic_error("Not Found");
            }
            return it->second;
        }

        //observer
        key_compare key_comp()const{return t.key_comp();}
        value_compare value_comp()const{return value_compare(t.key_comp());}

        //emplace
        //When _args is const&, it calls emplace by copying
        //when _args is &&, it calls emplace by moving
        //It returns a pair<iterator, bool> 
        template<typename... _Args>
        std::pair<iterator,bool> emplace(_Args... _args){
            return t._M_emplace_unique(std::forward<_Args>(_args)...);
        }

        //emplace_hint
        //If found
        //it returns the key's iterator
        //else it returns the new iterator
        //Also perfect forwarding
        template<typename... _Args>
        iterator emplace_hint(const_iterator _Pos,_Args&&... _args){
            return t._M_emplace_hint_unique(_Pos,std::forward<_Args>(_args)...);
        }

        void try_debug( ) {
            t.try_debug( );
        }
        
};

template<typename _Key,typename _Tp,typename _Compare,typename _Alloc>
inline bool operator==(const map<_Key,_Tp,_Compare,_Alloc>& x,const map<_Key,_Tp,_Compare,_Alloc>& y){
    return x.t==y.t;
}

template<typename _Key,typename _Tp,typename _Compare,typename _Alloc>
inline bool operator<(const map<_Key,_Tp,_Compare,_Alloc>& x,const map<_Key,_Tp,_Compare,_Alloc>& y){
    return x.t<y.t;
}

//based on == and <
//to overload the other compare operator
template<typename _Key,typename _Tp,typename _Compare,typename _Alloc>
inline bool operator!=(const map<_Key,_Tp,_Compare,_Alloc>& x,const map<_Key,_Tp,_Compare,_Alloc>& y){
    return !(x==y);
}

template<typename _Key,typename _Tp,typename _Compare,typename _Alloc>
inline bool operator>(const map<_Key,_Tp,_Compare,_Alloc>& x,const map<_Key,_Tp,_Compare,_Alloc>& y){
    return y<x;
}

template<typename _Key,typename _Tp,typename _Compare,typename _Alloc>
inline bool operator<=(const map<_Key,_Tp,_Compare,_Alloc>& x,const map<_Key,_Tp,_Compare,_Alloc>& y){
    return !(y<x);
}

template<typename _Key,typename _Tp,typename _Compare,typename _Alloc>
inline bool operator>=(const map<_Key,_Tp,_Compare,_Alloc>& x,const map<_Key,_Tp,_Compare,_Alloc>& y){
    return !(x<y);
}

}