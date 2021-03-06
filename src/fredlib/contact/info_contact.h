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
 *  contact info
 */

#ifndef INFO_CONTACT_H_
#define INFO_CONTACT_H_

#include <string>
#include <vector>

#include <boost/date_time/posix_time/ptime.hpp>

#include "src/fredlib/opexception.h"
#include "src/fredlib/opcontext.h"
#include "util/optional_value.h"
#include "util/printable.h"
#include "info_contact_output.h"

namespace Fred
{
    /**
    * Contact info by handle.
    * Contact handle to get info about the contact is set via constructor.
    * It's executed by @ref exec method with database connection supplied in @ref OperationContext parameter.
    */
    class InfoContactByHandle : public Util::Printable
    {
        const std::string handle_;/**< handle of the contact */
        bool lock_;/**< if set to true lock object_registry row for update, if set to false lock for share */

    public:
        DECLARE_EXCEPTION_DATA(unknown_contact_handle, std::string);/**< exception members for unknown handle of the contact generated by macro @ref DECLARE_EXCEPTION_DATA*/
        struct Exception
        : virtual Fred::OperationException
        , ExceptionData_unknown_contact_handle<Exception>
        {};

        /**
        * Info contact constructor with mandatory parameter.
        * @param handle sets handle of the contact into @ref handle_ attribute
        */
        InfoContactByHandle(const std::string& handle);

        /**
        * Sets lock for update.
        * Default, if not set, is lock for share.
        * Sets true to lock flag in @ref lock_ attribute
        * @return operation instance reference to allow method chaining
        */
        InfoContactByHandle& set_lock();

        /**
        * Executes getting info about the contact.
        * @param ctx contains reference to database and logging interface
        * @param local_timestamp_pg_time_zone_name is postgresql time zone name of the returned data
        * @return info data about the contact
        * @throws Exception in case of wrong input data or other predictable and superable failure.
        * @throws InternalError otherwise
        * When exception is thrown changes to database are considered inconsistent and should be rolled back by the caller.
        */
        InfoContactOutput exec(OperationContext& ctx, const std::string& local_timestamp_pg_time_zone_name = "Europe/Prague");//return data

        /**
        * Dumps state of the instance into the string
        * @return string with description of the instance state
        */
        std::string to_string() const;

    };

    /**
    * Contact info by id.
    * Contact id to get info about the contact is set via constructor.
    * It's executed by @ref exec method with database connection supplied in @ref OperationContext parameter.
    */
    class InfoContactById : public Util::Printable
    {
        const unsigned long long id_;/**< object id of the contact */
        bool lock_;/**< if set to true lock object_registry row for update, if set to false lock for share */

    public:
        DECLARE_EXCEPTION_DATA(unknown_object_id, unsigned long long);/**< exception members for unknown object id of the contact generated by macro @ref DECLARE_EXCEPTION_DATA*/
        struct Exception
        : virtual Fred::OperationException
        , ExceptionData_unknown_object_id<Exception>
        {};

        /**
        * Info contact constructor with mandatory parameter.
        * @param id sets object id of the contact into @ref id_ attribute
        */
        explicit InfoContactById(unsigned long long id);

        /**
        * Sets lock for update.
        * Default, if not set, is lock for share.
        * Sets true to lock flag in @ref lock_ attribute
        * @return operation instance reference to allow method chaining
        */
        InfoContactById& set_lock();

        /**
        * Executes getting info about the contact.
        * @param ctx contains reference to database and logging interface
        * @param local_timestamp_pg_time_zone_name is postgresql time zone name of the returned data
        * @return info data about the contact
        * @throws Exception in case of wrong input data or other predictable and superable failure.
        * @throws InternalError otherwise
        * When exception is thrown changes to database are considered inconsistent and should be rolled back by the caller.
        */
        InfoContactOutput exec(OperationContext& ctx, const std::string& local_timestamp_pg_time_zone_name = "Europe/Prague");//return data

        /**
        * Dumps state of the instance into the string
        * @return string with description of the instance state
        */
        std::string to_string() const;

    };

    /**
    * Contact history info by registry object identifier  and optional time.
    * Contact registry object identifier to get history info about the contact is set via constructor.
    * It's executed by @ref exec method with database connection supplied in @ref OperationContext parameter.
    */
    class InfoContactHistory  : public Util::Printable
    {
        const std::string roid_;/**< registry object identifier of the contact */
        Optional<boost::posix_time::ptime> history_timestamp_;/**< timestamp of history state we want to get (in time zone set in @ref local_timestamp_pg_time_zone_name parameter) */
        bool lock_;/**< if set to true lock object_registry row for update, if set to false lock for share */

    public:
        DECLARE_EXCEPTION_DATA(unknown_registry_object_identifier, std::string);/**< exception members for unknown registry object identifier of the contact generated by macro @ref DECLARE_EXCEPTION_DATA*/
        struct Exception
        : virtual Fred::OperationException
        , ExceptionData_unknown_registry_object_identifier<Exception>
        {};

        /**
        * Info contact history constructor with mandatory parameter.
        * @param roid sets registry object identifier of the contact into @ref roid_ attribute
        */
        InfoContactHistory(const std::string& roid);

