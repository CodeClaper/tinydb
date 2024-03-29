#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef DATA_H
#define DATA_H

#define PAGE_SIZE 4096
#define MAX_TABLE_PAGE 10000
#define MAX_COLUMN_SIZE 256    // max column size
#define MAX_COLUMN_NAME_LEN 30 // max column name length
#define MAX_MULTI_TABLE_NUM 30 // max multi-table number.
#define BUFF_SIZE 1024
#define SPOOL_SIZE 1024   /* Spool buffer size. */

#define MAX_COLUMN_NAME_LEN 30 // max column name length
#define MAX_TABLE_NAME_LEN 30

#define MAX_INT_VALUE   (1 << 31) - 1
#define MAX_UINT_VALUE  (1 << 32) - 1
#define MAX_LONG_VALUE  (1 << 63) - 1

#define CREATED_XID_COLUMN_NAME  "created_xid"
#define EXPIRED_XID_COLUMN_NAME  "expired_xid"

/* System Data type. */
typedef enum SysDataType{
    SDT_VOID,
    SDT_STRING,
    SDT_INT,
    SDT_BOOL,
    SDT_FLOAT,
    SDT_DOUBLE,
    SDT_TIME_T,
    SDT_POINTER,
    SDT_COLUMN_NODE,
    SDT_COLUMN_SET_NODE,
    SDT_FUNCTION_VALUE_NODE,
    SDT_FUNCTION_NODE,
    SDT_CALCULATE_NODE,
    SDT_SELECT_ITEMS_NODE,
    SDT_SELECTION_NODE,
    SDT_SCALAR_EXP_SET_NODE,
    SDT_SCALAR_EXP_NODE,
    SDT_COLUMN_DEF_NODE,
    SDT_COLUMN_DEF_SET_NODE,
    SDT_PRIMARY_KEY_NODE,
    SDT_REFER_VALUE,
    SDT_VALUE_ITEM_NODE,
    SDT_VALUE_ITEM_SET_NODE,
    SDT_ASSIGNMENT_NODE,
    SDT_ASSIGNMENT_SET_NODE,
    SDT_CONDITION_NODE,
    SDT_PREDICATE_NODE,
    SDT_COMPARISON_NODE,
    SDT_LIKE_NODE,
    SDT_IN_NODE,
    SDT_LIMIT_NODE,
    SDT_TABLE_REF_NODE,
    SDT_TABLE_REF_SET_NODE,
    SDT_FROM_CLAUSE_NODE,
    SDT_WHERE_CLAUSE_NODE,
    SDT_TABLE_EXP_NODE,
    SDT_CREATE_TABLE_NODE,
    SDT_DROP_TABLE_NODE,
    SDT_SELECT_NODE,
    SDT_INSERT_NODE,
    SDT_UPDATE_NODE,
    SDT_DELETE_NODE,
    SDT_DESCRIBE_NODE,
    SDT_SHOW_NODE,
    SDT_AST_NODE,
    SDT_STATEMENT,
    SDT_STATEMENTS,
    SDT_PAGER,
    SDT_META_COLUMN,
    SDT_META_TABLE,
    SDT_TABLE,
    SDT_TABLE_CACHE,
    SDT_TABLE_BUFFER_ENTRY,
    SDT_TABLE_BUFFER,
    SDT_CURSOR,
    SDT_KEY_VALUE,
    SDT_MAP,
    SDT_MAP_LIST,
    SDT_ROW,
    SDT_QUERY_PARAM,
    SDT_SELECT_RESULT,
    SDT_TABLE_LIST,
    SDT_MENTRY,
    SDT_MHASH_TABLE,
    SDT_SESSION,
    SDT_CONF,
    SDT_REFER,
    SDT_REFER_UPDATE_ENTITY,
    SDT_INSERT_EXECUTE_RESULT,
    SDT_DB_RESULT,
    SDT_DB_RESULT_SET,
    SDT_LOCK_HANDLE,
    SDT_LOCK_TABLE,
    SDT_TRANSACTION_HANDLE,
    SDT_TRANSACTION_TABLE,
    SDT_LOG_ENTRY,
    SDT_LOG_TABLE,
    SDT_XLOG_ENTRY,
    SDT_XLOG_TABLE,
    SDT_ALIAS_ENTRY,
    SDT_ALIAS_MAP
}SysDataType;

