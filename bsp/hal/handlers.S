/*
* Copyright 2019 ETH Zürich and University of Bologna
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/* Exception codes */
#define EXCEPTION_INS_ACCESS_FAULT 1
#define EXCEPTION_ILLEGAL_INSN 2
#define EXCEPTION_BREAKPOINT 3
#define EXCEPTION_ECALL_M 11

.section .text.handlers
.global __no_irq_handler
.global sw_irq_handler
.global __timer_irq_handler
.global verification_irq_handler

//.global timer_irq   

# #define ASSERT_SAVED(reg,offset) ld reg,(8+offset)(sp) \
# 								jal printf
/* exception handling */
__no_irq_handler:
	la a0, no_exception_handler_msg
	jal ra, puts
	j __no_irq_handler

__timer_irq_handler:
	//ebreak
	# addi sp,sp,-128
	# sd ra, 0  (sp)
	# sd t0, 8  (sp)
	# sd t1, 16 (sp)
	# sd t2, 24 (sp)
	# sd a0, 32 (sp)
	# sd a1, 40 (sp)
	# sd a2, 48 (sp)
	# sd a3, 56 (sp)
	# sd a4, 64 (sp)
	# sd a5, 72 (sp)
	# sd a6, 80 (sp)
	# sd a7, 88 (sp)
	# sd t3, 96 (sp)
	# sd t4, 104(sp)
	# sd t5, 112(sp)
	# sd t6, 120(sp)
	//Check saved values (automatic or not)
	//csrr a1, 0x7c7
	//la a0, print_shadow_status_msg
	//jal printf
	//Second time for fun
	//csrr a1, 0x7c7
	//la a0, print_shadow_status_msg
	//jal printf
	csrr a1, 0x7c6
	mv a0, sp
	jal timer_irq
	//Restore context
	ld ra, 0  (sp)
    ld t0, 8  (sp)
    ld t1, 16 (sp)
    ld t2, 24 (sp)
    ld a0, 32 (sp)
    ld a1, 40 (sp)
    ld a2, 48 (sp)
    ld a3, 56 (sp)
    ld a4, 64 (sp)
    ld a5, 72 (sp)
    ld a6, 80 (sp)
    ld a7, 88 (sp)
    ld t3, 96 (sp)
    ld t4, 104(sp)
    ld t5, 112(sp)
	li t6, (0x1 << 26)
	csrs 0x7C7, t6
    ld t6, 120(sp)
    addi sp,sp, 128
    mret

sw_irq_handler:
	/* While we are still using puts in handlers, save all caller saved
	   regs.  Eventually, some of these saves could be deferred.  */
	# addi sp,sp,-128
	# sd ra, 0  (sp)
	# sd t0, 8  (sp)
	# sd t1, 16 (sp)
	# sd t2, 24 (sp)
	# sd a0, 32 (sp)
	# sd a1, 40 (sp)
	# sd a2, 48 (sp)
	# sd a3, 56 (sp)
	# sd a4, 64 (sp)
	# sd a5, 72 (sp)
	# sd a6, 80 (sp)
	# sd a7, 88 (sp)
	# sd t3, 96 (sp)
	# sd t4, 104(sp)
	# sd t5, 112(sp)
	# sd t6, 120(sp)
	csrr t0, mcause
	li t1, EXCEPTION_INS_ACCESS_FAULT
	beq t0, t1, handle_access_fault
	li t1, EXCEPTION_ILLEGAL_INSN
	beq t0, t1, handle_illegal_insn
	li t1, EXCEPTION_ECALL_M
	beq t0, t1, handle_ecall
	li t1, EXCEPTION_BREAKPOINT
	beq t0, t1, handle_ebreak
	j handle_unknown

handle_ecall:
	jal ra, handle_syscall
	j end_handler_incr_mepc

handle_ebreak:
	/* TODO support debug handling requirements.  */
	la a0, ebreak_msg
	jal ra, puts
	j end_handler_incr_mepc

handle_access_fault:
	la a0, access_fault_msg
	csrr a1, mepc
	jal ra, printf
	j end_handler_incr_mepc

handle_illegal_insn:
	la a0, illegal_insn_msg
	//jal ra, puts
	csrr a1, mepc
	jal ra, printf
	j end_handler_incr_mepc

handle_unknown:
	la a0, unknown_msg
	jal ra, puts
	/* We don't know what interrupt/exception is being handled, so don't
	   increment mepc.  */
	j end_handler_ret

end_handler_incr_mepc:
	csrr t0, mepc
	lb t1, 0(t0)
	li a0, 0x3
	and t1, t1, a0
	/* Increment mepc by 2 or 4 depending on whether the instruction at mepc
	   is compressed or not.  */
	bne t1, a0, end_handler_incr_mepc2
	addi t0, t0, 2
end_handler_incr_mepc2:
	addi t0, t0, 2
	csrw mepc, t0
end_handler_ret:
	ld ra, 0  (sp)
    ld t0, 8  (sp)
    ld t1, 16 (sp)
    ld t2, 24 (sp)
    ld a0, 32 (sp)
    ld a1, 40 (sp)
    ld a2, 48 (sp)
    ld a3, 56 (sp)
    ld a4, 64 (sp)
    ld a5, 72 (sp)
    ld a6, 80 (sp)
    ld a7, 88 (sp)
    ld t3, 96 (sp)
    ld t4, 104(sp)
    ld t5, 112(sp)
    ld t6, 120(sp)
    addi sp,sp, 128
	mret
/* this interrupt can be generated for verification purposes, random or when the
   PC is equal to a given value*/
verification_irq_handler:
	mret

.section .rodata
access_fault_msg:
	.string "instruction access fault @%x\n"
illegal_insn_msg:
	.string "illegal instruction exception handler entered @%x\n"
ecall_msg:
	.string "ecall exception handler entered\n"
ebreak_msg:
	.string "ebreak exception handler entered\n"
unknown_msg:
	.string "unknown exception handler entered\n"
no_exception_handler_msg:
	.string "no exception handler installed\n"
print_shadow_status_msg:
	.string "Shadow status: %lx\n"
