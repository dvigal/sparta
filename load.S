load:
    push dx 
    mov ah, 0x02
    mov al, dh  
    mov ch, 0   
    mov cl, 2   
    mov dh, 0   
    int 0x13    
    jc load_error
    pop dx       
    cmp al, dh   
                  
    jne load_error
    ret

load_error:
    mov bx, load_err_msg
    call print
    jmp $

load_err_msg: db "Cannot load from disk", 0