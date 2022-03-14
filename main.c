/**
 * @file main.c
 * @author xnacly
 * @brief contains the starting point of the project
 * @date 2021-02-21
 */

#include <ctype.h>  // used for tolower
#include <stdio.h>  // used for scanf, printf, EXIT_SUCCESS
#include <stdlib.h> // used for: loadImage, freeImage

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
    printf("[%s] Image in Ram\n\n", image_in_memory
                                        ? ANSI_COLOR_GREEN "+" ANSI_RESET
                                        : ANSI_COLOR_RED "-" ANSI_RESET);

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

    // check if selection is in the allowed spectre
    selection = check_is_option_valid(selection, image_in_memory);

    switch (selection) {
    case SELECTION_LOAD: {
      if (!image_in_memory) {
        printf("[%d] %s\n", SELECTION_LOAD, MAIN_OPTIONS[SELECTION_LOAD]);
        char filename[255] = ""; // size: 255 due to the maximum file length

        // avoid double free by checking if the image was freed before
        if (img != NULL) {
          freeImage(&img);
        } else {
          // loop until the input is a valid file which can be opened
          while (img == NULL) {
            printf("Dateiname (with .pgm): ");
            scanf("%s", filename);
            img = loadImage(filename);
            if (img == NULL) {
              throw_warning("Datei konnte nicht geöffnet werden.");
            }
          }

          printf("%s%s wurde eingelesen.%s\n", ANSI_COLOR_GREEN, filename,
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

      scanf("%s", temp);
      threshold_ = toInt(temp);
      free(temp);

      Image *copy = threshold(img, threshold_);
      freeImage(&img);
      img = copy;
      edited_unsaved_image_in_memory = 1;
      printf(ANSI_COLOR_GREEN "Bild wurde mit dem Threshold Operator "
                              "bearbeitet." ANSI_RESET);
      break;
    }
    case SELECTION_SCALE: {
      printf("[%d] %s\n", SELECTION_SCALE, MAIN_OPTIONS[SELECTION_SCALE]);
      int width = 0;
      int height = 0;

      printf("Höhe: ");

      scanf("%s", temp);
      height = toInt(temp);

      printf("Breite: ");

      scanf("%s", temp);
      width = toInt(temp);

      Image *copy = scale(img, width, height);
      freeImage(&img);
      img = copy;

      edited_unsaved_image_in_memory = 1;
      printf(ANSI_COLOR_GREEN "Bild wurde skaliert." ANSI_RESET);
      break;
    }
    case SELECTION_ROTATE: {
      printf("[%d] %s\n", SELECTION_ROTATE, MAIN_OPTIONS[SELECTION_ROTATE]);
      float angle = 0;
      int brightness = MAX_BRIGHT;
      printf("Winkel um den das Bild gedreht werden soll: ");
      scanf("%f", &angle);
      printf("Helligkeit mit der freiliegende Pixel gefüllt werden "
             "sollen: ");
      scanf("%d", &brightness);
      Image *copy = rotate(img, angle, brightness);
      freeImage(&img);
      img = copy;
      printf("%sBild wurde um %f-Grad im Uhrzeigersinn gedreht.%s\n",
             ANSI_COLOR_GREEN, angle, ANSI_RESET);
      edited_unsaved_image_in_memory = 1;
      break;
    }
    case SELECTION_SAVE: {
      printf("[%d] %s\n", SELECTION_SAVE, MAIN_OPTIONS[SELECTION_SAVE]);
      char filename[255];

      printf("Dateiname (with .pgm): ");
      scanf("%s", filename);

      int feedback = saveImage(filename, img);

      if (!feedback) {
        throw_error("Datei konnte nicht gespeichert werden. (Fehler "
                    "beim Speichern)");
      } else {
        freeImage(&img);
      }

      edited_unsaved_image_in_memory = 0;
      image_in_memory = 0;

      printf("%sBild wurde als: %s gespeichert.%s\n", ANSI_COLOR_GREEN,
             filename, ANSI_RESET);
      break;
    }
    case SELECTION_EXIT: {
      if (!edited_unsaved_image_in_memory) {
        printf("[%d] %s\n", SELECTION_EXIT, MAIN_OPTIONS[SELECTION_EXIT]);
        exit(EXIT_SUCCESS);
      }

      printf("Noch ein bearbeitetes, ungespeicherters Bild im "
             "Speicher, willst "
             "du wirklich beenden?\n");
      char c = -1;

      while (c != 'y' || c != 'n') {
        printf("[Y/n]: ");
        scanf(" %c", &c);

        c = tolower((unsigned char)c);

        if (c == 'y')
          exit(EXIT_SUCCESS);
        else if (c == 'n')
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