static char *SYS_DATA_TYPE_NAMES[] = { \
   "VOID",\
   "STRING",\ 
   "INT",\ 
   "BOOL",\
   "FLOAT",\
   "DOUBLE",\
   "TIME_T",\
   "POINTER",\
   "COLUMN_NODE",\
   "COLUMN_SET_NODE",\
   "FUNCTION_VALUE_NODE",\
   "FUNCTION_NODE",\
   "CALCULATE_NODE",\
   "SELECT_ITEMS_NODE",\
   "SELECTION_NODE",\
   "SCALAR_EXP_SET_NODE",\
   "SCALAR_EXP_NODE",\
   "COLUMN_DEF_NODE",\
   "COLUMN_DEF_SET_NODE",\
   "PRIMARY_KEY_NODE",\
   "REFER_VALUE",\
   "VALUE_ITEM_NODE",\
   "VALUE_ITEM_SET_NODE",\
   "ASSIGNMENT_NODE",\
   "ASSIGNMENT_SET_NODE",\
   "CONDITION_NODE",\
   "PREDICATE_NODE",\
   "COMPARISON_NODE",\
   "LIKE_NODE",\
   "IN_NODE",\
   "LIMIT_NODE",\
   "TABLE_REF_NODE",\
   "TABLE_REF_SET_NODE",\
   "FROM_CLAUSE_NODE",\
   "WHERE_CLAUSE_NODE",\
   "TABLE_EXP_NODE",\
   "CREATE_TABLE_NODE",\
   "DROP_TABLE_NODE",\
   "SELECT_NODE",\
   "INSERT_NODE",\
   "UPDATE_NODE",\
   "DELETE_NODE",\
   "DESCRIBE_NODE",\
   "SHOW_NODE",\
   "AST_NODE",\
   "STATEMENT",\
   "STATEMENTS",\
   "PAGER",\
   "META_COLUMN",\
   "META_TABLE",\
   "TABLE",\
   "TABLE_CACHE",\
   "TABLE_BUFFER_ENTRY",\
   "TABLE_BUFFER",\
   "CURSOR",\
   "KEY_VALUE",\
   "MAP",\
   "MAP_LIST",\
   "ROW",\
   "QUERY_PARAM",\
   "SELECT_RESULT",\
   "TABLE_LIST",\
   "MENTRY",\
   "MHASH_TABLE",\
   "SESSION",\
   "CONF",\
   "REFER",\
   "REFER_UPDATE_ENTITY",\
   "INSERT_EXECUTE_RESULT",\
   "DB_RESULT",\
   "DB_RESULT_SET",\
   "LOCK_HANDLE",\
   "LOCK_TABLE",\
   "TRANSACTION_HANDLE",\
   "TRANSACTION_TABLE",\
   "LOG_ENTRY",\
   "LOG_TABLE",\
   "XLOG_ENTRY",\
   "XLOG_TABLE",\
   "ALIAS_ENTRY", \
   "ALIAS_MAP" \
};

/* CompareType */
typedef enum { O_EQ, O_NE, O_GT, O_GE, O_LT, O_LE } CompareType;

/* DataType */
typedef enum DataType {T_UNKNOWN, T_BOOL, T_CHAR, T_INT, T_LONG, T_DOUBLE, T_FLOAT, T_STRING, T_DATE, T_TIMESTAMP, T_REFERENCE, T_ROW } DataType;

/* DataTypeNames */
static char *DATA_TYPE_NAMES[] = \
    {"unknown", "bool",  "char",  "int", "long", "double", "float", "string", "date", "timestamp",  "reference"};

/* FunctionType */
typedef enum { F_COUNT, F_MAX, F_MIN, F_SUM, F_AVG } FunctionType;

/* ConnType */
typedef enum { C_OR, C_AND, C_NONE} ConnType; // connector type

/* FunctionValueType */
typedef enum { V_INT, V_COLUMN, V_ALL } FunctionValueType; // value type.

