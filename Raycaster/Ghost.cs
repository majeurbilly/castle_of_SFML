using SFML.System;

namespace Raycaster
{
    public class Ghost
    {
        public Vector2f Position { get; set; }

        public Ghost(Vector2f position)
        {
            Position = position;
        }
    }
}

