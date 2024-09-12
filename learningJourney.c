/****************************************************************************
 * @file:   learningJourney.c
 * @author: Marion Bohr (C)
 * @date:   2024-08-21
 * @build:  gcc -W -pedantic -o lJ learningJourney.c
 * @description:
 *    Totally quick & dirty!!!
 *    Start with the column in domainsConcepts containing the highest
 *    familiarity value in persona.
 *    Find the max familiarity in this column. Save the corresponding line
 *    number. This line number gives us the next certificate to work for.
 *    Each certificate increases familiarity.
 *    We continue finding the next maximum familiarity in the domainsConcepts
 *    - excluding the line with the certificate the columns with the already
 *    known maximum familiarity.
 *    In the end, we get a sequence of certificates and thus the learning path.
 ****************************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define MAX_DOMAINS   7
#define MAX_CONCEPTS  7
#define MAX_PERSONAS  2

bool isInArray(int element, int array[], int size);

void maxFamiliarityPerColumn(const float domainsConcepts[MAX_DOMAINS][MAX_CONCEPTS],
  int certificates[MAX_DOMAINS], float* maxFamiliarity, int searchColumn,
  int searchLine, int* certificateLine);

// Check whether certificate is already suggested
bool isInArray(int element, int array[], int size) {
  for (int i = 0; i < size; i++) {
    //printf("---- %d %d\n", element, array[i]);
    if (array[i] == element) {
      return true;
    }
  }
  return false;
}

// Find maximum familiarity per column/ per concept
void maxFamiliarityPerColumn(const float domainsConcepts[MAX_DOMAINS][MAX_CONCEPTS],
  int certificates[MAX_DOMAINS], float* maxFamiliarity, int searchColumn,
  int searchLine, int* certificateLine) {

  *maxFamiliarity = 0.0f;
  *certificateLine = 0;
  int j = searchColumn;

  for (int i = 0; (i < MAX_DOMAINS); i++) {
    //printf("##### %d\n", i);
    // +1 display

    // Only for conepts which are not yet suggested within a certificate
    if (!(isInArray((i + 1), certificates, MAX_DOMAINS))){
      if (domainsConcepts[i][j] > *maxFamiliarity) {
        *maxFamiliarity = domainsConcepts[i][j];
        *certificateLine = i;
      }
    }
  }
}

//---------------------------------------------------------------------------

int main(void) {

    // Predifined 2x7 test table for persona with familiarities
    float persona[MAX_PERSONAS][MAX_CONCEPTS] = {
        { 0.2, 0.5, 0.3, 0.4, 0.6, 0.3, 0.1 },  // 0 = Emily
        { 0.4, 0.5, 0.6, 0.3, 10.2, 0.4, 0.2 }  // 1 = Jochen
    };

    // Predifined 7x7 test table for familiarities in domains and concepts
    float domainsConcepts[MAX_DOMAINS][MAX_CONCEPTS] = {
        { 0.9, 0.6, 0.4, 0.2, 0.3, 0.5, 0.9 },
        { 0.9, 0.7, 0.3, 0.3, 0.4, 0.5, 0.8 },
        { 0.7, 0.8, 0.5, 0.4, 0.3, 0.6, 0.7 },
        { 0.6, 0.8, 0.5, 0.4, 0.4, 0.7, 0.9 },
        { 0.9, 0.6, 0.8, 0.5, 0.7, 0.9, 0.8 },
        { 0.7, 0.8, 0.6, 0.3, 0.5, 0.9, 0.9 },
        { 0.9, 0.5, 0.9, 0.6, 0.5, 0.6, 0.8 }
    };

    // Planned certificates
    int certificates[MAX_DOMAINS] = { 0, 0, 0, 0, 0, 0, 0 };
    int certificateIndex = 0;
    int certificateLine = 0;

    // Output test table domainsConcepts
    printf("\n\n7x7 predefined test table domainsConcepts:\n\n");
    for (int i = 0; i < MAX_DOMAINS; i++) {
        for (int j = 0; j < MAX_CONCEPTS; j++) {
            printf("%3.1f ", domainsConcepts[i][j]);
        }
        printf("\n");
    }

    // Determine via test table persona in the line for Emily the maximum
    // familiarity and the position of the column.
    float maxFamiliarity = persona[0][0];
    int startColumn = 0;

    // Determine start values for e.g. Emily
    // int searchLine = 0; // Emily
    for (int j = 0; (j < MAX_CONCEPTS); j++) {
        if (persona[0][j] > maxFamiliarity) {
            maxFamiliarity = persona[0][j];
            startColumn = j;
        }
    }

    // Output test table persona
    printf("\n\n2x7 vordefinierte Tabelle:\n\n");
    for (int i = 0; i < MAX_PERSONAS; i++) {
        for (int j = 0; j < MAX_CONCEPTS; j++) {
            printf("%3.1f ", persona[i][j]);
        }
        printf("\n");
    }

    printf("\nEmily's maximum familiarity : %3.1f\n", maxFamiliarity);
    printf("Column: %d\n", startColumn + 1); // +1 für 1-basierte Nummerierung

    // Find in domainsConcepts next familiarity beginning with starting familiarity column
    float familiarity = 0.0f;

    int startLine = 0;

    maxFamiliarityPerColumn(domainsConcepts, certificates, &familiarity,
      startColumn, startLine, &certificateLine);
    printf("\nEmily's most familiar concept to start with: %3.1f %d\n",
      familiarity, certificateLine + 1);
    certificates[certificateIndex] = certificateLine + 1;
    certificateIndex++;
    //printf("Nr/ Certificate: %d %d\n", certificateIndex, certificates[certificateIndex]); // +1 für 1-basierte Nummerierung

    for (int j = 0; j < MAX_CONCEPTS; j++) {
      for (int i = 0; i < MAX_DOMAINS; i++) {
        if (certificateIndex < MAX_DOMAINS) {
          maxFamiliarityPerColumn(domainsConcepts, certificates, &familiarity,
            j, i, &certificateLine);
          printf("\nEmily's next domain: %3.1f %d\n", familiarity, certificateLine + 1);
          certificates[certificateIndex] = certificateLine + 1;
          certificateIndex++;
          //printf("Nr/ Certificate: %d %d\n", certificateIndex, certificates[certificateIndex]); // +1 für 1-basierte Nummerierung
        }
      }
    }

    for (int i = 0; i < MAX_DOMAINS; i++) {
      printf("Certificate %d: %d\n", i + 1, certificates[i]);
    }

    //---------------------------------------------------------------------------

    for (int i = 0; i < MAX_DOMAINS; i++) {
      certificates[i] = 0;
    }
    certificateIndex = 0;
    certificateLine = 0;

    maxFamiliarity = 0;
    startColumn = 0;

    // int searchLine = 1; // Jochen
    for (int j = 0; (j < MAX_CONCEPTS); j++) {
        if (persona[1][j] > maxFamiliarity) {
            maxFamiliarity = persona[1][j];
            startColumn = j;
        }
    }

    printf("\nJochen's maximum familiarity : %3.1f\n", maxFamiliarity);
    printf("Column: %d\n", startColumn + 1); // +1 für 1-basierte Nummerierung

    // Find in domainsConcepts next familiarity beginning with starting familiarity column
    familiarity = 0.0f;

    startLine = 0;

    maxFamiliarityPerColumn(domainsConcepts, certificates, &familiarity,
      startColumn, startLine, &certificateLine);
    printf("\nJochen's most familiar concept to start with: %3.1f %d\n",
      familiarity, certificateLine + 1);
    certificates[certificateIndex] = certificateLine + 1;
    certificateIndex++;
    //printf("Nr/ Certificate: %d %d\n", certificateIndex, certificates[certificateIndex]); // +1 für 1-basierte Nummerierung

    for (int j = 0; j < MAX_CONCEPTS; j++) {
      for (int i = 0; i < MAX_DOMAINS; i++) {
        if (certificateIndex < MAX_DOMAINS) {
          maxFamiliarityPerColumn(domainsConcepts, certificates, &familiarity,
            j, i, &certificateLine);
          printf("\nJochen's next domain: %3.1f %d\n", familiarity, certificateLine + 1);
          certificates[certificateIndex] = certificateLine + 1;
          certificateIndex++;
          //printf("Nr/ Certificate: %d %d\n", certificateIndex, certificates[certificateIndex]); // +1 für 1-basierte Nummerierung
        }
      }
    }

    for (int i = 0; i < MAX_DOMAINS; i++) {
      printf("Certificate %d: %d\n", i + 1, certificates[i]);
    }

    return 0;

    /* TODO:
      - I/O functions, reading tables from input file (csv)
      - more flexible logic
      - more elaborated logic
    */
}
