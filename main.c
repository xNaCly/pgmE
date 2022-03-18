/**
 * @file main.c
 * @author xnacly
 * @brief contains the starting point of the project
 * @date 2021-02-21
 */

#include <ctype.h>   // used for tolower
#include <stdio.h>   // used for scanf,  , EXIT_SUCCESS
#include <stdlib.h>  // used for: loadImage, freeImage
#include <string.h>
#include <unistd.h>  // getopt

#include "core/p_image.h"
#include "core/p_pgm.h"

#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_STYLE_BOLD "\x1b[1m"
#define ANSI_RESET "\x1b[0m"

char* stripIndex(char* text, int start, int end){
  for(int i = start; i < end; i++){
    memmove(&text[0], &text[0+1], strlen(text)-0);
  }
  return text;
}

double toDouble(const char *text) {
  char *ptr;
  long l;

  l = strtod(text, &ptr);

  // checks if text and rest after conversion from strtol is equal,
  // meaning no int was in text
  if (strcmp(text, ptr) == 0) {
    return 999;
  }
  
  return l;
}

int toInt(const char *text) {
  char *ptr;
  long l;

  l = strtol(text, &ptr, 10);

  // checks if text and rest after conversion from strtol is equal,
  // meaning no int was in text
  if (strcmp(text, ptr) == 0) {
    return 999;
  }

  return (int)l;
}

void usage(){
  printf("Usage: pgme FILE MODIFICATION [CMD_SPECIFIC_OPTIONS]\n"
         "       pgme FILE [-m] [-g] [-l] [-t] [-s] [-r] [CMD_SPECIFIC_OPTIONS]\n"
         "       pgme FILE MODIFICATION [--t] [--h] [--w] [--a] [--b]\n"
      );

  exit(EXIT_SUCCESS);
}

void throw_warning(const char text[]) {
  printf("%s%s%s\n", ANSI_COLOR_YELLOW, text, ANSI_RESET);
}

void main_menu(int argc, char **argv) {
  Image *img = NULL;
  int result = 0;
  int thresh = 0;
  double angle = 0;
  int brightness = 0;
  int width = 0;
  int height = 0;

  if(argc == 1){
    usage();
  }

  char filenames[10][255];

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      strcpy(filenames[i - 1], argv[i]);
    } else if (argv[i][0] == '-') {
      if (strcmp(argv[i], "--help") == 0) {
        usage();
      } else if (strncmp(argv[i], "--t=", 4) == 0){
        char* temp = argv[i];
        temp = stripIndex(temp, 0, 4);
        thresh = toInt(temp);
      } else if (strncmp(argv[i], "--a=", 4) == 0){
        char* temp = argv[i];
        temp = stripIndex(temp, 0, 4);
        angle = toDouble(temp);
      } else if (strncmp(argv[i], "--b=", 4) == 0){
        char* temp = argv[i];
        temp = stripIndex(temp, 0, 4);
        brightness = toInt(temp);
      } else if (strncmp(argv[i], "--h=", 4) == 0){
        char* temp = argv[i];
        temp = stripIndex(temp, 0, 4);
        height = toInt(temp);
      } else if (strncmp(argv[i], "--w=", 4) == 0){
        char* temp = argv[i];
        temp = stripIndex(temp, 0, 4);
        width = toInt(temp);
      } else if(argv[i][1] != '-'){
        for (size_t ii = 1; ii < strlen(argv[i]); ii++) {
          switch (argv[i][ii]) {
            case 'g':
            case 'm':
            case 'l':
            case 't':
            case 's':
            case 'r':
              result = argv[i][ii];
              break;
            default:
              printf("%s\n", argv[i]);
              throw_warning("Unrecognized argument");
              exit(EXIT_FAILURE);
          }
        }
      }
    }
  }

  img = loadImage(filenames[0]);

  if (img == NULL) {
    char temp[559];
    sprintf(temp, "pgmE %s", filenames[0]);
    perror(temp);
    exit(EXIT_FAILURE);
  }
  switch (result) {
    case 'g': {
      Image *copy = gauss(img);
      freeImage(&img);
      img = copy;
      break;
    }
    case 'm': {
      Image *copy = median(img);
      freeImage(&img);
      img = copy;
      break;
    }
    case 'l': {
      Image *copy = laplace(img);
      freeImage(&img);
      img = copy;
      break;
    }
    case 't': {
      Image *copy = threshold(img, thresh);
      freeImage(&img);
      img = copy;
      break;
    }
    case 'r': {
      Image *copy = rotate(img, angle, brightness);
      freeImage(&img);
      img = copy;
      break;
    }
    case 's': {
      Image *copy = scale(img, width, height);
      freeImage(&img);
      img = copy;
      break;
    }
    default: {
      throw_warning(
          "No filter or operator specified, see --help for more info.");
      break;
    }
  }

  int feedback = saveImage(filenames[0], img);

  if (!feedback) {
    char temp[559];
    sprintf(temp, "pgmE%s", filenames[0]);
    perror(temp);
    exit(EXIT_FAILURE);
  } else {
    freeImage(&img);
  }
}


int main(int argc, char **argv) {
  main_menu(argc, argv);
  return EXIT_SUCCESS;
}
