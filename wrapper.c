/* 
 * This file is part of the https://github.com/yu-shao-gm/setuid_wrapper
 * Copyright (c) 2018 Yu Shao
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *
 * Running shell script in setuid is disabled by default from most Linux
 * distrubutions due to security reasons. If you still have the need to 
 * "setuid", you could recompile the kenrel, or by calling the shell script
 *  from a C wrapper as mentioned here: https://access.redhat.com/solutions/124693
 * 
 * The C code here is an enhanced version with following features added:
 *
 *  - Passing arguments when calling the shell script
 *  - Calling argv[0].sh, means you can rename it to 
 *    any other name, such as "foo", then calling foo 
 *    will be redirected to foo.sh with all the arguments
 *  - setgid could be added by setgid(0)
 *
 * So, compile and install it:
 *
 *  gcc wrapper.c -o foo
 *  cp foo /bin/
 *  chmod 4711 /bin/foo
 *  chmod 700 /bin/foo.sh
 *
 * Enjoy it! Yu Shao <yu.shao.gm@gmail.com>
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

int main (int argc, char *argv[])
{
    setuid(0);

    int i;
    size_t size;

    size = 1;
    for (i = 1; i < argc; i++) {
        size += strlen(argv[i]) + 1;
    }

    char *arguments = malloc(size);

    if (!arguments) {
        fprintf(stderr, "No memory\n");
        return 2;
    }

    size = 0;

    for (i = 1; i < argc; i++) {
        size += sprintf(arguments + size, "%s ", argv[i]);
        assert(arguments[size] == '\0');
    }

    arguments[--size] = '\0';
    system(strcat(strcat(argv[0], ".sh "), arguments));

    free(arguments);
    return 0;
}
