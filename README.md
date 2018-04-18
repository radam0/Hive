--Hive
Hive is capable of only structured data.
Hive is a Hadoop-based data warehousing-like framework originally developed at Facebook.
It allows users to write queries in a SQL-like language called HiveQL(HQL), which are then converted to MapReduce jobs.
All Hadoop eco system components stores data on HDFS.
Hive is not case-sensitive
In Hive, everything will be in directories.
Default file format in Hive is text.
Default delimiter in Hive is ctrlA character. Its ASCII value is 001


--Limitations of Hive
Hive doesn’t provide record-level update, insert, nor delete.
Hadoop is batch-oriented system, hive queries have higher latency, due to start up overhead for MapReduce jobs. Queries that would finish in seconds for a traditional database, takes longer for hive, even for relatively small datasets.  Hive doesn’t provide transactions.

--Differences b/w RDBMS and Hive
We can perform update, insert on RDBMS
Hive stores the data on HDFS. So, we cannot change the data i.e., row level updates/deletes cannot be permitted.

OLTP – Online Transaction Processing Systems
Hive is not best suited for OLTP where continuous updates will be required.
Hive does not provide insert and update at row level. So, it is not suitable for OLTP system.

OLAP – Online Analytical Processing Systems
Hive is best suited for OLAP 

Hive doesn’t support OLTP.  If you need OLTP features, you should consider NoSQL databases like HBase, Cassandra and DynamoDB, if you are using Amazon EMR / EC2


Hive can runs in the following modes
	i)  Local mode (Default)
	ii) Distributed mode
	iii)Pseudo-distributed mode

All Linux commands can be performed on hive using ! before the command.

All configuration files related to hive will be present in cd /etc /hive/conf

There are two types of datatypes in hive.
	i) Primitive
	ii) Collection

--Differences between EXTERNAL and MANAGED tables
When you drop a MANAGED table, all the underlying files residing on HDFS path will be deleted.
When you drop an EXTERNAL TABLE, all the underlying files residing on HDFS path will not be deleted. Because it’s external, Hive does not assume it owns the data. Therefore, dropping the table does not delete the data, although the metadata for the table will be deleted.


--PARTITIONING
	Partitioning means dividing the table data into smaller parts based on the values of particular columns. Partitioning can be done on 1 or more columns. Partitioning are defined at the time of table creation using the PARTITION BY clause
Advantages
•Used for distributing execution load horizontally.
•As the data is stored as slices/parts, query response time is faster to process the small part of the data instead of looking for a search in the entire data set.

--MULTIPARTITIONINIG
In this, the partition column can have more than 1 column

--Dynamic partitioning

Instead of loading each partition with single SQL statement as shown above, which will result in writing lot of SQL statements for huge no of partitions, Hive supports dynamic partitioning with which we can add any number of partitions with single SQL execution. 
Hive will automatically splits our data into separate partition files based on the values of partition keys present in the input files.
if you have a lot of partitions to create, you must write a lot of SQL! Fortunately, hive also supports a dynamic partition feature, where it can infer the partitions to create based on query parameters 
like
It gives the advantages of easy coding and no need of manual identification of partitions

set hive.exec.dynamic.partition=true;
set hive.exec.dynamic.partition.mode=nonstrict;
set hive.exec.max.dynamic.partitions.pernode=1000;

--BUCKETING(SUB PARTITIONING)
	Hive partition divides table into number of partitions and these partitions can be further subdivided into more manageable parts known as Buckets or Clusters. The Bucketing concept is based on Hash function, which depends on the type of the bucketing column. Records which are bucketed by the same column will always be saved in the same bucket.
Here, CLUSTERED BY clause is used to divide the table into buckets.
In Hive Partition, each partition will be created as directory. But in Hive Buckets, each bucket will be created as file.
SET hive.enforce.bucketing=true;
Bucketing can also be done even without partitioning on Hive tables.

--SORT MERGE BUCKET (SMB) JOIN 
•In SMB join in Hive, each mapper reads a bucket from the first table and the corresponding bucket from the second table and then a merge sort join is performed.
•Sort Merge Bucket (SMB) join in hive is mainly used as there is no limit on file or partition or table join. 
•SMB join can best be used when the tables are large. 
•In SMB join the columns are bucketed and sorted using the join columns. All tables should have the same number of buckets in SMB join.


--What if we want to load the JSON file, here comes the concept of SERDE
SERDE – Serializer and De-Serializer
              - used to insert non-text format files for loading onto the hive table
Serializer – converting from text format to JSON format
De-Serializer – converting from JSON to Text format


--File Formats
TEXTFILE	: Default file format
SEQUENCEFILE	: if I have the plan to have the data in compressed manner, use sequence file.
ORC		: It is the columnar format.
PARQUET	: For impala, parquet is the default file format. The visual analytic people (tableau)                                                                                                            access the hive tables using impala. The default file format in Impala is Parquet. It is the columnar formats.
AVRO		: Default file format for Impala

--When to go with ORC and Parquet?
If we have nested data, we go with Parquet

--Views

A view allows a query to be saved and treated like a table. It is a logical construct, as it does not store data like a table. In other words, materialized views are not currently supported by Hive.
When a query references a view, the information in its definition is combined with the rest of the query by Hive’s query planner. Logically, you can imagine that Hive executes the view and then uses the results in the rest of the query.

--HiveQL: Indexes
Hive has limited indexing capabilities. There are no keys in the usual relational database sense, but you can build an index on columns to speed some operations. The index data for a table is stored in another table.

Indexing is also a good alternative to partitioning when the logical partitions would actually, be too numerous and small to be useful. Indexing can aid in pruning some blocks from a table as input for a MapReduce job. Not all queries can benefit from an index.


--Types of Indexes in Hive
i) BitMap
ii)Compact : The  B-Tree in RDBMS is called as Compact in hive

--RDBMS
BitMap : when data cardinality (uniqueness of data values in a table, Example gender will be male/female) is very low, we use BitMap
B-Tree (default) : when data cardinality is high (uniqueness of data values in a table example, id will have many)a, we use B-Tree








