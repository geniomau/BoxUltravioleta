//#include <16f628a.h>
#include <12C508A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC                    //Internal RC Osc
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOMCLR                   //Master Clear pin used for I/O

#use delay(clock=4000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_B0,bits=8)

