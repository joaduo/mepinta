/*
 * props_macros.h
 *
 *  Created on: Jul 30, 2012
 *      Author: jduo
 */

#ifndef PROPS_MACROS_H_
#define PROPS_MACROS_H_

#include "config.h"

//{ Properties' variable declaration and value replacement Macros
  //Macros depending on build mode (Release, Debug)
  #ifdef MEPINTA_DEBUG_TYPES
    #define CHECK_ARGS(args)                              \
      if(args == NULL ){                                  \
        log_error("NULL args. Stopping processor.\n");    \
        return EXIT_ERROR_MISSING_ARGS;                   \
      }

    //WARNING On Release mode variable won't be const (for performance reasons)
    #define DECLARE_INPUT_PROP_VALIDATED(data_type, var_name, args, in_out_id, prop_name,VALIDATION_EXPANSION)\
      CHECK_ARGS(args)                                                                             \
      data_type var_name##__temp__;                                                                \
      {                                                                                            \
        if (MP_declare_prop_debug(#data_type, sizeof(data_type),(void**)&var_name##__temp__        \
               , args, in_out_id, #prop_name) == EXIT_FAILURE ) {                                  \
          log_error("Type checking error o non-existence for property value: '"#prop_name"' "      \
                    "with type '"#data_type"'. Stopping processor.\n");                            \
          return EXIT_ERROR_MISSING_PROPERTY;                                                      \
        }                                                                                          \
        /* Hack to maintain constness */                                                           \
        data_type var_name = var_name##__temp__;                                                   \
        VALIDATION_EXPANSION                                                                       \
        var_name##__temp__ = var_name;                                                             \
      }                                                                                            \
      data_type const var_name = var_name##__temp__;

    //WARNING On Release mode variable won't be const (for performance reasons)
    #define DECLARE_INPUT_PROP_REF(data_type, var_name, args, in_out_id, prop_name)                \
      CHECK_ARGS(args)                                                                             \
      data_type* var_name##__temp__;                                                               \
      {                                                                                            \
        if (MP_declare_prop_debug(typeid(data_type*).name(), sizeof(data_type),(void**)&var_name##__temp__        \
               , args, in_out_id, #prop_name) == EXIT_FAILURE ) {                                  \
          log_error("Type checking error o non-existence for property value: '"#prop_name"' "      \
                    "with type '"#data_type"'. Stopping processor.\n");                            \
          return EXIT_ERROR_MISSING_PROPERTY;                                                      \
        }                                                                                          \
      }                                                                                            \
      data_type const &  var_name = *var_name##__temp__;

    //Fix this??
    #define DECLARE_INPUT_PROP_VALUE(data_type, var_name, args, in_out_id, prop_name)              \
      CHECK_ARGS(args)                                                                             \
      data_type var_name##__temp__;                                                                \
      {                                                                                            \
        if (MP_declare_prop_debug(#data_type, sizeof(data_type),(void**)&var_name##__temp__        \
               , args, in_out_id, #prop_name) == EXIT_FAILURE ) {                                  \
          log_error("Type checking error o non-existence for property value: '"#prop_name"' "      \
                    "with type '"#data_type"'. Stopping processor.\n");                            \
          return EXIT_ERROR_MISSING_PROPERTY;                                                      \
        }                                                                                          \
      }                                                                                            \
      data_type const var_name = var_name##__temp__;

    //Declare a Property Value. Useful for getting values from inputs and outputs
    //TODO: distinguish error on type checking and existence
    #define DECLARE_PROP_VALUE(data_type, var_name, args, in_out_id, prop_name)                    \
      data_type var_name;                                                                          \
      CHECK_ARGS(args)                                                                             \
      {                                                                                            \
        if (MP_declare_prop_debug(#data_type, sizeof(data_type),(void**)&var_name                  \
               , args, in_out_id, #prop_name) == EXIT_FAILURE ) {                                  \
          log_error("Type checking error o non-existence for property value: '"#prop_name"' "      \
                    "with type '"#data_type"'. Stopping processor.\n");                            \
          return EXIT_ERROR_MISSING_PROPERTY;                                                      \
        }                                                                                          \
      }

    //Replace an output value passing 'by value'
    #define REPLACE_OUTPUT_VALUE(args,prop_name,new_v) \
      CHECK_ARGS(args)                                 \
      MP_replace_value_debug(args,#prop_name,(void**)&new_v,sizeof(new_v))

    //Replace an output value passing 'by reference'
    #define REPLACE_OUTPUT_REFERENCE(args,prop_name,new_v)  \
      CHECK_ARGS(args)                                      \
      MP_replace_reference_debug(args,#prop_name,(void**)&new_v,sizeof(new_v),NULL)

    //Replace an output value passing 'by reference'
    #define REPLACE_OUT_REF_FAST(args,prop_name,new_v,func_ptr_del)  \
      CHECK_ARGS(args)                                               \
      MP_replace_reference_debug(args,#prop_name,(void**)&new_v,sizeof(new_v),func_ptr_del)

    //Replace an output value passing 'by reference' without freeing previous value (nasty)
    #define NASTY_REPLACE_REFERENCE(args,in_out_id,prop_name,new_v)         \
      CHECK_ARGS(args)                                                      \
      MP_replace_reference_debug(args,in_out_id,#prop_name,(void**)&new_v,sizeof(new_v))

    //Validate a previously declared value.
    //Example (if a pointer): VALIDATE(scalar_number, 0 < scalar_number && scalar_number < 100, 0)
    #define VALIDATE_DEFAULT(var_name, validation_expression, default_v)                                             \
      log_debug_verbose("VALIDATE_DEFAULT("#var_name","#validation_expression","#default_v") "                       \
        "Remember not pass a pointer as default value. In that case use REPLACE_PROP_VALUE macro .\n");              \
      if( !(validation_expression) ){                                                                                \
        log_debug("Property '"#var_name"' couldn't pass check ("#validation_expression"). Setting default value.\n");\
        var_name = default_v;                                                                                        \
      }

    #define MARK_PROP_CHANGED(args,prop_name) \
        CHECK_ARGS(args)                      \
        MP_set_changed_byname_debug(args,OUTPUT_PROPS,#prop_name)

    //Validate a property checking validity of an expression
    #define VALIDATE_DEBUG_RETURN(var_name, validation_expression)                                                      \
      if( !(validation_expression) ){                                                                                   \
          log_warning("Property '"#var_name"' couldn't pass check ("#validation_expression"). Stopping processor.\n");  \
          return EXIT_ERROR_PROPERTY_INVALID;                                                                           \
      }

    #define CAST_PROP(data_type,value) \
        (*(data_type*) MP_check_cast_debug(#data_type,value))

    //TODO: review ugly mangled names (delete this?)
    #define CPP_CAST_PROP(data_type,value) \
        (*(data_type*) MP_check_cast_debug(typeid(data_type).name(),value))

  #else
    //TODO: review this def again!
    #define CHECK_ARGS
    //Declare a Property Value. Useful for getting values from inputs and outputs
    #define DECLARE_PROP_VALUE(data_type, var_name, args, in_out_id, prop_name)                    \
      data_type var_name;                                                                          \
      MP_declare_prop_release(sizeof(data_type), (void**)&var_name, args, in_out_id, #prop_name)
    //Replace an output value passing 'by value'
    #define REPLACE_OUTPUT_VALUE(args,prop_name,new_v) \
      MP_replace_value_release(args,#prop_name,(void**)&new_v,sizeof(new_v))
    //Replace an output value passing 'by reference'
    #define REPLACE_OUTPUT_REFERENCE(args,prop_name,new_v)  \
      MP_replace_reference_release(args,#prop_name,(void**)&new_v,sizeof(new_v),NULL)
    //Replace an output value passing 'by reference'
    #define REPLACE_OUT_REF_FAST(args,prop_name,new_v,func_ptr_del)  \
      MP_replace_reference_release(args,#prop_name,(void**)&new_v,sizeof(new_v),func_ptr_del)
    //Replace an output value passing 'by reference' without freeing previous value (nasty)
    #define NASTY_REPLACE_REFERENCE(args,in_out_id,prop_name,new_v)         \
      MP_replace_reference_release(args,in_out_id,#prop_name,(void**)&new_v,sizeof(new_v))
    //Validate a previously declared value.
    //Example (if a pointer): VALIDATE(scalar_number, 0 < scalar_number && scalar_number < 100, 0)
    #define VALIDATE_DEFAULT(var_name, validation_expression, default_v)                                             \
      if( !(validation_expression) ){                                                                                \
        log_debug("Property '"#var_name"' couldn't pass check ("#validation_expression"). Setting default value.\n");\
        var_name = default_v;                                                                                        \
      }
    #define MARK_PROP_CHANGED(args,prop_name) \
            MP_set_changed_byname_release(args,OUTPUT_PROPS,#prop_name)
    #define VALIDATE_DEBUG_RETURN(var_name, validation_expression)
    #define CAST_PROP(data_type,value) (*(data_type*)value)

    #define CPP_CAST_PROP(data_type,value) (*(data_type*)value)

  #endif


  //Reset the hint index for searching a property. Useful when entering in a new  processor. //TODO:remove
  #define RESET_PROPS_HINT_INDEX(args) \
      MP_set_hint_index(args,0)

  //Validate a property checking the validity of an expression
  #define VALIDATE_RETURN(var_name, validation_expression)                                                                \
    if( !(validation_expression) ){                                                                                       \
        log_warning("Property '"#var_name"' couldn't pass check ("#validation_expression"). Stopping processor.\n");      \
        return EXIT_ERROR_PROPERTY_INVALID;                                                                                                \
    }

  //When getting a property we can check its boundaries or a special condition, if it fails we return null
  #define DECLARE_VALIDATED_RETURN(data_type, var_name, args, in_out_id, prop_name, validation_expression)            \
          DECLARE_PROP_VALUE(data_type, var_name, args, in_out_id, prop_name)                                         \
          VALIDATE_RETURN(var_name, validation_expression)

  //When getting a property we can check its boundaries, if it fails we return null
  #define DECLARE_VALIDATED_DEFAULT(data_type, var_name, args, in_out_id, prop_name, validation_expression, default_v) \
          DECLARE_PROP_VALUE(data_type, var_name, args, in_out_id, prop_name)                                          \
          VALIDATE_DEFAULT(var_name, validation_expression, default_v)


  //{ Aliases
    //Larger macros, where the name of the variable can differ from the name of the property
    #define INPUT_RENAME(data_type, var_name, args, prop_name) \
            DECLARE_INPUT_PROP_VALUE(data_type, var_name, args, INPUT_PROPS , prop_name)
    #define OUTPUT_RENAME(data_type, var_name, args, prop_name) \
            DECLARE_PROP_VALUE(data_type, var_name, args, OUTPUT_PROPS, prop_name)

    //Define shorter macros. Name of variable is the same as name of property (var_name=prop_name)
    #define INPUT(data_type, var_name, args) \
            DECLARE_INPUT_PROP_VALUE(data_type, var_name, args, INPUT_PROPS , var_name)
    #define INPUT_REF(data_type, var_name, args) \
            DECLARE_INPUT_PROP_REF(data_type, var_name, args, INPUT_PROPS , var_name)
    #define OUTPUT(data_type, var_name, args) \
            DECLARE_PROP_VALUE(data_type, var_name, args, OUTPUT_PROPS, var_name)

    //Define shorter macros. Name of variable is the same as name of property (var_name=prop_name)
    //With validation_expression version. Returns if fails.
    #define INPUT_VALIDATED_RETURN(data_type, var_name, args, validation_expression)   \
            DECLARE_INPUT_PROP_VALUE(data_type, var_name, args, in_out_id, prop_name)  \
            VALIDATE_RETURN(var_name, validation_expression)

    //Define shorter macros. Name of variable is the same as name of property (var_name=prop_name)
    //With validation_expression version. Set default value if fails.
    #define INPUT_VALIDATED_DEFAULT(data_type, var_name, args, validation_expression, default_v) \
            DECLARE_INPUT_PROP_VALIDATED(data_type, var_name, args, INPUT_PROPS, var_name, VALIDATE_DEFAULT(var_name, validation_expression, default_v))

  //} Aliases
//} Properties' variable declaration and value replacement Macros


#endif /* PROPS_MACROS_H_ */
