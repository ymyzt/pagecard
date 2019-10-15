#include "Card3D_Sprite.h"

void Card3D_Sprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
#if CC_USE_CULLING
	// Don't do calculate the culling if the transform was not updated
	auto visitingCamera = Camera::getVisitingCamera();
	auto defaultCamera = Camera::getDefaultCamera();
	if (visitingCamera == defaultCamera) {
		_insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY) || visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
	}
	else
	{
		_insideBounds = renderer->checkVisibility(transform, _contentSize);
	}

	if (_insideBounds)
#endif
	{
		
		
// 		if (_isClockwise) {
// 			unsigned short indices[6];
// 			for (int i = 0; i < 6; i++)
// 			{
// 				indices[i] = _polyInfo.triangles.indices[i];
// 			}
// 			unsigned short a, b;
// 			a = indices[1];
// 			b = indices[4];
// 			indices[1] = indices[2];
// 			indices[2] = a;
// 			indices[4] = indices[5];
// 			indices[5] = b;
// 			_isClockwise = false;
// 			_polyInfo.triangles.indices = indices;
// 		}
		_trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
		//_trianglesCommand.set3D(true);
		
		//_trianglesCommand.setTransparent(false);
		renderer->addCommand(&_trianglesCommand);

#if CC_SPRITE_DEBUG_DRAW
		_debugDrawNode->clear();
		auto count = _polyInfo.triangles.indexCount / 3;
		auto indices = _polyInfo.triangles.indices;
		auto verts = _polyInfo.triangles.verts;
		for (ssize_t i = 0; i < count; i++)
		{
			//draw 3 lines
			Vec3 from = verts[indices[i * 3]].vertices;
			Vec3 to = verts[indices[i * 3 + 1]].vertices;
			_debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x, to.y), Color4F::WHITE);

			from = verts[indices[i * 3 + 1]].vertices;
			to = verts[indices[i * 3 + 2]].vertices;
			_debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x, to.y), Color4F::WHITE);

			from = verts[indices[i * 3 + 2]].vertices;
			to = verts[indices[i * 3]].vertices;
			_debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x, to.y), Color4F::WHITE);
		}
#endif //CC_SPRITE_DEBUG_DRAW
	}
}
Card3D_Sprite * Card3D_Sprite::create(const std::string path)
{
	auto cg = new Card3D_Sprite();
	if (cg&&cg->initWithFile(path))
		return cg;
	return NULL;
}
Card3D_Sprite::Card3D_Sprite()
	:_isClockwise(false)
{
}

Card3D_Sprite::~Card3D_Sprite()
{
}


