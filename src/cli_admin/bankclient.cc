/*
 *  Copyright (C) 2008  CZ.NIC, z.s.p.o.
 *
 *  This file is part of FRED.
 *
 *  FRED is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
 *
 *  FRED is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with FRED.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "simple.h"
#include "bankclient.h"
#include "commonclient.h"
#include "register/bank.h"
#include "register/register.h"

namespace Admin {

BankClient::BankClient()
{
    m_options = new boost::program_options::options_description(
            "Bank related options");
    m_options->add_options()
        addOpt(BANK_ONLINE_LIST_NAME)
        addOpt(BANK_STATEMENT_LIST_NAME)
        addOpt(BANK_ADD_ACCOUNT_NAME)
        addOpt(BANK_ADD_ACCOUNT_HELP_NAME)
        addOpt(BANK_SHOW_OPTS_NAME);

    m_optionsInvis = new boost::program_options::options_description(
            "Bank related sub options");
    m_optionsInvis->add_options()
        addOptStr(BANK_ACCOUNT_NUMBER_NAME)
        addOptStr(BANK_ACCOUNT_NAME_NAME)
        addOptStr(BANK_BANK_CODE_NAME)
        addOptUInt(BANK_ZONE_ID_NAME)
        addOptStr(BANK_ZONE_NAME_NAME);
}
BankClient::BankClient(
        std::string connstring,
        std::string nsAddr) : BaseClient(connstring, nsAddr)
{
    m_db.OpenDatabase(connstring.c_str());
    m_options = NULL;
    m_optionsInvis = NULL;
}

BankClient::~BankClient()
{
    delete m_options;
    delete m_optionsInvis;
}

void
BankClient::init(
        std::string connstring,
        std::string nsAddr,
        Config::Conf &conf)
{
    BaseClient::init(connstring, nsAddr);
    m_db.OpenDatabase(connstring.c_str());
    m_conf = conf;
}

boost::program_options::options_description *
BankClient::getVisibleOptions() const
{
    return m_options;
}

boost::program_options::options_description *
BankClient::getInvisibleOptions() const
{
    return m_optionsInvis;
}

void
BankClient::show_opts() const
{
    std::cout << *m_options << std::endl;
    std::cout << *m_optionsInvis << std::endl;
}

int
BankClient::online_list()
{
    std::ofstream stdout("/dev/stdout",std::ios::out);   

    std::auto_ptr<Register::Banking::Manager> bankMan(
            Register::Banking::Manager::create(&m_db));
    std::auto_ptr<Register::Banking::OnlinePaymentList> statList(
            bankMan->createOnlinePaymentList());
    statList->reload();
    statList->exportXML(stdout);
    return 0;
}

int
BankClient::statement_list()
{
    std::ofstream stdout("/dev/stdout",std::ios::out);   

    std::auto_ptr<Register::Banking::Manager> bankMan(
            Register::Banking::Manager::create(&m_db));
    std::auto_ptr<Register::Banking::StatementList> statList(
            bankMan->createStatementList());
    statList->reload();
    statList->exportXML(stdout);

    return 0;
}

void
BankClient::add_bank_account()
{
    std::string account_number = m_conf.get<std::string>(BANK_ACCOUNT_NUMBER_NAME);
    std::string account_name;
    if (m_conf.hasOpt(BANK_ACCOUNT_NAME_NAME)) {
        account_name = m_conf.get<std::string>(BANK_ACCOUNT_NAME_NAME);
    }
    std::string bank_code = m_conf.get<std::string>(BANK_BANK_CODE_NAME);
    std::auto_ptr<Register::Banking::Manager>
        bankMan(Register::Banking::Manager::create(&m_db));
    bool retval = true;
    if (m_conf.hasOpt(BANK_ZONE_ID_NAME)) {
        Database::ID zoneId = m_conf.get<unsigned int>(BANK_ZONE_ID_NAME);
        retval = bankMan->insertBankAccount(zoneId, account_number, account_name, bank_code);
    } else if (m_conf.hasOpt(BANK_ZONE_NAME_NAME)) {
        std::string zoneName = m_conf.get<std::string>(BANK_ZONE_NAME_NAME);
        retval = bankMan->insertBankAccount(zoneName, account_number, account_name, bank_code);
    }
    if (!retval) {
        std::cout << "Error occured!" << std::endl;
    }
}

void
BankClient::add_bank_account_help()
{
    std::cout << 
        "** Add new bank account **\n\n"
        "  $ " << g_prog_name << " --" << BANK_ADD_ACCOUNT_NAME << " \\\n"
        "    --" << BANK_ZONE_ID_NAME << "=<zone_id> | \\\n"
        "    --" << BANK_ZONE_NAME_NAME << "=<zone_fqdn> \\\n"
        "    --" << BANK_ACCOUNT_NUMBER_NAME << "=<account_number> \\\n"
        "    --" << BANK_BANK_CODE_NAME << "=<bank_code> \\\n"
        "    [--" << BANK_ACCOUNT_NAME_NAME << "=<account_name>]\n"
        << std::endl;
}

} // namespace Admin;

