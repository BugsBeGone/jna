/* x86 linux (including Android) structure alignment test for JNA */
#include <assert.h>  /* static_assert() */
#include <stddef.h>  /* offsetof() */

/* This is the C equivalent of the definition for TestStructure, from method
 * testGNUCAlignment() in master/test/com/sun/jna/StructureTest.java, line 170+.
 */
typedef struct JNATestStructure {
	char   b;  /* offset:  0, size: 1, padding: 1 */
	short  s;  /* offset:  2, size: 2, padding: 0 */
	int    i;  /* offset:  4, size: 4, padding: 0 */
	long   l;  /* offset:  8, size: 4, padding: 0 */
	float  f;  /* offset: 12, size: 4, padding: 0 */
	double d;  /* offset: 16, size: 8, padding: 0 */
} jnats;  /* Total size: 24 bytes */

jnats ts;  /* Need an instance so we can use sizeof */

/* According to the JNA source, the expected size of the struct is 28 or 32:
 *   "final int SIZE = Native.MAX_ALIGNMENT == 8 ? 32 : 28;"
 * With NDK r17c (the last revision before gcc was removed), I get neither of
 * these sizes compiling with i686-linux-android-gcc.  Likewise with NDK r19c,
 * I still get neither of these sizes compiling with i686-linux-android16-clang.
 * In fact, no matter what NDK cross compiler I use to target x86, I always get
 * the sizes and offsets in the below asserts, which all pass.
 */

/* Test offsets */
static_assert(offsetof(jnats, b) ==  0, "offsetof char   (ts.b) !=  0");
static_assert(offsetof(jnats, s) ==  2, "offsetof short  (ts.s) !=  2");
static_assert(offsetof(jnats, i) ==  4, "offsetof int    (ts.i) !=  4");
static_assert(offsetof(jnats, l) ==  8, "offsetof long   (ts.l) !=  8");
static_assert(offsetof(jnats, f) == 12, "offsetof float  (ts.f) != 12");
static_assert(offsetof(jnats, d) == 16, "offsetof double (ts.d) != 16");
/* Test sizes */
static_assert(sizeof(ts.b) == 1, "sizeof char   (ts.b) != 1");
static_assert(sizeof(ts.s) == 2, "sizeof short  (ts.s) != 2");
static_assert(sizeof(ts.i) == 4, "sizeof int    (ts.i) != 4");
static_assert(sizeof(ts.l) == 4, "sizeof long   (ts.l) != 4");
static_assert(sizeof(ts.f) == 4, "sizeof float  (ts.f) != 4");
static_assert(sizeof(ts.d) == 8, "sizeof double (ts.d) != 8");
/* Test total size */
static_assert(sizeof(ts) == 24, "sizeof struct ts != 24");
/* Test padding */
static_assert((offsetof(jnats, s) - offsetof(jnats, b) - sizeof(ts.b)) == 1, "padding for ts.b != 1");
static_assert((offsetof(jnats, i) - offsetof(jnats, s) - sizeof(ts.s)) == 0, "padding for ts.s != 0");
static_assert((offsetof(jnats, l) - offsetof(jnats, i) - sizeof(ts.i)) == 0, "padding for ts.i != 0");
static_assert((offsetof(jnats, f) - offsetof(jnats, l) - sizeof(ts.l)) == 0, "padding for ts.l != 0");
static_assert((offsetof(jnats, d) - offsetof(jnats, f) - sizeof(ts.f)) == 0, "padding for ts.f != 0");
static_assert((sizeof(ts)         - offsetof(jnats, d) - sizeof(ts.d)) == 0, "padding for ts.d != 0");

/* If your compiler passes all of these static asserts with no complaints, that
 * must mean that the default maximum alignment for linux x86 really is 4 bytes.
 */

int main(void) {
	return 0;
}

