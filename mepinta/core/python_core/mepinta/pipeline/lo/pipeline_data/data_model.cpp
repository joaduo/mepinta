#include "builtin.hpp"
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

/**
Mepinta
Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar

This file is part of Mepinta.

Mepinta is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mepinta is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mepinta. If not, see <http://www.gnu.org/licenses/>.
*/

namespace __mepinta__ {
namespace __pipeline__ {
namespace __lo__ {
namespace __pipeline_data__ {
namespace __data_model__ {

str *const_0, *const_1, *const_10, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

using __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller;
using __pipeline_backend__::__solve_symbol__::__solve_symbol__::solve_symbol;
using __copy__::deepcopy;
using __pipeline_backend__::__logging__::__logging__::logDebug;
using __pipeline_backend__::__logging__::__logging__::logWarning;
using __pipeline_backend__::__logging__::__logging__::logCritical;
using __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph;
using __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections;
using __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError;

str *MEPINTA_C_NAMESPACE_PREFIX, *__name__;
__ss_int FUNCTION_PROPERTY_FLAG, NULL_UID;


str * default_3;
void * default_1;
void * default_0;
__ss_int  default_4;
Topology * default_2;


/**
class DataType
*/

class_ *cl_DataType;

void *DataType::updateHandle(void *lib_handle) {
    dict<str *, void *>::for_in_loop __48;
    __iter<str *> *__46;
    __ss_int __47;
    dict<str *, void *> *__45, *__49;
    str *name;

    this->lib_handle = lib_handle;

    FOR_IN(name,this->symbols,45,47,48)
        this->symbols->__setitem__(name, this->solve_symbol(name));
    END_FOR

    return NULL;
}

str *DataType::__str__() {
    
    return this->name;
}

void *DataType::getFuncPtr(str *name) {
    dict<str *, void *> *__44;

    if ((!(this->symbols)->__contains__(name))) {
        this->symbols->__setitem__(name, this->solve_symbol(name));
    }
    return (this->symbols)->__getitem__(name);
}

void *DataType::solve_symbol(str *name) {
    
    return __pipeline_backend__::__solve_symbol__::__solve_symbol__::solve_symbol(this->lib_handle, __modct(const_0, 2, MEPINTA_C_NAMESPACE_PREFIX, this->name), name);
}

void *DataType::__init__(str *name, void *lib_handle) {
    
    this->name = name;
    this->lib_handle = lib_handle;
    this->symbols = (new dict<str *, void *>());
    return NULL;
}

/**
class ProcessorFunction
*/

class_ *cl_ProcessorFunction;

void *ProcessorFunction::getFuncPointer() {
    
    return this->func_pointer;
}

void *ProcessorFunction::updateFuncPointer(void *func_pointer) {
    
    this->func_pointer = func_pointer;
    return NULL;
}

void *ProcessorFunction::__init__(str *name, void *func_pointer) {
    
    this->name = name;
    this->func_pointer = func_pointer;
    return NULL;
}

/**
class PropertyValuePointer
*/

class_ *cl_PropertyValuePointer;

void *PropertyValuePointer::decrementReferenceCount(void *func_ptr_del) {
    
    this->count = (this->count-1);
    if ((this->count==0)) {
        this->freeValue(func_ptr_del);
    }
    return NULL;
}

void *PropertyValuePointer::incrementReferenceCount() {
    
    this->count = (this->count+1);
    logDebug(__modct(const_1, 2, ___box(this->count), this));
    return NULL;
}

__ss_bool PropertyValuePointer::notReferenced() {
    
    return ___bool((this->count==0));
}

void *PropertyValuePointer::freeValue(void *func_ptr_del) {
    str *msg;

    if ((this->value!=NULL)) {
        if (((this->function_caller)->callFunc(func_ptr_del, this->value)!=NULL)) {
            msg = __modct(const_2, 1, this);
            logCritical(msg);
            throw ((new __mepinta__::__pipeline__::__lo__::__exceptions__::__MepintaLoError__::MepintaLoError(msg)));
        }
    }
    return NULL;
}

void *PropertyValuePointer::getValue() {
    
    return this->value;
}

void *PropertyValuePointer::__init__(void *value) {
    
    this->count = 0;
    this->value = value;
    this->function_caller = (new __mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller());
    return NULL;
}

void *PropertyValuePointer::replaceValue(void *value, void *func_ptr_del) {
    
    this->freeValue(func_ptr_del);
    this->value = value;
    return NULL;
}

/**
class Property
*/

class_ *cl_Property;

PropertyValuePointer *Property::getValuePtr() {
    
    return this->value_ptr;
}

str *Property::__str__() {
    
    return this->name;
}

void *Property::setValuePtr(PropertyValuePointer *value_ptr, void *func_ptr_del) {
    PropertyValuePointer *old_value_ptr;

    if (__ne(this->value_ptr, value_ptr)) {
        old_value_ptr = this->value_ptr;
        this->value_ptr = value_ptr;
        (this->value_ptr)->incrementReferenceCount();
        old_value_ptr->decrementReferenceCount(func_ptr_del);
    }
    return NULL;
}

void *Property::getValue() {
    
    return (this->value_ptr)->getValue();
}

void *Property::__init__(__ss_int prop_type, str *name, __ss_int dtype_id) {
    
    this->type = prop_type;
    this->name = name;
    this->dtype_id = dtype_id;
    this->value_ptr = (new PropertyValuePointer(NULL));
    (this->value_ptr)->incrementReferenceCount();
    return NULL;
}

/**
class Topology
*/

class_ *cl_Topology;

void *Topology::disconnect(__ss_int dent_id, __ss_int dency_id) {
    
    (this->connections)->disconnect(dent_id, dency_id);
    (this->changed_primary)->add(dent_id);
    return NULL;
}

void *Topology::disconnectAll(__ss_int prop_id) {
    
    (this->changed_primary)->update(1, (new set<__ss_int>((this->connections)->disconnectAll(prop_id))));
    return NULL;
}

void *Topology::connectDency(__ss_int dent_id, __ss_int dency_id) {
    
    (this->connections)->connectDency(dent_id, dency_id);
    return NULL;
}

void *Topology::addPropId(__ss_int prop_id) {
    
    (this->properties)->add(prop_id);
    (this->changed_primary)->add(prop_id);
    return NULL;
}

str *Topology::__str__() {
    
    if ((len(this->properties)==0)) {
        return const_3;
    }
    else if ((len(this->connections)==0)) {
        return __modct(const_4, 1, this->properties);
    }
    else {
        return (this->connections)->__str__();
    }
    return 0;
}

void *Topology::removePropId(__ss_int prop_id) {
    
    if ((this->properties)->__contains__(prop_id)) {
        (this->properties)->remove(prop_id);
        (this->connections)->disconnectAll(prop_id);
        this->__removeFromSet(prop_id, this->cached);
        this->__removeFromSet(prop_id, this->changed_primary);
    }
    return NULL;
}

void *Topology::disconnectDpdencies(__ss_int dent_id) {
    
    (this->connections)->disconnectDpdencies(dent_id);
    (this->changed_primary)->add(dent_id);
    return NULL;
}

void *Topology::connect(__ss_int dent_id, __ss_int dency_id) {
    
    (this->connections)->connect(dent_id, dency_id);
    (this->changed_primary)->add(dent_id);
    return NULL;
}

void *Topology::copyFrom(Topology *copied_topo) {
    
    this->properties = deepcopy(copied_topo->properties);
    this->connections = deepcopy(copied_topo->connections);
    this->cached = deepcopy(copied_topo->cached);
    return NULL;
}

void *Topology::connectDent(__ss_int dent_id, __ss_int dency_id) {
    
    (this->connections)->connectDent(dent_id, dency_id);
    (this->changed_primary)->add(dent_id);
    return NULL;
}

void *Topology::__initValues() {
    
    this->properties = (new set<__ss_int>());
    this->connections = (new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections(1));
    this->cached = (new set<__ss_int>());
    return NULL;
}

void *Topology::__init__(Topology *copied) {
    
    this->changed_primary = (new set<__ss_int>());
    if ((copied==NULL)) {
        this->__initValues();
    }
    else {
        this->copyFrom(copied);
    }
    return NULL;
}

void *Topology::__removeFromSet(__ss_int prop_id, set<__ss_int> *set_) {
    
    if ((set_)->__contains__(prop_id)) {
        set_->remove(prop_id);
    }
    return NULL;
}

/**
class Pipeline
*/

class_ *cl_Pipeline;

Topology *Pipeline::getTopology(__ss_int topo_id) {
    
    if ((topo_id==NULL_UID)) {
        return (this->topologies)->__getitem__(this->current_topolgy_id);
    }
    else {
        return (this->topologies)->__getitem__(topo_id);
    }
    return 0;
}

__ss_bool Pipeline::pendingChanges() {
    
    return ___bool((0!=len((this->getTopology(default_4))->changed_primary)));
}

__ss_int Pipeline::startTopologyChangeSet() {
    dict<__ss_int, Topology *> *__51;
    Topology *base_topo;

    base_topo = this->getTopology(default_4);
    (this->changed_primary)->update(1, base_topo->changed_primary);
    this->current_topolgy_id = this->__newTopologyId();
    this->topologies->__setitem__(this->current_topolgy_id, (new Topology(base_topo)));
    return this->current_topolgy_id;
}

__ss_int Pipeline::addProperty(Property *prop) {
    __ss_int prop_id;
    dict<__ss_int, Property *> *__52;

    prop_id = this->__newPropertyId();
    this->all_properties->__setitem__(prop_id, prop);
    (this->changed_track)->add(prop_id);
    return prop_id;
}

Topology *Pipeline::popTopology(__ss_int topo_id) {
    
    if ((topo_id!=this->getCurrentTopologyId())) {
        return (this->topologies)->pop(topo_id);
    }
    else {
        logWarning(const_5);
        return NULL;
    }
    return 0;
}

__ss_int Pipeline::__newTopologyId() {
    
    this->topology_id_count = (this->topology_id_count+1);
    return this->topology_id_count;
}

__ss_int Pipeline::getCurrentTopologyId() {
    
    return this->current_topolgy_id;
}

void *Pipeline::setCurrentTopologyId(__ss_int topo_id) {
    
    this->current_topolgy_id = topo_id;
    return NULL;
}

Property *Pipeline::deleteProperty(__ss_int prop_id) {
    __iter<Topology *> *__54;
    Property *prop;
    dictentry<__ss_int, Topology *> *__57;
    Topology *topo;
    list<Topology *>::for_in_loop __56;
    list<Topology *> *__53;
    __ss_int __55;
    dict<__ss_int, Topology *> *__58;

    prop = (this->all_properties)->pop(prop_id);

    FOR_IN(topo,(this->topologies)->values(),53,55,56)
        topo->removePropId(prop_id);
    END_FOR

    (this->cached_link)->__delitem__(prop_id);
    if ((this->marked_outputs)->__contains__(prop_id)) {
        (this->marked_outputs)->remove(prop_id);
    }
    if ((this->changed_track)->__contains__(prop_id)) {
        (this->changed_track)->remove(prop_id);
    }
    return prop;
}

void *Pipeline::__initTopo() {
    dict<__ss_int, Topology *> *__50;

    this->current_topolgy_id = this->__newTopologyId();
    this->topologies->__setitem__(this->current_topolgy_id, (new Topology(NULL)));
    return NULL;
}

__ss_int Pipeline::__newPropertyId() {
    
    this->property_id_count = (this->property_id_count+1);
    return this->property_id_count;
}

void *Pipeline::__init__(str *name) {
    
    this->name = name;
    this->property_id_count = NULL_UID;
    this->all_properties = (new dict<__ss_int, Property *>());
    this->current_topolgy_id = NULL_UID;
    this->topology_id_count = NULL_UID;
    this->topologies = (new dict<__ss_int, Topology *>());
    this->marked_outputs = (new set<__ss_int>());
    this->changed_track = (new set<__ss_int>());
    this->changed_primary = (new set<__ss_int>());
    this->cached_link = (new __mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph(1));
    this->__initTopo();
    return NULL;
}

tuple2<Pipeline *, __ss_int> *shedskin_pipeline_data_model() {
    DataType *dt;
    PropertyValuePointer *pvp;
    ProcessorFunction *pf;
    Property *prop;
    str *name;
    Topology *topo;
    void *func_pointer, *func_ptr_del, *lib_handle;
    Pipeline *pline;
    __ss_int dtype_id, prop_id, topo_id;

    lib_handle = NULL;
    name = const_6;
    dt = (new DataType(name, lib_handle));
    dt->getFuncPtr(const_7);
    dt->updateHandle(lib_handle);
    dt->__repr__();
    func_pointer = NULL;
    pf = (new ProcessorFunction(name, func_pointer));
    pf->getFuncPointer();
    pf->updateFuncPointer(func_pointer);
    pvp = (new PropertyValuePointer(NULL));
    func_ptr_del = func_pointer;
    pvp->replaceValue(NULL, func_ptr_del);
    pvp->freeValue(func_ptr_del);
    pvp->getValue();
    pvp->incrementReferenceCount();
    pvp->decrementReferenceCount(func_ptr_del);
    pvp->notReferenced();
    dtype_id = 1;
    prop = (new Property(FUNCTION_PROPERTY_FLAG, name, dtype_id));
    prop->getValue();
    prop->getValuePtr();
    prop->setValuePtr(pvp, func_ptr_del);
    prop->__repr__();
    pline = (new Pipeline(const_8));
    pline->addProperty(prop);
    topo_id = 1;
    pline->setCurrentTopologyId(topo_id);
    topo = (new Topology(NULL));
    topo = (new Topology(topo));
    topo->copyFrom(topo);
    topo->addPropId(1);
    topo->addPropId(2);
    topo->connect(1, 2);
    topo->disconnect(1, 2);
    topo->disconnectAll(1);
    topo->disconnectDpdencies(1);
    topo->removePropId(1);
    topo->__str__();
    pline->startTopologyChangeSet();
    pline->pendingChanges();
    pline->getTopology(default_4);
    pline->popTopology(pline->getCurrentTopologyId());
    prop_id = pline->addProperty(prop);
    (pline->changed_track)->add(prop_id);
    (pline->cached_link)->add(prop_id, prop_id);
    (pline->marked_outputs)->add(prop_id);
    pline->deleteProperty(prop_id);
    prop_id = pline->addProperty(prop);
    return (new tuple2<Pipeline *, __ss_int>(2,pline,prop_id));
}

void __init() {
    const_0 = new str("%s%s_");
    const_1 = new str("Reference count=%r for %r");
    const_2 = new str("Couldn't free pipeline value for %s. This may mean a memory leak.");
    const_3 = new str("Empty Topology");
    const_4 = new str("%r with no connections");
    const_5 = new str("You can't remove current topology ");
    const_6 = new str("name");
    const_7 = new str("symbol searched");
    const_8 = new str("actiontree");
    const_9 = new str("default");
    const_10 = new str("__main__");

    __name__ = new str("data_model");

    FUNCTION_PROPERTY_FLAG = __mepinta__::__pipeline__::__lo__::__constants__::FUNCTION_PROPERTY_FLAG;
    MEPINTA_C_NAMESPACE_PREFIX = __mepinta__::__pipeline__::__lo__::__constants__::MEPINTA_C_NAMESPACE_PREFIX;
    NULL_UID = __mepinta__::__pipeline__::__lo__::__constants__::NULL_UID;
    cl_DataType = new class_("DataType");
    cl_ProcessorFunction = new class_("ProcessorFunction");
    default_0 = NULL;
    cl_PropertyValuePointer = new class_("PropertyValuePointer");
    default_1 = NULL;
    cl_Property = new class_("Property");
    default_2 = NULL;
    cl_Topology = new class_("Topology");
    default_3 = const_9;
    default_4 = NULL_UID;
    cl_Pipeline = new class_("Pipeline");
    if (__eq(__name__, const_10)) {
        shedskin_pipeline_data_model();
    }
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

/* extension module glue */

extern "C" {
#include <Python.h>
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"
#include <structmember.h>
#include "copy.hpp"
#include "pipeline_backend/void_pointer_casting/void_pointer_casting.hpp"
#include "pipeline_backend/solve_symbol/solve_symbol.hpp"
#include "pipeline_backend/solve_symbol/__init__.hpp"
#include "pipeline_backend/__init__.hpp"
#include "pipeline_backend/void_pointer_casting/__init__.hpp"
#include "pipeline_backend/logging/logging.hpp"
#include "sys.hpp"
#include "pipeline_backend/logging/__init__.hpp"
#include "mepinta/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/TopologyConnections.hpp"
#include "mepinta/pipeline/lo/exceptions/MepintaLoError.hpp"
#include "mepinta/pipeline/lo/pipeline_data/data_model.hpp"
#include "mepinta/pipeline/lo/constants.hpp"
#include "mepinta/pipeline/lo/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/BiDirectedGraph.hpp"
#include "mepinta/pipeline/lo/pipeline_data/hidden_data_types.hpp"
#include "mepinta/pipeline/lo/generic_data/__init__.hpp"
#include "mepinta/pipeline/lo/exceptions/__init__.hpp"
#include "mepinta/pipeline/lo/generic_data/DirectedGraph.hpp"
#include "mepinta/pipeline/__init__.hpp"
#include "mepinta/pipeline/lo/pipeline_data/__init__.hpp"
#include "mepinta/pipeline/lo/FunctionCaller.hpp"

PyObject *__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model;

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

/* class DataType */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_updateHandle(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("lib_handle", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->updateHandle(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___str__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->__str__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_getFuncPtr(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("name", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->getFuncPtr(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_solve_symbol(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("name", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->solve_symbol(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("name", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("lib_handle", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->__init__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"updateHandle", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_updateHandle, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__str__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___str__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getFuncPtr", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_getFuncPtr, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"solve_symbol", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_solve_symbol, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::cl_DataType;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeDealloc(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self, void *closure) {
    return __to_py(self->__ss_object->name);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->name = __to_ss<str *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_symbols(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self, void *closure) {
    return __to_py(self->__ss_object->symbols);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_symbols(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->symbols = __to_ss<dict<str *, void *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_lib_handle(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self, void *closure) {
    return __to_py(self->__ss_object->lib_handle);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_lib_handle(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->lib_handle = NULL;
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeGetSet[] = {
    {(char *)"name", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_name, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_name, (char *)"", NULL},
    {(char *)"symbols", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_symbols, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_symbols, (char *)"", NULL},
    {(char *)"lib_handle", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_lib_handle, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_lib_handle, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "data_model.DataType",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    (PyObject *(*)(PyObject *))__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___str__, /* tp_str           */
    0,              /* tp_getattro       */
    0,              /* tp_setattro       */
    0,              /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT, /* tp_flags          */
    0,              /* tp_doc            */
    0,              /* tp_traverse       */
    0,              /* tp_clear          */
    0,              /* tp_richcompare    */
    0,              /* tp_weaklistoffset */
    0,              /* tp_iter           */
    0,              /* tp_iternext       */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->name));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->symbols));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->lib_handle));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataType__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->name = __to_ss<str *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->symbols = __to_ss<dict<str *, void *> *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)self)->__ss_object->lib_handle = __to_ss<void *>(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __data_model__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

/* class ProcessorFunction */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_getFuncPointer(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)self)->__ss_object->getFuncPointer());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_updateFuncPointer(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_pointer", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)self)->__ss_object->updateFuncPointer(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("name", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("func_pointer", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)self)->__ss_object->__init__(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getFuncPointer", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_getFuncPointer, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"updateFuncPointer", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_updateFuncPointer, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::cl_ProcessorFunction;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionDealloc(__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *self, void *closure) {
    return __to_py(self->__ss_object->name);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->name = __to_ss<str *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_func_pointer(__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *self, void *closure) {
    return __to_py(self->__ss_object->func_pointer);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_func_pointer(__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->func_pointer = NULL;
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionGetSet[] = {
    {(char *)"name", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_name, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_name, (char *)"", NULL},
    {(char *)"func_pointer", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_func_pointer, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_func_pointer, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "data_model.ProcessorFunction",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    0,              /* tp_str            */
    0,              /* tp_getattro       */
    0,              /* tp_setattro       */
    0,              /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT, /* tp_flags          */
    0,              /* tp_doc            */
    0,              /* tp_traverse       */
    0,              /* tp_clear          */
    0,              /* tp_richcompare    */
    0,              /* tp_weaklistoffset */
    0,              /* tp_iter           */
    0,              /* tp_iternext       */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(2);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)self)->__ss_object->name));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)self)->__ss_object->func_pointer));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunction__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)self)->__ss_object->name = __to_ss<str *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)self)->__ss_object->func_pointer = __to_ss<void *>(PyTuple_GetItem(state, 1));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __data_model__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

/* class PropertyValuePointer */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_decrementReferenceCount(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_ptr_del", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->decrementReferenceCount(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_incrementReferenceCount(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->incrementReferenceCount());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_notReferenced(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->notReferenced());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_freeValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("func_ptr_del", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->freeValue(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_getValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->getValue());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("value", 0, 1, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_replaceValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        void *arg_0 = __ss_arg<void *>("value", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("func_ptr_del", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->replaceValue(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"decrementReferenceCount", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_decrementReferenceCount, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"incrementReferenceCount", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_incrementReferenceCount, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"notReferenced", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_notReferenced, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"freeValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_freeValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_getValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"replaceValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_replaceValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::cl_PropertyValuePointer;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerDealloc(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_count(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self, void *closure) {
    return __to_py(self->__ss_object->count);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_count(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->count = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_value(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self, void *closure) {
    return __to_py(self->__ss_object->value);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_value(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->value = NULL;
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_function_caller(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self, void *closure) {
    return __to_py(self->__ss_object->function_caller);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_function_caller(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->function_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerGetSet[] = {
    {(char *)"count", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_count, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_count, (char *)"", NULL},
    {(char *)"value", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_value, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_value, (char *)"", NULL},
    {(char *)"function_caller", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_function_caller, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_function_caller, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "data_model.PropertyValuePointer",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    0,              /* tp_str            */
    0,              /* tp_getattro       */
    0,              /* tp_setattro       */
    0,              /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT, /* tp_flags          */
    0,              /* tp_doc            */
    0,              /* tp_traverse       */
    0,              /* tp_clear          */
    0,              /* tp_richcompare    */
    0,              /* tp_weaklistoffset */
    0,              /* tp_iter           */
    0,              /* tp_iternext       */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(3);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->count));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->value));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->function_caller));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointer__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->count = __to_ss<__ss_int >(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->value = __to_ss<void *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)self)->__ss_object->function_caller = __to_ss<__mepinta__::__pipeline__::__lo__::__FunctionCaller__::FunctionCaller *>(PyTuple_GetItem(state, 2));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __data_model__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

/* class Property */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_getValuePtr(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->getValuePtr());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___str__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->__str__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_setValuePtr(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        PropertyValuePointer *arg_0 = __ss_arg<PropertyValuePointer *>("value_ptr", 0, 0, 0, args, kwargs);
        void *arg_1 = __ss_arg<void *>("func_ptr_del", 1, 1, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->setValuePtr(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_getValue(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->getValue());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_type", 0, 0, 0, args, kwargs);
        str *arg_1 = __ss_arg<str *>("name", 1, 0, 0, args, kwargs);
        __ss_int arg_2 = __ss_arg<__ss_int >("dtype_id", 2, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->__init__(arg_0, arg_1, arg_2));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getValuePtr", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_getValuePtr, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__str__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___str__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setValuePtr", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_setValuePtr, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getValue", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_getValue, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::cl_Property;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyDealloc(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_dtype_id(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, void *closure) {
    return __to_py(self->__ss_object->dtype_id);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_dtype_id(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->dtype_id = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_value_ptr(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, void *closure) {
    return __to_py(self->__ss_object->value_ptr);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_value_ptr(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->value_ptr = __to_ss<PropertyValuePointer *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_type(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, void *closure) {
    return __to_py(self->__ss_object->type);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_type(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->type = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, void *closure) {
    return __to_py(self->__ss_object->name);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->name = __to_ss<str *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyGetSet[] = {
    {(char *)"dtype_id", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_dtype_id, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_dtype_id, (char *)"", NULL},
    {(char *)"value_ptr", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_value_ptr, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_value_ptr, (char *)"", NULL},
    {(char *)"type", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_type, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_type, (char *)"", NULL},
    {(char *)"name", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_name, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_name, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "data_model.Property",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    (PyObject *(*)(PyObject *))__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___str__, /* tp_str           */
    0,              /* tp_getattro       */
    0,              /* tp_setattro       */
    0,              /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT, /* tp_flags          */
    0,              /* tp_doc            */
    0,              /* tp_traverse       */
    0,              /* tp_clear          */
    0,              /* tp_richcompare    */
    0,              /* tp_weaklistoffset */
    0,              /* tp_iter           */
    0,              /* tp_iternext       */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_Property___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(4);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->dtype_id));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->value_ptr));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->type));
    PyTuple_SetItem(b, 3, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->name));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Property__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->dtype_id = __to_ss<__ss_int >(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->value_ptr = __to_ss<PropertyValuePointer *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->type = __to_ss<__ss_int >(PyTuple_GetItem(state, 2));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)self)->__ss_object->name = __to_ss<str *>(PyTuple_GetItem(state, 3));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __data_model__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

/* class Topology */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_disconnect(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->disconnect(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_disconnectAll(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->disconnectAll(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connectDency(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->connectDency(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_addPropId(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->addPropId(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___str__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->__str__());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_removePropId(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->removePropId(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_disconnectDpdencies(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->disconnectDpdencies(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connect(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->connect(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_copyFrom(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        Topology *arg_0 = __ss_arg<Topology *>("copied_topo", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->copyFrom(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connectDent(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("dent_id", 0, 0, 0, args, kwargs);
        __ss_int arg_1 = __ss_arg<__ss_int >("dency_id", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->connectDent(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___initValues(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->__initValues());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        Topology *arg_0 = __ss_arg<Topology *>("copied", 0, 1, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___removeFromSet(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);
        set<__ss_int> *arg_1 = __ss_arg<set<__ss_int> *>("set_", 1, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->__removeFromSet(arg_0, arg_1));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnect", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_disconnect, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectAll", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_disconnectAll, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connectDency", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connectDency, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"addPropId", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_addPropId, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__str__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___str__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"removePropId", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_removePropId, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"disconnectDpdencies", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_disconnectDpdencies, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connect", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connect, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"copyFrom", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_copyFrom, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"connectDent", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connectDent, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__initValues", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___initValues, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__removeFromSet", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___removeFromSet, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::cl_Topology;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyDealloc(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connections(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, void *closure) {
    return __to_py(self->__ss_object->connections);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connections(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->connections = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_changed_primary(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, void *closure) {
    return __to_py(self->__ss_object->changed_primary);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_changed_primary(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->changed_primary = __to_ss<set<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_properties(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, void *closure) {
    return __to_py(self->__ss_object->properties);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_properties(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->properties = __to_ss<set<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_cached(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, void *closure) {
    return __to_py(self->__ss_object->cached);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_cached(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->cached = __to_ss<set<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyGetSet[] = {
    {(char *)"connections", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connections, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_connections, (char *)"", NULL},
    {(char *)"changed_primary", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_changed_primary, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_changed_primary, (char *)"", NULL},
    {(char *)"properties", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_properties, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_properties, (char *)"", NULL},
    {(char *)"cached", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_cached, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_cached, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "data_model.Topology",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    (PyObject *(*)(PyObject *))__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___str__, /* tp_str           */
    0,              /* tp_getattro       */
    0,              /* tp_setattro       */
    0,              /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT, /* tp_flags          */
    0,              /* tp_doc            */
    0,              /* tp_traverse       */
    0,              /* tp_clear          */
    0,              /* tp_richcompare    */
    0,              /* tp_weaklistoffset */
    0,              /* tp_iter           */
    0,              /* tp_iternext       */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(4);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->connections));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->changed_primary));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->properties));
    PyTuple_SetItem(b, 3, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->cached));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Topology__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->connections = __to_ss<__mepinta__::__pipeline__::__lo__::__pipeline_data__::__TopologyConnections__::TopologyConnections *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->changed_primary = __to_ss<set<__ss_int> *>(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->properties = __to_ss<set<__ss_int> *>(PyTuple_GetItem(state, 2));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)self)->__ss_object->cached = __to_ss<set<__ss_int> *>(PyTuple_GetItem(state, 3));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __data_model__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

/* class Pipeline */

typedef struct {
    PyObject_HEAD
    __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *__ss_object;
} __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject;

static PyMemberDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineMembers[] = {
    {NULL}
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_getTopology(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("topo_id", 0, 1, __data_model__::default_4, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->getTopology(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_pendingChanges(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->pendingChanges());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_startTopologyChangeSet(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->startTopologyChangeSet());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_addProperty(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        Property *arg_0 = __ss_arg<Property *>("prop", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->addProperty(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_popTopology(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("topo_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->popTopology(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___newTopologyId(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->__newTopologyId());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_getCurrentTopologyId(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->getCurrentTopologyId());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_setCurrentTopologyId(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("topo_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->setCurrentTopologyId(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_deleteProperty(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        __ss_int arg_0 = __ss_arg<__ss_int >("prop_id", 0, 0, 0, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->deleteProperty(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___initTopo(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->__initTopo());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___newPropertyId(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->__newPropertyId());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___init__(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {
        str *arg_0 = __ss_arg<str *>("name", 0, 1, __data_model__::default_3, args, kwargs);

        return __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->__init__(arg_0));

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods __ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline__reduce__(PyObject *self, PyObject *args, PyObject *kwargs);
PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline__setstate__(PyObject *self, PyObject *args, PyObject *kwargs);

static PyMethodDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineMethods[] = {
    {(char *)"__reduce__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline__reduce__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__setstate__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline__setstate__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getTopology", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_getTopology, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"pendingChanges", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_pendingChanges, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"startTopologyChangeSet", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_startTopologyChangeSet, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"addProperty", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_addProperty, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"popTopology", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_popTopology, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__newTopologyId", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___newTopologyId, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"getCurrentTopologyId", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_getCurrentTopologyId, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"setCurrentTopologyId", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_setCurrentTopologyId, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"deleteProperty", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_deleteProperty, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__initTopo", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___initTopo, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__newPropertyId", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___newPropertyId, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"__init__", (PyCFunction)__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___init__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

int __ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___tpinit__(PyObject *self, PyObject *args, PyObject *kwargs) {
    if(!__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___init__(self, args, kwargs))
        return -1;
    return 0;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineNew(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)type->tp_alloc(type, 0);
    self->__ss_object = new __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline();
    self->__ss_object->__class__ = __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::cl_Pipeline;
    __ss_proxy->__setitem__(self->__ss_object, self);
    return (PyObject *)self;
}

void __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineDealloc(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self) {
    self->ob_type->tp_free((PyObject *)self);
    __ss_proxy->__delitem__(self->__ss_object);
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_primary(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->changed_primary);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_primary(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->changed_primary = __to_ss<set<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_property_id_count(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->property_id_count);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_property_id_count(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->property_id_count = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_marked_outputs(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->marked_outputs);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_marked_outputs(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->marked_outputs = __to_ss<set<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_all_properties(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->all_properties);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_all_properties(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->all_properties = __to_ss<dict<__ss_int, Property *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_current_topolgy_id(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->current_topolgy_id);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_current_topolgy_id(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->current_topolgy_id = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_track(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->changed_track);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_track(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->changed_track = __to_ss<set<__ss_int> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topologies(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->topologies);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topologies(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->topologies = __to_ss<dict<__ss_int, Topology *> *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topology_id_count(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->topology_id_count);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topology_id_count(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->topology_id_count = __to_ss<__ss_int >(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->name);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_name(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->name = __to_ss<str *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyObject *__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_cached_link(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, void *closure) {
    return __to_py(self->__ss_object->cached_link);
}

int __ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_cached_link(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self, PyObject *value, void *closure) {
    try {
        self->__ss_object->cached_link = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(value);
    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return -1;
    }
    return 0;
}

PyGetSetDef __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineGetSet[] = {
    {(char *)"changed_primary", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_primary, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_primary, (char *)"", NULL},
    {(char *)"property_id_count", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_property_id_count, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_property_id_count, (char *)"", NULL},
    {(char *)"marked_outputs", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_marked_outputs, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_marked_outputs, (char *)"", NULL},
    {(char *)"all_properties", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_all_properties, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_all_properties, (char *)"", NULL},
    {(char *)"current_topolgy_id", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_current_topolgy_id, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_current_topolgy_id, (char *)"", NULL},
    {(char *)"changed_track", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_track, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_changed_track, (char *)"", NULL},
    {(char *)"topologies", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topologies, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topologies, (char *)"", NULL},
    {(char *)"topology_id_count", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topology_id_count, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_topology_id_count, (char *)"", NULL},
    {(char *)"name", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_name, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_name, (char *)"", NULL},
    {(char *)"cached_link", (getter)__ss_get___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_cached_link, (setter)__ss_set___ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_cached_link, (char *)"", NULL},
    {NULL}
};

PyTypeObject __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType = {
    PyObject_HEAD_INIT(NULL)
    0,              /* ob_size           */
    "data_model.Pipeline",        /* tp_name           */
    sizeof(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject), /* tp_basicsize      */
    0,              /* tp_itemsize       */
    (destructor)__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineDealloc, /* tp_dealloc        */
    0,              /* tp_print          */
    0,              /* tp_getattr        */
    0,              /* tp_setattr        */
    0,              /* tp_compare        */
    0,              /* tp_repr           */
    &__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline_as_number,  /* tp_as_number      */
    0,              /* tp_as_sequence    */
    0,              /* tp_as_mapping     */
    0,              /* tp_hash           */
    0,              /* tp_call           */
    0,              /* tp_str            */
    0,              /* tp_getattro       */
    0,              /* tp_setattro       */
    0,              /* tp_as_buffer      */
    Py_TPFLAGS_DEFAULT, /* tp_flags          */
    0,              /* tp_doc            */
    0,              /* tp_traverse       */
    0,              /* tp_clear          */
    0,              /* tp_richcompare    */
    0,              /* tp_weaklistoffset */
    0,              /* tp_iter           */
    0,              /* tp_iternext       */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineMethods,      /* tp_methods        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineMembers,      /* tp_members        */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineGetSet,       /* tp_getset         */
    0,              /* tp_base           */
    0,              /* tp_dict           */
    0,              /* tp_descr_get      */
    0,              /* tp_descr_set      */
    0,              /* tp_dictoffset     */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline___tpinit__, /* tp_init           */
    0,              /* tp_alloc          */
    __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineNew,          /* tp_new            */
};

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline__reduce__(PyObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *t = PyTuple_New(3);
    PyTuple_SetItem(t, 0, PyObject_GetAttrString(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "__newobj__"));
    PyObject *a = PyTuple_New(1);
    Py_INCREF((PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType);
    PyTuple_SetItem(a, 0, (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType);
    PyTuple_SetItem(t, 1, a);
    PyObject *b = PyTuple_New(10);
    PyTuple_SetItem(b, 0, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->changed_primary));
    PyTuple_SetItem(b, 1, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->property_id_count));
    PyTuple_SetItem(b, 2, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->marked_outputs));
    PyTuple_SetItem(b, 3, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->all_properties));
    PyTuple_SetItem(b, 4, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->current_topolgy_id));
    PyTuple_SetItem(b, 5, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->changed_track));
    PyTuple_SetItem(b, 6, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->topologies));
    PyTuple_SetItem(b, 7, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->topology_id_count));
    PyTuple_SetItem(b, 8, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->name));
    PyTuple_SetItem(b, 9, __to_py(((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->cached_link));
    PyTuple_SetItem(t, 2, b);
    return t;
}

PyObject *__ss_mepinta_pipeline_lo_pipeline_data_data_model_Pipeline__setstate__(PyObject *self, PyObject *args, PyObject *kwargs) {
    int l = PyTuple_Size(args);
    PyObject *state = PyTuple_GetItem(args, 0);
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->changed_primary = __to_ss<set<__ss_int> *>(PyTuple_GetItem(state, 0));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->property_id_count = __to_ss<__ss_int >(PyTuple_GetItem(state, 1));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->marked_outputs = __to_ss<set<__ss_int> *>(PyTuple_GetItem(state, 2));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->all_properties = __to_ss<dict<__ss_int, Property *> *>(PyTuple_GetItem(state, 3));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->current_topolgy_id = __to_ss<__ss_int >(PyTuple_GetItem(state, 4));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->changed_track = __to_ss<set<__ss_int> *>(PyTuple_GetItem(state, 5));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->topologies = __to_ss<dict<__ss_int, Topology *> *>(PyTuple_GetItem(state, 6));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->topology_id_count = __to_ss<__ss_int >(PyTuple_GetItem(state, 7));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->name = __to_ss<str *>(PyTuple_GetItem(state, 8));
    ((__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)self)->__ss_object->cached_link = __to_ss<__mepinta__::__pipeline__::__lo__::__generic_data__::__DirectedGraph__::DirectedGraph *>(PyTuple_GetItem(state, 9));
    Py_INCREF(Py_None);
    return Py_None;
}

} // namespace __mepinta__
} // namespace __pipeline__
} // namespace __lo__
} // namespace __pipeline_data__
} // namespace __data_model__

namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */
PyObject *Global_mepinta_pipeline_lo_pipeline_data_data_model_shedskin_pipeline_data_model(PyObject *self, PyObject *args, PyObject *kwargs) {
    try {

        return __to_py(__data_model__::shedskin_pipeline_data_model());

    } catch (Exception *e) {
        PyErr_SetString(__to_py(e), ((e->message)?(e->message->unit.c_str()):""));
        return 0;
    }
}

static PyNumberMethods Global_mepinta_pipeline_lo_pipeline_data_data_model_as_number = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static PyMethodDef Global_mepinta_pipeline_lo_pipeline_data_data_modelMethods[] = {
    {(char *)"__newobj__", (PyCFunction)__ss__newobj__, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {(char *)"shedskin_pipeline_data_model", (PyCFunction)Global_mepinta_pipeline_lo_pipeline_data_data_model_shedskin_pipeline_data_model, METH_VARARGS | METH_KEYWORDS, (char *)""},
    {NULL}
};

PyMODINIT_FUNC initmepinta_pipeline_lo_pipeline_data_data_model(void) {

    __ss_mod_mepinta_pipeline_lo_pipeline_data_data_model = Py_InitModule((char *)"data_model", Global_mepinta_pipeline_lo_pipeline_data_data_modelMethods);
    if(!__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model)
        return;

    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "DataType", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType);
    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "ProcessorFunction", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType);
    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "PropertyValuePointer", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType);
    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "Property", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType);
    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "Topology", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType);
    if (PyType_Ready(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType) < 0)
        return;

    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, "Pipeline", (PyObject *)&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType);


}

PyMODINIT_FUNC addmepinta_pipeline_lo_pipeline_data_data_model(void) {
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, (char *)"MEPINTA_C_NAMESPACE_PREFIX", __to_py(__data_model__::MEPINTA_C_NAMESPACE_PREFIX));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, (char *)"FUNCTION_PROPERTY_FLAG", __to_py(__data_model__::FUNCTION_PROPERTY_FLAG));
    PyModule_AddObject(__ss_mod_mepinta_pipeline_lo_pipeline_data_data_model, (char *)"NULL_UID", __to_py(__data_model__::NULL_UID));

}

} // namespace __mepinta__

} // namespace __pipeline__

} // namespace __lo__

} // namespace __pipeline_data__

} // namespace __data_model__

} // extern "C"
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

PyObject *DataType::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)(__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType, 0));
        self->__ss_object = this;
        __ss_proxy->__setitem__(self->__ss_object, self);
        p = (PyObject *)self;
    }
    Py_INCREF(p);
    return p;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::DataType *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (DataType expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_DataTypeObject *)p)->__ss_object;
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

PyObject *ProcessorFunction::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)(__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType, 0));
        self->__ss_object = this;
        __ss_proxy->__setitem__(self->__ss_object, self);
        p = (PyObject *)self;
    }
    Py_INCREF(p);
    return p;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::ProcessorFunction *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (ProcessorFunction expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_ProcessorFunctionObject *)p)->__ss_object;
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

PyObject *PropertyValuePointer::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType, 0));
        self->__ss_object = this;
        __ss_proxy->__setitem__(self->__ss_object, self);
        p = (PyObject *)self;
    }
    Py_INCREF(p);
    return p;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::PropertyValuePointer *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (PropertyValuePointer expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyValuePointerObject *)p)->__ss_object;
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

PyObject *Property::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType, 0));
        self->__ss_object = this;
        __ss_proxy->__setitem__(self->__ss_object, self);
        p = (PyObject *)self;
    }
    Py_INCREF(p);
    return p;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Property *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (Property expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_PropertyObject *)p)->__ss_object;
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

PyObject *Topology::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)(__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType, 0));
        self->__ss_object = this;
        __ss_proxy->__setitem__(self->__ss_object, self);
        p = (PyObject *)self;
    }
    Py_INCREF(p);
    return p;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Topology *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (Topology expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_TopologyObject *)p)->__ss_object;
}
}
namespace __mepinta__ { /* XXX */
namespace __pipeline__ { /* XXX */
namespace __lo__ { /* XXX */
namespace __pipeline_data__ { /* XXX */
namespace __data_model__ { /* XXX */

PyObject *Pipeline::__to_py__() {
    PyObject *p;
    if(__ss_proxy->has_key(this))
        p = (PyObject *)(__ss_proxy->__getitem__(this));
    else {
        __ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *self = (__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)(__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType.tp_alloc(&__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType, 0));
        self->__ss_object = this;
        __ss_proxy->__setitem__(self->__ss_object, self);
        p = (PyObject *)self;
    }
    Py_INCREF(p);
    return p;
}

} // module namespace
} // module namespace
} // module namespace
} // module namespace
} // module namespace

namespace __shedskin__ { /* XXX */

template<> __mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::Pipeline *__to_ss(PyObject *p) {
    if(p == Py_None) return NULL;
    if(PyObject_IsInstance(p, (PyObject *)&__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObjectType)!=1)
        throw new TypeError(new str("error in conversion to Shed Skin (Pipeline expected)"));
    return ((__mepinta__::__pipeline__::__lo__::__pipeline_data__::__data_model__::__ss_mepinta_pipeline_lo_pipeline_data_data_model_PipelineObject *)p)->__ss_object;
}
}
