#pragma once

#define MC_X 1
#define MC_Y 1
#define MC_Z 1

#define DT 0.00565
#define DX 0.01
#define DY 0.01

#define DZ 0.01
#define DR 0.01

// Taken from '/usr/include/math.h' on Arch linux, tested on few sites (sorry).
#define PI (3.141592653589793238462643383279502884)

constexpr int cpu_min[3] = {0, 0, 0},
              cpu_max[3] = {100, 100, 100};
