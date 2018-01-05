## ===== member implementation template

static bool ${signature_name}_get_${name}(se::State& s)
{
    ${namespaced_class_name}* cobj = (${namespaced_class_name}*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "${signature_name}_get_${name} : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    #if $ntype.is_object and not $ntype.object_can_convert($generator, False)
    ${ntype.from_native({"generator": $generator,
                         "type_name": $ntype.namespaced_class_name.replace("*", ""),
                         "ntype": $ntype.get_whole_name($generator),
                         "level": 2,
                         "in_value": "cobj->" + $pretty_name,
                         "out_value": "jsret"
                        })};
    #else
    ${ntype.from_native({"generator": $generator,
                         "type_name": $ntype.namespaced_class_name.replace("*", ""),
                         "ntype": $ntype.get_whole_name($generator),
                         "level": 2,
                         "scriptname": $generator.scriptname_from_native($ntype.namespaced_class_name, $ntype.namespace_name),
                         "in_value":"cobj->" + $pretty_name,
                         "out_value": "jsret"
                         })};
    #end if
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(${signature_name}_get_${name})

static bool ${signature_name}_set_${name}(se::State& s)
{
    const auto& args = s.args();
    ${namespaced_class_name}* cobj = (${namespaced_class_name}*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "${signature_name}_set_${name} : Invalid Native Object");

    CC_UNUSED bool ok = true;
#if $ntype.is_numeric
    ${ntype.to_string($generator)} arg0 = 0;
#elif $ntype.is_pointer
    ${ntype.to_string($generator)} arg0 = nullptr;
#else
    ${ntype.to_string($generator)} arg0;
#end if
#if $ntype.is_object and not $ntype.object_can_convert($generator)
    ${ntype.to_native({"generator": $generator,
                        "arg_idx": 2,
                        "ntype": $ntype.get_whole_name($generator),
                        "in_value": "args[0]",
                        "out_value": "arg0",
                        "func_name": $name,
                        "level": 2,
                        "arg":$ntype,
                    })};
#else
    ${ntype.to_native({"generator": $generator,
                        "arg_idx": 2,
                        "in_value": "args[0]",
                        "out_value": "arg0",
                        "func_name": $name,
                        "scriptname": $generator.scriptname_from_native($ntype.namespaced_class_name, $ntype.namespace_name),
                        "level": 2,
                        "arg":$ntype,
                    })};
#end if
    SE_PRECONDITION2(ok, false, "${signature_name}_set_${name} : Error processing new value");
    cobj->$pretty_name = arg0;
    return true;
}
SE_BIND_PROP_SET(${signature_name}_set_${name})
