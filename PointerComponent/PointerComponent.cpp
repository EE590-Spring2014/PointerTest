// PointerComponent.cpp
#include "PointerComponent.h"

using namespace PointerComponent;
using namespace Platform;

PointerExampleInCPP::PointerExampleInCPP()
{
	// Let's start off by creating a chunk of memory.  We do this via "new".
	// We're going to create 40 bytes of memory, and treat them as a series of 10 floats
	int numFloats = 10;
	float * myFloatPtr = new float[numFloats];

	// Next, let's set them up with some initial data.  We'll just store the index into each element
	for( int i=0; i<numFloats; ++i )
		myFloatPtr[i] = (float)i;

	// Now let's start playing around with pointers!  I suggest dropping breakpoints into here and
	// looking at the values of the various variables to see what's really going on.  First, we're
	// going to just get the address of this floating-point array:
	unsigned long floatArrayAddress = (unsigned long) myFloatPtr;

	// Stepping over that line and investigating the contents of "floatArrayAddress" shows a number;
	// this number is the number you would give to the CPU's "load memory" instruction, which would
	// return the floating point number 0.0f.  If we increment the address and tell the CPU to load
	// that memory address in, it will return 1.0f.  So let's do that:
	floatArrayAddress += sizeof(float);

	// Now there are many ways to load data in from a memory address.  We'll go over all of them.
	// First, we can create another "float *" pointer variable and point it to the new address:
	float * myOtherFloatPtr = (float *)floatArrayAddress;
	float doesItEqualOne = myOtherFloatPtr[0];

	// Type "doesItEqualOne" into the debug watch, and you will see that it is now equal to 1.0f
	// We don't strictly need to create "myOtherFloatPtr", the only reason it is convenient is
	// because the "[0]" at the end dereferences the pointer for us.  "Dereferencing" means to
	// travel to the memory location stored in the variable and get the value of whatever it's
	// pointing to.  So, we could instead use a typecast and get rid of the new pointer variable:
	doesItEqualOne = ((float *)floatArrayAddress)[0];

	// This is a little ugly, but works just fine, and is the kind of thing low-level C programmers
	// do all the time.  We don't have to use "[0]" as our dereferencing operator however, we could
	// instead dereference directly with the "*" operator:
	doesItEqualOne = *myOtherFloatPtr;

	// This "*" in front of a variable means "dereference this pointer".  E.g. it looks at a 
	// variable of type "T *", goes to the address stored in that variable, loads in the memory
	// that corresponds to that "T" and returns it, thereby translating from "T *" to "T".  In
	// this case, "T" is "float".  We can use the dereference operator anywhere, as long as we
	// typecast with appropriate fervor:
	doesItEqualOne = *(float *)floatArrayAddress;

	// We can take this a step further and perform the incrementing of floatArrayAddress on the
	// line assigning to doesItEqualOne:
	floatArrayAddress = (unsigned long) myFloatPtr;
	doesItEqualOne = *((float *) (floatArrayAddress + sizeof(float)));

	// Note the (over) usage of parentheses here; we first add "sizeof(float)" bytes to
	// floatArrayAddress, then typecast it to "float *", and THEN dereference it.
	// Doing things in a different order would have different results:
	doesItEqualOne = *(((float *)floatArrayAddress) + sizeof(float));

	// In this case, since "sizeof(float)" == 4, we are adding 4 on to a "float *", but the
	// compiler is smart enough to already know that float's are 4 bytes large.  So this
	// actually skips forward 16 bytes instead of 4, which is why doesItEqualOne does not
	// equal one.

	// Next, let's go hog wild and eschew temporaries completely, just performing all these
	// operations in one go, and removing floatArrayAddress completely:
	doesItEqualOne = *(myFloatPtr + 1);

	// Such simplicity.  Such elegance.  Plus, the above line is completely equivalent to:
	doesItEqualOne = myFloatPtr[1];

	// In fact, there is literally no difference between the two.




	// Great, you are now a master at dereferencing, so let's go in the opposite direction.
	// We can take a variable and get its address via the "&" operator.  Let's take a look:
	floatArrayAddress = (unsigned long) &myFloatPtr[0];

	// This takes the first element of myFloatPtr and returns its address.  In fact,
	// this is the same thing as what we first did:
	floatArrayAddress = (unsigned long) myFloatPtr;

	// The two are again, completely equivalent, as are these three:
	floatArrayAddress = (unsigned long) (myFloatPtr + 1);
	floatArrayAddress = (unsigned long) &myFloatPtr[1];
	floatArrayAddress = (unsigned long) myFloatPtr + sizeof(float);

	// We have to be very intentional with our parentheses here, as order of operations
	// is really important: addition with a T * increments in steps of sizeof(T), whereas
	// addition with an unsigned long just increments that number by the addend.  In the
	// three examples above, we add 1 to the first because we are adding to a "float *",
	// and so since "sizeof(float)" == 4 we will skip straight to the next float element.
	// The second example uses "[1]" which similarly knows the size of elements and can
	// be intelligent about it.  The last example, the typecast has a higher order of
	// operations than the addition, so we are adding together unsigned longs, and we
	// must manually increment the pointer by the sizeof(float).
}
