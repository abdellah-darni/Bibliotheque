#include "client.h"
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"
#include "string.h"

// cette variable contient le dernier identifiant client généré
int last_client_id = 0;

Client *string_to_client(char *str)
{
    // splitting the string
    int length;
    char **split_string = split(str, delimiter, &length);

    // checking if all the fields are present
    if (length != 7)
    {
        printf("Erreur de lecture du fichier client");
        return NULL;
    }

    // TODO add checks for email and phone number

    // parsing the string to client
    Client *client       = (Client *) malloc(sizeof(Client));
    client->id           = atoi(split_string[0]);
    client->nom          = split_string[1];
    client->prenom       = split_string[2];
    client->CIN          = split_string[3];
    client->email        = split_string[4];
    client->phone_number = split_string[5];
    client->ville        = split_string[6];

    return client;
}


char *client_to_string(Client *client)
{
    // this is the buffer used to store the string
    char *buffer = (char *) malloc(2048 * sizeof(char));
    char id[10];
	itoa(12, id, 10);
    strcpy(buffer, id);
    strcat(buffer, "#");
    strcat(buffer, client->nom);
    strcat(buffer, "#");
    strcat(buffer, client->prenom);
    strcat(buffer, "#");
    strcat(buffer, client->CIN);
    strcat(buffer, "#");
    strcat(buffer, client->email);
    strcat(buffer, "#");
    strcat(buffer, client->phone_number);
    strcat(buffer, "#");
    strcat(buffer, client->ville);
    return buffer;
}