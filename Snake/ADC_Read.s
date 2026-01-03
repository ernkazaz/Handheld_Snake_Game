; ADC_Read.s

        AREA    |.text|, CODE, READONLY, ALIGN=2
        THUMB
        EXPORT  ADC_Read


ADC_Read
       
        LDR R1, =0x40038028  
        LDR R0, [R1]
        ORR R0, R0, #0x08 
        STR R0, [R1]
        
wait_loop
        LDR R1, =0x40038004 
        LDR R0, [R1]
        ANDS R0, R0, #0x08  
        BEQ wait_loop       

        LDR R1, =0x4003800C  
        LDR R0, [R1]
        ORR R0, R0, #0x08  
        STR R0, [R1]

        LDR R1, =0x400380A8  
        LDR R0, [R1] 
        
        BX LR   
        ALIGN
        END