/* SelectItemType */
typedef enum { SELECT_COLUMNS, SELECT_FUNCTION, SELECT_ALL } SelectItemType;

/* ConditionNodeType */
typedef enum { LOGIC_CONDITION, EXEC_CONDITION } ConditionNodeType;

/* ShowNodeType */
typedef enum { SHOW_TABLES, SHOW_MEMORY } ShowNodeType;

/* StatementType */
typedef enum { 
    UNKONWN_STMT,
    BEGIN_TRANSACTION_STMT, 
    COMMIT_TRANSACTION_STMT, 
    ROLLBACK_TRANSACTION_STMT, 
    CREATE_TABLE_STMT, 
    SELECT_STMT, 
    INSERT_STMT, 
    UPDATE_STMT, 
    DELETE_STMT, 
    DESCRIBE_STMT, 
    SHOW_STMT, 
    DROP_TABLE_STMT 
} StatementType; // statement type

/* Tansaction operation type. */
typedef enum { TR_SELECT, TR_INSERT, TR_DELETE, TR_UPDATE } TransOpType;

/* NodeType */
typedef enum { UNKNOWN_NODE, LEAF_NODE, INTERNAL_NODE } NodeType;

/* ExecuteResult */
typedef enum { 
    EXECUTE_SUCCESS = 200, 
    EXECUTE_FAIL, 
    EXECUTE_SQL_ERROR, 
    EXECUTE_TABLE_NOT_EXIST_FAIL, 
    EXECUTE_TABLE_CREATE_FAIL, 
    EXECUTE_TABLE_DROP_FAIL, 
    EXECUTE_TABLE_OPEN_FAIL,
    EXECUTE_DUPLICATE_COLUMN,
    EXECUTE_NOT_MATCH_COLUMN,
    EXECUTE_UNKNOWN_COLUMN,
    EXECUTE_DUPLICATE_KEY,
    EXECUTE_EXCEEDED_MAX_COLUMN,
    EXECUTE_OPEN_DATABASE_FAIL,
    EXECUTE_RW_DATABASE_FAIL,
    EXECUTE_CONVERT_DATA_TYPE_FAIL
} ExecuteStatus;

/* LogLevel */
typedef enum { 
    TRACE,      /* Show detail infomation. */ 
    DEBUGER,    /* Show infomation to help debuger,*/
    INFO,       /* DB running Infomation. */
    SUCCESS,    /* Success result to client. */
    WARN,       /* For unexpected messages including sql syntaxt error, reapeated begin transaction or commit .etc. */ 
    ERROR,      /* Abort transaction. */
    FATAL,      /* Abort process. */
    PANIC       /* Shut down the database. */
} 
LogLevel;

/* Lock level. */
typedef enum { LEVEL_ROW, LEVEL_TABLE } LockLevel;

/* Lock mode. */
typedef enum LockMode { RD_MODE, WR_MODE } LockMode;

/* The Four Transaction Isolation Level. */
typedef enum { READ_UNCOMMITTED, READ_COMMITTED, REPEATABLE_READ, SERIALIZABLE } TransIsolationLevel;

/* DDL Type. */
typedef enum DDLType { DDL_INSERT, DDL_DELETE } DDLType;

/* ColumnNode */
typedef struct ColumnNode {
    char *column_name;
    char *range_variable;
    bool *has_sub_column;
    struct ColumnNode *sub_column;
    struct ScalarExpSetNode *scalar_exp_set;
} ColumnNode;

/* ColumnSetNode */
typedef struct ColumnSetNode {
  ColumnNode **columns;
  uint32_t size;
} ColumnSetNode;

/* FunctionValueType */
typedef struct FunctionValueNode {
  FunctionValueType value_type;
  union {
    int32_t i_value;
    ColumnNode *column;
  };
} FunctionValueNode;

/* FunctionNode */
typedef struct FunctionNode {
    FunctionType type;
    FunctionValueNode *value;
} FunctionNode;

/* CalculateType */
typedef enum CalculateType {
    CAL_ADD,
    CAL_SUB,
    CAL_MUL,
    CAL_DIV
} CalculateType;

/* CalculateNode */
typedef struct CalculateNode {
    CalculateType type;
    struct ScalarExpNode *left;
    struct ScalarExpNode *right;
} CalculateNode;

