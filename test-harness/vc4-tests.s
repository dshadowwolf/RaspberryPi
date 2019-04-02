        .section        .text.get_version,"ax",@progbits
        .p2align        1
        .globl  get_version
        .type   get_version, @function
get_version:
	stm     r6,lr,(--sp)
        add.m   sp,sp,#-4
        add.m   r6,sp,#0
	version r0
	st r0, (r6)
	add.m sp, r6, #4
	ldm r6,pc,(sp++)

        .section        .text.btest_run,"ax",@progbits
        .p2align        1
        .globl  btest_run
        .type   btest_run, @function
btest_run:	
	stm     r6,lr,(--sp)
        add.m   sp,sp,#-8
        add.m   r6,sp,#0
	st r0, (r6)
	ld r0, (r6)
	st r1, (r6+4)
	ld r1, (r6+4)
	btest r0, r1
	mov r0, sr
	add.m sp, r6, #8
	ldm r6,pc,(sp++)
	
        .section        .text.get_status_register,"ax",@progbits
        .p2align        1
        .globl  get_status_register
        .type   get_status_register, @function
get_status_register:
	stm r6,lr,(--sp)
	add.m sp,sp,#-4
	add.m r6,sp,#0
	mov r0, sr
	st r0, (r6)
	add.m sp, r6, #4
	ldm r6,pc,(sp++)
	
