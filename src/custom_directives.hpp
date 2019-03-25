
#if !defined(BOOST_WAVE_CUSTOM_DIRECTIVES_HOOKS_INCLUDED)
#define BOOST_WAVE_CUSTOM_DIRECTIVES_HOOKS_INCLUDED

#include <cstdio>
#include <ostream>
#include <string>
#include <algorithm>
#include <unordered_map>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/wave/token_ids.hpp>
#include <boost/wave/util/macro_helpers.hpp>
#include <boost/wave/preprocessing_hooks.hpp>

template <typename ContainerT, typename TString>
class custom_directives_hooks
:   public boost::wave::context_policies::default_preprocessing_hooks
{
public:
    template <typename ContextT, typename ContainerT>
    bool
    found_unknown_directive(ContextT const& ctx, ContainerT const& line, 
        ContainerT& pending)
    {
        namespace wave = boost::wave;

        typedef typename ContainerT::const_iterator iterator_type;
        iterator_type it = line.begin();
        wave::token_id id = wave::util::impl::skip_whitespace(it, line.end());

        if (id != wave::T_IDENTIFIER)
            return false; // nothing we could do

        if (it->get_value() == "declare")
        {
            bool skip = true;
            ContainerT newCtx;
            for (auto jt = line.begin(); jt != line.end(); ++jt)
            {
                if (skip)
                {
                    skip = false;
                    continue;
                }

                newCtx.push_back(*jt);
            }
            
            ++it;
            declared[std::string(it->get_value())] = newCtx;
            return true;
        }

        return false; // unknown directive
    }

    typedef std::tuple<int, char, char> key_t;

    struct key_hash : public std::unary_function<key_t, std::size_t>
    {
        std::size_t operator()(const key_t& k) const
        {
            return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k);
        }
    };

    typedef std::unordered_map<const key_t, data, key_hash, key_equal> map_t;

    std::unordered_map<TString, ContainerT> declared;
};


#endif // BOOST_WAVE_ADVANCED_PREPROCESSING_HOOKS_INCLUDED
