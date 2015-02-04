#ifndef __HEADER_VM__
#define __HEADER_VM__

#include <vector>
#include "Value.hpp"

class VM
{
public:
    void pushFloat(float v);
    void pushCFunction(CFunctionPtr v);
    void pushString(const String & str);

    void add();
    void call();

    float popFloat();
    String popString();

    inline ValueType getType() const { return m_stack.empty() ? VT_NIL : m_stack[m_stack.size() - 1].getType(); }

private:
    Value & getTop();
    void push(const Value & v);
    void pop();
    Value popValue();

    std::vector<Value> m_stack;
    // TODO Bytecode
    // TODO Program counter
    // TODO Stack pointer

};

#endif // __HEADER_VM__

