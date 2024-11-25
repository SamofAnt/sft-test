#include <stdio.h>
#include <string.h>
#include "truck.h"
#include "mapping.h"

int isPackageValid(double weight, double volume) {
    bool isValid = true;
    if (weight < 1 || weight > 1000)
        isValid = false;

    if (volume != SMALL_BOX && volume != MEDIUM_BOX && volume != LARGE_BOX)
        isValid = false;

    return isValid;
}


int isDestValid(const struct Map* map, const struct Point dest) {
    return dest.row >= 0 && dest.row < map->numRows && dest.col >= 0 && dest.col < map->numCols;
}


void addPackage(struct Truck* truck, const struct Package* package) {
    if (truck->capacity.currWeight + package->weight <= MAX_WEIGHT &&
        truck->capacity.currVolume + package->volume <= MAX_VOLUME &&
        truck->capacity.numOfPackages < MAX_PACKAGES) {

        truck->packages[truck->capacity.numOfPackages] = *package;
        truck->capacity.currWeight += package->weight;
        truck->capacity.currVolume += package->volume;
        truck->capacity.numOfPackages++;
    }
}


struct Delivery calcDeliveryPath(const struct Map* map, const struct Route* route, const struct Point* point) {
    struct Delivery delivery;
    delivery.path = shortestPath(map, route->points[0], *point);
    delivery.routeDist = distance(&route->points[route->numPoints - 1], point);
    delivery.closestPoint = route->points[getClosestPoint(route, *point)];
    delivery.isPossible = delivery.path.numPoints > 0;
    return delivery;
}


int isPackageAcceptable(const struct Truck* truck, const struct Package* package) {
    return (truck->capacity.currWeight + package->weight <= MAX_WEIGHT &&
        truck->capacity.currVolume + package->volume <= MAX_VOLUME &&
        truck->capacity.numOfPackages < MAX_PACKAGES);
}
