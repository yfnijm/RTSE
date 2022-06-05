#include <pybind11/pybind11.h>
#include <pybind11/attr.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <bits/stdc++.h>
#include "Rtree.hpp"
#include "Rtree_non_overlapping.hpp"



PYBIND11_MODULE(_RTSE, m) {
	m.doc() = "pybind11 plugin";
	pybind11::class_<Node_non_overlapping>(m, "Node_non_overlapping")	
		//.def(pybind11::init<int>())
		.def("get_coor1", &Node_non_overlapping::get_coor1)
		.def("get_coor2", &Node_non_overlapping::get_coor2)
		.def("print_node", &Node_non_overlapping::print_node)
		;
	pybind11::class_<Rtree_non_overlapping>(m, "Rtree_non_overlapping")
		.def(pybind11::init<int>())
		.def(pybind11::init<std::vector< std::vector<int>>, int>())
		.def("insert_nodes", &Rtree_non_overlapping::insert_nodes)
		.def("delete_nodes", &Rtree_non_overlapping::delete_nodes)
		
		.def("print_nodes", &Rtree_non_overlapping::print_nodes)	
		.def("size", &Rtree_non_overlapping::size)	
		
		.def("spatial_queries", &Rtree_non_overlapping::spatial_queries)
		//.def("__getitem__", &Matrix::getitem)
		//.def("__setitem__", &Matrix::setitem)
		//.def_property_readonly("nrow", &Matrix::nrow)
		//.def_property_readonly("ncol", &Matrix::ncol)
		.def("intersets", &Rtree_non_overlapping::intersects)
        .def("covered_by", &Rtree_non_overlapping::covered_by)
        .def("disjoint", &Rtree_non_overlapping::disjoint)
        .def("overlaps", &Rtree_non_overlapping::overlaps)
        .def("within", &Rtree_non_overlapping::within);
		;
	
	pybind11::class_<Leaf_node>(m, "Leaf_node")	
		//.def(pybind11::init<int>())
		//.def("get_coor1", &Node_non_overlapping::get_coor1)
		//.def("get_coor2", &Node_non_overlapping::get_coor2)
		//.def("print_node", &Node_non_overlapping::print_node)
		;
	pybind11::class_<Rtree>(m, "Rtree")
		//.def(pybind11::init<int>())
		.def(pybind11::init<std::vector< std::vector<int>>>())
		//.def("insert_nodes", &Rtree::insert_nodes)
		//.def("delete_nodes", &Rtree::delete_nodes)
		
		//.def("print_nodes", &Rtree::print_nodes)	
		//.def("size", &Rtree::size)	
		
		.def("spatial_queries", &Rtree::spatial_queries)
		//.def("__getitem__", &Matrix::getitem)
		//.def("__setitem__", &Matrix::setitem)
		//.def_property_readonly("nrow", &Matrix::nrow)
		//.def_property_readonly("ncol", &Matrix::ncol)
		.def("intersets", &Rtree::intersects)
        .def("covered_by", &Rtree::covered_by)
        .def("disjoint", &Rtree::disjoint)
        .def("overlaps", &Rtree::overlaps)
        .def("within", &Rtree::within);
		;
}


