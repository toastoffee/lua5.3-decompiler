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

#include "../state/lua_stack.hpp"
#include "../vm/instruction_types.hpp"
#include "../state/lua_table.hpp"


typedef int LuaType;
typedef int ArithOp;
typedef int CompareOp;


class LuaState {
public:
    LuaStack *_stack;

    std::string boolToString(bool value) {
        return value ? "true" : "false";
    }

public:

    LuaState(int _stackSize) {
        _stack = LuaStack::NewLuaStack(_stackSize);
    }

    void PushLuaStack(LuaStack* stack) {
        stack->_prev = _stack;
        _stack = stack;
    }

    void PopLuaStack() {
        LuaStack* stack = _stack;
        _stack = stack->_prev;
        stack->_prev = nullptr;
    }

    void PrintStack() {
        for (int i = 1; i <= _stack->GetTop(); ++i) {
            auto t = Type(i);
            switch (t) {
                case LUA_TBOOLEAN:
                    printf("[%s]", boolToString(ToBoolean(i)).c_str());
                    break;
                case LUA_TNUMBER:
                    printf("[%g]", ToNumber(i));
                    break;
                case LUA_TSTRING:
                    printf("[\"%s\"]", ToString(i).c_str());
                    break;
                default:
                    printf("[%s]", TypeName(t).c_str());
            }
        }
        printf("\n");
    }

    void PrintTypesInverse() {
        for (int i = -1; i >= -_stack->GetTop(); --i) {
            auto t = TypeName(Type(i));
            printf("[%d:%s]", i, t.c_str());
        }
        printf("---top:%d\n", _stack->GetTop());
    }

    /* outer interface */
    int Load(byte chunk[], std::string chunkName, std::string mode);
    void Call(int nArgs, int nResults);
    void CallLuaClosure(int nArgs, int nResults, Closure* c);
    void runLuaClosure();

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

    void Arith(ArithOp op);
    bool Compare(int idx1, int idx2, CompareOp op);
    void Len(int idx);
    void Concat(int n);


    /* lua vm functions */
    int PC();                   // get current pc
    void AddPC(int n);          // modify pc (to realize JMP)
    Instruction Fetch();        // fetch current instruction, make pc point to next instruction
    void GetConst(int idx);     // push current const to stack
    void GetRK(int rk);         // push current const or stack value to stack

private:
    LuaType getTable(LuaValue t, LuaValue k);
    void setTable(LuaValue t, LuaValue k, LuaValue v);
public:
    /* lua table methods */
    /* get functions */
    void NewTable();
    void CreateTable();

    LuaType GetTable(int idx);
    LuaType GetField(int idx, std::string k);
    LuaType GetI(int idx, int64 i);

    /* get functions */
    void SetTable(int idx);
    void SetField(int idx, std::string k);
    void SetI(int idx, int64 i);

    /* closure extension */
    int RegisterCount();
    void LoadVararg(int n);
    void LoadProto(int idx);
};


#endif //LUA5_3_DECOMPILER_LUA_STATE_HPP
