/*
 * dList.h
 *
 *  Created on: 18.07.2018
 *     Author: Patrick Wagner
 *
 *     doubly linked list
 *     attributes:
 *     float temp: temperature
 *     int index: index
 *     functions:
 *     append(struct dList *pList, float temp, int index): append node to list
 *     addAscending(struct dList *pList, float temp, int index): add node in ascending order to list
 *     swap(struct dList *pList, struct dList *pNode1, struct dList *pNode2) : swap 2 elements
 *     sortDescending(struct dList *pList): sort list in descending order
 *     print(struct dList *pList, ): print list
 *     delete(struct dList *pList, ): delete all nodes in list
 *     void sort(struct dList *pList, enum mode, enum attribute), mode: ascending/descending,
 *     attribute: temp/index
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

enum mode {
	ascending, descending
} sortMode;
enum attribute {
	temp, index
} sortAttribute;

bool doSwap = false;

struct dList {
	float temp;
	int index;
	struct dList *next;
	struct dList *previous;
	struct dList *begin;
	struct dList *end;
};

/* void initialize(struct dList *pList, struct dList *pList)
 * @brief initializes transferred list by setting the pointers to NULL
 * @param struct dList *pList: pointer to transferred List
 * @return none
 */
void initialize(struct dList *pList) {
	pList->begin = NULL;
	pList->end = NULL;
	pList->next = NULL;
	pList->previous = NULL;
}

/* void append(struct dList *pList, float temp, int index)
 * add a node to the end of the list
 * parameters: float temp, int index
 * return: none
 */
void append(struct dList *pList, float temp, int index) {
	struct dList *pHelper = pList;

//check if list is empty
	//if list is empty, allocate memory for new element and add it to the begin
	//of the list i.e adding the first element to the list
	if (pList->begin == NULL) {
		if ((pList->begin = malloc(sizeof(struct dList))) == NULL) {
			fprintf(stderr,
					"memory allocation for begin failed with error: %d\n",
					errno);
		}
		//toDo: comment this
		pList->begin->temp = temp;
		pList->begin->index = index;
		pList->begin->next = NULL;
		pList->begin->previous = NULL;
		pList->end = pList->begin;
	}
//check if 1 element is in the list (and not more)
	// and if thats the case add the second element to the list
	// necessary step, to connect the begin pointer to the rest of the list
	else if ((pList->begin == pList->end) && pList->begin != NULL) {
		if ((pList->end = malloc(sizeof(struct dList))) == NULL) {
			fprintf(stderr, "memory allocation for end failed with error: %d\n",
			errno);
		}
		//toDo: comment this
		pList->end->temp = temp;
		pList->end->index = index;
		pList->end->next = NULL;
		pList->end->previous = pList->begin;
		pList->begin->next = pList->end;
	}

// else at this point means, there are at least 2 elements in the list
	// therefore we can simply add the new element to the end of the list
	else {
		pHelper = pList->end;
		if ((pList->end = malloc(sizeof(struct dList))) == NULL) {
			fprintf(stderr, "memory allocation for end failed with error: %d\n",
			errno);
		}
		//toDo: comment this
		pList->end->temp = temp;
		pList->end->index = index;
		pList->end->next = NULL;
		pList->end->previous = pHelper;
		pHelper->next = pList->end;
	}

}

/* void addAscending(struct dList *pList, float temp, int index)
 * add a node in ascending order relating to the temperature value to the list
 * paramter: float temp, int index
 * return: none
 */
void addAscending(struct dList *pList, float temp, int index) {
	struct dList *pHelper = pList, *newElement = pList;

//check if list is empty
	// if it is, we can simply use append() at this point
	if (pList->begin == NULL) {
		append(pList, temp, index);
	}

	else {

		//check if we have to add the new Element to the begin of the list
		if (pList->begin->temp > temp) {
			pHelper = pList->begin;
			if ((pList->begin = malloc(sizeof(struct dList))) == NULL) {
				fprintf(stderr,
						"memory allocation for end failed with error: %d\n",
						errno);
			}
			//toDo: comment this
			pList->begin->temp = temp;
			pList->begin->index = index;
			pList->begin->previous = NULL;
			pList->begin->next = pHelper;
			pHelper->previous = pList->begin;
		}

		//check if we have to add the new Element to the end of the list
		else if (pList->end->temp < temp) {
			pHelper = pList->end;
			if ((pList->end = malloc(sizeof(struct dList))) == NULL) {
				fprintf(stderr,
						"memory allocation for end failed with error: %d\n",
						errno);
			}
			//toDo: comment this
			pList->end->temp = temp;
			pList->end->index = index;
			pList->end->next = NULL;
			pList->end->previous = pHelper;
			pHelper->next = pList->end;
		}

		// else means we have to add the new element in between
		else {

			pHelper = pList->begin;
			// this is a bit of a tricky one: when adding a 'newElement', each
			// added node is called 'newElement', which means one cannot take
			// 'newElement' as break condition e.g.: while(pHelper != newElement)
			// would lead to the while loop being broken after reaching the first
			// 'newElement'
			// what we want here is to break the while loop after the if statement
			// got executed, so we have to find a while condition that realizes this
			// which is the case when pHelper->next->temp equals the transfered value
			// important to note is that we increment pHelper at the end of
			// the while loop, therefore our break condition is pHelper->temp and not
			// pHelper->next->temp
			while (pHelper->temp != temp) {
				if (pHelper->next->temp > temp) {
					if ((newElement = malloc(sizeof(struct dList))) == NULL) {
						fprintf(stderr,
								"memory allocation for new element failed with error: %d\n",
								errno);
					}
					//toDo: comment this
					newElement->temp = temp;
					newElement->index = index;
					newElement->previous = pHelper;
					newElement->next = pHelper->next;
					pHelper->next->previous = newElement;
					pHelper->next = newElement;
				}
				pHelper = pHelper->next;
			}

		}
	}
}

