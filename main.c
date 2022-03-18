/**
 * @file main.c
 * @author xnacly
 * @brief contains the starting point of the project
 * @date 2021-02-21
 */

#include <ctype.h>   // used for tolower
#include <stdio.h>   // used for scanf, printf, EXIT_SUCCESS
#include <stdlib.h>  // used for: loadImage, freeImage
#include <time.h>    // used for clock

#include "core/p_image.h"
#include "core/p_pgm.h"
#include "core/p_util.h"

void main_menu(int edited_unsaved_image_in_memory, int image_in_memory) {
  const char *MAIN_OPTIONS[SELECTION_EXIT + 1] = {
      "Datei laden",      "Median-Filter",        "Gauß-Filter",
      "Laplace-Operator", "Schwellwertverfahren", "Bild skalieren",
      "Bild rotieren",    "Datei speichern",      "Exit"};
  int selection = 0;
  Image *img = NULL;

  while (selection >= 0) {
    printf("\nMain Menu:\n\n");
    // indicator to visualise when image is in ram
    printf("[%s] Image in Ram (%s)\n\n",
           image_in_memory ? ANSI_COLOR_GREEN "+" ANSI_RESET
                           : ANSI_COLOR_RED "-" ANSI_RESET,
           img == NULL ? "-" : img->name);

    // loop over all options and print them
    for (int i = 0; i <= SELECTION_EXIT; i++) {
      int isActive =
          (image_in_memory || i == SELECTION_LOAD || i == SELECTION_EXIT);
      // print all options not available red, the available ones green
      printf("[%d] %s%s%s\n", i, isActive ? ANSI_COLOR_GREEN : ANSI_COLOR_RED,
             MAIN_OPTIONS[i], ANSI_RESET);
    }

    printf("\nSelection (0-%d): ", SELECTION_EXIT);

    // allocate temp variable for usage later
    char *temp = malloc(sizeof(char) * 10);
    scanf("%s", temp);
    // safe conversion from string to integer using strtol in toInt
    selection = toInt(temp);
    free(temp);

    // check if selection is in the allowed spectre
    selection = check_is_option_valid(selection, image_in_memory);

    switch (selection) {
      case SELECTION_LOAD: {
        if (!image_in_memory) {
          double time_spent = 0;
          printf("[%d] %s\n", SELECTION_LOAD, MAIN_OPTIONS[SELECTION_LOAD]);
          char filename[255] = "";  // size: 255 due to the maximum file length

          // avoid double free by checking if the image was freed before
          if (img != NULL) {
            freeImage(&img);
          } else {
            // loop until the input is a valid file which can be opened
            while (img == NULL) {
              printf("Dateiname (with .pgm): ");
              scanf("%s", filename);
              clock_t begin = clock();
              img = loadImage(filename);
              clock_t end = clock();
              // benchmark to stop the time it took to load file into memory
              time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
              if (img == NULL) {
                throw_warning("Datei konnte nicht geöffnet werden.");
              }
            }

            printf("%s%s wurde eingelesen. [%.4f s]%s\n", ANSI_COLOR_GREEN, filename, time_spent,
                   ANSI_RESET);
            image_in_memory = 1;
          }

          break;
        }
        // disallow reading an image into mem if there is already one
        throw_warning("Bereits eine Datei in memory!");
        break;
      }
      case SELECTION_MEDIAN_FILTER: {
        printf("[%d] %s\n", SELECTION_MEDIAN_FILTER,
               MAIN_OPTIONS[SELECTION_MEDIAN_FILTER]);
        Image *copy = median(img);
        freeImage(&img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        printf(ANSI_COLOR_GREEN
               "Bild wurde mit dem Median Operator bearbeitet." ANSI_RESET);
        break;
      }
      case SELECTION_GAUSS_FILTER: {
        printf("[%d] %s\n", SELECTION_GAUSS_FILTER,
               MAIN_OPTIONS[SELECTION_GAUSS_FILTER]);
        Image *copy = gauss(img);
        freeImage(&img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        printf(ANSI_COLOR_GREEN
               "Bild wurde mit dem Gauss Filter bearbeitet." ANSI_RESET);
        break;
      }
      case SELECTION_LAPLACE_OPERATOR: {
        printf("[%d] %s\n", 3, MAIN_OPTIONS[3]);
        Image *copy = laplace(img);
        freeImage(&img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        printf(ANSI_COLOR_GREEN
               "Bild wurde mit dem Laplace Operator bearbeitet." ANSI_RESET);
        break;
      }
      case SELECTION_THRESHOLD: {
        printf("[%d] %s\n", SELECTION_THRESHOLD,
               MAIN_OPTIONS[SELECTION_THRESHOLD]);
        int threshold_ = 0;
        printf("Schwellwert: ");

        char *text = malloc(sizeof(char) * 255);
        scanf("%s", text);
        threshold_ = toInt(text);
        free(text);

        Image *copy = threshold(img, threshold_);
        freeImage(&img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        printf(ANSI_COLOR_GREEN
               "Bild wurde mit dem Threshold Operator "
               "bearbeitet." ANSI_RESET);
        break;
      }
      case SELECTION_SCALE: {
        printf("[%d] %s\n", SELECTION_SCALE, MAIN_OPTIONS[SELECTION_SCALE]);
        int width = 0;
        int height = 0;

        printf("Höhe: ");

        char *text = malloc(sizeof(char) * 255);
        scanf("%s", text);
        height = toInt(text);

        printf("Breite: ");

        scanf("%s", text);
        width = toInt(text);
        free(text);

        Image *copy = scale(img, width, height);
        freeImage(&img);
        img = copy;

        edited_unsaved_image_in_memory = 1;
        printf(ANSI_COLOR_GREEN "Bild wurde skaliert." ANSI_RESET);
        break;
      }
      case SELECTION_ROTATE: {
        printf("[%d] %s\n", SELECTION_ROTATE, MAIN_OPTIONS[SELECTION_ROTATE]);
        double angle = 0;
        int brightness = MAX_BRIGHT;
        printf("Winkel um den das Bild gedreht werden soll: ");

        char *text = malloc(sizeof(char) * 255);
        scanf("%s", text);
        angle = toDouble(text);

        printf(
            "Helligkeit mit der freiliegende Pixel gefüllt werden "
            "sollen: ");

        scanf("%s", text);
        brightness = toInt(text);
        free(text);

        Image *copy = rotate(img, angle, brightness);

        freeImage(&img);
        img = copy;

        printf("%sBild wurde um %2f-Grad im Uhrzeigersinn gedreht.%s\n",
               ANSI_COLOR_GREEN, angle, ANSI_RESET);
        edited_unsaved_image_in_memory = 1;
        break;
      }
      case SELECTION_SAVE: {
        printf("[%d] %s\n", SELECTION_SAVE, MAIN_OPTIONS[SELECTION_SAVE]);
        char filename[255];

        printf("Dateiname (mit .pgm): ");
        scanf("%s", filename);

        clock_t begin = clock();
        int feedback = saveImage(filename, img);
        clock_t end = clock();
        double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;

        if (!feedback) {
          throw_error(
              "Datei konnte nicht gespeichert werden. (Fehler "
              "beim Speichern)");
        } else {
          freeImage(&img);
        }

        edited_unsaved_image_in_memory = 0;
        image_in_memory = 0;

        printf("%sBild wurde als: %s gespeichert. [%.4f s]%s\n", ANSI_COLOR_GREEN,
               filename, time_spent, ANSI_RESET);
        break;
      }
      case SELECTION_EXIT: {
        // allow immediate exit if no file was edited
        if (!edited_unsaved_image_in_memory) {
          printf("[%d] %s\n", SELECTION_EXIT, MAIN_OPTIONS[SELECTION_EXIT]);
          exit(EXIT_SUCCESS);
        }

        printf(ANSI_COLOR_RED
               "Noch ein bearbeitetes, ungespeicherters Bild im "
               "Speicher, willst "
               "du wirklich beenden?\n" ANSI_RESET);

        // very simple yes no prompt
        char c = -1;

        while (c != 'y' || c != 'n') {
          printf("[Y/n]: ");
          scanf(" %c", &c);

          /*
          convert char to lowercase representation therefore cutting down
          on the usage of conditional statements
          */
          c = tolower((unsigned char)c);

          /*
           Exit program on y, go back into main loop on n
           */
          if (c == 'y'){
            freeImage(&img);
            exit(EXIT_SUCCESS);
          } else if (c == 'n')
            break;
        }

        break;
      }
      default: {
        throw_warning("Invalide Option");
        break;
      }
    }
  }
  exit(EXIT_SUCCESS);
}

int main(void) {
  // enables confirmation prompt on exit while there is an edited image in
  // memory
  int edited_image_in_memory = 0;
  // enables disallowing editing images while there arent any in memory
  int image_in_memory = 0;
  main_menu(edited_image_in_memory, image_in_memory);
  return EXIT_SUCCESS;
}
