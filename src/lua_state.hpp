/**
  ******************************************************************************
  * @file           : lua_state.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/14
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_LUA_STATE_HPP
#define LUA5_3_DECOMPILER_LUA_STATE_HPP

#include "lua_stack.hpp"

typedef int LuaType;

class LuaState {
private:
    LuaStack *_stack;
    Prototype proto;
    int pc;

    std::string boolToString(bool value) {
        return value ? "true" : "false";
    }

public:

    LuaState() {
        _stack = LuaStack::NewLuaStack(20);
    }

    void PrintStack() {
        for (int i = 1; i <= _stack->GetTop(); ++i) {
            auto t = Type(i);
            switch (t) {
                case LUA_TBOOLEAN:
                    printf("[%s]", boolToString(ToBoolean(i)).c_str());
                    break;
                case LUA_TNUMBER:
                    printf("[%f]", ToNumber(i));
                    break;
                case LUA_TSTRING:
                    printf("[%s]", ToString(i).c_str());
                    break;
                default:
                    printf("[%s]", TypeName(t).c_str());
            }
        }
        printf("\n");
    }

    /* basic stack manipulation */
    int GetTop();
    int AbsIndex(int idx);
    bool CheckStack(int n);
    void Pop(int n);
    void Copy(int fromIdx, int toIdx);
    void PushValue(int idx);
    void Replace(int idx);
    void Insert(int idx);
    void Remove(int idx);
    void Rotate(int idx, int n);
    void SetTop(int idx);

    /* access functions (stack -> c++) */
    std::string TypeName(LuaType tp);
    LuaType Type(int idx);
    bool IsNone(int idx);
    bool IsNil(int idx);
    bool IsNoneOrNil(int idx);
    bool IsBoolean(int idx);
    bool IsInteger(int idx);
    bool IsNumber(int idx);
    bool IsString(int idx);
    bool ToBoolean(int idx);
    int64 ToInteger(int idx);
    std::tuple<int64, bool> ToIntegerX(int idx);
    float64 ToNumber(int idx);
    std::tuple<float64 , bool> ToNumberX(int idx);
    std::string ToString(int idx);
    std::tuple<std::string, bool> ToStringX(int idx);

    /* push functions (c++ -> stack) */
    void PushNil();
    void PushBoolean(bool b);
    void PushInteger(int64 n);
    void PushNumber(float64 n);
    void PushString(std::string s);

};


#endif //LUA5_3_DECOMPILER_LUA_STATE_HPP
