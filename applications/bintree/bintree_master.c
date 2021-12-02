#include <stdlib.h>
#include <api.h>

///////// DONT CHANGE
// REMOVE VALUES BEFORE COMPILING
// begin
#define MSG_LENGHT			2
#define NUMBER_OF_SLAVES	2
#define MAX_SLAVES		 	2


int Slave[MAX_SLAVES] = {bintree_slave0,bintree_slave1};
// end

Message msg;

int main()
{
	volatile int x, y, i,j;
    int aux_msg[3];

    Echo(itoa(GetTick()));
	while(1);
	// calculate number of block and pad value (PCKS5) of last block
	Echo("reuschxx:");

	// for( x=0 ; x < MAX_SLAVES ; x++ ){2
    //     msg.length = sizeof(aux_msg);
	// 	aux_msg[0] = 1;
	// 	aux_msg[1] = 2;
	// 	aux_msg[2] = 3;
	// 	memcpy(&msg.msg, &aux_msg, 4*msg.length);
	// 	Send(&msg, Slave[x]);  
	// }

	
    // // Receive Encrypted block from Slave_PE
    // for(y = 0; y < NUMBER_OF_SLAVES ; y++){2
    //         Receive(&msg, Slave[(x+y) % NUMBER_OF_SLAVES]);2
    //     }
    // }
	
	exit();		
}
