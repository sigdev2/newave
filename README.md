# Newave

New c-like preprocessor based on Boost Wave with additional interface. May used for any languages. Promising for web development.  

# Parameters

 - **-a** - alias declare in global space
 - **-s** - system declare in global space
 - **-i** - insert directive may use in global space
 - **-x** - enable *system* directives runing, if flag not specifed, then system declarations and aliases using ignored and replaced with empty string  

# Dircetives

 - **\#pragma aliasns** *alias* *alias_arguments*  
   , where:  
     - *alias* - using alias name *\[A-z_\]\[A-z0-9_\]\**
     - *alias_arguments* - *optionaly* arguments with spaces and any symbols sended to old directive  
    
    Namespace for using aliases registred from *\#pragma alias* or *\#pragma system* when global flag is not specifed. When called with alias name will be replaced with directive output. When global flag is specifed namespace partical or fully becomes available in global directive space, but store all rules of this namespace described below.  
    
    When register indenticeal named aliases will replace each other. Can't use starndard directives names, *insert*, *system*, *alias* names and aliases registred by *system* directive can't be rewrited, and an any attempt will cause an error. Aliases can't be undefined.  
    
    Aliases can register only in first included *"aliases.h"* file, but declared aliases may used in any files after this include. Other *"aliases.h"* may be included in root *"aliases.h"*.  
 
 - **\#pragma alias** *new_directive_name* *directive1* *directive1_arguments*; ... ; *directiveN* *directiveN_arguments*  
   , where:  
     - *new_directive_name* - new directive neme without spaces *\[A-z_\]\[A-z0-9_\]\**
     - *directive* - old directive name  without spaces *\[A-z_\]\[A-z0-9_\]\**
     - *directive_arguments* - *optionaly* arguments with spaces and any symbols sended to old directive  

    This directive declare new directive. If declare is success replaces with empty string.  
    
    Сannot be use *\#pragma system* in declaration, it will cause an error.  

    Arguments of new directive is appended to *directive_arguments*, but herewith you may use arguments replace *\%s*, *\%s\%*, *\#\#* with next syntax:  
     - *\%s* - replace to all remaining new arguments
     - *\%s\%* - replace to one word from new arguments
     - *\%s\#\#word*, *word\#\#\%s\%* ... etc - use *\#\#* symbols from without space inserting
     - *\%s*, *\;*, *\%s\%* or *\#\#*- to ignore replace  

    Only in alias declaration you may use build-in macroses (non-overwritable):  
     - **\_\_DIR\_\_** - full file path
     - **\_\_FILENAME\_\_** - full file name
     - **\_\_BASENAME\_\_** - file base name
     - **\_\_FILEPATH\_\_** - *\_\_DIR\_\_* with full file name, *\_\_FILE\_\_* eqal
     - **\_\_INSERT_COUNT_NUMBER\_\_** - if file insert with directive *\#pragma insert* with specifed amount, then this macro is eqal current number starts with 1 of copy inserted file, else it eqal 1
     - **\_\_IS_MODIFED_PREPROCESSOR\_\_** - always 1 for this preprocessor  

    Only in alias declaration you may use build-in functions:  
     - **$use_context(** *file* **)** - switch context of macros *\_\_DIR\_\_*, *\_\_FILENAME\_\_*, *\_\_BASENAME\_\_*, *\_\_FILEPATH\_\_* to specified *file* path in standard include syntax (absolute or relative double quoted or *<>* for search in standard directories), can use only as first directive in alias and change all alias
     - **$to_macros_name(** *str* **)** - convert str to correct macros name in upper case with replace not *\[A-z0-9_\]* symbols to *_* and add forward and ended *__*
     - **$macros_by_macros(** *macros* **)** - get name of *macros* by other macros value with use *$to_macros_name(str)*  

    Functions use without spaces between *$* and *(*, function argument read before the first occurrence *)* and use with trimed spaces. Language constructions aka string quotes, comments or brackets is ignored.  
    
    All macroses and functions will be call only when alias is used.  

    Use if no flag global:  
    
        #pragma aliasns <alias>

 - **\#pragma system** *command* *command_arguments*  
   , where:  
     - *command* - command, programm or script name used for *<alias_name>* without extension and replace all not *\[A-z0-9_\]* symbols to *_*
     - *command_arguments* - *optionaly* any other arguments  

    This directive register next aliases for command:  
     - *<alias_name>* - use as liner directive, replaced to *STDOUT* of command
     - *begin<alias_name>* - start block directive for collect future *STDIN*
     - *end<alias_name>* - end block directive, run command, put to *STDIN* this block and replace block to *STDOUT* of command  
    
    Arguments of new directive is appended to *command_arguments*. if end with not *=* then prepand lead whitespace.  
    
    if register is success replaces with empty string.  

    Use if no flag global:  

        #pragma aliasns <alias_name>
        #pragma aliasns begin<alias_name>
            CODE_TO_STDIN
        #pragma aliasns end<alias_name>
    
 - **\#pragma insert** *mask_or_path1* *amount1*, ... , *mask_or_pathN* *amountN*  
   , where:  
     - *mask_or_path* - absolute file path or relative current file path, may use *glob* files mask, any quotes (*'*, *"*, *"""*, *'''*) and search in standard directories with *<>*
     - *amount* - *optionaly* *\[0-9\]\** count of inserts for file or files.  
    
    Replaced to file's content insert ordered by finded order. If specified amount, then repeat repeat all block of files (not every) the specified number of times.  

    Use if no flag global:  

        #pragma insert <file>, <or_mask> 10, <file> 1

