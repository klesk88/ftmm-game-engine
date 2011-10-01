#ifndef   __Light_H__
#define  __Light_H__

#include "Vector4.h"
#include "Vector3.h"
#include "SDL.h"
#include <string.h>

class Light
{

	public:
		// internal method for calculating current squared distance from some world position
		void calcTempSquareDist(const Vector3& worldPos);

		// Defines the type of light
        enum LightTypes
        {
            // Point light sources give off light equally in all directions, so require only position not direction
            LT_POINT = 0,
            // Directional lights simulate parallel light beams from a distant source, hence have direction but no position
            LT_DIRECTIONAL = 1,
            // Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
            LT_SPOTLIGHT = 2
        };

		// Standard destructor.
        ~Light();

		// Sets the type of light - see LightTypes for more info.
        void setType(LightTypes type);

        // Returns the light type.
        LightTypes getType(void) const;

		 /** Sets the position of the light.
            @remarks
                Applicable to point lights and spotlights only.
            @note
                This will be overridden if the light is attached to a SceneNode.
        */
        void setPosition(float x, float y, float z);

		        /** Sets the position of the light.
            @remarks
                Applicable to point lights and spotlights only.
            @note
                This will be overridden if the light is attached to a SceneNode.
        */
        void setPosition(const Vector3& vec);

        /** Returns the position of the light.
            @note
                Applicable to point lights and spotlights only.
        */
        const Vector3& getPosition(void) const;

        /** Sets the direction in which a light points.
            @remarks
                Applicable only to the spotlight and directional light types.
            @note
                This will be overridden if the light is attached to a SceneNode.
        */
        void setDirection(float x, float y, float z);

        /** Sets the direction in which a light points.
            @remarks
                Applicable only to the spotlight and directional light types.
            @note
                This will be overridden if the light is attached to a SceneNode.
        */
        void setDirection(const Vector3& vec);

        /** Returns the light's direction.
            @remarks
                Applicable only to the spotlight and directional light types.
        */
        const Vector3& getDirection(void) const;

		/** Sets the colour of the diffuse light given off by this source.
            @remarks
                Material objects have ambient, diffuse and specular values which indicate how much of each type of
                light an object reflects. This value denotes the amount and colour of this type of light the light
                exudes into the scene. The actual appearance of objects is a combination of the two.
            @par
                Diffuse light simulates the typical light emanating from light sources and affects the base colour
                of objects together with ambient light.
        */
        void setDiffuseColour(float red, float green, float blue);

        /** Sets the colour of the specular light given off by this source.
            @remarks
                Material objects have ambient, diffuse and specular values which indicate how much of each type of
                light an object reflects. This value denotes the amount and colour of this type of light the light
                exudes into the scene. The actual appearance of objects is a combination of the two.
            @par
                Specular light affects the appearance of shiny highlights on objects, and is also dependent on the
                'shininess' Material value.
        */
        void setSpecularColour(float red, float green, float blue);

        /** Sets the attenuation parameters of the light source i.e. how it diminishes with distance.
            @remarks
                Lights normally get fainter the further they are away. Also, each light is given a maximum range
                beyond which it cannot affect any objects.
            @par
                Light attenuation is not applicable to directional lights since they have an infinite range and
                constant intensity.
            @par
                This follows a standard attenuation approach - see any good 3D text for the details of what they mean
                since i don't have room here!
            @param
                range The absolute upper range of the light in world units
            @param
                constant The constant factor in the attenuation formula: 1.0 means never attenuate, 0.0 is complete attenuation
            @param
                linear The linear factor in the attenuation formula: 1 means attenuate evenly over the distance
            @param
                quadratic The quadratic factor in the attenuation formula: adds a curvature to the attenuation formula.
        */
        void setAttenuation(float range, float constant, float linear, float quadratic);

        /** Returns the absolute upper range of the light.
        */
        float getAttenuationRange(void) const;

        /** Returns the constant factor in the attenuation formula.
        */
        float getAttenuationConstant(void) const;

        /** Returns the linear factor in the attenuation formula.
        */
        float getAttenuationLinear(void) const;

        /** Returns the quadric factor in the attenuation formula.
        */
        float getAttenuationQuadric(void) const;

		
	private:

		// Normal constructor. Should not be called directly, but rather the SceneManager::createLight method should be used.
        Light(const char* name);
		
		//Default Costructor
		Light();

		// Variables
		LightTypes m_light_type;
		Vector3 m_position;
		Vector3 m_direction;
		Vector3 m_diffuse;
		Vector3 m_specular;
};


#endif