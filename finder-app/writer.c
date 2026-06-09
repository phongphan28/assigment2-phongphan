#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    ssize_t bytes_written;
    size_t string_length;

    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d", argc - 1);
        fprintf(stderr, "Error: Missing arguments\n");
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        syslog(LOG_ERR, "Failed to open file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not create file %s\n", writefile);
        closelog();
        return 1;
    }

    string_length = strlen(writestr);

    bytes_written = write(fd, writestr, string_length);
    if (bytes_written == -1)
    {
        syslog(LOG_ERR, "Failed to write to file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not write to file %s\n", writefile);
        close(fd);
        closelog();
        return 1;
    }

    if ((size_t)bytes_written != string_length)
    {
        syslog(LOG_ERR, "Partial write to file %s: wrote %zd of %zu bytes",
               writefile, bytes_written, string_length);
        fprintf(stderr, "Error: Partial write to file %s\n", writefile);
        close(fd);
        closelog();
        return 1;
    }

    if (close(fd) == -1)
    {
        syslog(LOG_ERR, "Failed to close file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not close file %s\n", writefile);
        closelog();
        return 1;
    }

    closelog();
    return 0;
}
