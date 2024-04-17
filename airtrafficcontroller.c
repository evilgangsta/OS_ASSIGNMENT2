#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/msg.h>



struct Plane{
    int airport_arrival;
    int total_plane_weight;
    int plane_id;
    int airport_depart;
    int plane_type;
    int occupied_seats;
};

struct my_msg{
    long msg_type;
    struct Plane data;
    
};

//This process is used to direct planes to airports and from one airport to another
int main(){
    key_t key;
    int num_of_airports_managed; //2-10 inclusive
    printf("Enter the number of airports to be handled/managed:\n");
    // fflush(stdout);
    // scanf("%d",&num_of_airports_managed);
    
    // if (scanf("%d", &num_of_airports_managed) != 1) {
    //     fprintf(stderr, "Error reading input.\n");
    //     exit(EXIT_FAILURE);
    // }
    printf("Enter the number of airports to be handled/managed:\n");
    // printf("%d",num_of_airports_managed);
    //Set up a message queue
    
    int msgid;
    // struct my_msg plane_info;
    system("touch msgq.txt");
    key = ftok("msgq.txt", 2);
    if (key == -1){
        printf("error in creating unique key\n");
        exit(1);
    }
    
    msgid = msgget(key, 0644 | IPC_CREAT);
    printf("%d",msgid);
    if(msgid == -1){
        printf("error in creating queue\n");
        return 1;
    }
    printf("Message queue created with ID: %d", msgid);
    printf("Enter the number of airports to be handled/managed:\n");
    while (1){
        // for(int i=1;i<=10;i++){
            struct my_msg rec_msg;
            printf("hello");
            if(msgrcv(msgid,(void *)&rec_msg,sizeof(struct Plane),1,0)==-1){
                perror("message receive error");
                return 1;
            }

            struct my_msg airport_msg;
            airport_msg.msg_type=1+10;
            airport_msg.data=rec_msg.data;
            printf("%d",airport_msg.data.total_plane_weight);

            // if (msgsnd(msgid, (void *)&airport_msg, sizeof(struct Plane), 0) == -1) {
            //     perror("msgsnd");
            //     return 1;
            // }       
        // }
    }
    

    return 0;
}