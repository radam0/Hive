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

