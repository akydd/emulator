        LOAD  A1,DATA1   # 0:  [60 03 00 30] load address DATA1 into A1
        LOADI R1,A1      # 4:  [61 C1] load contents of address in A1 into R1
        LOAD  A2,DATA2   # 6:  [60 02 00 32] load address DATA2 into A2
        LOADI R2,A2      # 10: [61 80] load contents of address in A2 into R2
        OUTI  A1         # 12: [70 03] output contents of address in A1 as a number
        OUTC  43         # 14: [6d 00 00 2b] output ASCII character 43 ('+')
        OUTI  A2         # 18: [70 02] output contents of address in A2 as a number
        OUTC  61         # 20: [6d 00 00 3d] output ASCII character 61 ('=')
        ADDR  R1,R2      # 24: [69 01] add contents of register R2 to R1 and store in R1
        STORE R1,RESULT  # 26: [62 01 00 34] store contents of register R1 to address RESULT
        LOAD  A2,RESULT  # 30: [60 02 00 34] load the address of RESULT
        LOADI R2,A2      # 34: [61 80] load the value of RESULT
        OUTR  R2         # 36: [6e 00] output contents of register R2 as a number
        OUTC  12         # 38: [6d 00 00 0c] output a carriage return
        OUTC  13         # 42: [6d 00 00 0d] output a line feed
        HALT             # 46: [31 00] Adieu, mon ami!
DATA1   DATA  251        # 48: [00 fb] This is -5
DATA2   DATA  249        # 50: [00 f9] This is -7
RESULT  DATA  0          # 52: [00 00]

