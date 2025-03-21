// Author: Archit Jaiswal

// This is code shows how to handle a signal or software interupt in a program
// This code will not stop execution when it received CTRL + C from the STANDARD INPUT f
// from terminal. Instead, it will execute a signal/interupt handler

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Defining the interupt handler
static void interupt_handler(int input_sig_ID){
    static int count = 0; // To count how many times the signal/interupt arrived

    printf("\nJSR! Interupt Handler Executed... \n");

    if (input_sig_ID == SIGINT){
        count++;
        printf("Received CTRL + C... Continuing the program execution.\n");
        fflush(stdout); /* Flush any pending stdout */
        return;

        // Not a good idea to use non-async-signal-safe functions. 
        
        // Non-async-signal-safe functions are the ones from stdio library. 
        // Since these functions deals with buffering, they become inconsistent
        // or unpredictable when used in a signal handler. 

        // If an interupt arrives while a handler is in execution, the program
        // will start executing another handler. So the data buffered from previous
        // handler is still there and it might get over-written or dumped into the 
        // newly called handler. All of these will take the program in indeterminate 
        // state where the output will be unpredictable. 
    }
    else{
        printf("Some other signal interupt other than CTRL + C has arrived... Continuing the regular program execution.\n");
        exit(1);
    }
}


int main (int argc, char *argv[]){

    // Frist step is to register a signal handlers for SIGINT (CTRL + C) and SIGQUIT (CTRL + \)

    int error_check; // This will hold the return value of the function used to register a signal handler.

    // 1. Registering handler for SIGINT
    error_check = signal(SIGINT, interupt_handler);

    if (error_check == SIG_ERR){
        printf("Error received while registering SIGINT handler! \n");
        fflush(stdout);
        exit(SIG_ERR); // SIG_ERR = (-1) and it is defined in signum-generic.h
    }

    // 2. Registering handler for SIGQUIT
    error_check = signal(SIGQUIT, interupt_handler);

    if (error_check == SIG_ERR){
        printf("Error received while registering SIGINT handler! \n");
        fflush(stdout);
        exit(SIG_ERR);
    }

    int i;
    for (i = 0; i <= 100; i++){
        printf("i = %d\n", i);
        sleep(2); // Loop slowly over 101 values
    }

    return 0;
}
