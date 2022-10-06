# World Atlas - Part A - Advanced-Programming
This repository includes the second assignment created as part of the Advanced Programming course at the Ben-Gurion University of the Negev.

<p align="center">
<img src="https://shushan.co.il/wp-content/uploads/2021/08/bash.jpg"  width=30%>
<img src="https://wallpaperaccess.com/full/1537294.png"  width=25%>
<img src="https://i.pinimg.com/originals/fe/60/4c/fe604c386cbe5de093a44ac6584be8c4.jpg"  width=25%>
</p>

The Advanced Programming course goes over **C programming**, by focusing on **abstract data types** including the main components, **structures**, **linked lists**, **modules**, **memory management, **file handling**, and the **compilation process**... In addition, **C++ programming** principles and mechanisms like **encapsulation**, **inheritance**, **polymorphism**, **generic programming**, and **templates** were taught. The course also teaches script languages as another approach to programming.


## World Atlas
Create a world atlas that contains countries, cities and information about them. 
The script receives two parameters
<ol>
  <li>Number of countries (the number of countries that should be read from the countries file)</li>
  <li>Configuration file path (contains countries and cities that should be in the system).</li>

### Explanation about the entities in the system:

#### Country:
Every country has a name, geographical area, number of cities that it contains and a list of those cities.

#### City:
Every city has a name, number of residents and a popular food.

#### Geographical Area:
Two coordinates - the first coordinate (x1,y1) represents the upper left point, and the second coordinate represents the lower right point.

### Functionalities:
```
please choose one of the following numbers:
1 : print countries
2 : add city to country
3 : remove city from country
4 : find country in area
5 : print country by name
6 : exit
```

print country by name example:
```
Country Israel coordinates: <1,5> , <8,2>
HodHasharon includes 56700 residents and their favorite food is
frozenYogurt.
Berrsheba includes 202495 residents and their favorite food is
hummus.
```
<p align="center">
<img src="https://in.bgu.ac.il/marketing/DocLib/Pages/graphics/heb-en-arabic-logo-small.png">
</p>
