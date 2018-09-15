#include "EFrustum.h"

namespace E3D
{
    EFrustum::EFrustum(CAMERA_TYPE mode, const EVector4D &pos, const EVector4D &dir,
        const EVector4D &target, EFloat nearZ, EFloat farZ, EFloat fov, EFloat viewportWidth,
        EFloat viewportHeight)
        : camMode(mode), position(pos), direction(dir), camTarget(target),
        clip_z_near(nearZ), clip_z_far(farZ), fov(fov), viewport_width(viewportWidth),
        viewport_height(viewportHeight), camUp(EVector4D::UNIT_Y), camRight(EVector4D::UNIT_X),
        camLook(EVector4D::UNIT_Z), mWorldToCamera(EMatrix44::IDENTITY),
        mCameraToPerspective(EMatrix44::IDENTITY), mPerspectiveToScreen(EMatrix44::IDENTITY)
    {
        viewport_center_X       = (viewport_width - 1) * 0.5f;
        viewport_center_Y       = (viewport_height - 1) * 0.5f;

        aspect_ratio            = viewport_width / viewport_height;

        viewplane_width         = 2.0f;
        viewplane_height        = 2.0f / aspect_ratio;

        EFloat tan_fov_div2 = tan(Degree_To_Radian(fov * 0.5f));
        view_dist = 0.5f * viewplane_width / tan_fov_div2;

        EVector4D point = EVector4D::ZERO;
        
        //right plane
        EVector4D normalR = EVector4D(-view_dist, 0, viewplane_width * 0.5f);
        clip_plane_R = EPlane3D(point, normalR);

        //left plane
        EVector4D normalL = EVector4D(view_dist, 0, viewplane_width * 0.5f);
        clip_plane_L = EPlane3D(point, normalL);

        //top plane
        EVector4D normalT = EVector4D(0, -view_dist, viewplane_height * 0.5f);
        clip_plane_T = EPlane3D(point, normalT);

        //bottom plane
        EVector4D normalB = EVector4D(0, view_dist, viewplane_height * 0.5f);
        clip_plane_B = EPlane3D(point, normalB);

        mPerspectiveToScreen = EMatrix44(
            view_dist, 0, 0, 0,
            0, view_dist * aspect_ratio, 0, 0,
            0, 0, 1, 1,
            0, 0, 0, 0
        );

    }

}