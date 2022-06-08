#include <stdio.h>
/*simulate cache with 256B blocks and 16 sets for 32-bit architecture*/

//returns the byte offset of the address within its cache block
unsigned int getOffset(unsigned int address){
	return address & 0xff;
	//isolate last two
}

//returns the cache set for the address
unsigned int getSet(unsigned int address){
	return (address >> 8) & 0xf;
}

//returns the cache tag for the address
unsigned int getTag(unsigned int address){
	return address >> 12;
	//isolate first five
}

int main(){
	printf("0x12345678: offset: %x - tag: %x - set: %x\n", getOffset(0x12345678), getTag(0x12345678), getSet(0x12345678));
	printf("0x87654321: offset: %x - tag: %x - set: %x\n", getOffset(0x87654321), getTag(0x87654321), getSet(0x87654321));
}
