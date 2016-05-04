import numpy as np;
import matplotlib.pyplot as plt





nodef=open('nodes.txt','r')
springf=open('springs.txt','r') 

nodes=[]
springs=[]
for line in nodef:
	line=line.split()
	nodes.append([float(line[0]),float(line[1]),int(line[2])])

for line in springf:
	line=line.split()
	springs.append([int(line[0]),int(line[1])])
	

for i in range(0,len(springs)):
	node0=springs[i][0]
	node1=springs[i][1]
	x0=nodes[node0][0]
	x1=nodes[node1][0]
	y0=nodes[node0][1]
	y1=nodes[node1][1]
	plt.plot([x0,x1],[y0,y1])



for i in range(0,len(nodes)):
	if nodes[i][2]==1:
		plt.scatter(nodes[i][0]+0.05,nodes[i][1]+0.05)
	if nodes[i][2]==2:
		plt.scatter(nodes[i][0]+0.05,nodes[i][1]+0.05)
		plt.scatter(nodes[i][0]-0.05,nodes[i][1]-0.05)



plt.show()





print nodes
print springs
