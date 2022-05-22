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



def test_performance():
	time_cost(2)

	return 
