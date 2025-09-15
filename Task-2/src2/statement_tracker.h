#include <string>
#include <algorithm>

static ExecutorEnd_hook_type hook_holder_ExecutorEnd = NULL;
static ProcessUtility_hook_type hook_holder_process_utility = NULL;

static void queryFetcherForDML(QueryDesc * query);
static void queryFetcherForDDL(
    PlannedStmt *pstmt, const char *queryString,
    bool readOnlyTree,
    ProcessUtilityContext context, ParamListInfo params,
    QueryEnvironment *queryEnv,
    DestReceiver *dest, QueryCompletion *qc
);
static std::string get_first_word(std::string query);
static void updateDB(std::string typeOf);
