#### RoadMap

​		Begin 2023-07-28, I tried to realise a simple object-oriented database engine, just for fun and the roadmap as follws:

- [ ] B-Tree data page store

- [ ] Based Lex&Yacc implement sql parser
- [ ] Create a table using sql
- [ ] Query data using sql
- [ ] Insert data using sql
- [ ] Query special column data using sql
- [ ] Query data under condition using sql
- [ ] B+Tree index store
- [ ] Implement view
- [ ] Implement MVCC



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
