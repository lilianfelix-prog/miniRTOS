	.file	"sbrk.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	heap_ptr
	.section	.sdata,"aw"
	.align	3
	.type	heap_ptr, @object
	.size	heap_ptr, 8
heap_ptr:
	.dword	__end
	.text
	.align	1
	.globl	_sbrk
	.type	_sbrk, @function
_sbrk:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	mv	a5,a0
	sb	a5,-33(s0)
	lui	a5,%hi(heap_ptr)
	ld	a5,%lo(heap_ptr)(a5)
	sd	a5,-24(s0)
	lui	a5,%hi(heap_ptr)
	ld	a4,%lo(heap_ptr)(a5)
	lbu	a5,-33(s0)
	slli	a5,a5,2
	add	a5,a4,a5
	sd	a5,-32(s0)
	lui	a5,%hi(heap_ptr)
	ld	a4,-24(s0)
	sd	a4,%lo(heap_ptr)(a5)
	ld	a5,-24(s0)
	mv	a0,a5
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	_sbrk, .-_sbrk
	.ident	"GCC: (SiFive GCC-Metal 10.2.0-2020.12.8) 10.2.0"
