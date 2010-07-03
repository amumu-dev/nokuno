#!/usr/bin/python
import MySQLdb

db = MySQLdb.connect(db="sourcecode", user="nokuno", passwd="nokuno")
db.close()
