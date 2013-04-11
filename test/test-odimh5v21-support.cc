/*
 * =====================================================================================
 *
 *       Filename:  test-support.cpp
 *
 *    Description:  Test support objects
 *
 *        Version:  1.0
 *        Created:  03/12/2013 11:05:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <radarlib/odimh5v21_support.hpp>
#include <assert.h>

void test_nodes()
{
	using OdimH5v21::Nodes;

	try {
		Nodes node("aaa");
	} catch (const std::exception& e) {
		assert(false);
	}

	try {
		Nodes node("'aaa'");
	} catch (const std::exception& e) {
		assert(false);
	}
	
	try {
		Nodes node("a'aa");
		assert(false);
	} catch (const std::exception& e) {
	}

	std::vector<Nodes> nodes;

	nodes = Nodes::parseSequence("");
	assert(nodes.size() == 0);

	nodes = Nodes::parseSequence("aaa,aaa");
	assert(nodes.size() == 2);
	assert(nodes.at(0).get() == "'aaa'");
}

int main()
{
	test_nodes();
	return 0;
}
