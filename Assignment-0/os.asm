segment .data
	x dq 0
	scanf_format db "%ld", 0
	scanf_format_str db "%s", 0
	msg_num db "Number entered is: %ld", 0x0a, 0
	msg_str db "String entered is: %s", 0x0a, 0

segment .bss
	string resb 100

segment .text
	global main
	global fact
	extern scanf
	extern printf

main:
	push rbp
	mov rbp, rsp

; SCANF CALL
	lea rdi, [scanf_format]
	lea rsi, [x]
	xor eax, eax
	call scanf

	lea rdi, [scanf_format_str]
	lea rsi, [string]
	xor eax, eax
	call scanf

; PRINTF CALL
	lea rdi, [msg_num]
	mov rsi, [x]
	xor eax, eax
	call printf


	lea rdi, [msg_str]
	mov rsi, string
	xor eax, eax
	xor rax, rax
	call printf
	xor rsi, rsi

; EXIT STATUS 0
	xor eax, eax
	leave
	exit
