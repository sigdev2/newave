# Newave

New c-like preprocessor based on Boost Wave with additional interface

# Parameters

 - alias in global space
 - system in global space
 - enable system  

# Dircetives

 - **\#pragma alias** *new_directive_name* *directive1* *directive1_arguments*; ... ; *directiveN* *directiveN_arguments*  
   , where:  
     - *new_directive_name* - new directive neme without spaces *\[A-z\]\[A-z0-9\]\**
     - *directive* - old directive name  without spaces *\[A-z\]\[A-z0-9\]\**
     - *directive_arguments* - commands line with spaces and any symbols sended to old directive  

    This directive declare new directive and replaces with empty string if success. Alisases with identical names replace each other. Can't undefine alias. 

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
     - **\_\_IS_MODIFED_PREPROCESSOR\_\_** - always true for this preprocessor  

    Only in alias declaration you may use build-in functions:  
     - **$use_context(** *file* **)** - switch context of macros *\_\_DIR\_\_*, *\_\_FILENAME\_\_*, *\_\_BASENAME\_\_*, *\_\_FILEPATH\_\_* to specified *file*, may use only as first directive in alias and change all alias
     - **$to_macros_name(** *str* **)** - convert str to correct macros name in upper case with replace not *\[A-z0-9_\]* symbols to *_* and add forward and ended *__*
     - **$macros_by_macros(** *macros* **)** - get name of *macros* by other macros value with use *$to_macros_name(str)*  

    Functions use without spaces between *$* and *(*, function argument read before the first occurrence *)* and use with trimed spaces. Language constructions aka string quotes, comments or brackets is ignored.  
    
    All macroses and functions will be call only when alias is used.  

    Use if no flag global:  
    
        #pragma aliasns <alias>

 - **\#pragma system** *command* *command_arguments*  
   , where:  
     - *command* - command, programm or script name used for alias
     - *command_arguments* - any other arguments  

    This directive register next aliases for command:  
     - *command* - use command as liner directive, replaced command *STDOUT*
     - start*command* - use start block directive
     - end*command* - use for command as start block directive

    Use if no flag global:  
    **\#pragma systemns** *<command_name>*
    **\#pragma systemin** *<programm_name>*  
        *CODE_TO_STDIN*  
    **\#pragma endsystem**  

# Modifed directive

 - **#include** *mask_or_path* *<once|\[0-9\]\*>*

# Declared aliases of directives

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
    
    // include once
    #alias include_once use_context %s; guard; #include %s; endcontext
    
    // regexp
    #alias regexp define __RANDOM_123 %s; export rx
    #alias endrx endexport; system sed __RANDOM_123 __FILE__.0.rx; system del __FILE__.0.rx; undef __RANDOM_123
    
    // try like something like this
    #alias export_exec export %s%; system %s; endexport

Example use in code:

    #include "file.h" once

    #guard

        int main(int argc, char *argv[])
        {
        #pystyle
        #    regexp s/Goodbye/Hello/g
                 if argc == 1:
                     print(u'Goodbye world')
        #    endrx
        #endpy
        #pyinclude "your_python_styled_code.py"
             return 0;
        }
    
    #endguard

# Что бы разработка не превратилась в ад ...

