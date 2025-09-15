extern "C" {
    #include "postgres.h"
    #include "fmgr.h"
    #include "executor/spi.h"
    #include "utils/elog.h"
    #include "executor/executor.h"
    #include "tcop/utility.h"
    #include "nodes/nodes.h"
    #include "nodes/parsenodes.h"

    PG_MODULE_MAGIC;
}

#include<statement_tracker.h>

extern "C" void _PG_init(void){

    elog(LOG,"Extension loaded");

    hook_holder_ExecutorEnd = ExecutorEnd_hook;
    ExecutorEnd_hook = queryFetcherForDML;

    hook_holder_process_utility = ProcessUtility_hook;
    ProcessUtility_hook = queryFetcherForDDL;
}

extern "C" void _PG_fini(void){
    elog(LOG,"Extension unloaded");
    ExecutorEnd_hook = hook_holder_ExecutorEnd;
    ProcessUtility_hook = hook_holder_process_utility;
}

static void queryFetcherForDML(QueryDesc* queryDesc){

    std::string query = queryDesc->sourceText;
    std::string first_word = get_first_word(query);

    if(query.find("statement_tracker") != std::string::npos){
        return;
    }

    std::transform(first_word.begin(), first_word.end(), first_word.begin(),
        [](unsigned char c) { return std::tolower(c); }); 
    
    if(first_word == "select") return;

    updateDB("DML");

    if(hook_holder_ExecutorEnd != NULL) hook_holder_ExecutorEnd(queryDesc);

}

static void queryFetcherForDDL(
    PlannedStmt *pstmt, const char *queryString,
    bool readOnlyTree,
    ProcessUtilityContext context, ParamListInfo params,
    QueryEnvironment *queryEnv,
    DestReceiver *dest, QueryCompletion *qc
){

    // Code for sql to update
    updateDB("DDL");

    if(hook_holder_process_utility != NULL) hook_holder_process_utility(pstmt,queryString,readOnlyTree,context,params,queryEnv,dest,qc);
    // standard_ProcessUtility();
}


static std::string get_first_word(std::string query){
    unsigned int position = query.find(' ');
    if(position == std::string::npos) return query;
    return query.substr(0,position);
}

static void updateDB(std::string typeOf){
    
    if(typeOf != "DDL" && typeOf != "DML"){
        elog(LOG,"Not a valid statement");
        return;
    }

    SPI_connect();

    int result;
    
    if(typeOf == "DDL"){
        result = SPI_exec("UPDATE statement_tracker SET no_of_DDL_queries_ran = no_of_DDL_queries_ran+1;",0);
    }
    else result = SPI_exec("UPDATE statement_tracker SET no_of_DML_queries_ran = no_of_DML_queries_ran+1;",0);

    if(result != SPI_OK_UPDATE){
        elog(LOG,"Unsuccessful in updating the value");
    }

    SPI_finish();

}

extern "C"{
    PG_FUNCTION_INFO_V1(dummy);

    Datum
    dummy(PG_FUNCTION_ARGS){
        elog(LOG, "Dummy Function");
        PG_RETURN_VOID();
    }
}