#include <stdlib.h>
#include <api.h>
#include <stdbool.h>


void sendIntToSlave(int msgArray[3],int id);
void sendIntToMaster(int msgArray[3]);
int ReceiveFromSlave(int id);
bool isPair(int val);