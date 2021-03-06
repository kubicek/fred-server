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

#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>
#include <exception>
#include <queue>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include <boost/algorithm/string.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time.hpp>
#include <boost/assign/list_of.hpp>

#include "setup_server_decl.h"
#include "time_clock.h"
#include "src/fredlib/registrar.h"
#include "src/fredlib/contact/copy_contact.h"
#include "src/fredlib/opexception.h"
#include "util/util.h"

#include "src/fredlib/contact/create_contact.h"
#include "src/fredlib/contact/info_contact.h"

#include "src/fredlib/contact_verification/contact.h"
#include "src/fredlib/object_states.h"
#include "src/contact_verification/contact_verification_impl.h"
#include "random_data_generator.h"
#include "concurrent_queue.h"


#include "src/fredlib/db_settings.h"

#include "cfg/handle_general_args.h"
#include "cfg/handle_server_args.h"
#include "cfg/handle_logging_args.h"
#include "cfg/handle_database_args.h"
#include "cfg/handle_threadgroup_args.h"
#include "cfg/handle_corbanameservice_args.h"

//not using UTF defined main
#define BOOST_TEST_NO_MAIN

#include "cfg/config_handler_decl.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestCopyContact)

const std::string server_name = "test-copy-contact";

struct copy_contact_fixture
{
    std::string xmark;
    std::string sys_registrar_handle;
    std::string registrar_handle;
    std::string src_contact_handle;
    std::string dst_contact_handle;

    copy_contact_fixture()
    :   xmark(RandomDataGenerator().xnumstring(6)),
        src_contact_handle(std::string("TEST-COPY-CONTACT-SRC-HANDLE") + xmark),
        dst_contact_handle(std::string("TEST-COPY-CONTACT-DST-HANDLE") + xmark)
    {
        Fred::OperationContext ctx;
        Database::Result registrar_result = ctx.get_conn().exec(
            "SELECT (SELECT handle FROM registrar WHERE system ORDER BY id LIMIT 1),"
                   "(SELECT handle FROM registrar WHERE NOT system ORDER BY id LIMIT 1)");
        sys_registrar_handle = static_cast<std::string>(registrar_result[0][0]);
        registrar_handle = static_cast<std::string>(registrar_result[0][1]);
        BOOST_CHECK(!registrar_handle.empty());//expecting existing system registrar

        Fred::CreateContact(src_contact_handle, registrar_handle)
            .set_name(std::string("TEST-COPY-CONTACT NAME")+xmark)
            .set_disclosename(true)
            .set_street1(std::string("STR1")+xmark)
            .set_city("Praha").set_postalcode("11150").set_country("CZ")
            .set_discloseaddress(true)
            .exec(ctx);

        ctx.commit_transaction();
    }
    ~copy_contact_fixture()
    { }
};

/**
 * test CopyContact
 * ...
 * calls in test shouldn't throw
 */
