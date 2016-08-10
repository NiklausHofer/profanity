#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//regex_t regex;
//int status;

char * replace( char * str, char * regexp, char * replacement )
{
  // Initialize the variables
  size_t matchcount = 1;
  regmatch_t matches[1];
  int new_str_size = 1;

  // Build the regex
  regex_t regex;
  if( regcomp( &regex, regexp, REG_EXTENDED) )
  {
    fprintf( stderr, "Unable to compile your shitty regex you piece of shit");
    exit( 1 );
  }

  // calculate the size of the new string
  int replacement_size = strlen( replacement );

  char * stringpos = str;
  while( !regexec( &regex, stringpos, matchcount, matches, 0 ) )
  {
    new_str_size += matches[0].rm_so;
    stringpos = stringpos + matches[0].rm_eo;
    new_str_size += replacement_size;
  }
  new_str_size += strlen( stringpos );

  // prepare the new string
  char * new_string = (char*)malloc(new_str_size);
  char * new_string_pos = new_string;
  int i;
  for( i=0; i<new_str_size; i++)
    new_string[i] = '\0';

  // Actual replacement work
  stringpos = str;
  while( !regexec( &regex, stringpos, matchcount, matches, 0 ) )
  {
    //fprintf( stdout, "match at:\t%d,\tend at:\t%d\n", matches[0].rm_so, matches[0].rm_eo );

    // Copy data into the new string
    strncpy( new_string_pos, stringpos, matches[0].rm_so );
    new_string_pos = new_string_pos + matches[0].rm_so;
    // Copy in the replacement
    strcpy( new_string_pos, replacement );
    new_string_pos = new_string_pos + replacement_size;

    // reset the string
    stringpos = stringpos + matches[0].rm_eo;
  }
  strcpy( new_string_pos, stringpos );
  //fprintf( stdout, "===================================\n%s\n", new_string );

  return new_string;
}

char * htmlstrip( char * text )
{
  // <br> tag, all other tags and the five special chars of XML
  char regexes[] = "<br\\s?/?>\0<[^>]+>\0&amp;\0&gt;\0&lt;\0&quot;\0&apos;";
  char replacement[] = "\n\0\0&\0>\0<\0\"\0'";

  char * regex_pt = regexes;
  char * replacement_pt = replacement;

  // Do this so we can free the string in each loop
  char * new_str = malloc( strlen(text) * sizeof(char) );
  strcpy( new_str, text );

  int i;
  for( i = 0; i<7; i++ )
  {
    char * tmp_str = replace( new_str, regex_pt, replacement_pt );
    free( new_str );
    new_str = tmp_str;
    regex_pt += strlen(regex_pt) + 1;
    replacement_pt += strlen(replacement_pt) + 1;
  }

  return new_str;
}

char * htmlencode( const char *const text )
{
  // The 5 special chars of XML and newlines
  char regexes[] = "&\0>\0<\0\"\0'\0\n";
  char replacement[] = "&amp;\0&gt;\0&lt;\0&quot;\0&apos;\0<br />";

  char * regex_pt = regexes;
  char * replacement_pt = replacement;

  // Do this so we can free the string in each loop
  char * new_str = malloc( strlen(text) * sizeof(char) );
  strcpy( new_str, text );

  int i;
  for( i = 0; i<6; i++ )
  {
    char * tmp_str = replace( new_str, regex_pt, replacement_pt );
    free( new_str );
    new_str = tmp_str;
    regex_pt += strlen(regex_pt) + 1;
    replacement_pt += strlen(replacement_pt) + 1;
  }

  return new_str;
}
