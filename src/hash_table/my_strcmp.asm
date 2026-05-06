segment .text

global my_strcmp

default rel

my_strcmp:
    vmovdqu     ymm0, [rdi]
    vmovdqu     ymm1, [rsi]

    vpcmpeqb    ymm2, ymm0, ymm1
    vpmovmskb   eax, ymm2

    mov         ecx, edx
    cmp         ecx, 32
    je          .full_mask
    mov         edx, 1
    shl         edx, cl
    sub         edx, 1
    jmp         .done
.full_mask:
    mov         edx, -1
.done:
    
    xchg        ecx, edx

    and         eax, edx
    cmp         eax, edx
    setne       al
    movzx       eax, al
    
    vzeroupper
    ret