/* SelectItemsNode */
typedef struct {
    ColumnSetNode *column_set_node;
    FunctionNode *function_node;
    SelectItemType type;
} SelectItemsNode;

/* SelectionNode */
typedef struct SelectionNode {
    bool all_column;
    struct ScalarExpSetNode *scalar_exp_set;
} SelectionNode;

/* ScalarExprSetNode */
typedef struct ScalarExpSetNode {
    uint32_t size;
    struct ScalarExpNode **data;
} ScalarExpSetNode;

/* ScalarExpType */
typedef enum ScalarExpType {
    SCALAR_CALCULATE,
    SCALAR_COLUMN,
    SCALAR_FUNCTION,
    SCALAR_VALUE
} ScalarExpType;

/* ScalarExpNode */
typedef struct ScalarExpNode {
    ScalarExpType type;
    union {
        CalculateNode *calculate;
        ColumnNode *column;
        FunctionNode *function;
        struct ValueItemNode *value;
    };
    char *alias;
} ScalarExpNode;

/* ColumnDefNode */
typedef struct {
    ColumnNode *column;
    DataType data_type;
    bool is_define_len;
    uint32_t data_len;
    char *table_name;
    bool is_primary;
    bool allow_null;
} ColumnDefNode;

/* ColumnDefSetNode */
typedef struct {
    ColumnDefNode **column_defs;
    uint32_t size;
} ColumnDefSetNode;

/* PrimaryKeyNode */
typedef struct {
    ColumnNode *column;
} PrimaryKeyNode;

/* ReferFetchType */
typedef enum ReferFetchType {
    DIRECTLY = 1,
    INDIRECTLY
}ReferFetchType;

/* ReferValue */
typedef struct ReferValue {
    ReferFetchType type;
    union {
        /* For directly. */
        struct ValueItemSetNode *nest_value_item_set;
        /* For indirectly. */
        struct ConditionNode *condition;
    };
} ReferValue;

/* ValueItemNode */
typedef struct ValueItemNode {
    DataType data_type;
    union {
        /* T_INT, T_LONG */
        int64_t i_value;
        /* T_BOOL */
        bool b_value;
        /* T_CHAR, T_STRING */
        char *s_value;
        /* T_FLOAT */
        float f_value;
        /* T_DOUBLE */
        double d_value;
        /* T_TIMESTAMP, T_DATE */
        time_t t_value;
        /* T_REFERENCE */
        ReferValue *r_value;
    } value;
} ValueItemNode;

/* ValueItemSetNode */
typedef struct ValueItemSetNode {
    ValueItemNode **value_item_node;
    uint32_t num;
} ValueItemSetNode;

/* AssignmentNode */
typedef struct {
    ColumnNode *column;
    ValueItemNode *value;
} AssignmentNode;

/* AssignmentSetNode */
typedef struct {
    AssignmentNode **assignment_node;
    uint32_t num;
} AssignmentSetNode;

/* ConditionNode */
typedef struct ConditionNode {
    ConnType conn_type;
    struct ConditionNode *left;
    struct ConditionNode *right;
    struct PredicateNode *predicate;
} ConditionNode;

/* PredicateType */
typedef enum PredicateType {
    PRE_COMPARISON,
    PRE_LIKE,
    PRE_IN
} PredicateType;

/* PredicateNode */
typedef struct PredicateNode {
    PredicateType type;
    union {
        struct ComparisonNode *comparison;
        struct LikeNode *like;
        struct InNode *in;
    };
} PredicateNode;

/* ComparisonNode */
typedef struct ComparisonNode {
    CompareType type;
    ColumnNode *column;
    ScalarExpNode *value;
} ComparisonNode;

/* LikeNode */
typedef struct LikeNode {
    ColumnNode *column;
    ValueItemNode *value;
} LikeNode;

/* InNode */
typedef struct InNode {
    ColumnNode *column;
    ValueItemSetNode *value_set;
} InNode;

/* LimitNode */
typedef struct LimitNode {
    int32_t start;
    int32_t end;
} LimitNode;

/* TableRefNode. */
typedef struct TableRefNode {
    char *table;
    char *range_variable;
} TableRefNode;

