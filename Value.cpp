#include "Value.hpp"

Value::~Value()
{
    reset();
}

void Value::reset()
{
    switch (m_type)
    {
    case VT_STRING:
        delete m_data.pString;
        break;
    case VT_VALUE_ARRAY:
        delete m_data.pValueArray;
        break;
    default:
        break;
    }
    m_type = VT_NIL;
}

void Value::setBool(bool v)
{
    reset();
    m_type = VT_BOOL;
    m_data.vBool = v;
}

void Value::setInt(int v)
{
    reset();
    m_type = VT_INT;
    m_data.vInt = v;
}

void Value::setFloat(float v)
{
    reset();
    m_type = VT_FLOAT;
    m_data.vFloat = v;
}

void Value::setString(const String & v)
{
    reset();
    m_type = VT_STRING;
    m_data.pString = new String(v);
}

void Value::setCFunction(CFunctionPtr v)
{
    reset();
    m_type = VT_CFUNCTION;
    m_data.pCFunction = v;
}

void Value::setValueArray(const ValueArray & v)
{
    reset();
    m_type = VT_VALUE_ARRAY;
    auto * va = new ValueArray();
    for (auto it = v.begin(); it != v.end(); ++it)
        va->push_back(*it);
    m_data.pValueArray = va;
}

void Value::setByCopy(const Value & other)
{
    reset();
    switch (other.m_type)
    {
    case VT_NIL: break;
    case VT_BOOL: setString(*other.m_data.pString); break;
    case VT_INT: setInt(other.m_data.vInt); break;
    case VT_FLOAT: setFloat(other.m_data.vFloat); break;
    case VT_STRING: setString(*other.m_data.pString); break;
    case VT_CFUNCTION: setCFunction(other.m_data.pCFunction); break;
    case VT_VALUE_ARRAY: setValueArray(*other.m_data.pValueArray); break;
    default: break;
    }
}

bool Value::add(const Value & other)
{
    switch (other.m_type)
    {
    case VT_BOOL:
        if (m_type == VT_STRING)
        {
            *m_data.pString += (other.m_data.vBool ? "true" : "false");
            return true;
        }
        else
            return false;

    case VT_INT:
        switch (m_type)
        {
        case VT_INT:
            m_data.vInt += other.m_data.vInt;
            return true;

        case VT_FLOAT:
            m_data.vFloat += static_cast<float>(other.m_data.vInt);
            return true;

        case VT_STRING:
            *m_data.pString += std::to_string(m_data.vInt);
            return true;

        default:
            return false;
        }

    case VT_FLOAT:
        switch (m_type)
        {
        case VT_FLOAT:
            m_data.vFloat += other.m_data.vFloat;
            return true;

        case VT_STRING:
            *m_data.pString += std::to_string(other.m_data.vFloat);
            return true;

        default:
            return false;
        }

    case VT_STRING:
    {
        const String & os = *other.m_data.pString;
        String * s = new String(toString() + *other.m_data.pString);
        reset();
        m_type = VT_STRING;
        m_data.pString = s;
        return true;
    }

    default:
        return false;
    }
}

bool Value::sub(const Value & other)
{
    // Not implemented yet
    return false;
}

bool Value::mul(const Value & other)
{
    // Not implemented yet
    return false;
}

bool Value::div(const Value & other)
{
    // Not implemented yet
    return false;
}

Value * Value::index(const Value & other)
{
    // Not implemented yet
    return false;
}

int Value::call(VM & vm)
{
    if (m_type == VT_CFUNCTION)
    {
        return m_data.pCFunction(vm);
    }
    else
    {
        return -1;
    }
}

String Value::toString()
{
    switch (m_type)
    {
    case VT_NIL:
        return "nil";

    case VT_BOOL:
        return m_data.vBool ? "true" : "false";

    case VT_INT:
        return std::to_string(m_data.vInt);

    case VT_FLOAT:
        return std::to_string(m_data.vFloat);

    case VT_STRING:
        return *m_data.pString;

    case VT_CFUNCTION:
        // TODO append hexa pointer value
        return "<CFunction>";

    case VT_VALUE_ARRAY:
        // TODO append hexa pointer value
        return "<ValueArray>";

    default:
        return "<error>";
    }
}

