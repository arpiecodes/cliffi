#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library_path_resolver.h"
#include "argparser.h"
#include "invoke_handler.h"
#include "return_formatter.h"
#include "types_and_utils.h"



int main(int argc, char* argv[]) {
    if (strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s <library> <return_type> <function_name> [<args>...]\n", argv[0]);
        printf("  [--help]         Print this help message\n");
        printf("  <library>        The path to the shared library containing the function to invoke\n"
               "                   or the name of the library if it is in the system path\n");
        printf("  <return_type>    The type of the return value of the function to invoke\n"
               "                   v for void, i for int, s for string, etc\n");
        printf("  <function_name>  The name of the function to invoke\n");
        printf("  [typeflag] <arg> The argument values to pass to the function\n"
               "                   Types will be inferred if not prefixed with flags\n"
               "                   Flags look like -i for int, -s for string, etc\n");
        printf("\n"
               "  Examples:\n"
               "         %s libexample.so i addints 3 4\n", argv[0]);
        printf("         %s path/to/libexample.so v dofoo\n", argv[0]);
        printf("         %s ./libexample.so s concatstrings -s hello -s world\n", argv[0]);
        printf("         %s libexample.so s concatstrings hello world\n", argv[0]);
        printf("         %s libexample.so d multdoubles -d 1.5 1.5d\n", argv[0]);
        printf("         %s libc.so i printf 'Here is a number: %%.3f' 4.5", argv[0]);
        return 0;
    }
    else if (argc < 4) {
        fprintf(stderr, "Usage: %s [--help] <library> <return_type> <function_name> [[-typeflag] <arg>...]\n", argv[0]);
        return 1;
    }


    //print all args
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    // Step 1: Resolve the library path
    // For now we've delegated that call to parse_arguments


    // Step 2: Parse command-line arguments
    FunctionCallInfo* call_info = parse_arguments(argc, argv);
    convert_all_arrays_to_arginfo_ptr_sized_after_parsing(call_info);
    

    // Step 2.5 (optional): Print the parsed function call call_info
    printf("Parsed function call call_info:\n");
    log_function_call_info(call_info);

    // Step 3: Invoke the specified function
    int invoke_result = invoke_dynamic_function(call_info);
    if (invoke_result != 0) {
        fprintf(stderr, "Error: Function invocation failed\n");
    }

    // Step 4: Print the return value and any modified arguments



    convert_all_arrays_to_static_sized_after_function_return(call_info);

    printf("Function returned: ");

    format_and_print_arg_value(&call_info->return_var);

    for (int i = 0; i < call_info->arg_count; i++) {
        // if it could have been modified, print it
        if (call_info->args[i].is_array || call_info->args[i].pointer_depth > 0) {
            printf("Arg %d after function return: ", i);
            format_and_print_arg_value(&call_info->args[i]);
            printf("\n");
        }
    }

    // Clean up
    freeFunctionCallInfo(call_info); 

    return invoke_result;
}