# Benefits of using

 - simplimentate directives syntax
 - full graph paradigm, we may merge and split files
 - containering many files in one easy to edit packed file
 - easy and visual using external tools from code processing
 - high level of codegeneration
 - use as build system or project file
 - collect statistic of build files, e-mailing when preprocessing  

# Using and examples

Standard directives, which cannot be rewritten:  
 - include
 - if
 - elif
 - else if
 - else
 - endif
 - undef
 - define
 - pragma  

Standard *"aliases.h"*:  

    // include guard
    #pragma alias guard ifndef $macros_by_macros(__FILENAME__); define $macros_by_macros(__FILENAME__)
    #pragma alias endguard endif
    
    // include once
    #pragma alias include_once $use_context(%s); pragma aliasns guard; include %s; pragma aliasns endguard
    
    // aliases
    #pragma alias require_once include_once
    #pragma alias req_once include_once
    #pragma alias import_once include_once
    #pragma alias inc_once include_once
    
    #pragma alias depend include
    #pragma alias depends pragma insert

    #pragma alias inc include
    #pragma alias import include
    #pragma alias require include

    #pragma alias fi endif

    #pragma alias remove undef
    #pragma alias delete undef
    #pragma alias del undef
    
    #pragma alias macro define
    #pragma alias macros define
    #pragma alias def define

    #pragma alias directive pragma alias
    #pragma alias direct pragma alias
    #pragma alias declaration pragma alias
    #pragma alias declare pragma alias
    #pragma alias decl pragma alias

Examples of *system* directive using:

    #pragma system cat
    #pragma system sed --expression=

More examples of *system* directive using:

    // python styled code
    #pragma system py2cpp.exe
    #pragma alias pystyle beginpy2cpp
    #pragma alias endpy endpy2cpp
    #pragma alias pyinclude py2cpp

Example use in code:

    #include_once "file.h"

    #guard

        int main(int argc, char *argv[])
        {
    #       pystyle
    #           beginsed "s/Goodbye/Hello/g"
                 if argc == 1:
                     print(u'Goodbye world')
    #           endsed
    #       endpy
    #       pyinclude "your_python_styled_code.py"
             
             return 0;
        }
    
    #endguard

# Что бы разработка не превратилась в ад ...

Что бы разработка не превратилась в ад нужно соблюдать следующие правила:
 - Знак начала директивы *\#* размещать в начале строки.
 - Директиву желательно умещать в одну строку.
 - Помнить, что алиасы не могут быть удалены, поэтому не засорять лишний раз пространство имён.
 - По-максимуму придерживаться стандарта препроцессора C99. Прибегать к нестандартным директивам только в случае крайней необходимости, если польза и уменьшение размера кода действительно будут значимыми.
 - Применять переименование стандартных директив только в случае если они меняют смысловую составляющую. Приемлемые сокращения стандартых директив приведены в стандартном *"aliases.h"*, другие не желательны.
 - Думать о том, что люди будут читать обработанный препроцессором код, а следовательно, на выходе должен получаться читабельный и отлаживаемый код. Никакой обфусцированной кодогенерации.
 - Ни в коем случае не использовать данный препроцессор для оформления кода, это приведёт только к накладным расходам во время компиляции и некрасивому коду на выходе.
 - Имена алиасов должны быть короткие и ясные, чётко отображать своё содержание. Если такое имя сложно подобрать или есть сомнения, то лучше не создавать такой алиас, а оставить всё как есть.
 - Имена алиасов директив окончания блока должны начинаться со слова end (исключение if ... fi)
 - Основное назначение директивы *\#pragma system* - это генерация и преобразование кода. Директива не предназначена для изменения состояния OS, IDE или внешних файлов, такое поведение лучше полностью исключить.
 - Так как директива *\#pragma system* предоставляет огромные возможности как разработчикам, так и злоумышленникам, которые могут распространять зловредный исходный код, следует чётко контролировать использование этой директивы. Использовать только в своём конечном продукте, не использовать в своих библиотеках, при импорте чужого кода искать директиву *\#pragma system* и при нахождении либо удалять, либо выносить в свои контролируемые файлы, либо не использовать этот код вовсе.
 - По тойже причине в директиве *\#pragma system* следует использовать только проверенные программы.
 - Желательно в репозитории своего проекта держать директорию tools в корне проекта с вашим проверенным набором инструментов для директивы *\#pragma system*, это обезопасит вас от подмены программ, а другим разработчикам будет передан цельный нефрагментированный pipeline. В то же время из-за угрозы вредоносных программ, в репозитории сторонних проектов папку tools перед использованием придётся тщательно проверять или вообще не использовать.
