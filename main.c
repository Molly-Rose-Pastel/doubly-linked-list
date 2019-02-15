/*
 * main.c
 *
 *  Created on: 18.07.2018
 *      Author: Patrick Wagner
 *
 *      testprogram for the doubly linked list:
 *
 *      first create an object 'struct dList'
 *      then initialize the object
 *      then play around with the functions
 */

#include "dList.h"

int main() {

	struct dList liste;
	initialize(&liste);

	addAscending(&liste, 7, 1);
	addAscending(&liste, 3, 2);
	addAscending(&liste, 5, 3);
	addAscending(&liste, 4, 4);
	addAscending(&liste, 6, 5);
	addAscending(&liste, 2, 6);
	print(&liste);
	printf("\n");
	sort(&liste, ascending, index);
	print(&liste);
	printf("\n");
	delete(&liste);
	print(&liste);

	return 0;
}

