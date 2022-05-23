#pragma once

class Player {
public:
    MuSeoun::vec2 coord;
    MuSeoun::vec2 quad[4];
    float size;
    MuSeoun::vec3 color;

    Player(float size_, float x_, float y_, MuSeoun::vec3 col)
    {
        coord = MuSeoun::vec2(0, 0);
        size = 0.2;
        color = col;

        quad[0] = MuSeoun::vec2(-size, size);
        quad[1] = MuSeoun::vec2(size, size);
        quad[2] = MuSeoun::vec2(-size, -size);
        quad[3] = MuSeoun::vec2(size, -size);
    }
    ~Player()
    {

    }

    void MoveUp(float distance)
    {
        coord.y = distance;
    }

    void MoveRight(float distance)
    {
        coord.x = distance;
    }

    void Render()
    {
        quad[0] = quad[0] + coord;
        quad[1] = quad[1] + coord;
        quad[2] = quad[2] + coord;
        quad[3] = quad[3] + coord;

        glBegin(GL_TRIANGLES);
        glColor4f(color.x, color.y, color.z, 0.5f);
        glVertex3f(quad[0].x, quad[0].y, 0.0f);
        glVertex3f(quad[1].x, quad[1].y, 0.0f);
        glVertex3f(quad[2].x, quad[2].y, 0.0f);

        glVertex3f(quad[1].x, quad[1].y, 0.0f);
        glVertex3f(quad[3].x, quad[3].y, 0.0f);
        glVertex3f(quad[2].x, quad[2].y, 0.0f);

        glEnd();
    }

};
