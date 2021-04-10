#ifndef _PADDLE_DROID_BLOCKS_HPP
#define _PADDLE_DROID_BLOCKS_HPP

#include <vector>
#include <cmath>

typedef struct block {
	float x;
	float y;
	bool active;
} block;

class Blocks {
    private:
        float m_width;
        float m_height;
        float m_gap;
        std::vector<block> m_blocks;
    public:
        void Init(float x1, float y1, float x2, float y2, float width, float height, float gap);
        void Clear();
        int Render();
};

void Blocks::Init(float x1, float y1, float x2, float y2, float width, float height, float gap) {
    int numX = static_cast<int>(floor((x2 - x1) / (width + gap)));
    int numY = static_cast<int>(floor((y2 - y1) / (height + gap)));
    int num = numX * numY;

    m_blocks.reserve(num);
    m_width = width;
    m_height = height;
    m_gap = gap;

    for (int i = 0; i < num; i++) {
        block b = {
            x1 + (((width / 2) + gap) * (i % numX)),
            y1 + ((height / 2) + gap),
            true
        };
        m_blocks.push_back(b);
    }
}

void Blocks::Clear() {
    m_blocks.clear();
}

#endif
