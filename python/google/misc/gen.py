#!/usr/bin/python
import sys, random

if len(sys.argv) > 1:
    num = int(sys.argv[1])
else:
    num = 100

address = [
    "nokuno@nokuno.jp",
    "test@test.jp",
    "google@google.com",
    "moe@moemoe.ac.jp",
    "okuno@soft.ics.keio.ac.jp",
    "fr020473@ics.keio.ac.jp",
    "nokuno@social-ime.com",
    "english@difficult.en",
]

for i in range(num):
    index = random.randint(0, len(address)-1)
    print address[index]
