//
// Created by Chris Jurich  on 9/5/20.
//
#ifndef PRETTY_PRING_PRETTY_PRINT_H
#define PRETTY_PRING_PRETTY_PRINT_H

#include <iostream>
#include <cxxabi.h>
#include <vector>


#include <map>
#include <unordered_map>

//TODO the rest of the STL
//TODO add macros to check for compatability
//TODO check user-defined types for iterators

namespace pretty {

    typedef char yes;
    typedef char (&no)[2];

    struct anyx { template <class T> anyx(const T &); };

    no operator << (const anyx &, const anyx &);
    no operator >> (const anyx &, const anyx &);


    template <class T> yes check(T const&);
    no check(no);

    template <typename StreamType, typename T>
    struct has_left_shift {
        static StreamType &stream;
        static T &x;
        static const bool value = sizeof(check(stream << x)) == sizeof(yes);
    };

    template<typename T>
    std::string
    _clean_name(T const & t) {
        return std::string{
            abi::__cxa_demangle(typeid(t).name(),
                    nullptr,
                    nullptr,
                    nullptr
                    )
        };
    }

    template <typename K, typename V>
    std::string
    _clean_name(std::unordered_map<K,V>const & map) {
        return "std::unordered_map<" + _clean_name(map.begin()->first) + "," + _clean_name(map.begin()->second) + ">";
    }

    template <typename K, typename V>
    std::string
    _clean_name(std::map<K,V>const & map) {
        return "std::map<" + _clean_name(map.begin()->first) + "," + _clean_name(map.begin()->second) + ">";
    }

    template<typename T>
    void
    _print( T const& input) {
        if(has_left_shift<typeof(std::cout),T>::value){
            std::cout<<input;
        } else {
            std::cout<<_clean_name(input)<<" instance at "<<&input<<">";
        }
    }

    template<>
    void
    _print<char>(char const& input) {
        std::cout<<"\'"<<input<<"\'";
    }

    template<>
    void
    _print<bool>(bool const& input) {
        std::cout<<(input?"true" : "false");
    }

    template<>
    void
    _print<std::string>(std::string const& input) {
        std::cout<<"\""<<input<<"\"";
    }

    template<>
    void
    _print<const char* & >(const char* &input) {
        std::cout<<"\""<<input<<"\"";
    }

    template<typename T>
    void
    print(T const& input) {
        std::cout<<"\t";
        _print(input);
        std::cout<<"\n";
    }

    template<typename T1, typename T2>
    void
    print(std::pair<T1,T2> const& pair) {
        std::cout<<"\t{";
        _print(pair.first);
        std::cout<<",";
        _print(pair.second);
        std::cout<<"}\n";
    }

    template<typename T>
    void
    print(std::vector<T> const& vec) {
        const auto vec_size = vec.size();

        for(auto ii = 0; ii<vec_size; ++ii) {
            if(ii < 5 || (vec_size - ii) < 5) {
                print(vec[ii]);
            } else if (ii == 5) {
                print("\t...\t");
            }
        }
    }

    template<typename K, typename V>
    void
    print(std::map<K,V> const& map) {
        std::cout<<_clean_name(map) <<"{";
        const auto last_comma = map.size() - 1;
        auto ii(0);
        for(const auto& pr : map) {
            std::cout<<"{";
            _print(pr.first);
            std::cout<<",";
            _print(pr.second);
            std::cout<<"}";
            if(++ii < last_comma)  {
                std::cout<<",";
            }
        }
        std::cout<<"}\n";
    }

    template<typename K, typename V>
    void
    print(std::unordered_map<K,V> const& map) {
        std::cout<<_clean_name(map)<<"{";
        const auto last_comma = map.size() - 1;
        auto ii(0);
        for(const auto& pr : map) {
            std::cout<<"{";
            _print(pr.first);
            std::cout<<",";
            _print(pr.second);
            std::cout<<"}";
            if(++ii < last_comma)  {
                std::cout<<",";
            }
        }
        std::cout<<"}\n";
    }


} // namespace pretty
#endif //PRETTY_PRING_PRETTY_PRINT_H