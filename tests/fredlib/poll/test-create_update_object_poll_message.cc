/*
 * Copyright (C) 2014  CZ.NIC, z.s.p.o.
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

//not using UTF defined main
#define BOOST_TEST_NO_MAIN

#include "setup_utils.h"

#include "src/fredlib/poll/create_update_object_poll_message.h"
#include "src/fredlib/poll/create_poll_message_impl.h"
#include "src/fredlib/poll/message_types.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestPoll)
BOOST_AUTO_TEST_SUITE(TestCreateUpdateObjectPollMessage)

/**
 @test
 executing TestCreateUpdateObjectPollMessage and checking data in database common for all types

 @pre existing domain history_id
 @post correct values present in message and poll_eppaction tables
 */
BOOST_AUTO_TEST_CASE( test_correct_generic_data )
{
    Fred::OperationContext ctx;

    setup_domain domain;

    Database::Result ids_res = ctx.get_conn().exec(
        "SELECT id AS count_ "
        "   FROM message "
    );

    std::vector<int> ids_before;
    for(Database::Result::Iterator it = ids_res.begin();
        it != ids_res.end();
        ++it
    ) {
        ids_before.push_back(
            static_cast<int>((*it)["count_"])
        );
    }

    Fred::Poll::CreateUpdateObjectPollMessage(
        domain.data_.info_domain_data.historyid
    ).exec(ctx);

    Database::Result ids2_res = ctx.get_conn().exec(
        "SELECT id AS count_ "
        "   FROM message "
    );

    int new_message_id = -1;
    std::vector<int> ids_after;
    for(Database::Result::Iterator it = ids2_res.begin();
        it != ids2_res.end();
        ++it
    ) {
        ids_after.push_back(
            static_cast<int>((*it)["count_"])
        );

        if( std::find(ids_before.begin(), ids_before.end(), *ids_after.rbegin())
            == ids_before.end()
        ) {
            new_message_id = *ids_after.rbegin();
        }
    }

    BOOST_CHECK_MESSAGE(new_message_id != -1, "SOMETHING IS TERRIBLY WRONG");
    BOOST_CHECK_EQUAL(ids_before.size() + 1, ids_after.size());

    Database::Result message_res = ctx.get_conn().exec_params(
        "SELECT seen "
        "   FROM message "
        "   WHERE id=$1::integer",
        Database::query_param_list
            (new_message_id)
    );

    BOOST_CHECK_EQUAL(message_res.size(), 1);
    BOOST_CHECK_EQUAL(static_cast<bool>(message_res[0]["seen"]), false);

    Database::Result polleppaction_res = ctx.get_conn().exec_params(
        "SELECT msgid, objid "
        "   FROM poll_eppaction "
        "   WHERE msgid=$1::integer",
        Database::query_param_list
            (new_message_id)
    );

    BOOST_CHECK_EQUAL(polleppaction_res.size(), 1);
    BOOST_CHECK_EQUAL(static_cast<unsigned long long>(polleppaction_res[0]["objid"]), domain.data_.info_domain_data.historyid);

    ctx.commit_transaction();
}

/**
 @test
 executing TestCreateUpdateObjectPollMessage with history_ids of all registry object types

 @pre existing samples of all registry object types
 @post correct messagetype present poll_eppaction tables or correct exception thrown
 */
BOOST_AUTO_TEST_CASE( test_correct_type_specific_data)
{

    for(int i=0; i<3; ++i) {
        Fred::OperationContext ctx;

        Database::Result ids_res = ctx.get_conn().exec(
            "SELECT id AS count_ "
            "   FROM message "
        );

        std::vector<int> ids_before;
        for(Database::Result::Iterator it = ids_res.begin();
            it != ids_res.end();
            ++it
        ) {
            ids_before.push_back(
                static_cast<int>((*it)["count_"])
            );
        }
        setup_domain domain;
        setup_keyset keyset;
        setup_nsset nsset;

        switch(i) {
            case 0:

                Fred::Poll::CreateUpdateObjectPollMessage(
                    domain.data_.info_domain_data.historyid
                ).exec(ctx);
                break;
            case 1:
                Fred::Poll::CreateUpdateObjectPollMessage(
                    keyset.data_.info_keyset_data.historyid
                ).exec(ctx);
                break;
            case 2:
                Fred::Poll::CreateUpdateObjectPollMessage(
                    nsset.data_.info_nsset_data.historyid
                ).exec(ctx);
                break;
        }
        Database::Result ids2_res = ctx.get_conn().exec(
            "SELECT id AS count_ "
            "   FROM message "
        );

        int new_message_id = -1;
        std::vector<int> ids_after;
        for(Database::Result::Iterator it = ids2_res.begin();
            it != ids2_res.end();
            ++it
        ) {
            ids_after.push_back(
                static_cast<int>((*it)["count_"])
            );

            if( std::find(ids_before.begin(), ids_before.end(), *ids_after.rbegin())
                == ids_before.end()
            ) {
                new_message_id = *ids_after.rbegin();
            }
        }

        BOOST_CHECK_MESSAGE(new_message_id != -1, "SOMETHING IS TERRIBLY WRONG");
        BOOST_CHECK_EQUAL(ids_before.size() + 1, ids_after.size());

        Database::Result message_res = ctx.get_conn().exec_params(
            "SELECT mt.name     AS msgtype_name_ "
            "   FROM message AS m "
            "       JOIN messagetype AS mt "
            "           ON m.msgtype = mt.id "
            "   WHERE m.id=$1::integer",
            Database::query_param_list
                (new_message_id)
        );

        switch(i) {
            case 0:
                BOOST_CHECK_EQUAL(static_cast<std::string>(message_res[0]["msgtype_name_"]), Fred::Poll::UPDATE_DOMAIN);
                break;
            case 1:
                BOOST_CHECK_EQUAL(static_cast<std::string>(message_res[0]["msgtype_name_"]), Fred::Poll::UPDATE_KEYSET);
                break;
            case 2:
                BOOST_CHECK_EQUAL(static_cast<std::string>(message_res[0]["msgtype_name_"]), Fred::Poll::UPDATE_NSSET);
                break;
        }

        ctx.commit_transaction();
    }

    bool caught_the_right_exception = false;
    try {
        Fred::OperationContext ctx;

        setup_contact contact;
        Fred::Poll::CreateUpdateObjectPollMessage(
            contact.data_.info_contact_data.historyid
        ).exec(ctx);

        ctx.commit_transaction();
    } catch(const Fred::Poll::CreatePollMessage::Exception& e) {
        if(e.is_set_poll_message_type_not_found()) {
            caught_the_right_exception = true;
        }
    }

    BOOST_CHECK_EQUAL(caught_the_right_exception, true);
}

/**
 @test
 executing CreateUpdateObjectPollMessage with nonexistent history_id and checking thrown exception

 @pre nonexistent object history_id
 @post exception is thrown and has correct flag set
 */
BOOST_AUTO_TEST_CASE( test_nonexistent_historyid )
{
    setup_nonexistent_object_historyid nonexist_historyid;

    Fred::OperationContext ctx;

    bool correct_exception_caught = false;
    try {
        Fred::Poll::CreateUpdateObjectPollMessage(
            nonexist_historyid.history_id_
        ).exec(ctx);
    } catch(const Fred::Poll::CreateUpdateObjectPollMessage::Exception& e) {
        if(e.get_object_history_not_found()) {
            correct_exception_caught = true;
        }
    }

    BOOST_CHECK_EQUAL(correct_exception_caught, true);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();
