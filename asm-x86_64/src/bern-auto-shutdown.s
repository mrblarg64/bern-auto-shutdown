		.data
AC_STATUS_FILE:
	.string "/sys/class/power_supply/ACAD/online"
BATTERY_STATUS_FILE:
	.string "/sys/class/power_supply/BAT1/capacity"
SHUTDOWN_CMD:
	.string "/sbin/shutdown"
arg0:
	.string "shutdown"
arg1:
	.string "-h"
arg2:
	.string "now"
SHUTDOWN_ARGS:
	.quad arg0
	.quad arg1
	.quad arg2
	.quad 0

timespec:
	.quad 60
	.quad 0

buf:
	.int

	
	.globl _start
	.text
_start:
	mov $2, %rax #open
	mov $AC_STATUS_FILE, %rdi
	mov $0, %rsi
	syscall
	cmp $0, %eax
	jl failed
	
	mov %eax, %edi
	mov $0, %rax #read
	mov $buf, %rsi
	mov $1, %rdx
	syscall
	cmp $0, %rax
	je failed

	mov $3, %rax #close
	syscall	

	cmpb $48, buf #48 = '0'
	je checkbattery

sleeploop:

	mov $35, %rax #nanosleep
	mov $timespec, %rdi
	mov $0, %rsi
	syscall
	jmp _start
	
checkbattery:
	mov $2, %rax #open
	mov $BATTERY_STATUS_FILE, %rdi
	mov $0, %rsi
	syscall
	cmp $0, %eax
	jl failed
	
	mov %eax, %edi
	mov $0, %rax #read
	mov $buf, %rsi
	mov $4, %rdx
	syscall
	cmp $0, %rax
	je failed

	mov %rax, %rsi
	mov $3, %rax #close
	syscall

	cmp $3, %rsi  #less than 3 therefore 1 number and a newline (less than 10%)
	jl shutdown
	jg sleeploop
	cmpb $49, buf #49 = '1'
	jne sleeploop
	cmpb $53, (buf + 1) #53 = '5'
	jle shutdown
	jmp sleeploop

shutdown:
	mov $59, %rax #execve
	mov $SHUTDOWN_CMD, %rdi
	mov $SHUTDOWN_ARGS, %rsi
	mov $0, %rdx
	syscall
	
failed:	
	mov $60, %rax #exit
	mov $1, %rdi
	syscall

