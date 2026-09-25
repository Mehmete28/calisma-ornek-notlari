#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stddef.h>

int send_string(int sockfd, const char *buffer)
{
    size_t bytes_to_send = strlen(buffer);
    const char *ptr = buffer;

    while (bytes_to_send > 0) {
        ssize_t sent_bytes;

        sent_bytes = send(sockfd, ptr, bytes_to_send, 0);

        if (sent_bytes <= 0) {
            return -1;
        }

        bytes_to_send -= (size_t)sent_bytes;
        ptr += sent_bytes;
    }

    return 1;
}

int recv_line(int sockfd, char *dest_buffer, size_t buffer_size)
{
    const char *eol = "\r\n";
    size_t eol_matched = 0;
    size_t index = 0;

    if (dest_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    while (index < buffer_size - 1) {
        unsigned char c;
        ssize_t received;

        received = recv(sockfd, &c, 1, 0);

        if (received == 0) {
            return 0;       // bağlantı kapandı
        }

        if (received < 0) {
            return -1;      // socket hatası
        }

        dest_buffer[index++] = (char)c;

        if (c == (unsigned char)eol[eol_matched]) {
            eol_matched++;

            if (eol_matched == 2) {
                dest_buffer[index - 2] = '\0';
                return (int)(index - 2);
            }
        } else {
            eol_matched = 0;
        }
    }

    dest_buffer[buffer_size - 1] = '\0';
    return -2;              // buffer yetersiz
}