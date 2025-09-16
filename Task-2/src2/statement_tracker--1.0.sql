create table if not exists statement_tracker(
    no_of_DML_queries_ran int default 0,
    no_of_DDL_queries_ran int default 0
);


INSERT INTO statement_tracker (no_of_DML_queries_ran, no_of_DDL_queries_ran)
SELECT 0, 0
WHERE NOT EXISTS (SELECT 1 FROM statement_tracker);


COMMENT ON EXTENSION statement_tracker IS 'An extension for logging queries';

CREATE FUNCTION dummy() RETURNS void AS
'$libdir/statement_tracker', 'dummy' LANGUAGE C STRICT;