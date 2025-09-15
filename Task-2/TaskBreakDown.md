### Create an postgres extension that read the queries ran on the DB and differentitate the queries as DDL, DML, DQL, DCL, TCL

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

#### Doubts
