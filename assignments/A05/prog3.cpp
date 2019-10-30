///////////////////////////////////////////////////////////////////////////////
//
// Date:             30 October 2019
// Title:            Program 3 - Top 3
// Semester:         Fall 2019
// Course:           CMPS 3013 
// Assignment:       A05
// Author:           Mary Davis
// Email:            maryelijah2010@gmail.com
// Files:            citites.json, geo.hpp, heap.hpp, 
//                   json.hpp, JsonFacade.hpp
// Description:
//       Takes a list of cities, finds the haversine distance between all   
//       cities in the list. Sets haversine distance to priority and puts 
//      them into a min heap based on the priority. And prints out the cities   
//      from closest to farthest
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string.h>
#include "Heap.hpp"
#include "JsonFacade.hpp"
#include "json.hpp"
#include "Geo.hpp"

using namespace std;

using json = nlohmann::json;

struct City{
    int Priority;
    string Name;
    int Growth_from_2000_to_2013;
    int Latitude;
    int Longitude;
    int Rank;
    string State;
    City(){
        Priority = 0;
        Name = "";
        Growth_from_2000_to_2013 = 0;
        Latitude = 0;
        Longitude = 0;
        Rank = 0;
        State = "";
        
    }
    City(json obj){
        Name = obj["city"];
        Priority = obj["population"];
        Growth_from_2000_to_2013 = obj["growth_from_2000_to_2013"];
        Latitude = obj["latitude"];
        Longitude = obj["longitude"];
        Rank = obj["rank"];
        State = obj["state"];
    }
};


int main(int argc, char **argv){ 

    string filename = "cities.json";
    JsonFacade J(filename); // already knows all about the json file 
    json temp_city;
    City* c;

    City** Cities = new City*[J.getSize()];
    Heap <City> H(1000,false);

    for(int i=0;i<J.getSize();i++){
        temp_city = J.getNext();
        Cities[i] = new City(temp_city);
    }
    
    for(int i=0;i<J.getSize();i++){
        // get one city
        cout<<Cities[i]->Name<<endl;
        Coordinate Coord1 = Coordinate(Cities[i]->Longitude, Cities[i]->Latitude);
        for(int j = 0;j<J.getSize();j++){
            if(i != j){
                Coordinate Coord2 = Coordinate(Cities[j]->Longitude, Cities[j]->Latitude);
                Cities[j]->Priority = HaversineDistance(Coord1, Coord2);
                H.Insert(Cities[j]);}
            }
             for(int i = 1; i <=argc ; i++){
            c=H.Extract(); 
            cout <<"\t" << i << "." <<c->Name<<" "<<c->Priority<<endl;
             }
       
         H.Delete();
        
    }






    return 0;
}