Что бы разработка не превратилась в ад нужно соблюдать следующие правила:
 - По-максимуму придерживаться стандарта препроцессора C99. Прибегать к нестандартным директивам только в случае крайней необходимости, если польза и уменьшение размера кода действительно будут значимыми.
 - Думать о том, что люди будут читать обработанный препроцессором код, а следовательно, на выходе должен получаться читабельный и отлаживаемый код. Никакой обфусцированной кодогенерации.
 - Ни в коем случае не использовать данный препроцессор для оформления кода, это приведёт только к накладным расходам во время компиляции и некрасивому коду на выходе.
 - Имена алиасов должны быть короткие и ясные, чётко отображать своё содержание. Если такое имя сложно подобрать или есть сомнения, то лучше не создавать такой алиас, а оставить всё как есть.
 - Имена алиасов директив окончания блока должны начинаться со слова end (исключение if ... fi)
 - В коде использовать только директиву **\#alias**, все остальные новые директивы, встроенные макросы и функции использовать только в рамках этой директивы. (Возможно, в дальнейшем я сделаю это программно регулируемым)
 - Имена алиасов для директивы **\#system** должны использовать имя используемой внутри программы. Это приведёт к тому, что если использовать всеми известные утилиты (sed, grep ... и т.д.), то и имена и принцип работы новых директив будут понятны для читающих код, а также, они смогут найти информацию по имени директивы в сети. (Возможно, в дальнейшем я сделаю это программно регулируемым)
 - Основное назначение директивы **\#system** - это генерация и преобразование кода. Директива не предназначена для изменения состояния OS, IDE или внешних файлов, такое поведение лучше полностью исключить.
 - Так как директива **\#system** предоставляет огромные возможности как разработчикам, так и злоумышленникам, которые могут распространять зловредный исходный код, следует чётко контролировать использование этой директивы. Использовать только в своём конечном продукте, не использовать в своих библиотеках, при импорте чужого кода искать директиву **\#system** и все её алиасы и при нахождении либо удалять, либо выносить в свои контролируемые файлы, либо не использовать этот код вовсе.
 - По тойже причине в директиве **\#system** следует использовать только проверенные программы. (Возможно, ряд проверенных утилит придётся встроить или же написать самому)
 - Желательно в репозитории своего проекта держать директорию tools в корне проекта с вашим проверенным набором инструментов, это обезопасит вас от подмены программ, а другим разработчикам будет передан цельный нефрагментированный pipeline. В то же время из-за угрозы вредоносных программ, в репозитории сторонних проектов папку tools перед использованием придётся тщательно проверять или вообще не использовать. (Возможно, в дальнейшем я сделаю это программно регулируемым)
 - Не использовать вложенные объявления **\#system**, всегда объявлять алиасы **\#system** отдельно. Это поможет разгрузить объявления сложных алиасов. (Возможно, в дальнейшем я сделаю это программно регулируемым)
 - В своём коде держать все алиасы в одном файле aliases.h в корне проекта, для того, чтобы их было удобно контролировать и другие разработчики легко могли его найти и прочитать. (Возможно, в дальнейшем я сделаю это программно регулируемым)
 - Есть два пути спользования **\#system**, первый - с использованием директивы **\#export** для обработки блока кода, а второй - с использованием **\#include** для обработки и включения кода из внешнего файла. Плюс первого способа в том, что весь код собран в одном месте и его можно использовать в разных местах маленькими блоками, а минус - в накладных расходах с использованием файловой системы (хотя кэширование FS успешно решает данные проблемы). Минус второго способа в том, что невозможно использовать маленькие блоки и получается слишком много файлов, но в то же время, возможно сначала писать библиотеки кода, которые затем подвергаются включению и обработке директивой **\#system** в одном месте, например в main.cpp или специально созданном для этого файле preprocessed.h. Данный подход более безопасен в плане распространения кода и является наиболее предпочтительным в использовании. (Возможно, в дальнейшем я сделаю это программно регулируемым, но вряд ли)
 - Имена стандартных директив возможно сократить по средствам алиасов, но лучше этого не делать. Лучше по-максимуму использовать стандартные имена директив, чтобы сохранить обратную совместимость со старыми препроцессорами и узнаваемость кода другими разработчиками. Хотя, использование сокращений допускается для того, что бы печатать меньше символов и следовательно, сократить время разработки. Возможно, в будущем данные сокращения войдут в стандарты программирования, но на данный момент такие эксперименты лучше изолировать либо в отдельных модулях, либо использовать там, где вы уверены, что данный код не будет переиспользован, например, в корневых проектах.
