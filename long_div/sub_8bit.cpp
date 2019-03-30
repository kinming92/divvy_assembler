////////////////////////////////////////////////////////

//Substract  a - b using 8 bit variable

//////////////////////////////////////////////////////

#include <iostream>
#include <bitset>
#include <stdint.h>
using namespace std;

int main() {
  uint32_t a = 0x0d0a00;
  uint32_t b = 0x00000c;
  uint32_t result;

  result = a-b;
  cout << "a: " << bitset<24>(a) << endl;
  cout << "b: " << bitset<24>(b) << endl;
  cout << "result: "<< bitset<24>(result)<<endl;

  uint8_t a_0 = 0x00;
  uint8_t a_1 = 0x0a;
  uint8_t a_2 = 0x0d;

  uint8_t b_0 = 0x0c;
  uint8_t b_1 = 0x00;
  uint8_t b_2 = 0x00;

  cout << "a: " << bitset<8>(a_2) << " " << bitset<8>(a_1) << " " << bitset<8>(a_0) << endl;
  cout << "b: " << bitset<8>(b_2) << " " << bitset<8>(b_1) << " " << bitset<8>(b_0) << endl;

  uint8_t temp;
  temp = 0x01;

  temp = ~(temp);

  //a - b
  if ( a_0 <= b_0){
    if(a_1 <= b_1){
      if(b_2 == 0){
          a_2 = a_2 + temp;
          a_2 += 1;
        }

      if(a_1 == 0){
        a_1 = ~a_1;
      }
    }else{ // a_1 > b_1
      a_1 = a_1 + temp;
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
  cout << "result: "<< bitset<8>(a_2) << " " << bitset<8>(a_1) << " " << bitset<8>(a_0) <<endl;

  return 0;


}
