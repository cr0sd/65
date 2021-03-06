; MASM x86_64 assembly program
; Modified from C source to cut out unnecessary bits
INCLUDE listing.inc
INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	i
EXTRN	__imp_CloseHandle:PROC
EXTRN	__imp_WaitForSingleObject:PROC
EXTRN	__imp_CreateProcessA:PROC
EXTRN	__imp_GetStartupInfoA:PROC

_DATA	SEGMENT
cmd DB	'bin/fes.exe test/vram.nes',0
_DATA	ENDS

_TEXT	SEGMENT
procinfo$ = 80
info$ = 112
i	PROC
$LN3:
	sub	rsp, 232

	lea	rcx, QWORD PTR info$[rsp]
	call	QWORD PTR __imp_GetStartupInfoA

	lea	rax, QWORD PTR procinfo$[rsp]
	mov	QWORD PTR [rsp+72], rax
	lea	rax, QWORD PTR info$[rsp]
	mov	QWORD PTR [rsp+64], rax
	mov	QWORD PTR [rsp+56], 0
	mov	QWORD PTR [rsp+48], 0
	mov	DWORD PTR [rsp+40], 0
	mov	DWORD PTR [rsp+32], 0
	xor	r9d, r9d
	xor	r8d, r8d
	lea	rdx, OFFSET cmd
	xor	ecx, ecx
	call	QWORD PTR __imp_CreateProcessA

	mov	edx, -1
	mov	rcx, QWORD PTR procinfo$[rsp]
	call	QWORD PTR __imp_WaitForSingleObject

	mov	rcx, QWORD PTR procinfo$[rsp]
	call	QWORD PTR __imp_CloseHandle

	mov	rcx, QWORD PTR procinfo$[rsp+8]
	call	QWORD PTR __imp_CloseHandle

	mov	eax, 88

	add	rsp, 232
	ret	0
i	ENDP
_TEXT	ENDS
END
