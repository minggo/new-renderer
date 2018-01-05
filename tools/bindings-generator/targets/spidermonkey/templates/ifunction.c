## ===== instance function implementation template

static bool ${signature_name}(se::State& s)
{
    ${namespaced_class_name}* cobj = (${namespaced_class_name}*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "${signature_name} : Invalid Native Object");
#if len($arguments) >= $min_args
    const auto& args = s.args();
    size_t argc = args.size();
    #set arg_count = len($arguments)
    #set arg_idx = $min_args
    #if $arg_count > 0 or $ret_type.name != "void"
    CC_UNUSED bool ok = true;
    #end if
    #while $arg_idx <= $arg_count
    if (argc == ${arg_idx}) {
        #set $count = 0
        #while $count < $arg_idx
            #set $arg = $arguments[$count]
            #if $arg.is_numeric
        ${arg.to_string($generator)} arg${count} = 0;
            #elif $arg.is_pointer
        ${arg.to_string($generator)} arg${count} = nullptr;
            #else
        ${arg.to_string($generator)} arg${count};
            #end if
            #set $count = $count + 1
        #end while
        #set $count = 0
        #set arg_list = ""
        #set arg_array = []
        #while $count < $arg_idx
            #set $arg = $arguments[$count]
        ${arg.to_native({"generator": $generator,
                             "in_value": "args[" + str(count) + "]",
                             "out_value": "arg" + str(count),
                             "class_name": $class_name,
                             "level": 2,
                             "is_static": False,
                             "is_persistent": $is_persistent,
                             "ntype": str($arg)})};
            #set $arg_array += ["arg"+str(count)]
            #set $count = $count + 1
        #end while
        #if $arg_idx > 0
        SE_PRECONDITION2(ok, false, "${signature_name} : Error processing arguments");
        #end if
        #set $arg_list = ", ".join($arg_array)
        #if $ret_type.name != "void"
            #if $ret_type.is_enum
        $ret_type.enum_declare_type result = ($ret_type.enum_declare_type)cobj->${func_name}($arg_list);
            #else
        ${ret_type.get_whole_name($generator)} result = cobj->${func_name}($arg_list);
            #end if
        ${ret_type.from_native({"generator": $generator,
                                    "in_value": "result",
                                    "out_value": "s.rval()",
                                    "class_name": $ret_type.get_class_name($generator),
                                    "ntype": str($ret_type),
                                    "level": 2})};
        SE_PRECONDITION2(ok, false, "${signature_name} : Error processing arguments");
        #else
        cobj->${func_name}($arg_list);
        #end if
        return true;
    }
        #set $arg_idx = $arg_idx + 1
    #end while
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, $arg_count);
#end if
    return false;
}
SE_BIND_FUNC(${signature_name})
