/* Tuan Nguyen
 * Project 4
 * COMP 322L - Class #16766 (MoWe 12:30PM-01:45PM)
 * C program displays the user's permissions for each one file/directory in the command line.
 * The path name is relative to the user's home directory if it is not full path.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>

#define BIT_LEN 11
#define BUFFER_SIZE 200

// String cat
char *strcat ( char *s1, const char *s2 ) {
    char *p = s1;
    while( *p ) ++p;
    while ( *p++ = *s2++ ) ;
    return s1;
}

// Convert file mode st_mode to string
char *mode_string ( int mode ) {
    char *s = ( char* )malloc( BIT_LEN * sizeof( char ) );
    
    s[0] =  S_ISBLK( mode )     ?   'b' :           // block device
            S_ISCHR( mode )     ?   'c' :           // char device
            S_ISDIR( mode )     ?   'd' :           // directory
            S_ISFIFO( mode )    ?   'p' :           // named pipe
            S_ISLNK( mode )     ?   'l' :           // symbolic link
            S_ISSOCK( mode )    ?   's' :           // socket
                                    '-' ;           // regular file
    
    s[1] =  mode & 0400      ?   'r' : '-' ;        // 3 bits for user
    s[2] =  mode & 0200      ?   'w' : '-' ;
    s[3] =  mode & 0100      ?   'x' : '-' ;
    
    s[4] =  mode & 0040      ?   'r' : '-' ;        // 3 bits for group
    s[5] =  mode & 0020      ?   'w' : '-' ;
    s[6] =  mode & 0010      ?   'x' : '-' ;
    
    s[7] =  mode & 0004      ?   'r' : '-' ;        // 3 bits for others
    s[8] =  mode & 0002      ?   'w' : '-' ;
    s[9] =  mode & 0001      ?   'x' : '-' ;
    
    return s;
}
// Extract then return user's permission from file_permission
char *user_permission ( struct stat file_info, struct passwd *pd, char *file_permission ) {
    char *s = ( char* ) malloc( BIT_LEN * sizeof( char ) );
    int k = 0;
    for (; k < BIT_LEN - 1; k++) s[k] = '-';
    s[0] = file_permission[0];
         /* User owns the file */
    if ( pd->pw_uid == file_info.st_uid ) {
        s[1] = file_permission[1];
        s[2] = file_permission[2];
        s[3] = file_permission[3];
    }    /* User does not own the file but belongs to the group */
    else if ( pd->pw_gid == file_info.st_gid ) {
        s[4] = file_permission[4];
        s[5] = file_permission[5];
        s[6] = file_permission[6];
    }    /* User belongs to the other */
    else {
        s[7] = file_permission[7];
        s[8] = file_permission[8];
        s[9] = file_permission[9];
    }
    return s;
}

int main( int argc, char **argv ) {
    if ( argc < 2) {
        perror( "File name error.\n" );
        return 1;
    }
    
    /* User ID */
    uid_t   my_id = getuid();
    struct  passwd  ps;
    struct  passwd  *pd = &ps, *dummy = NULL;
    char    pwd_buffer[BUFFER_SIZE];
    int     pwd_len = sizeof(pwd_buffer), k = 1, n_error = 0;
    
    for (; k < argc; k++) {
        /* Inquire passwd for user's ID, group ID, and home directory */
        if ( ( getpwuid_r( my_id, pd, pwd_buffer, pwd_len, &dummy ) ) < 0 ) {
            perror( "getpwdid_r() error.\n" );
            return 1;
        }
        /* Constructe file path for file kth */
        char *file_path = argv[k][0] == '/' ? argv[k] :
                                              strcat( strcat( pd->pw_dir, "/" ), argv[k] );
        
        /* Inquire stat() for file's mode, user ID, group ID */
        struct  stat file_info;
        if ( stat( file_path, &file_info ) < 0 ) {
            n_error++;
            perror( "stat() error.\n" );
            continue;
        }
        
        /* File mode */
        mode_t  mode = file_info.st_mode;
        
        /* File permission info */
        char *file_permission = ( char* )malloc( BIT_LEN * sizeof( char ) );
        file_permission = mode_string( mode );
        
        /* Constructe user's permission on file then print out */
        char *user_info = ( char* )malloc( BIT_LEN * sizeof( char ) );
        user_info = user_permission( file_info, pd, file_permission );
        printf( "%s\t%s\n", user_info, file_path );
    }
    
    return n_error ? 1 : 0;
}
