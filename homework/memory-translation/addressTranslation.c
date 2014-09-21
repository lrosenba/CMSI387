/** 
 *Implementation of the software paging unit.
 */
#include "addressTranslation.h"

#include <stdio.h>
#include <stdlib.h>

static pagetable *ptr = NULL; // ptr = "page table register"

void setPageTable(pagetable *pt) {
    ptr = pt;
}

int getPhysical(int logical) {
    if (logical < 0 || logical > 255) {
        return ERR_OUT_OF_RANGE;
        exit(ERR_OUT_OF_RANGE);       
    }
    int displacement;
    int pageIndex;
    displacement = logical & PAGESIZE;
    pageIndex = (logical & PAGEMASK) >> PAGEBITS;
    int pageValue = ptr[pageIndex].frame;
    int isValid = ptr[pageIndex].valid;
    if (isValid == 0) {
        return ERR_INVALID;
        exit(ERR_OUT_OF_RANGE);
    }  
    //printf("Logical = %d displacement = %d pageIndex = %d pageValue = %d\n ", logical, displacement, pageIndex, pageValue);
    printf("physical = %d\n ", (pageValue << PAGEBITS)+displacement);
    return (pageValue << PAGEBITS)+displacement;
} 