/* TableRefSetNode. */
typedef struct TableRefSetNode {
    uint32_t size;
    TableRefNode **set;
} TableRefSetNode;

/* FromClauseNode. */
typedef struct FromClauseNode {
    TableRefSetNode *from;
} FromClauseNode;

/* WhereClauseNode. */
typedef struct WhereClauseNode {
    ConditionNode *condition; 
} WhereClauseNode;

/* TableExpNode */
typedef struct TableExpNode {
    FromClauseNode *from_clause;
    WhereClauseNode *where_clause;
} TableExpNode;

/* CreateTableNode */
typedef struct {
    char *table_name;
    ColumnDefSetNode *column_def_set_node;
    PrimaryKeyNode *primary_key_node;
} CreateTableNode;

/* DropTableNode */
typedef struct {
    char *table_name;
} DropTableNode;

/* SelectNode */
typedef struct {
    SelectionNode *selection;
    TableExpNode *table_exp;
} SelectNode;

/* InsertNode */
typedef struct {
    bool all_column;
    char *table_name;
    ColumnSetNode *columns_set_node;
    ValueItemSetNode *value_item_set_node;
} InsertNode;

/* UpdateNode */
typedef struct {
    char *table_name;
    AssignmentSetNode *assignment_set_node;
    WhereClauseNode *where_clause;
} UpdateNode;

/* DeleteNode */
typedef struct {
    char *table_name;
    ConditionNode *condition_node;
} DeleteNode;

/* DescribeNode */
typedef struct {
    char *table_name;
} DescribeNode;

/* ShowNode */
typedef struct {
    ShowNodeType type;
} ShowNode;

/* Statement */
typedef struct {
  StatementType statement_type;
  union {
        CreateTableNode *create_table_node;
        DropTableNode *drop_table_node;
        SelectNode *select_node;
        InsertNode *insert_node;
        UpdateNode *update_node;
        DeleteNode *delete_node;
        DescribeNode *describe_node;
        ShowNode *show_node;
  };
} Statement;

/* Statements */
typedef struct {
    uint32_t size;
    Statement **list;
} Statements;

/* Pager */
typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t size;
    void *pages[MAX_TABLE_PAGE];
} Pager;

/* MetaColumn */
typedef struct {
    char column_name[MAX_COLUMN_NAME_LEN];
    DataType column_type;
    char table_name[MAX_TABLE_NAME_LEN];
    uint32_t column_length;
    bool is_primary;
    bool sys_reserved; /* System reserved column, only visible for system. */
} MetaColumn;

/* MetaTable */
typedef struct MetaTable {
    char *table_name;
    MetaColumn **meta_column;
    uint32_t column_size;       /* size of column, excluding system reserved columns. */
    uint32_t all_column_size;   /* sizo of column, including system reserved columns. */
} MetaTable;

/* Table */
typedef struct Table {
    Pager *pager;
    uint32_t root_page_num;
    MetaTable *meta_table;
} Table;

/* TableCache */
typedef struct TableCache {
    Table **table_list;
    uint32_t size;
}TableCache;

/* TableBufferEntry */
typedef struct TableBufferEntry {
    Table *table;
    int64_t xid;
    int64_t tid;
} TableBufferEntry;

/* TableBuffer */
typedef struct TableBuffer {
    TableBufferEntry **buffer;
    uint32_t size;
} TableBuffer;


/* TableList */
typedef struct TableList {
  char **table_name_list;
  uint32_t count;
} TableList;

/* Cursor */
typedef struct Cursor {
    Table *table;
    uint32_t page_num;
    uint32_t cell_num;
} Cursor;

/* KeyValue */
typedef struct KeyValue {
    char *key;
    void *value;
    DataType data_type;
    char *table_name;
} KeyValue;

/* Map */
typedef struct Map {
    KeyValue **body;
    uint32_t size;
} Map;

typedef struct MapList {
    Map **data;
    uint32_t size;
} MapList;

/* Row */
typedef struct Row {
    void *key;
    char *table_name;
    KeyValue **data;
    uint32_t column_len;
} Row;

