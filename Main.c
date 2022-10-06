
/*
 ============================================================================
 Name        : MyCountries.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Countries.h"


int main(int argc, char* argv[]) {
	int numberOfCountries = atoi(argv[1]);
	char *configurationFile;
	configurationFile = argv[2];
	//strcpy(configurationFile, argv[2]);
	Country **Countries = (Country**)malloc(sizeof(Country*) * numberOfCountries);
	FILE *pFile;
	pFile = fopen(configurationFile, "r");
	if(pFile == NULL)
	{
		printf("Failed to open the file.\n");
		return 1;
	}
	int cCount=0;
	while(cCount != numberOfCountries)
	{
		char newCountryName[30];
		char line[100];
		int X1,Y1;
		int X2,Y2;
		fscanf(pFile, "%s", line);
		char *token1;
		token1 = strtok (line,",");
		strcpy(newCountryName,token1);
		token1 = strtok (NULL,",");
		X1 = atoi(token1);
		token1 = strtok (NULL,",");
		Y1 = atoi(token1);
		token1 = strtok (NULL,",");
		X2 = atoi(token1);
		token1 = strtok (NULL,",");
		Y2 = atoi(token1);
		Point *pPoint1 = initPoint(X1,Y1);
		Point *pPoint2 = initPoint(X2,Y2);
		GeoT *newGeoT = initGeoT(pPoint1, pPoint2);
		Country *newCountry = initCountry(newCountryName, newGeoT);
		Countries[cCount] = newCountry;
		while(fgetc(pFile) == '\n' && fgetc(pFile) == '\t')
		{
			//city insert
			fseek(pFile, (-1), SEEK_CUR);
			char newCityName[20];
			char newFavoriteFood[30];
			int numOfResidents;
			char line2[100];
			fscanf(pFile, "%*c%s", line2);
			char *token2;
			token2 = strtok (line2,",");
			strcpy(newCityName,token2);
			token2 = strtok (NULL,",");
			strcpy(newFavoriteFood,token2);
			token2 = strtok (NULL,",");
			numOfResidents = atoi(token2);
			City *newCity = initCity(newCityName, newFavoriteFood, numOfResidents);
			addCity(newCity, newCountry);
		}
		cCount++;
		fseek(pFile, (-1), SEEK_CUR);
	}
	fclose(pFile);

	int ch = 0;
	while( ch != 6 ) {
		printf("please choose one of the following numbers:\n");
		printf("1 : print countries \n");
		printf("2 : add city to country \n");
		printf("3 : remove city from country \n");
		printf("4 : find country in area \n");
		printf("5 : print country by name \n");
		printf("6 : exit\n");
		scanf("%d", &ch );
		switch( ch )
		{
		case 1:
		{
			/* print countries */
			int k;
			for (k=0; k<numberOfCountries; k++){
				printCountry(Countries[k]);
			}

			/*
				cleanup: ;
				Point *p1 = initPoint(1,2);
				Point *p2 = initPoint(3,4);
				Point *p3 = initPoint(2,10);
				GeoT *geoT = initGeoT(p1 , p2);
				City *city1 = initCity("Haifa", "Smoke", 5);
				Country *country1 = initCountry("Israel", geoT);
				addCity(city1, country1);
				City *city2 = initCity("SdeNahom", "SweetLemon", 50000);
				addCity(city2, country1);
				printCountry(country1);
				if (isInRange(p3, country1) == true)
				{
					printf("nooooo\n");
				}
				Country *country1Copy = copyCountry(country1);
				printCountry(country1Copy);

				freeContry(country1Copy);
				if (country1Copy != NULL)
				{
					printf("nooooo\n");
				}
			 */

		}
		break;

		case 2:
		{
			/* add city to country */
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			bool countryExists = false;
			int i;
			for (i=0; (i < numberOfCountries) && (countryExists == false); i++)
			{
				char temp[30];
				strcpy(temp, getCountryNameField(Countries[i]));
				if (strcmp(temp,inputCountryName) == 0)
				{
					countryExists = true;
				}
			}
			if (countryExists == false)
			{
				printf("country name not exist .\n");
				break;
			}

			Country *pCountry = getCountryFromName(Countries, numberOfCountries, inputCountryName);

			char inputCityName[20];
			printf("please enter a city name\n");
			scanf("%s", inputCityName);
			if (searchCity(pCountry, inputCityName) == true)
			{
				printf("this city already exist in this country .\n");
				break;
			}
			else
			{
				char inputFavoriteFood[30];
				printf("please enter the city favorite food\n");
				scanf("%s", inputFavoriteFood);
				int inputResidents;
				printf("please enter number of residents in city\n");
				scanf("%d", &inputResidents);
				City *newCity = initCity(inputCityName, inputFavoriteFood, inputResidents);
				addCity(newCity, pCountry);
			}
			break;
		}


		case 3:
		{
			/* remove city from country */
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			bool countryExists = false;
			int i;
			for (i=0; i < numberOfCountries; i++)
			{
				if (strcmp(getCountryNameField(Countries[i]),inputCountryName) == 0)
				{
					countryExists = true;
				}
			}
			if (countryExists == false)
			{
				printf("country name not exist .\n");
				break;
			}

			Country *pCountry = getCountryFromName(Countries, numberOfCountries, inputCountryName);
			char inputCityName[20];
			printf("please enter a city name\n");
			scanf("%s", inputCityName);
			if (searchCity(pCountry, inputCityName) == false)
			{
				printf("the city not exist in this country .\n");
				break;
			}
			else
			{
				deleteCity(pCountry, inputCityName);
			}
			break;
		}

		case 4:
		{
			/* find country in area */
			int inputX;
			int inputY;
			char coordinates[30];
			printf("please enter x and y coordinations:x,y\n");
			scanf("%s", coordinates);
			char *token3;
			token3 = strtok (coordinates,",");
			inputX = atoi(token3);
			token3 = strtok (NULL,",");
			inputY = atoi(token3);
			Point *pPoint = initPoint(inputX, inputY);
			bool isPointInRange=false;
			int i;
			for (i=0; (i < numberOfCountries) && (isPointInRange == false); i++)
			{
				if (isInRange(pPoint , Countries[i]) == true)
				{
					char temp[30];
					strcpy(temp,getCountryNameField(Countries[i]));
					printf("found in: %s\n", temp);
					isPointInRange=true;
					break;

				}
			}
			if(isPointInRange == false)
			{
				printf("there is no country in the area\n");
			}
			break;
		}


		case 5:
		{
			/* print country by name */
			char inputCountryName[30];
			printf("please enter a country name\n");
			scanf("%s", inputCountryName);
			bool countryExists = false;
			int i;
			for (i=0; (i < numberOfCountries) && (countryExists == false); i++)
			{
				if (strcmp(getCountryNameField(Countries[i]),inputCountryName) == 0)
				{
					countryExists = true;
					Country *pCountry = getCountryFromName(Countries, numberOfCountries, inputCountryName);
					printCountry(pCountry);
				}
			}
			if (countryExists == false)
			{
				printf("country name not exist .\n");
			}
			break;
		}
		case 6:
		{
			/* exit */
			int i;
			for (i=numberOfCountries-1; i > -1; i--)
			{
				freeCountry(Countries[i]);
			}
			free(Countries);
			printf("all the memory cleaned and the program is safely closed");
			break;
		}

		default:
			printf("please choose a valid number\n");
			break;

		}
	}

	return EXIT_SUCCESS;
}
