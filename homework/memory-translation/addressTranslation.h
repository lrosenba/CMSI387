/**
 *Interface for working with the software paging unit.
 */
#ifndef __ADDRESS_TRANSLATION__
#define __ADDRESS_TRANSLATION__

/**
 * The size of a page or frame, represented as a bit field.
 */
#define PAGESIZE 0xf

/**
 * The number of bits occupied by the displacement; this should be the
 * same as the number of set bits in PAGESIZE.
 */
#define PAGEBITS 4

/**
 * The total number of available pages --- this corresponds to a process's
 * overall address space.
 */
#define PAGECOUNT 16

/**
 * Bit mask that separates the page from the displacement.
 */
#define PAGEMASK 0xf0

/**
 * Definition of an individual page table entry.
 */
typedef struct {
    int frame;
    int valid; // In practice, just a single bit!
} pagetable;

/**
 * Error constant for an out-of-range address.
 */
#define ERR_OUT_OF_RANGE -1

/**
 * Error constant for an invalid address.
 */
#define ERR_INVALID -2

/**
 * Sets a pointer to the current page table.
 */
void setPageTable(pagetable *pt);

/**
 * Translates the given logical address to the corresponding physical address.
 * Returns < 0 if there was a problem with the address.
 */
int getPhysical(int logical);

#endif
