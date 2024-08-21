// TODO: header nachtragen
// Totally quick & dirty!!!
// Build: gcc -W -pedantic -o lJ learningJourney.c

#include <stdio.h>

int main() {
    // Vordefinierte 2x7 Tabelle for persona with familiarities
    float persona[2][7] = {
        { 0.2, 0.5, 0.3, 0.4, 0.6, 0.3, 0.1 },  // 0 = Emily
        { 0.4, 0.5, 0.6, 0.3, 10.2, 0.4, 0.2 }  // 1 = Jochen
    };

    // Vordefinierte 7x7 Tabelle for familiarities in domains and concepts
    float domainsConcepts[7][7] = {
        { 0.9, 0.6, 0.4, 0.2, 0.3, 0.5, 0.9 },
        { 0.9, 0.7, 0.3, 0.3, 0.4, 0.5, 0.8 },
        { 0.7, 0.8, 0.5, 0.4, 0.3, 0.6, 0.7 },
        { 0.6, 0.8, 0.5, 0.4, 0.4, 0.7, 0.9 },
        { 0.9, 0.6, 0.8, 0.5, 0.7, 0.9, 0.8 },
        { 0.7, 0.8, 0.6, 0.3, 0.5, 0.9, 0.9 },
        { 0.9, 0.5, 0.9, 0.6, 0.5, 0.6, 0.8 }
    };

    // reached certificates
    int certificates[7] ={ 0, 0, 0, 0, 0, 0, 0 };

        // Ausgabe der Tabelle
    printf("\n\n7x7 vordefinierte Tabelle:\n\n");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%3.1f ", domainsConcepts[i][j]);
        }
        printf("\n");
    }

    // Bestimme in der Persona Tabelle In der Zeile für Emily, die maximale Familiarity und ihre Position
    // Variablen für Maximalwert und Spaltennummer
    float maxFamiliarity = persona[0][0];
    int maxColumn = 0;

    // Bestimme Maximalwert und Spaltennummer in der ersten Zeile
    // int searchLine = 0; // im Test steht hier Emily
    for (int j = 0; (j < 7); j++) {
        if (persona[0][j] > maxFamiliarity) {
            maxFamiliarity = persona[0][j];
            maxColumn = j;
        }
    }

        // Ausgabe der Tabelle
    printf("\n\n2x7 vordefinierte Tabelle:\n\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%3.1f ", persona[i][j]);
        }
        printf("\n");
    }

    // Ausgabe des Maximalwerts und der Spaltennummer
    printf("\nEmily's maximal familiarity : %3.1f\n", maxFamiliarity);
    printf("Column: %d\n", maxColumn + 1); // +1 für 1-basierte Nummerierung

    // Finde in der Tabelle DomainConcept in der entsprechenden Spalte die maximale Familiarity
    // Find in DomainsConcepts next familiarity beginning with starting familiarity column
    /*for (int i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
            }
    }
    int k = maxColumn;
    maxFamiliarity = 0;
    for (int i = k; (i < 7); i++) {
        if (persona[i][k] > maxFamiliarity) {
            maxFamiliarity = persona[0][j];
            maxColumn = j;
        }
    } */

    // Start with the column in domainConcepts containing showing the highest familiarity value in persona.
    // Find the max familirity in this column. Save the corresponding line number. This line number gives us
    // the next certificate to work for. The certificate increases familiarity.
    // We continue finding the next max familiarity in the domainsConcepts - excludingly the line with the
    // certificate.
    // We exclude always the lines in domainsConcepts which have a certificate (entry) and the columns with the
    // max familiarity.
    // In the end, we have a seqence of certificates and thus the learning path.
    return 0;
}

