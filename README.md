# Newave
New c-like preprocessor based on Boost Wave with additional interface

# Planed predefined macros

 - **\_\_FILENAME\_\_** - full file name
 - **\_\_BASENAME\_\_** - file base name

# Planed dircetives

 - **\#alias** *new_directive_name* *directive1* *directive1_arguments* ; *directive2* *directive2_arguments* ; ...  
   , where:  
     - *new_directive_name* - new directive neme without spaces \[A-z\]\[A-z0-9\]\*  
     - *directive* - old directive name  without spaces \[A-z\]\[A-z0-9\]\*  
     - *directive_arguments* - commands line with spaces and any symbols sended to old directive  
   Arguments of new directive is appended to *directive_arguments*, but herewith you may use arguments replace %s, %s%, ## with next syntax:  
     - %s - replace to all remaining new arguments
     - %s% - replace to one word from new arguments
     - %s##word, word##%s% .. etc - use ## symbols from without space inserting
     - \%s, \;, \%s% or \##- to ignore replace

   This directive declare new directive and replaces with empty string if success. Alisases with identical names replace each other. Can't undefine alias.

 - **\#system** *command_line*  
   , where:  
     - *command_line* - any command line command

   This directive call any command line command and replaces his STDOUT.
   
 - **\#export** *postfix*  
       *CODE*  
   **\#endexport**  
   , where:  
     - *postfix* - postfix to file name, may be empty
     
   Save *CODE* to file with name \_\_FILE\_\_.<counter + 1>[.*postfix*] and replaces with empty string if success.
   
# Planing modifed directive

 - **#include** *mask_or_path* *<once|\[0-9\]\*>*

# Planing declared aliases of directives

 - require_once = import_once = inc_once = include_once = include %s once
 - require = import = inc = include
 - if
 - elif = else if
 - else
 - endif = fi
 - del = delete = undef = remove
 - def = define = macro = macros
 - alias = directive = direct = declare = declaration = decl
 - system = sys = shell = exec = execute

# Planed build-in functions

In all new directives may use macroses. But same times need get name of macros by other macros value. In this new directives use function \_\_GET\_MACROS\_BY\_MACROS\_\_(*macro_name*). To convert macros value to safe macro name use function \_\_TO\_MACRO\_NAME\_\_(*macro_name*), but \_\_GET\_MACROS\_BY\_MACROS\_\_ make it automatical.

All function insert only when directive is called, and use macroses of current call-space.

# Benefits of using

 - simplimentate directives syntax
 - full graph paradigm, we may merge and split files
 - containering many files in one easy to edit packed file
 - easy and visual using external tools from code processing
 - high level of codegeneration
 - use as build system or project file

Example declare aliases:

    // python styled code
    #alias pystyle export py
    #alias endpy endexport; system py2cpp.exe __FILE__.0.py; system del __FILE__.0.py
    
    // include python styled code
    #alias pyinclude system py2cpp.exe
    
    // include guard
    #alias guard ifndef __GET_MACROS_BY_MACROS__(__FILENAME__); define __GET_MACROS_BY_MACROS__(__FILENAME__)
    #alias endguard endif
    
    //

Example use in code:

    #include "file.h" once

    #guard

        int main(int argc, char *argv[])
        {
        #pystyle
            if argc == 1:
                print(u'Hello world')
        #endpy
        #pyinclude "your_python_styled_code.py"
             return 0;
        }
    
    #endguard
