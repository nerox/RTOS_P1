#include "Scheduler.h"
#include "Controller.h"



/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
	address_t ret;
	asm volatile("xor    %%fs:0x30,%0\n"
			"rol    $0x11,%0\n"
			: "=g" (ret)
			: "0" (addr));
	return ret;
}


void setup(int num,address_t f)
{
	address_t sp, pc;

  // Make thread 1's stack point to memory on the data section.
	sp = (address_t)process_list[num].stack + STACK_SIZE - sizeof(address_t); 
  // Make thread 1's program counter point to f.
	pc = f;

  // Copy sp,pc into the jmpbuf struct.
	sigsetjmp(process_list[num].env,1);
	(process_list[num].env->__jmpbuf)[JB_SP] = translate_address(sp);
	(process_list[num].env->__jmpbuf)[JB_PC] = translate_address(pc);
	sigemptyset(&process_list[num].env->__saved_mask);     

}
