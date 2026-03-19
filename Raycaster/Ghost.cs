using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace Raycaster
{
    public class Ghost
    {
        public Vector2f Position { get; set; }
        private CircleShape shape;

        public Ghost(Vector2f position)
        {
            Position = position;
            shape = new CircleShape(4f);
            shape.FillColor = Color.Red;
            shape.Origin = new Vector2f(4f, 4f);
        }

        public void DrawOnMinimap(RenderWindow window)
        {
            shape.Position = Position;
            window.Draw(shape);
        }
    }
}

