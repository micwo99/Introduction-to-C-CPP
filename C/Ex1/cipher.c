#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ASCII_AMIN 97
#define ASCII_ZMIN 122
#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_25 25
#define ASCII_5 5
/**
 * The function encode a letter s depending on k the number that tell us to how much
 * the letter has to advance in the alphabet
 * @param s letter that we want to encode
 * @param k number that precises how much the letter has to advance
 * @return the function returns the value of s after the function encodes it
 */
int Encode(int s, int k) {
  if (ASCII_A <= s && s <= ASCII_Z) {
    s = s + k;
    if (s > ASCII_Z) {
      s = s - ASCII_25;
    }
  }
  else if (ASCII_AMIN <= s && s <= ASCII_ZMIN) {
    s = s + k;
    if (s > ASCII_ZMIN) {
      s = s - ASCII_25;
    }
  }
  return s;
}
/**
 * The function decode a letter s depending on k the number that tell us to how much
 * the letter has to move back in the alphabet
 * @param s letter that we want to decode
 * @param k number that precises how much the letter has to advance
 * @return the function returns the value of s after the function decodes it
 */
int Decode(int s, int k){
  if (ASCII_A <= s && s <= ASCII_Z) {
    s = s -k;
    if (s < ASCII_A) {
      s = s + ASCII_25;
    }
  }
  else if (ASCII_AMIN <= s && s <= ASCII_ZMIN) {
    s = s - k;
    if (s < ASCII_AMIN) {
      s = s + ASCII_25;
    }
  }
  return s;

}
/**
 * the function read a file and encode the text in the file and write the encoding text in a new file
 * @param inputFile the file where the function read the original text
 * @param outputFile the file where the function will write the encoding text
 * @param k number that precises how much each letter has to advance
 */
int EncodingFile(char* inputFile, char* outputFile, int k)
{

    int x;
    FILE *input= fopen(inputFile, "r");
    FILE *output= fopen(outputFile,"w");
    while((x=fgetc(input)) !=EOF){
      int res= Encode(x,k);
      fprintf(output,"%c", res);
    }
    fclose(input);
    fclose(output);
    return 0;
}
/**
 * the function read a file and decode the text in the file and write the decoding text in a new file
 * @param inputFile the file where there is a encoding text
 * @param outputFile the file where the function will write the original text
 * @param k number that precises how much each letter has to move back
 */
int DecodingFile(char* inputFile, char* outputFile, int k)
{

  int x;
  FILE *input= fopen(inputFile, "r");
  FILE *output= fopen(outputFile,"w");

  while((x=fgetc(input)) !=EOF)
  {
    int res= Decode(x,k);
    fprintf(output,"%c", res);
  }

  fclose(input);
  fclose(output);
  return 0;
}
/**
 * the function return 0 if filename exists and 1 if it doesn't
 * @param filename name of a file that we want to check if it exist or not
 * @return 0:if the file exist 1;if it doesn't exist
 */
int CheckFile(char* filename)
{

  FILE *file;
  file = fopen(filename, "r");

  if (file)
  {
    fclose(file);
    return 0;
  }
  return 1;
}
/**
 * the function checks if the arguments the user enter are valid or not
 * @param argc number of arguments
 * @param argv arguments
 */
void CheckArgs(int argc,char* argv[])
{
  int k;
  k = atoi(argv[2]);
  if (argc!=ASCII_5)
  {
    fprintf(stderr,"Usage: cipher <encode|decode> <k> <source path file> <output path file>\n");
    exit(EXIT_FAILURE);
  }
  else if(k < 0)
  {
    fprintf(stderr,"The given shifts value is invalid\n");
    exit(EXIT_FAILURE);
  }
  else if (strcmp(argv[1], "encode") != 0 && strcmp(argv[1], "decode") != 0){
      fprintf(stderr, "The given command is invalid\n");
      exit(EXIT_FAILURE);
  }
  else if (CheckFile(argv[3])==1){
    fprintf(stderr,"The given file is invalid\n");
    exit(EXIT_FAILURE);
  }
}
/**
 * the function encode or decode a file depending on the user enters as arguments
 * @param argc number of arguments
 * @param argv the arguments
 */
int main(int argc,char* argv[]){
  CheckArgs(argc, argv);
  int k;
  k = atoi(argv[2]);
  if(strcmp(argv[1], "encode")==0){
    EncodingFile(argv[3], argv[4], k);
    return 0;
  }
  if(strcmp(argv[1], "decode")==0){
    DecodingFile(argv[3], argv[4], k);
    return 0;
  }
}