/* QueryParam */
typedef struct QueryParam {
    char *table_name;
    SelectionNode *selection;
    ConditionNode *condition_node;
    LimitNode *limit_node;
} QueryParam;

/* SelectResult */
typedef struct SelectResult {
    char *table_name;               /* Table name. */
    char *range_variable;           /* Range variable. */
    uint32_t row_size;              /* Row size. */
    int32_t row_index;              /* current row index. */
    Row **rows;                     /* Selected rows. */
    struct SelectResult *derived;   /* Derived select result, used for multi-table query. */
    bool last_derived;              /* Last derived flag. */
} SelectResult;

/* MEntry */
typedef struct MEntry {
    void *ptr;
    size_t size;
    SysDataType stype;
    struct MEntry *next;
} MEntry;

/* MHashTable */
typedef struct {
    MEntry **entry_list;
    uint32_t num;      /* number of entry list. */
    uint32_t capacity; /* capacity of table cell. */
} MHashTable;

/* Session */
typedef struct {
    int client;
    uint32_t frequency;
    uint32_t volumn;
    char spool[SPOOL_SIZE]; /* Store messsage pool. */
    int pindex;             /* Current spool position index. */
} Session;

/* Abount configuration. */
typedef struct {
    /* data */
    char *data_dir;     /* database file directory. */
    /* base */
    ushort port;        /* Server listening port. */
    /* log */
    char *log_dir;      /* log directory */
    LogLevel log_level; /* log level */
    /* transaction */
    TransIsolationLevel trans_iso_level;
} Conf;

/* Refer */
typedef struct Refer{
    char table_name[MAX_TABLE_NAME_LEN];
    int32_t page_num;
    int32_t cell_num;
} Refer;

typedef struct ReferUpdateEntity {
    Refer *old_refer;
    Refer *new_refer;
} ReferUpdateEntity;

typedef struct {
    ExecuteStatus status;
    Refer *refer;
} InsertExecuteResult;

/* Db execute result. */
typedef struct {
    StatementType stmt_type;
    char *table;
    bool success;
    void *data;
    uint32_t rows;
    char *message;
    double duration;
} DBResult;

/* DB Result Set.*/
typedef struct {
    uint32_t size;
    DBResult **set;
} DBResultSet;

/* Alias struct flock. */
typedef struct flock FileLock;

/* LockState */
typedef struct LockHandle {
    Refer *refer;
    pthread_rwlock_t lock;  /* wrlock. */
    uint32_t shared; /* number of shared the lock. */
    struct LockHandle *next; /* next */
} LockHandle;

/* LockTable */
typedef struct {
    LockHandle *head; /* the head of list */
    LockHandle *tail; /* the tail of list */
    uint32_t size;
} LockTable;

/* TransactionHandle */
typedef struct TransactionHandle {
    int64_t xid; /* transaction id. */ 
    int64_t tid; /* thread id. */
    bool auto_commit; /* auto commit. */
    struct TransactionHandle *next; /* next */
} TransactionHandle;

/* Transaction Table. */
typedef struct {
    TransactionHandle *head;
    TransactionHandle *tail;
    volatile uint32_t size;
} TransactionTable; 

/* LogEntry puts current pthread messsage. */
typedef struct LogEntry {
    int64_t tid;           /* pthread id */
    char *message;          /* mssage */
    struct LogEntry *next;  /* next */
} LogEntry;

/* LogEntry Collector. */
typedef struct LogTable {
    LogEntry *head;
    LogEntry *tail;
    uint32_t size;
} LogTable;

/* XLogEntry */
typedef struct XLogEntry {
    int64_t xid;            /* Transaction Id */
    Refer *refer;           /* Row refer. */
    DDLType type;           /* DDL type. */
    struct XLogEntry *next; /* Next XLogEntry */
}XLogEntry;

/* XLogEntry */
typedef struct XLogTable {
    XLogEntry **list;
    uint32_t size;
} XLogTable;

/* AliasEntry */
typedef struct AliasEntry {
    char *name;
    char *alias;
} AliasEntry;

/* AliasMap */
typedef struct AliasMap {
    uint32_t size;
    AliasEntry map[MAX_MULTI_TABLE_NUM];
} AliasMap;

#endif
