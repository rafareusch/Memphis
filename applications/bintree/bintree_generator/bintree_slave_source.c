#include <stdlib.h>
#include <api.h>
#include "bintree.h"
#include <stdbool.h>

///////// DONT CHANGE
// begin
#define MSG_LENGHT			
#define NUMBER_OF_SLAVES	

int Slave[NUMBER_OF_SLAVES] = {};
// end

Message msg;


void sendIntToSlave(int msgArray[3],int id){
	int aux_msg[3];
	msg.length = sizeof(msgArray);
	aux_msg[0] = msgArray[0];
	aux_msg[1] = msgArray[1];
	aux_msg[2] = msgArray[2];
	__builtin_memcpy(&msg.msg, &aux_msg, 4*msg.length);
	Send(&msg,  Slave[id]);  
}

void sendIntToMaster(int msgArray[3]){
	int aux_msg[3];
	msg.length = sizeof(msgArray);
	aux_msg[0] = msgArray[0];
	aux_msg[1] = msgArray[1];
	aux_msg[2] = msgArray[2];
	__builtin_memcpy(&msg.msg, &aux_msg, 4*msg.length);
	Send(&msg,  bintree_master);  
}

int ReceiveFromSlave(int id){
	unsigned int input_text[16]; 
	Receive(&msg, Slave[id]);
	__builtin_memcpy(input_text, msg.msg, 12);
	return input_text[0];	
}

bool isPair(int val){
	if ((val % 2) == 0) {
		return true;
	}  
	else
	{ 
		return false;
	}
}


int main()
{
	int slave_id = 0;
	volatile int i;
	int msg_payload[3];
	unsigned int recv_value[16]; 
	unsigned int recv_int; 


	Echo("Starting binary tree slave...");
	Echo(" ");



	// RECEIVE FROM MASTER AND CALCULATE INTERNAL SUM
	// 		0 - SLAVE_ID
	// 		1 - DATA TO PROCESS
	// 		2 - DATA TO PROCESS
	Receive(&msg, bintree_master);
	__builtin_memcpy(recv_value, msg.msg, 12);
	slave_id = recv_value[0];

	Echo("Slave received from master:");
	for(i=0; i<4;i++){
		Echo(itoh(recv_value[i]));		
	}
	Echo(" ");
	int internalSum = recv_value[0] + recv_value[1] + recv_value[2];
	Echo("Slave ID:"); 
	Echo(itoh(slave_id));
	Echo("Soma:"); 
	Echo(itoh(internalSum));

	Echo(" ");
	Echo(" ");
	Echo(" ");
	Echo(" ");



	// APPLICATION
	// this example application will sum every received value and send thru the binary tree
	
	// 


	//// Binary tree operation
	int NUM_SLAVES = NUMBER_OF_SLAVES;
	Echo("Number of total slaves: ");
	Echo(itoh(NUM_SLAVES));
	int NUM_LAYERS = NUMBER_OF_SLAVES/2;

	int layer = 0;
	int step = 1;
	int num_slaves_layer = NUMBER_OF_SLAVES;


	while (layer <= NUM_LAYERS)
	{
		Echo("------------------------");
		Echo("layer: ");
		Echo(itoh(layer));
		Echo("slaves on layer: ");
		Echo(itoh(num_slaves_layer));
		Echo("step: ");
		Echo(itoh(step));
		
		
		if (slave_id % step != 0){
			Echo("Slave is not on layer...");
			break;
		} 
		else if ( slave_id != 0 && isPair(num_slaves_layer) && isPair(slave_id / step)){
			recv_int = ReceiveFromSlave(slave_id+step);
			
			Echo("Received from");
			Echo(itoh(slave_id+step));
			Echo("data:");
			Echo(itoh(recv_int));
			Echo(" ");
			// APPLICATION 
			// in this example the slave will sum received value with our internal sum
			// your application must handle this received value.
			internalSum += recv_int;
		}
		else if ( slave_id != 0 && isPair(num_slaves_layer) && isPair(slave_id / step) == FALSE ){
			msg_payload[0] = internalSum;
			sendIntToSlave(msg_payload,slave_id-step);
			Echo("Sent to");
			Echo(itoh(slave_id-step));
			Echo("sum:");
			Echo(itoh(internalSum));
			Echo(" ");
		}
		else if( slave_id == 0 && num_slaves_layer > 1 ){
			recv_int = ReceiveFromSlave(slave_id+step);
			Echo("Received from");
			Echo(itoh(slave_id+step));
			Echo("data:");
			Echo(itoh(recv_int));
			Echo(" ");
			// APPLICATION 
			// in this example the slave will sum received value with our internal sum
			// your application must handle this received value.
			internalSum += recv_int;
		} 
		else if(  slave_id == 0 && num_slaves_layer <= 1 ){
			Echo("Sending to master.. sum:");
			Echo(itoh(internalSum));
			// package application result to payload and send to master
			msg_payload[0] = internalSum;
			sendIntToMaster(msg_payload);
			Echo(" ");
			break;
		}

		num_slaves_layer = (NUM_SLAVES/(2^layer));
		step = NUM_SLAVES / num_slaves_layer;
		layer++;
	}


	Echo("Stopping slave"); 
	exit();		
}