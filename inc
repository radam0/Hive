--oracle table
CREATE TABLE HDP_base_table (
        id NUMBER,
        field1 VARCHAR2(200),
        modified_date DATE)

INSERT INTO HDP_base_table values (5,'ramu',sysdate)
 
 update xxitemhub.HDP_base_table set modified_date=sysdate-2
 
 select * from xxitemhub.HDP_base_table where trunc(modified_date) = trunc(sysdate)
 
		
--hive base table 
CREATE TABLE tv_retaildb.base_table (
        id STRING,
        field1 STRING,
        modified_date string)
    ROW FORMAT DELIMITED
    FIELDS TERMINATED BY ','
    STORED AS ORC;
--hive external table	
CREATE EXTERNAL TABLE tv_retaildb.incremental_table (
        id STRING,
        field1 STRING,
        modified_date string)
    ROW FORMAT DELIMITED
    FIELDS TERMINATED BY ','
    STORED AS TEXTFILE
    location '/app/hdpc3bl/HIVE/WAREHOUSE/tv_retaildb.db/incremental_table';	
--hive external history table
	CREATE TABLE tv_retaildb.incremental_table_hist (
        id STRING,
        field1 STRING,
        modified_date string)
    ROW FORMAT DELIMITED
    FIELDS TERMINATED BY ','
    STORED AS ORC;

--===================================	
--xxincr.sh
sqoop import --connect jdbc:oracle:thin:@lnxdbcj-pts-505.cisco.com:1804/TS3CG11 \
--username XXITEMHUB  \
--password Xl5Q1t9K \
--delete-target-dir \
--target-dir /app/hdpc3bl/HIVE/WAREHOUSE/tv_retaildb.db/incremental_table -m 1 \
--query 'select * from xxitemhub.HDP_base_table where trunc(modified_date) = trunc(sysdate) AND $CONDITIONS'	

hive -e "INSERT OVERWRITE TABLE tv_retaildb.incremental_table_hist select * from tv_retaildb.incremental_table"	
--==========================
	
CREATE VIEW tv_retaildb.reconcile_view AS
SELECT t1.* FROM
    (SELECT * FROM tv_retaildb.base_table
     UNION ALL
     SELECT * from tv_retaildb.incremental_table) t1
JOIN
    (SELECT id, max(modified_date) max_modified FROM
        (SELECT * FROM tv_retaildb.base_table
         UNION ALL
         SELECT * from tv_retaildb.incremental_table)
     GROUP BY id) t2
ON t1.id = t2.id AND t1.modified_date = t2.max_modified;


CREATE VIEW reconcile_view AS
    SELECT t1.* FROM
        (SELECT * FROM base_table
         UNION
         SELECT * FROM incremental_table) t1
     JOIN
         (SELECT id, max(modified_date) max_modified FROM
             (SELECT * FROM base_table
              UNION
              SELECT * FROM incremental_table)
      GROUP BY id) t2
   ON t1.id = t2.id AND t1.modified_date = t2.max_modified
   AND t1.delete_date IS NULL;
   
   
   
   start_date end_date
   1-1-2018   12-12-2018
   
