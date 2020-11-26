#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); i ++)
using namespace std;
using ll = long long;
using PL = pair<ll,ll>;
using P = pair<int,int>;
constexpr int INF = 1000000000;
constexpr long long HINF = 1000000000000000;
constexpr long long MOD = 1000000007;
constexpr double EPS = 1e-9;
constexpr double PI = 3.14159265358979;

/* geometry library */

// a > 0 : +1, a == 0 : 0, a < 0 : -1
int sgn(const double a) {return (a < - EPS ? -1: (a > EPS ? 1: 0));}

/* 2d Point class */
struct Point {
    double x,y;
    constexpr Point(double x = 0.0,double y = 0.0) :x(x),y(y) {}

    Point operator+() const {return *this;}
    Point operator-() const {return Point(-x,-y);}

    constexpr Point &operator+=(const Point &q) {x += q.x;y += q.y;return *this;}
    constexpr Point &operator-=(const Point &q) {x -= q.x;y -= q.y;return *this;}
    constexpr Point &operator*=(double a) {x *= a;y *= a;return *this;}
    constexpr Point &operator/=(double a) {x /= a;y /= a;return *this;}
    
    constexpr Point operator+(const Point &q) const {return Point(*this) += q;}
    constexpr Point operator-(const Point &q) const {return Point(*this) -= q;}
    constexpr Point operator*(double a) const  {return Point(*this) *= a;}
    constexpr Point operator/(double a) const {return Point(*this) /= a;}

    inline bool operator<(const Point&q) const {return (sgn(x - q.x) != 0 ? sgn(x - q.x) < 0 : sgn(y - q.y) < 0);}
    inline bool operator>(const Point&q) const {return (sgn(x - q.x) != 0 ? sgn(x - q.x) > 0 : sgn(y - q.y) > 0);}
    inline bool operator==(const Point&q) const {return (sgn(x - q.x) == 0 && sgn(y - q.y) == 0);}

    friend ostream& operator<<(ostream& os,const Point &p) {return os << '(' << p.x << ", " << p.y << ')';}
    friend istream& operator>>(istream& is,Point &p) {return is >> p.x >> p.y;}
};

constexpr double dot(const Point &p,const Point &q) {return p.x * q.x + p.y * q.y;}
constexpr double cross(const Point &p,const Point &q) {return p.x * q.y - q.x * p.y;}
constexpr double norm(const Point &p) {return dot(p,p);}
inline double length(const Point &p) {return sqrt(norm(p));}
inline double dist(const Point &p,const Point &q) {return length(p - q);}
constexpr double sgn_area(const Point &p,const Point &q,const Point &r) {return cross(q - p,r - p)/2.0;}
constexpr double area(const Point &p,const Point &q,const Point &r) {return abs(sgn_area(p,q,r));}
inline Point normalized(const Point &p) {Point x = p/length(p);return x;}
inline Point rotation(const Point &p,double arg) {return Point(cos(arg) * p.x - sin(arg) * p.y,sin(arg) * p.x + cos(arg) * p.y);}
inline double angle(const Point &p) {return atan2(p.y,p.x);}
constexpr Point rot90(const Point &p) {return Point(-p.y,p.x);}

int iSP(const Point &a,const Point &b,const Point &c) { 
    if (sgn(cross(c - b,a - b)) > 0) return 1; //ab bc __/: +1
    if (sgn(cross(c - b,a - b)) < 0) return -1;//ab bc --\: -1
    if (sgn(dot(a - b,c - b)) < 0) return 2;   //abc   ---: +2
    if (sgn(dot(a - c,b - c)) < 0) return -2;  //acb   ---: -2
    return 0;                                  //bac   ---:  0
}
//error point: changed depending on the problem
const Point error_point(INF,INF);

/* 2d Line(or Segment or Ray) class */
//2d Line class
struct Line {
    Point begin,end;
    constexpr Line(const Point &begin = Point(0.0,0.0),const Point &end = Point(0.0,0.0)):begin(begin),end(end) {}
    constexpr Point vec() const {return end - begin;}
};
using Segment = Line;
using Ray = Line;

Point ll_Intersection(const Line &l1,const Line &l2) {
    if (sgn(cross(l1.vec(),l2.vec())) == 0) return error_point;                               //parallel or partially matched
    return l1.begin + l1.vec() * cross(l2.vec(),l2.begin - l1.begin)/cross(l2.vec(),l1.vec());//Intersection
}
Point ss_Intersection(const Segment &s1,const Segment &s2) {return ll_Intersection(s1,s2);}
bool ss_isIntersect(const Segment &s1,const Segment &s2) {
    if (iSP(s2.begin,s1.begin,s1.end)*iSP(s2.end,s1.begin,s1.end) <= 0 && iSP(s1.begin,s2.begin,s2.end)*iSP(s1.end,s2.begin,s2.end) <= 0) return true;
    return false;
}
bool sr_isIntersect(const Segment &s,const Ray &r) {
    Point ret = ll_Intersection(s,r);
    if (ret == error_point) return false;
    //cout << ret << r.begin << r.end << s.begin << s.end << '\n';
    Point sv1 = s.begin - ret,sv2 = s.end - ret;
    Point rv1 = ret - r.begin,rv2 = r.end - r.begin;
    //printf("dot: %lf %lf\n",dot(sv1,sv2),dot(rv1,rv2));
    if (sgn(dot(sv1,sv2)) <= 0 && sgn(dot(rv1,rv2)) > 0) return true;
    return false; 
}
bool s_isOn(const Point &p,const Segment &s) {return iSP(p,s.begin,s.end) == 0;}
double pl_distance(const Point &p,const Line &l) {return abs(cross(l.vec(),p - l.begin)/length(l.vec()));}
double ps_distance(const Point &p,const Segment &s) {return min({length(p - s.begin),length(p - s.end),pl_distance(p,s)});}
Point proj(const Point &p,const Line &l) {return l.begin + normalized(l.vec())*(dot(l.vec(),p - l.begin)/length(l.vec()));}
Point reflection(const Point &p,const Line &l) {return proj(p,l)*2 - p;}
Line vertical_bisector(const Point &p,const Point &q) {Point mid = (p + q)/2,vec = rot90(p - q);return Line(mid,mid + vec);}

/* 2d Circle class */
struct Circle {
    Point cent; double r;
    constexpr Circle(const Point &cent = Point(0.0,0.0),double r = 0.0):cent(cent),r(r) {}
};
Circle make_circle(const Point &p,const Point &q,double r) {
    Line l = vertical_bisector(p,q);
    double x = sqrt(r*r - norm(p - q)/4);
    return Circle(l.begin + l.vec() * x,r);
}
bool c_isIn(const Circle &c,const Point &p) {return sgn(dist(c.cent,p) - c.r) <= 0;}