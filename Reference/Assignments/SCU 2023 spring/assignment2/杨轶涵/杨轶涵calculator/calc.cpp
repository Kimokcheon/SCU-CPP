#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <random>
#include <chrono>
#include <climits>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct num {
    double v;
    double overdot;

    num( ) : v( 0 ) , overdot( false ) {}
    num( double x ) : v(x) , overdot( false ) {}

    void append( char c ) {
        if( c == '.' ) overdot = 1;
        else {
            if( overdot ) overdot = overdot * 0.1 , v = v + ( c - '0' ) * overdot;
            else v = v * 10 + ( c - '0' );
        }
    }

    num operator + ( const num& c ) { return num( v + c.v ); }
    num operator - ( const num& c ) { return num( v - c.v ); }
    num operator * ( const num& c ) { return num( v * c.v ); }
    num operator / ( const num& c ) { return num( v / c.v ); }
};

stack<num> val_stk;
stack<char> op_stk;
map<string,char> sp_op { {"sqrt",'s'} , {"exp",'e'} , {"abs",'a'} , {"max",'x'} , {"random",'r'} , {"sin",'i'} };
map<string,double> constant_val { {"PI",acos( -1. )} , {"E",exp( 1 )} };
map<string,double> vars;
const set<char> reserved { '+' , '-' , '*' , '/' , '(' , ')' , ',' };
bool exc;
const double eps = 1e-9;

int sgn( double x ) {
    if( fabs( x ) < eps ) return 0;
    return x > 0 ? 1 : -1;
}

int level( char c ) {
    if( c == '+' || c == '-' ) return 0;
    if( c == '*' || c == '/' ) return 1;
    return -1;
}

bool calc_once( ) {
    if( op_stk.empty() || level( op_stk.top() ) == -1 ) return false;
    double rv = val_stk.top().v;
    val_stk.pop();
    double lv = val_stk.top().v;
    val_stk.pop();
    char o = op_stk.top();
    op_stk.pop();
    if( o == '+' ) val_stk.push( lv + rv );
    if( o == '-' ) val_stk.push( lv - rv );
    if( o == '*' ) val_stk.push( lv * rv );
    if( o == '/' ) {
        if( sgn( rv ) == 0 ) {
            puts("#INFINITE");
            exc = true;
            return false;
        }
        val_stk.push( lv / rv );
    }
    
    return true;
}

void math_fun( char o ) {
    double v = val_stk.top().v; val_stk.pop();
    if( o == 's' ) {
        if( v < 0 ) {
            puts("Not a real number (error message)");
            exc = true;
            return;
        }
        val_stk.push( sqrt( v ) );
    } else if( o == 'e' ) {
        val_stk.push( exp( v ) );
    } else if( o == 'a' ) {
        val_stk.push( abs( v ) );
    } else if( o == 'x' ) {
        double lv = val_stk.top().v; val_stk.pop();
        val_stk.push( max( lv , v ) );
    } else if( o == 'r' ) {
        unsigned int x = rng();
        if( sgn( v ) == 0 ) 
            val_stk.push( x );
        else
            val_stk.push( ( x * 1. / UINT_MAX ) * v );
    } else if( o == 'i' ) {
        val_stk.push( sin( v ) );
    } else 
        assert( 0 );
}

bool flush_name( string& name ) {
    if( sp_op.count( name ) ) op_stk.push( sp_op[name] );
    else if( constant_val.count( name ) ) val_stk.push( constant_val[name] );
    else if( vars.count( name ) ) val_stk.top().v = vars[name];
    else {
        puts("The variable does not exist! (error message)");
        exc = true;
        return false;
    }
    name = "";
    return true;
}

string naming;

void calc( string::iterator spos , const string::iterator epos ) {
    if( spos == epos ) {
        if( naming.size( ) ) flush_name( naming );
        if( exc ) return;
        while( calc_once( ) );
        if( exc ) return;
        if( !op_stk.empty() ) {
            puts("The bracket is not matching! (error message)");
            exc = true;
        }
        return;
    }

    if( *spos == ' ' ) {
        return calc( spos + 1 , epos );
    }

    if( !naming.size() && ( *spos >= 'a' && *spos <= 'z' || *spos >= 'A' && *spos <= 'Z' || *spos == '_' ) ) {
        naming.push_back( *spos );
        return calc( spos + 1 , epos );
    }
    
    if( naming.size() && !reserved.count( *spos ) ) {
        naming.push_back( *spos );
        return calc( spos + 1 , epos );
    }

    if( naming.size() ) {
        flush_name( naming );
        if( exc ) return;
    }

    char &cp = *spos;
    if( ( cp >= '0' && cp <= '9' ) || cp == '.' ) val_stk.top().append( cp );
    if( level( cp ) != -1 ) {
        while( !op_stk.empty() && level( op_stk.top() ) >= level( cp ) ) 
            calc_once( );
        if( exc ) return;
        op_stk.push( cp ) , val_stk.push( 0 );
    }
    if( cp == ',' ) {
        while( calc_once( ) );
        val_stk.push( 0 );
        if( exc ) return;
    }
    if( cp == ')' ) {
        while( calc_once( ) );
        if( exc ) return;
        if( op_stk.empty() || op_stk.top() != '(' ) {
            puts("The bracket is not matching! (error message)");
            exc = true;
            return;
        }
        op_stk.pop( );
        if( !op_stk.empty() && !reserved.count( op_stk.top() ) ) {
            math_fun( op_stk.top() );
            op_stk.pop();
        }
    }
    if( cp == '(' ) {
        op_stk.push( '(' );
    }
    calc( spos + 1 , epos );
}

int main() {
    string S;
    while( getline( cin , S ) ) {
        if( S == "quit()" ) break; 
        while( !val_stk.empty() ) val_stk.pop();
        while( !op_stk.empty() ) op_stk.pop();
        naming = "";
        exc = false;
        if( S.find( '=' ) == S.npos ) {
            val_stk.push( 0. );
            calc( S.begin() , S.end() );
            if( !exc ) 
                cout << setprecision( 12 ) << val_stk.top().v << endl;
        } else {
            string name = S.substr( 0 , S.find( '=' ) );
            while( name.back() == ' ' ) name.pop_back();
            while( *name.begin() == ' ' ) name.erase( *name.begin() );
            if( !( ( name[0] >= 'a' && name[0] <= 'z' ) || ( name[0] >= 'A' && name[0] <= 'Z' ) || name[0] == '_' ) ) {
                puts("The variable name is not valid! (error message)");
                continue;
            }
            if( sp_op.count( name ) || name.find( ' ' ) != name.npos ) {
                puts("The variable name is not valid! (error message)");
                continue;
            }
            for( const auto& c : reserved ) if( name.find( c ) != name.npos ) {
                exc = true;
                puts("The variable name is not valid! (error message)");
                break;
            }
            if( exc ) continue;
            if( constant_val.count( name ) ) {
                puts("This is constant value. Cannot be changed! (error message)");
                continue;
            }
            string equ = S.substr( S.find( '=' ) + 1 , S.size() );
            val_stk.push( 0. );
            calc( equ.begin() , equ.end() );
            if( !exc )
                vars[name] = val_stk.top().v;
        }
    }
}
