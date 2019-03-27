//////////////////////////////////////////////////////////
//work on progress
/////////////////////////////////////////////////////////////////////
//8bit variable
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <bitset>
#include <stdint.h>

void var_8_ver_2(uint8_t, uint8_t, uint8_t);
void var_8(uint8_t, uint8_t, uint8_t);

using namespace std;
int main() {
//16 bit dividend
uint8_t Mdividend = 0x00;
uint8_t Ldividend = 0x01;

//8 bit divisor
uint8_t divisor = 0x03;

var_8_ver_2(Mdividend, Ldividend, divisor);
var_8(Mdividend, Ldividend, divisor);

}

void var_8_ver_2(uint8_t Mdividend, uint8_t Ldividend, uint8_t divisor){
//16 bit quotient and 8 bit decimal point
uint8_t Mquotient = 0;
uint8_t Lquotient = 0;
uint8_t quot_dp = 0;


uint8_t Mdividend_cp = Mdividend;
uint8_t Ldividend_cp = Ldividend;
uint8_t divisor_cp_2 = divisor;
uint8_t divisor_cp_1 = 0;
uint8_t divisor_cp_0 = 0;

uint8_t temp;
uint8_t temp2;

if(divisor == 0){
  Mquotient = 0xff;
  Lquotient = 0xff;
  quot_dp = 0xff;
  cout << "dividend: "<< bitset<8>(Mdividend) << " " << bitset<8>(Ldividend) <<endl;
  cout << "divisor: "<< bitset<8>(divisor)    <<endl;
  cout << "quotient: "<< bitset<8>(Mquotient) << " " << bitset<8>(Lquotient) <<endl;
  cout << "quotientdp: " << bitset<8>(quot_dp) <<endl;
  return;
  
}

while(  (divisor_cp_2 > 0) 
        ||	(divisor_cp_1 > 0)
        ||	(divisor_cp_0 >= divisor)	)
{
  
  if(	divisor_cp_2 > 0 
		|| divisor_cp_1 > Mdividend_cp
		|| (divisor_cp_1 == Mdividend_cp && divisor_cp_0 > Ldividend_cp)	)
  
  {
    //quotient <<= 1;
    //save the MSB of Lquotient
    int temp = Lquotient & 0x80;
    temp >>= 7;
    Lquotient <<= 1;
    Mquotient <<= 1;
    Mquotient |= temp;
    
  }else{
    //quotient <<= 1;
    
    temp = Lquotient & 0x80;
    temp >>= 7;
    Lquotient <<= 1;
    Mquotient <<= 1;
    Mquotient |= temp;

    //quotient |= 1;
    Lquotient |= 1;
    //divd -= divs;
    if ( Ldividend_cp < divisor_cp_0 ){
      temp = 0x01;
      temp = ~(temp);
      Mdividend_cp = Mdividend_cp + temp;
      Mdividend_cp = Mdividend_cp + 1;
    }
    
    temp = divisor_cp_0;
    temp = ~ ( divisor_cp_0 );
    Ldividend_cp = Ldividend_cp + temp;
    Ldividend_cp = Ldividend_cp + 1;
    
    temp = ~( divisor_cp_1);
    Mdividend_cp = Mdividend_cp + temp;
    Mdividend_cp = Mdividend_cp + 1;
  } //end of else
	  
  //divs >>= 1;
  temp = divisor_cp_2 & 0x01;
  temp <<= 7;
  divisor_cp_2 >>= 1;
	
	temp2 = divisor_cp_1 & 0x01;
	temp2 <<= 7;
	divisor_cp_1 >>= 1;
	divisor_cp_1 |= temp;
	
	divisor_cp_0 >>= 1;
	divisor_cp_0 |= temp2;

}
  
if (Mdividend_cp == 0 && Ldividend_cp == 0){
  std::cout<<"no remainder"<< std::endl;
  std::cout<<"store the decimalpoint back to the data mem"<< std::endl;
}

int i = 0;
while (i<8){
  //cout << "dividend_cp: "<< bitset<8>(Mdividend_cp) << " " << bitset<8>(Ldividend_cp) <<endl;
  //dividend_cp <<= 1;
  temp = Ldividend_cp & 0x80;
  temp >>= 7;
  Ldividend_cp <<= 1;
  Mdividend_cp <<= 1;
  Mdividend_cp |= temp;
  //cout << "temp: " << bitset<8>(temp) <<endl;
  // cout << "Before::::dividend_cp: "<< bitset<8>(Mdividend_cp) << " " << bitset<8>(Ldividend_cp) <<endl;
  //dividend_cp >= divisor
  if( (Mdividend_cp > 0) ||  Ldividend_cp >= divisor){
	// quotient_dp <<= 1
	quot_dp <<= 1;
	quot_dp |= 1;
  //cout << "Before - \t";
  //cout << "dividend_cp: "<< bitset<8>(Mdividend_cp) << " " << bitset<8>(Ldividend_cp) <<endl;
	// dividend_cp -= divisor
	if ( Ldividend_cp < divisor ){
      temp = 0x01;
      temp = ~(temp);
      Mdividend_cp = Mdividend_cp + temp;
      Mdividend_cp = Mdividend_cp + 1;
    }
    
    temp = divisor;
    temp = ~ ( divisor );
    Ldividend_cp = Ldividend_cp + temp;
    Ldividend_cp = Ldividend_cp + 1;
    
    temp = ~(0);
    Mdividend_cp = Mdividend_cp + temp;
    Mdividend_cp = Mdividend_cp + 1;

  //cout << "After - \t";
  //cout << "dividend_cp: "<< bitset<8>(Mdividend_cp) << " " << bitset<8>(Ldividend_cp) <<endl;
  
  }else{
	  quot_dp <<= 1;
  }
  
  i++;
}


cout << "dividend: "<< bitset<8>(Mdividend) << " " << bitset<8>(Ldividend) <<endl;
cout << "divisor: "<< bitset<8>(divisor)    <<endl;
cout << "quotient: "<< bitset<8>(Mquotient) << " " << bitset<8>(Lquotient) <<endl;
cout << "quotientdp: " << bitset<8>(quot_dp) <<endl;

}


