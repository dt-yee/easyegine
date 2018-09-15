#pragma once
#include "ECommon.h"
#include "EVector.h"
#include "EMatrix.h"
#include "ECore.h"

namespace E3D
{
    enum CAMERA_TYPE
    {
        CAMERA_MODEL_ELUA = 1, 
        CAMERA_MODEL_UVN = 2,
    };

    struct EFrustum
    {
        EInt    state;
        EInt    attribute;
        CAMERA_TYPE camMode;

        EVector4D position;
        EVector4D direction;    //camera look at direction

        //UVN model
        EVector4D camUp;        //uvn up direction
        EVector4D camRight;     //uvn right direction
        EVector4D camLook;      //uvn look at direction
        EVector4D camTarget;    //uvn look at point

        EFloat view_dist;   //distance from viewpoint to view plane

        EFloat fov;         //field of view

        EFloat clip_z_near;         //near section
        EFloat clip_z_far;          //far section

        EPlane3D clip_plane_R;      //right section
        EPlane3D clip_plane_L;      //left section
        EPlane3D clip_plane_T;      //top section
        EPlane3D clip_plane_B;      //bottom section

        EFloat viewplane_width;     //view plane size     
        EFloat viewplane_height;

        EFloat viewport_width;      //screen size
        EFloat viewport_height;
        EFloat viewport_center_X;   //screen center
        EFloat viewport_center_Y;

        EFloat aspect_ratio;        //ratio of screen

        EMatrix44 mWorldToCamera;           //matrix world to camera
        EMatrix44 mCameraToPerspective;     //matrix camera to perspective
        EMatrix44 mPerspectiveToScreen;     //matrix perspective to screen

        EFrustum(CAMERA_TYPE mode, const EVector4D &pos, const EVector4D &dir,
            const EVector4D &target, EFloat nearZ, EFloat farZ, EFloat fov,
            EFloat viewportWidth, EFloat viewportHeight);

    };
}
