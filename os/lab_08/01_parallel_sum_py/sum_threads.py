import sys, random, threading
line = sys.stdin.readline()
if not line:
    sys.exit(0)
n =int(line.strip())
if n<16:
    sys.exit(0)
random.seed(42)
a =[random.randint(0, 999) for _ in range(n)]
totl = 0
lock = threading.Lock()
def worker(l, r):
    local = sum(a[l:r])
    with lock:
        global totl
        totl += local
base, rem = divmod(n, 4)
threads = []
pos = 0
for i in range(4):
    length = base + (1 if i < rem else 0)
    t = threading.Thread(target=worker, args=(pos, pos + length))
    t.start()
    threads.append(t)
    pos += length

for t in threads:
    t.join()

print("Array:", *a)
print("Total sum:", totl)
