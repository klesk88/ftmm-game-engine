#ifndef __MovableObject_H__
#define __MovableObject_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"
#include "Math.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"


class MovableObject{


	public:

		 enum TransformSpace
        {
            /// Transform is relative to the local space
            TS_LOCAL,
            /// Transform is relative to the space of the parent node
            TS_PARENT,
            /// Transform is relative to world space
            TS_WORLD
        };
		
		virtual const Quaternion & getOrientation() const;
		virtual const Vector3 & getScale() const;
		virtual const Vector3 & getPosition() const;
		virtual void translate (const Vector3& translation_value, TransformSpace relativeTo);
		virtual void setPosition(const Vector3& position_value);
		virtual void rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo);
		virtual void rotate(const Quaternion& rotation_value, TransformSpace relativeTo);
		virtual void roll(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
        virtual void pitch(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
        virtual void yaw(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
		virtual void setOrientation(const Quaternion & orientation_value);
		virtual void scale(const Vector3& scale_value);
		virtual void setScale(const Vector3& scale_value);
		
		

	protected:

		Matrix4 global_transform;



};

#endif