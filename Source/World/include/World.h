#ifndef WORLD_H
#define WORLD_H

#include "Prerequisites.h"
#include "RGBColor.h"
#include "ViewPlane.h"

typedef std::vector<std::shared_ptr<Object>> ObjectList;

class World : public std::enable_shared_from_this<World> {
	public:
		World();
		~World();

		void Build();
		void RenderScene() const;
		ShadeRecord HitObjects(const Ray &);

		ViewPlane m_ViewPlane;

		RGBColor m_BackgroundColor;

		std::shared_ptr<Tracer> m_TracerPtr;

		// List of the pixels in the view plane.
		RGBColor *m_Pixels;

		// List of the objects in the scene.
		ObjectList m_Objects;


	private:
		void DisplayPixel(const int, const int, const RGBColor &) const;
		void AddObject(std::shared_ptr<Object>);
		RGBColor MaxToOne(const RGBColor &) const;
		RGBColor ClampToColor(const RGBColor &, const RGBColor &) const;
};

inline void World::AddObject(std::shared_ptr<Object> objPtr) {
	m_Objects.push_back(objPtr);

}

#endif
