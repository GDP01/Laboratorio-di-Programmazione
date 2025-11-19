#include "lettura.h"

lettura::lettura()
{
    yaw_v, yaw_a, pitch_v, pitch_a, roll_v, roll_a = 0;
}

lettura::lettura(double yaw_v, double yaw_a, double pitch_v, double pitch_a, double roll_v, double roll_a)
{
    yaw_v = yaw_v;
    yaw_a = yaw_a;
    pitch_v = pitch_v;
    pitch_a = pitch_a;
    roll_v = roll_v;
    roll_a = roll_a;
}

double lettura::get_yaw_v()
{
    return yaw_v;
}
double lettura::get_yaw_a()
{
    return yaw_a;
}
double lettura::get_pitch_v()
{
    return pitch_v;
}
double lettura::get_pitch_a()
{
    return pitch_a;
}
double lettura::get_roll_v()
{
    return roll_v;
}
double lettura::get_roll_a()
{
    return roll_a;
}