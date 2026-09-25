#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static int send_all(int sockfd, const char *data, size_t length)
{
    size_t sent_total = 0;

    while (sent_total < length) {
        ssize_t sent = send(sockfd, data + sent_total,
                            length - sent_total, 0);

        if (sent < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }

        if (sent == 0)
            return -1;

        sent_total += (size_t)sent;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *results, *addr;
    int sockfd = -1;
    int status;
    char request[1024];
    unsigned char buffer[4096];
    ssize_t received;

    if (argc != 2) {
        fprintf(stderr, "Kullanim: %s <alan-adi>\n", argv[0]);
        return 1;
    }

    /* Kullanım: example.com; https:// veya /path ekleme. */
    if (strchr(argv[1], '\r') || strchr(argv[1], '\n')) {
        fprintf(stderr, "Alan adi satir sonu karakteri iceremez.\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;       /* IPv4 veya IPv6 */
    hints.ai_socktype = SOCK_STREAM;   /* TCP */

    status = getaddrinfo(argv[1], "80", &hints, &results);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    for (addr = results; addr != NULL; addr = addr->ai_next) {
        sockfd = socket(addr->ai_family, addr->ai_socktype,
                        addr->ai_protocol);
        if (sockfd == -1)
            continue;

        if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) == 0)
            break;

        close(sockfd);
        sockfd = -1;
    }

    freeaddrinfo(results);

    if (sockfd == -1) {
        perror("Baglanti kurulamadi");
        return 1;
    }

    int request_length = snprintf(
        request, sizeof(request),
        "HEAD / HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n"
        "\r\n",
        argv[1]
    );

    if (request_length < 0 ||
        (size_t)request_length >= sizeof(request)) {
        fprintf(stderr, "HTTP istegi icin alan adi cok uzun.\n");
        close(sockfd);
        return 1;
    }

    if (send_all(sockfd, request, (size_t)request_length) == -1) {
        perror("send");
        close(sockfd);
        return 1;
    }

    while ((received = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        if (fwrite(buffer, 1, (size_t)received, stdout)
            != (size_t)received) {
            perror("fwrite");
            close(sockfd);
            return 1;
        }
    }

    if (received < 0) {
        perror("recv");
        close(sockfd);
        return 1;
    }

    close(sockfd);
    return 0;
}