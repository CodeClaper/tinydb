# An object-oriented database engine --TinyDb

## Introduction

TinyDb (can also be called tinydb as well) is a light, statble and effecive object-oriented database engine.  TinyDb is intended to design and store more intuitive data model. When you use object-oriented language to build program like java, python etc,  the object  data structure in the code and the table structure in the TinyDb database have direct one-to-one mapping relationship. By TinyDb, you can easily save the data in memory to disk without unnecessary data structure conversion as well as reading data from disk.

## Requirements

### Linux OS

TinyDb is a server-side database engine and currently only support linux environment. 

### Lex & Yacc

TinyDb uses Lex & Yacc to realize sql lexical analyzer and parser. If you want to compile the sql file, you must have theses tools or substitutes. 

Debian or Ubuntu

```sh
sudo apt-get install flex bison
```

Centos

```shell
yum install flex bison
```



## RoadMap

- [x] B-Tree data page store
- [x] Based Lex&Yacc implement sql parser
- [x] Create a table using sql
- [x] Query data using sql
- [x] Insert data using sql
- [x] Update data using sql
- [x] Delete data using sql
- [x] Query special column data using sql
- [x] Query data under conditions using sql
- [x] Query data with aggregate function sum, avg, max, min, count
- [ ] Multiple data type, bool, char, int, float, double, string(scalable varchar), date, timestamp and reference.
- [ ] Stream output of query result
- [ ] Support index, B+Tree index store
- [ ] Create view using sql
- [ ] Implement MVCC and support transaction
- [ ] Bin Log
- [ ] Distributed
