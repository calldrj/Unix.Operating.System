/* Tuan Nguyen
 * C program lists recursively all of the directories in the subtree under a given directory.
 * Assume it's the current directory if there is none on the command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/* String cat */
char *strcat ( char *s1, const char *s2 ) {
    char *p = s1;
    while( *p ) ++p;
    while ( *p++ = *s2++ ) ;
    return s1;
}

/* Print list of current directory and its sub-directories */
void list_dir( char *path_name ) {
    DIR *dp;
    struct dirent *dir;
    
    if ( ( dp = opendir( path_name ) ) == NULL ) {
        perror( "cannot open directory.\n" );
        return;
    }
    
    while ( ( dir  = readdir( dp ) ) != NULL )
    /* Only consider the directories [ without "." or ".." ] */
        if ( dir->d_type == DT_DIR && dir->d_name[0] != '.' ) {
            /* Generate the path for the sub-directory */
            char sub_path[ BUFFER_SIZE ];
            snprintf( sub_path, sizeof( sub_path ), "%s/%s", path_name, dir->d_name );
            /* Print out the current directory */
            printf( "%s\n", dir->d_name );
            /* Recursively call list directory function */
            list_dir( sub_path );
        }
    closedir ( dp );
}

int main( int argc, char **argv ) {
    
    char    *path_name = ( char* ) malloc( BUFFER_SIZE * sizeof( char ) );
    uid_t   id = getuid();
    struct  passwd ps;
    struct  passwd *pd = &ps, *dummy = NULL;
    char    pwd_buffer[ BUFFER_SIZE ];
    int     pwd_len = sizeof( pwd_buffer );
    
    if ( ( getpwuid_r( id, pd, pwd_buffer, pwd_len, &dummy ) ) < 0) {
        perror( "getpwdid_r() error.\n" );
        return 1;
    }
    
    /* Create a full path name to pass into the list directory function */
    path_name = argc > 1 ? argv[1][0] == '/' ? argv[1] :
                           strcat( strcat( pd->pw_dir, "/" ), argv[1] ) :
                           pd->pw_dir;
   
    /* Call the list directory function */
    list_dir( path_name );
    
    return 0;
}
