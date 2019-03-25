
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class

#include "custom_directives.hpp"


int main(int argc, char *argv[])
{
    if (2 != argc)
	{
        std::cerr << "Usage: custom_directives infile" << std::endl;
        return -1;
    }

	boost::wave::util::file_position_type current_position;

    try
	{
		std::ifstream instream(argv[1]);
		std::string instring;

        if (!instream.is_open())
		{
            std::cerr << "Could not open input file: " << argv[1] << std::endl;
            return -2;
        }
        instream.unsetf(std::ios::skipws);
        instring = std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
                               std::istreambuf_iterator<char>());

        typedef boost::wave::cpplexer::lex_token<> token_type;
        typedef boost::wave::cpplexer::lex_iterator<token_type> lex_iterator_type;
        typedef std::list<token_type, boost::fast_pool_allocator<token_type> > token_sequence_type;
        typedef boost::wave::context<std::string::iterator,
		                             lex_iterator_type,
                                     boost::wave::iteration_context_policies::load_file_to_string,
                                     custom_directives_hooks<token_sequence_type, token_type::string_type>
									> context_type;

		context_type ctx(instring.begin(), instring.end(), argv[1]);

		ctx.set_language(boost::wave::enable_long_long(ctx.get_language()));
		ctx.set_language(boost::wave::enable_preserve_comments(ctx.get_language()));
		ctx.set_language(boost::wave::enable_prefer_pp_numbers(ctx.get_language()));

		context_type::iterator_type first = ctx.begin();
		context_type::iterator_type last = ctx.end();

        while (first != last)
		{
            current_position = first->get_position();
            std::cout << first->get_value();
            ++first;
        }
    }
    catch (boost::wave::cpp_exception const& e)
	{
        std::cerr 
            << e.file_name() << "(" << e.line_no() << "): "
            << e.description() << std::endl;
        return 2;
    }
    catch (std::exception const& e)
	{
        std::cerr 
            << current_position.get_file() 
            << "(" << current_position.get_line() << "): "
            << "exception caught: " << e.what()
            << std::endl;
        return 3;
    }
    catch (...)
	{
        std::cerr 
            << current_position.get_file() 
            << "(" << current_position.get_line() << "): "
            << "unexpected exception caught." << std::endl;
        return 4;
    }
    return 0;
}
