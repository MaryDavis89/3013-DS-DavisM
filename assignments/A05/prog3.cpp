
#include <iostream>
#include <fstream>
#include <string.h>
#include "Heap.hpp"
#include "JsonFacade.hpp"
#include "json.hpp"

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


int main(){ 

    string filename = "cities.json";
    JsonFacade J(filename); // already knows all about the json file 
    json temp_city;

    City** Cities = new City*[J.getSize()];

    for(int i=0;i<J.getSize();i++){
        temp_city = J.getNext();
        Cities[i] = new City(temp_city);
    }
    
    for(int i=0;i<J.getSize();i++){
        cout << Cities[i]->Name<<endl;
        // get one city
        
    }






    return 0;
}