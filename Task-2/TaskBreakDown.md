### Create an postgres extension that read the command ran on the DB and differentitate the queries as DDL, DML, DQL

#### My approach :
- Set a project extension
- Know how to read the query ran on db
    - use hooks --> Executor hook --> Override to do your instrutions and call the regular instruction at your overrided place
    - We are going to use executorEnd_ hook.
- Then differentiate that into type of Query
    - As we use the executorEnd_ hook, we only get the queries without error and they mostly will be executed ones
    - Use the trim() and then check the first word and you can do it.
    - make that to be in order.
- Log that into a file
    - Learn about file handling
    - use text file


### Create an extension that read the command ran on the DB and differnetiate type of command and increment the count of times it is executed.
- setup project
- learn how to execute the sql commands from the extension
- on the first time of extension run, check for table that we are gng to increment, if not available create // done
    - describe your schema of the table // done
- everytime the statement is executed, run the sql for increament the table's row

#### Doubts
