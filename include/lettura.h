#ifndef LETTURA_H
#define LETTURA_H

class lettura
{
    private:
    double yaw_v, yaw_a, pitch_v, pitch_a, roll_v, roll_a;
    
    public:
    lettura(double yaw_v, double yaw_a, double pitch_v, double pitch_a, double roll_v, double roll_a);
    lettura();

    double get_yaw_v();
    double get_yaw_a();
    double get_pitch_v();
    double get_pitch_a();
    double get_roll_v();
    double get_roll_a();
};
#endif
