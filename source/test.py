import pytest
import numpy
import time
import random
import re

from rtree import index
import _RTSE

def valid_res():
	return 


def case1(dim):
	if(dim == 2):
		treeA = _RTSE.Rtree_non_overlapping(dim)

		treeA.insert_nodes([[1, 2, 2, 3], 
							[2, 5, 3, 6]])
		print(treeA.size())
		treeA.print_nodes()

		#	case 0: intersects(spatial);
		#	case 1: covered_by(spatial);
		#	case 2: disjoint(spatial);
		#	case 3: overlaps(spatial);
		#	case 4: within(spatial);
		queries = [
			([-100, -100, 100, 100], 0),
			
			([1, 2, 3, 6], 1),
			([-100, -100, 100, 100], 1),
			
			([1, 2, 3, 6], 2),
			([10, 10, 20, 20], 2),
			
			([1, 2, 3, 6], 3),
			

			([1, 2, 3, 6], 4),
			([0, 1, 4, 7], 4),
			]
		resA = treeA.spatial_queries(queries)
		print(str(len(resA)))
		assert len(resA) == len(queries)
		
		print(str(len(resA[0])))
		print(str(len(resA[1])))
		print(str(len(resA[2])))
		print(str(len(resA[3])))
		print(str(len(resA[4])))
		print(str(len(resA[5])))
		print(str(len(resA[6])))
		print(str(len(resA[7])))

		assert len(resA[0]) == 2
		assert len(resA[1]) == 2
		assert len(resA[2]) == 0
		assert len(resA[3]) == 0
		assert len(resA[4]) == 2
		assert len(resA[5]) == 0
		assert len(resA[6]) == 0
		assert len(resA[7]) == 2
	return 

def case2(filename):
	treeB = _RTSE.Rtree_non_overlapping(2)
	node_list = []
	with open(filename + ".brd.benmakring", "r") as fin:
		for line in fin:
			numbers = [int(s) for s in re.findall(r'-?\d+\.?\d*', line)]
			node_list.append([numbers[1], numbers[2], numbers[1] + numbers[5], numbers[2] + numbers[6]])
			node_list.append([numbers[3], numbers[4], numbers[3] + numbers[5], numbers[4] + numbers[6]])
	treeB.insert_nodes(node_list)	
	print(len(node_list))
	return treeB


def case3():
	# Write the performance into a text file
	fout = open("performance.txt", "w")




	# Read the routing solution
	node_list = []
	with open("temp.gdt", "r") as fin:
		count = 0
		for line in fin:
			count += 1
			if(count <= 4):
				continue;
			
			numbers = [float(s) for s in re.findall(r'-?\d+\.?\d*', line)]
			if(len(numbers) == 0):
				break

			layer = int(numbers[1])
			if( (numbers[2] == numbers[8]) &
				(numbers[3] == numbers[5]) & 
				(numbers[4] == numbers[6]) & 
			   	(numbers[7] == numbers[9])):
				node_list.append([layer, int(numbers[2] * 1000), int(numbers[3] * 1000), 
							  layer, int(numbers[6] * 1000), int(numbers[7] * 1000)])










	#TreeC initial	
	treeC = _RTSE.Rtree_non_overlapping(3)
	time_tmp = time.time()
	
	for t in range(1):
		treeC = _RTSE.Rtree_non_overlapping(3)
		treeC.insert_nodes(node_list)
		#treeC.delete_nodes(node_list)
	fout.write("Tree initial time cost :" + str(time.time() - time_tmp) + "\n")

	for t in range(1):
		treeC = _RTSE.Rtree_non_overlapping(3)
		treeC.insert_nodes(node_list)
		treeC.delete_nodes(node_list)
	fout.write("Tree initial and delete time cost :" +  str(time.time() - time_tmp) + "\n")

	#Re-initial the tree
	treeC = _RTSE.Rtree_non_overlapping(3)
	treeC.insert_nodes(node_list)
	fout.write("\n")



	#TreeD init
	#treeD = _RTSE.Rtree(3)
	time_tmp = time.time()
	
	for t in range(1):
		treeD = _RTSE.Rtree(node_list)
	fout.write("Rtree initial time cost :" + str(time.time() - time_tmp) + "\n")

	#Re-initial the tree
	treeD = _RTSE.Rtree(node_list)
	fout.write("\n")




	#Buildin tree initial
	p = index.Property()
	p.dimension = 3
	p.dat_extension = 'data'
	p.idx_extension = 'index'
	idx3d = index.Index('3d_index',properties=p)
		
	time_tmp = time.time() - time.time()
	for t in range(1):
		time_tmp2 = time.time()
		for i in range(len(node_list)):
			idx3d.insert(i, (float(node_list[i][0]), float(node_list[i][1]), float(node_list[i][2]), float(node_list[i][3]),float(node_list[i][4]), float(node_list[i][5])))
		time_tmp += time.time() - time_tmp2
		for i in range(len(node_list)):
			idx3d.delete(i, (float(node_list[i][0]),float(node_list[i][1]), float(node_list[i][2]), float(node_list[i][3]),float(node_list[i][4]), float(node_list[i][5])))
	fout.write("Python bulidin tree initial time cost :" + str(time_tmp) + "\n")
	

	#idx3d = index.Index('3d_index',properties=p)
	time_tmp = time.time()
	for t in range(1):
		for i in range(len(node_list)):
			idx3d.insert(i, (float(node_list[i][0]), float(node_list[i][1]), float(node_list[i][2]), float(node_list[i][3]), float(node_list[i][4]), float(node_list[i][5])))
		for i in range(len(node_list)):
			idx3d.delete(i, (float(node_list[i][0]),float(node_list[i][1]), float(node_list[i][2]), float(node_list[i][3]), float(node_list[i][4]), float(node_list[i][5])))
	fout.write("Python bulidin tree initial and delete time cost :" + str(time.time() - time_tmp) + "\n")
	

	#Re-initial the tree	
	for i in range(len(node_list)):
		idx3d.insert(i, (float(node_list[i][0]), float(node_list[i][1]), float(node_list[i][2]), float(node_list[i][3]),float(node_list[i][4]), float(node_list[i][5])))
	fout.write("\n")










	#Buliding query testcase
	query_list = []
	for t in range(1000):
		tar_layer = random.randint(1, 3)
		t1 = random.randint(200000, 300000)
		t2 = random.randint(200000, 300000)
		t3 = random.randint(200000, 300000)
		t4 = random.randint(200000, 300000)
		query_list.append([[tar_layer, min(t1, t2), min(t3, t4), tar_layer, max(t1, t2), max(t3, t4)], 0])
		



	#TreeC query's time cost
	time_tmp = time.time()
	for t in range(10):
		treeC.spatial_queries(query_list)
	fout.write("Tree query time cost :" + str(time.time() - time_tmp) + "\n")
	
	#TreeD query's time cost
	time_tmp = time.time()
	for t in range(10):
		treeD.spatial_queries(query_list)
	fout.write("Tree query time cost :" + str(time.time() - time_tmp) + "\n")
	

	
	#Buildin tree's time cost
	for t in range(10):
		for q, _ in query_list:
			idx3d.intersection(q)
	fout.write("Python bulidin tree query time cost :" +  str(time.time() - time_tmp) + "\n")
	









	fout.write("\n")










	return 

def test_performance():
	#case1(2)
	#case2("1")
	case3()
	return 
