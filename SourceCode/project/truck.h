#ifndef TRUCK_H
#define TRUCK_H


#define MAX_WEIGHT 1500
#define MAX_COLOUR_SIZE 10
#define MAX_VOLUME 48
#define SMALL_BOX 0.5
#define MEDIUM_BOX 1.0
#define LARGE_BOX 2.0
#define MAX_PACKAGES 100
#define MAX_DIST 9999

#include <stdbool.h>
#include "mapping.h"


/// <summary>
/// Structure for package representation
/// </summary>
struct Package
{
	double weight;
	double volume;
	struct Point destination;
};



/// <summary>
/// Truck capacity is current weight, current volume, and the number of packages for the truck
/// </summary>
struct TruckCapacity
{
	double currWeight;
	double currVolume;
	int numOfPackages;
};

/// <summary>
/// The truck representation with truck's route, capacity, and a collection of packages assigned to the truck
/// </summary>
struct Truck
{
	struct Route route;
	struct TruckCapacity capacity;
	struct Package packages[MAX_PACKAGES];
	char routeColour[MAX_COLOUR_SIZE];

};


/// <summary>
/// The delivery representation with closestPoint to destination, path from route to destination, and distance from route to destination
/// </summary>
struct Delivery
{
	struct Route path;
	double routeDist;
	struct Point closestPoint;
	bool isPossible;
};


/**
 * Checks if a packages weight and volume are valid
 * @param weight - the weight of the package in kg
 * @param volume - the volume of the package in m3
 * @return 1 if the package is valid, 0 if it is not 
 */
int isPackageValid(double weight, double volume);


/**
 * Checks if a destination point is valid
 * @param map - the map to query
 * @param dest - the destination point
 * @return 1 if the destination is valid, 0 if it is not
 */
int isDestValid(const struct Map* map, const struct Point dest);

/**
 * Adds a package to a truck
 * @param truck - The truck to add the package to
 * @param package - The package to be added
 */
void addPackage(struct Truck* truck, const struct Package* package);

/**
 * Calculates the shortest path from truck's route to the destination
 * @param map The map to query
 * @param route - The truck's route
 * @param point - The destination point
 * @return A Delivery structure with the details about the delivery
 */
struct Delivery calcDeliveryPath(const struct Map* map, const struct Route* route, const struct Point* point);

/**
 * Check if a package can be acceptable by a truck
 * @param truck The truck to check
 * @param package - The package to check
 * @return 1 if the package can be acceptable, 0 if it cannot
 */
int isPackageAcceptable(const struct Truck* truck, const struct Package* package);


#endif