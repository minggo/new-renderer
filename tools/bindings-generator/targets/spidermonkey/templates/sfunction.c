## ===== static function implementation template

static bool ${signature_name}(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
#if len($arguments) >= $min_args
    #set arg_count = len($arguments)
    #set arg_idx = $min_args
    #if ($arg_count > 0 or str($ret_type) != "void")
    CC_UNUSED bool ok = true;
    #end if
    #while $arg_idx <= $arg_count
    if (argc == ${arg_idx}) {
        #set arg_list = ""
        #set arg_array = []
        #set $count = 0
        #while $count < $arg_idx
            #set $arg = $arguments[$count]
            #set $arg_type = $arg.to_string($generator)
            #if $arg.is_numeric
        $arg_type arg${count} = 0;
            #elif $arg.is_pointer
        $arg_type arg${count} = nullptr;
            #else
        $arg_type arg${count};
            #end if
            #set $count = $count + 1
        #end while
        #set $count = 0
        #while $count < $arg_idx
            #set $arg = $arguments[$count]
            #set $arg_type = $arg.to_string($generator)
        ${arg.to_native({"generator": $generator,
            "arg_type": $arg_type,
            "in_value": "args[" + str(count) + "]",
            "out_value": "arg" + str(count),
            "class_name": $class_name,
            "level": 2,
            "is_static": True,
            "is_persistent": $is_persistent,
            "ntype": str($arg)})};
            #set $arg_array += ["arg"+str($count)]
            #set $count = $count + 1
        #end while
        #if $arg_idx > 0
        SE_PRECONDITION2(ok, false, "${signature_name} : Error processing arguments");
        #end if
        #set $arg_list = ", ".join($arg_array)
    #if str($ret_type) != "void"
        #if $func_name.startswith("create") and $is_ref_class
        auto result = ${namespaced_class_name}::${func_name}($arg_list);
        result->retain();
        auto obj = se::Object::createObjectWithClass(__jsb_${underlined_class_name}_class);
        obj->setPrivateData(result);
        s.rval().setObject(obj);
        #elif $func_name.startswith("getInstance") and $is_ref_class
        auto result = ${namespaced_class_name}::${func_name}($arg_list);
        se::Value instanceVal;
        native_ptr_to_seval<${namespaced_class_name}>(result, __jsb_${underlined_class_name}_class, &instanceVal);
        instanceVal.toObject()->root();
        s.rval() = instanceVal;
        #else
          #if $ret_type.is_enum
        $ret_type.enum_declare_type result = ($ret_type.enum_declare_type)${namespaced_class_name}::${func_name}($arg_list);
          #else
        ${ret_type.get_whole_name($generator)} result = ${namespaced_class_name}::${func_name}($arg_list);
          #end if
        ${ret_type.from_native({"generator": $generator,
                                "in_value": "result",
                                "out_value": "s.rval()",
                                "class_name": $ret_type.get_class_name($generator),
                                "ntype": str($ret_type),
                                "level": 1})};
        SE_PRECONDITION2(ok, false, "${signature_name} : Error processing arguments");
        #end if
    #else
        ${namespaced_class_name}::${func_name}($arg_list);
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
