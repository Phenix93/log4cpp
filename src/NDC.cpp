/*
 * NDC.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the LICENSE file for the terms of usage and distribution.
 */

#include "log4cpp/NDC.hh"

namespace log4cpp {

    NDC::DiagnosticContext::DiagnosticContext(const string& message) :
        message(message),
        fullMessage(message) {
    }

    NDC::DiagnosticContext::DiagnosticContext(const string& message, 
            const DiagnosticContext& parent) :
        message(message),
        fullMessage(parent.message + " " + message) {
    }

    NDC NDC::_nDC;

    void NDC::clear() {
        getNDC()._clear();
    }

    NDC::ContextStack* NDC::cloneStack() {
        return getNDC()._cloneStack();
    }

    const string& NDC::get() {
        return getNDC()._get();
    }

    int NDC::getDepth() {
        return getNDC()._getDepth();
    }

    void NDC::inherit(NDC::ContextStack* stack) {
        getNDC()._inherit(stack);
    }

    string NDC::pop() {
        return getNDC()._pop();
    }

    void NDC::push(const string& message) {
        getNDC()._push(message);
    }

    void NDC::setMaxDepth(int maxDepth) {
        getNDC()._setMaxDepth(maxDepth);
    }

    NDC& NDC::getNDC() {
        return _nDC;
    }

    NDC::NDC() {
    }

    NDC::~NDC() {
    }

    void NDC::_clear() {
        _stack.clear();
    }

    NDC::ContextStack* NDC::_cloneStack() {
        return new ContextStack(_stack);
    }

    const string& NDC::_get() const {
        static string empty = "";

        return _stack.empty() ?
            empty :
            _stack.back().fullMessage;
    }

    int NDC::_getDepth() const {
        return _stack.size();
    }

    void NDC::_inherit(NDC::ContextStack* stack) {
        _stack = *stack;
    }

    string NDC::_pop() {
        string result = _stack.back().message;
        _stack.pop_back();
        return result;
    }

    void NDC::_push(const string& message) {
        if (_stack.empty()) {
            _stack.push_back(DiagnosticContext(message));
        } else {            
            _stack.push_back(DiagnosticContext(message, _stack.back()));
        }
    }

    void NDC::_setMaxDepth(int maxDepth) {
        // XXX no maximum
    }

}