BOOST_FIXTURE_TEST_CASE(copy_contact, copy_contact_fixture)
{
    Fred::OperationContext ctx;

    const Fred::InfoContactData src_contact_info = Fred::InfoContactByHandle(src_contact_handle).exec(ctx).info_contact_data;
    BOOST_CHECK(src_contact_info.delete_time.isnull());

    Fred::CopyContact(src_contact_handle, dst_contact_handle, sys_registrar_handle, 0).exec(ctx);
    ctx.commit_transaction();

    const Fred::InfoContactData dst_contact_info = Fred::InfoContactByHandle(dst_contact_handle).exec(ctx).info_contact_data;

    BOOST_CHECK(src_contact_info.roid != dst_contact_info.roid);
    BOOST_CHECK(boost::algorithm::to_upper_copy(src_contact_info.handle).compare(boost::algorithm::to_upper_copy(dst_contact_info.handle)) != 0);
    BOOST_CHECK(boost::algorithm::to_upper_copy(src_contact_info.sponsoring_registrar_handle).compare(boost::algorithm::to_upper_copy(dst_contact_info.sponsoring_registrar_handle)) != 0);
    BOOST_CHECK(boost::algorithm::to_upper_copy(src_contact_info.create_registrar_handle).compare(boost::algorithm::to_upper_copy(dst_contact_info.create_registrar_handle)) != 0);
    BOOST_CHECK(src_contact_info.authinfopw == dst_contact_info.authinfopw);
    BOOST_CHECK((src_contact_info.name.isnull() == dst_contact_info.name.isnull()) &&
                (src_contact_info.name.isnull() || (src_contact_info.name.get_value().compare(
                                                    dst_contact_info.name.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.organization.isnull() == dst_contact_info.organization.isnull()) &&
                (src_contact_info.organization.isnull() || (src_contact_info.organization.get_value().compare(
                                                            dst_contact_info.organization.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.street1.isnull() == dst_contact_info.street1.isnull()) &&
                (src_contact_info.street1.isnull() || (src_contact_info.street1.get_value().compare(
                                                       dst_contact_info.street1.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.street2.isnull() == dst_contact_info.street2.isnull()) &&
                (src_contact_info.street2.isnull() || (src_contact_info.street2.get_value().compare(
                                                       dst_contact_info.street2.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.street3.isnull() == dst_contact_info.street3.isnull()) &&
                (src_contact_info.street3.isnull() || (src_contact_info.street3.get_value().compare(
                                                       dst_contact_info.street3.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.city.isnull() == dst_contact_info.city.isnull()) &&
                (src_contact_info.city.isnull() || (src_contact_info.city.get_value().compare(
                                                    dst_contact_info.city.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.stateorprovince.isnull() == dst_contact_info.stateorprovince.isnull()) &&
                (src_contact_info.stateorprovince.isnull() || (src_contact_info.stateorprovince.get_value().compare(
                                                               dst_contact_info.stateorprovince.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.postalcode.isnull() == dst_contact_info.postalcode.isnull()) &&
                (src_contact_info.postalcode.isnull() || (src_contact_info.postalcode.get_value().compare(
                                                          dst_contact_info.postalcode.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.country.isnull() == dst_contact_info.country.isnull()) &&
                (src_contact_info.country.isnull() || (src_contact_info.country.get_value().compare(
                                                       dst_contact_info.country.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.telephone.isnull() == dst_contact_info.telephone.isnull()) &&
                (src_contact_info.telephone.isnull() || (src_contact_info.telephone.get_value().compare(
                                                         dst_contact_info.telephone.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.fax.isnull() == dst_contact_info.fax.isnull()) &&
                (src_contact_info.fax.isnull() || (src_contact_info.fax.get_value().compare(
                                                   dst_contact_info.fax.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.email.isnull() == dst_contact_info.email.isnull()) &&
                (src_contact_info.email.isnull() || (src_contact_info.email.get_value().compare(
                                                     dst_contact_info.email.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.notifyemail.isnull() == dst_contact_info.notifyemail.isnull()) &&
                (src_contact_info.notifyemail.isnull() || (src_contact_info.notifyemail.get_value().compare(
                                                           dst_contact_info.notifyemail.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.vat.isnull() == dst_contact_info.vat.isnull()) &&
                (src_contact_info.vat.isnull() || (src_contact_info.vat.get_value().compare(
                                                   dst_contact_info.vat.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.ssntype.isnull() == dst_contact_info.ssntype.isnull()) &&
                (src_contact_info.ssntype.isnull() || (src_contact_info.ssntype.get_value().compare(
                                                       dst_contact_info.ssntype.get_value()) == 0)));
    BOOST_CHECK((src_contact_info.ssn.isnull() == dst_contact_info.ssn.isnull()) &&
                (src_contact_info.ssn.isnull() || (src_contact_info.ssn.get_value().compare(
                                                   dst_contact_info.ssn.get_value()) == 0)));
    BOOST_CHECK(src_contact_info.disclosename == dst_contact_info.disclosename);
    BOOST_CHECK(src_contact_info.discloseorganization == dst_contact_info.discloseorganization);
    BOOST_CHECK(src_contact_info.discloseaddress == dst_contact_info.discloseaddress);
    BOOST_CHECK(src_contact_info.disclosetelephone == dst_contact_info.disclosetelephone);
    BOOST_CHECK(src_contact_info.disclosefax == dst_contact_info.disclosefax);
    BOOST_CHECK(src_contact_info.discloseemail == dst_contact_info.discloseemail);
    BOOST_CHECK(src_contact_info.disclosevat == dst_contact_info.disclosevat);
    BOOST_CHECK(src_contact_info.discloseident == dst_contact_info.discloseident);
    BOOST_CHECK(src_contact_info.disclosenotifyemail == dst_contact_info.disclosenotifyemail);
}

/**
 * test CopyContactBad
 * ...
 * calls in test should throw
 */
BOOST_FIXTURE_TEST_CASE(copy_contact_bad, copy_contact_fixture)
{
    const std::string bad_src_contact_handle = dst_contact_handle;
    try {
        Fred::OperationContext ctx;//new connection to rollback on error
        Fred::CopyContact(bad_src_contact_handle, dst_contact_handle, sys_registrar_handle, 0).exec(ctx);
        ctx.commit_transaction();
        BOOST_CHECK(false);
    }
    catch(const Fred::CopyContact::Exception &ex) {
        BOOST_CHECK(ex.is_set_src_contact_handle_not_found());
        BOOST_CHECK(ex.get_src_contact_handle_not_found().compare(bad_src_contact_handle) == 0);
    }

    const std::string bad_dst_contact_handle = src_contact_handle;
    try {
        Fred::OperationContext ctx;//new connection to rollback on error
        Fred::CopyContact(src_contact_handle, bad_dst_contact_handle, sys_registrar_handle, 0).exec(ctx);
        ctx.commit_transaction();
        BOOST_CHECK(false);
    }
    catch(const Fred::CopyContact::Exception &ex) {
        BOOST_CHECK(ex.is_set_dst_contact_handle_already_exist());
        BOOST_CHECK(ex.get_dst_contact_handle_already_exist().compare(bad_dst_contact_handle) == 0);
    }

    const std::string bad_registrar_handle = std::string("BAD") + sys_registrar_handle + xmark;
    try {
        Fred::OperationContext ctx;//new connection to rollback on error
        Fred::CopyContact(src_contact_handle, dst_contact_handle, bad_registrar_handle, 0).exec(ctx);
        ctx.commit_transaction();
        BOOST_CHECK(false);
    }
    catch(const Fred::CopyContact::Exception &ex) {
        BOOST_CHECK(ex.is_set_create_contact_failed());
    }
}

BOOST_AUTO_TEST_SUITE_END();//TestCopyContact
