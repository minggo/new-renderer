## ===== static function implementation template - for overloaded functions

static bool ${signature_name}(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    #for func in $implementations
    #if len($func.arguments) >= $func.min_args
    #set arg_count = len($func.arguments)
    #set arg_idx = $func.min_args
    #while $arg_idx <= $arg_count
    do {
        if (argc == ${arg_idx}) {
            #set arg_list = ""
            #set arg_array = []
            #set count = 0
            #while $count < $arg_idx
                #set $arg = $func.arguments[$count]
                #if $arg.is_numeric
            ${arg.to_string($generator)} arg${count} = 0;
                #elif $arg.is_pointer
            ${arg.to_string($generator)} arg${count} = nullptr;
                #else
            ${arg.to_string($generator)} arg${count};
                #end if
            ${arg.to_native({"generator": $generator,
                             "in_value": "args[" + str(count) + "]",
                             "out_value": "arg" + str(count),
                             "class_name": $class_name,
                             "level": 3,
                             "is_static": True,
                             "is_persistent": $is_persistent,
                             "ntype": str($arg)})};
            #set $arg_array += ["arg"+str(count)]
            #set $count = $count + 1
            #if $arg_idx > 0
            if (!ok) { ok = true; break; }
            #end if
            #end while
            #set $arg_list = ", ".join($arg_array)
            #if str($func.ret_type) != "void"
                #if $func.ret_type.is_enum
            $ret_type.enum_declare_type result = ($ret_type.enum_declare_type)${namespaced_class_name}::${func.func_name}($arg_list);
                #else
            ${func.ret_type.get_whole_name($generator)} result = ${namespaced_class_name}::${func.func_name}($arg_list);
                #end if
            ${func.ret_type.from_native({"generator": $generator,
                                         "in_value": "result",
                                         "out_value": "s.rval()",
                                         "class_name": $func.ret_type.get_class_name($generator),
                                         "ntype": str($func.ret_type),
                                         "level": 3})};
            SE_PRECONDITION2(ok, false, "${signature_name} : Error processing arguments");
            #else
            ${namespaced_class_name}::${func.func_name}($arg_list);
            #end if
            return true;
        }
        #set $arg_idx = $arg_idx + 1
    } while (false);
    #end while
    #end if
    #end for
    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(${signature_name})
