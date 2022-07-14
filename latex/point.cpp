const double EPS = 1e-7;

struct point {
    double x, y;

    point operator * (int a) {return {a * x, a * y};}
    point operator / (int a) {return {x / a, y / a};}
    point operator + (point b){return {x + b.x, y + b.y};}
    point operator - (point b){return {x - b.x, y - b.y};}

    double operator * (point b){return x * b.x + y * b.y;}
    double operator ^ (point b){return x * b.y - y * b.x;}
};

double abs(point a){ return sqrt(a.x * a.x + a.y * a.y); }

int sign(double a){
    if(abs(a) < EPS) return 0;
    else return (a > 0 ? 1 : -1);
}

int ori(point a, point b, point c){
    return sign((b-a)^(c-a));
}