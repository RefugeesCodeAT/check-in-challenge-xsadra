#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

typedef struct PARTICIPANT
{
    string name;
    bool checked_in;
    struct PARTICIPANT* next;
}
PARTICIPANT;

PARTICIPANT* participants = NULL;

#define CHECKED_IN true
#define CHECKED_OUT false

string get_user_input();
bool perform(string user_input);

// TODO: Functions to implement
void add_one(string participant_name);
void remove_one(string participant_name);
void check_one(string participant_name);
void display_participants();
void free_memory();

int main(void)
{
    bool working = true;

    while(working)
    {
        string user_input = get_user_input();
        working = perform(user_input);
    }

    free_memory();
}

string get_user_input()
{
    return get_string("Command: ");
}

// Performs the action from the "user_input"
bool perform(string user_input) // add sadra
{
    // Read the string of user input into two variables
    string action_name = strtok(user_input, " ");
    string participant_name = strtok(NULL, " ");

    if(strcmp(action_name, "add") == 0)
    {
        add_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "remove") == 0)
    {
        remove_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "check") == 0)
    {
        check_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "display") == 0)
    {
       display_participants();
       return true;
    }
    if(strcmp(action_name, "exit") == 0)
    {
        return false;
    }

    return true;
}

/*
    Adds a participant to the beginning of the list
*/
void add_one(string participant_name)
{
    printf("add %s\n", participant_name);

    PARTICIPANT* new_participant = malloc(sizeof(PARTICIPANT));
    new_participant->name = participant_name;
    new_participant->checked_in = CHECKED_OUT; // false == 0
    new_participant->next = participants;
    participants = new_participant;
}

/*
    Search for a participant in the list and if it exists, remove it.
*/
void remove_one(string participant_name)
{
    printf("remove %s\n", participant_name);

    PARTICIPANT *current = participants, *previous = participants;

    // Only for the first participant.
    if(strcmp(current->name, participant_name) == 0)
    {
        participants = participants->next;
        free(current);
        return;
    }
    
    while(current != NULL)
    {

        if(strcmp(current->name, participant_name) == 0)
        {
            previous->next =  current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

/*
    Check a participant from the list in or out
*/
void check_one(string participant_name)
{
    printf("check %s\n", participant_name);
    PARTICIPANT* current = participants;
    bool exist = false;
    while(current != NULL)
    {
        if(strcmp(current->name, participant_name) == 0)
        {
            current->checked_in = !(current->checked_in);
            exist = true;
            return;
        }
        current = current->next;
    }
    if(!exist)
    {
        printf("--%s Not Exist!\n", participant_name);
    }
}

/*
    Display all participants and their status.
*/
void display_participants()
{
    printf("\ndisplay:\n");
    
    PARTICIPANT* current = participants;
    while(current != NULL)
    {
        printf("Name: %s \n", current->name);
        printf("Status: %i \n", current->checked_in);
        current = current->next;
    }
}

/*
    Free all memory used by participants in the list
*/
void free_memory()
{
    printf("freeing stuff.\n");

    PARTICIPANT* current = participants;
    while(current != NULL)
    {
        PARTICIPANT* next = current->next;
        printf("  Freeing %s\n", current->name);
        free(current);
        current = next;
    }
}