/* void swap(struct dList *pList, struct dList *pNode1,struct dList *pNode2)
 * swaps two nodes in the list
 * Note: pNode1 has to be begin and pNode2 has to be end, if swapping both
 * or one of each!
 * parameter: List and nodes to swap
 * return: none
 */
void swap(struct dList *pList, struct dList *pNode1, struct dList *pNode2) {
//as always, first we check if the list is empty
	if (pList->begin == NULL) {
		printf("No nodes to swap.\n");
	} else {
		struct dList *pH1 = pNode1->previous, *pH2 = pNode1,
				*pH3 = pNode1->next, *pH4 = pNode2->previous, *pH5 = pNode2,
				*pH6 = pNode2->next;

		//check for begin,end and neighboors and store state in variables
		bool pNode1Begin = false, pNode2End = false, pNeighboor = false;
		if (pNode1 == pList->begin) {
			pNode1Begin = true;
		}
		if (pNode2 == pList->end) {
			pNode2End = true;
		}
		if (pH3 == pNode2 || pH4 == pNode1) {
			pNeighboor = true;
		}

		//swap address
		pNode1 = pH5;
		pNode2 = pH2;

		//rearrange next and previous pointers of involved nodes
		//check for begin
		if (pNode1Begin == false) {
			pNode1->previous = pH1;
			pH1->next = pNode1;
		} else {
			pList->begin = pNode1;
			pList->begin->previous = NULL;
		}

		//check for neighboor
		if (pNeighboor == false) {
			pNode1->next = pH3;
			pH3->previous = pNode1;

			pNode2->previous = pH4;
			pH4->next = pNode2;
		} else {
			pNode1->next = pNode2;
			pNode2->previous = pNode1;
		}

		//check for end
		if (pNode2End == false) {
			pNode2->next = pH6;
			pH6->previous = pNode2;
		} else {
			pList->end = pNode2;
			pList->end->next = NULL;
		}
	}

}

/* void sortDescending(struct dList *pList)
 * sorts the whole list in descending order
 * parameter: none
 * return: none
 */
void sortDescending(struct dList *pList) {
	struct dList *pOut, *pIn;
	pOut = pList->begin;
	pIn = pOut->next;
// check if list is empty
	if (pList->begin == NULL) {
		printf("No list to sort.\n");
	}

	else {
		// create outer counting loop
		while (pOut != NULL) {
			// create inner counting loop
			while (pIn != NULL) {
				if (pOut->temp < pIn->temp) {
					swap(pList, pOut, pIn);
					//swapping also swaps the counter pointers, so we have to
					//swap them back, using a buffer pointer
					struct dList *pBuffer;
					pBuffer = pOut;
					pOut = pIn;
					pIn = pBuffer;
				}
				pIn = pIn->next;
			}
			pOut = pOut->next;
			pIn = pOut;
		}
	}
}

/* void sort(struct dList *pList, enum mode sortMode, enum attribute sortAttribute)
 * sorts the list according to the parameters
 * parameters:	sortMode: ascending/descending
 * 				sortAttribute: temp/index
 * return: none
 */
void sort(struct dList *pList, enum mode sortMode, enum attribute sortAttribute) {
	struct dList *pOut, *pIn;
	pOut = pList->begin;
	pIn = pOut->next;
	if (pList->begin == NULL) {
		printf("No list to sort.\n");
	}

	else {
		// create outer counting loop
		while (pOut != NULL) {
			// create inner counting loop
			while (pIn != NULL) {

				if (sortMode == descending && sortAttribute == temp) {
					if (pOut->temp < pIn->temp) {
						doSwap = true;
					}
				} else if (sortMode == descending && sortAttribute == index) {
					if (pOut->index < pIn->index) {
						doSwap = true;
					}
				}

				else if (sortMode == ascending && sortAttribute == temp) {
					if (pOut->temp > pIn->temp) {
						doSwap = true;
					}
				}

				else if (sortMode == ascending && sortAttribute == index) {
					if (pOut->index > pIn->index) {
						doSwap = true;
					}
				}

				if (doSwap == true) {
					swap(pList,pOut, pIn);
					//swapping also swaps the counter pointers, so we have to
					//swap them back, using a buffer pointer
					struct dList *pBuffer;
					pBuffer = pOut;
					pOut = pIn;
					pIn = pBuffer;
					doSwap = false;
				}
				pIn = pIn->next;
			}
			pOut = pOut->next;
			pIn = pOut;
		}
	}
}

void print(struct dList *pList) {
//check if list is empty
	if (pList->begin == NULL) {
		printf("There is no list to print.\n");
	} else {
		struct dList *pHelper = pList->begin;
		while (pHelper != NULL) {
			printf("Temperature: %.1f", pHelper->temp);
			printf(" | Index: %i\n", pHelper->index);
			pHelper = pHelper->next;
		}
	}
}

void delete(struct dList *pList) {
	if (pList->begin == NULL) {
		printf("Nothing to delete.\n");
	} else {
		struct dList *pCleaner = pList->begin;
		while (pCleaner != NULL) {
			pCleaner = pCleaner->next;
			free(pCleaner);
		}
		pList->begin = NULL;
		pList->end = NULL;
	}

	printf("List has been deleted.\n");
}

#endif /* DLIST_H_ */
