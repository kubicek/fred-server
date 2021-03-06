/*
 * Copyright (C) 2013  CZ.NIC, z.s.p.o.
 *
 * This file is part of FRED.
 *
 * FRED is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * FRED is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FRED.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 *  @file
 *  keyset check
 */

#ifndef CHECK_KEYSET_H
#define CHECK_KEYSET_H

#include <string>

#include "src/fredlib/opexception.h"
#include "src/fredlib/opcontext.h"
#include "util/printable.h"

namespace Fred
{

    /**
    * Checking of keyset properties.
    */
    class CheckKeyset : public Util::Printable
    {
        const std::string handle_;/**< keyset identifier */
    public:

        /**
        * Check keyset constructor.
        * @param handle a keyset identifier.
        */
        CheckKeyset(const std::string& handle);

        /**
        * Check keyset handle syntax.
        * @param ctx an operation context with database and logging interface.
        * @return true if invalid, false if ok
        */
        bool is_invalid_handle();

        /**
        * Check if keyset handle is registered.
        * @param ctx an operation context with database and logging interface.
        * @param conflicting_handle_out an conflicting keyset identifier reference used for output if true is returned.
        * @return true if registered, false if not
        */
        bool is_registered(OperationContext& ctx, std::string& conflicting_handle_out);

        /**
        * Check if keyset handle is registered.
        * @param ctx an operation context with database and logging interface.
        * @return true if registered, false if not
        */
        bool is_registered(OperationContext& ctx);

        /**
        * Check if keyset handle is in protection period.
        * @param ctx an operation context with database and logging interface.
        * @return true if protected, false if not
        */
        bool is_protected(OperationContext& ctx);

        /**
        * Check if keyset handle is free for registration.
        * @param ctx an operation context with database and logging interface.
        * @return true if protected, false if not
        */
        bool is_free(OperationContext& ctx);

        /**
        * Dumps state of the instance into the string
        * @return string with description of the instance state
        */
        std::string to_string() const;
    };//class CheckKeyset

}//namespace Fred

#endif//CHECK_KEYSET_H
