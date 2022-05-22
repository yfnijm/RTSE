import pytest
import numpy
import time
import _RTSE

def valid_res():
	return 


def time_cost(dim):
	if(dim == 2):
		treeA = _RTSE.Rtree_non_overlapping(dim)

		treeA.insert_nodes([[1, 2, 2, 3], 
							[2, 5, 3, 6]])
		print(treeA.size())
		treeA.print_nodes()

		resA = treeA.spatial_queries([
			([-100, -100, 100, 100], 0),
			([1, 2, 3, 6], 1),
			([-100, -100, 100, 100], 1),
			([1, 2, 3, 6], 2),
			([1, 2, 3, 6], 3),
			([1, 2, 3, 6], 4),
			])
		print(str(len(resA)))
		#assert len(resA) == 5
		
		print(str(len(resA[0])))
		print(str(len(resA[1])))
		print(str(len(resA[2])))
		print(str(len(resA[3])))
		print(str(len(resA[4])))
		assert len(resA[0]) == 2
		assert len(resA[1]) != -1
		assert len(resA[2]) != -1
		assert len(resA[3]) != -1
		assert len(resA[4]) != -1

		assert False
	return 



def test_performance():
	time_cost(2)

	return 
