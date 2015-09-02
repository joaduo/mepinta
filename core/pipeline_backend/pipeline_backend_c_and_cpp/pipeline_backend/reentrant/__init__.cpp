#include "builtin.hpp"
#include "pipeline_backend/reentrant/__init__.hpp"

namespace __pipeline_backend__ {
namespace __reentrant__ {


str *__name__;



void __init() {
    __name__ = new str("reentrant");

}

} // module namespace
} // module namespace

