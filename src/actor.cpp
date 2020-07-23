//
// Created by sam on 2020-07-21.
//

#include "actor.h"

Actor::Actor() {

}

Actor::~Actor() {

}

Mat36_12f Actor::genCube() {
    Arr3f a0(0.5, 0.5, 0.5);
    Arr3f b0(0.5, 0.5, -0.5);
    Arr3f c0(-0.5, 0.5, -0.5);
    Arr3f d0(-0.5, 0.5, 0.5);

    Arr3f a1(0.5, -0.5, 0.5);
    Arr3f b1(0.5, -0.5, -0.5);
    Arr3f c1(-0.5, -0.5, -0.5);
    Arr3f d1(-0.5, -0.5, 0.5);

    Arr3f n0(0, 0, 1);
    Arr3f n1(0, 0, -1);
    Arr3f n2(1, 0, 0);
    Arr3f n3(-1, 0, 0);
    Arr3f n4(0, 1, 0);
    Arr3f n5(0, -1, 0);

    Arr2f t0(0, 0);
    Arr2f t1(0, 1);
    Arr2f t2(1, 0);
    Arr2f t3(1, 1);

    Arr4f white(1, 1, 1, 1);

    Mat36_3f pos;
    pos << d0, d1, a1, a1, a0, d0, // front face
            b0, b1, c1, c1, c0, b0, // back face
            a0, a1, b1, b1, b0, a0, // right face
            c0, c1, d1, d1, d0, c0, // left face
            c0, d0, a0, a0, b0, c0, // top face
            d1, c1, b1, b1, a1, d1; // bottom face

    Mat36_3f normals;
    normals << n0.replicate(6, 1),
            n1.replicate(6, 1),
            n2.replicate(6, 1),
            n3.replicate(6, 1),
            n4.replicate(6, 1),
            n5.replicate(6, 1);

    Mat6_2f t_rec;
    t_rec << t1, t0, t2, t2, t3, t1;
    Mat36_2f t_coords = t_rec.replicate(6, 1);

    Mat36_4f colors = white.replicate(36, 1);

    Mat36_12f cube;
    cube.block<36, 3>(0, 0) = pos;
    cube.block<36, 4>(0, 3) = colors;
    cube.block<36, 3>(0, 7) = normals;
    cube.block<36, 2>(0, 10) = t_coords;

    return cube;
}
