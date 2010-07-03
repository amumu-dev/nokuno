#!/usr/bin/python
import timeit
print timeit.Timer('for i in xrange(10): oct(i)', 'gc.enable()').timeit()

