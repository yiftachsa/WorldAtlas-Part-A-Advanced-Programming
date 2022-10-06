/*
 * Countries.c
 *
 *  Created on: Nov 13, 2018
 *      Author: merav
 */
#include "Countries.h"


struct Point_t
{
	int X;
	int Y;
};

struct Geo_Territory_t
{
	Point *firstPoint;
	Point *secondPoint;
};

struct City_t
{
	char cityName[20];
	char foodName[30];
	int population;
};

struct Country_t
{
	char countryName[30];
	int numberOfCities;
	GeoT *territory;
	City **citiesList;
};

Point* initPoint(int x , int y)
{
	Point *pPoint=(Point*)malloc(sizeof(Point));
	if (pPoint != NULL)
	{
		pPoint->X = x;
		pPoint->Y = y;
		return pPoint;
	}
	return NULL;
}

Point* copyPoint(Point *pPoint)
{
	Point *pPointCopy=(Point*)malloc(sizeof(Point));
	if (pPointCopy != NULL)
	{
		pPointCopy->X = pPoint->X;
		pPointCopy->Y = pPoint->Y;
		return pPointCopy;
	}
	return NULL;
}

void freePoint(Point *pPoint)
{
	free(pPoint);
}

GeoT* initGeoT(Point *x, Point *y)
{
	GeoT *pGeoT=(GeoT*)malloc(sizeof(GeoT));;
	if (pGeoT == NULL)
	{
		freePoint(x);
		freePoint(y);
		return NULL;
	}
	//else not NULL
	pGeoT->firstPoint = x;
	pGeoT->secondPoint = y;
	return pGeoT;
}

GeoT* copyGeoT(GeoT *pGeoT)
{
	if(pGeoT==NULL)
	{
		return NULL;
	}
	GeoT *pGeoTCopy=(GeoT*)malloc(sizeof(GeoT));;
	if (pGeoTCopy == NULL)
	{
		return NULL;
	}
	//else not NULL
	Point *pPointA=copyPoint(pGeoT->firstPoint);
	Point *pPointB=copyPoint(pGeoT->secondPoint);
	pGeoTCopy->firstPoint = pPointA;
	pGeoTCopy->secondPoint = pPointB;
	return pGeoTCopy;
}

void printGeoT(GeoT *pGeoT)
{
	printf ("<%d,%d> , <%d,%d>\n", pGeoT->firstPoint->X, pGeoT->firstPoint->Y, pGeoT->secondPoint->X, pGeoT->secondPoint->Y);
}


void freeGeoT(GeoT *pGeoT)
{

	freePoint(pGeoT->firstPoint);
	freePoint(pGeoT->secondPoint);
	free(pGeoT);
}

City* initCity(char cName[],char fName[], int numberOfPepole)
{
	City* pCity=(City*)malloc(sizeof(City));
	if (pCity == NULL)
	{
		return NULL;
	}
	strcpy(pCity->cityName, cName);
	strcpy(pCity->foodName, fName);
	pCity->population=numberOfPepole;
	return pCity;

}

City* copyCity(City *pCity)
{
	if (pCity == NULL)
	{
		return NULL;
	}
	City* pCityCopy=(City*)malloc(sizeof(City));
	if (pCityCopy == NULL)
	{
		return NULL;
	}
	strcpy(pCityCopy->cityName, pCity->cityName);
	strcpy(pCityCopy->foodName, pCity->foodName);
	pCityCopy->population=pCity->population;
	return pCityCopy;

}

void printCity(City *pCity)
{
	printf ("\t%s includes %d residents and their favorite food is %s.\n", pCity->cityName, pCity->population, pCity->foodName);
}

void freeCity(City *pCity)
{
	free(pCity);
}

Country* initCountry(char cName[], GeoT *terr)
{
	Country* pCountry=(Country*)malloc(sizeof(Country));
	if (pCountry == NULL)
	{
		freeGeoT(terr);
		return NULL;
	}
	strcpy(pCountry->countryName, cName);
	pCountry->numberOfCities = 0;
	pCountry->territory = terr;
	pCountry->citiesList = NULL;
	return pCountry;
}

Country* copyCountry(Country *pCountry)
{
	if (pCountry == NULL)
	{
		return NULL;
	}
	Country* pCountryCopy=(Country*)malloc(sizeof(Country));
	if (pCountryCopy == NULL)
	{
		return NULL;
	}
	strcpy(pCountryCopy->countryName, pCountry->countryName);
	pCountryCopy->numberOfCities = 0;
	pCountryCopy->territory = copyGeoT(pCountry->territory);
	int i;
	for(i=0;i<pCountry->numberOfCities;i++)
	{
		City *newCity = copyCity(*(pCountry->citiesList+i));
		addCity(newCity , pCountryCopy);
	}
	return pCountryCopy;
}

