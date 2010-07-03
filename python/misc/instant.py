#!/usr/bin/python
#encoding: utf-8

x,y,z = 1,2,3
print x,y,z

first, second = 1, 2
first, second = second, first
print first, second

a = b = 123
print a,b


if x < 5 or (x > 10 and x < 20):
    print "The value is OK."

if x < 5 or 10 < x < 20:
    print "The value is OK."

for i in [1,2,3,4,5]:
    print "This is iteration number", i

x = 10
while x >= 0:
    print "x is still not negative."
    x = x-1

# Print out the values from 0 to 99 inclusive.
for value in range(100):
    print value

#x = input("Please enter a number: ")
#print "The square of that number is", x*x

name = ["Cleese", "John"]
print name

x = [[1,2,3],[y,z],[[[]]]]
print x

print name[1], name[0] # Prints "John Cleese"
name[0] = "Smith"

x = ["spam","spam","spam","spam","spam","eggs","and","spam"]
print x[5:7] # Prints the list ["eggs","and"]

print { "Alice" : 23452532, "Boris" : 252336,
  "Clarice" : 2352525, "Doris" : 23624643}

person = { 'first name': "Robin", 'last name': "Hood",
           'occupation': "Scoundrel" }
print person

person['last name'] = "of Locksley"
print person

