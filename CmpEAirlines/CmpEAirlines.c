#include <stdio.h>
#include <stdlib.h>

int M;
int N;

struct passenger{
	int type;
	char ticket_c;
	int ticket_i;
	int type3_condition;
};
typedef struct passenger Passenger;

struct seat{
	char line;
	Passenger * pass;
};
typedef struct seat Seat;

void write_output(Seat * Q){
	FILE * fp;
    /* open the file for writing*/
    fp = fopen ("CmpEAirlinesOutput3.txt","w");
    
	int i;
	printf("A line:\n");
	for(i = 0;i<N;i++){
		if(Q[i].pass == NULL){
			printf("\t%d\n",0);
			fprintf(fp,"%d\n",0);
		}else{
			printf("\t%d %c%d\n",Q[i].pass->type,Q[i].pass->ticket_c,Q[i].pass->ticket_i);
			fprintf(fp,"%d %c%d\n",Q[i].pass->type,Q[i].pass->ticket_c,Q[i].pass->ticket_i);
		}		
	}
	printf("B line:\n");
	for(i = N;i<M+N;i++){
		if(Q[i].pass == NULL){
			printf("\t%d\n",0);
			fprintf(fp,"%d\n",0);
		}else{
			printf("\t%d %c%d\n",Q[i].pass->type,Q[i].pass->ticket_c,Q[i].pass->ticket_i);
			fprintf(fp,"%d %c%d\n",Q[i].pass->type,Q[i].pass->ticket_c,Q[i].pass->ticket_i);
		}
	}
}

void add(Seat * Q, int type, int type3_condition,int seat_i,char seat_c,char to_seat_i, char to_seat_c){
	if(to_seat_c == 'A'){
		to_seat_i = (to_seat_i-1) % N + 1;
	}else{
		to_seat_i = (to_seat_i-1) % M + 1;
		to_seat_i += N;
	}

	int temp_type,temp_ticket_i,temp_type3_condition;
	char temp_ticket_c;
	
	if(Q[to_seat_i-1].pass == NULL){
		Q[to_seat_i-1].pass 					= (Passenger*)malloc(sizeof(Passenger));
		Q[to_seat_i-1].pass->type 				= type;
		Q[to_seat_i-1].pass->ticket_c 			= seat_c;
		Q[to_seat_i-1].pass->ticket_i 			= seat_i;
		Q[to_seat_i-1].pass->type3_condition	= type3_condition;
	}else{
		temp_type 								= Q[to_seat_i-1].pass->type;
		temp_ticket_c 							= Q[to_seat_i-1].pass->ticket_c;
		temp_ticket_i							= Q[to_seat_i-1].pass->ticket_i;
		temp_type3_condition  					= Q[to_seat_i-1].pass->type3_condition+1;
		
		Q[to_seat_i-1].pass->type 				= type;
		Q[to_seat_i-1].pass->ticket_c 			= seat_c;
		Q[to_seat_i-1].pass->ticket_i 			= seat_i;
		Q[to_seat_i-1].pass->type3_condition	= type3_condition;

		switch(temp_type){
			case 1:
				if(to_seat_c == 'A'){
					to_seat_c = 'B';
				}else{
					to_seat_c = 'A';
				}
				add(Q,temp_type,temp_type3_condition,temp_ticket_i,temp_ticket_c,to_seat_i,to_seat_c);
				break;
			case 2:
				if(to_seat_i == N+M && to_seat_c == 'B'){
					to_seat_c = 'A';
					to_seat_i = 0;
				}
				
				if(to_seat_i == N && to_seat_c == 'A'){
					to_seat_c = 'B';
					to_seat_i = 0;
				}else if(to_seat_c == 'B')
					to_seat_i -= N;
						

				add(Q,temp_type,temp_type3_condition,temp_ticket_i,temp_ticket_c,to_seat_i+1,to_seat_c);
				break;
			case 3:
				to_seat_i = (to_seat_i+temp_type3_condition*2-1-1)%(M+N)+1;
				if(to_seat_i>N)
					to_seat_c = 'B';
				else
					to_seat_c = 'A';
				
				if(to_seat_c == 'B')
					to_seat_i -= N;
				
				add(Q,temp_type,temp_type3_condition,temp_ticket_i,temp_ticket_c,to_seat_i,to_seat_c);
				break;
		}
	}
		
}

void initial_pass(Seat * Q,int type,int ticket_i,int ticket_c){
	add(Q,type,0,ticket_i,ticket_c,ticket_i,ticket_c);
}

int main(){
	FILE *fp;
    char char_in[255];
	int int_in;
	
    fp = fopen("CmpEAirlinesInput3.txt", "r");
	
	fscanf(fp, "%d", &int_in);
	N = int_in;
	fscanf(fp, "%d", &int_in);
	M = int_in;
	
	//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	Seat seats[M+N];
			
	int i;						
	for(i = 0;i<N;i++){
		seats[i].line = 'A';	//
		seats[i].pass = NULL; 		//	PLANE INITIALIZER
	}							// 
	for(i = N;i<M+N;i++){		
		seats[i].line = 'B';
		seats[i].pass = NULL;
	}
	//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	
	fscanf(fp, "%d", &int_in); // element: number of queries
	int type,seat_i;
	char seat_c;
	for(i = 0;i<int_in;i++){
		fscanf(fp, "%d", &type);
		fscanf(fp, "%s", char_in);
		seat_c = char_in[0];
		seat_i = char_in[1]-'0';
		initial_pass(seats, type, seat_i, seat_c);
	}
	fclose(fp);

	write_output(seats);
}
