        .section        .text.strlen,"ax",@progbits
        .p2align        1
        .globl  strlen
        .type   strlen, @function
strlen:
	add.m   sp,sp,#-16
        add.m   r6,sp,#0
        st.s    r0,(r6+8)  	; original pointer
	st.s    r1,(r6+12)      ; save whatever was here
        mov.s   r1,#0           ; counter = 0
        st.s    r1,(r6)         ; put that into the stack frame
        st.s    r0,(r6+4)       ; store a copy
	b       count_loop
	
add_count:
	ld.s    r0, (r6+4)      ; load the work pointer
	add.s   r1, #1		; increment the counter
	add.s   r0, #1		; increment to the next byte
	st.s    r0, (r6+4)	; save that
	
count_loop:
	ldb.s   r0, (r0)	; load the byte pointed to
	cmp.s   r0, #0		; is it NULL ?
	bne     add_count	; no, increment the counter and the pointer
        st.s    r0,(r6+4)	; save the count for return
	mov     r0, r1          ; return value
        add.m   sp,r6,#16	; restore the stack-frame
        ldm     r6,(sp++)	; restore the original r6 and sp
        rts			; return
