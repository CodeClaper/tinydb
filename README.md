#### BackGround

2023/07/28开始，尝试手动写一个面向对象的数据库内核@_@，简单的RoadMap如下

- [ ] B-Tree数据存储，分页储存

- [ ] B+Tree索引存储，构建查询
- [ ] 实现DQL操作
- [ ] 实现DDL操作
- [ ] 基于Lex&Yacc实现sql解析
- [ ] 实现sql查询
- [ ] 实现视图功能
- [ ] 实现MVVC

#### Data Structre B+Tree B-Tree
A db file is divided into a whole number pages.

page includes meta data and cells.

Meta data includes node type, is root leaf node, parent pointer and cell number.

Cell is a Key-Value, key is index and value containes one row data in table.

TinyDb use B-Tree as disk data structre.

Each node correspond to one page.

There are two types nodes, leaf node and internal node.

Only leaf node store table data.

Internal node store keys.

Root node also as leaf node, but does not store data.

Usually, root node is page 0.
