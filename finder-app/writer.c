#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>
#include <limits.h>

int make_directory(const char *filepath) {
	//doublicate the new string as path of the file, which can be modifled (avoid filepath as read-only)
	char *path = strdup(filepath);
	if(path == NULL) {
		perror("strdup");
        return -1;
	}
	char *dir = dirname(path);
	char tmp[PATH_MAX];
    snprintf(tmp, sizeof(tmp), "%s", dir);

    char *p = tmp;

    for (; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (strlen(tmp) > 0 && access(tmp, F_OK) != 0) {
                if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
                    perror("mkdir");
                    free(path);
                    return -1;
                }
            }
            *p = '/';
        }
    }

    if (access(tmp, F_OK) != 0) {
        if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
            perror("mkdir");
            free(path);
            return -1;
        }
    }
	free(path);
	return 0;
}

int main(int argc, char* argv[])
{
	// CHECK input arguments
	openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
	if (argc != 3) {
    	syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d", argc - 1);
    	fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
    	closelog();
    	return 1;
	}
	const char *writefile = argv[1];
	const char *writestr = argv[2];

	if(make_directory(writefile) != 0){
		syslog(LOG_ERR, "Failed to create directory path for: %s", writefile);
		fprintf(stderr, "Failed to create directory path for: %s", writefile);
		closelog();
		return 1;
	}

	FILE *file = fopen(writefile, "w");
    if (!file) {
        syslog(LOG_ERR, "Failed to open file: %s", writefile);
        fprintf(stderr, "Error: Failed to open file: %s\n", writefile);
        perror("fopen");
        closelog();
        return 1;
    }

    if (fputs(writestr, file) == EOF) {
        syslog(LOG_ERR, "Failed to write to file: %s", writefile);
        fprintf(stderr, "Error: Failed to write to file: %s\n", writefile);
        fclose(file);
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing \"%s\" to %s", writestr, writefile);

    fclose(file);
	
	//return success
	closelog();
	return 0;
}
