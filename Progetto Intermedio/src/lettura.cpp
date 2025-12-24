#include "../include/lettura.h"

lettura::lettura()
: yaw_v(0.0), yaw_a(0.0), pitch_v(0.0), pitch_a(0.0), roll_v(0.0), roll_a(0.0)
{}

lettura::lettura(double yv, double ya, double pv, double pa, double rv, double ra)
: yaw_v(yv), yaw_a(ya), pitch_v(pv), pitch_a(pa), roll_v(rv), roll_a(ra)
{}

double lettura::get_yaw_v() const {
    return yaw_v;
}
double lettura::get_yaw_a() const {
    return yaw_a;
}
double lettura::get_pitch_v() const {
    return pitch_v;
}
double lettura::get_pitch_a() const {
    return pitch_a;
}
double lettura::get_roll_v() const {
    return roll_v;
}
double lettura::get_roll_a() const {
    return roll_a;
}
