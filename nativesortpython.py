f=open("input.txt","r")
g=open("output.txt", "w")
n=f.readline()
v=f.readline()
arr=[int(x) for x in v.split()]
arr=sorted(arr)
for i in arr:
    g.write(str(i)+" ")
f.close()
g.close()
