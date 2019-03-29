/* x86 linux (including Android) structure alignment test for JNA */
#include <assert.h>  /* static_assert() */
#include <stddef.h>  /* offsetof() */

/* My own simple test struct example: a 4-byte float and an 8-byte double.
 * With a maximum alignment of 4 bytes, it should not require any padding and
 * should always take up just 12 bytes, regardless of the order of members.
 */
typedef struct BugsBeGoneTestStructure {
	float  field1;  /* offset: 0, size: 4, padding: 0 */
	double field2;  /* offset: 4, size: 8, padding: 0 */
} bbgts;  /* Total size: 12 bytes */

bbgts myts;  /* Need an instance so we can use sizeof */

/* Test offsets */
static_assert(offsetof(bbgts, field1) == 0, "offsetof float  (myts.field1) != 0");
static_assert(offsetof(bbgts, field2) == 4, "offsetof double (myts.field2) != 4");
/* Test sizes */
static_assert(sizeof(myts.field1) == 4, "sizeof float  (myts.field1) != 4");
static_assert(sizeof(myts.field2) == 8, "sizeof double (myts.field2) != 8");
/* Test total size */
static_assert(sizeof(myts) == 12, "sizeof struct myts != 12");
/* Test padding */
static_assert((offsetof(bbgts, field2) - offsetof(bbgts, field1) - sizeof(myts.field1)) == 0, "padding for myts.field1 != 0");
static_assert((sizeof(myts)            - offsetof(bbgts, field2) - sizeof(myts.field2)) == 0, "padding for myts.field2 != 0");


int main(void) {
	return 0;
}

