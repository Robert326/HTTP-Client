#define _GNU_SOURCE
#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "commands.h"
#include "parson.h" 

//Datele de conectare la server
char Host[20] = "34.246.184.49";
int Port = 8080;

int main(int argc, char *argv[])
{   
    int sockfd;
    char *message;
    char *response;
    char *command = malloc(50 * sizeof(char));
    check_allocation(command);
    char *username = malloc(50 * sizeof(char));
    check_allocation(username);
    char *password = malloc(50 * sizeof(char));
    check_allocation(password);
    char *cookie = NULL;
    char *token = NULL;

    while (1) {
        scanf("%s", command);
        Command cmd = get_command(command);

        switch (cmd) {
            case Register: {
                //citire date de inregistrare
                printf("username=");
                scanf("%s", username);
                
                printf("password=");
                scanf("%s", password);

                //creare obiect JSON
                JSON_Value *root_value = json_value_init_object();
                JSON_Object *root_object = json_value_get_object(root_value);
                json_object_set_string(root_object, "username", username);
                json_object_set_string(root_object, "password", password);

                //transformare obiect JSON in string
                char *body_data = json_serialize_to_string(root_value);
                json_value_free(root_value);

                //creare conexiune
                sockfd = open_connection(Host, Port, AF_INET, SOCK_STREAM, 0);
                
                //creare mesaj
                message = compute_post_request(
                    Host,
                    "/api/v1/tema/auth/register",
                    "application/json",
                    body_data,
                    NULL,
                    0
                );
                
                //trimitere mesaj
                send_to_server(sockfd, message);
                
                //raspuns de la server
                response = receive_from_server(sockfd);
                printf("%s\n", response);

                
            break;
            }
            case Login: {
                //citire date de logare
                printf("username=");
                scanf("%s", username);

                printf("password=");
                scanf("%s", password);

                //creare obiect JSON
                JSON_Value *root_value = json_value_init_object();
                JSON_Object *root_object = json_value_get_object(root_value);

                json_object_set_string(root_object, "username", username);
                json_object_set_string(root_object, "password", password);


                //transformare obiect JSON in string
                char *body_data = json_serialize_to_string(root_value);
                json_value_free(root_value);

                //creare conexiune
                sockfd = open_connection(Host, Port, AF_INET, SOCK_STREAM, 0);

                //creare mesaj
                message = compute_post_request(
                    Host,
                    "/api/v1/tema/auth/login",
                    "application/json",
                    body_data,
                    NULL,
                    0
                );

                //trimitere mesaj
                send_to_server(sockfd, message);

                //raspuns de la server
                response = receive_from_server(sockfd);
                printf("%s\n", response);
                //extrag codul de status al login-ului
                int status_code = get_status_code(response);

                //daca login-ul a fost cu succes, extrag cookie-ul
                if (status_code == 200) {
                    // char *cookie_start = strstr(response, "Set-Cookie: ");
                    // cookie_start += strlen("Set-Cookie: ");
                    // char *cookie_end = strstr(cookie_start, ";");
                    // cookie = malloc((cookie_end - cookie_start + 1) * sizeof(char));
                    // check_allocation(cookie);
                    // strncpy(cookie, cookie_start, cookie_end - cookie_start);
                    // cookie[cookie_end - cookie_start] = '\0';

                    
                }
            break;
            }
            case Enter_library: {
                //creare conexiune
                sockfd = open_connection(Host, Port, AF_INET, SOCK_STREAM, 0);

                //creare mesaj
                message = compute_get_request(
                    Host,
                    "/api/v1/tema/library/access",
                    cookie,
                    token
                );

                //trimitere mesaj
                send_to_server(sockfd, message);

                //raspuns de la server
                response = receive_from_server(sockfd);
                printf("%s\n", response);
            break;
            }

            case Get_books: {
                //creare conexiune
                sockfd = open_connection(Host, Port, AF_INET, SOCK_STREAM, 0);

                //creare mesaj
                message = compute_get_request(
                    Host,
                    "/api/v1/tema/library/books",
                    cookie,
                    token
                );
            break;
            }

            case Get_book: {
                //citire id carte
                int id;
                printf("id=");
                scanf("%d", &id);

                //creeare obiect JSON
                JSON_Value *root_value = json_value_init_object();
                JSON_Object *root_object = json_value_get_object(root_value);

                //url-ul va fi de urmatorul tip : /api/v1/tema/library/books/:bookId
                char* url;
                if (asprintf(&url, "/api/v1/tema/library/books/%d", id) < 0) {
                    perror("asprintf");
                    exit(1);
                }

                //transformare obiect JSON in string
                char *body_data = json_serialize_to_string(root_value);
                json_value_free(root_value);


                //creare conexiune
                sockfd = open_connection(Host, Port, AF_INET, SOCK_STREAM, 0);

                //creare mesaj
                message = compute_get_request(
                    Host,
                    url,
                    cookie,
                    token
                );

                //trimitere mesaj
                send_to_server(sockfd, message);

                //raspuns de la server
                response = receive_from_server(sockfd);
                printf("%s\n", response);
            break;
            }

            case Add_book:

                //citire date carte
                char *title = malloc(50 * sizeof(char));
                printf("title=");
                scanf("%s", title);

                char *author = malloc(50 * sizeof(char));
                printf("author=");
                scanf("%s", author);

                char *genre = malloc(50 * sizeof(char));
                printf("genre=");
                scanf("%s", genre);

                char *publisher = malloc(50 * sizeof(char));
                printf("publisher=");
                scanf("%s", publisher);

                int page_count;
                printf("page_count=");
                scanf("%d", &page_count);

                //creare obiect JSON
                JSON_Value *root_value = json_value_init_object();
                JSON_Object *root_object = json_value_get_object(root_value);


            break;

            case Delete_book:

            break;

            case Logout:

            break;

            case Exit:
                return 0;
    
            default:
                printf("Unknown command\n");
            break;
        }
        
    }
    

    return 0;
}