status printCountry(Country *pCountry)
{
	if (pCountry == NULL)
	{
		return failure;
	}
	printf ("Country %s coordinates: ", pCountry->countryName);
	printGeoT(pCountry->territory);
	int i;
	for(i=0; i<pCountry->numberOfCities; i++)
	{
		printCity(*(pCountry->citiesList+i));
	}

	return success;
}


void freeCountry(Country *pCountry)
{
	freeGeoT(pCountry->territory);
	int i;
	for(i=pCountry->numberOfCities-1 ;i>-1 ;i--)
	{
		freeCity(*(pCountry->citiesList+i));
	}
	free(pCountry->citiesList);
	free(pCountry);
}


Country* addCountry(char cName[], int x1, int x2, int y1, int y2)
{
	Point *pointA = initPoint( x1, y1 );
	Point *pointB = initPoint( x2, y2 );
	GeoT *territory = initGeoT( pointA, pointB );
	Country *country = initCountry( cName , territory );
	return country;
}

status addCity(City *cityToAdd, Country *countryToAddTo)
{
	if (cityToAdd == NULL || countryToAddTo == NULL)
	{
		return failure;
	}
	//first city addition
	if ( countryToAddTo->numberOfCities == 0)
	{
		City **newCitiesList = (City**)malloc(sizeof(City*));
		countryToAddTo->citiesList = newCitiesList;
		*(countryToAddTo->citiesList)=cityToAdd;
		countryToAddTo->numberOfCities = 1;
		return success;
	}
	else
	{
		countryToAddTo->citiesList = (City**)realloc(countryToAddTo->citiesList, sizeof(City*)*((countryToAddTo->numberOfCities)+1));
		*(countryToAddTo->citiesList + (countryToAddTo->numberOfCities)) = cityToAdd;
		countryToAddTo->numberOfCities++;
	}
	return success;
}

status deleteCity(Country *pCountry, char *cName)
{
	if (pCountry == NULL || cName == NULL)
	{
		return failure;
	}
	int i;
	for (i=0; i < pCountry->numberOfCities; i++)
	{
		// Deleting the City and reassigning the city array pointers, in order to delete the free spaces.
		if(strcmp(cName,(*(pCountry->citiesList + i))->cityName)==0)
		{
			freeCity(*(pCountry->citiesList + i));
			int j;
			for (j = i; j<(pCountry->numberOfCities - 1);j++)
			{
				*(pCountry->citiesList + j) = *(pCountry->citiesList + (j+1));
			}
			pCountry->numberOfCities--;
			if(pCountry->numberOfCities == 0)
			{
				free((pCountry->citiesList[0]));
				free(*(pCountry->citiesList));
				free(pCountry->citiesList);
				return success;
			}
			else
			{
				pCountry->citiesList = (City**)realloc(pCountry->citiesList, sizeof(City*)*(pCountry->numberOfCities));
				return success;
			}
		}
	}
	return failure;
}


bool isInRange(Point *pPoint, Country *pCountry)
{
	if (pPoint == NULL || pCountry == NULL)
	{
		return false;
	}
	if(!((((pCountry->territory->firstPoint->X) <= pPoint->X) && (pPoint->X <= (pCountry->territory->secondPoint->X))) || (((pCountry->territory->secondPoint->X) <= pPoint->X) && (pPoint->X <= (pCountry->territory->firstPoint->X)))))
	{
		return false;
	}
	if(!((((pCountry->territory->firstPoint->Y) <= pPoint->Y) && (pPoint->Y <= (pCountry->territory->secondPoint->Y))) || (((pCountry->territory->secondPoint->Y) <= pPoint->Y) && (pPoint->Y <= (pCountry->territory->firstPoint->Y)))))
	{
		return false;
	}
	return true;
}

Country* getCountryFromName(Country** Countries, int numberOfCountries, char* countryName ){
	int i;
	for (i=0; i < numberOfCountries; i++)
	{
		if (strcmp(Countries[i]->countryName, countryName) == 0)
		{
			return Countries[i];
		}
	}
	return NULL;
}

bool searchCity( Country *pCountry, char *inputCityName)
{
	int i;
	for (i=0; i < pCountry->numberOfCities; i++)
	{
		if(strcmp(inputCityName,(*(pCountry->citiesList + i))->cityName)==0)
		{
			return true;
		}
	}
	return false;
}
char* getCountryNameField (Country *pCountry)
{
	return pCountry->countryName;
}
