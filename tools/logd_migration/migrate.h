#ifndef _MIGRATE_H_
#define _MIGRATE_H_

#include <iostream>
#include <fstream>
#include <map>


#include "db/transaction.h"

#include "src/register/request_impl.h"

#include "util/types/id.h"

// needed becase of pool_subst
#include "m_epp_parser.h"

#define ALLOC_STEP 4

using namespace Database;
using namespace Register::Logger;

typedef unsigned long long TID;


#endif

