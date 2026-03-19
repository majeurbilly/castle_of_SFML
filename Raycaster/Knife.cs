using SFML.System;

namespace Raycaster
{
    public struct Knife
    {
        public Vector2f Position { get; set; }

        public Knife(Vector2f position)
        {
            Position = position;
        }
    }
}

