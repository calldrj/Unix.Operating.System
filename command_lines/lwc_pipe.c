/* Tuan Nguyen
 * Project 6
 * COMP 322L - Class #16766 (MoWe 12:30PM-01:45PM)
 * Program simulates the UNIX wc commmand with particularly option -lwc using pipe()
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

// Struct holds numbers of lines, words, and characters
struct file { int lines; int words; int chars; };

// Return 1 if the charater is either a '\t', ' ', or '\n', 0 otherwise
int is_blank( int ch ) { return ch == 9 || ch == 10 || ch == 32; }

// Return -1 if a command option is in -(l, w, c) format,
// ASCII value of the first invalid character otherwise
int valid_option_v( char* ch ) {
    if ( ch[0] != 45 ) return -2;
    int k = 1;
    while ( ch[k] != '\0' ) {
        if ( ch[k] != 99 && ch[k] != 108 && ch[k] != 119 )
            return ch[k];
        k++;
    }
    return -1;
}

/* Validate the second argument of the command line
 * Return an array of integers v such that:
 *  if ch begins with -, v[0] = -1, and
 *      + v[1] = number of character l
 *      + v[2] = number of character w
 *      + v[3] = number of character c
 *  if ch does not begin with - and ch contain all l, c, w, v[0] = -2
 *  or v[0] = ASCII value of the first invalid character in ch
 */
int* valid_option ( char* ch ) {
    int* v = ( int* )malloc( 4 * sizeof( int ) );
    v[0] = -1; v[1] = v[2] = v[3] = 0;
    // In case the command option does not begin with an -
    if ( ch[0] != 45 ) { v[0] = -2; return v; }
    // In case the command option begins with an -
    int k = 1;
    while ( ch[k] != '\0' ) {
        switch ( ch[k] ) {
            case 108:
                v[1]++;         // count number of l
                break;
            case 119:
                v[2]++;         // count number of w
                break;
            case 99:
                v[3]++;         // count number of c
                break;
            default:
                v[0] = ch[k];   // if invalid character
                return v;
        }
        k++;
    }
    return v;
}

// Read and count from file
struct file count( FILE* fp ) {
    struct file fc = { 0, 0, 0 };
    int pre_ch = 32, ch;
    // Count words and lines of the file
    while ( ( ch = getc( fp ) ) != EOF ) {
        if ( is_blank( ch ) ) {
            if ( !is_blank( pre_ch ) ) ( fc.words )++;
            if ( ch == 10 )            ( fc.lines )++;
        }
        ( fc.chars )++;
        pre_ch = ch;
    }
    return fc;
}

// Read and count from stdin
struct file count_std() {
    struct file fc = { 0, 0, 0 };
    int pre_ch = 32, ch;
    // Count words and lines of the file
    while ( ( ch = getchar() ) != EOF ) {
        if ( is_blank( ch ) ) {
            if ( !is_blank( pre_ch ) ) ( fc.words )++;
            if ( ch == 10 )            ( fc.lines )++;
        }
        ( fc.chars )++;
        pre_ch = ch;
    }
    return fc;
}

// Print numbers of lines, words, and characters from stdin or only one file
void print_lwc( FILE* fp, int* v, int all ) {
    struct file fc = ( fp ) ? count( fp ) : count_std();
    if ( all )
        printf( "%d\t%d\t%d\t", fc.lines, fc.words, fc.chars );
    else {
        if ( v[1] > 0 ) printf( "%d\t", fc.lines );
        if ( v[2] > 0 ) printf( "%d\t", fc.words );
        if ( v[3] > 0 ) printf( "%d\t", fc.chars );
    }
}

