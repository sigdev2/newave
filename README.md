# Newave
New c-like preprocessor based on Boost Wave with additional interface

# Planed arguments settings

 - **-v** - version
 - **-c** - config, included json with all newt arguments

# Planed dircetives

 - **\#alias** *new_directive_name* *directive* *directive_arguments*  
   , where:  
     - *new_directive_name* - new directive neme without spaces \[A-z]\[A-z0-9]\*  
     - *directive* - old directive name  without spaces \[A-z]\[A-z0-9]\*  
     - *directive_arguments* - commands line with spaces and any symbols sended to old directive  
   Arguments of new directive is appended to *directive_arguments*, but herewith you may use arguments replace %s, %s%, ## with next syntax:  
     - %s - replace to all remaining new arguments
     - %s% - replace to one word from new arguments
     - %s##word, word##%s% .. etc - use ## symbols from without space inserting
     - \%s or \%s% or \##- to ignore replace
