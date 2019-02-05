        .section        .text.strlen,"ax",@progbits
        .p2align        1
        .globl  strlen
        .type   strlen, @function
strlen:
	add.m   sp,sp,#-12
        add.m   r6,sp,#0
        st.s    r0,(r6+8)  	; original pointer
        mov.s   r0,#0           ; counter = 0
        st.s    r0,(r6)         ; put that into the stack frame
        ld.s    r0,(r6+8)       ; load the original
        st.s    r0,(r6+4)       ; store a copy
	b       count_loop
	
add_count:
	ld.s    r0, (r6)	; load the counter
	add.s   r0, #1		; increment it
	st.s    r0, (r6)	; save it
	ld.s	r0, (r6+4)	; load the work pointer
	add.s   r0, #1		; increment it to the next byte
	st.s    r0, (r6+4)	; save that
	
count_loop:
	ld.s    r0, (r6+4)      ; load the work pointer
	ldb.s   r0, (r0)	; load the byte pointed to
	cmp.s   r0, #0		; is it NULL ?
	bne     add_count	; no, increment the counter and the pointer
        ld.s    r0,(r6)		; save the count for return
        add.m   sp,r6,#12	; restore the stack-frame
        ldm     r6,(sp++)	; restore the original r6 and sp
        rts			; return
