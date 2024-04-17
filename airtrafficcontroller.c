#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <string.h>

#define MAX_MSG_SIZE sizeof(Plane)
#define MAX_TEXT 200
#define MSG_TYPE 1

typedef struct{
    int airport_arrival;
    int total_plane_weight;
    int plane_id;
    int airport_depart;
    int plane_type;
    int occupied_seats;
} Plane;

typedef struct{
    long int msg_type;
    Plane plane_data;
} plane_info;

typedef struct{
    long int msg_type;
    char some_text[MAX_TEXT]
} plane_order;

//This process is used to direct planes to airports and from one airport to another
int main(int argc, char *argv[]){

    int num_of_airports_managed; //2-10 inclusive
    printf("\nEnter the number of airports to be handled/managed: ");
    scanf("%d", &num_of_airports_managed);

    key_t air_trarffic_key;
    air_trarffic_key = ftok("sharedmem1.txt", 2);

    //Set up a message queue
    int msgid;

    msgid = msgget(air_trarffic_key, 0666 | IPC_CREAT);

    plane_info recieved_plane_info;
    msgrcv(msgid, &recieved_plane_info, MAX_MSG_SIZE, MSG_TYPE, 0);

    Plane recieved_plane = recieved_plane_info.plane_data;

    printf("Recieve Plane ID: %d\n", recieved_plane.id);

    plane_order order;
    order.msg_type = MSG_TYPE;
    
    if(msgid == -1){
        printf("error in creating queue\n");
        return 1;
    }
    
    printf("Give the plane order to land of takeoff: ");
    fgets(order.some_text, MAX_TEXT, stdin);

    msgsnd(msgid, &order, sizeof(plane_order), 0);

    printf("Data Sent is : %s \n", order.some_text);

    return 0;
}