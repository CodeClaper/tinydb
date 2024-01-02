# An object-oriented database engine --TinyDb

## Introduction

TinyDb (can also be called tinydb as well) is a light, statble and effecive object-oriented database engine.  TinyDb is intended to design and store more intuitive data model. When you use object-oriented language to build program like java, python etc,  the object  data structure in the code and the table structure in the TinyDb database have direct one-to-one mapping relationship. By TinyDb, you can easily save the data in memory to disk without unnecessary data structure conversion as well as reading data from disk.

## Requirements

### Linux OS

TinyDb is a server-side database engine and currently only support linux environment. 

### Lex & Yacc

TinyDb uses Lex & Yacc to realize sql lexical analyzer and parser. If you want to compile the sql file, you must have theses tools or substitutes. 

**Debian** or **Ubuntu**

```sh
sudo apt-get install flex bison
```

**Centos**

```shell
yum install flex bison
```

### GNU Readline

Tinydb cli bases the GNU Readline as command helper, so if you want use cli, you must install GNU Readline firstly.

**Debian** or **Ubuntu**

```shell
sudo apt install libreadline-dev
```

**Centos**

```shell
yum install readline-devel
```



## Compile

TinyDb uses GNU Automake as the tool to compile the program. 

Firstly,  generate configuration scripts.

```shell
autoconf
```

The configure script is automatic generated, run it to to determine certain information about the packages.

```
./configure
```

If you want debug.

```shell
./configure --enable-debug=yes CFLAGS='-g -O0'
```

Finally, makefile is generated, compile it.

```shell
make
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
- [x] Multiple data type, bool, char, int, float, double, string(scalable varchar), date, timestamp and reference.
- [x] Data type valid check.
- [x] Implement MVCC , support transaction and support the four types of transaction isolations.
- [ ] Support index, B+Tree index store
- [ ] Create view using sql
- [ ] Bin Log 
- [ ] Distributed
