create table if not exists statement_tracker(
    no_of_DML_queries_ran int default 0,
    no_of_DDL_queries_ran int default 0
);

COMMENT ON EXTENSION statement_tracker IS 'An extension for logging queries';

CREATE FUNCTION dummy() RETURNS void AS
'$libdir/statement_tracker', 'dummy' LANGUAGE C STRICT;
