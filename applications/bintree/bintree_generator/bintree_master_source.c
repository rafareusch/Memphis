#include <stdlib.h>
#include <api.h>

///////// DONT CHANGE
// REMOVE VALUES BEFORE COMPILING
// begin
#define MSG_LENGHT			
#define NUMBER_OF_SLAVES	
#define MAX_SLAVES		 	


int Slave[MAX_SLAVES] = {};
// end

Message msg;

int main()
{
	volatile int x, y, i,j;
    int aux_msg[3];
	int input_text[16];
    Echo(itoa(GetTick()));

	// calculate number of block and pad value (PCKS5) of last block
	

	for( x=0 ; x < MAX_SLAVES ; x++ ){
        msg.length = sizeof(aux_msg);
		aux_msg[0] = 1+x;
		aux_msg[1] = 2+x;
		aux_msg[2] = 3+x;
		__builtin_memcpy(&msg.msg, &aux_msg, 4*msg.length);
		Send(&msg, Slave[x]);  
	}
	Echo("Master sent message to slaves, waiting response...");


	for( x=0 ; x < MAX_SLAVES ; x++ ){
		Receive(&msg, Slave[x]);
		__builtin_memcpy(input_text, msg.msg, 12);
			
		Echo(" ");
		Echo("Master received SUM from slave:");
		Echo(itoh(input_text[0]));		
	}
	
	
	exit();		
}
