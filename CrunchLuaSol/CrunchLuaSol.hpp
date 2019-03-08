#ifndef CRUNCHLUASOL_CRUNCHLUASOL_HPP
#define CRUNCHLUASOL_CRUNCHLUASOL_HPP

#include <StickLuaSol/StickLuaSol.hpp>

#include <Crunch/Circle.hpp>
#include <Crunch/Colors.hpp>
#include <Crunch/CommonFunc.hpp>
#include <Crunch/GeometricFunc.hpp>
#include <Crunch/Line.hpp>
#include <Crunch/LineSegment.hpp>
#include <Crunch/Matrix2.hpp>
#include <Crunch/Matrix3.hpp>
#include <Crunch/Matrix32.hpp>
#include <Crunch/Matrix4.hpp>
#include <Crunch/MatrixFunc.hpp>
#include <Crunch/PerlinNoise.hpp>
#include <Crunch/Quaternion.hpp>
#include <Crunch/Randomizer.hpp>
#include <Crunch/Rectangle.hpp>
#include <Crunch/StringConversion.hpp>
#include <Crunch/Tween.hpp>
#include <Crunch/Vector2.hpp>
#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>

namespace crunchLuaSol
{
STICK_API void registerCrunch(sol::state_view _lua, const stick::String & _namespace = "");
STICK_API void registerCrunch(sol::state_view _lua, sol::table _tbl);

using Float = stick::Float32;
using Circle = crunch::Circle<Float>;
using Vec2 = crunch::Vector2<Float>;
using Vec3 = crunch::Vector3<Float>;
using Vec4 = crunch::Vector4<Float>;
using Mat2 = crunch::Matrix2<Float>;
using Mat32 = crunch::Matrix32<Float>;
using Mat3 = crunch::Matrix3<Float>;
using Mat4 = crunch::Matrix4<Float>;
using Quat = crunch::Quaternion<Float>;
using ColorRGB = crunch::ColorRGBT<Float>;
using ColorRGBA = crunch::ColorRGBAT<Float>;
using ColorHSB = crunch::ColorHSBT<Float>;
using ColorHSBA = crunch::ColorHSBAT<Float>;
using Rect = crunch::Rectangle<Float>;
using Line2 = crunch::Line<Vec2>;
using Line3 = crunch::Line<Vec3>;
using LineSegment2 = crunch::LineSegment<Vec2>;

namespace detail
{
static inline crunch::PerlinNoise & luaNoiseGenerator()
{
    static crunch::PerlinNoise s_noise;
    return s_noise;
}

static inline crunch::Randomizer & luaRandomNumberGenerator()
{
    static crunch::Randomizer s_luaRandomNumbers;
    return s_luaRandomNumbers;
}

template <class Tween>
void registerTweenClass(sol::table _tbl, const char * _name)
{
    using VT = typename Tween::ValueType;

    _tbl.new_usertype<Tween>(_name,
                             sol::call_constructor,
                             sol::constructors<Tween(), Tween(const VT &, const VT &, stick::Float64)>(),
                             "update",
                             &Tween::update,
                             "origin",
                             &Tween::origin,
                             "destination",
                             &Tween::destination,
                             "current",
                             &Tween::current,
                             "timeElapsed",
                             &Tween::timeElapsed,
                             "duration",
                             &Tween::duration,
                             "isFinished",
                             &Tween::isFinished);
}

} // namespace detail

STICK_API void registerCrunch(sol::state_view _lua, const stick::String & _namespace)
{
    registerCrunch(_lua, stickLuaSol::ensureNamespaceTable(_lua, _lua.globals(), _namespace));
}

STICK_API void registerCrunch(sol::state_view _lua, sol::table _tbl)
{
    using namespace crunch;
    using namespace stick;

    sol::table tbl = _tbl;

    tbl.new_usertype<Vec2>(
        "Vec2",
        sol::call_constructor,
        sol::constructors<Vec2(), Vec2(Float, Float), Vec2(Float), Vec2(const Vec2 &)>(),
        "x",
        &Vec2::x,
        "y",
        &Vec2::y,
        sol::meta_function::equal_to,
        &Vec2::operator==,
        sol::meta_function::addition,
        sol::overload(((Vec2(Vec2::*)(const Vec2 &) const) & Vec2::operator+),
                      ((Vec2(Vec2::*)(Float) const) & Vec2::operator+)),
        sol::meta_function::subtraction,
        sol::overload(((Vec2(Vec2::*)(const Vec2 &) const) & Vec2::operator-),
                      ((Vec2(Vec2::*)(Float) const) & Vec2::operator-)),
        sol::meta_function::multiplication,
        sol::overload(((Vec2(Vec2::*)(const Vec2 &) const) & Vec2::operator*),
                      ((Vec2(Vec2::*)(Float) const) & Vec2::operator*)),
        sol::meta_function::division,
        sol::overload(((Vec2(Vec2::*)(const Vec2 &) const) & Vec2::operator/),
                      ((Vec2(Vec2::*)(Float) const) & Vec2::operator/)));

    tbl.new_usertype<Vec3>(
        "Vec3",
        sol::call_constructor,
        sol::constructors<Vec3(), Vec3(Float, Float, Float), Vec3(Float), Vec3(const Vec3 &)>(),
        "x",
        &Vec3::x,
        "y",
        &Vec3::y,
        "z",
        &Vec3::z,
        sol::meta_function::equal_to,
        &Vec3::operator==,
        sol::meta_function::addition,
        sol::overload(((Vec3(Vec3::*)(const Vec3 &) const) & Vec3::operator+),
                      ((Vec3(Vec3::*)(Float) const) & Vec3::operator+)),
        sol::meta_function::subtraction,
        sol::overload(((Vec3(Vec3::*)(const Vec3 &) const) & Vec3::operator-),
                      ((Vec3(Vec3::*)(Float) const) & Vec3::operator-)),
        sol::meta_function::multiplication,
        sol::overload(((Vec3(Vec3::*)(const Vec3 &) const) & Vec3::operator*),
                      ((Vec3(Vec3::*)(Float) const) & Vec3::operator*)),
        sol::meta_function::division,
        sol::overload(((Vec3(Vec3::*)(const Vec3 &) const) & Vec3::operator/),
                      ((Vec3(Vec3::*)(Float) const) & Vec3::operator/)));

    tbl.new_usertype<Vec4>("Vec4",
                           sol::call_constructor,
                           sol::constructors<Vec4(),
                                             Vec4(Float, Float, Float, Float),
                                             Vec4(Float),
                                             Vec4(const Vec4 &)>(),
                           "x",
                           &Vec4::x,
                           "y",
                           &Vec4::y,
                           "z",
                           &Vec4::z,
                           "w",
                           &Vec4::z,
                           sol::meta_function::equal_to,
                           &Vec4::operator==,
                           sol::meta_function::addition,
                           sol::overload(((Vec4(Vec4::*)(const Vec4 &) const) & Vec4::operator+),
                                         ((Vec4(Vec4::*)(Float) const) & Vec4::operator+)),
                           sol::meta_function::subtraction,
                           sol::overload(((Vec4(Vec4::*)(const Vec4 &) const) & Vec4::operator-),
                                         ((Vec4(Vec4::*)(Float) const) & Vec4::operator-)),
                           sol::meta_function::multiplication,
                           sol::overload(((Vec4(Vec4::*)(const Vec4 &) const) & Vec4::operator*),
                                         ((Vec4(Vec4::*)(Float) const) & Vec4::operator*)),
                           sol::meta_function::division,
                           sol::overload(((Vec4(Vec4::*)(const Vec4 &) const) & Vec4::operator/),
                                         ((Vec4(Vec4::*)(Float) const) & Vec4::operator/)));

    tbl.set_function("abs1", (Float(*)(const Float &))crunch::abs);
    tbl.set_function("abs2", (Vec2(*)(const Vec2 &))crunch::abs);
    tbl.set_function("abs3", (Vec3(*)(const Vec3 &))crunch::abs);
    tbl.set_function("abs4", (Vec4(*)(const Vec4 &))crunch::abs);

    tbl.set_function("floor1", (Float(*)(const Float &))crunch::floor);
    tbl.set_function("floor2", (Vec2(*)(const Vec2 &))crunch::floor);
    tbl.set_function("floor3", (Vec3(*)(const Vec3 &))crunch::floor);
    tbl.set_function("floor4", (Vec4(*)(const Vec4 &))crunch::floor);

    tbl.set_function("ceil1", (Float(*)(const Float &))crunch::ceil);
    tbl.set_function("ceil2", (Vec2(*)(const Vec2 &))crunch::ceil);
    tbl.set_function("ceil3", (Vec3(*)(const Vec3 &))crunch::ceil);
    tbl.set_function("ceil4", (Vec4(*)(const Vec4 &))crunch::ceil);

    tbl.set_function("fract1", (Float(*)(const Float &))crunch::fract);
    tbl.set_function("fract2", (Vec2(*)(const Vec2 &))crunch::fract);
    tbl.set_function("fract3", (Vec3(*)(const Vec3 &))crunch::fract);
    tbl.set_function("fract4", (Vec4(*)(const Vec4 &))crunch::fract);

    tbl.set_function("min1", (Float(*)(const Float &, const Float &))crunch::min);
    tbl.set_function("min2", (Vec2(*)(const Vec2 &, const Vec2 &))crunch::min);
    tbl.set_function("min3", (Vec3(*)(const Vec3 &, const Vec3 &))crunch::min);
    tbl.set_function("min4", (Vec4(*)(const Vec4 &, const Vec4 &))crunch::min);

    tbl.set_function("max1", (Float(*)(const Float &, const Float &))crunch::max);
    tbl.set_function("max2", (Vec2(*)(const Vec2 &, const Vec2 &))crunch::max);
    tbl.set_function("max3", (Vec3(*)(const Vec3 &, const Vec3 &))crunch::max);
    tbl.set_function("max4", (Vec4(*)(const Vec4 &, const Vec4 &))crunch::max);

    tbl.set_function("clamp1",
                     (Float(*)(const Float &, const Float &, const Float &))crunch::clamp);
    tbl.set_function("clamp2", (Vec2(*)(const Vec2 &, const Vec2 &, const Vec2 &))crunch::clamp);
    tbl.set_function("clamp3", (Vec3(*)(const Vec3 &, const Vec3 &, const Vec3 &))crunch::clamp);
    tbl.set_function("clamp4", (Vec4(*)(const Vec4 &, const Vec4 &, const Vec4 &))crunch::clamp);

    tbl.set_function("cross2", (Float(*)(const Vec2 &, const Vec2 &))crunch::cross);
    tbl.set_function("cross3", (Vec3(*)(const Vec3 &, const Vec3 &))crunch::cross);
    tbl.set_function("cross",
                     sol::overload((Float(*)(const Vec2 &, const Vec2 &))crunch::cross,
                                   (Vec3(*)(const Vec3 &, const Vec3 &))crunch::cross));

    tbl.set_function("normalize2", (Vec2(*)(const Vec2 &))crunch::normalize);
    tbl.set_function("normalize3", (Vec3(*)(const Vec3 &))crunch::normalize);
    tbl.set_function("normalize",
                     sol::overload((Vec2(*)(const Vec2 &))crunch::normalize,
                                   (Vec3(*)(const Vec3 &))crunch::normalize));

    tbl.set_function("rotate2", ((Vec2(*)(const Vec2 &, Float))crunch::rotate));
    tbl.set_function("rotateAround2", ((Vec2(*)(const Vec2 &, const Vec2 &, Float))crunch::rotate));
    tbl.set_function("rotate",
                     sol::overload(((Vec2(*)(const Vec2 &, Float))crunch::rotate),
                                   ((Vec2(*)(const Vec2 &, const Vec2 &, Float))crunch::rotate)));

    tbl.set_function("dot2", (Float(*)(const Vec2 &, const Vec2 &))crunch::dot);
    tbl.set_function("dot3", (Float(*)(const Vec3 &, const Vec3 &))crunch::dot);
    tbl.set_function("dot",
                     sol::overload((Float(*)(const Vec2 &, const Vec2 &))crunch::dot,
                                   (Float(*)(const Vec3 &, const Vec3 &))crunch::dot));

    tbl.set_function("length2", (Float(*)(const Vec2 &))crunch::length);
    tbl.set_function("length3", (Float(*)(const Vec3 &))crunch::length);
    tbl.set_function("length",
                     sol::overload((Float(*)(const Vec2 &))crunch::length,
                                   (Float(*)(const Vec3 &))crunch::length));

    tbl.set_function("distance2", (Float(*)(const Vec2 &, const Vec2 &))crunch::distance);
    tbl.set_function("distance3", (Float(*)(const Vec3 &, const Vec3 &))crunch::distance);
    tbl.set_function("distance",
                     sol::overload((Float(*)(const Vec2 &, const Vec2 &))crunch::distance,
                                   (Float(*)(const Vec3 &, const Vec3 &))crunch::distance));

    tbl.set_function("distanceSquared2",
                     (Float(*)(const Vec2 &, const Vec2 &))crunch::distanceSquared);
    tbl.set_function("distanceSquared3",
                     (Float(*)(const Vec3 &, const Vec3 &))crunch::distanceSquared);
    tbl.set_function("distanceSquared",
                     sol::overload((Float(*)(const Vec2 &, const Vec2 &))crunch::distanceSquared,
                                   (Float(*)(const Vec3 &, const Vec3 &))crunch::distanceSquared));

    tbl.new_usertype<Mat2>(
        "Mat2", sol::call_constructor,
        sol::constructors<Mat2(), Mat2(const Vec2 &, const Vec2 &),
                          Mat2(Float, Float, Float, Float), Mat2(Float), Vec2(const Mat2 &)>(),
        "identity", &Mat2::identity, "zero", &Mat2::zero, "rotation", &Mat2::rotation, "scaling",
        sol::overload((Mat2(*)(Float, Float)) & Mat2::scaling,
                      (Mat2(*)(const Vec2 &)) & Mat2::scaling, (Mat2(*)(Float)) & Mat2::scaling),
        sol::meta_function::equal_to, &Mat2::operator==,
        sol::meta_function::addition, & Mat2::operator+,
        sol::meta_function::subtraction,(Mat2 (Mat2::*)(const Mat2 &) const) & Mat2::operator-,
        sol::meta_function::multiplication,
        sol::overload(((Mat2(Mat2::*)(const Mat2 &) const) & Mat2::operator*),
                      ((Mat2(Mat2::*)(Float) const) & Mat2::operator*),
                      ((Vec2(Mat2::*)(const Vec2 &) const) & Mat2::operator*)),
        "element", (const Float & (Mat2::*)(UInt32, UInt32) const) & Mat2::element, "scale",
        sol::overload((Mat2 & (Mat2::*)(Float)) & Mat2::scale,
                      (Mat2 & (Mat2::*)(Float, Float)) & Mat2::scale,
                      (Mat2 & (Mat2::*)(const Vec2 &)) & Mat2::scale),
        "rotate", &Mat2::rotate);

    tbl.new_usertype<Mat32>(
        "Mat32", sol::call_constructor,
        sol::constructors<Mat32(), Mat32(const Vec2 &, const Vec2 &, const Vec2 &),
                          Mat32(Float, Float, Float, Float, Float, Float), Mat32(Float),
                          Mat32(const Mat32 &)>(),
        "identity", &Mat32::identity, "zero", &Mat32::zero, "translation",
        sol::overload((Mat32(*)(Float, Float)) & Mat32::translation,
                      (Mat32(*)(const Vec2 &)) & Mat32::translation),
        "rotation", &Mat32::rotation, "scaling",
        sol::overload((Mat32(*)(Float, Float)) & Mat32::scaling,
                      (Mat32(*)(const Vec2 &)) & Mat32::scaling,
                      (Mat32(*)(Float)) & Mat32::scaling),
        "skewMatrix",
        sol::overload((Mat32(*)(Float, Float)) & Mat32::skewMatrix,
                      (Mat32(*)(const Vec2 &)) & Mat32::skewMatrix),
        sol::meta_function::equal_to, &Mat32::operator==,
        sol::meta_function::addition, & Mat32::operator+,
        sol::meta_function::subtraction,(Mat32 (Mat32::*)(const Mat32 &) const) & Mat32::operator-,
        sol::meta_function::multiplication,
        sol::overload(((Mat32(Mat32::*)(const Mat32 &) const) & Mat32::operator*),
                      ((Mat32(Mat32::*)(Float) const) & Mat32::operator*),
                      ((Vec2(Mat32::*)(const Vec2 &) const) & Mat32::operator*)),
        "element", (const Float & (Mat32::*)(UInt32, UInt32) const) & Mat32::element, "scale",
        sol::overload((Mat32 & (Mat32::*)(Float)) & Mat32::scale,
                      (Mat32 & (Mat32::*)(Float, Float)) & Mat32::scale,
                      (Mat32 & (Mat32::*)(const Vec2 &)) & Mat32::scale),
        "skew",
        sol::overload((Mat32 & (Mat32::*)(Float, Float)) & Mat32::skew,
                      (Mat32 & (Mat32::*)(const Vec2 &)) & Mat32::skew),
        "rotate", &Mat32::rotate, "translate",
        sol::overload((Mat32 & (Mat32::*)(Float, Float)) & Mat32::translate,
                      (Mat32 & (Mat32::*)(const Vec2 &)) & Mat32::translate));

    tbl.new_usertype<Mat3>(
        "Mat3", sol::call_constructor,
        sol::constructors<Mat3(), Mat3(const Vec3 &, const Vec3 &, const Vec3 &),
                          Mat3(Float, Float, Float, Float, Float, Float, Float, Float, Float),
                          Mat3(Float), Mat3(const Mat3 &)>(),
        "identity", &Mat3::identity, "zero", &Mat3::zero, "translation2D",
        sol::overload((Mat3(*)(Float, Float)) & Mat3::translation2D,
                      (Mat3(*)(const Vec2 &)) & Mat3::translation2D),
        "rotation",
        sol::overload((Mat3(*)(Float, const Vec3 &)) & Mat3::rotation,
                      (Mat3(*)(Float, Float, Float)) & Mat3::rotation,
                      (Mat3(*)(const Vec3 &)) & Mat3::rotation),
        "rotation2D", &Mat3::rotation2D, "scaling",
        sol::overload((Mat3(*)(Float, Float, Float)) & Mat3::scaling,
                      (Mat3(*)(const Vec3 &)) & Mat3::scaling, (Mat3(*)(Float)) & Mat3::scaling),
        "scaling2D",
        sol::overload((Mat3(*)(Float, Float)) & Mat3::scaling2D,
                      (Mat3(*)(const Vec2 &)) & Mat3::scaling2D,
                      (Mat3(*)(Float)) & Mat3::scaling2D),
        "skewMatrix2D",
        sol::overload((Mat3(*)(Float, Float)) & Mat3::skewMatrix2D,
                      (Mat3(*)(const Vec2 &)) & Mat3::skewMatrix2D),
        sol::meta_function::equal_to, &Mat3::operator==,
        sol::meta_function::addition, & Mat3::operator+,
        sol::meta_function::subtraction,(Mat3 (Mat3::*)(const Mat3 &) const) & Mat3::operator-,
        sol::meta_function::multiplication,
        sol::overload(((Mat3(Mat3::*)(const Mat3 &) const) & Mat3::operator*),
                      ((Mat3(Mat3::*)(Float) const) & Mat3::operator*),
                      ((Vec2(Mat3::*)(const Vec2 &) const) & Mat3::operator*),
                      ((Vec3(Mat3::*)(const Vec3 &) const) & Mat3::operator*)),
        "element", (const Float & (Mat3::*)(UInt32, UInt32) const) & Mat3::element, "scale",
        sol::overload((Mat3 & (Mat3::*)(Float)) & Mat3::scale,
                      (Mat3 & (Mat3::*)(Float, Float, Float)) & Mat3::scale,
                      (Mat3 & (Mat3::*)(const Vec3 &)) & Mat3::scale),
        "scale2D",
        sol::overload((Mat3 & (Mat3::*)(Float)) & Mat3::scale2D,
                      (Mat3 & (Mat3::*)(Float, Float)) & Mat3::scale2D,
                      (Mat3 & (Mat3::*)(const Vec2 &)) & Mat3::scale2D),
        "skew2D",
        sol::overload((Mat3 & (Mat3::*)(Float, Float)) & Mat3::skew2D,
                      (Mat3 & (Mat3::*)(const Vec2 &)) & Mat3::skew2D),
        "translate2D",
        sol::overload((Mat3 & (Mat3::*)(Float, Float)) & Mat3::translate2D,
                      (Mat3 & (Mat3::*)(const Vec2 &)) & Mat3::translate2D),
        "rotate",
        sol::overload((Mat3 & (Mat3::*)(Float, const Vec3 &)) & Mat3::rotate,
                      (Mat3 & (Mat3::*)(Float, Float, Float)) & Mat3::rotate,
                      (Mat3 & (Mat3::*)(const Vec3 &)) & Mat3::rotate),
        "rotate2D", &Mat3::rotate2D);

    tbl.new_usertype<Mat4>(
        "Mat4", sol::call_constructor,
        sol::constructors<Mat4(), Mat4(const Vec4 &, const Vec4 &, const Vec4 &, const Vec4 &),
                          Mat4(Float, Float, Float, Float, Float, Float, Float, Float, Float, Float,
                               Float, Float, Float, Float, Float, Float),
                          Mat4(Float), Mat4(const Mat4 &)>(),
        "identity", &Mat4::identity, "zero", &Mat4::zero, "translation",
        sol::overload((Mat4(*)(Float, Float, Float)) & Mat4::translation,
                      (Mat4(*)(const Vec3 &)) & Mat4::translation),
        "rotation",
        sol::overload((Mat4(*)(Float, const Vec3 &)) & Mat4::rotation,
                      (Mat4(*)(Float, Float, Float)) & Mat4::rotation,
                      (Mat4(*)(const Vec3 &)) & Mat4::rotation),
        "scaling",
        sol::overload((Mat4(*)(Float, Float, Float)) & Mat4::scaling,
                      (Mat4(*)(const Vec3 &)) & Mat4::scaling, (Mat4(*)(Float)) & Mat4::scaling),
        "ortho", &Mat4::ortho, "frustum", &Mat4::frustum, "perspective", &Mat4::perspective,
        sol::meta_function::equal_to, &Mat4::operator==,
        sol::meta_function::addition, & Mat4::operator+,
        sol::meta_function::subtraction,(Mat4 (Mat4::*)(const Mat4 &) const) & Mat4::operator-,
        sol::meta_function::multiplication,
        sol::overload(((Mat4(Mat4::*)(const Mat4 &) const) & Mat4::operator*),
                      ((Mat4(Mat4::*)(Float) const) & Mat4::operator*),
                      ((Vec4(Mat4::*)(const Vec4 &) const) & Mat4::operator*),
                      ((Vec3(Mat4::*)(const Vec3 &) const) & Mat4::operator*)),
        "element", (const Float & (Mat4::*)(UInt32, UInt32) const) & Mat4::element, "scale",
        sol::overload((Mat4 & (Mat4::*)(Float)) & Mat4::scale,
                      (Mat4 & (Mat4::*)(Float, Float, Float)) & Mat4::scale,
                      (Mat4 & (Mat4::*)(const Vec3 &)) & Mat4::scale),
        "translate",
        sol::overload((Mat4 & (Mat4::*)(Float, Float, Float)) & Mat4::translate,
                      (Mat4 & (Mat4::*)(const Vec3 &)) & Mat4::translate),
        "rotate",
        sol::overload((Mat4 & (Mat4::*)(Float, const Vec3 &)) & Mat4::rotate,
                      (Mat4 & (Mat4::*)(Float, Float, Float)) & Mat4::rotate,
                      (Mat4 & (Mat4::*)(const Vec3 &)) & Mat4::rotate));

    tbl.set_function("transpose2", (Mat2(*)(const Mat2 &))crunch::transpose);
    tbl.set_function("transpose3", (Mat3(*)(const Mat3 &))crunch::transpose);
    tbl.set_function("transpose4", (Mat4(*)(const Mat4 &))crunch::transpose);
    tbl.set_function("transpose",
                     sol::overload((Mat2(*)(const Mat2 &))crunch::transpose,
                                   (Mat3(*)(const Mat3 &))crunch::transpose,
                                   (Mat4(*)(const Mat4 &))crunch::transpose));

    tbl.set_function("determinant2", (Float(*)(const Mat2 &))crunch::determinant);
    tbl.set_function("determinant3", (Float(*)(const Mat3 &))crunch::determinant);
    tbl.set_function("determinant4", (Float(*)(const Mat4 &))crunch::determinant);
    tbl.set_function("determinant",
                     sol::overload((Float(*)(const Mat2 &))crunch::determinant,
                                   (Float(*)(const Mat3 &))crunch::determinant,
                                   (Float(*)(const Mat4 &))crunch::determinant));

    tbl.set_function("adjoint2", (Mat2(*)(const Mat2 &))crunch::adjoint);
    tbl.set_function("adjoint3", (Mat3(*)(const Mat3 &))crunch::adjoint);
    tbl.set_function("adjoint4", (Mat4(*)(const Mat4 &))crunch::adjoint);
    tbl.set_function("adjoint",
                     sol::overload((Mat2(*)(const Mat2 &))crunch::adjoint,
                                   (Mat3f(*)(const Mat3 &))crunch::adjoint,
                                   (Mat4(*)(const Mat4 &))crunch::adjoint));

    tbl.set_function("inverse2", (Mat2(*)(const Mat2 &))crunch::inverse);
    tbl.set_function("inverse3", (Mat3(*)(const Mat3 &))crunch::inverse);
    tbl.set_function("inverse32", (Mat32(*)(const Mat32 &))crunch::inverse);
    tbl.set_function("inverse4", (Mat4(*)(const Mat4 &))crunch::inverse);
    tbl.set_function("inverse",
                     sol::overload((Mat2(*)(const Mat2 &))crunch::inverse,
                                   (Mat3(*)(const Mat3 &))crunch::inverse,
                                   (Mat32(*)(const Mat32 &))crunch::inverse,
                                   (Mat4(*)(const Mat4 &))crunch::inverse));

    tbl.new_usertype<ColorRGB>(
        "ColorRGB",
        sol::call_constructor,
        sol::constructors<ColorRGB(),
                          ColorRGB(Float, Float, Float),
                          ColorRGB(Float),
                          ColorRGB(const ColorRGB &)>(),
        "r",
        &ColorRGB::r,
        "g",
        &ColorRGB::g,
        "b",
        &ColorRGB::b,
        sol::meta_function::equal_to,
        &ColorRGB::operator==,
        sol::meta_function::addition,
        sol::overload(((ColorRGB(ColorRGB::*)(const ColorRGB &) const) & ColorRGB::operator+),
                      ((ColorRGB(ColorRGB::*)(Float) const) & ColorRGB::operator+)),
        sol::meta_function::subtraction,
        sol::overload(((ColorRGB(ColorRGB::*)(const ColorRGB &) const) & ColorRGB::operator-),
                      ((ColorRGB(ColorRGB::*)(Float) const) & ColorRGB::operator-)),
        sol::meta_function::multiplication,
        sol::overload(((ColorRGB(ColorRGB::*)(const ColorRGB &) const) & ColorRGB::operator*),
                      ((ColorRGB(ColorRGB::*)(Float) const) & ColorRGB::operator*)),
        sol::meta_function::division,
        sol::overload(((ColorRGB(ColorRGB::*)(const ColorRGB &) const) & ColorRGB::operator/),
                      ((ColorRGB(ColorRGB::*)(Float) const) & ColorRGB::operator/)));

    tbl.new_usertype<ColorRGBA>(
        "ColorRGBA",
        sol::call_constructor,
        sol::constructors<ColorRGBA(),
                          ColorRGBA(Float, Float, Float, Float),
                          ColorRGBA(const ColorRGBA &)>(),
        "r",
        &ColorRGBA::r,
        "g",
        &ColorRGBA::g,
        "b",
        &ColorRGBA::b,
        "a",
        &ColorRGBA::a,
        sol::meta_function::equal_to,
        &ColorRGBA::operator==,
        sol::meta_function::addition,
        sol::overload(((ColorRGBA(ColorRGBA::*)(const ColorRGBA &) const) & ColorRGBA::operator+),
                      ((ColorRGBA(ColorRGBA::*)(Float) const) & ColorRGBA::operator+)),
        sol::meta_function::subtraction,
        sol::overload(((ColorRGBA(ColorRGBA::*)(const ColorRGBA &) const) & ColorRGBA::operator-),
                      ((ColorRGBA(ColorRGBA::*)(Float) const) & ColorRGBA::operator-)),
        sol::meta_function::multiplication,
        sol::overload(((ColorRGBA(ColorRGBA::*)(const ColorRGBA &) const) & ColorRGBA::operator*),
                      ((ColorRGBA(ColorRGBA::*)(Float) const) & ColorRGBA::operator*)),
        sol::meta_function::division,
        sol::overload(((ColorRGBA(ColorRGBA::*)(const ColorRGBA &) const) & ColorRGBA::operator/),
                      ((ColorRGBA(ColorRGBA::*)(Float) const) & ColorRGBA::operator/)));

    tbl.new_usertype<ColorHSB>(
        "ColorHSB",
        sol::call_constructor,
        sol::constructors<ColorHSB(),
                          ColorHSB(Float, Float, Float),
                          ColorHSB(Float),
                          ColorHSB(const ColorHSB &)>(),
        "h",
        &ColorHSB::h,
        "s",
        &ColorHSB::s,
        "b",
        &ColorHSB::b,
        sol::meta_function::equal_to,
        &ColorHSB::operator==,
        sol::meta_function::addition,
        sol::overload(((ColorHSB(ColorHSB::*)(const ColorHSB &) const) & ColorHSB::operator+),
                      ((ColorHSB(ColorHSB::*)(Float) const) & ColorHSB::operator+)),
        sol::meta_function::subtraction,
        sol::overload(((ColorHSB(ColorHSB::*)(const ColorHSB &) const) & ColorHSB::operator-),
                      ((ColorHSB(ColorHSB::*)(Float) const) & ColorHSB::operator-)),
        sol::meta_function::multiplication,
        sol::overload(((ColorHSB(ColorHSB::*)(const ColorHSB &) const) & ColorHSB::operator*),
                      ((ColorHSB(ColorHSB::*)(Float) const) & ColorHSB::operator*)),
        sol::meta_function::division,
        sol::overload(((ColorHSB(ColorHSB::*)(const ColorHSB &) const) & ColorHSB::operator/),
                      ((ColorHSB(ColorHSB::*)(Float) const) & ColorHSB::operator/)));

    tbl.new_usertype<ColorHSBA>(
        "ColorHSBA",
        sol::call_constructor,
        sol::constructors<ColorHSBA(),
                          ColorHSBA(Float, Float, Float, Float),
                          ColorHSBA(const ColorHSBA &)>(),
        "h",
        &ColorHSBA::h,
        "s",
        &ColorHSBA::s,
        "b",
        &ColorHSBA::b,
        "a",
        &ColorHSBA::a,
        sol::meta_function::equal_to,
        &ColorHSBA::operator==,
        sol::meta_function::addition,
        sol::overload(((ColorHSBA(ColorHSBA::*)(const ColorHSBA &) const) & ColorHSBA::operator+),
                      ((ColorHSBA(ColorHSBA::*)(Float) const) & ColorHSBA::operator+)),
        sol::meta_function::subtraction,
        sol::overload(((ColorHSBA(ColorHSBA::*)(const ColorHSBA &) const) & ColorHSBA::operator-),
                      ((ColorHSBA(ColorHSBA::*)(Float) const) & ColorHSBA::operator-)),
        sol::meta_function::multiplication,
        sol::overload(((ColorHSBA(ColorHSBA::*)(const ColorHSBA &) const) & ColorHSBA::operator*),
                      ((ColorHSBA(ColorHSBA::*)(Float) const) & ColorHSBA::operator*)),
        sol::meta_function::division,
        sol::overload(((ColorHSBA(ColorHSBA::*)(const ColorHSBA &) const) & ColorHSBA::operator/),
                      ((ColorHSBA(ColorHSBA::*)(Float) const) & ColorHSBA::operator/)));

    tbl.set_function("toRGB",
                     sol::overload((ColorRGB(*)(const ColorRGBA &)) & toRGB,
                                   (ColorRGB(*)(const ColorHSBA &)) & toRGB,
                                   (ColorRGB(*)(const ColorHSB &)) & toRGB));

    tbl.set_function("toRGBA",
                     sol::overload((ColorRGBA(*)(const ColorRGB &)) & toRGBA,
                                   (ColorRGBA(*)(const ColorHSBA &)) & toRGBA,
                                   (ColorRGBA(*)(const ColorHSB &)) & toRGBA));

    tbl.set_function("toHSB",
                     sol::overload((ColorHSB(*)(const ColorRGBA &)) & toHSB,
                                   (ColorHSB(*)(const ColorHSBA &)) & toHSB,
                                   (ColorHSB(*)(const ColorRGB &)) & toHSB));

    tbl.set_function("toHSBA",
                     sol::overload((ColorHSBA(*)(const ColorRGBA &)) & toHSBA,
                                   (ColorHSBA(*)(const ColorHSB &)) & toHSBA,
                                   (ColorHSBA(*)(const ColorRGB &)) & toHSBA));

    tbl.new_usertype<Rect>("Rect",
                           sol::call_constructor,
                           sol::constructors<Rect(),
                                             Rect(Float, Float, Float, Float),
                                             Rect(const Rect &),
                                             Rect(const Vec2 &, const Vec2 &),
                                             Rect(const Vec2 &, Float, Float)>(),
                           sol::meta_function::equal_to,
                           &Rect::operator==,
                           "contains",
                           sol::overload((bool (Rect::*)(const Rect &) const) & Rect::contains,
                                         (bool (Rect::*)(const Vec2 &) const) & Rect::contains),
                           "setSize",
                           sol::overload((void (Rect::*)(Float, Float)) & Rect::setSize,
                                         (void (Rect::*)(const Vec2 &)) & Rect::setSize),
                           "setPosition",
                           sol::overload((void (Rect::*)(Float, Float)) & Rect::setPosition,
                                         (void (Rect::*)(const Vec2 &)) & Rect::setPosition),
                           "moveBy",
                           sol::overload((void (Rect::*)(Float, Float)) & Rect::moveBy,
                                         (void (Rect::*)(const Vec2 &)) & Rect::moveBy),
                           "setMin",
                           sol::overload((void (Rect::*)(Float, Float)) & Rect::setMin,
                                         (void (Rect::*)(const Vec2 &)) & Rect::setMin),
                           "setMax",
                           sol::overload((void (Rect::*)(Float, Float)) & Rect::setMax,
                                         (void (Rect::*)(const Vec2 &)) & Rect::setMax),
                           "area",
                           &Rect::area,
                           "min",
                           (const Vec2 & (Rect::*)(void)const) & Rect::min,
                           "max",
                           (const Vec2 & (Rect::*)(void)const) & Rect::max,
                           "center",
                           &Rect::center,
                           "width",
                           &Rect::width,
                           "height",
                           &Rect::height,
                           "size",
                           &Rect::size);

    tbl.new_usertype<Line2>(
        "Line2",
        sol::call_constructor,
        sol::constructors<Line2(), Line2(const Line2 &), Line2(const Vec2 &, const Vec2 &)>(),
        "fromPoints",
        &Line2::fromPoints,
        "position",
        &Line2::position,
        "direction",
        &Line2::direction);

    tbl.new_usertype<LineSegment2>("LineSegment2",
                                   sol::call_constructor,
                                   sol::constructors<LineSegment2(),
                                                     LineSegment2(const LineSegment2 &),
                                                     LineSegment2(const Vec2 &, const Vec2 &)>(),
                                   "positionOne",
                                   &LineSegment2::positionOne,
                                   "positionTwo",
                                   &LineSegment2::positionTwo,
                                   "direction",
                                   &LineSegment2::direction);

    tbl.set_function(
        "intersect",
        sol::overload((stick::Maybe<Vec2>(*)(const Line2 &, const Line2 &)) & intersect,
                      (stick::Maybe<Vec2>(*)(const LineSegment2 &, const LineSegment2 &)) &
                          intersect));

    // Register Tweens
    detail::registerTweenClass<TweenLinearEaseOutf>(tbl, "TweenLinearEaseOut");
    detail::registerTweenClass<TweenLinearEaseOut2f>(tbl, "TweenLinearEaseOut2");

    detail::registerTweenClass<TweenCubicEaseInf>(tbl, "TweenCubicEaseIn");
    detail::registerTweenClass<TweenCubicEaseIn2f>(tbl, "TweenCubicEaseIn2");
    detail::registerTweenClass<TweenCubicEaseOutf>(tbl, "TweenCubicEaseOut");
    detail::registerTweenClass<TweenCubicEaseOut2f>(tbl, "TweenCubicEaseOut2");
    detail::registerTweenClass<TweenCubicEaseInOutf>(tbl, "TweenCubicEaseInOut");
    detail::registerTweenClass<TweenCubicEaseInOut2f>(tbl, "TweenCubicEaseInOut2");

    detail::registerTweenClass<TweenElasticEaseInf>(tbl, "TweenElasticEaseIn");
    detail::registerTweenClass<TweenElasticEaseIn2f>(tbl, "TweenElasticEaseIn2");
    detail::registerTweenClass<TweenElasticEaseOutf>(tbl, "TweenElasticEaseOut");
    detail::registerTweenClass<TweenElasticEaseOut2f>(tbl, "TweenElasticEaseOut2");
    //@TODO: thse are missing in crunch, too
    // detail::registerTweenClass<TweenElasticEaseInOutf>(tbl, "TweenElasticEaseInOut");
    // detail::registerTweenClass<TweenElasticEaseInOut2f>(tbl, "TweenElasticEaseInOut2");
    
    detail::registerTweenClass<TweenBackEaseInf>(tbl, "TweenBackEaseIn");
    detail::registerTweenClass<TweenBackEaseIn2f>(tbl, "TweenBackEaseIn2");
    detail::registerTweenClass<TweenBackEaseOutf>(tbl, "TweenBackEaseOut");
    detail::registerTweenClass<TweenBackEaseOut2f>(tbl, "TweenBackEaseOut2");
    detail::registerTweenClass<TweenBackEaseInOutf>(tbl, "TweenBackEaseInOut");
    detail::registerTweenClass<TweenBackEaseInOut2f>(tbl, "TweenBackEaseInOut2");


    // tbl.new_usertype<TweenLinearEaseOutf>(
    //     "TweenLinearEaseOut",
    //     sol::call_constructor,
    //     sol::constructors<TweenLinearEaseOutf(),
    //                       TweenLinearEaseOutf(const Float32 &, const Float32 &, Float64)>(),
    //     "update",
    //     &TweenLinearEaseOutf::update,
    //     "origin",
    //     &TweenLinearEaseOutf::origin,
    //     "destination",
    //     &TweenLinearEaseOutf::destination,
    //     "current",
    //     &TweenLinearEaseOutf::current,
    //     "timeElapsed",
    //     &TweenLinearEaseOutf::timeElapsed,
    //     "duration",
    //     &TweenLinearEaseOutf::duration,
    //     "isFinished",
    //     &TweenLinearEaseOutf::isFinished);

    // tbl.new_usertype<TweenLinearEaseOut2f>(
    //     "TweenLinearEaseOut2",
    //     sol::call_constructor,
    //     sol::constructors<TweenLinearEaseOut2f(),
    //                       TweenLinearEaseOut2f(const Vec2f &, const Vec2f &, Float64)>(),
    //     "update",
    //     &TweenLinearEaseOut2f::update,
    //     "origin",
    //     &TweenLinearEaseOut2f::origin,
    //     "destination",
    //     &TweenLinearEaseOut2f::destination,
    //     "current",
    //     &TweenLinearEaseOut2f::current,
    //     "timeElapsed",
    //     &TweenLinearEaseOut2f::timeElapsed,
    //     "duration",
    //     &TweenLinearEaseOut2f::duration,
    //     "isFinished",
    //     &TweenLinearEaseOut2f::isFinished);

    // tbl.new_usertype<TweenCubicEaseOutf>(
    //     "TweenCubicEaseOut",
    //     sol::call_constructor,
    //     sol::constructors<TweenCubicEaseOutf(),
    //                       TweenCubicEaseOutf(const Float32 &, const Float32 &, Float64)>(),
    //     "update",
    //     &TweenCubicEaseOutf::update,
    //     "origin",
    //     &TweenCubicEaseOutf::origin,
    //     "destination",
    //     &TweenCubicEaseOutf::destination,
    //     "current",
    //     &TweenCubicEaseOutf::current,
    //     "timeElapsed",
    //     &TweenCubicEaseOutf::timeElapsed,
    //     "duration",
    //     &TweenCubicEaseOutf::duration,
    //     "isFinished",
    //     &TweenCubicEaseOutf::isFinished);

    // tbl.new_usertype<TweenCubicEaseOut2f>(
    //     "TweenCubicEaseOut2",
    //     sol::call_constructor,
    //     sol::constructors<TweenCubicEaseOut2f(),
    //                       TweenCubicEaseOut2f(const Vec2f &, const Vec2f &, Float64)>(),
    //     "update",
    //     &TweenCubicEaseOut2f::update,
    //     "origin",
    //     &TweenCubicEaseOut2f::origin,
    //     "destination",
    //     &TweenCubicEaseOut2f::destination,
    //     "current",
    //     &TweenCubicEaseOut2f::current,
    //     "timeElapsed",
    //     &TweenCubicEaseOut2f::timeElapsed,
    //     "duration",
    //     &TweenCubicEaseOut2f::duration,
    //     "isFinished",
    //     &TweenCubicEaseOut2f::isFinished);

    // tbl.new_usertype<TweenCubicEaseInf>(
    //     "TweenCubicEaseIn",
    //     sol::call_constructor,
    //     sol::constructors<TweenCubicEaseInf(),
    //                       TweenCubicEaseInf(const Float32 &, const Float32 &, Float64)>(),
    //     "update",
    //     &TweenCubicEaseInf::update,
    //     "origin",
    //     &TweenCubicEaseInf::origin,
    //     "destination",
    //     &TweenCubicEaseInf::destination,
    //     "current",
    //     &TweenCubicEaseInf::current,
    //     "timeElapsed",
    //     &TweenCubicEaseInf::timeElapsed,
    //     "duration",
    //     &TweenCubicEaseInf::duration,
    //     "isFinished",
    //     &TweenCubicEaseInf::isFinished);

    // tbl.new_usertype<TweenCubicEaseIn2f>(
    //     "TweenCubicEaseIn2",
    //     sol::call_constructor,
    //     sol::constructors<TweenCubicEaseIn2f(),
    //                       TweenCubicEaseIn2f(const Vec2f &, const Vec2f &, Float64)>(),
    //     "update",
    //     &TweenCubicEaseIn2f::update,
    //     "origin",
    //     &TweenCubicEaseIn2f::origin,
    //     "destination",
    //     &TweenCubicEaseIn2f::destination,
    //     "current",
    //     &TweenCubicEaseIn2f::current,
    //     "timeElapsed",
    //     &TweenCubicEaseIn2f::timeElapsed,
    //     "duration",
    //     &TweenCubicEaseIn2f::duration,
    //     "isFinished",
    //     &TweenCubicEaseIn2f::isFinished);

    // tbl.new_usertype<TweenCubicEaseInOutf>(
    //     "TweenCubicEaseInOut",
    //     sol::call_constructor,
    //     sol::constructors<TweenCubicEaseInOutf(),
    //                       TweenCubicEaseInOutf(const Float32 &, const Float32 &, Float64)>(),
    //     "update",
    //     &TweenCubicEaseInOutf::update,
    //     "origin",
    //     &TweenCubicEaseInOutf::origin,
    //     "destination",
    //     &TweenCubicEaseInOutf::destination,
    //     "current",
    //     &TweenCubicEaseInOutf::current,
    //     "timeElapsed",
    //     &TweenCubicEaseInOutf::timeElapsed,
    //     "duration",
    //     &TweenCubicEaseInOutf::duration,
    //     "isFinished",
    //     &TweenCubicEaseInOutf::isFinished);

    // tbl.new_usertype<TweenCubicEaseInOut2f>(
    //     "TweenCubicEaseInOut2",
    //     sol::call_constructor,
    //     sol::constructors<TweenCubicEaseInOut2f(),
    //                       TweenCubicEaseInOut2f(const Vec2f &, const Vec2f &, Float64)>(),
    //     "update",
    //     &TweenCubicEaseInOut2f::update,
    //     "origin",
    //     &TweenCubicEaseInOut2f::origin,
    //     "destination",
    //     &TweenCubicEaseInOut2f::destination,
    //     "current",
    //     &TweenCubicEaseInOut2f::current,
    //     "timeElapsed",
    //     &TweenCubicEaseInOut2f::timeElapsed,
    //     "duration",
    //     &TweenCubicEaseInOut2f::duration,
    //     "isFinished",
    //     &TweenCubicEaseInOut2f::isFinished);

    // tbl.new_usertype<TweenElasticEaseOutf>(
    //     "TweenElasticEaseOut",
    //     sol::call_constructor,
    //     sol::constructors<TweenElasticEaseOutf(),
    //                       TweenElasticEaseOutf(const Float32 &, const Float32 &, Float64)>(),
    //     "update",
    //     &TweenElasticEaseOutf::update,
    //     "origin",
    //     &TweenElasticEaseOutf::origin,
    //     "destination",
    //     &TweenElasticEaseOutf::destination,
    //     "current",
    //     &TweenElasticEaseOutf::current,
    //     "timeElapsed",
    //     &TweenElasticEaseOutf::timeElapsed,
    //     "duration",
    //     &TweenElasticEaseOutf::duration,
    //     "isFinished",
    //     &TweenElasticEaseOutf::isFinished);

    // tbl.new_usertype<TweenElasticEaseOut2f>(
    //     "TweenElasticEaseOut2",
    //     sol::call_constructor,
    //     sol::constructors<TweenElasticEaseOut2f(),
    //                       TweenElasticEaseOut2f(const Vec2f &, const Vec2f &, Float64)>(),
    //     "update",
    //     &TweenElasticEaseOut2f::update,
    //     "origin",
    //     &TweenElasticEaseOut2f::origin,
    //     "destination",
    //     &TweenElasticEaseOut2f::destination,
    //     "current",
    //     &TweenElasticEaseOut2f::current,
    //     "timeElapsed",
    //     &TweenElasticEaseOut2f::timeElapsed,
    //     "duration",
    //     &TweenElasticEaseOut2f::duration,
    //     "isFinished",
    //     &TweenElasticEaseOut2f::isFinished);

    tbl.set_function(
        "random",
        sol::overload(
            []() { return detail::luaRandomNumberGenerator().randomd(); },
            [](Float _num) { return detail::luaRandomNumberGenerator().randomd(_num); },
            [](Float _a, Float _b) { return detail::luaRandomNumberGenerator().randomd(_a, _b); }));

    tbl.set_function(
        "randomi",
        sol::overload(
            []() { return detail::luaRandomNumberGenerator().randomi(); },
            [](Int32 _num) { return detail::luaRandomNumberGenerator().randomi(_num); },
            [](Int32 _a, Int32 _b) { return detail::luaRandomNumberGenerator().randomi(_a, _b); }));

    tbl.set_function("randomSeed",
                     [](Size _val) { detail::luaRandomNumberGenerator().setSeed(_val); });

    tbl.set_function(
        "noise",
        sol::overload([](Float _a) { return detail::luaNoiseGenerator().noise(_a); },
                      [](Float _a, Float _b) { return detail::luaNoiseGenerator().noise(_a, _b); },
                      [](Float _a, Float _b, Float _c) {
                          return detail::luaNoiseGenerator().noise(_a, _b, _c);
                      },
                      [](Float _a, Float _b, Float _c, Float _d) {
                          return detail::luaNoiseGenerator().noise(_a, _b, _c, _d);
                      }));

    tbl.set_function("noiseSeed", [](Int32 _val) { detail::luaNoiseGenerator().setSeed(_val); });

    tbl.set_function("toRadians", toRadians<Float>);
    tbl.set_function("toDegrees", toDegrees<Float>);
    tbl.set_function("directedAngle", directedAngle<Float>);
}
} // namespace crunchLuaSol

#endif // CRUNCHLUASOL_CRUNCHLUASOL_HPP