// Print numbers of lines, words, and characters from stdin or 1+ files using pipe()
void print_lwc_multi( int start, int argc, char* argv[], int* v, int all ) {
    FILE*   fp;
    int     pd_l[2], pd_w[2], pd_c[2],  k = start, l = start,
            c_count, w_count, l_count,
            total_chars = 0, total_words = 0, total_lines = 0;
    pid_t   pid;
    
    // Create pipes to store character, line, and word counts
    pipe( pd_c ); pipe( pd_l );pipe( pd_w );
    
    for ( ; k < argc; k++ ) {
        if ( ( pid = fork() ) == -1 ) {         // call fork process for argv[k]
            perror( "fork() failed\n" );
            exit (1);
        }
        waitpid( pid, NULL, 0 );
        if ( pid == 0 ) {
            fp = fopen( argv[k], "r" );         // open file with name argv[k]
            if ( !fp )
                printf( "Fail to open file %s\n", argv[k] );
            else {
                print_lwc( fp, v, all );        // print counts for file argv[k]
                printf( "%s\n", argv[k] );
                rewind( fp );                   // return file reader pointer to the beginning of the file
                struct file fc = count( fp );
                l_count = fc.lines; w_count = fc.words; c_count = fc.chars;
                
                close( pd_l[READ] ); close( pd_w[READ] ); close( pd_c[READ] ); // close read ends of 3 pipes
                
                if ( write( pd_l[WRITE], &l_count, sizeof( int ) ) == -1 ) {   // write to line-count pipe
                    perror( "Write line count failed\n" ); exit (1);
                }
                
                if ( write( pd_w[WRITE], &w_count, sizeof( int ) ) == -1 ) {   // write to word-count pipe
                    perror( "Write word count failed\n" ); exit (1);
                }
                
                if ( write( pd_c[WRITE], &c_count, sizeof( int ) ) == -1 ) {  // write to character-count pipe
                    perror( "Write character count failed\n" ); exit (1);
                }
                fclose( fp );                                                 // close file argv[k]
            }
            return;                                                           // terminate process for argv[k]
        }
    }
    
    for ( ; l < argc; l++ ) {
        waitpid( pid, NULL, 0 );
        if ( read( pd_l[READ], &l_count, sizeof( int ) ) == -1 ) {           // read line-count pipe to l_count
            perror( "Read line count failed\n" ); exit (1);
        }
        
        if ( read( pd_w[READ], &w_count, sizeof( int ) ) == -1 ) {           // read word-count pipe to w_count
            perror( "Read word count failed\n" ); exit (1);
        }
        
        if ( read ( pd_c[READ], &c_count, sizeof( int ) ) == -1 ) {         // read character-count pipe to w_count
            perror( "Read character count failed\n" ); exit (1);
        }
        total_chars += c_count; total_words += w_count ; total_lines += l_count;
    }
    
    if ( k > start + 1 ) {
        if ( all )
            printf( "%d\t%d\t%d\t", total_lines, total_words, total_chars );
        else {
            if ( v[1] > 0 ) printf( "%d\t", total_lines );
            if ( v[2] > 0 ) printf( "%d\t", total_words );
            if ( v[3] > 0 ) printf( "%d\t", total_chars );
        }
        printf( "total\n" );
    }
}

int main( int argc, char* argv[] ) {
    FILE* fp;
    
    /**** The command line has only 1 argument, read and count from stdin, then exit ***/
    if ( argc == 1 ) {
        print_lwc( NULL, NULL, 1 );
        printf( "\n" );
        return 0;
    }
    
    /**** The command line has 2+ arguments ***/
    // Examine second argument
    int* v = valid_option( argv[1] );
    
    /**** The command line has 2 arguments ***/
    if ( argc == 2 ) {
        // Second argument has -(l,c, w), read and count stdin
        if ( v[0] == -1 ) {
            print_lwc( NULL, v, 0 );
            printf( "\n" );
        }
        // Second argument is a file name, read and count the file
        else if ( v[0] == -2 ) {
            fp = fopen( argv[1], "r" );
            if ( !fp )
                printf( "Fail to open file %s\n", argv[1] );
            else {
                print_lwc( fp, v, 1 );
                printf( "%s\n", argv[1] );
                fclose( fp );
            }
        }
        else              // second argument is neither a file name nor a valid option
            printf( "Invalid option -- '%c'\n", v[0]);
        return 1;
    }
    
    /**** The command line has 3+ arguments ***/
    // Second argument begins with -(l,c, w), read and count files from third argument
    if ( v[0] == -1 )
        print_lwc_multi( 2, argc, argv, v, 0 );
    // Second argument does not have option, read and count files from second argument
    else if ( v[0] == -2 )
        print_lwc_multi( 1, argc, argv, v, 1 );
    // Second argument is neither a file name nor a valid option
    else printf( "Invalid option -- '%c'\n", v[0] );
    
    return 0;
}
