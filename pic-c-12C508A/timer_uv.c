//#include "C:\Users\r5527821\Dropbox\pic\projpic\time_uv\timer_uv.h"
#include "timer_uv.h"
#use fast_io(b)

 void pulso_clock()
   {
      output_high(pin_b0); // 
      output_low(pin_b0);
      //SHCP Low
      
   }
 
   void contar(unsigned int8 numero)
   {
   
   int8 databits;
    switch(numero){
      case 0:numero=0xc0;      break;
      case 1:numero= 0xF9;      break;
      case 2:numero= 0xA4;      break;
      case 3:numero= 0xB0;      break;
      case 4:numero= 0x99;      break;
      case 5:numero= 0x92;      break;
      case 6:numero= 0x82;      break;
      case 7:numero= 0xF8;      break;
      case 8:numero= 0x80;      break;
      case 9:numero= 0x90;      break;
    }
    
      //case 'L':return 0xc7;      break;
      //case 'A':return 0x88;      break;
      //case 'P':return 0x8c;      break;
      //case 'C':return 0xc6;      break;
      //case 'E':return 0x86;      break;
      //case 'F':return 0x86;      break;
      //case 'b':return 0x83;      break;
      //case 'u':return 0xC1;      break;
      //case '-':return 0xbf;      break;
   
   
   
   
      output_low(pin_b1); // Set latch
      for(databits=0; databits<8; databits++){
         if(numero & 0b10000000){
            output_high(pin_b4); // Set data
         }else{
            output_low(pin_b4);
         }
         pulso_clock();
         numero <<= 1;
      }
      output_high(pin_b1); // Set latch
   }
 
void time(){
   delay_ms(502);
}

void ola(){
   contar(247); 
   contar(247); 
   contar(247);
   time();  
   contar(191);
   contar(191);
   contar(191);
   time();
   contar(254); 
   contar(0b11111110);
   contar(254);  
   time();
   contar(0b10001000); //a
   contar(0b11000111);//l
   contar(0xc0);     //o
}

void pause(){
   contar(0b11000001);  //u
   contar(0b10001000); //a
   contar(0b10001100); //p
   time();   
   contar(0b10000110); //E
   contar(0x92); //s
   contar(0b10111111);  //-
   time();
}

void on(){
   contar(0b10000110);  //e
   contar(0xc6); //c
   contar(0b10001000); //a
   time();
   contar(0xc0);  //o
   contar(0x92); //s
   contar(0b10111111); //-
   time();
}

void of(){
   contar(0b10001110);  //f
   contar(0b10001110); //f
   contar(0xc0); //o 
}

void main()
{
   
   unsigned int8 cont,giro,seg,min;
   unsigned long tempo;

   set_tris_b(0b00001100); 
   output_b(0b00000000);   
   ola();
   cont=min=seg=0;
   
while(true)
{
   if (input(PIN_B3)) {
      seg++;
      if(seg>=6) {
         seg=0; 
         if(min<9)min++;
      }
      time();
      cont=min*10+seg;
      contar(0xc0);
      contar(seg);
      contar(min);      
   }   
   if (input(PIN_B2)){
      if(cont>0){
         tempo=min;
         tempo= (tempo*60)+(seg*10);
         while(tempo>0){ 
            output_high(pin_b5);
            time();
            //=======================
            if(input(PIN_B2)){
               output_low(pin_b5);
               time();
               while(!input(PIN_B2)){  
                  pause();
                 // time();
               }          
             }
             //=======================           
            time();
            tempo--;             
            giro=(tempo%60);
            min=(tempo-giro)/60;            
            seg=(giro-(giro%10))/10;
            contar(tempo%10);
            contar(seg);
            contar(min);             
          }        
      }else{        
            time();
            if (input(pin_b2)){
                output_high(pin_b5);
                 time(); 
                while(!input(pin_b2)){
                 on();             
                }
             }
         time();
      }
      output_low(pin_b5); 
      of();
      seg=min=cont=0;          
   }  
}
}

