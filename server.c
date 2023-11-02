#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include "mem.h"
#include "common.h"
#include "misc.h"
#include "stmt.h"
#include "free.h"
#include "log.h"


/**********************************************************************/
/* Get a line from a socket, whether the line ends in a newline,
 * carriage return, or a CRLF combination.  Terminates the string read
 * with a null character.  If no newline indicator is found before the
 * end of the buffer, the string is terminated with a null.  If any of
 * the above three line terminators is read, the last character of the
 * string will be a linefeed and the string will be terminated with a
 * null character.
 * Parameters: the socket descriptor
 *             the buffer to save the data in
 *             the size of the buffer
 * Returns: the number of bytes stored (excluding null) */
/**********************************************************************/
static int get_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(sock, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
        if (n > 0)
        {
            if (c == '\r')
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                /* DEBUG printf("%02X\n", c); */
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';

    return(i);
}

bool db_send(int client, const char *buff) {
    size_t size = strlen(buff) + 1; 
    if (send(client, &size, sizeof(size), 0) > 0) // first send buff size
    {
        if (send(client, buff, size, 0) > 0)
            return 1;
    }
    return -1;
}

//Send out 
bool send_out(int client, Output *out) {
    if (out->result == EXECUTE_SUCCESS) 
        return db_send(client, out->json_data)
            && db_send(client, out->duration)
            && db_send(client, "Over"); // 'Over' means these session is over.
    else
        return db_send(client, get_current_error()) 
            && db_send(client, "Over");
}

//Start up the server.
int startup(u_short port) {
    int httpd = 0;
    int on = 1;
    struct sockaddr_in *address = sys_malloc(sizeof(struct sockaddr_in));
    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        fatal("Create socket fail.");
    memset(address, 0, sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) {
        fatal("Set socket option fail.");
    }
    if (bind(httpd, (struct sockaddr *)address, sizeof(*address)) < 0) {
        fatal("Bind socket fail.");
    }
    if (listen(httpd, 10) < 0) {
        fatal("Socket listen fail.");
    }
    return httpd;
}

//Accept request.
void accept_request(void *arg) {
    int client = (intptr_t) arg;
    size_t chars_num;
    char buf[1024];
    while((chars_num = recv(client, buf, 1024, 0)) > 0) {
        buf[chars_num] = '\0';
        Output *out = statement(buf);   
        size_t send_size = send_out(client, out);
        free_out_put(out);
        if (send_size < 0)
            break;
    }
    close(client);
    printf("Client disconnect.\n");
}
