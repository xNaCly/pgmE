/**
 * @file main.c
 * @author xnacly
 * @brief contains the starting point of the project
 * @date 2021-02-21
 */
#include <ctype.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include "core/p_image.h"
#include "core/p_pgm.h"

#include "main.h"

int isDir(const char* target){
  struct stat statbuf;
  stat(target, &statbuf);
  return S_ISDIR(statbuf.st_mode);
}

int verbose = 0;

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

  if (strcmp(text, ptr) == 0) {
    return 999;
  }
  
  return l;
}

int toInt(const char *text) {
  char *ptr;
  long l;

  l = strtol(text, &ptr, 10);

  
 
  if (strcmp(text, ptr) == 0) {
    return 999;
  }

  return (int)l;
}

void usage(){
  printf("Usage: pgme FILE MODIFICATION [CMD_SPECIFIC_OPTIONS]\n"
         "       pgme FILE [-m] [-g] [-l] [-t] [-s] [-r] [-v] [CMD_SPECIFIC_OPTIONS]\n"
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
  int amount_of_files = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      strcpy(filenames[i - 1], argv[i]);
      amount_of_files++;
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
            case 'v':
              verbose = 1;
              break;
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

  clock_t begin = clock();
  
  for(int i = 0; i < amount_of_files; i++){
    if(isDir(filenames[i])){
      if(verbose)
        printf("'%s' is a directory.\n", filenames[i]);
      continue;
    }

    img = loadImage(filenames[i]);

    if(img == NULL){
      if(verbose)
        printf("'%s' isn't a pgm image.\n", filenames[i]);
      continue;
    }

    if(verbose)
      printf("opened %s\n", img->name);

    switch (result) {
      case 'g': {
        Image *copy = gauss(img);
        freeImage(&img);
        img = copy;
        if(verbose)
          printf("applied gauss filter to '%s'\n", img->name);
        break;
      }
      case 'm': {
        Image *copy = median(img);
        freeImage(&img);
        img = copy;
        if(verbose)
          printf("applied median filter to '%s'\n", img->name);
        break;
      }
      case 'l': {
        Image *copy = laplace(img);
        freeImage(&img);
        img = copy;
        if(verbose)
          printf("applied laplace operator to '%s'\n", img->name);
        break;
      }
      case 't': {
        if (thresh < 1) {
          if(verbose)
            printf("threshold was too small, was set to: 1\n");
          thresh = 1;
        } else if (thresh > MAX_BRIGHT) {
          if(verbose)
            printf("threshold was too big, was set to: %d\n", MAX_BRIGHT);
          thresh = MAX_BRIGHT;
        }
        Image *copy = threshold(img, thresh);
        freeImage(&img);
        img = copy;
        if(verbose)
          printf("applied threshold filter to '%s'\n", img->name);
        break;
      }
      case 'r': {
        Image *copy = rotate(img, angle, brightness);
        freeImage(&img);
        img = copy;
        if(verbose)
          printf("rotated '%s'\n", img->name);
        break;
      }
      case 's': {
        Image *copy = scale(img, width, height);
        freeImage(&img);
        img = copy;
        if(verbose)
          printf("scaled '%s'\n", img->name);
        break;
      }
      default: {
        throw_warning(
            "No filter or operator specified, see --help for more info.");
        break;
      }
    }

    int feedback = saveImage(filenames[i], img);

    if (!feedback) {
      printf("Couldn't save '%s'", img->name);
      exit(EXIT_FAILURE);
    } else {
      if(verbose)
        printf("saved %s\n", img->name);
      freeImage(&img);
    }
   
  }

  if(verbose){
    clock_t end = clock();
    printf("took: %.4fs\n", (double) (end-begin) / CLOCKS_PER_SEC);
  }

}


int main(int argc, char **argv) {
  main_menu(argc, argv);
  return EXIT_SUCCESS;
}
