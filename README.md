# Newave
New c-like preprocessor based on Boost Wave with additional interface

# Planed dircetives

In all new directives may use macroses.

 - **\#alias** *new_directive_name* *directive1* *directive1_arguments* ; *directive2* *directive2_arguments* ; ...  
   , where:  
     - *new_directive_name* - new directive neme without spaces \[A-z]\[A-z0-9]\*  
     - *directive* - old directive name  without spaces \[A-z]\[A-z0-9]\*  
     - *directive_arguments* - commands line with spaces and any symbols sended to old directive  
   Arguments of new directive is appended to *directive_arguments*, but herewith you may use arguments replace %s, %s%, ## with next syntax:  
     - %s - replace to all remaining new arguments
     - %s% - replace to one word from new arguments
     - %s##word, word##%s% .. etc - use ## symbols from without space inserting
     - \%s, \;, \%s% or \##- to ignore replace

   This directive declare new directive and replaces with empty string if success.

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
