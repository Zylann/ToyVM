#include "VM.hpp"

void VM::pushFloat(float v)
{
    m_stack.push_back(Value(v));
}

void VM::pushCFunction(CFunctionPtr v)
{
    m_stack.push_back(Value(v));
}

void VM::pushString(const String & str)
{
    m_stack.push_back(Value(str));
}

void VM::add()
{
    if (m_stack.empty())
        return;
    Value res(m_stack[0]);
    for (auto it = m_stack.begin()+1; it != m_stack.end(); ++it)
    {
        const Value & v = *it;
        if (!res.add(v))
            return;
    }
    m_stack.clear();
    push(res);
}

void VM::call()
{
    Value top = getTop();
    pop();
    top.call(*this);
}

float VM::popFloat()
{
    if (m_stack.empty())
        return 0;
    float v = getTop().getFloat();
    pop();
    return v;
}

String VM::popString()
{
    if (m_stack.empty())
        return "";
    String s = getTop().getString();
    pop();
    return s;
}


Value & VM::getTop()
{
    return m_stack[m_stack.size() - 1];
}

void VM::push(const Value & v)
{
    m_stack.push_back(v);
}

void VM::pop()
{
    m_stack.pop_back();
}


