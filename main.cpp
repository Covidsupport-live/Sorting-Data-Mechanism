#include<bits/stdc++.h>
#include<iostream>
#define std_lat 36.0
#define std_lon 68.0
#define std_dist 295
using namespace std;

struct details
{
    string supllier;
    string location;
    string district;
    string state;
    string mail;
    string mob;
    string info;
    string last_update;
    long unsigned int ind;
    long double lat;
    long double lon;
    int dist_id;
};

vector<details> grid[16][16];
vector<details> indx;


long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
 

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
 
    long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);
 
    ans = 2 * asin(sqrt(ans));

    long double R = 6371;
    ans = ans * R;
 
    return ans;
}



vector<long double> read_record(int dist_id)
{
    FILE *fp = fopen("/home/tanmoy/Desktop/Data-Sorting/LatLon.txt", "r"); /// ****** file location must be changed
    char str[20];
    fscanf(fp,"%s",str);
    assert( (dist_id>=0) && (dist_id<=atoi(str)));
    rewind(fp);
    
    string targ = to_string(dist_id);
    vector<long double> coor;
    while(fscanf(fp,"%s",str))
    {
        if(strcmp(str,targ.c_str())==0)
            {
                fscanf(fp,"%s",str);
                coor.push_back(stof(str));
                fscanf(fp,"%s",str);
                coor.push_back(stof(str));
                break;
            }
    }
    
    fclose(fp);
    return coor;
}


void insertData(int dist_id,string supllier,string location,string district, string state, string mail,string mob,string info,string last_update)
{
    vector<long double> coor = read_record(dist_id);
    long double lat = coor[0], lon = coor[1];
    
    int row = (std_lat - lat)/2;
    int col = (lon - std_lon)/2;
    
    long unsigned int i = indx.size();
    details ob1 = {supllier,location,district,state,mail,mob,info,last_update,i,lat,lon,dist_id};
    grid[row][col].push_back(ob1);
    indx.push_back(ob1);
} 


vector<pair<float, long unsigned>> searchNear(long double lat, long double lon,long double maxx_dist)
{
    int expand = maxx_dist / std_dist  + 1;
    int row = (std_lat - lat)/2;
    int col = (lon - std_lon)/2;

    vector<pair<float, long unsigned> > vp;
    
    for(int i=0;i< 2*expand+1;i++)
        for(int j=0;j< 2*expand+1;j++)
            {
                if( (row-expand+i < 16) && (col-expand+j< 16) && (row-expand+i >=0) && (col-expand+j >= 0) )
                {
                for(auto x:grid[row-expand+i][col-expand+j])
                {
                    long double dis = distance(x.lat, x.lon,lat,lon);
                    if(dis<maxx_dist)
                    {
                        vp.push_back(make_pair(dis, x.ind));
                    }
                }
                }
            }
    sort(vp.begin(), vp.end());
    return vp;
}

vector<pair<float, long unsigned>> searchNear(int dist_id,long double maxx_dist)
{
    vector<long double> coor = read_record(dist_id);
    return searchNear(coor[0], coor[1], maxx_dist);
}


int main(int argc, const char * argv[])
{
    //insertData(int dist_id, string supllier, string location, string district, string state, string mail, string mob, string info, string last_update)  ... this input format
    
    insertData(730,"NRS","Sealdah","Kolkata","WB","xyz@gov.in","323232","N/a","N/a");
    insertData(724,"Desun","Bidhan","Siliguri","WB","N/a","231432","N/a","Today");
    insertData(727,"Desun","Jn. More","Jalpaiguri","WB","N/a","87546","N/a","Today");
    insertData(732,"Applo","Lalbag","Murshidabad","WB","N/a","2312132","N/a","Today");
    insertData(726,"Neotia","Hazra","Howrah","WB","N/a","423232","N/a","Today");
    insertData(725,"CMH","Chamta","Hoogly","WB","N/a","9999999","N/a","Today");
    insertData(722,"Applo","Dinhata","CoochBehar","WB","N/a","23232","N/a","N/a");
    insertData(741,"MCC","Raigunj","N.DinajPore","WB","N/a","9999","N/a","N/a");
    insertData(741,"SuperSP","Islampore","N.DinajPore","WB","N/a","2323","N/a","N/a");
    insertData(101,"NTT","Patna","Patna","BH","N/a","33232","N/a","N/a");
    insertData(722,"Applo","Cooch Behar","CoochBehar","WB","N/a","23992232","N/a","N/a");
    insertData(159,"FRC","Motera","Ahmedabad","GUJ","N/a","23992232","N/a","N/a");
    insertData(176,"DESSun","Kach","Kach","GUJ","N/a","23992232","N/a","N/a");
    insertData(159,"SUper","Ahmedabad","Ahmedabad","GUJ","N/a","23992232","N/a","N/a");
    insertData(176,"Applo","Vadodora","Kach","GUJ","N/a","23992232","N/a","N/a");
   

    long double target_lat, target_lon, max_dist;
    cin>>target_lat>>target_lon>>max_dist;
    
    vector<pair<float, long unsigned> >  nearest_cen = searchNear(target_lat, target_lon, max_dist);
    
    int flag = 0;
    
    for(auto x:nearest_cen) // output same ,  x.first represents the distance
    {
        cout<<indx[x.second].supllier<<", "<<indx[x.second].location<<" at "<<x.first<<" km(Air)\n";
        flag = 1;
    }
    
    if(flag==0)
    cout<<"No Results Found\n";
    
    return 0;
}

// 22.572 88.65 3000
//25.0108 88.1411 3000
//28.628375  77.074996 1000
