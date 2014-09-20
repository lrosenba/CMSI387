/** 
 *Test driver for our software paging unit.
 */
#include "addressTranslation.h"

#include <assert.h>

int main(int argc, char *argv[]) {
    // Sample page table.
    pagetable pt[] = {
        {  4, 1 }, // { frame, valid }
        {  2, 1 },
        {  9, 1 },
        { 10, 1 },
        {  0, 1 },
        { 14, 1 },
        { 12, 0 },
        {  6, 1 },
        {  1, 1 },
        {  3, 0 },
        { 13, 1 },
        {  8, 1 },
        {  7, 1 },
        { 11, 1 },
        { 15, 1 },
        {  5, 0 } // Should be PAGECOUNT members.
    };
    setPageTable(pt);

    // Tests...feel free to add more!
    assert(getPhysical(-1) == ERR_OUT_OF_RANGE);
    assert(getPhysical(5) == 69);
    assert(getPhysical(13) == 77);
    assert(getPhysical(24) == 40);
    assert(getPhysical(31) == 47);
    assert(getPhysical(52) == 164);
    assert(getPhysical(72) == 8);
    assert(getPhysical(90) == 234);
    assert(getPhysical(98) == ERR_INVALID);
    assert(getPhysical(104) == ERR_INVALID);
    assert(getPhysical(128) == 16);
    assert(getPhysical(150) == ERR_INVALID);
    assert(getPhysical(179) == 131);
    assert(getPhysical(181) == 133);
    assert(getPhysical(199) == 119);
    assert(getPhysical(218) == 186);
    assert(getPhysical(239) == 255);
    assert(getPhysical(240) == ERR_INVALID);
    assert(getPhysical(249) == ERR_INVALID);
    assert(getPhysical(256) == ERR_OUT_OF_RANGE);
}