        /**
        * Info contact history constructor with all parameters.
        * @param roid sets registry object identifier of the contact into @ref roid_ attribute
        * @param history_timestamp sets timestamp of history state we want to get @ref history_timestamp_ attribute
        */
        InfoContactHistory(const std::string& roid, const Optional<boost::posix_time::ptime>& history_timestamp);

        /**
        * Sets timestamp of history state we want to get.
        * @param history_timestamp sets timestamp of history state we want to get @ref history_timestamp_ attribute
        * @return operation instance reference to allow method chaining
        */
        InfoContactHistory& set_history_timestamp(boost::posix_time::ptime history_timestamp);

        /**
        * Sets lock for update.
        * Default, if not set, is lock for share.
        * Sets true to lock flag in @ref lock_ attribute
        * @return operation instance reference to allow method chaining
        */
        InfoContactHistory& set_lock();

        /**
        * Executes getting history info about the contact.
        * @param ctx contains reference to database and logging interface
        * @param local_timestamp_pg_time_zone_name is postgresql time zone name of the returned data
        * @return history info data about the contact
        * @throws Exception in case of wrong input data or other predictable and superable failure.
        * @throws InternalError otherwise
        * When exception is thrown changes to database are considered inconsistent and should be rolled back by the caller.
        */
        std::vector<InfoContactOutput> exec(OperationContext& ctx, const std::string& local_timestamp_pg_time_zone_name = "Europe/Prague");//return data

        /**
        * Dumps state of the instance into the string
        * @return string with description of the instance state
        */
        std::string to_string() const;

    };

    /**
    * Contact info by id including history.
    * Contact id to get info about the contact is set via constructor.
    * It's executed by @ref exec method with database connection supplied in @ref OperationContext parameter.
    */
    class InfoContactHistoryById : public Util::Printable
    {
        unsigned long long id_;/**< object id of the contact */
        bool lock_;/**< if set to true lock object_registry row for update, if set to false lock for share */

    public:
        DECLARE_EXCEPTION_DATA(unknown_object_id, unsigned long long);/**< exception members for unknown object id of the contact generated by macro @ref DECLARE_EXCEPTION_DATA*/
        struct Exception
        : virtual Fred::OperationException
        , ExceptionData_unknown_object_id<Exception>
        {};

        /**
        * Info contact history constructor with mandatory parameter.
        * @param id sets object id of the contact into @ref id_ attribute
        */
        explicit InfoContactHistoryById(unsigned long long id);

        /**
        * Sets lock for update.
        * Default, if not set, is lock for share.
        * Sets true to lock flag in @ref lock_ attribute
        * @return operation instance reference to allow method chaining
        */
        InfoContactHistoryById& set_lock();

        /**
        * Executes getting history info about the contact.
        * @param ctx contains reference to database and logging interface
        * @param local_timestamp_pg_time_zone_name is postgresql time zone name of the returned data
        * @return history info data about the contact
        * @throws Exception in case of wrong input data or other predictable and superable failure.
        * @throws InternalError otherwise
        * When exception is thrown changes to database are considered inconsistent and should be rolled back by the caller.
        */
        std::vector<InfoContactOutput> exec(OperationContext& ctx, const std::string& local_timestamp_pg_time_zone_name = "Europe/Prague");//return data

        /**
        * Dumps state of the instance into the string
        * @return string with description of the instance state
        */
        std::string to_string() const;

    };

    /**
    * Contact info by historyid.
    * Contact historyid to get info about the contact is set via constructor.
    * It's executed by @ref exec method with database connection supplied in @ref OperationContext parameter.
    */
    class InfoContactHistoryByHistoryid : public Util::Printable
    {
        unsigned long long historyid_;/**< history id of the contact */
        bool lock_;/**< if set to true lock object_registry row for update, if set to false lock for share */

    public:
        DECLARE_EXCEPTION_DATA(unknown_object_historyid, unsigned long long);/**< exception members for unknown object historyid of the contact generated by macro @ref DECLARE_EXCEPTION_DATA*/
        struct Exception
        : virtual Fred::OperationException
        , ExceptionData_unknown_object_historyid<Exception>
        {};

        /**
        * Info contact history constructor with mandatory parameter.
        * @param historyid sets object historyid of the contact into @ref historyid_ attribute
        */
        explicit InfoContactHistoryByHistoryid(unsigned long long historyid);

        /**
        * Sets lock for update.
        * Default, if not set, is lock for share.
        * Sets true to lock flag in @ref lock_ attribute
        * @return operation instance reference to allow method chaining
        */
        InfoContactHistoryByHistoryid& set_lock();

        /**
        * Executes getting history info about the contact.
        * @param ctx contains reference to database and logging interface
        * @param local_timestamp_pg_time_zone_name is postgresql time zone name of the returned data
        * @return history info data about the contact
        * @throws Exception in case of wrong input data or other predictable and superable failure.
        * @throws InternalError otherwise
        * When exception is thrown changes to database are considered inconsistent and should be rolled back by the caller.
        */
        InfoContactOutput exec(OperationContext& ctx, const std::string& local_timestamp_pg_time_zone_name = "Europe/Prague");//return data

        /**
        * Dumps state of the instance into the string
        * @return string with description of the instance state
        */
        std::string to_string() const;

    };

}//namespace Fred

#endif//INFO_CONTACT_H_
