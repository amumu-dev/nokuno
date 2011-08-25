#!/bin/bash
sort | ./init.py | \
./map.py | sort | ./reduce.py | \
./map.py | sort | ./reduce.py | \
./map.py | sort | ./reduce.py | \
./map.py | sort | ./reduce.py | \
./map.py | sort | ./reduce.py 
