#include "Card3D_Grid.h"

Card3D_Grid * Card3D_Grid::create(const Size & gridSize)
{
	auto cg = new Card3D_Grid();
	if(cg&&cg->initWithSize(gridSize))
		return cg;
	return NULL;
}

Card3D_Grid::Card3D_Grid()
{
}

Card3D_Grid::~Card3D_Grid()
{
}

void Card3D_Grid::blit()
{
	int n = _gridSize.width * _gridSize.height;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	//glCullFace(GL_BACK);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	_shaderProgram->use();
	_shaderProgram->setUniformsForBuiltins();;

	//
	// Attributes
	//

	// position
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _vertices);

	// texCoords
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _texCoordinates);

	glDrawElements(GL_TRIANGLES, (GLsizei)n * 6, GL_UNSIGNED_SHORT, _indices);
	glDisable(GL_CULL_FACE);
}
