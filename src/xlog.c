/*
 * ========================================= Transaction Log Manager============================================================
 * TinyDb transactin log is Write-Ahead Log (WAL). Transaction Log records all transactions and the database modifications 
 * that are made by each transactin. The transactin log is a critical component of the database and, if there`s a system failure, 
 * the transactin log might be required to bring your database back to a consistent state.
 * The Transaction log manager basically supports three functions:
 * (1) Supports Transaction Roll Back.
 * (2) Supports recovery data when server restart up.
 * (3) Support Transaction replication in distributed cluster.
 * ==============================================================================================================================
 * */