void var_8(uint8_t Mdividend, uint8_t Ldividend, uint8_t divisor){

  uint8_t divisor_cp_0 = 0;
  uint8_t divisor_cp_1 = 0;
  uint8_t divisor_cp_2 = 0;
  uint8_t divisor_cp_3 = divisor;
  
  uint8_t dividend_cp_0 = 0;
  uint8_t dividend_cp_1 = Ldividend;
  uint8_t dividend_cp_2 = Mdividend;

  uint8_t quotient_0 = 0;
  uint8_t quotient_1 = 0;
  uint8_t quotient_dp = 0;


  uint8_t i = 0;
  uint8_t temp;
  uint8_t temp2;

  while(i<25){
    if( divisor_cp_3 > 0
      || (divisor_cp_2 == dividend_cp_2 && divisor_cp_1 > dividend_cp_1 )
      || (divisor_cp_2 == dividend_cp_2 && divisor_cp_1 == dividend_cp_1 && divisor_cp_0>dividend_cp_0)
      ){
            //quotient <<= 1;
            temp = quotient_dp & 0x80;
            temp >>= 7;
            
            temp2 = quotient_0 & 0x80;
            temp2 >>= 7;
            
            quotient_dp <<= 1;
            quotient_0 <<= 1;
            quotient_1 <<= 1;
            
            quotient_0 |= temp;
            quotient_1 |= temp2;

      }else{
        	//quotient <<= 1;
            temp = quotient_dp & 0x80;
            temp >>= 7;
            
            temp2 = quotient_0 & 0x80;
            temp2 >>= 7;
            
            quotient_dp <<= 1;
            quotient_0 <<= 1;
            quotient_1 <<= 1;
            
            quotient_0 |= temp;
            quotient_1 |= temp2;
    	    //quotient |= 1;
            quotient_dp |= 1;
    	    //divd -= divs;
            temp = 0x01;
            temp = ~(temp);
            //a - b
            if ( dividend_cp_0 <= divisor_cp_0 ){
              if( dividend_cp_1 <= divisor_cp_1 ){
                dividend_cp_1 = dividend_cp_1 + temp;
                dividend_cp_1 += 1;
                dividend_cp_2 += temp;
                dividend_cp_2 += 1;
              }else{
                dividend_cp_1 += temp;
                dividend_cp_1 += 1;
              }
            }
            temp = ~ ( divisor_cp_0 );
            dividend_cp_0 += temp;
            dividend_cp_0 += 1;

            temp = ~( divisor_cp_1);
            dividend_cp_1 += temp;
            dividend_cp_1 += 1;

            temp = ~(divisor_cp_3);
            dividend_cp_2 += temp;
            dividend_cp_2 += 1;
            //cout << "result: "<< bitset<8>(a_2) << bitset<8>(a_1) << bitset<8>(a_0)   <<endl;
      }// end of else
	
	//divs >>= 1;
    //i++;
	temp = divisor_cp_3 & 0x01;
	temp <<= 7;
	
	divisor_cp_3 >>= 1;
	
	temp2 = divisor_cp_2 & 0x01;
	temp<<= 7;
	
	divisor_cp_2 >>= 1;
	divisor_cp_2 |= temp;
	
	temp = divisor_cp_1 & 0x01;
	temp <<= 7;
	
	divisor_cp_1 >>= 1;
	divisor_cp_1 |= temp2;

	divisor_cp_0 >>= 1;
	divisor_cp_0 |= temp;
	
	i++;
	
  }// end of while loop

  cout << "quotient: "<< bitset<8>(quotient_1) << " " << bitset<8>(quotient_0)<< endl;
	cout << "quot_dp: " << bitset<8>(quotient_dp) <<endl;

}