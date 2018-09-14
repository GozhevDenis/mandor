#pragma once

#define MC_X 1
#define MC_Y 1
#define MC_Z 1

//#define DT 0.00565
//#define DX 0.01
//#define DY 0.01
//
//#define DZ 0.01
//#define DR 0.01

extern int    min[3];
extern int    max[3];

extern double dx,
              dy,
              dz;
extern double l[3];

extern double dt,
              nStep;

// This parameter exists only for a test. dx = dy = dy in equation yee
extern const double dr;

// Taken from '/usr/include/math.h' on Arch linux, tested on few sites (sorry).
#define PI (3.141592653589793238462643383279502884)

// Не понял до конца, как лучше задавать. Пока сделал из файла. Если нет,
// то что использовать для инициализации mesh
extern int cpu_min[3],
           cpu_max[3];

//constexpr int cpu_min[3] = {0, 0, 0},
//              cpu_max[3] = {100, 100, 100};
