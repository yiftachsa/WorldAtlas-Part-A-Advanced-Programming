/*
 * Countries.h
 *
 *  Created on: Nov 13, 2018
 *      Author: merav
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef COUNTRIES_H_
#define COUNTRIES_H_

typedef enum e_bool {true, false} bool;
typedef enum e_status {success, failure} status;
typedef struct Point_t Point;
typedef struct Geo_Territory_t GeoT;
typedef struct City_t City;
typedef struct Country_t Country;

//Point
Point* initPoint( int , int );
Point* copyPoint(Point *);
void freePoint(Point *);
//GeoT
GeoT* initGeoT(Point *, Point *);
GeoT* copyGeoT(GeoT *);
void freeGeoT(GeoT *);
//City
City* initCity(char *,char *, int );
City* copyCity(City *);
void freeCity(City *);
//Country
Country* initCountry(char *, GeoT *);
Country* copyCountry(Country *);
status printCountry(Country *);
void freeCountry(Country *);
//Other functions
Country* addCountry(char *, int , int , int , int );
status addCity(City *, Country *);
status deleteCity(Country *, char *);
bool isInRange(Point *, Country *);
Country* getCountryFromName(Country** , int , char* );
bool searchCity( Country* , char* );
char* getCountryNameField (Country *);

#endif /* COUNTRIES_H_ */
