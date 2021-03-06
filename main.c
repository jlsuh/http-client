#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MIN_ARGS_SIZE 5
#define SUFFIX_ESC_SEQS "\r\n"

int connect_to_host(char* host, char* port) {
    int conn;
    struct addrinfo hints;
    struct addrinfo* serverInfo;
    struct addrinfo* p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int rv = getaddrinfo(host, port, &hints, &serverInfo);
    if (0 == rv) {
        for (p = serverInfo; p != NULL; p = p->ai_next) {
            conn = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if (-1 == conn) {
                continue;
            }
            if (connect(conn, p->ai_addr, p->ai_addrlen) != -1) {
                break;
            }
            close(conn);
        }
        freeaddrinfo(serverInfo);
        if (conn != -1 && p != NULL) {
            return conn;
        }
    }
    fprintf(stderr, "%s\n", gai_strerror(rv));
    return -1;
}

void get_res(int fromSocket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);
    while (read(fromSocket, buffer, BUFFER_SIZE - 1) != 0) {
        fprintf(stdout, "%s", buffer);
        memset(buffer, '\0', BUFFER_SIZE);
    }
    printf("\n");
}

void send_req(int toSocket, char const* verb, char const* pathToResource) {
    char* req = calloc(strlen(verb) + 1 + strlen(pathToResource) + strlen(SUFFIX_ESC_SEQS) + 1, sizeof(*req));
    sprintf(req, "%s %s%s", verb, pathToResource, SUFFIX_ESC_SEQS);
    write(toSocket, req, strlen(req) + 1);
    free(req);
}

int main(int argc, char* argv[]) {
    if (argc < MIN_ARGS_SIZE) {
        puts("Format: make start ARGS=\"<hostname> <port> <verb> </path/to/resource>\"");
        return -1;
    }
    int hostSock = connect_to_host(argv[1], argv[2]);
    if (-1 == hostSock) {
        return -1;
    }

    send_req(hostSock, argv[3], argv[4]);
    get_res(hostSock);

    close(hostSock);
    return 0;
}
