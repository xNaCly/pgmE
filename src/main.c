/**
 * @file main.c
 * @author xnacly
 * @brief contains the starting point of the project
 * @date 2021-02-21
 */

#include <stdio.h>
#include <stdlib.h>
#include "libs/pgm/_pgm.h"
#include "libs/util/_util.h"
#include "libs/image/_image.h"

void main_menu(int edited_unsaved_image_in_memory, int image_in_memory) {
  const char *MAIN_OPTIONS[
    SELECTION_EXIT + 1] = {"Datei laden", "Median-Filter", "Gauß-Filter", "Laplace-Operator", "Schwellwertverfahren",
                           "Bild skalieren", "Bild rotieren", "Datei speichern", "Exit"};
  int selection = 0;
  Image* img = NULL;

  while (selection >= 0) {
    printf("\nMain Menu:\n\n");
    printf("[%s] Image in Ram\n\n", image_in_memory ? ANSI_COLOR_GREEN"+"ANSI_RESET : ANSI_COLOR_RED"-"ANSI_RESET);
    for (int i = 0; i <= SELECTION_EXIT; i++) {
      // loop over all options and print them
      int isActive = (image_in_memory || i == SELECTION_LOAD || i == SELECTION_SAVE || i == SELECTION_EXIT);
      printf("[%d] %s%s%s\n", i, isActive ? ANSI_COLOR_GREEN : ANSI_COLOR_RED, MAIN_OPTIONS[i], ANSI_RESET);
    }
    printf("\nSelection (0-%d): ", SELECTION_EXIT);
    // TODO: use strtol
    scanf("%d", &selection);

    selection = check_is_option_valid(selection, image_in_memory);

    switch (selection) {
      case SELECTION_LOAD: {
        printf("[%d] %s\n", 0, MAIN_OPTIONS[0]);
        char filename[255] = ""; // size: 255 due to the maximum file length
        if (img != NULL) {
          freeImage(img);
        }
        while (img == NULL) {
          printf("Dateiname (with .pgm): ");
          scanf("%s", filename);
          img = loadImage(filename);
          if (img == NULL) {
            throw_warning("Datei konnte nicht geöffnet werden.");
          }
        }
        printf("%s%s wurde eingelesen.%s\n", ANSI_COLOR_GREEN, filename, ANSI_RESET);
        image_in_memory = 1;
        break;
      }
      case SELECTION_MEDIAN_FILTER:
        Image *copy = median(img);
        freeImage(img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        break;
      case SELECTION_GAUSS_FILTER:
        Image *copy = gauss(img);
        freeImage(img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        break;
      case SELECTION_LAPLACE_OPERATOR: {
        Image *copy = laplace(img);
        freeImage(img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        break;
      }
      case SELECTION_THRESHOLD: {
        int threshold_ = 0;
        printf("Schwellwert: ");
        scanf("%d", &threshold_);
        Image* copy = threshold(img, threshold_);
        freeImage(img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        break;
      }
      case SELECTION_SCALE: {
        Image *copy = scale(img);
        freeImage(img);
        img = copy;
        edited_unsaved_image_in_memory = 1;
        break;
      }
      case SELECTION_ROTATE: {
        printf("[%d] %s\n", 6, MAIN_OPTIONS[6]);
        float angle = 0;
        int brightness = MAX_BRIGHT;
        //clear();
        printf("Winkel um den das Bild gedreht werden soll: ");
        scanf("%f", &angle);
        printf("Helligkeit mit der freiliegende Pixel gefüllt werden sollen: ");
        scanf("%d", &brightness);
        Image* copy = rotate(img, angle, brightness);
        freeImage(img);
        img = copy;
        printf("%sBild wurde um %f-Grad im Uhrzeigersinn gedreht.%s\n", ANSI_COLOR_GREEN, angle, ANSI_RESET);
        edited_unsaved_image_in_memory = 1;
        break;
      }
      case SELECTION_SAVE: {
        char filename[255];
        printf("Dateiname (with .pgm): ");
        scanf("%s", filename);
        int feedback = saveImage(filename, img);
        if (!feedback) {
          throw_error("Datei konnte nicht gespeichert werden. (Fehler beim Speichern)");
        }
        freeImage(img);
        img = NULL;
        edited_unsaved_image_in_memory = 0;
        image_in_memory = 0;
        printf("%sBild wurde als: %s gespeichert.%s\n", ANSI_COLOR_GREEN, filename, ANSI_RESET);
        break;
      }
      case SELECTION_EXIT: {
        if (!edited_unsaved_image_in_memory) {
          exit(0);
        }
        printf("%sThere is still an unsaved edited image in memory, save it before exiting%s\n", ANSI_COLOR_RED,
               ANSI_RESET);
        break;
      }
      default:
        throw_warning("Invalid Option");
    }
  }

  freeImage(img);
  exit(0);
}

int main(void) {
  int edited_image_in_memory = 0;
  int image_in_memory = 0;
  main_menu(edited_image_in_memory, image_in_memory);
  return 0;
}
