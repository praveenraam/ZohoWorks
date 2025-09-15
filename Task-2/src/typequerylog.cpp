extern "C"{
    #include "postgres.h"
    #include "fmgr.h"
    #include "executor/executor.h"
    #include "executor/spi.h"
    #include "tcop/utility.h"
    #include "nodes/nodes.h"
    #include "nodes/parsenodes.h"
    #include "utils/elog.h"

    PG_MODULE_MAGIC;
}

#include "typequerylog.h"

// Const value declaration
const std::string PATH = "/home/praveen-pt7975/Documents/Extension/TypeQueryLog/Log.log";

// Init
extern "C" void _PG_init(void){
    elog(LOG, "Extension loaded, hook installed");

    hook_holder_ExecutorEnd = ExecutorEnd_hook;
    ExecutorEnd_hook = queryFetcherForDML;

    hook_holder_process_utility = ProcessUtility_hook;
    ProcessUtility_hook = queryFetcherForDDL;
}
// close
extern "C" void _PG_fini(void){
    ExecutorEnd_hook = hook_holder_ExecutorEnd;
    ProcessUtility_hook = hook_holder_process_utility;
}


static void queryFetcherForDML(QueryDesc* queryDesc){
    std::ofstream log_file(PATH, std::ios::app);
    elog(LOG,"Function executing");

    if(!log_file.is_open()){
        elog(LOG, "Not able to log the Statements");
        return;
    }

    time_t my_time = time(NULL);
    std::string current_time = ctime(&my_time);
    current_time.erase(std::remove(current_time.begin(), current_time.end(), '\n'), current_time.end());
    

    std::string typeFound = queryTypeFinder(queryDesc->sourceText);
    log_file << "[" << current_time << "] " << queryDesc->sourceText << " Type : " <<  typeFound << "\n";

    elog(LOG,"Query to execute : %s",queryDesc->sourceText);

    log_file.close();
}

static void queryFetcherForDDL(
    PlannedStmt *pstmt, const char *queryString,
    bool readOnlyTree,
    ProcessUtilityContext context, ParamListInfo params,
    QueryEnvironment *queryEnv,
    DestReceiver *dest, QueryCompletion *qc) {
    
        std::ofstream log_file(PATH, std::ios::app);
        elog(LOG,"Function executing DDL");

        if(!log_file.is_open()){
            elog(LOG, "Not able to log the Statements");
            return;
        }

        time_t my_time = time(NULL);
        std::string current_time = ctime(&my_time);
        current_time.erase(std::remove(current_time.begin(), current_time.end(), '\n'), current_time.end());

        log_file << "[" << current_time << "] " << queryString << " Type : DDL" << "\n";
        elog(LOG,"Query to execute : %s",queryString);

        log_file.close();

        if(hook_holder_process_utility != NULL) hook_holder_process_utility(pstmt,queryString,readOnlyTree,context,params,queryEnv,dest,qc);
    }


static std::string queryTypeFinder(std::string query){
    
    query.erase(0,query.find_first_not_of(" \n\r\t"));

    std::string first_word = get_first_word(query);

    std::transform(first_word.begin(), first_word.end(), first_word.begin(),
        [](unsigned char c) { return std::tolower(c); }); // 

    if(first_word == "insert" || first_word == "update" || first_word == "delete"){
        return "DML";
    }

    return "DQL";
}

static std::string get_first_word(std::string query){
    unsigned int position = query.find(' ');
    if(position == std::string::npos) return query;
    return query.substr(0,position);
}

// Dummy data for loading 
extern "C" {
    PG_FUNCTION_INFO_V1(dummy);

    Datum
    dummy(PG_FUNCTION_ARGS)
    {
        elog(LOG, "Dummy function called");
        PG_RETURN_VOID();
    }
}