#ifndef CRUNCHLUASOL_CRUNCHLUASOL_HPP
#define CRUNCHLUASOL_CRUNCHLUASOL_HPP

#include <Stick/String.hpp>
#include <sol/sol.hpp>

namespace crunchLuaSol
{
STICK_API sol::table ensureNamespaceTable(sol::state_view _lua, sol::table _startTbl, const stick::String & _namespace);
STICK_API void registerCrunch(sol::state_view _lua, const stick::String & _namespace = "");
STICK_API void registerCrunch(sol::state_view _lua, sol::table _tbl);
} // namespace crunchLuaSol

#endif // CRUNCHLUASOL_CRUNCHLUASOL_HPP
