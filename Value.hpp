#ifndef __HEADER_VALUE__
#define __HEADER_VALUE__

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cassert>

enum ValueType
{
    VT_NIL = 0,
    VT_BOOL = 1,
    VT_INT = 2,
    VT_FLOAT = 3,
    VT_STRING = 4,
    VT_CFUNCTION = 5,
    VT_VALUE_ARRAY = 6,

    VT_COUNT // Keep last
};

class Value;
class VM;

typedef std::string String;
typedef std::vector<Value> ValueArray;
typedef int(*CFunctionPtr)(VM&);

union ValueData
{
    bool vBool;
    int vInt;
    float vFloat;

    String * pString;
    CFunctionPtr pCFunction;
    ValueArray * pValueArray;
};

class Value
{
public:
    Value():
        m_type(VT_NIL)
    {}

    explicit Value(int v):
        m_type(VT_INT)
    {
        m_data.vInt = v;
    }

    explicit Value(float v) :
        m_type(VT_FLOAT)
    {
        m_data.vFloat = v;
    }

    explicit Value(CFunctionPtr v) :
        m_type(VT_CFUNCTION)
    {
        m_data.pCFunction = v;
    }

    explicit Value(const String & v) :
        m_type(VT_STRING)
    {
        m_data.pString = new String(v);
    }

    Value(const Value & other):
        m_type(VT_NIL)
    {
        setByCopy(other);
    }

    ~Value();

    void reset();

    inline ValueType getType() const { return m_type; }
    
    inline bool isNil() const { return m_type == VT_NIL; }

    inline bool getBool() const { assert(m_type == VT_BOOL); return m_data.vBool; }
    inline int getInt() const { assert(m_type == VT_INT); return m_data.vInt; }
    inline float getFloat() const { assert(m_type == VT_FLOAT); return m_data.vFloat; }
    inline const String & getString() const { assert(m_type == VT_STRING); return *m_data.pString; }
    inline CFunctionPtr getCFunction() const { assert(m_type == VT_CFUNCTION); return *m_data.pCFunction; }
    inline const ValueArray & getValueArray() { assert(m_type == VT_VALUE_ARRAY); return *m_data.pValueArray; }

    void setBool(bool v);
    void setInt(int v);
    void setFloat(float v);
    void setString(const String & v);
    void setCFunction(CFunctionPtr v);
    void setValueArray(const ValueArray & v);
    void setByCopy(const Value & other);

    bool add(const Value & other);
    bool sub(const Value & other);
    bool mul(const Value & other);
    bool div(const Value & other);
    Value * index(const Value & other);

    int call(VM & vm);

    String toString();

private:
    ValueType m_type;
    ValueData m_data;

};

#endif // __HEADER_VALUE__

