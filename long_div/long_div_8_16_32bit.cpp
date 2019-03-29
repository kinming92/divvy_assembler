//16/32/8 bit variable

//one while loop

#include <iostream>
#include <stdint.h>
#include <bitset>

void func2(uint16_t, uint8_t);
void func(uint16_t,uint8_t);
using namespace std;

int main()
{
  uint16_t dividend = 0x0010;
  uint8_t divisor =  0x03;

func2(dividend, divisor);
func(dividend, divisor);
}

void func2(uint16_t dividend, uint8_t divisor){
  uint32_t divs = divisor;  // we actually need 32 bit for this problem
  uint32_t divd = dividend; // we actually need 16+8 bit for this problem
  uint32_t quotient = 0; //quotient should be 24 bit
  divd <<= 8;
  divs = divs << 24;
  //cout << "div: "<<  bitset<32>(divs) << endl;
  //cout <<"divd: "<< bitset<16>(divd) << endl;
 
 int j = 0;
while( j<25 ){
	if ( divs > divd ){
    	quotient <<= 1;
	}
	else {
    	quotient <<= 1;
    	quotient |= 1;
    	divd -= divs;
	}
    	divs >>= 1;
      j++;
      //cout << "divs: " << bitset<32>(divs) << endl;
      //cout << "divd: " << "----------------" << bitset<16>(divd) << endl;
}

cout << "dividend: "<< bitset<16>(dividend)  <<endl;
cout << "divisor: "<< bitset<8>(divisor) <<endl;
cout << "quotient: "<< bitset<24>(quotient) <<endl;

}

void func(uint16_t n, uint8_t d){
  uint16_t rem = 0;
  uint16_t dividend = n;
  uint16_t quotient = 0;
  uint8_t quotientdp = 0;
  uint8_t divisor =  d;

  uint32_t divs = divisor;
  uint16_t divd = dividend;
  divs = divs << 16;
 
while( divs >= divisor ){
	if ( divs > divd ){
    	quotient <<= 1;
	}
	else {
    	quotient <<= 1;
    	quotient |= 1;
    	divd -= divs;
	}
    	divs >>= 1;
}
rem = divd;
if (divd == 0){
  //cout<<"no remainder"<<endl;
  //cout<<"store the decimalpoint back to the data mem"<<endl;
}

int i = 0;
while (i<8){
  //cout << "rem: " << bitset<16>(rem) << endl;
  rem <<= 1;
  if(rem >= divisor){

	  quotientdp <<= 1;
	  quotientdp |= 1;
    //cout << "Before - \t";
   // cout << "rem: " << bitset<16>(rem) << endl;
	  rem -= divisor;
    //cout << "after - \t";
    //cout << "rem: " << bitset<16>(rem) << endl;
  }else{
	  quotientdp <<= 1;
  }
  i++;
}
  cout << "quotient: "<< bitset<16>(quotient);
	cout << "" << bitset<8>(quotientdp) <<endl;
}