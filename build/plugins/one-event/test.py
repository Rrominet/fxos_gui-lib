import os
import sys
import json

data = json.loads(sys.stdin)
f = open("/tmp/test.txt", "w")
f.write(json.dumps(data))
f.close()

print(json.dumps(data))
