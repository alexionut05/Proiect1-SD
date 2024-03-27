f=open("input.txt","r")
g=open("output.txt", "w")
n=f.readline()
v=f.readline()
arr=[int(x) for x in v.split()]
v=arr
v=sorted(v)
for i in v:
    g.write(str(i)+" ")
f.close()
g.close()