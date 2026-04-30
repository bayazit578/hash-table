segment .text

global my_strcmp

default rel
my_strcmp:
    vmovdqu     ymm0, [rdi]
    vmovdqu     ymm1, [rsi]
    
    vpxor       ymm2, ymm2, ymm2
    
    vpcmpeqb    ymm3, ymm0, ymm1
    vpcmpeqb    ymm0, ymm0, ymm2
    vpcmpeqb    ymm1, ymm1, ymm2
    
    vpmovmskb   eax, ymm3
    vpmovmskb   ecx, ymm0
    vpmovmskb   edx, ymm1
    
    or          ecx, edx
    jz          .no_terminator
    
    ;есть нуль-терминатор
    tzcnt       ecx, ecx
    mov         edx, 1
    shlx        edx, edx, ecx
    sub         edx, 1
    
    and         eax, edx
    cmp         eax, edx
    sete        al
    movzx       eax, al
    vzeroupper
    ret

.no_terminator:
    cmp         eax, -1
    sete        al
    movzx       eax, al
    vzeroupper
    ret
