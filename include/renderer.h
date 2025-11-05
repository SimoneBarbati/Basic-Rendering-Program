#include <vector>

#include "shapes.h"

class Renderer
{
public:
    Renderer() = default;
    void Init();
    void RenderQuad(Quad& quad);

private:
    void LoadQuadVertices(Quad& quad);
    
    Quad lastDrawnQuad;
    unsigned int quadVao, quadVbo, quadEbo;
    std::vector<float> quadVertices;
    unsigned int quadIndices[6] = {
        0, 3, 2,
        0, 1, 3
    };
};