#include <stdlib.h>
#include <api.h>


///////// DONT CHANGE
// begin
#define MSG_LENGHT			2
#define NUMBER_OF_SLAVES	
#define MAX_SLAVES		 	2
int Slave[MAX_SLAVES] = {bintree_slave0,bintree_slave1};
// end



Message msg;


void sendInt(int msgArray[3]){
	int aux_msg[3];
	msg.length = sizeof(msgArray);
	aux_msg[0] = msgArray[0];
	aux_msg[1] = msgArray[1];
	aux_msg[2] = msgArray[2];
	__builtin_memcpy(&msg.msg, &aux_msg, 4*msg.length);
	Send(&msg, bintree_master);  
}



int main()
{
	volatile int x, y, i,j;
    int aux_msg[3];
	int msg_payload[3];
	unsigned int input_text[16]; 

    Echo(itoa(GetTick()));

	// calculate number of block and pad value (PCKS5) of last block
	Echo("Starting binary tree slave...");
			Echo(" ");


	Receive(&msg, bintree_master);
	__builtin_memcpy(input_text, msg.msg, 12);
		

	Echo("Slave received from master:");
	int sum = input_text[0] + input_text[1] + input_text[2];
	for(i=0; i<3;i++){
		Echo(itoh(input_text[i]));		
	}
	Echo("Soma:"); 
	Echo(itoa(sum));

	msg_payload[0] = sum;
	sendInt(msg_payload);
	

	exit();		
}