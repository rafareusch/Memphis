#include <stdlib.h>
#include <api.h>

///////// DON'T MODIFY!! 
// begin
#define MSG_LENGHT			
#define NUMBER_OF_SLAVES			 	
int Slave[NUMBER_OF_SLAVES] = {};
// end

Message msg;

int main()
{
	volatile int x, y, i,j;
    int aux_msg[3];
	int input_text[16];
    Echo(itoa(GetTick()));


	
	// SEND TO SLAVES
	for( x=0 ; x < NUMBER_OF_SLAVES ; x++ ){
        msg.length = sizeof(aux_msg);
		aux_msg[0] = x;
		aux_msg[1] = 2+x;
		aux_msg[2] = 3+x;
		__builtin_memcpy(&msg.msg, &aux_msg, 4*msg.length);
		Send(&msg, Slave[x]);  
	}
	Echo("Master sent message to slaves, waiting response...");



	// RECEIVE FROM SLAVE 0
	Receive(&msg, Slave[0]);
	__builtin_memcpy(input_text, msg.msg, 12);
		
	Echo(" ");
	Echo("Master received SUM from slave:");
	Echo(itoh(input_text[0]));		

	
	exit();		
}
