const double EPS = 1e-7;

struct point {
    double x, y;

    point operator * (int a) {return {a * x, a * y};}
    point operator / (int a) {return {x / a, y / a};}
    point operator + (point b){return {x + b.x, y + b.y};}
    point operator - (point b){return {x - b.x, y - b.y};}

    double operator * (point b){return x * b.x + y * b.y;}
    double operator ^ (point b){return x * b.y - y * b.x;}

    bool operator < (point b){
        return x == b.x ? y < b.y : x < b.x;
    }
};

double abs(point a){ return sqrt(a.x * a.x + a.y * a.y); }

int sign(double a){
    if(abs(a) < EPS) return 0;
    else return (a > 0 ? 1 : -1);
}

int ori(point a, point b, point c){
    return sign((b-a)^(c-a));
}

bool colinear(point a, point b, point c){
    return sign((b-a)^(c-a)) == 0;
}

bool between(point a, point b, point c){
    if(!colinear(a,b,c)) return false;
    return sign((a-c) * (b-c)) <= 0; 
}

bool intersect(point a, point b, point c, point d){
    int abc = ori(a,b,c);
    int abd = ori(a,b,d);
    int cda = ori(c,d,a);
    int cdb = ori(c,d,b);
    if(abc==0 && abd==0) 
        return between(a,b,c) || between(a,b,d) || between(c,d,a) || between(c,d,b);
    return abc * abd <= 0 && cda * cdb <= 0;
}

point intersect_point(point a, point b, point c, point d){
    int adc = (d-a) ^ (c-a);
    int bdc = (d-b) ^ (c-b);
    return (a * bdc + b * adc) / (adc + bdc);
}

point projection(point a, point b, point c){
    return (b-a) * ((b-a) * (c-a)) / (abs(b-a) * abc(b-a)) ;
}

vector<point> convex_hull(vector<point> points){
    sort(points.begin(),points.end());

    vector<point> hull;
    for(int t = 0; t < 2; t++){
        int sz = hull.size();
        for(int i = 0; i < points.size(); i++){
            while(hull.size() >= sz+2 && ori(hull[hull.size()-2], hull.back(), points[i]) <= 0){
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        hull.pop_back();
        reverse(points.begin(),points.end());
    }
    return hull;
}

double area(point a, point b, point c){
    return abs(((c-a) ^ (b-a))/2);
}

double farthest_pair_of_points(vector<point> hull){
    double res = 0;
    if(hull.size() == 2){
        return abs(hull[0]-hull[1]);
    }
 
    hull.push_back(hull[0]);
    
    int j = 2;
 
    for(int i = 0;i < hull.size()-1;i++){
        while(area(hull[i],hull[i+1],hull[j]) < area(hull[i],hull[i+1],hull[(j+1)%hull.size()])){
            j = (j+1)%hull.size();
        }
        res = max(res,max(abs(hull[i]-hull[j]),abs(hull[i+1]-hull[j])));
    }
 
    return res;
}

bool polar_sort(point a, point b){
    auto up = [&](point p){
        return p.y > 0 || p.y == 0 && p.x >= 0;
    };
    int A = up(a), B = up(b);

    if(A != B){
        return A < B;
    }

    if(sign(a^b) == 0)
        return abs(a) < abs(b);

    return sign(a^b) > 0;
}

