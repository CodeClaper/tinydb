#### Introduction

​	Begin 2023-07-28, I tried to develop a simple object-oriented database engine named Tinydb.  Tinydb is intended to design and store more intuitive data model. When you use object-oriented language to build program like java, python etc,  the object  data structure in the code and the table structure in the Tinydb database have direct one-to-one mapping relationship. By Tinydb, you can easily save the data in memory to disk without unnecessary data structure conversion as well as reading data from disk.

#### RoadMap

- [x] B-Tree data page store
- [x] Based Lex&Yacc implement sql parser
- [x] Create a table using sql
- [x] Query data using sql
- [x] Insert data using sql
- [x] Update data using sql
- [x] Delete data using sql
- [x] Query special column data using sql
- [x] Query data under conditions using sql
- [ ] Stream output of query result
- [ ] Support index,  B+Tree index store
- [ ] Create view using sql
- [ ] Implement MVCC and support transaction
- [ ] Bin Log
- [ ] Distributed



#### Remember
- A db file is divided into a whole number pages.

- page includes meta data and cells.

- Meta data includes node type, is root leaf node, parent pointer and cell number.

- Cell is a Key-Value, key is index and value containes one row data in table.

- TinyDb use B-Tree as disk data structre.

- Each node correspond to one page.

- There are two types nodes, leaf node and internal node.

- Only leaf node store table data.

- Internal node store keys.

- Root node also as leaf node, but does not store data.

- Usually, root node is page 0.
