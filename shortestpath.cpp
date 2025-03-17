#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

#define INF numeric_limits<double>::infinity()
#define EARTH_RADIUS 6371.0  // Radius of Earth in kilometers

// Structure to store latitude and longitude
struct Location {
    string name;
    double latitude;
    double longitude;
};

// Function to calculate distance between two locations using Haversine formula
double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dLon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS * c;  // Distance in km
}

// Graph class for Dijkstra’s Algorithm
class Graph {
public:
    unordered_map<string, vector<pair<string, double>>> adjList;
    unordered_map<string, Location> locations;

    void addLocation(string name, double lat, double lon) {
        locations[name] = {name, lat, lon};
    }

    void addEdge(string loc1, string loc2) {
        if (locations.find(loc1) == locations.end() || locations.find(loc2) == locations.end()) {
            cout << "Invalid locations: " << loc1 << " or " << loc2 << "\n";
            return;
        }
        double distance = haversine(locations[loc1].latitude, locations[loc1].longitude,
                                    locations[loc2].latitude, locations[loc2].longitude);
        adjList[loc1].push_back({loc2, distance});
        adjList[loc2].push_back({loc1, distance});
    }

    void dijkstra(string src, string dest) {
        if (locations.find(src) == locations.end() || locations.find(dest) == locations.end()) {
            cout << "Invalid source or destination location!\n";
            return;
        }

        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<>> pq;
        unordered_map<string, double> dist;
        unordered_map<string, string> parent;

        for (auto &loc : locations) dist[loc.first] = INF;
        dist[src] = 0.0;
        pq.push({0.0, src});

        while (!pq.empty()) {
            auto [currDist, curr] = pq.top();
            pq.pop();

            if (curr == dest) break;

            for (auto &[neighbor, weight] : adjList[curr]) {
                if (dist[curr] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[curr] + weight;
                    pq.push({dist[neighbor], neighbor});
                    parent[neighbor] = curr;
                }
            }
        }

        if (dist[dest] == INF) {
            cout << "No path found from " << src << " to " << dest << "\n";
            return;
        }

        // Printing shortest path
        vector<string> path;
        for (string at = dest; at != ""; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest path from " << src << " to " << dest << ":\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal Distance: " << dist[dest] << " km\n";
    }
};

int main() {
    Graph g;

 // Adding locations on IIT ISM campus
g.addLocation("Main gate", 23.809308, 86.442553);
g.addLocation("Teacher colony",23.811089, 86.444374);
g.addLocation("Rock garden",23.809800, 86.442671);
g.addLocation("ISM campus administive office",23.810034, 86.442733);
g.addLocation("UGC park",23.810501, 86.442334);
g.addLocation("India post IIT",23.811326, 86.442203);
g.addLocation("Academic building dep.electrical",23.811667, 86.441531);
g.addLocation("Raman hall dep. of physics",23.811511, 86.441206);
g.addLocation("Electrical eng.dep.",23.811637, 86.440480);
g.addLocation("ECE dep.",23.811735, 86.440659);
g.addLocation("civil eng. dep.",23.811664, 86.440525);
g.addLocation("Academic complex",23.811447, 86.440978);
g.addLocation("Faculty apartments",23.810536, 86.439829);
g.addLocation("ISM children park",23.810536, 86.437801);
g.addLocation("Tample",23.811313, 86.440007);
g.addLocation("IIT health center",23.812014, 86.439067);
g.addLocation("ISM durga mandap",23.812020, 86.437998);
g.addLocation("Prathmik vidhyalay ismag",23.811027, 86.437648);
g.addLocation("Staff recreation club",23.812757, 86.437738);
g.addLocation("Computer science & eng. dep.",23.811868, 86.440903);
g.addLocation("Managment dep.",23.812165, 86.440446);
g.addLocation("EDC,IIT dhanbad",23.812069, 86.441397);
g.addLocation("ISM ENVIS center",23.812433, 86.439868);
g.addLocation("Environmental dep.",23.812627, 86.440072);
g.addLocation("Mechanical eng.dep.",23.813218, 86.439451);
g.addLocation("Fual & Mineral eng.dep",23.812807, 86.439606);
g.addLocation("HSE dep.",23.813720, 86.440402);
g.addLocation("Electrical Substation",23.814257, 86.438506);
g.addLocation("Scolomin house",23.811131, 86.443151);
g.addLocation("SBI ATM IIT",23.811735, 86.442133);
g.addLocation("ism Upper Ground",23.812979, 86.441042);
g.addLocation("oval ground",23.814033, 86.441207);
g.addLocation("Petrified wood",23.813768, 86.441211);
g.addLocation("Chemistry Laboratory for UG",23.813137, 86.440245);
g.addLocation("ISM administrative buliding",23.814502, 86.442389);
g.addLocation("Main building",23.814453, 86.441252);
g.addLocation("mining eng.dep",23.814434, 86.440954);
g.addLocation("Applide geophysis dep.",23.814647, 86.441618);
g.addLocation("Applide geology dep.",23.814449, 86.441401);
g.addLocation("Old library",23.815126, 86.442003);
g.addLocation("Main canteen",23.815100, 86.441575);
g.addLocation("Penman auditorium",23.814951, 86.441208);
g.addLocation("opel hostel",23.815610, 86.441420);
g.addLocation("Science block",23.814634, 86.440113);
g.addLocation("Diamond hostel",23.815448, 86.440518);
g.addLocation("Central workshop",23.814814, 86.439361);
g.addLocation("Open air theater",23.814057, 86.440061);
g.addLocation("OLHC",23.814127, 86.440165);
g.addLocation("GJLT",23.814004, 86.440301);
g.addLocation("International EDC",23.815682, 86.439721);
g.addLocation("Central library",23.816039, 86.442242);
g.addLocation("Pentroleum eng. dep",23.815546, 86.442995);
g.addLocation("Applied geophysics annexture building",23.814860, 86.443178);
g.addLocation("Administrative block",23.814192, 86.442378);
g.addLocation("Ruby garden",23.813194, 86.443464);
g.addLocation("ism lower ground",23.813016, 86.442620);
g.addLocation("Ruby hostel",23.813319, 86.444558);
g.addLocation("Eco Vatika",23.812984, 86.444334);
g.addLocation("Rosaline hostel",23.813339, 86.445116);
g.addLocation("international hostel",23.813684, 86.444564);
g.addLocation("ISM staff Quaters",23.813843, 86.447296);
g.addLocation("IIT ISM shooting range",23.814503, 86.443593);
g.addLocation("Seismological observatory",23.815191, 86.444047);
g.addLocation("Jasper hostel",23.816573, 86.440812);
g.addLocation("Jasper garden",23.816629, 86.441641);
g.addLocation("Ram Dhani Tea Shop",23.816435, 86.440282);
g.addLocation("NLHC",23.816353, 86.439450);
g.addLocation("Pumping station",23.817396, 86.439306);
g.addLocation("Amber hostel",23.818569, 86.439671);
g.addLocation("Gymkhana ground",23.817750, 86.438796);
g.addLocation("ISM sports complex",23.816690, 86.438823);
g.addLocation("Basketball court",23.817009, 86.438871);
g.addLocation("New sports complex",23.816798, 86.438840);
g.addLocation("SAC",23.817416, 86.437621);
g.addLocation("IIT boxing",23.817573, 86.437331);
g.addLocation("Karma Jyoti",23.817497, 86.437467);
g.addLocation("Topaz Hostel",23.818711, 86.437965);
g.addLocation("NCC IIT",23.818864, 86.437149);
g.addLocation("ISM dhaiya gate",23.820746, 86.435400);

    // Connecting locations with edges
    g.addEdge("Main gate", "Teacher colony");
    g.addEdge("Main gate", "Rock garden");
    g.addEdge("Rock garden", "ISM campus administive office");
    g.addEdge("ISM campus administive office", "UGC park");
    g.addEdge("UGC park", "India post IIT");
    g.addEdge("UGC park", "Faculty apartments");
    g.addEdge("Faculty apartments", "ISM children park");
    g.addEdge("Faculty apartments", "Academic complex");
    g.addEdge("Academic complex", "Electrical eng.dep.");
    g.addEdge("Academic complex", "Tample");
    g.addEdge("Academic complex", "India post IIT");
    g.addEdge("Academic complex", "Raman hall dep. of physics");
    g.addEdge("Academic complex", "civil eng. dep.");
    g.addEdge("Academic complex", "ECE dep.");
    g.addEdge("Tample", "IIT health center");
    g.addEdge("IIT health center", "Staff recreation club");
    g.addEdge("IIT health center", "Prathmik vidhyalay ismag");
    g.addEdge("IIT health center", "ISM durga mandap");
    g.addEdge("Staff recreation club", "ISM durga mandap");
    g.addEdge("Tample", "Computer science & eng. dep.");
    g.addEdge("Computer science & eng. dep.", "Managment dep.");
    g.addEdge("Computer science & eng. dep.", "EDC,IIT dhanbad");
    g.addEdge("EDC,IIT dhanbad","ISM ENVIS center");
    g.addEdge("EDC,IIT dhanbad","Environmental dep.");
    g.addEdge("EDC,IIT dhanbad","SBI ATM IIT");
    g.addEdge("Fual & Mineral eng.dep","Environmental dep.");
    g.addEdge("Mechanical eng.dep.","Environmental dep.");
    g.addEdge("Scolomin house", "India post IIT");
    g.addEdge("Ruby garden","Scolomin house");
    g.addEdge("Ruby garden", "Ruby hostel");
    g.addEdge("Ruby garden","Administrative block");
    g.addEdge("Ruby hostel", "Rosaline hostel");
    g.addEdge("Ruby hostel", "Eco Vatika");
    g.addEdge("Rosaline hostel","international hostel");
    g.addEdge("international hostel","IIT ISM shooting range");
    g.addEdge("IIT ISM shooting range","ISM staff Quaters");
    g.addEdge("IIT ISM shooting range","Applied geophysics annexture building");
    g.addEdge("Applied geophysics annexture building","Pentroleum eng. dep");
    g.addEdge("Applied geophysics annexture building","Administrative block");
    g.addEdge("Pentroleum eng. dep","Central library");
    g.addEdge("Central library","Old library");
    g.addEdge("Old library","Main canteen");
    g.addEdge("Old library","opel hostel");
    g.addEdge("Old library","ISM administrative buliding");
    g.addEdge("Main canteen","Penman auditorium");
    g.addEdge("opel hostel","Diamond hostel");
    g.addEdge("Diamond hostel","Central workshop");
    g.addEdge("Diamond hostel","Science block");
    g.addEdge("Science block","Central workshop");
    g.addEdge("Science block","GJLT");
    g.addEdge("GJLT","HSE dep.");
    g.addEdge("Central workshop","OLHC");
    g.addEdge("Central workshop","International EDC");
    g.addEdge("OLHC","GJLT");
    g.addEdge("OLHC","Open air theater");
    g.addEdge("Central workshop","Electrical Substation");
    g.addEdge("Staff recreation club","Electrical Substation");
    g.addEdge("GJLT","oval ground");
    g.addEdge("GJLT","ism Upper Ground");
    g.addEdge("SBI ATM IIT","ism Upper Ground");
    g.addEdge("Chemistry Laboratory for UG","ism Upper Ground");
    g.addEdge("oval ground","ism Upper Ground");
    g.addEdge("oval ground","Petrified wood");
    g.addEdge("oval ground","ISM administrative buliding");
    g.addEdge("oval ground","Main building");
    g.addEdge("mining eng.dep","Main building");
    g.addEdge("Applide geophysis dep.","Main building");
    g.addEdge("Applide geology dep.","Main building");
    g.addEdge("Central library","Jasper garden");
    g.addEdge("Jasper hostel","Jasper garden");
    g.addEdge("Ram Dhani Tea Shop","Jasper garden");
    g.addEdge("Ram Dhani Tea Shop","Jasper hostel");
    g.addEdge("Ram Dhani Tea Shop","NLHC");
    g.addEdge("Ram Dhani Tea Shop","Pumping station");

    g.addEdge("NLHC","Pumping station");
    g.addEdge("ISM sports complex","Pumping station");
    g.addEdge("Gymkhana ground","Pumping station");
    g.addEdge("ISM sports complex","New sports complex");
    g.addEdge("ISM sports complex","Basketball court");
    g.addEdge("Gymkhana ground","Amber hostel");
    g.addEdge("Gymkhana ground","Topaz Hostel");
    g.addEdge("Gymkhana ground","SAC");
    g.addEdge("IIT boxing","SAC");
    g.addEdge("Karma Jyoti","SAC");
    g.addEdge("NCC IIT","Topaz Hostel");
    g.addEdge("ISM dhaiya gate","NCC IIT");



    // Finding shortest path
    string src, dest;
    cout << "Enter source location: ";
    getline(cin, src);
    cout << "Enter destination location: ";
    getline(cin, dest);

    g.dijkstra(src, dest);

    return 0;
}