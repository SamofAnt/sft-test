#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "mapping.h"
#include "truck.h"




// fjsofisjgoisjgis
//godsjgpojkgpokgpodgop
// Initialize delivery trucks with their routes
void initializeTrucks(struct Truck* trucks) {
    // Blue truck
    trucks[0].route = getBlueRoute();
    strcpy(trucks[0].routeColour, "BLUE");
    trucks[0].capacity.currWeight = 0;
    trucks[0].capacity.currVolume = 0;
    trucks[0].capacity.numOfPackages = 0;

    // Green truck
    trucks[1].route = getGreenRoute();
    trucks[1].capacity.currWeight = 0;
    trucks[1].capacity.currVolume = 0;
    trucks[1].capacity.numOfPackages = 0;

    // Yellow truck
    trucks[2].route = getYellowRoute();
    strcpy(trucks[2].routeColour, "YELLOW");
    trucks[2].capacity.currWeight = 0;
    trucks[2].capacity.currVolume = 0;
    trucks[2].capacity.numOfPackages = 0;
}

// Convert column letter to number (A=0, B=1, etc.)
int convertColToNum(char col) {
    return col - 'A';
}

// Convert coordinate string to Point
struct Point parseDestination(const char* dest) {
    struct Point point;
    int row;
    char col;
    sscanf(dest, "%d%c", &row, &col);
    point.row = row - 1; // Convert to 0-based
    point.col = convertColToNum(col);
    return point;
}

void printDeliveryPath(const struct Route* route) {
    int i;
    for (i = 0; i < route->numPoints; i++) {
        printf("%d%c", route->points[i].row + 1, 'A' + route->points[i].col);
        if (i < route->numPoints - 1) printf(", ");
    }
    printf("\n");
}

int main(void) {
    struct Map map = populateMap();
    struct Truck trucks[3];
    double weight, volume;
    char destination[10];
    struct Point dest;
    struct Delivery bestAttempt;
    int bestTruckIndex;
    double minDiversionDistance;

  

    initializeTrucks(trucks);

    printf("=================\n");
    printf("Seneca Deliveries\n");
    printf("=================\n");

    while (1) {
        printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
        scanf("%lf %lf %s", &weight, &volume, destination);

        if (weight == 0 && volume == 0 && destination[0] == 'x') {
            break;
        }

        // Validate input
        if (!isPackageValid(weight, volume)) {
            if (weight > MAX_WEIGHT) {
                printf("Invalid weight (must be 1-1000 Kg.)\n");
            }
            else {
                printf("Invalid size\n");
            }
            continue;
        }

        dest = parseDestination(destination);
        if (!isDestValid(&map, dest)) {
            printf("Invalid destination\n");
            continue;
        }

        // Create package
        struct Package package = { weight, volume, dest };

        // Find best truck for delivery
        bestTruckIndex = -1;
        minDiversionDistance = 999999.9;

        for (int i = 0; i < 3; i++) {
            if (!isPackageAcceptable(&trucks[i], &package)) {
                continue;
            }

            struct Delivery attempt = calcDeliveryPath(&map, &trucks[i].route, &dest);

            if (attempt.isPossible &&
                (bestTruckIndex == -1 || attempt.path.numPoints < minDiversionDistance)) {
                bestTruckIndex = i;
                bestAttempt = attempt;
                minDiversionDistance = attempt.path.numPoints;
            }
        }

        if (bestTruckIndex >= 0) {
            addPackage(&trucks[bestTruckIndex], &package);

            printf("Ship on %s LINE", trucks[bestTruckIndex].routeColour);

            if (bestAttempt.path.numPoints > 0) {
                printf(", divert: ");
                printDeliveryPath(&bestAttempt.path);
            }
            else {
                printf(", no diversion\n");
            }
        }
        else {
            printf("Ships tomorrow\n");
        }
    }

    printf("Thanks for shipping with Seneca!\n");
    return 0;
}