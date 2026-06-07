#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 8080

void parse_request(char *request, char *method, char *path){
    sscanf(request, "%s %s", method, path);
}

void send_response(int client_fd, int status_code, char *status_text, char *content_type, char *body) {
    char response[4096];
    int body_len = strlen(body);

    int response_len = snprintf(
        response,
        sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code,
        status_text,
        content_type,
        body_len,
        body
    );

    write(client_fd, response, response_len);

int main () {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1 ;

    //step 1 create the socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket successfully created");
}   

    //set socket options
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == 1) {
            perror("setsockopt failed");
            exit(EXIT_FAILURE)
        }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd(struct sockaddr *)&address, sizeof(address)) == - 1) {
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }
    printf("Bound to port %d\n", PORT);

    if (listen(server_fd, 10) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Listen on port %d...\n", PORT);

    int addrlen = sizeof(address);
    int client_fd;

    while (1) {
        client_fd = accept(server_fd,(struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_fd == -1) {
            perror("accepet failed");
            continue
        }
        printf("Connection Accepted")
        close(client_fd);
    }

    char buffer[4096] = {0};
    int bytes_read = read(client_fd, buffer, sizeof(buffer) -1);
    if (bytes_read < 0) {
        perror("read failed")
        close(client_fd);
        continue
    }

    char method[16] = {0};
    char method[256] = {0};
    parse_request(buffer, method, path);

    printf("[%s] %s\n", method, path);

    if (strcmp(method, "GET") == 0){
        if(strcmp(path, "/") == 0 ){
            send_response(client_fd, 200, "OK", "text/html",
            "<html><body><h1>Hello from my C server!</h1></body></html>");
        } else if(strcmp(path, "/about") == 0) {
            send_response(client_fd, 200, "OK", "text/html",
            "<html><body><h1>About Page</h1><p>Built with raw C sockets.</p></body></html>");
        } else {
            send_response(client_fd, 404, "Method Not Allowed", "text/html",
            "method not allowed");
        }
        close(client_fd);
    }
    if (strcmp(method, "POST") == 0{
        if(strcmp(path, "/") ==0){
            send_response(client_fd, 201, "OK", "text/html",
            "<html<body><h1>DEUS EX MACHINA!</>h1<body></html>");
        } else {
            send_response(client_fd, 404, "Method Not Allowed", "text/html",
            "method not allowed")
        }
        close(client_fd);
    })

    if (strcmp(method, "DELETE") == 0) {
        if(strcmp(path, "/") == 0){
            send_response(client_fd, 204, "DELETED", "text/html",
            "<html<body><h1>Deleted!</>h1<body></html>");
        } else {
            send_response(client_fd, 404, "method not allowed", "text/html",
            "method now allowed")
        }
        clost(client_fd);
    }
    if (strcmp(method, "PATCH") == 0) {
        send_response(client_fd, )
    })

    close(server_fd);
    return 0;



