////////////////////////////////////////////////////////

//Substract  a - b using 8 bit variable

//////////////////////////////////////////////////////

#include <iostream>
#include <bitset>
#include <stdint.h>
using namespace std;

int main() {
  uint32_t a = 0x800f00;
  uint32_t b = 0xf9fccf;
  uint32_t result;

  result = a-b;
  cout << "result: "<< bitset<24>(result)<<endl;

  uint8_t a_0 = 0x00;
  uint8_t a_1 = 0x0f;
  uint8_t a_2 = 0x80;

  uint8_t b_0 = 0xcf;
  uint8_t b_1 = 0xfc;
  uint8_t b_2 = 0xf9;

  uint8_t temp;
  temp = 0x01;

  temp = ~(temp);
  //a - b
  if ( a_0 <= b_0 ){
    if( a_1 <= b_1 ){
      a_1 = a_1 + temp;
      a_1 += 1;
      a_2 = a_2 + temp;
      a_2 += 1;
    }else{
      a_1 += temp;
      a_1 += 1;
    }
  }
  temp = ~ ( b_0 );
  a_0 = a_0 + temp;
  a_0 += 1;

  temp = ~( b_1);
  a_1 += temp;
  a_1 += 1;

  temp = ~(b_2);
  a_2 += temp;
  a_2 += 1;
  cout << "result: "<< bitset<8>(a_2) << bitset<8>(a_1) << bitset<8>(a_0)     <<endl;

  return 0;


}
