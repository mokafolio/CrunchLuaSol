#include <Stick/Test.hpp>

#define SOL_CHECK_ARGUMENTS 1
#include <CrunchLuaSol/CrunchLuaSol.hpp>

using namespace stick;
using namespace crunchLuaSol;

#include <vector>

static void printVec2(const Vec2 & _vec)
{
    printf("A VEC2 %f %f\n", _vec.x, _vec.y);
}

static stick::Error returnError()
{
    return stick::Error(stick::ec::InvalidOperation, "Could not do dis :(", STICK_FILE, STICK_LINE);
}

static stick::Maybe<int> emptyMaybe()
{
    return stick::Maybe<int>();
}

static stick::Maybe<int> filledMaybe()
{
    return 99;
}

struct A
{
    A(int _x) :
        x(_x)
    {}

    int x;
};

struct B : public A
{
    B(int _x, int _y) :
        A(_x),
        y(_y)
    {

    }

    int y;
};


// namespace sol
// {
//     template <class T>
//     struct is_container<stick::DynamicArray<T>> : std::true_type
//     {

//     };

//     template <class T>
//     struct container_traits<stick::DynamicArray<T>>
//     {
//         using iterator = typename stick::DynamicArray<T>::Iter;
//         using const_iterator = typename stick::DynamicArray<T>::ConstIter;
//         using value_type = typename stick::DynamicArray<T>::ValueType;
//         using difference_type = std::ptrdiff_t;
//         using reference = value_type&;
//         using const_reference = const value_type &;
//         using pointer = value_type*;
//         using const_pointer = const value_type *;

//         static iterator begin(lua_State * L, stick::DynamicArray<T> & _self)
//         {
//             return _self.begin();
//         }

//         static iterator end(lua_State * L, stick::DynamicArray<T> & _self)
//         {
//             return _self.end();
//         }

//         static std::ptrdiff_t index_adjustment(lua_State *, stick::DynamicArray<T> & _self)
//         {
//             return 0;
//         }
//     };
// }

const Suite spec[] =
{
    SUITE("Namespacing Tests")
    {
        sol::state lua;
        {
            lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);
            registerCrunch(lua, "crunch");

            lua.set_function("returnError", returnError);
            lua.set_function("emptyMaybe", emptyMaybe);
            lua.set_function("filledMaybe", filledMaybe);
            lua.set_function("printVec2", printVec2);
            lua.new_usertype<A>("A", "x", &A::x);
            lua.new_usertype<B>("B",
            "y", &B::y,
            sol::base_classes, sol::bases<A>(),
            "printY", [](B & _self) { printf("DA FOCKIN Y %i\n", _self.y); });

            // A * b = new B(33, 66);
            // lua["ns"] = stick::DynamicArray<Int32> {1, 2, 3, 4};
            // lua["ns"] = std::vector<Int32>{1, 2, 3, 4};
            // lua["b"] = b;

            auto shared = stick::makeShared<B>(99, 33);
            lua["test"] = std::move(shared);
            B * ab = lua["test"];
            printf("B %i %i\n", ab->x, ab->y);

            // lua["maybe"] = stick::Maybe<Float32>(1.5f);
            // lua["emptyVariant"] = stick::Variant<Float32, const char *, A*>();
            // lua["fullVariant"] = stick::Variant<Float32, const char *, A*>("test");
            // lua["testVar"] = "fooock";
            // stick::Maybe<Float32> m = lua.get<stick::Maybe<Float32>>("maybe");

            // // const char * str = lua["testVar"];
            // // stick::Variant<Float32, A*, const char *> variant = lua["b"];
            // auto v = lua.get<stick::Variant<Float32, const char *, A*>>("fullVariant");


            // EXPECT(m);
            // EXPECT(*m == 1.5f);
            // EXPECT(v.is<const char*>());
            // printf("%s\n", v.get<const char*>());
            // EXPECT(std::strcmp(v.get<const char*>(), "test") == 0);

            // lua["someError"] = stick::Error(stick::ec::InvalidOperation, "Could not do dis :(", STICK_FILE, STICK_LINE);
            // // lua.script("print(b, b.x, b.y, ns) printVec2(crunch.Vec2(0.5, 0.3))"
            // //            " print('WOOT', returnError().file, someError.message)"
            // //            " print(emptyMaybe(), filledMaybe())");

            // // lua.script("print(ns, ns[3], #ns) for i=1,#ns,1 do print(ns[i]) end for k,v in pairs(ns) do print(k, v) end");
            lua.script("test:printY()");

            // delete b;
        }
    }
};

int main(int _argc, const char * _args[])
{
    return runTests(spec, _argc, _args);
}
