COMMENT ON EXTENSION typequerylog IS 'An extension for logging queries';

CREATE FUNCTION dummy() RETURNS void AS
'$libdir/typequerylog', 'dummy' LANGUAGE C STRICT;
