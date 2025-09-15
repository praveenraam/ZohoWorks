
// Lib
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cctype> 
#include <stdlib.h>

static ExecutorEnd_hook_type hook_holder_ExecutorEnd = NULL;
static ProcessUtility_hook_type hook_holder_process_utility = NULL;

// Function Declaration
static void queryFetcherForDML(QueryDesc * queryDesc);
static void queryFetcherForDDL(
    PlannedStmt *pstmt, const char *queryString,
    bool readOnlyTree,
    ProcessUtilityContext context, ParamListInfo params,
    QueryEnvironment *queryEnv,
    DestReceiver *dest, QueryCompletion *qc
);
static std::string queryTypeFinder(std::string query);
static std::string get_first_word(std::string query);