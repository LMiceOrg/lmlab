/** Copyright 2018, 2019 He Hao<hehaoslj@sina.com> */
#include <stdio.h>

extern "C" int add(int, int);
int main() {
  wprintf(L"execute manager %d\n", add(12, 23));
  return 0;
}
