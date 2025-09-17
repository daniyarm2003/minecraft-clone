#include "blocks.h"
#include "block_atlas_face_selector.h"

namespace World::Chunks::Blocks {
    const Block AIR(0, false, std::make_unique<SimpleBlockAtlasFaceSelector>(0));
    const Block DIRT(1, true, std::make_unique<SimpleBlockAtlasFaceSelector>(1));
    const Block GRASS(2, true, std::make_unique<PillarShapeBlockAtlasFaceSelector>(2, 3, 1));
    const Block STONE(3, true, std::make_unique<SimpleBlockAtlasFaceSelector>(4));
}